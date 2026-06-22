from cmath import inf, nan
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d
from matplotlib.patches import Polygon

PLANNING_DURATION = 10.0  # 规划时长 s
SAMPLE_RATE = 20.0  #时间采样频率
NUM_TIME_SAMPLES = int(PLANNING_DURATION * SAMPLE_RATE) + 1  # 时间采样数量
DELTA_T = 1 / SAMPLE_RATE
Behivour = 'Follow'  # Overtake / Follow / Stop


class Trajectory:

    def __init__(self, trajectory_id, s, v, a, jerk, t):
        self.id = trajectory_id
        self.s = s
        self.v = v
        self.a = a
        self.jerk = jerk
        self.t = t

    def smooth(self, s_smooth, t_smooth):
        self.s = s_smooth
        self.t = t_smooth


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


class LatticePlanner:

    def __init__(self, initial_velocity, max_velocity, min_velocity,
                 max_acceleration, max_deceleration, max_jerk, min_jerk,
                 num_samples):
        self.initial_velocity = initial_velocity
        self.max_acceleration = max_acceleration
        self.max_deceleration = max_deceleration
        self.num_samples = num_samples
        self.min_velocity = min_velocity
        self.max_velocity = max_velocity
        self.max_jerk = max_jerk
        self.min_jerk = min_jerk
        self.trajectories = []
        self.time_samples = []
        # self.velocity_samples = []
        # self.acceleration_samples = []
        self.jerk_samples = []

    def sample(self):
        self.time_samples = np.linspace(0, PLANNING_DURATION, NUM_TIME_SAMPLES)
        # self.velocity_samples = np.linspace(self.min_velocity,
        #                                     self.max_velocity,
        #                                     self.num_samples)
        # self.acceleration_samples = np.linspace(self.max_deceleration,
        #                                         self.max_acceleration,
        #                                         self.num_samples)
        self.jerk_samples = np.linspace(self.max_jerk, self.min_jerk,
                                        self.num_samples)

    def generate_candidate_trajectories(self, ref_v):
        for i in range(self.num_samples):
            s = 0
            t = 0
            v = self.initial_velocity
            a = 0
            jerk = 0

            s_data = []
            v_data = []
            a_data = []
            jerk_data = []
            t_data = []

            for j in range(len(self.time_samples)):

                # a = self.acceleration_samples[
                #     i] if v < self.velocity_samples[i] else max_deceleration
                jerk = self.jerk_samples[i]
                jerk_data.append(jerk)

                a = max(
                    min(a + jerk * (self.time_samples[j] - t),
                        max_acceleration), max_deceleration)

                a_data.append(a)
                v = max(min(v + a * (self.time_samples[j] - t), max_velocity),
                        min_velocity)
                v_data.append(v)
                s += v * (self.time_samples[j] - t)
                s_data.append(s)
                t = self.time_samples[j]
                t_data.append(t)
            #print("s:\n {}".format(s_data))
            #print("t:\n {}".format(t_data))
            self.trajectories.append(
                Trajectory(i, s_data, v_data, a_data, jerk_data, t_data))

    def smooth_trajectories(self):
        for trajectory in self.trajectories:
            s_smooth, t_smooth = self.interpolate_trajectory(
                trajectory.s, trajectory.t)
            trajectory.smooth(s_smooth, t_smooth)

    def interpolate_trajectory(self, s, t):
        f = interp1d(t, s, kind='cubic')
        t_smooth = np.linspace(min(t), max(t), num=1000)
        s_smooth = f(t_smooth)
        return s_smooth, t_smooth


