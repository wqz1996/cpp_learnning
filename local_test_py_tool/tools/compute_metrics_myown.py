#!/usr/bin/env python3

import pandas as pd
from clickhouse_sqlalchemy import make_session
from sqlalchemy import create_engine
from datetime import datetime
import matplotlib
import matplotlib.pyplot as plt
import logging

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


class LonMetricAnalysis:

    def __init__(self, session, config_dict: dict) -> None:
        self._session = session
        self._vehicle_name = config_dict.get("vehicle_name")
        start_ts = datetime.strptime(config_dict.get("start_time"),
                                     "%Y-%m-%d %H:%M:%S.%f").timestamp()
        end_ts = datetime.strptime(config_dict.get("end_time"),
                                   "%Y-%m-%d %H:%M:%S.%f").timestamp()
        time_step = config_dict.get("time_step")
        self._search_ts_list = []
        temp_ts = start_ts
        while temp_ts < end_ts:
            self._search_ts_list.append(temp_ts)
            temp_ts += time_step
        self._search_ts_list.append(end_ts)
        self._control_cmd_sql = \
            """
            SELECT ts,
            JSONExtractBool(vehicle_dbw_reports, 'superpilotEnabled') as superpilot_enabled,
            JSONExtractBool(vehicle_dbw_reports, 'dbwEnabled') as dbw_enabled,
            JSONExtractFloat(vehicle_control_cmd, 'debugCmd', 'vError') as v_error,
            JSONExtractFloat(vehicle_control_cmd, 'debugCmd', 'aReport') as a_report,
            JSONExtractFloat(vehicle_control_cmd, 'debugCmd', 'mpcAccelerationCmd') as mpc_acceleration_cmd,
            JSONExtractFloat(vehicle_control_cmd, 'debugCmd', 'aCmdFeedbackMrac') as driveline_inertia_factor_11,
            JSONExtractFloat(vehicle_control_cmd, 'debugCmd', 'vPidFeedback') as driveline_inertia_factor_12
            FROM bag_messages bm
            WHERE vehicle = '{0}' and  ts > '{1}' and ts < '{2}'
            ORDER BY ts
            """
        self.avg_v_error = [0, 0]
        self.avg_a_error = [0, 0]
        self.avg_driveline_inertia_factor_11 = [0, 0]
        self.avg_driveline_inertia_factor_12 = [0, 0]
        self.v_error_total_list = []
        self.a_error_total_list = []
        self.driveline_inertia_factor_11_total_list = []
        self.driveline_inertia_factor_12_total_list = []
        self.timestamp_list = []

    def get_query(self):
        for index, _ in enumerate(range(len(self._search_ts_list) - 1)):
            v_error_list = []
            a_error_list = []
            driveline_inertia_factor_11_list = []
            driveline_inertia_factor_12_list = []

            # print(self._vehicle_name, self._search_ts_list[index],
            #       self._search_ts_list[index + 1])

            try:
                query_msg = self._session.execute(
                    self._control_cmd_sql.format(
                        self._vehicle_name, self._search_ts_list[index],
                        self._search_ts_list[index + 1])).fetchall()
            except Exception:
                print('Query Error!')
                continue

            superpilot_enabled_flag = False
            dbw_enabled_flag = False
            for msg in query_msg:

                if msg['superpilot_enabled'] is not None:
                    superpilot_enabled = msg['superpilot_enabled']
                    if superpilot_enabled == 1:
                        superpilot_enabled_flag = True
                    else:
                        superpilot_enabled_flag = False

                if msg['dbw_enabled'] is not None:
                    dbw_enabled = msg['dbw_enabled']
                    if superpilot_enabled == 1:
                        dbw_enabled_flag = True
                    else:
                        dbw_enabled_flag = False

                if msg['v_error'] is not None:
                    v_error = msg['v_error']
                    self.v_error_total_list.append(v_error)
                    if dbw_enabled_flag is True:
                        v_error_list.append(v_error)

                if (msg['a_report']
                        is not None) and (msg['mpc_acceleration_cmd']
                                          is not None):
                    a_error = msg['mpc_acceleration_cmd'] - msg['a_report']
                    self.a_error_total_list.append(a_error)
                    if dbw_enabled_flag is True:
                        a_error_list.append(a_error)

                if msg['driveline_inertia_factor_11'] is not None:
                    driveline_inertia_factor_11 = msg[
                        'driveline_inertia_factor_11']
                    self.driveline_inertia_factor_11_total_list.append(
                        driveline_inertia_factor_11)
                    if dbw_enabled_flag is True:
                        driveline_inertia_factor_11_list.append(
                            driveline_inertia_factor_11)

                if msg['driveline_inertia_factor_12'] is not None:
                    driveline_inertia_factor_12 = msg[
                        'driveline_inertia_factor_12']
                    self.driveline_inertia_factor_12_total_list.append(
                        driveline_inertia_factor_12)
                    if dbw_enabled_flag is True:
                        driveline_inertia_factor_12_list.append(
                            driveline_inertia_factor_12)

            if len(v_error_list) != 0:
                self.avg_v_error = \
                    [(self.avg_v_error[0] * self.avg_v_error[1] + sum(v_error_list)) / (self.avg_v_error[1] + len(v_error_list)),
                    self.avg_v_error[1] + len(v_error_list)]

            if len(a_error_list) != 0:
                self.avg_a_error = \
                    [(self.avg_a_error[0] * self.avg_a_error[1] + sum(a_error_list)) / (self.avg_a_error[1] + len(a_error_list)),
                    self.avg_a_error[1] + len(a_error_list)]

            if len(driveline_inertia_factor_11_list) != 0:
                self.avg_driveline_inertia_factor_11 = \
                [(self.avg_driveline_inertia_factor_11[0] *
                self.avg_driveline_inertia_factor_11[1] +
                sum(driveline_inertia_factor_11_list)) /
                (self.avg_driveline_inertia_factor_11[1] +
                 len(driveline_inertia_factor_11_list)),
                self.avg_driveline_inertia_factor_11[1] +
                len(driveline_inertia_factor_11_list)]

            if len(driveline_inertia_factor_12_list) != 0:
                self.avg_driveline_inertia_factor_12 = \
                [(self.avg_driveline_inertia_factor_12[0] *
                self.avg_driveline_inertia_factor_12[1] +
                sum(driveline_inertia_factor_12_list)) /
                (self.avg_driveline_inertia_factor_12[1] +
                 len(driveline_inertia_factor_12_list)),
                self.avg_driveline_inertia_factor_12[1] +
                len(driveline_inertia_factor_12_list)]
        print('11 factor len: %d' %
              (len(self.driveline_inertia_factor_11_total_list)))
        print('12 factor len: %d' %
              (len(self.driveline_inertia_factor_12_total_list)))

    def plot_function(self):
        logger.info("plotting")
        if 'fontsize' in FIG_CONFIG:
            matplotlib.rcParams.update({'font.size': FIG_CONFIG['fontsize']})
        if 'figsize' in FIG_CONFIG and 'dpi' in FIG_CONFIG:
            fig = plt.figure(num=0,
                             figsize=FIG_CONFIG['figsize'],
                             dpi=FIG_CONFIG['dpi'])
        fig.canvas.set_window_title('test')
        plt.subplot(3, 1, 1)
        plt.plot(self.driveline_inertia_factor_11_total_list,
                 label='11 gear factor')
        plt.plot(self.driveline_inertia_factor_12_total_list,
                 label='12 gear factor')
        plt.legend()
        plt.grid()

        plt.subplot(3, 1, 2)
        plt.plot(self.v_error_total_list, label='v_error')
        plt.legend()
        plt.grid()

        plt.subplot(3, 1, 3)
        plt.plot(self.a_error_total_list, label='a_error')
        plt.legend()
        plt.grid()
        plt.show()


