#include "control_v2/common/mpc_solver.h"

#include <logging/plus_logger.h>
#include <metrics/macros.h>

#include "monitor/status_reporter.h"

using namespace drive::common::monitor;
namespace drive {
namespace control_v2 {
using common::monitor_msg::SystemState;
using namespace plusai::common::logging;

static Logger logger("mpc_solver");
// control dimension is fixed as 1, to reduce dynamic memory allocation
// need to use matrix to calculate it, if the input dimension is changed in the
// future
const int MpcSolver::kControlDimension = 1;

MpcSolver::MpcSolver(const int max_iteration, const double eps_abs,
                     const double eps_rel, const int check_termination_interval,
                     const double alpha) {
  _osqp_settings =
      reinterpret_cast<OSQPSettings *>(c_malloc(sizeof(OSQPSettings)));
  if (_osqp_settings == nullptr) {
    logger.error("malloc osqp settings failed");
  } else {
    osqp_set_default_settings(_osqp_settings);
    _osqp_settings->polish = true;
    _osqp_settings->max_iter = max_iteration;
    _osqp_settings->eps_abs = eps_abs;
    _osqp_settings->eps_rel = eps_rel;
    _osqp_settings->scaled_termination = true;
    _osqp_settings->check_termination = check_termination_interval;
    _osqp_settings->warm_start = true;
    _osqp_settings->alpha = alpha;
    if (::plusai::common::logging::GetLogVerbosityLevel() >= 4) {
      // print verbose outputs
      _osqp_settings->verbose = true;
    } else {
      _osqp_settings->verbose = false;
    }
    // TODO: get below const variable from config
    constexpr int DENSE_MATRIX_MAX_COLS = 256;
    constexpr int DENSE_MATRIX_MAX_ROWS = 256;
    _P_data.reserve(DENSE_MATRIX_MAX_COLS * DENSE_MATRIX_MAX_ROWS);
    _P_indices.reserve(DENSE_MATRIX_MAX_COLS * DENSE_MATRIX_MAX_ROWS);
    _P_indptr.reserve(DENSE_MATRIX_MAX_COLS + 1);
    _A_data.reserve(DENSE_MATRIX_MAX_COLS * DENSE_MATRIX_MAX_ROWS);
    _A_indices.reserve(DENSE_MATRIX_MAX_COLS * DENSE_MATRIX_MAX_ROWS);
    _A_indptr.reserve(DENSE_MATRIX_MAX_COLS + 1);
  }
}

MpcSolver::~MpcSolver() {
  OsqpCleanUp();
  if (_osqp_settings != nullptr) {
    c_free(_osqp_settings);
    _osqp_settings = nullptr;
  }
}

/**
 *      discrete linear predictive control solver, with control format
 *      x(i + 1) = A * x(i) + B * u (i) + C
 *      Format in standard qp_solver
 *      min X  : q(X) = 0.5 * X^T * H * X  + X^T * G
 *               with respect to: lc <= K * X <= uc
 *                                lb <= X <= ub
 *               where X = [x(k), x(k+1), ... x(k+N-1), u(k), u(k+1), ...
 * u(k+N-1)]^T
 * */
bool MpcSolver::SolveFirstRun(
    const Eigen::MatrixXd &matrix_a, const Eigen::MatrixXd &matrix_b,
    const Eigen::MatrixXd &matrix_c, const Eigen::MatrixXd &matrix_q,
    double lambda, double matrix_r, double lower_bound, double upper_bound,
    const Eigen::MatrixXd &lower_constraint,
    const Eigen::MatrixXd &upper_constraint, int control_horizon,
    const Eigen::MatrixXd &matrix_initial_state,
    const std::vector<Eigen::MatrixXd> &reference, std::vector<double> &control,
    int &osqp_solve_status) {
  SCOPED_TIMER("MpcSolver::SolveFirstRun");
  if (!CheckFirstRunDimension(matrix_a, matrix_b, matrix_q) ||
      !CheckConstraintDimension(matrix_a, lower_constraint, upper_constraint)) {
    StatusReporter::getInstance().reportSystemState(
        SystemState::CONTROL_CONFIG_ERROR);
    logger.error("MPC solver: One or more matrices have incompatible "
                 "dimensions. Aborting.");
    return false;
  }

  int prediction_horizon = static_cast<int>(reference.size());
  if (control_horizon > prediction_horizon) {
    control_horizon = prediction_horizon;
  }
  PLUS_VLOG(4, "first_run | control horizon: %% , prediction horizon: %% ",
            control_horizon, prediction_horizon);

  int state_dimension = static_cast<int>(matrix_b.rows());
  OsqpCleanUp();
  _osqp_data = reinterpret_cast<OSQPData *>(c_malloc(sizeof(OSQPData)));
  if (_osqp_data == nullptr) {
    logger.error("malloc osqp data failed");
    return false;
  } else {
    int num_param = (state_dimension + kControlDimension) * prediction_horizon;
    _osqp_data->n = num_param;
    _osqp_data->m = num_param + state_dimension * prediction_horizon;
    CalculateMatrixHessian(prediction_horizon, num_param, state_dimension,
                           matrix_q, lambda, matrix_r);
    DenseToCSCMatrix(_matrix_hessian, &_P_data, &_P_indices, &_P_indptr);
    _osqp_data->P =
        csc_matrix(num_param, num_param, _P_data.size(), _P_data.data(),
                   _P_indices.data(), _P_indptr.data());
    CalculateMatrixGradient(prediction_horizon, state_dimension, num_param,
                            matrix_q, lambda, reference);
    _osqp_data->q = _matrix_gradient.data();
    CalculateMatrixConstraint(prediction_horizon, control_horizon, num_param,
                              state_dimension, matrix_a, matrix_b);
    DenseToCSCMatrix(_matrix_constraint, &_A_data, &_A_indices, &_A_indptr);
    _osqp_data->A =
        csc_matrix(_osqp_data->m, _osqp_data->n, _A_data.size(), _A_data.data(),
                   _A_indices.data(), _A_indptr.data());
    CalculateConstraintVectors(
        prediction_horizon, control_horizon, state_dimension, lower_bound,
        upper_bound, lower_constraint, upper_constraint, matrix_initial_state);
    _osqp_data->l = _lower_constraint.data();
    _osqp_data->u = _upper_constraint.data();
  }
  _osqp_workspace = osqp_setup(_osqp_data, _osqp_settings);
  if (_osqp_workspace == nullptr) {
    logger.error("osqp setup failed");
    return false;
  }
  if (!SolveOsqp(prediction_horizon, state_dimension, control,
                 osqp_solve_status)) {
    return false;
  }
  return true;
}

bool MpcSolver::SolveHotStart(const Eigen::MatrixXd &matrix_a,
                              const Eigen::MatrixXd &matrix_q, double lambda,
                              const Eigen::MatrixXd &matrix_initial_state,
                              double lower_bound, double upper_bound,
                              const Eigen::MatrixXd &lower_constraint,
                              const Eigen::MatrixXd &upper_constraint,
                              const int control_horizon,
                              const std::vector<Eigen::MatrixXd> &reference,
                              std::vector<double> &control,
                              int &osqp_solve_status) {
  int prediction_horizon = static_cast<int>(reference.size());
  PLUS_VLOG(4, "hot_start | prediction horizon: %% ", prediction_horizon);

  int state_dimension = static_cast<int>(matrix_a.rows());
  int num_param = (state_dimension + kControlDimension) * prediction_horizon;
  CalculateMatrixGradient(prediction_horizon, state_dimension, num_param,
                          matrix_q, lambda, reference);
  CalculateConstraintVectors(
      prediction_horizon, control_horizon, state_dimension, lower_bound,
      upper_bound, lower_constraint, upper_constraint, matrix_initial_state);
  osqp_update_lin_cost(_osqp_workspace, _matrix_gradient.data());
  osqp_update_bounds(_osqp_workspace, _lower_constraint.data(),
                     _upper_constraint.data());
  if (!SolveOsqp(prediction_horizon, state_dimension, control,
                 osqp_solve_status)) {
    return false;
  }
  return true;
}

void MpcSolver::CalculateMatrixHessian(int prediction_horizon, int num_param,
                                       int state_dimension,
                                       const Eigen::MatrixXd &matrix_q,
                                       double lambda, double matrix_r) {
  _matrix_hessian = Eigen::MatrixXd::Zero(num_param, num_param);
  const int state_total_dim = state_dimension * prediction_horizon;
  for (int i = 0; i < prediction_horizon; i++) {
    for (int j = 0; j < state_dimension; j++) {
      _matrix_hessian(i * state_dimension + j, i * state_dimension + j) =
          matrix_q(j, j) * exp(i * lambda);
    }
    _matrix_hessian(state_total_dim + i * kControlDimension,
                    state_total_dim + i * kControlDimension) = matrix_r;
  }
}

void MpcSolver::CalculateMatrixGradient(
    int prediction_horizon, int state_dimension, int num_param,
    const Eigen::MatrixXd &matrix_q, double lambda,
    const std::vector<Eigen::MatrixXd> &reference) {
  SCOPED_TIMER("MpcSolver::CalculateMatrixGradient");
  _matrix_gradient = Eigen::MatrixXd::Zero(num_param, 1);
  for (int i = 0; i < prediction_horizon; i++) {
    _matrix_gradient.block(i * state_dimension, 0, state_dimension, 1) =
        -1.0 * matrix_q * exp(i * lambda) * reference[i];
  }
}

// TODO: C is zero matrix for current problem, will add it into calculation if
// it's non zero later
void MpcSolver::CalculateMatrixConstraint(int prediction_horizon,
                                          int control_horizon, int num_param,
                                          int state_dimension,
                                          const Eigen::MatrixXd &matrix_a,
                                          const Eigen::MatrixXd &matrix_b) {
  _matrix_constraint = Eigen::MatrixXd::Zero(
      (2 * state_dimension + kControlDimension) * prediction_horizon,
      num_param);

  _matrix_constraint.block(0, 0, state_dimension * prediction_horizon,
                           state_dimension * prediction_horizon) =
      -1.0 * Eigen::MatrixXd::Identity(state_dimension * prediction_horizon,
                                       state_dimension * prediction_horizon);

  for (int i = 1; i < prediction_horizon; i++) {
    _matrix_constraint.block(i * state_dimension, (i - 1) * state_dimension,
                             state_dimension, state_dimension) = matrix_a;
    _matrix_constraint.block(i * state_dimension,
                             (i - 1) * kControlDimension +
                                 prediction_horizon * state_dimension,
                             state_dimension, kControlDimension) = matrix_b;
  }

  _matrix_constraint.block(state_dimension * prediction_horizon, 0, num_param,
                           num_param) =
      Eigen::MatrixXd::Identity(num_param, num_param);

  if (control_horizon < prediction_horizon) {
    int equal_control_rows =
        kControlDimension * (prediction_horizon - control_horizon);
    _matrix_constraint.block(2 * state_dimension * prediction_horizon +
                                 kControlDimension * control_horizon,
                             state_dimension * prediction_horizon +
                                 kControlDimension * (control_horizon - 1),
                             equal_control_rows, equal_control_rows) =
        -1.0 *
        Eigen::MatrixXd::Identity(equal_control_rows, equal_control_rows);
  }
}

void MpcSolver::CalculateConstraintVectors(
    int prediction_horizon, int control_horizon, int state_dimension,
    double lower_bound, double upper_bound,
    const Eigen::MatrixXd &lower_constraint,
    const Eigen::MatrixXd &upper_constraint,
    const Eigen::MatrixXd &matrix_initial_state) {
  _lower_constraint = Eigen::MatrixXd::Zero(
      (2 * state_dimension + kControlDimension) * prediction_horizon, 1);
  _lower_constraint.block(0, 0, state_dimension, 1) =
      -1.0 * matrix_initial_state;
  _upper_constraint = _lower_constraint;
  for (int i = 0; i < prediction_horizon; i++) {
    _lower_constraint.block(state_dimension * prediction_horizon +
                                state_dimension * i,
                            0, state_dimension, 1) = lower_constraint;
    _upper_constraint.block(state_dimension * prediction_horizon +
                                state_dimension * i,
                            0, state_dimension, 1) = upper_constraint;
    if (i < control_horizon) {
      _lower_constraint(
          kControlDimension * i + 2 * state_dimension * prediction_horizon, 0) =
          lower_bound;
      _upper_constraint(
          kControlDimension * i + 2 * state_dimension * prediction_horizon, 0) =
          upper_bound;
    }
  }
}

bool MpcSolver::CheckFirstRunDimension(const Eigen::MatrixXd &matrix_a,
                                       const Eigen::MatrixXd &matrix_b,
                                       const Eigen::MatrixXd &matrix_q) {
  if (matrix_a.rows() != matrix_a.cols() ||
      matrix_b.rows() != matrix_a.rows() ||
      matrix_q.rows() != matrix_q.cols() ||
      matrix_q.rows() != matrix_b.rows()) {
    return false;
  }
  return true;
}

bool MpcSolver::CheckConstraintDimension(
    const Eigen::MatrixXd &matrix_a, const Eigen::MatrixXd &lower_constraint,
    const Eigen::MatrixXd &upper_constraint) {
  if (lower_constraint.rows() != upper_constraint.rows() ||
      lower_constraint.rows() != matrix_a.rows()) {
    return false;
  }
  return true;
}

bool MpcSolver::GetMPCStates(std::vector<double> &augmented_mpc_states,
                             int prediction_horizon, int state_dimension) {
  if (_osqp_workspace == nullptr) {
    logger.error("osqp failed, get MPC states failed");
    return false;
  }
  if (_osqp_workspace->solution == nullptr ||
      _osqp_workspace->solution->x == nullptr) {
    logger.error("The solution from OSQP is nullptr");
    return false;
  }

  augmented_mpc_states.assign(_osqp_workspace->solution->x,
                              _osqp_workspace->solution->x +
                                  prediction_horizon * state_dimension);
  return true;
}

bool MpcSolver::SolveOsqp(int prediction_horizon, int state_dimension,
                          std::vector<double> &control,
                          int &osqp_solve_status) {
  SCOPED_TIMER("MpcSolver::SolveOsqp");
  osqp_solve(_osqp_workspace);
  if (_osqp_workspace == nullptr) {
    logger.error("osqp setup failed");
    return false;
  }
  if (_osqp_workspace->info == nullptr) {
    logger.error("osqp workspace info is nullptr");
    return false;
  }
  osqp_solve_status = _osqp_workspace->info->status_val;
  if (osqp_solve_status != 1) {
    logger.error("failed optimization status: %% ",
                 _osqp_workspace->info->status);
    return false;
  }
  if (_osqp_workspace->solution == nullptr ||
      _osqp_workspace->solution->x == nullptr) {
    logger.error("The solution from OSQP is nullptr");
    return false;
  }
  if (std::isnan(
          _osqp_workspace->solution->x[state_dimension * prediction_horizon])) {
    logger.error("The solver result is nan");
    return false;
  }

  control.assign(_osqp_workspace->solution->x + _osqp_data->n -
                     prediction_horizon,
                 _osqp_workspace->solution->x + _osqp_data->n);
  return true;
}

} // namespace control_v2
} // namespace drive
