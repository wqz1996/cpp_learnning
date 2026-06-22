import numpy as np
import matplotlib.pyplot as plt


class FeasibleRegion:

    def VUpper(self, t):
        return 27.0  # Placeholder value

    def VLower(self, t):
        return 0.0  # Placeholder value


feasible_region = FeasibleRegion()  # Placeholder value
FLAGS = {
    'num_velocity_sample': 6,
    'trajectory_time_length': 8.0,
    'polynomial_minimal_param': 0.0,
    'min_velocity_sample_gap': 2.0
}  # Placeholder values


class State:

    def __init__(self, s, v, a):
        self.s = s
        self.v = v
        self.a = a


class Condition:

    def __init__(self, state, time):
        self.state = state
        self.time = time


class Curve1d:

    def __init__(self) -> None:
        pass

    def Evaluate(order, param):
        pass

    def Paramlenght():
        return 0

    def Tostring():
        pass


def sample_lon_end_conditions_for_cruising(ref_cruise_speed):
    assert FLAGS['num_velocity_sample'] > 1

    num_of_time_samples = 9
    time_samples = np.zeros(num_of_time_samples)
    for i in range(1, num_of_time_samples):
        ratio = i / (num_of_time_samples - 1)
        time_samples[i] = FLAGS['trajectory_time_length'] * ratio
    time_samples[0] = FLAGS['polynomial_minimal_param']

    end_s_conditions = []
    for time in time_samples:
        v_upper = min(feasible_region.VUpper(time), ref_cruise_speed)
        v_lower = feasible_region.VLower(time)

        lower_end_s = State(0.0, v_lower, 0.0)
        end_s_conditions.append(Condition(lower_end_s, time))

        upper_end_s = State(0.0, v_upper, 0.0)
        end_s_conditions.append(Condition(upper_end_s, time))

        v_range = v_upper - v_lower
        num_of_mid_points = min(
            FLAGS['num_velocity_sample'] - 2,
            int(v_range / FLAGS['min_velocity_sample_gap']))

        if num_of_mid_points > 0:
            velocity_seg = v_range / (num_of_mid_points + 1)
            for i in range(1, num_of_mid_points + 1):
                end_s = State(0.0, v_lower + velocity_seg * i, 0.0)
                #print("end_s.v: {}".format(v_lower + velocity_seg * i))
                end_s_conditions.append(Condition(end_s, time))

    return end_s_conditions


def GenerateSpeedProfilesForCruising(target_speed):
    print("target speed is: {}".format(target_speed))
    end_conditions = sample_lon_end_conditions_for_cruising(target_speed)


def main():
    ref_cruise_speed = 20.0  # Placeholder value

    end_conditions = sample_lon_end_conditions_for_cruising(ref_cruise_speed)

    times = [cond.time for cond in end_conditions]
    velocities = [cond.state.v for cond in end_conditions]

    plt.figure(figsize=(8, 6))
    # plt.plot(times[1:-1],
    #          smoothed_velocities,
    #          color='blue',
    #          label='Smoothed V-T Curve')
    plt.scatter(times, velocities, color='blue', label='End conditions')
    plt.xlabel('Time (s)')
    plt.ylabel('Velocity (m/s)')
    plt.title('V-T sample')
    plt.legend()
    plt.grid(True)
    plt.show()


if __name__ == "__main__":
    main()
