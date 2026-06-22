import bisect
import numpy as np
import matplotlib.pyplot as plt
import math
import sys

## some const value
epsilon = sys.float_info.epsilon
# 正无穷大
positive_infinity = float('inf')
# 负无穷大
negative_infinity = float('-inf')

## truck Behavior -> from decision module
Behavior = 'Follow'  # Overtake / Follow / Stop

# Parameters
Car_Config = {
    'initial_velocity': 10.0,
    'max_acceleration': 2.0,
    'max_deceleration': -3.0,
    'max_velocity': 27.0,
    'min_velocity': 0.0,
    'max_jerk': 2.0,
    'min_jerk': -2.0,
}

FLAGS_planning_upper_speed_limit = 27.0
FLAGS_enable_dp_reference_speed = True

ref_v = 15.0  # m/s
target_s = 150.0  # m
# Obstacle param
Obstacle_Config = {
    'obstacle_enter_time': 4.0,
    'obstacle_exit_time': 6.0,
    'obstacle_length': 10.0,
    'obstacle_speed': 15.0,
    'obstacle_distance': 0.0,
    # safe bound
    'overtake_safe_distance': 5.0,
    'follow_safe_distance': 5.0,
}

EM_Planner_Config = {
    'total_length_t': 10.0,  # 规划总时间
    'unit_t': 1.0,  # 采样时间间隔
    'total_length_s': 200.0,  # 规划总距离
    'dense_unit_s': 0.1,  # 稠密距离间隔
    'sparse_unit_s': 1.0,  # 稀疏距离间隔
    'dense_dimension_s': 101,  # 稠密距离采样个数

    ## penalty config
    'spatial_potential_penalty': 100.0,  # spatial cost weight
    'reference_weight': 0.0,  # reference cost weight
    'exceed_speed_penalty': 1000.0,  # over speed penalty weight
    'low_speed_penalty': 10.0,  # low speed penalty weight
    'default_speed_cost': 1000.0,  # default speed cost
    'reference_speed_penalty': 100.0,  # hope to close to cruise speed
    'accel_penalty': 1.0,
    'decel_penalty': 1.0,
    'positive_jerk_coeff': 1.0,
    'negative_jerk_coeff': 1.0,
    'obstacle_weight': 1.0,
    'default_obstacle_cost': 10000.0
}

SPEED_LIMIT = []
CRUISE_SPEED = 25.0


class SpeedPoint:

    def __init__(self, s, t, v):
        self.s = s
        self.t = t
        self.v = v

    def set_s(self, s):
        self.s = s

    def set_t(self, t):
        self.t = t

    def set_v(self, v):
        self.v = v


class STGraphMessage:

    def __init__(self, c, r):
        self.c = c
        self.r = r


class STPoint:

    def __init__(self, s, t):
        self.s = s
        self.t = t


class STGraphPoint:

    def __init__(self) -> None:
        self.index_t = 0
        self.index_s = 0
        self.optimal_speed = 0.0
        self.reference_cost = 0.0
        self.obstacle_cost = 0.0
        self.spatial_potential_cost = 0.0
        self.total_cost = positive_infinity
        self.pre_point = None
        self.point = STPoint

    def Init(self, index_t, index_s, st_point: STPoint):
        self.index_t = index_t
        self.index_s = index_s
        self.point = st_point


class Trajectory:

    def __init__(self, trajectory_id, s, v, a, jerk, t):
        self.id = trajectory_id
        self.s = s
        self.v = v
        self.a = a
        self.jerk = jerk
        self.t = t


class TrajectoryPoint:

    def __init__(self, s, v, a, jerk, t):
        self.s = s
        self.v = v
        self.a = a
        self.jerk = jerk
        self.t = t


class Obstacle:

    def __init__(self, obstacle_enter_time, obstacle_exit_time,
                 obstacle_length, obstacle_speed, obstacle_distance,
                 ego_initial_velocity):
        self.obstacle_enter_time = obstacle_enter_time
        self.obstacle_exit_time = obstacle_exit_time
        self.obstacle_length = obstacle_length
        self.obstacle_speed = obstacle_speed
        self.obstacle_distance = obstacle_distance
        self.ego_initial_velocity = ego_initial_velocity
        self.obstacle_coordinate_in_S_T_graph = []
        self.safe_bound = []

    def calculate_obstacle_coordinate_in_S_T_graph(self):
        # 定义平行四边形的四个顶点坐标
        # B------------------->C
        # ^                    |
        # |                    |
        # |                    v
        # A--------------------D
        A = (self.obstacle_enter_time,
             self.obstacle_enter_time * self.ego_initial_velocity +
             self.obstacle_distance)
        B = (self.obstacle_enter_time,
             self.obstacle_enter_time * self.ego_initial_velocity +
             self.obstacle_distance + self.obstacle_length)
        C = (self.obstacle_exit_time,
             self.obstacle_enter_time * self.ego_initial_velocity +
             (self.obstacle_exit_time - self.obstacle_enter_time) *
             self.obstacle_speed + self.obstacle_length +
             self.obstacle_distance)
        D = (self.obstacle_exit_time,
             self.obstacle_enter_time * self.ego_initial_velocity +
             (self.obstacle_exit_time - self.obstacle_enter_time) *
             self.obstacle_speed + self.obstacle_distance)
        self.obstacle_coordinate_in_S_T_graph = [A, B, C, D]

    def calculate_safe_bound(self, overtake_safe_distance,
                             follow_safe_distance):
        # define bound [[begin point x, end point x],[begin point y, end point y]]
        overtake_bound = [[
            self.obstacle_coordinate_in_S_T_graph[1][0],
            self.obstacle_coordinate_in_S_T_graph[2][0]
        ],
                          [
                              self.obstacle_coordinate_in_S_T_graph[1][1] +
                              overtake_safe_distance,
                              self.obstacle_coordinate_in_S_T_graph[2][1] +
                              overtake_safe_distance
                          ]]
        follow_bound = [[
            self.obstacle_coordinate_in_S_T_graph[0][0],
            self.obstacle_coordinate_in_S_T_graph[3][0]
        ],
                        [
                            self.obstacle_coordinate_in_S_T_graph[0][1] -
                            follow_safe_distance,
                            self.obstacle_coordinate_in_S_T_graph[3][1] -
                            follow_safe_distance
                        ]]
        #[[overtake: (t0,t1) , (s0,s1)], [follow: (t0,t1) , (s0,s1)]]
        self.safe_bound = [overtake_bound, follow_bound]


