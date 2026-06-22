#!/usr/bin/env python3
import pandas as pd
from clickhouse_sqlalchemy import make_session
from sqlalchemy import create_engine
from datetime import datetime


class VErrorAnalysis:

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
            JSONExtractFloat(vehicle_control_cmd, 'debugCmd', 'vError') as v_error
            FROM bag_messages bm
            WHERE vehicle = '{0}' and  ts > '{1}' and ts < '{2}'
            ORDER BY ts
            """
        self.v_error_statistic = [0, 0]

    def get_query(self):
        for index, _ in enumerate(range(len(self._search_ts_list) - 1)):
            # print(self._vehicle_name, self._search_ts_list[index],
            #       self._search_ts_list[index + 1])
            v_error_list = []
            try:
                query_msg = self._session.execute(
                    self._control_cmd_sql.format(
                        self._vehicle_name, self._search_ts_list[index],
                        self._search_ts_list[index + 1])).fetchall()
            except Exception:
                print('Query Error!')
                continue

            engage_flag = False
            for msg in query_msg:
                if msg['superpilot_enabled'] is not None:
                    superpilot_enabled = msg['superpilot_enabled']
                    if superpilot_enabled == 1:
                        engage_flag = True
                    else:
                        engage_flag = False
                if msg['v_error'] is not None:
                    v_error = msg['v_error']
                    if engage_flag is True:
                        v_error_list.append(v_error)
            if len(v_error_list) == 0:
                continue
            self.v_error_statistic = \
                [(self.v_error_statistic[0] * self.v_error_statistic[1] + sum(v_error_list)) / (self.v_error_statistic[1] + len(v_error_list)),
                 self.v_error_statistic[1] + len(v_error_list)]


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
    config_dict = {
        "vehicle_name": 'pdb-l4e-b0007',
        "start_time": '2023-03-31 11:00:00.00',
        "end_time": '2023-03-31 11:05:00.00',
        "time_step": 80
    }
    v_error = VErrorAnalysis(session=session, config_dict=config_dict)
    v_error.get_query()
    print("avg v_error: %f, frame_num: %d" %
          (v_error.v_error_statistic[0], v_error.v_error_statistic[1]))
