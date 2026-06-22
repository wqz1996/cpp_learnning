#include <Eigen/Dense>

/**
 * @class KalmanFilter
 *
 * @brief Implements a discrete-time Kalman filter.
 *
 * @param XN dimension of state
 * @param ZN dimension of observations
 * @param UN dimension of controls
 */
template <typename T, unsigned int XN, unsigned int ZN, unsigned int UN>
class KalmanFilter {
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

public:
  /**
   * @brief Constructor which defers initialization until the initial state
   * distribution parameters are set (with SetStateEstimate),
   * typically on the first observation
   */

  KalmanFilter() { resetMatrix(); }
  /**
   * @brief Constructor which fully initializes the Kalman filter
   * @param X Mean of the state belief distribution
   * @param P Covariance of the state belief distribution
   */
  KalmanFilter(const Eigen::Matrix<T, XN, 1> &X,
               const Eigen::Matrix<T, XN, XN> &P) {
    setStateEstimate(X, P);
  }

  // KalmanFilter(const KalmanFilterParam& kalman_filter_param) {
  // resetMatrix(kalman_filter_param); }

  /**
   * @brief Destructor
   */
  ~KalmanFilter() = default;

  /**
   * @brief reset matrixs value
   */
  void resetMatrix() {
    _is_initialized = false;
    _X.setZero();
    _P.setZero();
    _A.setIdentity();
    _Q.setIdentity();
    _B.setZero();
    _H.setZero();
    _R.setZero();
    _I.setIdentity();
  }

  /**
   * @brief Sets the initial state belief distribution.
   *
   * @param X Mean of the state belief distribution
   * @param P Covariance of the state belief distribution
   */
  void setStateEstimate(const Eigen::Matrix<T, XN, 1> &X,
                        const Eigen::Matrix<T, XN, XN> &P) {
    _X = X;
    _P = P;
    _is_initialized = true;
  }

  /**
   * @brief Changes the system transition function under zero control.
   *
   * @param A New transition matrix
   */
  void setTransitionMatrix(const Eigen::Matrix<T, XN, XN> &A) { _A = A; }

  /**
   * @brief Changes the covariance matrix of the transition noise.
   *
   * @param Q New covariance matrix
   */
  void setTransitionNoise(const Eigen::Matrix<T, XN, XN> &Q) { _Q = Q; }

  /**
   * @brief Changes the observation matrix, which maps states to observations.
   *
   * @param H New observation matrix
   */
  void setObservationMatrix(const Eigen::Matrix<T, ZN, XN> &H) { _H = H; }

  /**
   * @brief Changes the covariance matrix of the observation noise.
   *
   * @param R New covariance matrix
   */
  void setObservationNoise(const Eigen::Matrix<T, ZN, ZN> &R) { _R = R; }

  /**
   * @brief Changes the covariance matrix of current state belief distribution.
   *
   * @param P New state covariance matrix
   */
  void setStateCovariance(const Eigen::Matrix<T, XN, XN> &P) { _P = P; }

  /**
   * @brief Changes the control matrix in the state transition rule.
   *
   * @param B New control matrix
   */
  void setControlMatrix(const Eigen::Matrix<T, XN, UN> &B) { _B = B; }

  /**
   * @brief get estimated state
   *
   * @param[out] matrix - return state x
   */
  const Eigen::Matrix<T, XN, 1> &getStateEstimate() const { return _X; }

  /**
   * @brief get state covariance
   *
   * @param[out] matrix - return state covariance P
   */
  const Eigen::Matrix<T, XN, XN> &getStateCovariance() const { return _P; }

  /**
   * @brief get estimated state
   *
   * @param[out] bool - return if kalman filter is initialized
   */
  bool isInitialized() const { return _is_initialized; }

  /**
   * @brief Updates the state belief distribution given the control input U.
   *
   * @param U Control input
   */
  void predict(const Eigen::Matrix<T, UN, 1> &U);