class DPSTCost:

    def __init__(self, obstacle: Obstacle, init_point: TrajectoryPoint,
                 total_t, total_s, unit_t):
        self.obstacle = obstacle
        self.init_point = init_point
        self.total_t = total_t
        self.total_s = total_s
        self.unit_t = unit_t
        self.accel_cost_list = [-1.0] * 200  # 存储加速度cost的值，避免重复运算
        self.jerk_cost_list = [-1.0] * 400  # 存储jerk cost的值，避免重复运算

    def get_obstacle_cost(self, point: STGraphPoint):
        print("get_obstacle_cost")
        cost = 0.0
        s = point.point.s
        t = point.point.t

        obstacle = self.obstacle
        obstacle_coordinate_in_S_T_graph = obstacle.obstacle_coordinate_in_S_T_graph
        safe_bound = obstacle.safe_bound
        obstacle_speed = obstacle.obstacle_speed

        obstacle_enter_t = obstacle_coordinate_in_S_T_graph[0][0]
        obstacle_enter_t_idx = obstacle_enter_t / self.unit_t

        obstacle_exit_t = obstacle_coordinate_in_S_T_graph[2][0]
        obstacle_exit_t_idx = obstacle_exit_t / self.unit_t

        obstacle_enter_s_lower_bound = obstacle_coordinate_in_S_T_graph[0][1]
        obstacle_enter_s_upper_bound = obstacle_coordinate_in_S_T_graph[1][1]

        obstacle_exit_s_lower_bound = obstacle_coordinate_in_S_T_graph[3][1]
        obstacle_exit_s_upper_bound = obstacle_coordinate_in_S_T_graph[2][1]

        obstacle_overtake_enter_s_safe_bound = safe_bound[0][1][0]
        obstacle_overtake_exit_s_safe_bound = safe_bound[0][1][1]
        obstacle_follow_enter_s_safe_bound = safe_bound[1][1][0]
        obstacle_follow_exit_s_safe_bound = safe_bound[1][1][1]

        obstacle_s_upper_bound_by_time_idx = obstacle_enter_s_upper_bound + obstacle_speed * self.unit_t * (
            t - obstacle_enter_t)

        obstacle_s_lower_bound_by_time_idx = obstacle_enter_s_lower_bound + obstacle_speed * self.unit_t * (
            t - obstacle_enter_t)

        obstacle_overtake_s_safe_bound_by_time_idx = obstacle_overtake_enter_s_safe_bound + obstacle_speed * self.unit_t * (
            t - obstacle_enter_t)

        obstacle_follow_s_safe_bound_by_time_idx = obstacle_follow_enter_s_safe_bound + obstacle_speed * self.unit_t * (
            t - obstacle_enter_t)

        print(
            "obstacle_overtake_enter_s_safe_bound: {} obstacle_overtake_exit_s_safe_bound: {} obstacle_follow_enter_safe_bound: {} obstacle_follow_exit_safe_bound: {}"
            .format(obstacle_overtake_enter_s_safe_bound,
                    obstacle_overtake_exit_s_safe_bound,
                    obstacle_follow_enter_s_safe_bound,
                    obstacle_follow_exit_s_safe_bound))
        ## TODO
        if t >= obstacle_enter_t and t <= obstacle_exit_t:
            ## selected ego Behavior
            if Behavior is 'Follow' and s >= obstacle_s_lower_bound_by_time_idx:
                return positive_infinity
            elif Behavior is 'Overtake' and s <= obstacle_s_upper_bound_by_time_idx:
                return positive_infinity

            if s >= obstacle_s_lower_bound_by_time_idx and s <= obstacle_s_upper_bound_by_time_idx:
                return positive_infinity
            elif s > obstacle_s_upper_bound_by_time_idx and s < obstacle_overtake_s_safe_bound_by_time_idx:
                s_diff = Obstacle_Config[
                    'overtake_safe_distance'] + obstacle_s_upper_bound_by_time_idx - s
                cost += EM_Planner_Config[
                    'obstacle_weight'] * EM_Planner_Config[
                        'default_obstacle_cost'] * s_diff * s_diff
            elif s < obstacle_s_lower_bound_by_time_idx and s > obstacle_follow_s_safe_bound_by_time_idx:
                s_diff = Obstacle_Config[
                    'follow_safe_distance'] - obstacle_s_lower_bound_by_time_idx + s
                cost += EM_Planner_Config[
                    'obstacle_weight'] * EM_Planner_Config[
                        'default_obstacle_cost'] * s_diff * s_diff

        else:
            print("out of obstacle time range")

        print("obstacle_enter_t_idx: {} obstacle_exit_t_idx: {}".format(
            obstacle_enter_t_idx, obstacle_exit_t_idx))

        print("obstacle_coordinate_in_S_T_graph: {}".format(
            obstacle_coordinate_in_S_T_graph))
        print("safe_bound: {}".format(safe_bound))
        print("*********************************")
        return 0.0

    def get_spatial_potential_cost(self, point: STGraphPoint):
        print("get_spatial_potential_cost")
        spatial_potential_cost = (
            self.total_s -
            point.point.s) * EM_Planner_Config['spatial_potential_penalty']
        print("*********************************")
        return spatial_potential_cost

    ##TODO current not used
    def get_reference_cost(self, point: STPoint, reference_point: STPoint):
        print("get_reference_cost")
        reference_cost = EM_Planner_Config['reference_weight'] * (
            point.s - reference_point.s) * (point.s -
                                            reference_point.s) * self.unit_t
        print("*********************************")
        return reference_cost

    def get_speed_cost(self, first: STPoint, second: STPoint, speed_limit,
                       cruise_speed):
        print("get_speed_cost")
        speed_cost = 0.0
        speed = (second.s - first.s) / self.unit_t
        print("speed: {}".format(speed))
        if speed < 0.0:
            return positive_infinity
        det_speed = (speed - speed_limit) / speed_limit
        if det_speed > 0.0:
            print("det_speed is positive")
            speed_cost += EM_Planner_Config[
                'exceed_speed_penalty'] * EM_Planner_Config[
                    'default_speed_cost'] * det_speed * det_speed * self.unit_t
        elif det_speed < 0.0:
            print("det_speed is negative")
            speed_cost += EM_Planner_Config[
                'low_speed_penalty'] * EM_Planner_Config[
                    'default_speed_cost'] * -det_speed * self.unit_t

        if FLAGS_enable_dp_reference_speed:
            diff_speed = speed - cruise_speed
            speed_cost += EM_Planner_Config[
                'reference_speed_penalty'] * EM_Planner_Config[
                    'default_speed_cost'] * abs(diff_speed) * self.unit_t
        print("*********************************")
        return speed_cost

    def get_accel_cost(self, accel):
        print("get_accel_cost")
        cost = 0.0
        kEpsilon = 0.1
        kShift = 100.0
        accel_key = int(accel / kEpsilon + 0.5 + kShift)
        print("accel_key: {}".format(accel_key))

        if accel_key >= len(self.accel_cost_list):
            print("accel_key is out of range, return inf")
            return positive_infinity

        if self.accel_cost_list[accel_key] < 0.0:
            accel_sq = accel * accel
            max_acc = Car_Config['max_acceleration']
            max_dec = Car_Config['max_deceleration']
            accel_penalty = EM_Planner_Config['accel_penalty']
            decel_penalty = EM_Planner_Config['decel_penalty']

            if accel > 0.0:
                cost = accel_penalty * accel_sq
            else:
                cost = decel_penalty * accel_sq

            cost += accel_sq * decel_penalty * decel_penalty / (
                1.0 + np.exp(1.0 * (accel - max_dec))
            ) + accel_sq * accel_penalty * accel_penalty / (
                1.0 + np.exp(-1.0 * (accel - max_acc)))
            self.accel_cost_list[accel_key] = cost
        else:
            cost = self.accel_cost_list[accel_key]
        print("*********************************")
        return cost * self.unit_t

    def get_accel_cost_by_two_point(self, pre_speed, first: STPoint,
                                    second: STPoint):
        print("get_accel_cost_by_two_point")
        current_speed = (second.s - first.s) / self.unit_t
        print("current_speed: {} pre_speed: {}".format(current_speed,
                                                       pre_speed))
        accel = (current_speed - pre_speed) / self.unit_t
        print("accel: {}".format(accel))
        print("*********************************")
        return self.get_accel_cost(accel)

    def get_accel_cost_by_three_point(self, first: STPoint, second: STPoint,
                                      third: STPoint):
        print("get_accel_cost_by_three_point")
        accel = (first.s + third.s - 2.0 * second.s) / (self.unit_t *
                                                        self.unit_t)
        print("accel: {}".format(accel))
        print("*********************************")
        return self.get_accel_cost(accel)

    def get_jerk_cost(self, jerk):
        print("get_jerk_cost")
        cost = 0.0
        kEpsilon = 0.1
        kShift = 200.0
        jerk_key = int(jerk / kEpsilon + 0.5 + kShift)
        if jerk_key >= len(self.jerk_cost_list):
            return positive_infinity

        if self.jerk_cost_list[jerk_key] < 0.0:
            jerk_sq = jerk * jerk
            if jerk > 0.0:
                cost = EM_Planner_Config[
                    'positive_jerk_coeff'] * jerk_sq * self.unit_t
            else:
                cost = EM_Planner_Config[
                    'negative_jerk_coeff'] * jerk_sq * self.unit_t
            self.jerk_cost_list[jerk_key] = cost
        else:
            cost = self.jerk_cost_list[jerk_key]
        print("*********************************")
        return cost

    def get_jerk_cost_by_two_point(self, pre_speed, pre_acc,
                                   pre_point: STPoint, curr_point: STPoint):
        print("get_jerk_cost_by_two_point")
        curr_speed = (curr_point.s - pre_point.s) / self.unit_t
        curr_accel = (curr_speed - pre_speed) / self.unit_t
        jerk = (curr_accel - pre_acc) / self.unit_t
        print("jerk: {}".format(jerk))
        print("*********************************")
        return self.get_jerk_cost(jerk)

    def get_jerk_cost_by_three_point(self, first_speed, first_point: STPoint,
                                     second_point: STPoint,
                                     third_point: STPoint):
        print("get_jerk_cost_by_three_point")
        pre_speed = (second_point.s - first_point.s) / self.unit_t
        pre_acc = (pre_speed - first_speed) / self.unit_t
        curr_speed = (third_point.s - second_point.s) / self.unit_t
        curr_acc = (curr_speed - pre_speed) / self.unit_t
        jerk = (curr_acc - pre_acc) / self.unit_t
        print("jerk: {}".format(jerk))
        print("*********************************")
        return self.get_jerk_cost(jerk)

    def get_jerk_cost_by_four_point(self, first: STPoint, second: STPoint,
                                    third: STPoint, fourth: STPoint):
        print("get_jerk_cost_by_four_point")
        jerk = (fourth.s - 3.0 * third.s + 3.0 * second.s -
                first.s) / (self.unit_t * self.unit_t * self.unit_t)
        print("jerk: {}".format(jerk))
        print("*********************************")
        return self.get_jerk_cost(jerk)