if __name__ == '__main__':
    CH_conf = {
        "user": "plus_viewer",
        "password": "ex4u1balSAeR68uC",
        "server_host": "clickhouse-proxy-cn.plusai.co",
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
    ## pdb b5 0327
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-29 05:57:00.00',
    #     "end_time": '2023-03-29 17:55:00.00',
    #     "time_step": 80
    # }

    ## pdb b5 0327
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-27 06:05:00.00',
    #     "end_time": '2023-03-27 17:00:00.00',
    #     "time_step": 80
    # }

    ## 48985 0329 road test
    # config_dict = {
    #     "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
    #     "start_time": '2023-03-29 13:47:36.00',
    #     "end_time": '2023-03-29 18:04:46.00',
    #     "time_step": 80
    # }

    ## 48985 0330 road test
    # config_dict = {
    #     "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
    #     "start_time": '2023-03-30 14:00:30.00',
    #     "end_time": '2023-03-30 17:39:19.00',
    #     "time_step": 80
    # }

    ## 48985 0331 road test
    config_dict = {
        "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
        "start_time": '2023-03-31 14:23:09.00',
        "end_time": '2023-03-31 17:58:44.00',
        "time_step": 80
    }

    lon_metric_analyzer = LonMetricAnalysis(session=session,
                                            config_dict=config_dict)
    lon_metric_analyzer.get_query()

    print("avg v_error: %f, frame_num: %d" %
          (lon_metric_analyzer.avg_v_error[0],
           lon_metric_analyzer.avg_v_error[1]))
    print("avg a_error: %f, frame_num: %d" %
          (lon_metric_analyzer.avg_a_error[0],
           lon_metric_analyzer.avg_a_error[1]))
    print("avg 11_factor: %f, frame_num: %d" %
          (lon_metric_analyzer.avg_driveline_inertia_factor_11[0],
           lon_metric_analyzer.avg_driveline_inertia_factor_11[1]))
    print("avg 12_factor: %f, frame_num: %d" %
          (lon_metric_analyzer.avg_driveline_inertia_factor_12[0],
           lon_metric_analyzer.avg_driveline_inertia_factor_12[1]))

    lon_metric_analyzer.plot_function()
