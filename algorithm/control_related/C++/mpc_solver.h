#pragma once

/**
 * @file mpc_solver.h
 * @brief Convert mpc problem to qp based problem and solve.
 */

#include "Eigen/Core"
#include "Eigen/Dense"
#include "Eigen/LU"
#include "osqp/osqp.h"
#include <gtest/gtest_prod.h>
#include <memory>
#include <vector>

namespace drive {
namespace control_v2 {

class MpcSolver {
public:
  MpcSolver(const int max_iteration, const double eps_abs, const double eps_rel,
            const int check_termination_interval, const double alpha);
  ~MpcSolver();
  /**
   * @brief Solver for discrete-time model predictive control problem.
   * @param matrix_a The system dynamic matrix
   * @param matrix_b The control matrix
   * @param matrix_c The disturbance matrix
   * @param matrix_q The cost matrix for control state
   * @param lambda The parameter of the descending exponent for cost matrix q,
   * must be negative
   * @param lower_bound The lower bound on control input
   * @param upper_bound The upper bound on control input
   * @param matrix_initial_state The initial state matrix
   * @param reference The control reference vector with respect to time
   * @param eps The control convergence tolerance
   * @param max_iter The maximum iterations for solving ARE
   * @param control The feedback control matrix (pointer)
   * @param lower_constraint The lower constraint on control state
   * @param upper_constraint The upper constraint on control state
   */
  bool SolveFirstRun(const Eigen::MatrixXd &matrix_a,
                     const Eigen::MatrixXd &matrix_b,
                     const Eigen::MatrixXd &matrix_c,
                     const Eigen::MatrixXd &matrix_q, double lambda,
                     double matrix_r, double lower_bound, double upper_bound,
                     const Eigen::MatrixXd &lower_constraint,
                     const Eigen::MatrixXd &upper_constraint,
                     int control_horizon,
                     const Eigen::MatrixXd &matrix_initial_state,
                     const std::vector<Eigen::MatrixXd> &reference,
                     std::vector<double> &control, int &osqp_solve_status);

  bool SolveHotStart(const Eigen::MatrixXd &matrix_a,
                     const Eigen::MatrixXd &matrix_q, double lambda,
                     const Eigen::MatrixXd &matrix_initial_state,
                     double lower_bound, double upper_bound,
                     const Eigen::MatrixXd &lower_constraint,
                     const Eigen::MatrixXd &upper_constraint,
                     const int control_horizon,
                     const std::vector<Eigen::MatrixXd> &reference,
                     std::vector<double> &control, int &osqp_solve_status);

  bool GetMPCStates(std::vector<double> &augmented_mpc_states,
                    int prediction_horizon, int state_dimension);

private:
  static const int kControlDimension;
  Eigen::MatrixXd _matrix_hessian;
  Eigen::MatrixXd _matrix_gradient;
  Eigen::MatrixXd _lower_constraint;
  Eigen::MatrixXd _upper_constraint;
  Eigen::MatrixXd _matrix_constraint;

  void CalculateMatrixHessian(int prediction_horizon, int num_param,
                              int state_dimension,
                              const Eigen::MatrixXd &matrix_q, double lambda,
                              double matrix_r);

  void CalculateMatrixGradient(int prediction_horizon, int state_dimension,
                               int num_param, const Eigen::MatrixXd &matrix_q,
                               double lambda,
                               const std::vector<Eigen::MatrixXd> &reference);

  void CalculateMatrixConstraint(int prediction_horizon, int control_horizon,
                                 int num_param, int state_dimension,
                                 const Eigen::MatrixXd &matrix_a,
                                 const Eigen::MatrixXd &matrix_b);

  void CalculateConstraintVectors(int prediction_horizon, int control_horizon,
                                  int state_dimension, double lower_bound,
                                  double upper_bound,
                                  const Eigen::MatrixXd &lower_constraint,
                                  const Eigen::MatrixXd &upper_constraint,
                                  const Eigen::MatrixXd &matrix_initial_state);

  bool CheckFirstRunDimension(const Eigen::MatrixXd &matrix_a,
                              const Eigen::MatrixXd &matrix_b,
                              const Eigen::MatrixXd &matrix_q);

  bool CheckConstraintDimension(const Eigen::MatrixXd &matrix_a,
                                const Eigen::MatrixXd &lower_constraint,
                                const Eigen::MatrixXd &upper_constraint);

  FRIEND_TEST(MpcSolverTest, CheckMatrixDimension);
  FRIEND_TEST(MpcSolverTest, NonFullRankMatrix);
  FRIEND_TEST(MpcSolverTest, NullMatrix);
  FRIEND_TEST(MpcSolverTest, CalculateMatrixHessian);
  FRIEND_TEST(MpcSolverTest, CalculateMatrixGradient);
  FRIEND_TEST(MpcSolverTest, CalculateMatrixConstraint);
  FRIEND_TEST(MpcSolverTest, CalculateConstraintVectors);
  FRIEND_TEST(MpcSolverTest, GetMpcStates);

  OSQPData *_osqp_data = nullptr;
  OSQPSettings *_osqp_settings = nullptr;
  OSQPWorkspace *_osqp_workspace = nullptr;
  std::vector<c_float> _P_data;
  std::vector<c_int> _P_indices;
  std::vector<c_int> _P_indptr;
  std::vector<c_float> _A_data;
  std::vector<c_int> _A_indices;
  std::vector<c_int> _A_indptr;

  void OsqpCleanUp() {
    if (_osqp_workspace != nullptr) {
      osqp_cleanup(_osqp_workspace);
      _osqp_workspace = nullptr;
    }
    if (_osqp_data != nullptr) {
      if (_osqp_data->A != nullptr) {
        c_free(_osqp_data->A);
        _osqp_data->A = nullptr;
      }
      if (_osqp_data->P != nullptr) {
        c_free(_osqp_data->P);
        _osqp_data->P = nullptr;
      }
      c_free(_osqp_data);
      _osqp_data = nullptr;
    }
  }

  bool SolveOsqp(int prediction_horizon, int state_dimension,
                 std::vector<double> &control, int &osqp_solve_status);

  template <typename T, int M, int N, typename D>
  void DenseToCSCMatrix(const Eigen::Matrix<T, M, N> &dense_matrix,
                        std::vector<T> *data, std::vector<D> *indices,
                        std::vector<D> *indptr) {
    int data_count = 0;
    data->clear();
    data->reserve(dense_matrix.cols() * dense_matrix.rows());
    indices->clear();
    indices->reserve(dense_matrix.cols() * dense_matrix.rows());
    indptr->clear();
    indptr->reserve(dense_matrix.cols() + 1);
    for (int c = 0; c < dense_matrix.cols(); ++c) {
      indptr->emplace_back(data_count);
      for (int r = 0; r < dense_matrix.rows(); ++r) {
        if (std::fabs(dense_matrix(r, c)) < 1e-6) {
          continue;
        }
        data->emplace_back(dense_matrix(r, c));
        ++data_count;
        indices->emplace_back(r);
      }
    }
    indptr->emplace_back(data_count);
  }
};

typedef std::unique_ptr<MpcSolver> MpcSolverPtr;

} // namespace control_v2
} // namespace drive