class EMPlanner:

    def __init__(self, target_s, ref_v, initial_velocity, max_velocity,
                 min_velocity, max_acceleration, max_deceleration, max_jerk,
                 min_jerk, obstacle: Obstacle, init_point: TrajectoryPoint):
        self.target_s = target_s
        self.ref_v = ref_v
        self.initial_velocity = initial_velocity
        self.max_acceleration = max_acceleration
        self.max_deceleration = max_deceleration
        self.min_velocity = min_velocity
        self.max_velocity = max_velocity
        self.max_jerk = max_jerk
        self.min_jerk = min_jerk

        self.total_length_t = EM_Planner_Config['total_length_t']
        self.unit_t = EM_Planner_Config['unit_t']
        self.dimension_t = 0
        self.total_length_s = EM_Planner_Config['total_length_s']
        self.dense_unit_s = EM_Planner_Config['dense_unit_s']
        self.sparse_unit_s = EM_Planner_Config['sparse_unit_s']
        self.dense_dimension_s = EM_Planner_Config['dense_dimension_s']
        self.sparse_dimension_s = 0
        self.dimension_s = 0

        self.cost_table = None
        self.spatial_distance_by_index = None
        self.speed_limit_by_index = None
        self.dp_st_cost = DPSTCost(obstacle, init_point,
                                   EM_Planner_Config['total_length_t'],
                                   target_s, EM_Planner_Config['unit_t'])
        self.init_point = init_point

    def init_cost_table(self):
        print("init_cost_table")
        if self.unit_t < epsilon:
            print("unit_t is smaller than the epsilon")
            return False
        if self.dense_dimension_s < 1:
            print("dense_dimension_s is at least 1")
            return False
        self.dimension_t = math.ceil(self.total_length_t / self.unit_t) + 1
        print("dimension_t: {}".format(self.dimension_t))
        sparse_length_s = self.total_length_s - (self.dense_dimension_s -
                                                 1) * self.dense_unit_s
        print("sparse_length_s: {}".format(sparse_length_s))
        self.sparse_dimension_s = math.ceil(
            sparse_length_s /
            self.sparse_unit_s) if sparse_length_s > epsilon else 0
        print("sparse_dimension_s: {}".format(self.sparse_dimension_s))
        self.dense_dimension_s = self.dense_dimension_s if sparse_length_s > epsilon else (
            math.ceil(self.total_length_s / self.dense_unit_s) + 1)
        print("dense_dimension_s: {}".format(self.dense_dimension_s))
        self.dimension_s = self.dense_dimension_s + self.sparse_dimension_s
        print("dimension_s: {} dense_dimension_s: {} sparse_dimension_s: {}".
              format(self.dimension_s, self.dense_dimension_s,
                     self.sparse_dimension_s))

        if self.dimension_t < 1 or self.dimension_s < 1:
            print("Dp st cost table size incorrect")
            return False

        self.cost_table = [[STGraphPoint() for _ in range(self.dimension_s)]
                           for _ in range(self.dimension_t)]
        print("len(self.cost_table): {}".format(len(self.cost_table)))
        print("len(self.cost_table[0]): {}".format(len(self.cost_table[0])))

        curr_t = 0.0
        print("init cost table loop")
        for i in range(0, len(self.cost_table)):
            # print("i: {}".format(i))

            # print("curr_t: {}".format(curr_t))
            curr_s = 0.0
            print("init cost table dense part")

            for j in range(0, self.dense_dimension_s):
                # print("j: {}".format(j))
                self.cost_table[i][j].Init(i, j, STPoint(curr_s, curr_t))
                curr_s += self.dense_unit_s
            print("============================")

            print("init cost table sparse part")
            curr_s = (self.dense_dimension_s -
                      1) * self.dense_unit_s + self.sparse_unit_s

            for j in range(self.dense_dimension_s, len(self.cost_table[i])):
                # print("j: {}".format(j))
                self.cost_table[i][j].Init(i, j, STPoint(curr_s, curr_t))
                curr_s += self.sparse_unit_s
            curr_t += self.unit_t
            print("============================")

        self.spatial_distance_by_index = [0.0] * len(self.cost_table[0])
        for i in range(0, len(self.cost_table[0])):
            self.spatial_distance_by_index[i] = self.cost_table[0][i].point.s

        print("display init cost table")
        for i in range(len(self.cost_table)):
            for j in range(len(self.cost_table[0])):
                print("(i: {} , j: {}) t: {} s: {}".format(
                    i, j, self.cost_table[i][j].point.t,
                    self.cost_table[i][j].point.s))
        print("============================")
        print("spatial_distance_by_index: {}".format(
            self.spatial_distance_by_index))
        # print("============================")
        print("*********************************")

    ##TODO just simple use, need to get the speed limit more accuracy
    def init_speed_limit_look_up(self):
        SPEED_LIMIT = [FLAGS_planning_upper_speed_limit] * self.dimension_s
        self.speed_limit_by_index = SPEED_LIMIT

    def calculate_total_cost(self):
        print("calculate_total_cost")
        # t corresponding to col 列
        # s corresponding to row 行
        next_highest_row = 0
        next_lowest_row = 0

        print("calculate total cost loop")
        for c in range(len(self.cost_table)):

            highest_row = 0
            lowest_row = len(self.cost_table[-1]) - 1

            count = next_highest_row - next_lowest_row + 1
            print("count: {}".format(count))
            print("dimense_s: ( {} , {} )".format(0.0,
                                                  len(self.cost_table[0])))
            print("next_highest_row: {} next_lowest_row: {}".format(
                next_highest_row, next_lowest_row))
            if count > 0:
                print("calulate cost at loop")
                for r in range(next_lowest_row, next_highest_row + 1):
                    msg = STGraphMessage(c, r)
                    self.calculate_cost_at(msg)
                print("============================")

            print("get row range loop")

            for r in range(next_lowest_row, next_highest_row + 1):
                # print("(c: {} , r: {})".format(c, r))
                if self.cost_table[c][r].total_cost < positive_infinity:
                    h_r, l_r = self.get_row_range(self.cost_table[c][r])
                    # print("h_r: {} l_r: {}".format(h_r, l_r))
                    highest_row = max(highest_row, h_r)
                    lowest_row = min(lowest_row, l_r)

            print("============================")
            next_highest_row = highest_row
            next_lowest_row = lowest_row
        print("============================")

        print("display final cost table")
        for i in range(len(self.cost_table)):
            for j in range(len(self.cost_table[0])):
                print(
                    "(i: {} , j: {}) t: {} s: {} optimal_speed: {} reference_cost: {} obstacle_cost: {} spatial_potential_cost: {} total_cost: {}"
                    .format(i, j, self.cost_table[i][j].point.t,
                            self.cost_table[i][j].point.s,
                            self.cost_table[i][j].optimal_speed,
                            self.cost_table[i][j].reference_cost,
                            self.cost_table[i][j].obstacle_cost,
                            self.cost_table[i][j].spatial_potential_cost,
                            self.cost_table[i][j].total_cost))
        print("============================")
        print("#########################################")

    def calculate_cost_at(self, msg: STGraphMessage):
        print("calculate_cost_at")
        c = msg.c
        r = msg.r
        print("(c: {} r: {})".format(c, r))

        cost_cr = self.cost_table[c][r]

        cost_cr.obstacle_cost = self.dp_st_cost.get_obstacle_cost(cost_cr)

        if cost_cr.obstacle_cost >= positive_infinity:
            print("trajectory is in obstacle range, return directly")
            print("============================")
            return

        cost_cr.spatial_potential_cost = self.dp_st_cost.get_spatial_potential_cost(
            cost_cr)

        cost_init = self.cost_table[0][0]
        if c == 0:
            print("c == 0, return directly")
            cost_cr.total_cost = 0.0
            cost_cr.optimal_speed = self.init_point.v
            print("============================")
            return
        speed_limit = self.speed_limit_by_index[r]
        cruise_speed = CRUISE_SPEED

        # 两个连续时间点的距离小于min_s_consider_speed的时候，将这两个点之间的运动简化为匀加速，当大于此值是可以考虑更复杂的运动模型
        min_s_consider_speed = self.dense_unit_s * self.dimension_t

        # 计算除初始点外，第一个点的加速度，用当前点的s/unit_t得到当前点的速度,再用当前点的速度减去初始速度 / unit_t 得到该点的加速度值
        if c == 1:
            print("c == 1")

            # s = v0 * t + 1/2 * a * t^2
            # a = 2 * ( s(1) / unit_t - init_v) / unit_t
            print("r: {} curr_point: (t: {} (idx: {}) s: {} (idx: {}))".format(
                r, cost_cr.point.t, cost_cr.index_t, cost_cr.point.s,
                cost_cr.index_s))
            acc = 2 * (cost_cr.point.s / self.unit_t -
                       self.init_point.v) / self.unit_t
            speed = self.init_point.v + acc * self.unit_t
            print("estimate acc: {} estimate speed: {}".format(acc, speed))
            if acc < self.max_deceleration or acc > self.max_acceleration:
                print(
                    "acc < self.max_deceleration or acc > self.max_acceleration"
                )
                return
            # 如果第一个点的速度接近于0，证明第一个点的减速度特别大，如果当前s已经大于min_s_consider_speed的时候就不能进行运动简化
            ##TODO to be update the description
            if speed < -epsilon and cost_cr.point.s > min_s_consider_speed:
                print(
                    "speed < -epsilon and cost_cr.point.s > min_s_consider_speed"
                )
                return

            # collision check
            if self.check_over_lop_on_dp_st_graph():
                print("is collision")
                return
            edge_cost = self.calculate_edge_cost_for_second_col(
                r, speed_limit, cruise_speed)
            cost_cr.total_cost = cost_cr.obstacle_cost + cost_cr.spatial_potential_cost + cost_init.total_cost + edge_cost
            cost_cr.pre_point = cost_init
            cost_cr.optimal_speed = speed
            print(
                "current_total_cost: {} = obstacle_cost: {} + spatial_potential_cost: {} + pre_total_cost: {} + edge_cost: {}"
                .format(cost_cr.total_cost, cost_cr.obstacle_cost,
                        cost_cr.spatial_potential_cost, cost_init.total_cost,
                        edge_cost))
            print("============================")
            return

        # 计算当前状态下可以行驶到最远的S位置的索引
        k_speed_range_buffer = 0.2
        ##TODO 为啥是减去max speed * unit t ??
        pre_lowest_s = cost_cr.point.s - FLAGS_planning_upper_speed_limit * (
            1 + k_speed_range_buffer) * self.unit_t

        print("cost_cr.point.s: {} pre_lowest_s: {}".format(
            cost_cr.point.s, pre_lowest_s))

        pre_lowest_idx = bisect.bisect_left(self.spatial_distance_by_index,
                                            pre_lowest_s)

        r_low = 0
        if pre_lowest_idx == len(self.spatial_distance_by_index):
            r_low = self.dimension_s - 1
        else:
            r_low = pre_lowest_idx

        r_pre_size = r - r_low + 1

        print("r_pre_size: {} = r: {} - r_row: {} + 1".format(
            r_pre_size, r, r_low))
        pre_col = self.cost_table[c - 1]
        curr_speed_limit = speed_limit

        if c == 2:
            print("c == 2")

            for i in range(r_pre_size):
                # print("Here")
                r_pre = r - i
                print("r_pre: {} = r: {} - i: {}".format(r_pre, r, i))
                if (math.isinf(pre_col[r_pre].total_cost)
                        or pre_col[r_pre].pre_point is None):
                    print(
                        "math.isinf(pre_col[r_pre].total_cost)  or pre_col[r_pre].pre_point is None"
                    )
                    continue
                # use curr_v = (point.s - pre_point.s) / unit_t as current v
                # use pre_v = (pre_point.s - prepre_point.s) / unit_t as pre_v
                # current acc estimate: curr_a = (curr_v - pre_v) / unit_t = (point.s  + prepre_point.s - 2 * pre_point.s) / (unit_t)^2
                print(
                    "r: {} curr_point: (t: {} (idx: {}) s: {} (idx: {}) optimal_v: {})\nr_pre: {} pre_point: (t: {} (idx: {}) s: {} (idx: {}) optimal_v: {}))"
                    .format(r, cost_cr.point.t, cost_cr.index_t,
                            cost_cr.point.s, cost_cr.index_s,
                            cost_cr.optimal_speed, r_pre,
                            pre_col[r_pre].point.t, pre_col[r_pre].index_t,
                            pre_col[r_pre].point.s, pre_col[r_pre].index_s,
                            pre_col[r_pre].optimal_speed))
                curr_a = 2 * (
                    (cost_cr.point.s - pre_col[r_pre].point.s) / self.unit_t -
                    pre_col[r_pre].optimal_speed) / self.unit_t
                speed = pre_col[r_pre].optimal_speed + curr_a * self.unit_t
                print("estimate acc: {} estimate speed: {}".format(
                    curr_a, speed))
                if curr_a < self.max_deceleration or curr_a > self.max_acceleration:
                    print(
                        "acc < self.max_deceleration or acc > self.max_acceleration"
                    )
                    continue

                if speed < -epsilon and cost_cr.point.s > min_s_consider_speed:
                    print(
                        "speed < -epsilon and cost_cr.point.s > min_s_consider_speed"
                    )
                    continue

                if self.check_over_lop_on_dp_st_graph():
                    print("is collision")
                    continue

                curr_speed_limit = min(curr_speed_limit,
                                       self.speed_limit_by_index[r_pre])
                edge_cost = self.calculate_edge_cost_for_third_col(
                    r, r_pre, curr_speed_limit, cruise_speed)
                cost = cost_cr.obstacle_cost + cost_cr.spatial_potential_cost + pre_col[
                    r_pre].total_cost + edge_cost

                print(
                    "current_total_cost: {} = obstacle_cost: {} + spatial_potential_cost: {} + pre_total_cost: {} + edge_cost: {}"
                    .format(cost, cost_cr.obstacle_cost,
                            cost_cr.spatial_potential_cost,
                            pre_col[r_pre].total_cost, edge_cost))
                if cost < cost_cr.total_cost:
                    cost_cr.total_cost = cost
                    cost_cr.pre_point = pre_col[r_pre]
                    cost_cr.optimal_speed = pre_col[
                        r_pre].optimal_speed + curr_a * self.unit_t
            print("============================")
            return

        print("c >= 2")
        for i in range(r_pre_size):
            r_pre = r - i
            print("r_pre: {} = r: {} - i: {}".format(r_pre, r, i))
            if math.isinf(pre_col[r_pre].total_cost):
                print("pre total cost is inf")
                continue
            if pre_col[r_pre].pre_point is None:
                print("pre_col pre_point is None")
                continue
            # use curr_v = (point.s - pre_point.s) / unit_t as current v
            # use pre_v = (pre_point.s - prepre_point.s) / unit_t as pre_v
            # current acc estimate: curr_a = (curr_v - pre_v) / unit_t = (point.s  + prepre_point.s - 2 * pre_point.s) / (unit_t)^2
            curr_a = 2 * (
                (cost_cr.point.s - pre_col[r_pre].point.s) / self.unit_t -
                pre_col[r_pre].optimal_speed) / self.unit_t
            if curr_a < self.max_deceleration or curr_a > self.max_acceleration:
                print("curr_a is out of range")
                continue

            if pre_col[
                    r_pre].optimal_speed + curr_a * self.unit_t < -epsilon and cost_cr.point.s > min_s_consider_speed:
                print(
                    "next speed is small than -epsilon and the point_s is larger than the min_s_consider_speed"
                )
                continue

            if self.check_over_lop_on_dp_st_graph():
                print("is collision")
                continue

            r_prepre = pre_col[r_pre].pre_point.index_s

            prepre_graph_point = self.cost_table[c - 2][r_prepre]

            if math.isinf(prepre_graph_point.total_cost):
                print("prepre total cost is inf")
                continue
            if prepre_graph_point.pre_point is None:
                print("prepre_col pre_point is None")
                continue

            triple_pre_point = prepre_graph_point.pre_point.point
            prepre_point = prepre_graph_point.point
            pre_point = pre_col[r_pre].point
            curr_point = cost_cr.point

            curr_speed_limit = min(curr_speed_limit,
                                   self.speed_limit_by_index[r_pre])
            edge_cost = self.calculate_edge_cost(triple_pre_point,
                                                 prepre_point, pre_point,
                                                 curr_point, curr_speed_limit,
                                                 cruise_speed)
            cost = cost_cr.obstacle_cost + cost_cr.spatial_potential_cost + pre_col[
                r_pre].total_cost + edge_cost
            print(
                "current_total_cost: {} = obstacle_cost: {} + spatial_potential_cost: {} + pre_total_cost: {} + edge_cost: {}"
                .format(cost, cost_cr.obstacle_cost,
                        cost_cr.spatial_potential_cost,
                        pre_col[r_pre].total_cost, edge_cost))
            if cost < cost_cr.total_cost:
                cost_cr.total_cost = cost
                cost_cr.pre_point = pre_col[r_pre]
                cost_cr.optimal_speed = pre_col[
                    r_pre].optimal_speed + curr_a * self.unit_t
        print("============================")
        print("*********************************")

    ##TODO Placeholder
    def check_over_lop_on_dp_st_graph(self):
        print("check_over_lop_on_dp_st_graph")

        print("*********************************")
        return False

    # calculate the s range for next step
    def get_row_range(self, point: STGraphPoint):
        # print("get_row_range")
        h_r = 0
        l_r = 0
        v0 = 0.0
        acc_coeff = 0.5
        # if pre point is none set the v0 as the init v, otherwise, set the v0 as the current point speed
        if point.pre_point is None:
            # print("point.pre_point is None")
            v0 = self.init_point.v
        else:
            # print("point.pre_point not None")
            v0 = point.optimal_speed

        max_s_size = self.dimension_s - 1
        # t^2
        t_squared = self.unit_t * self.unit_t
        ## calculate s upper bound
        # use max acceleration to compute the max s we can reach s = v0 * t + 0.5 * a * t^2
        s_upper_bound = v0 * self.unit_t + acc_coeff * self.max_acceleration * t_squared + point.point.s
        print("s_upper_bound: {}".format(s_upper_bound))

        next_highest_idx = bisect.bisect_left(self.spatial_distance_by_index,
                                              s_upper_bound)

        if next_highest_idx == len(self.spatial_distance_by_index):
            h_r = max_s_size
        else:
            h_r = next_highest_idx

        ## calculate s lower bound
        # use max deceleration, s is monotonically increasing
        s_lower_bound = max(
            0.0, v0 * self.unit_t +
            acc_coeff * self.max_deceleration * t_squared) + point.point.s
        print("s_lower_bound: {}".format(s_lower_bound))

        next_lowest_idx = bisect.bisect_left(self.spatial_distance_by_index,
                                             s_lower_bound)

        if next_lowest_idx == len(self.spatial_distance_by_index):
            l_r = max_s_size
        else:
            l_r = next_lowest_idx
        # print("*********************************")
        return h_r, l_r

    def retrieve_speed_profile(self):
        print("retrieve_speed_profile")
        min_cost = positive_infinity
        best_end_point = None
        for cur_point in self.cost_table[-1]:
            if (not math.isinf(
                    cur_point.total_cost)) and cur_point.total_cost < min_cost:
                best_end_point = cur_point
                min_cost = cur_point.total_cost
                # print("best_end_point: {} min_cost: {}".format(
                #     best_end_point, min_cost))

        if best_end_point is None:
            print("Fail to find best feasiable speed profile")

        speed_profile = []
        cur_point = best_end_point
        while cur_point is not None:
            speed_point = SpeedPoint(0, 0, 0)
            speed_point.set_s(cur_point.point.s)
            speed_point.set_t(cur_point.point.t)
            speed_point.set_v(cur_point.optimal_speed)
            speed_profile.append(speed_point)
            cur_point = cur_point.pre_point

        speed_profile.reverse()

        for i in range(0, len(speed_profile) - 1):
            v = (speed_profile[i + 1].s - speed_profile[i].s) / (
                speed_profile[i + 1].t - speed_profile[i].t + 1e-3)
            speed_profile[i].set_v(v)
        print("*********************************")
        return speed_profile

    def calculate_edge_cost(self, first: STPoint, second: STPoint,
                            third: STPoint, fourth: STPoint, speed_limit,
                            cruise_speed):
        print("calculate_edge_cost")
        speed_cost = self.dp_st_cost.get_speed_cost(third, fourth, speed_limit,
                                                    cruise_speed)
        accel_cost = self.dp_st_cost.get_accel_cost_by_three_point(
            second, third, fourth)
        jerk_cost = self.dp_st_cost.get_jerk_cost_by_four_point(
            first, second, third, fourth)

        total_cost = speed_cost + accel_cost + jerk_cost
        print(
            "total_cost: {} = speed_cost: {} + accel_cost: {} + jerk_cost: {}".
            format(total_cost, speed_cost, accel_cost, jerk_cost))
        print("*********************************")
        return total_cost

    def calculate_edge_cost_for_second_col(self, row, speed_limit,
                                           cruise_speed):
        print("calculate_edge_cost_for_second_col")

        init_speed = self.init_point.v
        init_acc = self.init_point.a
        pre_point = self.cost_table[0][0]
        curr_point = self.cost_table[1][row]
        print(
            "curr_point:(t: {} (idx: {}), s: {} (idx: {}))  pre_point:(t: {} (idx: {}), s: {} (idx: {}))"
            .format(curr_point.point.t, curr_point.index_t, curr_point.point.s,
                    curr_point.index_s, pre_point.point.t, pre_point.index_t,
                    pre_point.point.s, pre_point.index_s))
        speed_cost = self.dp_st_cost.get_speed_cost(pre_point.point,
                                                    curr_point.point,
                                                    speed_limit, cruise_speed)
        accel_cost = self.dp_st_cost.get_accel_cost_by_two_point(
            init_speed, pre_point.point, curr_point.point)
        jerk_cost = self.dp_st_cost.get_jerk_cost_by_two_point(
            init_speed, init_acc, pre_point.point, curr_point.point)
        total_cost = speed_cost + accel_cost + jerk_cost
        print(
            "total_edge_cost: {} = speed_cost: {} + accel_cost: {} + jerk_cost: {}"
            .format(total_cost, speed_cost, accel_cost, jerk_cost))
        print("*********************************")
        return total_cost

    def calculate_edge_cost_for_third_col(self, curr_row, pre_row, speed_limit,
                                          cruise_speed):
        print("calculate_edge_cost_for_third_col")
        init_speed = self.init_point.v
        first = self.cost_table[0][0]
        second = self.cost_table[1][pre_row]
        third = self.cost_table[2][curr_row]

        print(
            "curr_point:(t: {} (idx: {}), s: {} (idx: {}))  pre_point:(t: {} (idx: {}), s: {} (idx: {}) prepre_point:(t: {} (idx: {}), s: {} (idx: {}))"
            .format(third.point.t, third.index_t, third.point.s, third.index_s,
                    second.point.t, second.index_t, second.point.s,
                    second.index_s, first.point.t, first.index_t,
                    first.point.s, first.index_s))
        speed_cost = self.dp_st_cost.get_speed_cost(second.point, third.point,
                                                    speed_limit, cruise_speed)
        accel_cost = self.dp_st_cost.get_accel_cost_by_three_point(
            first.point, second.point, third.point)
        jerk_cost = self.dp_st_cost.get_jerk_cost_by_three_point(
            init_speed, first.point, second.point, third.point)
        total_cost = speed_cost + accel_cost + jerk_cost

        print(
            "total_edge_cost: {} = speed_cost: {} + accel_cost: {} + jerk_cost: {}"
            .format(total_cost, speed_cost, accel_cost, jerk_cost))
        print("*********************************")
        return total_cost


