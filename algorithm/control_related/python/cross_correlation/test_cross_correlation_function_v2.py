#!/usr/bin/env python3

from math import ceil
import random
import numpy as np
from collections import deque
import matplotlib
import matplotlib.pyplot as plt
import logging
import statistics

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


def compute_mean(data_list):
    return np.mean(data_list)


def compute_standard_deviation(data_list):
    return statistics.stdev(data_list)


def normalize_signal(data_list):
    print("normalize signal is running")
    data_mean = compute_mean(data_list)
    data_std = compute_standard_deviation(data_list)
    print("Before normalize | data_mean: {} data_std: {}".format(
        data_mean, data_std))
    for i in range(len(data_list)):
        data_list[i] = (data_list[i] - data_mean) / data_std
    print("After normalize | data_mean: {} data_std: {}".format(
        compute_mean(data_list), compute_standard_deviation(data_list)))
    return data_list


def compute_cross_correlation(self, data1, data2):
    normalized_data1 = normalize_signal(data1)
    reversed_data_1 = list(reversed(normalized_data1))


def rmse(input_list):
    rmse = np.sqrt(sum([v**2 for v in input_list]) / len(input_list))
    return rmse


if __name__ == '__main__':
    start_t = 0
    end_t = 10
    interested_start_t = 2
    interested_end_t = 6
    fs = 20  #hz
    t = np.linspace(start_t, end_t, (end_t - start_t) * fs)
    interested_t = np.linspace(interested_start_t, interested_end_t,
                               (interested_end_t - interested_start_t) * fs)
    print("data len: {}".format(len(t)))
    #print("t: {}".format(t))
    f = 0.2  #hz
    A = 1  #amplitude
    phase_bias = 0
    amplitude_bias = 0.0

    origin_signal = A * np.sin(2 * np.pi * f * t + phase_bias) + amplitude_bias

    interested_origin_signal = origin_signal[interested_start_t *
                                             fs:interested_end_t * fs]

    first_order_model = ModelGenerator(model_order=1.0,
                                       tau=0.3,
                                       gain=1.0,
                                       ts=1 / fs,
                                       delay_time=0.3)
    first_order_model.set_init_state()
    delay_signal = []
    for i in range(len(origin_signal)):
        delay_signal.append(first_order_model.model_generator(
            origin_signal[i]))

    interested_delay_signal = delay_signal[interested_start_t *
                                           fs:interested_end_t * fs]
    len1 = len(interested_origin_signal)
    len2 = len(interested_delay_signal)
    cross_correlation = np.correlate(interested_origin_signal,
                                     interested_delay_signal,
                                     mode='same') / (len1 * len2)

    time_lag = np.linspace(-len1 // 2, len1 // 2, len1)
    cross_correlation = list(cross_correlation)
    max_cross_correlation_idx = cross_correlation.index(max(cross_correlation))
    time_delay_second = -time_lag[max_cross_correlation_idx] / fs
    print("max cross correlation: {} index: {}".format(
        max(cross_correlation), max_cross_correlation_idx))
    print("time lag: {}".format(time_lag[max_cross_correlation_idx]))
    print("time delay: {}".format(time_delay_second))
    print("round time delay: {}".format(
        round(-time_lag[max_cross_correlation_idx]) / fs))
    # print("time delay list: {}".format(time_lag))
    fix_signal = delay_signal[interested_start_t * fs +
                              round(-time_lag[max_cross_correlation_idx]
                                    ):interested_end_t * fs +
                              round(-time_lag[max_cross_correlation_idx])]
    origin_signal_error = []
    fixed_signal_error = []
    for i in range(len(interested_origin_signal)):
        origin_signal_error.append(interested_origin_signal[i] -
                                   interested_delay_signal[i])
        fixed_signal_error.append(interested_origin_signal[i] - fix_signal[i])
    print("Before fix rmse: {} After fix rmse: {}".format(
        rmse(origin_signal_error), rmse(fixed_signal_error)))

    # print("fix_signal: {}".format(fix_signal))

    plt.subplot(3, 1, 1)
    plt.plot(interested_t, interested_origin_signal, label='origin')
    plt.plot(interested_t, interested_delay_signal, label='delayed')
    plt.plot(interested_t, fix_signal, label='fixed')
    plt.title("Signal")
    plt.xlabel('Time/s')
    plt.ylabel('Amplitude')
    plt.legend()
    plt.grid()

    plt.subplot(3, 1, 2)
    plt.plot(interested_t, origin_signal_error, label='origin error')
    plt.plot(interested_t, fixed_signal_error, label='fixed_error')
    plt.title("Error")
    plt.xlabel('Time/s')
    plt.ylabel('Amplitude')
    plt.legend()
    plt.grid()

    plt.subplot(3, 1, 3)
    plt.plot(time_lag, cross_correlation, label='cross correlation')
    plt.xlabel('Time lag')
    plt.ylabel('Correlation')
    plt.title("Cross Correlation")
    plt.grid()
    plt.legend()
    plt.tight_layout()
    plt.show()

    print("main function")
