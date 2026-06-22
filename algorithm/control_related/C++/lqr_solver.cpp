#pragma once

/**
 * @file
 * @brief Solver for discrete-time linear quadratic problem.
 */

#include "metrics/macros.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <limits>
#include <logging/plus_logger.h>
#include <type_traits>

namespace drive {
namespace control_v2 {

using namespace plusai::common::logging;

namespace detail {

template <typename T>
static constexpr bool is_eigen_matrix =
    std::is_base_of<Eigen::MatrixBase<std::decay_t<T>>, std::decay_t<T>>::value;

template <typename... Ts> struct is_all_eigen_matrix_impl : std::true_type {};

template <typename T, typename... Ts>
struct is_all_eigen_matrix_impl<T, Ts...>
    : std::integral_constant<bool, is_eigen_matrix<T> &&
                                       is_all_eigen_matrix_impl<Ts...>::value> {
};
} // namespace detail

template <typename... Ts>
static constexpr bool is_all_eigen_matrix =
    detail::is_all_eigen_matrix_impl<Ts...>::value;

/**
 * @brief Solver for discrete-time linear quadratic problem.
 * @param A The system dynamic matrix
 * @param B The control matrix
 * @param Q The cost matrix for system state
 * @param R The cost matrix for control output
 * @param tolerance The numerical tolerance for solving
 *        Algebraic Riccati equation (ARE)
 * @param max_num_iteration The maximum iterations for solving ARE
 * @param ptr_K The feedback control matrix (pointer)
 */
class LQRProblemSolver {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  LQRProblemSolver(int state_size);

  LQRProblemSolver() = default;

  void SetStateSize(int state_size);

  template <
      typename Matrix1, typename Matrix2, typename Matrix3, typename Matrix4,
      std::enable_if_t<is_all_eigen_matrix<Matrix1, Matrix2, Matrix3, Matrix4>,
                       bool> = true>
  void SolveLQRProblem(const Matrix1 &A, const Matrix2 &B, const Matrix1 &Q,
                       const Matrix3 &R, double tolerance,
                       uint max_num_iteration, Matrix4 &K, Matrix1 &P) {
    static_assert(
        Matrix1::RowsAtCompileTime == Matrix1::ColsAtCompileTime &&
            static_cast<int>(Matrix1::RowsAtCompileTime) ==
                static_cast<int>(Matrix2::RowsAtCompileTime) &&
            Matrix3::RowsAtCompileTime == Matrix3::ColsAtCompileTime &&
            static_cast<int>(Matrix3::RowsAtCompileTime) ==
                static_cast<int>(Matrix2::ColsAtCompileTime),
        "LQR solver: one or more matrices have incompatible dimensions.");
    PLUS_VLOG(2, "SolveLQRProblem:  ");
    PLUS_VLOG(2, "A: %%  ", A);
    PLUS_VLOG(2, "B: %%  ", B);
    PLUS_VLOG(2, "Q: %%  ", Q);
    PLUS_VLOG(2, "R: %%  ", R);

    auto _AT = A.transpose().eval();
    auto _BT = B.transpose().eval();
    Matrix1 _P_next;
    Matrix1 _PA;
    Matrix3 _P_tmp;
    Eigen::Matrix<typename Matrix1::Scalar, Matrix1::RowsAtCompileTime,
                  Matrix2::ColsAtCompileTime>
        _PB;

    // Solves a discrete-time Algebraic Riccati equation (DARE)
    // Calculate Matrix Difference Riccati Equation, initialize P and Q
    // Matrix P = Q;
    uint num_iteration = 0;
    double diff = std::numeric_limits<double>::max();
    while (num_iteration++ < max_num_iteration && diff > tolerance) {
      // _P_next = _AT * P * A - _AT * P * B * (R + _BT * P * B).inverse() * _BT
      // * P * A + Q;
      // https://eigen.tuxfamily.org/dox/TopicWritingEfficientProductExpression.html
      // break down into below
      _PA.noalias() = P * A;
      _PB.noalias() = P * B;
      _P_tmp = R;
      _P_tmp.noalias() += _BT * _PB;
      _P_next = Q;
      _P_next.noalias() += _AT * _PA;
      _P_next.noalias() -= _AT * _PB * _P_tmp.inverse() * _BT * _PA;
      // check the difference between P and P_next
      diff = fabs((_P_next - P).maxCoeff());
      P = _P_next;
    }

    if (num_iteration >= max_num_iteration) {
      PLUS_VLOG(2,
                "LQR solver cannot converge to a solution, last consecutive "
                "result diff is: "
                "%%  ",
                diff);
    } else {
      PLUS_LOG(info, "LQR solver converged at iteration: %%  ", num_iteration);
    }
    _P_tmp = R;
    _P_tmp.noalias() += _BT * P * B;
    K.noalias() = _P_tmp.inverse() * _BT * P * A;
  }

private:
  int _kStateSize;
};

} // namespace control_v2
} // namespace drive
