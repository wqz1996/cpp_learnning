from collections import deque
import scipy.signal as signal
import numpy as np
from clickhouse_sqlalchemy import make_session
from sqlalchemy import create_engine
from scipy import interpolate
import matplotlib.pyplot as plt
import matplotlib
import os
from datetime import datetime

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


def build_ch_session():
    CH_conf = {
        "user": "plus_viewer",
        "password": "ex4u1balSAeR68uC",
        "server_host": "172.16.100.90",
        "port": "9090",
        "db": "bagdb"
    }

    connection = 'clickhouse://{user}:{password}@{server_host}:{port}/{db}'.format(
        **CH_conf)
    engine = create_engine(connection,
                           pool_size=100,
                           pool_recycle=3600,
                           pool_timeout=20)
    session = make_session(engine)
    return session


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

    def model_generator(self, model_input, model_output):
        delayed_model_input = self.pure_delay(model_input)
        if self._last_y is None:
            self._last_y = model_output
            self._is_inited_state = True
            return model_output
        if not self._trigger_model_flag and delayed_model_input != 0.0:
            self._trigger_model_flag = True

        if not self._trigger_model_flag:
            self._last_y = model_output
            return model_output
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


class BrakeOvershootAnalyzer:

    def __init__(self, vehicle_name):
        self.a_report_time_list = []
        self.a_report_data_list = []
        self.mpc_acceleration_cmd_time_list = []
        self.mpc_acceleration_cmd_data_list = []
        self.brake_first_order_model_time_list = []
        self.brake_first_order_model_data_list = []
        self.filtered_data_list = []
        self.brake_overshoot_time_list = []
        self.brake_overshoot_data_list = []
        self.throttle_cmd_time_list = []
        self.throttle_cmd_data_list = []
        self.air_brake_cmd_time_list = []
        self.air_brake_cmd_data_list = []
        self.retarder_brake_cmd_time_list = []
        self.retarder_brake_cmd_data_list = []
        self.engine_brake_cmd_time_list = []
        self.engine_brake_cmd_data_list = []
        self.action_selected_time_list = []
        self.action_selected_data_list = []
        self.superpilot_enabled_time_list = []
        self.superpilot_enabled_data_list = []
        self.acc_enabled_time_list = []
        self.acc_enabled_data_list = []
        self.coasting_acceleration_data_list = []
        self.coasting_acceleration_time_list = []
        self.vehicle_name = vehicle_name

    def filter_a_y(self, data_y_list):
        cut_off = 1.0
        fs = 20.0
        wn = 2.0 * cut_off / fs
        order = 10.0
        try:
            b, a = signal.butter(order, wn, 'lowpass')
            return signal.filtfilt(b, a, data_y_list)
        except ValueError:
            return False

    def data_interpolation(self, x_original, y_original, x_new):
        dist_for_interp = 0.1  # Any number > 0 would suffice.
        if (not isinstance(x_original, (list, np.ndarray))
                or not isinstance(y_original, (list, np.ndarray))
                or len(x_original) != len(y_original) or len(x_original) < 2):
            raise RuntimeError(
                "Error using data_interpolation(): input lists must have same length which is >= 2!"
            )
        if not all([
                x_original[i] > x_original[i - 1]
                for i in range(1, len(x_original))
        ]):
            raise RuntimeError(
                "Error using data_interpolation(): input x_original must be in assending order with no duplicates!"
            )

        x_extend_left = min(min(x_new), x_original[0]) - dist_for_interp
        x_extend_right = max(max(x_new), x_original[-1]) + dist_for_interp

        y_extend_left = (y_original[1] - y_original[0]) / (
            x_original[1] - x_original[0]) * (x_extend_left - x_original[0])
        y_extend_left += y_original[0]
        y_extend_right = (y_original[-1] - y_original[-2]) / (
            x_original[-1] - x_original[-2]) * (x_extend_right -
                                                x_original[-1])
        y_extend_right += y_original[-1]

        x_original = np.insert(x_original, 0, x_extend_left)
        x_original = np.append(x_original, x_extend_right)
        y_original = np.insert(y_original, 0, y_extend_left)
        y_original = np.append(y_original, y_extend_right)

        data_interpolate = interpolate.interp1d(x_original, y_original)

        return list(data_interpolate(x_new))

    def filter_brake_overshoot_data(self):
        for idx, action_selected in enumerate(self.action_selected_data_list):
            if (action_selected == 1 or action_selected
                    == 4) or self.acc_enabled_data_list[idx] != 1:
                self.brake_overshoot_data_list.append(0.0)
            else:
                if self.air_brake_cmd_data_list[idx] < 0.0:
                    if np.abs(
                            self.brake_first_order_model_data_list[idx]) < 0.5:
                        if self.filtered_data_list[
                                idx] - self.brake_first_order_model_data_list[
                                    idx] < -0.3:
                            self.brake_overshoot_data_list.append(1.0)
                        else:
                            self.brake_overshoot_data_list.append(0.0)
                    else:
                        if self.filtered_data_list[
                                idx] - self.brake_first_order_model_data_list[
                                    idx] < -0.4 * np.abs(
                                        self.brake_first_order_model_data_list[
                                            idx]):
                            self.brake_overshoot_data_list.append(1.0)
                        else:
                            self.brake_overshoot_data_list.append(0.0)
                else:
                    self.brake_overshoot_data_list.append(0.0)
        if sum(self.brake_overshoot_data_list) > 0:
            return 1
        else:
            return 0

    # this function will generate the ideal model of air brake actuator
    # ps: J7 and PDB use different model parameters
    def generate_ideal_model(self):
        # origin tau = 0.2 delay = 0.5
        if "pdb" in self.vehicle_name:
            brake_first_order_model = ModelGenerator(model_order=1.0,
                                                     tau=0.4,
                                                     gain=1.0,
                                                     ts=0.05,
                                                     delay_time=0.9)
        elif "j7" in self.vehicle_name:
            brake_first_order_model = ModelGenerator(model_order=1.0,
                                                     tau=0.3,
                                                     gain=1.0,
                                                     ts=0.05,
                                                     delay_time=1.0)
        for idx, y in enumerate(self.mpc_acceleration_cmd_data_list):
            if self.action_selected_data_list[
                    idx] == 1 or self.action_selected_data_list[idx] == 4:
                action_selected = "throttle"
            else:
                action_selected = "brake"
            if action_selected == "throttle":
                brake_first_order_model.reset()
                self.brake_first_order_model_data_list.append(0.0)
            elif action_selected == "brake":
                if not brake_first_order_model._is_inited_state:
                    brake_first_order_model.set_init_state()
                self.brake_first_order_model_data_list.append(
                    brake_first_order_model.model_generator(
                        self.air_brake_cmd_data_list[idx],
                        self.filtered_data_list[idx]))

    def is_brake_overshoot(self, start_time, end_time):
        session = build_ch_session()
        brake_overshoot_sql = \
            '''
            SELECT
            ts,
            JSONExtractFloat(vehicle_control_cmd, 'debugCmd', 'mpcAccelerationCmd') as mpcAccelerationCmd,
            JSONExtractFloat(vehicle_control_cmd, 'debugCmd', 'aReport') as aReport,
            JSONExtractInt(vehicle_control_cmd, 'debugCmd', 'controlActionType') as controlActionType,
            JSONExtractFloat(vehicle_control_cmd, 'throttleCmd', 'normalizedValue') as normalizedValue,
            JSONExtractFloat(vehicle_control_cmd, 'brakeCmd', 'targetAcceleration') as targetAcceleration,
            JSONExtractFloat(vehicle_control_cmd, 'brakeCmd', 'engineBrakeTorquePct') as engineBrakeTorquePct,
            JSONExtractFloat(vehicle_control_cmd, 'brakeCmd', 'retarderTorquePct') as retarderTorquePct,
            JSONExtractBool(vehicle_dbw_reports, 'superpilotEnabled') as superpilotEnabled,
            JSONExtractBool(vehicle_dbw_reports, 'accEnabled') as accEnabled,
            JSONExtractFloat(vehicle_status, 'coastingAcceleration') as coastingAcceleration
            FROM bag_messages bm 
            where vehicle = '{0}'
            and ts >= '{1}' and ts <= '{2}'
            and (vehicle_control_cmd is not NULL or vehicle_dbw_reports is not NULL or vehicle_status is not NULL)
            order by ts
            '''.format(self.vehicle_name, start_time, end_time)
        brake_overshoot_msgs = session.execute(brake_overshoot_sql)
        session.close()
        for brake_overshoot_info in brake_overshoot_msgs:
            ts, mpcAccelerationCmd, aReport, controlActionType, normalizedValue, targetAcceleration, engineBrakeTorquePct,\
                retarderTorquePct, superpilotEnabled, accEnabled, coastingAcceleration = brake_overshoot_info
            ts = datetime.strptime(ts, "%Y-%m-%d %H:%M:%S.%f").timestamp()
            if mpcAccelerationCmd is not None and \
                (len(self.mpc_acceleration_cmd_time_list) == 0 or ts > self.mpc_acceleration_cmd_time_list[-1]):
                self.mpc_acceleration_cmd_time_list.append(ts)
                self.a_report_time_list.append(ts)
                self.action_selected_time_list.append(ts)
                self.air_brake_cmd_time_list.append(ts)
                self.engine_brake_cmd_time_list.append(ts)
                self.throttle_cmd_time_list.append(ts)
                self.retarder_brake_cmd_time_list.append(ts)
                self.mpc_acceleration_cmd_data_list.append(mpcAccelerationCmd)
                self.a_report_data_list.append(aReport)
                self.action_selected_data_list.append(controlActionType)
                self.air_brake_cmd_data_list.append(targetAcceleration)
                self.engine_brake_cmd_data_list.append(engineBrakeTorquePct)
                self.throttle_cmd_data_list.append(normalizedValue)
                self.retarder_brake_cmd_data_list.append(retarderTorquePct)
            if superpilotEnabled is not None and \
                (len(self.superpilot_enabled_time_list) == 0 or ts > self.superpilot_enabled_time_list[-1]):
                self.superpilot_enabled_time_list.append(ts)
                self.acc_enabled_time_list.append(ts)
                self.superpilot_enabled_data_list.append(superpilotEnabled)
                self.acc_enabled_data_list.append(accEnabled)
            if coastingAcceleration is not None and \
                (len(self.coasting_acceleration_time_list) == 0 or ts > self.coasting_acceleration_time_list[-1]):
                self.coasting_acceleration_time_list.append(ts)
                self.coasting_acceleration_data_list.append(
                    coastingAcceleration)
        self.brake_overshoot_time_list = self.mpc_acceleration_cmd_time_list
        self.brake_first_order_model_time_list = self.mpc_acceleration_cmd_time_list
        self.acc_enabled_data_list = \
            self.data_interpolation(np.array(self.acc_enabled_time_list), np.array(self.acc_enabled_data_list), np.array(self.mpc_acceleration_cmd_time_list))
        self.acc_enabled_time_list = self.mpc_acceleration_cmd_time_list
        self.superpilot_enabled_data_list = \
            self.data_interpolation(np.array(self.superpilot_enabled_time_list), np.array(self.superpilot_enabled_data_list), np.array(self.mpc_acceleration_cmd_time_list))
        self.superpilot_enabled_time_list = self.mpc_acceleration_cmd_time_list
        self.coasting_acceleration_data_list = \
            self.data_interpolation(np.array(self.coasting_acceleration_time_list), np.array(self.coasting_acceleration_data_list), np.array(self.mpc_acceleration_cmd_time_list))
        self.coasting_acceleration_time_list = self.mpc_acceleration_cmd_time_list
        self.filtered_data_list = self.filter_a_y(self.a_report_data_list)
        if self.filtered_data_list is False:
            return 0
        self.generate_ideal_model()
        return self.filter_brake_overshoot_data()

    def plot_function(self, file_name):
        if 'fontsize' in FIG_CONFIG:
            matplotlib.rcParams.update({'font.size': FIG_CONFIG['fontsize']})
        if 'figsize' in FIG_CONFIG and 'dpi' in FIG_CONFIG:
            fig = plt.figure(num=0,
                             figsize=FIG_CONFIG['figsize'],
                             dpi=FIG_CONFIG['dpi'])
        fig.canvas.set_window_title(os.path.basename(file_name))
        plt.subplot(4, 1, 1)
        plt.plot(self.brake_overshoot_time_list,
                 self.brake_overshoot_data_list,
                 label='brake_overshoot_flag')
        plt.legend()
        plt.grid()

        plt.subplot(4, 1, 2)
        plt.plot(self.a_report_time_list,
                 self.filtered_data_list,
                 label='filtered_a_report')
        plt.plot(self.a_report_time_list,
                 self.a_report_data_list,
                 label='original_a_report')
        plt.plot(self.mpc_acceleration_cmd_time_list,
                 self.mpc_acceleration_cmd_data_list,
                 label='mpc_acceleration_cmd')
        plt.plot(self.brake_first_order_model_time_list,
                 self.brake_first_order_model_data_list,
                 label='brake_first_order_model')
        plt.plot(self.action_selected_time_list,
                 np.array(self.action_selected_data_list) * 0.1,
                 label='action_selected')
        plt.plot(self.coasting_acceleration_time_list,
                 self.coasting_acceleration_data_list,
                 label='coasting_acceleration')
        plt.legend()
        plt.grid()

        plt.subplot(4, 1, 3)
        plt.plot(self.throttle_cmd_time_list,
                 self.throttle_cmd_data_list,
                 label='throttle_cmd')
        plt.plot(self.air_brake_cmd_time_list,
                 self.air_brake_cmd_data_list,
                 label='air_brake_cmd')
        plt.plot(self.engine_brake_cmd_time_list,
                 np.array(self.engine_brake_cmd_data_list) * -0.01,
                 label='engine_brake_cmd')
        plt.plot(self.retarder_brake_cmd_time_list,
                 np.array(self.retarder_brake_cmd_data_list) * -0.01,
                 label='retarder_brake_cmd')
        plt.legend()
        plt.grid()
        plt.subplot(4, 1, 4)
        plt.plot(self.superpilot_enabled_time_list,
                 self.superpilot_enabled_data_list,
                 label='superpilot_enable')
        plt.plot(self.acc_enabled_time_list,
                 self.acc_enabled_data_list,
                 label='acc_enabled')
        plt.legend()
        plt.grid()
        # plt.savefig('test_1.png')
        plt.show()


if __name__ == '__main__':
    brake_overshoot_analyzer = BrakeOvershootAnalyzer('pdb-l4e-b0001')
    brake_overshoot_flag = brake_overshoot_analyzer.is_brake_overshoot(
        1675147365, 1675147371)
    brake_overshoot_analyzer.plot_function('test')