if __name__ == "__main__":
    print("main function")
    init_trajectory_point = TrajectoryPoint(0.0, 10.0, 0.0, 0.0, 0.0)

    obstacle = Obstacle(Obstacle_Config['obstacle_enter_time'],
                        Obstacle_Config['obstacle_exit_time'],
                        Obstacle_Config['obstacle_length'],
                        Obstacle_Config['obstacle_speed'],
                        Obstacle_Config['obstacle_distance'],
                        Car_Config['initial_velocity'])
    obstacle.calculate_obstacle_coordinate_in_S_T_graph()
    obstacle.calculate_safe_bound(Obstacle_Config['overtake_safe_distance'],
                                  Obstacle_Config['follow_safe_distance'])

    EM_Planner = EMPlanner(target_s, ref_v, Car_Config['initial_velocity'],
                           Car_Config['max_velocity'],
                           Car_Config['min_velocity'],
                           Car_Config['max_acceleration'],
                           Car_Config['max_deceleration'],
                           Car_Config['max_jerk'], Car_Config['min_jerk'],
                           obstacle, init_trajectory_point)
    EM_Planner.init_cost_table()
    # print(
    #     "total_length_t: {}\nunit_t: {}\ndimension_t: {}\ntotal_length_s: {}\ndense_unit_s: {}\nsparse_unit_s: {}\ndense_dimension_s: {}\nsparse_dimenstion_s: {}\ndimension_s: {}"
    #     .format(
    #         EM_Planner.total_length_t,
    #         EM_Planner.unit_t,
    #         EM_Planner.dimension_t,
    #         EM_Planner.total_length_s,
    #         EM_Planner.dense_unit_s,
    #         EM_Planner.sparse_unit_s,
    #         EM_Planner.dense_dimension_s,
    #         EM_Planner.sparse_dimension_s,
    #         EM_Planner.dimension_s,
    #     ))
    EM_Planner.init_speed_limit_look_up()
    # print("speed limit: {}".format(EM_Planner.speed_limit_by_index))

    EM_Planner.calculate_total_cost()

    speed_profile = EM_Planner.retrieve_speed_profile()

    best_trajectory_t = []
    best_trajectory_s = []
    best_trajectory_v = []

    for value in speed_profile:
        best_trajectory_s.append(value.s)
        best_trajectory_t.append(value.t)
        best_trajectory_v.append(value.v)

    print("best_trajectory_t: {}".format(best_trajectory_t))
    print("best_trajectory_s: {}".format(best_trajectory_s))

    print("accel_cost_list: {}".format(EM_Planner.dp_st_cost.accel_cost_list))
    print("jerk_cost_list: {}".format(EM_Planner.dp_st_cost.jerk_cost_list))

    cost_table = EM_Planner.cost_table
    list_t = []
    list_s = []
    list_v = []

    for i in range(len(cost_table)):
        for j in range(len(cost_table[0])):
            cost_table_i_j = cost_table[i][j]
            list_t.append(cost_table_i_j.point.t)
            list_s.append(cost_table_i_j.point.s)
            list_v.append(cost_table_i_j.optimal_speed)

    plt.figure(figsize=(20, 15))
    obstacle_in_ST_graph = obstacle.obstacle_coordinate_in_S_T_graph
    safe_bound = obstacle.safe_bound
    plt.subplot(2, 1, 1)
    # plot obstacle coordinate in S-T graph

    plt.plot([obstacle_in_ST_graph[0][0], obstacle_in_ST_graph[3][0]],
             [obstacle_in_ST_graph[0][1], obstacle_in_ST_graph[3][1]], 'r')
    plt.plot([obstacle_in_ST_graph[1][0], obstacle_in_ST_graph[2][0]],
             [obstacle_in_ST_graph[1][1], obstacle_in_ST_graph[2][1]], 'r')
    plt.plot([obstacle_in_ST_graph[0][0], obstacle_in_ST_graph[1][0]],
             [obstacle_in_ST_graph[0][1], obstacle_in_ST_graph[1][1]], 'r')
    plt.plot([obstacle_in_ST_graph[3][0], obstacle_in_ST_graph[2][0]],
             [obstacle_in_ST_graph[3][1], obstacle_in_ST_graph[2][1]], 'r')

    # plot safe bound
    plt.plot(safe_bound[0][0], safe_bound[0][1], 'b--')
    plt.plot(safe_bound[1][0], safe_bound[1][1], 'b--')

    plt.scatter(list_t, list_s, color='blue')
    plt.scatter(best_trajectory_t,
                best_trajectory_s,
                color='red',
                label='best_trajectory')
    plt.xlabel('Time(s)')
    plt.ylabel('Space(m)')
    plt.title('S-T Samples')
    plt.legend()
    plt.grid()

    plt.subplot(2, 1, 2)
    plt.scatter(list_t, list_v, color='blue')

    plt.scatter(best_trajectory_t,
                best_trajectory_v,
                color='red',
                label='best_trajectory')
    plt.xlabel('Time(s)')
    plt.ylabel('Velocity(m/s)')
    plt.title('V-T Samples')
    plt.grid()

    plt.show()
