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
            JSONExtractFloat(vehicle_control_cmd, 'debugCmd', 'onlineTuneThrottleTable', 'totalDrivelineInertiaFactor', 'gear11') as driveline_inertia_factor_11,
            JSONExtractFloat(vehicle_control_cmd, 'debugCmd', 'onlineTuneThrottleTable', 'totalDrivelineInertiaFactor', 'gear12') as driveline_inertia_factor_12,
            JSONExtractBool(planning_trajectory, 'enabledStitchVelocity') as enabled_stitch_velocity
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
        self.filtered_driveline_inertia_factor_11_total_list = []
        self.filtered_driveline_inertia_factor_12_total_list = []
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

                if msg['driveline_inertia_factor_11'] is not None:
                    driveline_inertia_factor_11 = msg[
                        'driveline_inertia_factor_11']
                    self.driveline_inertia_factor_11_total_list.append(
                        driveline_inertia_factor_11)
                    if is_valid_data is True:
                        driveline_inertia_factor_11_list.append(
                            driveline_inertia_factor_11)

                if msg['driveline_inertia_factor_12'] is not None:
                    driveline_inertia_factor_12 = msg[
                        'driveline_inertia_factor_12']
                    self.driveline_inertia_factor_12_total_list.append(
                        driveline_inertia_factor_12)
                    if is_valid_data is True:
                        driveline_inertia_factor_12_list.append(
                            driveline_inertia_factor_12)

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
        self.stitch_precent = len(self.enable_stitch_list) / len(
            self.stitch_list)
        self.filtered_driveline_inertia_factor_11_total_list = [
            n
            for n in lon_metric_analyzer.driveline_inertia_factor_11_total_list
            if n > 0
        ]
        self.filtered_driveline_inertia_factor_12_total_list = [
            n
            for n in lon_metric_analyzer.driveline_inertia_factor_12_total_list
            if n > 0
        ]

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
        plt.plot(self.filtered_driveline_inertia_factor_11_total_list,
                 label='11 gear factor')
        plt.plot(self.filtered_driveline_inertia_factor_12_total_list,
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
    #####wuhan to hangzhou##############
    # #pdb b5 0412
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-04-12 05:58:05.00',
    #     "end_time": '2023-04-12 17:10:11.00',
    #     "time_step": 80
    # }

    # # pdb b5 0408
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-04-08 06:16:44.00',
    #     "end_time": '2023-04-08 17:16:53.00',
    #     "time_step": 80
    # }

    ## pdb b5 0402
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-04-02 05:54:23.00',
    #     "end_time": '2023-04-02 18:03:42.00',
    #     "time_step": 80
    # }

    ## pdb b5 0331
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-31 05:57:20.00',
    #     "end_time": '2023-03-31 18:00:34.00',
    #     "time_step": 80
    # }

    ## pdb b5 0329
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

    ## pdb b5 0325
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-25 05:53:52.00',
    #     "end_time": '2023-03-25 16:55:04.00',
    #     "time_step": 80
    # }
    ## pdb b5 0323
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-03-23 05:51:45.00',
    #     "end_time": '2023-03-23 16:51:13.00',
    #     "time_step": 80
    # }
    #########################################
    #####hangzhou to wuhan##############
    # #pdb b5 0411
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-04-11 05:59:26.00',
    #     "end_time": '2023-04-11 17:15:47.00',
    #     "time_step": 80
    # }

    # #pdb b5 0407
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0005',
    #     "start_time": '2023-04-07 05:58:50.00',
    #     "end_time": '2023-04-07 17:39:22.00',
    #     "time_step": 80
    # }

    ## pdb b5 0401
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
    #####wuhan to hangzhou##############
    # # pdb b3 0404
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0003',
    #     "start_time": '2023-04-04 06:03:19.00',
    #     "end_time": '2023-04-04 17:29:19.00',
    #     "time_step": 80
    # }
    # # pdb b3 0408
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0003',
    #     "start_time": '2023-04-08 06:06:52.00',
    #     "end_time": '2023-04-08 17:46:15.00',
    #     "time_step": 80
    # }
    # # pdb b3 0410
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0003',
    #     "start_time": '2023-04-10 05:54:58.00',
    #     "end_time": '2023-04-10 17:24:30.00',
    #     "time_step": 80
    # }
    #####hangzhou to wuhan##############
    # # pdb b3 0407
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0003',
    #     "start_time": '2023-04-07 05:55:46.00',
    #     "end_time": '2023-04-07 17:34:10.00',
    #     "time_step": 80
    # }
    ## pdb b3 0409
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0003',
    #     "start_time": '2023-04-09 05:36:24.00',
    #     "end_time": '2023-04-09 20:16:33.00',
    #     "time_step": 80
    # }
    # # pdb b3 0411
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0003',
    #     "start_time": '2023-04-11 05:52:36.00',
    #     "end_time": '2023-04-11 17:31:08.00',
    #     "time_step": 80
    # }
    #########################################
    ## 48985 0329 road test
    # config_dict = {
    #     "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
    #     "start_time": '2023-03-29 13:47:36.00',
    #     "end_time": '2023-03-29 18:04:46.00',
    #     "time_step": 80
    # }

    # # 48985 0330 road test
    # config_dict = {
    #     "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
    #     "start_time": '2023-03-30 14:00:30.00',
    #     "end_time": '2023-03-30 17:39:19.00',
    #     "time_step": 80
    # }

    # 48985 0331 road test
    # config_dict = {
    #     "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
    #     "start_time": '2023-03-31 14:23:09.00',
    #     "end_time": '2023-03-31 17:58:44.00',
    #     "time_step": 80
    # }

    # #48985 0404 road test
    # config_dict = {
    #     "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
    #     "start_time": '2023-04-04 15:09:44.00',
    #     "end_time": '2023-04-04 17:29:10.00',
    #     "time_step": 80
    # }

    # #48985 0406 road test
    # config_dict = {
    #     "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
    #     "start_time": '2023-04-06 14:07:02.00',
    #     "end_time": '2023-04-06 17:50:19.00',
    #     "time_step": 80
    # }

    # #48985 0407 road test
    # config_dict = {
    #     "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
    #     "start_time": '2023-04-07 14:14:59.00',
    #     "end_time": '2023-04-07 18:13:34.00',
    #     "time_step": 80
    # }

    # #48985 0410 road test
    # config_dict = {
    #     "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
    #     "start_time": '2023-04-10 14:08:32.00',
    #     "end_time": '2023-04-10 17:56:57.00',
    #     "time_step": 80
    # }

    # #48985 0411 road test
    # config_dict = {
    #     "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
    #     "start_time": '2023-04-11 14:52:45.00',
    #     "end_time": '2023-04-11 17:03:25.00',
    #     "time_step": 80
    # }
    # #48985 0412 road test
    # config_dict = {
    #     "vehicle_name": 'j7-l4e-LFWSRXSJ7M1F48985',
    #     "start_time": '2023-04-12 14:17:09.00',
    #     "end_time": '2023-04-12 18:20:23.00',
    #     "time_step": 80
    # }
    #########test################
    # # pdb b3 0417
    # config_dict = {
    #     "vehicle_name": 'pdb-l4e-b0003',
    #     "start_time": '2023-04-17 10:50:04.00',
    #     "end_time": '2023-04-17 13:54:40.00',
    #     "time_step": 80
    # }
    # pdb b3 0418
    config_dict = {
        "vehicle_name": 'pdb-l4e-b0003',
        "start_time": '2023-04-18 11:32:55.00',
        "end_time": '2023-04-18 12:10:24.00',
        "time_step": 80
    }

    lon_metric_analyzer = LonMetricAnalysis(session=session,
                                            config_dict=config_dict)
    lon_metric_analyzer.get_query()

    print(config_dict.get("vehicle_name"))
    print(config_dict.get("start_time"))
    print(config_dict.get("end_time"))
    print("Average: ")
    print("avg v_error: %f frame_num: %d" %
          (lon_metric_analyzer.avg_v_error[0],
           lon_metric_analyzer.avg_v_error[1]))
    print("avg a_error: %f frame_num: %d" %
          (lon_metric_analyzer.avg_a_error[0],
           lon_metric_analyzer.avg_a_error[1]))
    print("RMSE: ")
    print("v_rmse: %f frame num: %d" %
          (lon_metric_analyzer.v_rmse[0], lon_metric_analyzer.v_rmse[1]))
    print("a_rmse: %f frame num: %d" %
          (lon_metric_analyzer.a_rmse[0], lon_metric_analyzer.a_rmse[1]))
    print("Throttle table: ")
    print("avg 11_factor: %f frame_num: %d, min %f -> max %f" %
          (lon_metric_analyzer.avg_driveline_inertia_factor_11[0],
           lon_metric_analyzer.avg_driveline_inertia_factor_11[1],
           np.min(lon_metric_analyzer.
                  filtered_driveline_inertia_factor_11_total_list),
           np.max(lon_metric_analyzer.
                  filtered_driveline_inertia_factor_11_total_list)))
    print("avg 12_factor: %f frame_num: %d, min %f -> max %f" %
          (lon_metric_analyzer.avg_driveline_inertia_factor_12[0],
           lon_metric_analyzer.avg_driveline_inertia_factor_12[1],
           np.min(lon_metric_analyzer.
                  filtered_driveline_inertia_factor_12_total_list),
           np.max(lon_metric_analyzer.
                  filtered_driveline_inertia_factor_12_total_list)))
    print("stitch precent: %f" % lon_metric_analyzer.stitch_precent)

    lon_metric_analyzer.plot_function()
