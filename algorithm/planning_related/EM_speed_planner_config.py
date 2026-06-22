# 正无穷大
positive_infinity = float('inf')
# 负无穷大
negative_infinity = float('-inf')

## truck behivour -> from decision module
Behivour = 'Follow'  # Overtake / Follow / Stop

# Parameters
Car_Config = {
    'initial_velocity': 10.0,
    'max_acceleration': 2.0,
    'max_deceleration': -3.0,
    'max_velocity': 27.0,
    'min_velocity': 0.0,
    'max_jerk': 1.0,
    'min_jerk': -2.0,
}

SPEED_LIMIT = 27.0
CRUISE_SPEED = 25.0

FLAGS_planning_upper_speed_limit = 27.0
FLAGS_enable_dp_reference_speed = True

ref_v = 15.0  # m/s
target_s = 150.0  # m
# Obstacle param
Obstacle_Config = {
    'obstacle_enter_time': 4.0,
    'obstacle_exit_time': 8.0,
    'obstacle_length': 10.0,
    'obstacle_speed': 15.0,
    'obstacle_distance': 0.0,
    # safe bound
    'overtake_safe_distance': 5.0,
    'follow_safe_distance': 5.0,
}

# safe bound
overtake_safe_distance = 5.0  # m
follow_safe_distance = 5.0  # m

EM_Planner_Config = {
    'total_length_t': 10.0,  # 规划总时间
    'unit_t': 1.0,  # 采样时间间隔
    'total_length_s': 100.0,  # 规划总距离
    'dense_unit_s': 1.0,  # 稠密距离间隔
    'sparse_unit_s': 5.0,  # 稀疏距离间隔
    'dense_dimension_s': 11,  # 稠密距离采样个数
    'spatial_potential_penalty': 100.0,  # spatial cost weight
    'reference_weight': 0.0,  # reference cost weight
    'exceed_speed_penalty': 1000.0,  # over speed penalty weight
    'low_speed_penalty': 10.0,  # low speed penalty weight
    'default_speed_cost': 1000.0,  # default speed cost
    'reference_speed_penalty': 10.0,  # hope to close to cruise speed
    'accel_penalty': 1.0,
    'decel_penalty': 1.0,
    'positive_jerk_coeff': 1.0,
    'negative_jerk_coeff': 1.0,
}
