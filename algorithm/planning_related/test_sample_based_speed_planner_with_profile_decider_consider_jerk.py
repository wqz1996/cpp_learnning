from cmath import inf, nan
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d


class LatticePlanner:

    def __init__(self, initial_velocity, max_velocity, min_velocity,
                 max_acceleration, max_deceleration, max_jerk, min_jerk,
                 planning_duration, num_samples, num_time_samples):
        self.initial_velocity = initial_velocity
        self.max_acceleration = max_acceleration
        self.max_deceleration = max_deceleration
        self.planning_duration = planning_duration
        self.num_samples = num_samples
        self.num_time_samples = num_time_samples
        self.min_velocity = min_velocity
        self.max_velocity = max_velocity
        self.max_jerk = max_jerk
        self.min_jerk = min_jerk
        self.trajectories = []
        self.time_samples = []
        self.velocity_samples = []
        self.acceleration_samples = []
        self.jerk_samples = []

    def sample(self):
        self.time_samples = np.linspace(0, self.planning_duration,
                                        self.num_time_samples)
        self.velocity_samples = np.linspace(self.min_velocity,
                                            self.max_velocity,
                                            self.num_samples)
        self.acceleration_samples = np.linspace(self.max_deceleration,
                                                self.max_acceleration,
                                                self.num_samples)
        self.jerk_samples = np.linspace(self.max_jerk, self.min_jerk,
                                        self.num_samples)

    def generate_trajectories(self, ref_v):
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

    def valid_checker(self, candidate_trajectory):
        for v in candidate_trajectory.v:
            if v > self.max_velocity:
                print("trajectory id: {} v over max velocity, speed is: {}".
                      format(candidate_trajectory.id, v))
                return False

    def candidate_trajectories_evaluator(self, candidate_trajectory):
        w_s = 100.0
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

            # # consider all cost
            # total_cost = cost_s + cost_v + cost_a + cost_jerk

            # do not consider s cost
            total_cost = cost_v + cost_a + cost_jerk

            if total_cost < best_cost:
                best_trajectory_id = trajectory.id
                best_cost = total_cost
        return best_cost, best_trajectory_id


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


if __name__ == "__main__":
    # Parameters
    initial_velocity = 10.0  # 初始速度 m/s
    max_acceleration = 2.0  # 最大加速度 m/s^2
    max_deceleration = -4.0  # 最大减速度 m/s^2
    max_velocity = 27.0  # 最大速度 m/s
    min_velocity = 0.0  # 最小速度 m/s
    max_jerk = 1.0  # 最大加加速度 m/s^3
    min_jerk = -2.0  # 最小加加速度 m/s^3
    planning_duration = 10.0  # 规划时长 s
    num_samples = 20  # 轨迹采样数量
    num_time_samples = 10  # 时间采样数量
    ref_v = 15.0
    target_s = 50
    # Generate sample velocity profiles

    # Create a simple lattice planner with sampled data
    planner = LatticePlanner(initial_velocity, max_velocity, min_velocity,
                             max_acceleration, max_deceleration, max_jerk,
                             min_jerk, planning_duration, num_samples,
                             num_time_samples)
    planner.sample()
    planner.generate_trajectories(ref_v)
    speed_decider = SpeedDecider(max_velocity, min_velocity, max_acceleration,
                                 max_deceleration, ref_v, target_s)
    best_cost, best_trajectory_id = speed_decider.candidate_trajectories_evaluator(
        planner.trajectories)
    print("best_cost: {} best trajectory id: {}".format(
        best_cost, best_trajectory_id))
    # Visualize the trajectories on an S-T graph
    plt.figure(figsize=(20, 15))
    plt.subplot(2, 2, 1)
    for trajectory in planner.trajectories:
        plt.plot(trajectory.t,
                 trajectory.s,
                 label=f'Trajectory {trajectory.id}')
    plt.plot(planner.trajectories[best_trajectory_id].t,
             planner.trajectories[best_trajectory_id].s,
             marker='o')
    # plt.figure(figsize=(10, 6))q
    # planner.smooth_trajectories()
    # for trajectory in planner.trajectories:
    #     plt.plot(trajectory.t,
    #              trajectory.s,
    #              label=f'Trajectory {trajectory.id}',
    #              linestyle='--')

    plt.xlabel('Time (t)')
    plt.ylabel('Space (m)')
    plt.title('S-T Graph of Lattice Planner Trajectories')
    #plt.legend()
    plt.grid()

    plt.subplot(2, 2, 2)
    for trajectory in planner.trajectories:
        plt.plot(trajectory.t,
                 trajectory.v,
                 label=f'Trajectory {trajectory.id}')
    plt.plot(planner.trajectories[best_trajectory_id].t,
             planner.trajectories[best_trajectory_id].v,
             marker='o')
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
             marker='o')
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
             marker='o')
    plt.ylabel('Jerk (m/s^3)')
    plt.xlabel('Time (t)')
    plt.title('J-T Graph of Lattice Planner Trajectories')
    plt.grid()

    plt.show()
    # Smooth the trajectories using cubic spline interpolation
    #planner.smooth_trajectories()
