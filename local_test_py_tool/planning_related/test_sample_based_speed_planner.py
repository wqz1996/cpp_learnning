import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d


class LatticePlanner:

    def __init__(self, initial_velocity, max_velocity, min_velocity,
                 max_acceleration, max_deceleration, planning_duration,
                 num_samples):
        self.initial_velocity = initial_velocity
        self.max_acceleration = max_acceleration
        self.max_deceleration = max_deceleration
        self.planning_duration = planning_duration
        self.num_samples = num_samples
        self.min_velocity = min_velocity
        self.max_velocity = max_velocity
        self.trajectories = []
        self.time_samples = []
        self.velocity_samples = []
        self.acceleration_samples = []

    def sample(self):
        self.time_samples = np.linspace(0, self.planning_duration,
                                        self.num_samples)
        self.velocity_samples = np.linspace(self.min_velocity,
                                            self.max_velocity,
                                            self.num_samples)
        self.acceleration_samples = np.linspace(self.max_deceleration,
                                                self.max_acceleration,
                                                self.num_samples)

    def generate_trajectories(self, ref_v):
        for i in range(self.num_samples):
            s = 0
            t = 0
            v = self.initial_velocity
            a = 0

            s_data = []
            v_data = []
            a_data = []
            t_data = []

            for j in range(len(self.time_samples)):

                # a = self.acceleration_samples[
                #     i] if v < self.velocity_samples[i] else max_deceleration
                a = self.acceleration_samples[i]
                
                a_data.append(a)
                v = max(min(v + a * (self.time_samples[j] - t), max_velocity),
                        min_velocity)
                v_data.append(v)
                s += v * (self.time_samples[j] - t)
                s_data.append(s)
                t = self.time_samples[j]
                t_data.append(t)

            self.trajectories.append(
                Trajectory(i, s_data, v_data, a_data, t_data))

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


class Trajectory:

    def __init__(self, trajectory_id, s, v, a, t):
        self.id = trajectory_id
        self.s = s
        self.v = v
        self.a = a
        self.t = t

    def smooth(self, s_smooth, t_smooth):
        self.s = s_smooth
        self.t = t_smooth


if __name__ == "__main__":
    # Parameters
    initial_velocity = 5.0  # 初始速度 m/s
    max_acceleration = 2.0  # 最大加速度 m/s^2
    max_deceleration = -3.0  # 最大减速度 m/s^2
    max_velocity = 27.0  # 最大速度 m/s
    min_velocity = 0.0  # 最小速度 m/s
    planning_duration = 10.0  # 规划时长 s
    num_samples = 30  # 采样数量
    ref_v = 15.0
    # Generate sample velocity profiles

    # Create a simple lattice planner with sampled data
    planner = LatticePlanner(initial_velocity, max_velocity, min_velocity,
                             max_acceleration, max_deceleration,
                             planning_duration, num_samples)
    planner.sample()
    planner.generate_trajectories(ref_v)
    # Visualize the trajectories on an S-T graph
    plt.figure(figsize=(10, 6))
    for trajectory in planner.trajectories:
        plt.plot(trajectory.t,
                 trajectory.s,
                 label=f'Trajectory {trajectory.id}')
    # plt.figure(figsize=(10, 6))
    # planner.smooth_trajectories()
    # for trajectory in planner.trajectories:
    #     plt.plot(trajectory.t,
    #              trajectory.s,
    #              label=f'Trajectory {trajectory.id}',
    #              linestyle='--')

    plt.xlabel('Space (m)')
    plt.ylabel('Time (t)')
    plt.title('S-T Graph of Lattice Planner Trajectories')
    #plt.legend()
    plt.grid()
    plt.figure(figsize=(10, 6))
    for trajectory in planner.trajectories:
        plt.plot(trajectory.t,
                 trajectory.v,
                 label=f'Trajectory {trajectory.id}')
    plt.xlabel('Velocity (m/s)')
    plt.ylabel('Time (t)')
    plt.title('V-T Graph of Lattice Planner Trajectories')
    plt.grid()

    plt.figure(figsize=(10, 6))
    for trajectory in planner.trajectories:
        plt.plot(trajectory.t,
                 trajectory.a,
                 label=f'Trajectory {trajectory.id}')
    plt.xlabel('Acceleration (m/s^2)')
    plt.ylabel('Time (t)')
    plt.title('A-T Graph of Lattice Planner Trajectories')
    plt.grid()

    plt.show()
    # Smooth the trajectories using cubic spline interpolation
    #planner.smooth_trajectories()
