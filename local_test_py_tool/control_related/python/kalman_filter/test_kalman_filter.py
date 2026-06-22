#!/usr/bin/env python3
import random
import numpy as np
from collections import deque
import matplotlib
import matplotlib.pyplot as plt
import logging

StateNum = 2  # system state number
ObservNum = 1  # system observer number
ControlNum = 1  #system control number
logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.INFO)

FIG_CONFIG = {
    'figsize': (25, 20),
    'dpi': 80,
    'fontsize': 12,
    'subplots_adjust_left': 0.08,
    'subplots_adjust_bottom': 0.06,
    'subplots_adjust_right': 0.92,
    'subplots_adjust_top': 0.95,
    'subplots_adjust_wspace': 0.15,
    'subplots_adjust_hspace': 0.20,
}


def rmse(input_list):
    rmse = np.sqrt(sum([v**2 for v in input_list]) / len(input_list))
    return rmse


class ModelGenerator:

    def __init__(self, model_order, tau, gain, ts, delay_time):
        self._model_order = model_order
        self._tau = tau
        self._gain = gain
        self._last_y = None
        self._ts = ts
        self._ad = (1.0 + 0.5 * ts * (-1.0 / tau)) / (1.0 - 0.5 * ts *
                                                      (-1.0 / tau))
        self._bd = (gain / tau) * ts / (1.0 - 0.5 * ts * (-1.0 / tau))
        self._is_inited_state = False
        self._delay_time = delay_time
        self._delay_buffer = deque(maxlen=round(delay_time / ts) + 1)
        self._trigger_model_flag = False

    def model_generator(self, model_input):
        delayed_model_input = self.pure_delay(model_input)
        y = self._ad * self._last_y + self._bd * delayed_model_input
        self._last_y = y

        return y

    def set_init_state(self):
        self._last_y = 0.0
        self._is_inited_state = True
        self._trigger_model_flag = False

    def pure_delay(self, input):
        count = round(self._delay_time / self._ts)
        self._delay_buffer.append(input)
        if len(self._delay_buffer) == count + 1:
            return self._delay_buffer.popleft()
        else:
            return 0.0

    def reset(self):
        self._delay_buffer.clear()
        self._is_inited_state = False
        self._trigger_model_flag = False