class SpeedDecider:

    def __init__(self, max_velocity, min_velocity, max_acceleration,
                 max_deceleration, ref_v, target_s):
        self.max_acceleration = max_acceleration
        self.max_deceleration = max_deceleration
        self.min_velocity = min_velocity
        self.max_velocity = max_velocity
        self.ref_v = ref_v
        self.target_s = target_s

    def collision_checker(self, obstacle, candidate_trajectory):
        no_collision_trajectory = []
        enter_idx = int(obstacle.obstacle_enter_time / DELTA_T)
        exit_idx = int(obstacle.obstacle_exit_time / DELTA_T)

        print("enter_idx: {} exit_idx: {}".format(enter_idx, exit_idx))
        # print("obstacle.obstacle_coordinate_in_S_T_graph: {}".format(
        #     obstacle.obstacle_coordinate_in_S_T_graph))

        for trajectory in candidate_trajectory:
            is_collision = False
            print("id: {}".format(trajectory.id))
            for i in range(enter_idx, exit_idx):
                print("i: {}".format(i))
                print("s: {}".format(trajectory.s[i]))

                print("upper bound: {}".format(
                    (obstacle.obstacle_coordinate_in_S_T_graph[1][1] +
                     obstacle.obstacle_speed * DELTA_T * (i - enter_idx))))
                print("lower bound: {}".format(
                    (obstacle.obstacle_coordinate_in_S_T_graph[0][1] +
                     obstacle.obstacle_speed * DELTA_T * (i - enter_idx))))
                if trajectory.s[i] >= (
                        obstacle.obstacle_coordinate_in_S_T_graph[0][1] +
                        obstacle.obstacle_speed * DELTA_T *
                    (i - enter_idx)) and trajectory.s[i] <= (
                        obstacle.obstacle_coordinate_in_S_T_graph[1][1] +
                        obstacle.obstacle_speed * DELTA_T * (i - enter_idx)):
                    # print("trajectory id : {} is collision in time: {}".format(
                    #     trajectory.id, i * DELTA_T))
                    is_collision = True
                    break
            if not is_collision:
                # print("trajectory id : {} no collision".format(trajectory.id))
                no_collision_trajectory.append(trajectory)

        return no_collision_trajectory

    def behivour_decider(self, obstacle, candidate_trajectory):
        enter_idx = int(obstacle.obstacle_enter_time / DELTA_T)
        exit_idx = int(obstacle.obstacle_exit_time / DELTA_T)
        behivour_candidate_trajectory = []

        for trajectory in candidate_trajectory:
            match_behivours = True
            if Behivour is 'Overtake':
                for i in range(enter_idx, exit_idx):
                    if trajectory.s[i] <= (
                            obstacle.obstacle_coordinate_in_S_T_graph[0][1] +
                            obstacle.obstacle_speed * DELTA_T *
                        (i - enter_idx)):
                        match_behivours = False
                        break
                if match_behivours:
                    behivour_candidate_trajectory.append(trajectory)
            elif Behivour is 'Follow':
                for i in range(enter_idx, exit_idx):
                    if trajectory.s[i] >= (
                            obstacle.obstacle_coordinate_in_S_T_graph[1][1] +
                            obstacle.obstacle_speed * DELTA_T *
                        (i - enter_idx)):
                        match_behivours = False
                        break
                if match_behivours:
                    behivour_candidate_trajectory.append(trajectory)
            elif Behivour is 'Stop':
                if trajectory.v[-1] == 0:
                    behivour_candidate_trajectory.append(trajectory)
        return behivour_candidate_trajectory

    #TODO need update the evaluator conditions
    def candidate_trajectories_evaluator(self, candidate_trajectory):
        w_s = 1.0
        w_v = 1.0
        w_a = 1.0
        w_jerk = 1.0
        best_trajectory_id = -1
        best_cost = 1e6

        for trajectory in candidate_trajectory:
            # end s cost
            cost_s = w_s * (self.target_s - trajectory.s[-1])**2

            # average v is near ref v cost
            cost_v = w_v * (
                (sum([v for v in trajectory.v]) / len(trajectory.v)) -
                self.ref_v)**2

            # end v cost
            cost_v = w_v * (trajectory.v[-1] - ref_v)**2

            # acceleration cost
            cost_a = w_a * (sum([a**2
                                 for a in trajectory.a]) / len(trajectory.a))

            # jerk cost
            cost_jerk = w_jerk * (trajectory.jerk[0])**2

            # consider all cost
            total_cost = cost_s + cost_v + cost_a + cost_jerk

            ## do not consider s cost
            # total_cost = cost_v + cost_a + cost_jerk

            if total_cost < best_cost:
                best_trajectory_id = trajectory.id
                best_cost = total_cost
        return best_cost, best_trajectory_id


