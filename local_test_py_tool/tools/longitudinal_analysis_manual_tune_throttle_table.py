#!/usr/bin/env python3

import pandas as pd
from clickhouse_sqlalchemy import make_session
from sqlalchemy import create_engine
from datetime import datetime
import matplotlib
import matplotlib.pyplot as plt
import logging
import numpy as np
import math

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
            JSONExtractBool(planning_trajectory, 'enabledStitchVelocity') as enabled_stitch_velocity
            FROM bag_messages bm
            WHERE vehicle = '{0}' and  ts > '{1}' and ts < '{2}'
            ORDER BY ts
            """
        self.avg_v_error = [0, 0]
        self.avg_a_error = [0, 0]
        self.v_error_total_list = []
        self.a_error_total_list = []
        self.timestamp_list = []
        self.v_rmse = [0, 0]
        self.a_rmse = [0, 0]
        self.stitch_list = []
        self.enable_stitch_list = []
        self.stitch_precent = 0

    def get_query(self):
        for index, _ in enumerate(range(len(self._search_ts_list) - 1)):
            v_error_list = []
            a_error_list = []

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
            enabled_stitch_velocity_flag = False
            for msg in query_msg:
                if msg['enabled_stitch_velocity'] is not None:
                    enabled_stitch_velocity = msg['enabled_stitch_velocity']
                    self.stitch_list.append(enabled_stitch_velocity)
                    if enabled_stitch_velocity == 1:
                        self.enable_stitch_list.append(enabled_stitch_velocity)
                        enabled_stitch_velocity_flag = True
                    else:
                        enabled_stitch_velocity_flag = False

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
                is_valid_data = enabled_stitch_velocity_flag == True and dbw_enabled_flag == True
                if msg['v_error'] is not None:
                    v_error = msg['v_error']
                    self.v_error_total_list.append(v_error)
                    if is_valid_data is True:
                        v_error_list.append(v_error)

                if (msg['a_report']
                        is not None) and (msg['mpc_acceleration_cmd']
                                          is not None):
                    a_error = msg['mpc_acceleration_cmd'] - msg['a_report']
                    self.a_error_total_list.append(a_error)
                    if is_valid_data is True:
                        a_error_list.append(a_error)

            if len(v_error_list) != 0:
                self.avg_v_error = \
                    [(self.avg_v_error[0] * self.avg_v_error[1] + sum(v_error_list)) / (self.avg_v_error[1] + len(v_error_list)),
                    self.avg_v_error[1] + len(v_error_list)]
                self.v_rmse = \
                    [math.sqrt((np.array(self.v_rmse[0])**2 * self.v_rmse[1] + np.sum(np.array(v_error_list)**2)) / (self.v_rmse[1] + len(v_error_list))), self.v_rmse[1] + len(v_error_list)]

            if len(a_error_list) != 0:
                self.avg_a_error = \
                    [(self.avg_a_error[0] * self.avg_a_error[1] + sum(a_error_list)) / (self.avg_a_error[1] + len(a_error_list)),
                    self.avg_a_error[1] + len(a_error_list)]
                self.a_rmse = \
                    [math.sqrt((np.array(self.a_rmse[0])**2 * self.a_rmse[1] + np.sum(np.array(a_error_list)**2)) / (self.a_rmse[1] + len(a_error_list))), self.a_rmse[1] + len(a_error_list)]
        self.stitch_precent = len(self.enable_stitch_list) / len(
            self.stitch_list)

    def plot_function(self):
        logger.info("plotting")
        if 'fontsize' in FIG_CONFIG:
            matplotlib.rcParams.update({'font.size': FIG_CONFIG['fontsize']})
        if 'figsize' in FIG_CONFIG and 'dpi' in FIG_CONFIG:
            fig = plt.figure(num=0,
                             figsize=FIG_CONFIG['figsize'],
                             dpi=FIG_CONFIG['dpi'])
        fig.canvas.set_window_title('test')

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
    #####pdb b5#########################
    #####wuhan to hangzhou##############
    # # pdb b5 0402
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-04-02 05:54:23.00',
    #     "end_time": '2023-04-02 18:03:42.00',
    #     "time_step": 80
    # }

    # # pdb b5 0331
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-31 05:57:20.00',
    #     "end_time": '2023-03-31 18:00:34.00',
    #     "time_step": 80
    # }

    # # pdb b5 0329
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-29 05:57:00.00',
    #     "end_time": '2023-03-29 17:55:00.00',
    #     "time_step": 80
    # }

    # # pdb b5 0327
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-27 06:05:00.00',
    #     "end_time": '2023-03-27 17:00:00.00',
    #     "time_step": 80
    # }

    # # pdb b5 0325
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-25 05:53:52.00',
    #     "end_time": '2023-03-25 16:55:04.00',
    #     "time_step": 80
    # }
    # # pdb b5 0323
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-23 05:51:45.00',
    #     "end_time": '2023-03-23 16:51:13.00',
    #     "time_step": 80
    # }
    #########################################
    #####hangzhou to wuhan##############
    # # pdb b5 0401
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-04-01 05:54:15.00',
    #     "end_time": '2023-04-01 18:47:55.00',
    #     "time_step": 80
    # }

    # ## pdb b5 0330
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-30 06:06:49.00',
    #     "end_time": '2023-03-30 17:47:46.00',
    #     "time_step": 80
    # }

    # ## pdb b5 0328
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-28 05:49:00.00',
    #     "end_time": '2023-03-28 17:40:03.00',
    #     "time_step": 80
    # }

    # ## pdb b5 0326
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-26 06:08:35.00',
    #     "end_time": '2023-03-26 18:03:44.00',
    #     "time_step": 80
    # }

    # # pdb b5 0324
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-24 06:01:52.00',
    #     "end_time": '2023-03-24 17:30:28.00',
    #     "time_step": 80
    # }
    #########################################
    #####pdb b3#########################
    #####wuhan to hangzhou##############
    # # pdb b3 0329
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0003',
    #     "start_time": '2023-03-29 05:49:29.00',
    #     "end_time": '2023-03-29 17:25:58.00',
    #     "time_step": 80
    # }
    # pdb b3 0331
    config_dict = {
        "vehicle_name": 'pdb-l4e-b0003',
        "start_time": '2023-03-31 06:11:02.00',
        "end_time": '2023-03-31 17:20:13.00',
        "time_step": 80
    }
    # # pdb b3 0402
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0003',
    #     "start_time": '2023-04-02 05:42:51.00',
    #     "end_time": '2023-04-02 17:39:15.00',
    #     "time_step": 80
    # }
    #####hangzhou to wuhan##############
    # # pdb b3 0330
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0003',
    #     "start_time": '2023-03-30 06:06:43.00',
    #     "end_time": '2023-03-30 18:00:30.00',
    #     "time_step": 80
    # }
    # # pdb b3 0401
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0003',
    #     "start_time": '2023-04-01 05:47:09.00',
    #     "end_time": '2023-04-01 18:44:41.00',
    #     "time_step": 80
    # }
    ####################################
    # 48985 0329 road test
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
    # config_dict = {
    #     "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
    #     "start_time": '2023-03-31 14:23:09.00',
    #     "end_time": '2023-03-31 17:58:44.00',
    #     "time_step": 80
    # }

    lon_metric_analyzer = LonMetricAnalysis(session=session,
                                            config_dict=config_dict)
    lon_metric_analyzer.get_query()
    print(config_dict.get("vehicle_name"))
    print(config_dict.get("start_time"))
    print("Average: ")
    print("avg v_error: %f, frame_num: %d" %
          (lon_metric_analyzer.avg_v_error[0],
           lon_metric_analyzer.avg_v_error[1]))
    print("avg a_error: %f, frame_num: %d" %
          (lon_metric_analyzer.avg_a_error[0],
           lon_metric_analyzer.avg_a_error[1]))
    print("RMSE: ")
    print("v_rmse: %f, frame num: %d" %
          (lon_metric_analyzer.v_rmse[0], lon_metric_analyzer.v_rmse[1]))
    print("a_rmse: %f, frame num: %d" %
          (lon_metric_analyzer.a_rmse[0], lon_metric_analyzer.a_rmse[1]))
    print("stitch list len: %d, enable stitch list len: %d" %
          (len(lon_metric_analyzer.stitch_list),
           len(lon_metric_analyzer.enable_stitch_list)))
    print("stitch precent: %f" % lon_metric_analyzer.stitch_precent)

    # lon_metric_analyzer.plot_function()