class KalmanFilter:

    def __init__(self, KStateNum, KControlNum, KObservationNum) -> None:
        self._A = np.mat(np.eye(KStateNum))  # transition matrix
        self._B = np.mat(np.zeros((KStateNum, KControlNum)))  # control matrix
        self._H = np.mat(np.zeros(
            (KObservationNum, KStateNum)))  # observation matrix
        self._P = np.mat(np.eye(KStateNum))  # estimate state covariance matrix
        self._R = np.mat(
            np.eye(KObservationNum))  # measurement noise covariance matrix
        self._Q = np.mat(np.eye(KStateNum))  # process  noise covariance matrix
        self._I = np.mat(np.eye(KStateNum))  # identity matrix
        self._X = np.mat(np.zeros(
            (KStateNum, KControlNum)))  # k step state matrix

        self._Y = np.mat(np.zeros(
            (KStateNum, KControlNum)))  # pre-fit residual
        self._S = np.mat(np.zeros(
            KObservationNum))  # Innovation (or pre-fit residual) covariance
        self._K = np.mat(np.zeros((KStateNum, KObservationNum)))
        self._is_init_state = False

    def set_covariance_matrix(self, R, Q):
        self._R = R
        self._Q = Q

    def set_measurement_covariance_matrix(self, R):
        self._R = R

    def set_process_covariance_matrix(self, Q):
        self._Q = Q

    def set_transition_matrix(self, A):
        self._A = A

    def set_control_matrix(self, B):
        self._B = B

    def set_observation_matrix(self, H):
        self._H = H

    def set_state_covariance(self, P):
        self._P = P

    def reset_matrix(self):
        self._X.fill(0)
        self._P.fill(0)
        self._B.fill(0)
        self._H.fill(0)
        self._Q[:] = np.eye(self._Q.shape[0])
        self._R[:] = np.eye(self._R.shape[0])

    def set_init_state(self, X):
        self._X = X
        self._is_init_state = True

    def predict(self, U):
        # print("update")
        ## compute predict state X (priori)
        # X(k|k-1) = A(k) * X(k-1|k-1) + B(k) * U(k)
        self._X = self._A * self._X + self._B * U
        ## compute predict coveriance
        # P(k\k-1) = A(k) * P(k-1) * A.T + Q(k)
        self._P = self._A * self._P * self._A.T + self._Q

    def correct(self, Z):
        #print("correct")
        ## compute pre-fit residual
        # Y(k) = Z(k) - H(k) * X(k|k-1)
        self._Y = Z - self._H * self._X
        ## compute innovation covariance
        # S(k) = H(k) * P(k|k-1) * H.T(k) + R(k)
        self._S = self._H * self._P * self._H.T + self._R
        ## compute optimal kalman gain
        # K(k) = P(k|k-1) * H(k).T * S.inv()
        self._K = self._P * self._H.T * np.linalg.inv(self._S)
        ## update state estimate by using residual posteriori
        # x(k|k) = x(k|k-1) + K(k) * y(k)
        self._X = self._X + self._K * self._Y
        ## compute estimate covariance posteriori
        # P(k|k) = (I - K(k)H(k))P(k|k-1)
        self._P = (self._I - self._K * self._H) * self._P
        ## compute post-fit residual
        # Y(k|k) = Z(k) - H(k) * X(k|k)
        self._Y = Z - self._H * self._X
        # ## direct compute X(k|k)
        # self._X = (self._I - self._K * self._H) * self._X + self._K * Z


class AccEstimate:

    def __init__(self, KStateNum, KControlNum, KObservationNum):
        self._kalman_filter = KalmanFilter(KStateNum, KControlNum,
                                           KObservationNum)
        self._A = np.mat(np.eye(KStateNum))
        self._A[0, 1] = 0.05
        self._B = np.mat(np.zeros((KStateNum, KControlNum)))
        self._C_from_v = np.mat(np.zeros((KObservationNum, KStateNum)))
        self._C_from_v[0, 0] = 1
        self._C_from_a = np.mat(np.zeros((KObservationNum, KStateNum)))
        self._C_from_a[0, 1] = 1
        self._C_list = [self._C_from_v, self._C_from_a]
        self._R_from_v = np.mat(np.zeros((KObservationNum, KObservationNum)))
        self._R_from_a = np.mat(np.zeros((KObservationNum, KObservationNum)))
        self._R_from_v[0, 0] = 0.05
        self._R_from_a[0, 0] = 0.05
        self._R_list = [self._R_from_v, self._R_from_a]
        self._R = np.mat(np.eye(KObservationNum))
        self._Q = np.mat(np.eye(KStateNum))
        self._Q[0, 0] = 0.01
        self._Q[1, 1] = 0.01
        self._init_P = np.mat(np.eye(KStateNum))
        self._init_P[0, 0] = 1.0
        self._init_P[1, 1] = 1.0
        self._kalman_filter.set_process_covariance_matrix(self._Q)
        self._kalman_filter.set_state_covariance(self._init_P)
        self._kalman_filter.set_transition_matrix(self._A)
        self._kalman_filter.set_control_matrix(self._B)

    def init_state(self, input):
        if not self._kalman_filter._is_init_state:
            self._kalman_filter.set_init_state(input)

    def update(self, input):
        u = np.mat([0])
        self._kalman_filter.predict(u)
        for i in range(len(input)):
            self._kalman_filter.set_observation_matrix(self._C_list[i])
            self._kalman_filter.set_measurement_covariance_matrix(
                self._R_list[i])
            self._kalman_filter.correct(input[i])