if __name__ == "__main__":
    # Parameters
    initial_velocity = 10.0  # 初始速度 m/s
    max_acceleration = 2.0  # 最大加速度 m/s^2
    max_deceleration = -3.0  # 最大减速度 m/s^2
    max_velocity = 27.0  # 最大速度 m/s
    min_velocity = 0.0  # 最小速度 m/s
    max_jerk = 1.0  # 最大加加速度 m/s^3
    min_jerk = -2.0  # 最小加加速度 m/s^3
    num_samples = 100  # 轨迹采样采样数量
    ref_v = 15.0  # m/s
    target_s = 150.0  # m
    # Obstacle param
    obstacle_enter_time = 0.1  # s
    obstacle_exit_time = 8.0  # s
    obstacle_length = 10  # m
    obstacle_speed = 20.0  # m/s
    obstacle_distance = 25  # m

    # safe bound
    overtake_safe_distance = 5.0  # m/s
    follow_safe_distance = 5.0  # m/s
    # Generate sample velocity profiles

    # creat a polygon object
    obstacle = Obstacle(obstacle_enter_time, obstacle_exit_time,
                        obstacle_length, obstacle_speed, obstacle_distance,
                        initial_velocity)
    obstacle.calculate_obstacle_coordinate_in_S_T_graph()

    obstacle.calculate_safe_bound(overtake_safe_distance, follow_safe_distance)
    safe_bound = obstacle.safe_bound

    # 创建一个Polygon对象
    parallelogram = Polygon(obstacle.obstacle_coordinate_in_S_T_graph,
                            closed=True,
                            edgecolor='none',
                            facecolor='red')

    # Create a simple lattice planner with sampled data
    planner = LatticePlanner(initial_velocity, max_velocity, min_velocity,
                             max_acceleration, max_deceleration, max_jerk,
                             min_jerk, num_samples)
    planner.sample()
    planner.generate_candidate_trajectories(ref_v)

    ## select best trajectory in candidate trajectory
    speed_decider = SpeedDecider(max_velocity, min_velocity, max_acceleration,
                                 max_deceleration, ref_v, target_s)
    ## filter no collision trajectory
    no_collision_trajectory = speed_decider.collision_checker(
        obstacle, planner.trajectories)
    ## behivour decider
    behivour_decide_trajectory = speed_decider.behivour_decider(
        obstacle, no_collision_trajectory)
    ## use cost function to evaluate the trajectory
    best_cost, best_trajectory_id = speed_decider.candidate_trajectories_evaluator(
        behivour_decide_trajectory)
    print("best_cost: {} best trajectory id: {}".format(
        best_cost, best_trajectory_id))

    ##########################################################
    # Visualize the trajectories on an S-T graph
    # plot all candidate trajectory
    plt.figure(figsize=(20, 15))
    plt.subplot(2, 2, 1)
    for trajectory in planner.trajectories:
        plt.plot(trajectory.t, trajectory.s)
        #label=f'Candidate Trajectory {trajectory.id}'
    plt.plot(planner.trajectories[best_trajectory_id].t,
             planner.trajectories[best_trajectory_id].s,
             marker='o',
             markerfacecolor='royalblue',
             markeredgecolor='royalblue')
    # plot a polygon
    # plt.gca().add_patch(parallelogram)

    # plot obstacle coordinate in S-T graph
    plt.plot([
        obstacle.obstacle_coordinate_in_S_T_graph[0][0],
        obstacle.obstacle_coordinate_in_S_T_graph[3][0]
    ], [
        obstacle.obstacle_coordinate_in_S_T_graph[0][1],
        obstacle.obstacle_coordinate_in_S_T_graph[3][1]
    ], 'r')
    plt.plot([
        obstacle.obstacle_coordinate_in_S_T_graph[1][0],
        obstacle.obstacle_coordinate_in_S_T_graph[2][0]
    ], [
        obstacle.obstacle_coordinate_in_S_T_graph[1][1],
        obstacle.obstacle_coordinate_in_S_T_graph[2][1]
    ], 'r')
    plt.plot([
        obstacle.obstacle_coordinate_in_S_T_graph[0][0],
        obstacle.obstacle_coordinate_in_S_T_graph[1][0]
    ], [
        obstacle.obstacle_coordinate_in_S_T_graph[0][1],
        obstacle.obstacle_coordinate_in_S_T_graph[1][1]
    ], 'r')
    plt.plot([
        obstacle.obstacle_coordinate_in_S_T_graph[3][0],
        obstacle.obstacle_coordinate_in_S_T_graph[2][0]
    ], [
        obstacle.obstacle_coordinate_in_S_T_graph[3][1],
        obstacle.obstacle_coordinate_in_S_T_graph[2][1]
    ], 'r')

    plt.plot(obstacle.safe_bound[0][0], obstacle.safe_bound[0][1], 'b--')
    plt.plot(obstacle.safe_bound[1][0], obstacle.safe_bound[1][1], 'b--')

    plt.xlabel('Time (t)')
    plt.ylabel('Space (m)')
    plt.title('S-T Graph of Candidate Trajectories')
    plt.legend()
    plt.grid()

    plt.subplot(2, 2, 2)
    for trajectory in planner.trajectories:
        plt.plot(trajectory.t,
                 trajectory.v,
                 label=f'Trajectory {trajectory.id}')
    plt.plot(planner.trajectories[best_trajectory_id].t,
             planner.trajectories[best_trajectory_id].v,
             marker='o',
             markerfacecolor='royalblue',
             markeredgecolor='royalblue')
    plt.ylabel('Velocity (m/s)')
    plt.xlabel('Time (t)')
    plt.title('V-T Graph of Lattice Planner Trajectories')
    plt.grid()

    plt.subplot(2, 2, 3)
    for trajectory in planner.trajectories:
        plt.plot(trajectory.t,
                 trajectory.a,
                 label=f'Trajectory {trajectory.id}')
    plt.plot(planner.trajectories[best_trajectory_id].t,
             planner.trajectories[best_trajectory_id].a,
             marker='o',
             markerfacecolor='royalblue',
             markeredgecolor='royalblue')
    plt.ylabel('Acceleration (m/s^2)')
    plt.xlabel('Time (t)')
    plt.title('A-T Graph of Lattice Planner Trajectories')
    plt.grid()

    plt.subplot(2, 2, 4)
    for trajectory in planner.trajectories:
        plt.plot(trajectory.t,
                 trajectory.jerk,
                 label=f'Trajectory {trajectory.id}')
    plt.plot(planner.trajectories[best_trajectory_id].t,
             planner.trajectories[best_trajectory_id].jerk,
             marker='o',
             markerfacecolor='royalblue',
             markeredgecolor='royalblue')
    plt.ylabel('Jerk (m/s^3)')
    plt.xlabel('Time (t)')
    plt.title('J-T Graph of Lattice Planner Trajectories')
    plt.grid()

    ######################################################
    # plot no collision trajectory
    for trajectory in no_collision_trajectory:
        if trajectory.id is best_trajectory_id:
            no_collision_best_trajectory = trajectory

    plt.figure(figsize=(20, 15))
    plt.subplot(2, 2, 1)
    for trajectory in no_collision_trajectory:
        plt.plot(trajectory.t,
                 trajectory.s,
                 label=f'No Collision Trajectory {trajectory.id}')
    plt.plot(no_collision_best_trajectory.t,
             no_collision_best_trajectory.s,
             marker='o',
             markerfacecolor='royalblue',
             markeredgecolor='royalblue')

    # plot obstacle coordinate in S-T graph
    plt.plot([
        obstacle.obstacle_coordinate_in_S_T_graph[0][0],
        obstacle.obstacle_coordinate_in_S_T_graph[3][0]
    ], [
        obstacle.obstacle_coordinate_in_S_T_graph[0][1],
        obstacle.obstacle_coordinate_in_S_T_graph[3][1]
    ], 'r')
    plt.plot([
        obstacle.obstacle_coordinate_in_S_T_graph[1][0],
        obstacle.obstacle_coordinate_in_S_T_graph[2][0]
    ], [
        obstacle.obstacle_coordinate_in_S_T_graph[1][1],
        obstacle.obstacle_coordinate_in_S_T_graph[2][1]
    ], 'r')
    plt.plot([
        obstacle.obstacle_coordinate_in_S_T_graph[0][0],
        obstacle.obstacle_coordinate_in_S_T_graph[1][0]
    ], [
        obstacle.obstacle_coordinate_in_S_T_graph[0][1],
        obstacle.obstacle_coordinate_in_S_T_graph[1][1]
    ], 'r')
    plt.plot([
        obstacle.obstacle_coordinate_in_S_T_graph[3][0],
        obstacle.obstacle_coordinate_in_S_T_graph[2][0]
    ], [
        obstacle.obstacle_coordinate_in_S_T_graph[3][1],
        obstacle.obstacle_coordinate_in_S_T_graph[2][1]
    ], 'r')

    # plot safe bound of obstacle in S-T graph
    plt.plot(obstacle.safe_bound[0][0], obstacle.safe_bound[0][1], 'b--')
    plt.plot(obstacle.safe_bound[1][0], obstacle.safe_bound[1][1], 'b--')

    plt.xlabel('Time (t)')
    plt.ylabel('Space (m)')
    plt.title('S-T Graph No Collision Trajectories')
    # plt.legend()
    plt.grid()

    plt.subplot(2, 2, 2)
    for trajectory in no_collision_trajectory:
        plt.plot(trajectory.t,
                 trajectory.v,
                 label=f'Trajectory {trajectory.id}')
    plt.plot(no_collision_best_trajectory.t,
             no_collision_best_trajectory.v,
             marker='o',
             markerfacecolor='royalblue',
             markeredgecolor='royalblue')
    plt.ylabel('Velocity (m/s)')
    plt.xlabel('Time (t)')
    plt.title('V-T Graph of Lattice Planner Trajectories')
    plt.grid()

    plt.subplot(2, 2, 3)
    for trajectory in no_collision_trajectory:
        plt.plot(trajectory.t,
                 trajectory.a,
                 label=f'Trajectory {trajectory.id}')
    plt.plot(no_collision_best_trajectory.t,
             no_collision_best_trajectory.a,
             marker='o',
             markerfacecolor='royalblue',
             markeredgecolor='royalblue')

    plt.ylabel('Acceleration (m/s^2)')
    plt.xlabel('Time (t)')
    plt.title('A-T Graph of Lattice Planner Trajectories')
    plt.grid()

    plt.subplot(2, 2, 4)
    for trajectory in no_collision_trajectory:
        plt.plot(trajectory.t,
                 trajectory.jerk,
                 label=f'Trajectory {trajectory.id}')
    plt.plot(no_collision_best_trajectory.t,
             no_collision_best_trajectory.jerk,
             marker='o',
             markerfacecolor='royalblue',
             markeredgecolor='royalblue')
    plt.ylabel('Jerk (m/s^3)')
    plt.xlabel('Time (t)')
    plt.title('J-T Graph of Lattice Planner Trajectories')
    plt.grid()

    plt.show()
    # Smooth the trajectories using cubic spline interpolation
    #planner.smooth_trajectories()