  /**
   * @brief Updates the state belief distribution given an observation Z.
   *
   * @param Z Observation
   */
  void correct(const Eigen::Matrix<T, ZN, 1> &Z,
               const Eigen::Matrix<T, ZN, XN> &H,
               const Eigen::Matrix<T, ZN, ZN> &R);

  void correct(const Eigen::Matrix<T, ZN, 1> &Z);

private:
  bool _is_initialized = false;
  // estimated state
  Eigen::Matrix<T, XN, 1> _X;
  // estimated state covariance
  Eigen::Matrix<T, XN, XN> _P;
  // transition martix
  Eigen::Matrix<T, XN, XN> _A;
  // pure transition _A * _X -> reduce memory reallocation
  Eigen::Matrix<T, XN, 1> _T;
  // control input effect martix
  Eigen::Matrix<T, XN, UN> _B;
  // control input transition _B * U -> reduce memory reallocation
  Eigen::Matrix<T, XN, 1> _Y;

  // process noise covariance martix of state
  Eigen::Matrix<T, XN, XN> _Q;

  // observation constant matrix
  Eigen::Matrix<T, ZN, XN> _H;
  // measurement noise covariance martix
  Eigen::Matrix<T, ZN, ZN> _R;

  // _P * _A.transpose() or _PT * _P-> reduce memory reallocation
  Eigen::Matrix<T, XN, XN> _P_tmp;
  // Z - _H * _X -> reduce memory reallocation
  Eigen::Matrix<T, ZN, 1> _O;
  // H_ * P_ - > reduce memory reallocation
  Eigen::Matrix<T, ZN, XN> _S_tmp;
  // H_ * P_ * H_.transpose() + R_ - > reduce memory reallocation
  Eigen::Matrix<T, ZN, ZN> _S;
  // kalman gain -> reduce memory re-allocation.
  Eigen::Matrix<T, XN, ZN> _K;
  // kalman gain -> reduce memory re-allocation.
  Eigen::Matrix<T, XN, ZN> _K_tmp;
  // identity matrix -> reduce memory reallocation
  Eigen::Matrix<T, XN, XN> _I;
  // I - K*H -> reduce memory reallocation
  Eigen::Matrix<T, XN, XN> _PT;
};

template <typename T, unsigned int XN, unsigned int ZN, unsigned int UN>
void KalmanFilter<T, XN, ZN, UN>::predict(const Eigen::Matrix<T, UN, 1> &U) {
  // X = np.dot(A, X) + np.dot(B, U)
  // P = np.dot(A, np.dot(P, A.T)) + Q
  // use lazy evaluation to speed up the matrix multiplication
  _T.noalias() = _A * _X;
  _Y.noalias() = _B * U;
  _X = _T + _Y;
  // _P = _A * _P * _A.transpose() + _Q;
  _P_tmp.noalias() = _P * _A.transpose();
  _P.noalias() = _A * _P_tmp;
  _P += _Q;
}

template <typename T, unsigned int XN, unsigned int ZN, unsigned int UN>
void KalmanFilter<T, XN, ZN, UN>::correct(const Eigen::Matrix<T, ZN, 1> &Z) {
  // _O = z - _H * _X;
  _O.noalias() = Z - _H.lazyProduct(_X);
  // _S = _H * _P * _H.transpose() + _R;
  _S_tmp.noalias() = _H * _P;
  _S.noalias() = _S_tmp * _H.transpose();
  _S += _R;

  // need pseudo inverse to guarantee the float point computation and
  // det(M) = 0 issues.
  // _K = _P * _H.transpose() * PseudoInverse<T, ZN>(_S);
  _K_tmp.noalias() = _P * _H.transpose();
  _K.noalias() = _K_tmp * _S.completeOrthogonalDecomposition().pseudoInverse();

  // _X = _X + _K * _O;
  _X.noalias() = _X + _K.lazyProduct(_O);

  // _P = (Eigen::Matrix<T, XN, XN>::Identity() - _K * _H) * _P;
  _PT.noalias() = _I - _K.lazyProduct(_H);
  _P_tmp.noalias() = _PT * _P;
  _P = _P_tmp;
}