if __name__ == '__main__':
    print("main function")
    start_t = 0
    end_t = 10
    fs = 20
    t = np.linspace(start_t, end_t, (end_t - start_t) * fs)
    frequency = 0.1
    amplitude = 1
    phase_bias = 0
    amplitude_bias = 0
    model_input = amplitude * np.sin(2 * np.pi * frequency * t +
                                     phase_bias) + amplitude_bias

    velocity_signal = amplitude * np.sin(2 * np.pi * frequency * t +
                                         phase_bias) + amplitude_bias
    acceleration_signal = amplitude * np.cos(2 * np.pi * frequency * t +
                                             phase_bias) + amplitude_bias

    ## const acceleration motion
    # init_velocity = 0

    # init_acceleration = 0.5

    # acceleration_signal = [init_acceleration for _ in t]

    # velocity_signal = [init_velocity + init_acceleration * time for time in t]
    ###########################################################################

    model_output = []

    num_samples = (end_t - start_t) * fs
    ## test white noise
    mean = 0  # avg
    variance = 0.01
    white_noise = np.random.normal(mean, np.sqrt(variance), num_samples)
    # velocity noise
    v_mean = 0  # avg
    v_variance = 0.05
    v_white_noise = np.random.normal(v_mean, np.sqrt(v_variance), num_samples)
    # acceleration noise
    a_mean = 0  # avg
    a_variance = 0.05
    a_white_noise = np.random.normal(a_mean, np.sqrt(a_variance), num_samples)

    velocity_signal_with_white_noise = [
        a + b for a, b in zip(velocity_signal, v_white_noise)
    ]
    acceleration_signal_with_white_noise = [
        a + b for a, b in zip(acceleration_signal, a_white_noise)
    ]

    ## first order model
    first_order_model = ModelGenerator(model_order=1,
                                       tau=0.3,
                                       gain=1.0,
                                       ts=1 / fs,
                                       delay_time=0)
    first_order_model.set_init_state()

    for idx in range(len(t)):
        model_output.append(first_order_model.model_generator(
            model_input[idx]))

    model_with_white_noise = [a + b for a, b in zip(model_output, white_noise)]

    kalman_filter = KalmanFilter(StateNum, ControlNum, ObservNum)
    A = np.mat(np.eye(StateNum))
    A[0, 1] = 1 / fs
    kalman_filter.set_transition_matrix(A)

    B = np.mat(np.zeros((StateNum, ControlNum)))
    kalman_filter.set_control_matrix(B)

    C = np.mat(np.zeros((ObservNum, StateNum)))
    C[0, 0] = 1
    #C[1, 1] = 1
    kalman_filter.set_observation_matrix(C)

    Q = np.mat(np.eye(StateNum))
    Q[0, 0] = 0.01
    Q[1, 1] = 0.01

    R = np.mat(np.zeros((ObservNum, ObservNum)))
    R[0, 0] = 0.05
    #R[1, 1] = a_variance
    kalman_filter.set_covariance_matrix(R, Q)

    P = np.mat(np.zeros((StateNum, StateNum)))
    P[0, 0] = 1
    P[1, 1] = 1
    kalman_filter.set_state_covariance(P)

    a_kalman_filter = []
    v_kalman_filter = []
    P_result_0_0 = []
    P_result_0_1 = []
    P_result_1_0 = []
    P_result_1_1 = []
    for v, a in zip(velocity_signal_with_white_noise,
                    acceleration_signal_with_white_noise):
        init_state = np.mat(np.zeros((StateNum, ControlNum)))
        init_state[0, 0] = v
        init_state[1, 0] = a
        if not kalman_filter._is_init_state:
            kalman_filter.set_init_state(init_state)
        kalman_filter.predict(0)
        kalman_filter.correct(v)
        v_kalman_filter.append(kalman_filter._X[0, 0])
        a_kalman_filter.append(kalman_filter._X[1, 0])
        P_result_0_0.append(kalman_filter._P[0, 0])
        P_result_0_1.append(kalman_filter._P[0, 1])
        P_result_1_0.append(kalman_filter._P[1, 0])
        P_result_1_1.append(kalman_filter._P[1, 1])

    fuse_acc_v_kalman_filtered = []
    fuse_acc_a_kalman_filtered = []

    fuse_acc_kalman_filter = AccEstimate(StateNum, ControlNum, ObservNum)
    for v, a in zip(velocity_signal_with_white_noise,
                    acceleration_signal_with_white_noise):
        init_state = np.mat(np.zeros((StateNum, ControlNum)))
        init_state[0, 0] = v
        init_state[1, 0] = a
        fuse_acc_kalman_filter.init_state(init_state)
        fuse_acc_kalman_filter.update(init_state)
        fuse_acc_v_kalman_filtered.append(
            fuse_acc_kalman_filter._kalman_filter._X[0, 0])
        fuse_acc_a_kalman_filtered.append(
            fuse_acc_kalman_filter._kalman_filter._X[1, 0])

    fuse_acc_a_error = [
        a - b for a, b in zip(fuse_acc_a_kalman_filtered, acceleration_signal)
    ]
    fuse_acc_v_error = [
        a - b for a, b in zip(fuse_acc_v_kalman_filtered, velocity_signal)
    ]

    print("RMSE fuse_a: {} fuse_v: {}".format(rmse(fuse_acc_a_error),
                                              rmse(fuse_acc_v_error)))
    print("STD fuse_a: {} fuse_v:{}".format(np.std(fuse_acc_a_error),
                                            np.std(fuse_acc_v_error)))

    ## set figure config
    if 'fontsize' in FIG_CONFIG:
        matplotlib.rcParams.update({'font.size': FIG_CONFIG['fontsize']})
    if 'figsize' in FIG_CONFIG and 'dpi' in FIG_CONFIG:
        fig = plt.figure(num=0,
                         figsize=FIG_CONFIG['figsize'],
                         dpi=FIG_CONFIG['dpi'])
    fig.canvas.set_window_title('test')
    plt.subplot(3, 1, 1)
    # plt.plot(t, model_input, label='model_input')
    # plt.plot(t, model_output, label='model_output')
    # plt.plot(t, model_with_white_noise, label='model_with_white_noise')
    plt.plot(t, velocity_signal, label='true_v')
    plt.plot(t, acceleration_signal, label='true_a')
    plt.plot(t, velocity_signal_with_white_noise, label='v_with_noise')
    plt.plot(t, acceleration_signal_with_white_noise, label='a_with_noise')
    plt.plot(t, v_kalman_filter, label='v_kalman_filter')
    plt.plot(t, a_kalman_filter, label='a_kalman_filter')
    plt.plot(t, fuse_acc_v_kalman_filtered, label='fuse_acc_v_kalman_filtered')
    plt.plot(t, fuse_acc_a_kalman_filtered, label='fuse_acc_a_kalman_filtered')
    plt.title("Signal")
    plt.legend()
    plt.grid()

    plt.subplot(3, 1, 2)
    plt.plot(t, P_result_0_0, label='P_result_0_0')
    plt.plot(t, P_result_0_1, label='P_result_0_1')
    plt.plot(t, P_result_1_0, label='P_result_1_0')
    plt.plot(t, P_result_1_1, label='P_result_1_1')
    # plt.plot(t,)
    plt.legend()
    plt.grid()

    plt.subplot(3, 1, 3)
    plt.plot(t, white_noise, label='white_noise')
    plt.plot(t, white_noise, label='white_noise')
    plt.title(
        f"Acceleration White Noise (Mean: {a_mean}, Variance: {a_variance}) Velocity White Noise (Mean: {v_mean}, Variance: {v_variance})"
    )
    plt.legend()
    plt.grid()
    plt.show()
