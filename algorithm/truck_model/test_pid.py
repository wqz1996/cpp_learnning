from os import path
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
from matplotlib.animation import FuncAnimation

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


def body_to_frenet_coordinates(vehicle_x, vehicle_y, vehicle_heading,
                               path_start_x, path_start_y, path_heading):
    # Calculate the heading difference between the vehicle and the path
    heading_difference = vehicle_heading - path_heading

    # Calculate the position of the vehicle in path-relative coordinates
    dx = vehicle_x - path_start_x
    dy = vehicle_y - path_start_y
    rotated_dx = dx * np.cos(-path_heading) - dy * np.sin(-path_heading)
    rotated_dy = dx * np.sin(-path_heading) + dy * np.cos(-path_heading)

    # The s-coordinate is the projection of the vehicle's position onto the path direction
    s = rotated_dx

    # The l-coordinate is the lateral displacement from the path, which is simply the rotated y-coordinate
    l = rotated_dy

    # Heading error is the negative of the heading difference
    e_psi = -heading_difference

    # Lateral error is the l-coordinate
    e_y = l

    return s, l, e_psi, e_y


def body_to_cartesian(x_dot, y_dot, psi):
    """
    Convert velocity from the vehicle body frame to the world frame.

    Args:
    x_dot (float): Velocity along the vehicle's x-axis (forward).
    y_dot (float): Velocity along the vehicle's y-axis (lateral).
    psi (float): Vehicle's yaw angle in the world frame (radians).

    Returns:
    (float, float): The velocity components in the world frame (X_dot, Y_dot).
    """
    X_dot = x_dot * np.cos(psi) - y_dot * np.sin(psi)
    Y_dot = x_dot * np.sin(psi) + y_dot * np.cos(psi)
    return X_dot, Y_dot


def frenet_to_cartesian(s, l, lane_heading):
    """
    Transform from Frenet coordinates to Cartesian coordinates.
    
    Args:
    s (float): Arc-length along the lane.
    l (float): Lateral offset from the lane centerline.
    lane_heading (float): Heading angle of the lane (in radians).
    
    Returns:
    (float, float): The Cartesian coordinates (X, Y).
    """
    # Calculate the position on the centerline
    X_C = s * np.cos(lane_heading)
    Y_C = s * np.sin(lane_heading)

    # Calculate the normal vector components
    N_x = -np.sin(lane_heading)
    N_y = np.cos(lane_heading)

    # Calculate the Cartesian coordinates
    X_P = X_C + l * N_x
    Y_P = Y_C + l * N_y

    return X_P, Y_P


class PID:

    def __init__(self, kp, ki, kd, dt):
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.dt = dt
        self.integral = 0.0
        self.last_error = 0.0

    def ComputeCommand(self, ref, output):
        err = ref - output
        p = self.kp * err
        self.integral = self.integral + err * self.dt
        i = self.ki * self.integral

        d = self.kd * (self.last_error - err) / self.dt
        self.last_error = err
        return p + i + d


# class PathGenerator:
#     def __init__(self):

#     def generate(self):
#         return path


class TruckModel:
    ## X = [x_dot,y_dot,phi_dot,e_phi,e_y,s,l]^T
    ## u = [delta, ax]
    def __init__(self, kStateNum, kControlNum, sample_time):
        self.A = np.mat(np.zeros((kStateNum, kStateNum)))
        self.B = np.mat(np.zeros((kStateNum, kControlNum)))
        self.X = np.mat(np.zeros((kStateNum, 1)))
        self.U = np.mat(np.zeros((kControlNum, 1)))
        self.Ad = np.mat(np.zeros((kStateNum, kStateNum)))
        self.Bd = np.mat(np.zeros((kStateNum, kControlNum)))
        self.kappa = 0.
        self.m = 35000.  # mass (kg)
        self.Iz = 39000.  # moment of inertia about z-axis (kg*m^2)
        self.Cf = 75000.  # cornering stiffness of the front tires (N/rad)
        self.Cr = 107200.  # cornering stiffness of the rear tires (N/rad)
        self.lf = 1.64  # distance from CG to front axle (m)
        self.lr = 3.9 - self.lf  # distance from CG to rear axle (m)
        self.sample_time = sample_time

    def UpdateStateMatrix(self, x_dot, kappa):
        m = self.m
        Iz = self.Iz
        Cf = self.Cf
        Cr = self.Cr
        lf = self.lf
        lr = self.lr
        # self.A = [[0., 0., 0., 0., 0., 0.],
        #           [0., -2. * (Cf + Cr) / (m * x_dot),-2. * (lf * Cf - lr * Cr) / (m * x_dot), 0., 0., 0.],
        #           [0., -2. * (lf * Cf - lr * Cr) / (Iz * x_dot), -2. * (lf**2. * Cf + lr**2. * Cr) / (Iz * x_dot), 0., 0., 0.],
        #           [-kappa, 0., 1., 0., 0., 0.],
        #           [0., 1., 0., x_dot, 0., 0.],
        #           [1., 0., 0., 0., 0., 0.],
        #           [0., 1., 0., 0., 0., 0.] ]
        self.A[1, 1] = -2. * (Cf + Cr) / (m * x_dot)
        self.A[1, 2] = -2. * (lf * Cf - lr * Cr) / (m * x_dot)
        self.A[2, 1] = -2. * (lf * Cf - lr * Cr) / (Iz * x_dot)
        self.A[2, 2] = -2. * (lf**2. * Cf + lr**2. * Cr) / (Iz * x_dot)
        self.A[3, 0] = -kappa
        self.A[3, 2] = 1.0
        self.A[4, 1] = 1.0
        self.A[4, 3] = x_dot
        self.A[5, 0] = 1.0
        self.A[6, 1] = 1.0

        print("A", self.A)
        A_num = (np.eye(kStateNum) + self.A * self.sample_time * 0.5)
        print("A_num", A_num)

        A_den = np.linalg.inv(
            np.eye(kStateNum) - self.A * self.sample_time * 0.5)
        print("A_den", A_den)

        self.Ad = A_den * A_num
        print("Ad", self.Ad)

    def UpdateInputMatrix(self):
        m = self.m
        Iz = self.Iz
        lf = self.lf
        Cf = self.Cf
        # self.B = np.mat([[0., 1.],
        #                  [2. * Cf / m, 0.],
        #                  [2. * lf * Cf / Iz, 0.],
        #                  [0., 0.],
        #                  [0., 0.],
        #                  [0., 0.]])
        self.B[0, 1] = 1.0
        self.B[1, 0] = 2. * Cf / m
        self.B[2, 0] = 2. * lf * Cf / Iz
        print("B", self.B)
        self.Bd = np.linalg.inv(
            np.eye(kStateNum) -
            0.5 * self.A * self.sample_time) * self.B * self.sample_time
        print("Bd", self.Bd)

    def SetInitState(self, init_x_dot, init_y_dot, init_phi_dot, init_e_phi,
                     init_e_y, init_s, init_l, init_delta, init_ax):
        self.X = np.mat([
            init_x_dot, init_y_dot, init_phi_dot, init_e_phi, init_e_y, init_s,
            init_l
        ]).T
        self.U = np.mat([[init_delta], [init_ax]])

    def UpdateState(self, U):
        self.U = U
        self.X = self.Ad * self.X + self.Bd * self.U


if __name__ == "__main__":
    kStateNum = 7
    kControlNum = 2
    sample_time = 0.05
    total_time = 50.0
    steps = int(total_time / sample_time)
    truck_model = TruckModel(kStateNum=kStateNum,
                             kControlNum=kControlNum,
                             sample_time=sample_time)

    init_x = 0.0
    init_y = 0.0
    init_X = 0.0
    init_Y = 0.0
    init_phi = 0.0
    init_x_dot = 20.
    init_y_dot = 0.
    init_phi_dot = 0.
    init_e_phi = 0.
    init_e_y = 0.
    init_s = 0.
    init_l = 0.2
    init_delta = 0.
    init_ax = 0.

    ## 生成横向指令曲线
    t = np.linspace(0.0, total_time, steps)
    frequency = 0.1
    amplitude = 5. / 57.3
    phase_bias = 0.0
    amplitude_bias = 0.0
    delta_signal = amplitude * np.sin(2 * np.pi * frequency * t +
                                      phase_bias) + amplitude_bias

    truck_model.SetInitState(init_x_dot=init_x_dot,
                             init_y_dot=init_y_dot,
                             init_phi_dot=init_phi_dot,
                             init_e_phi=init_e_phi,
                             init_e_y=init_e_y,
                             init_s=init_s,
                             init_l=init_l,
                             init_delta=init_delta,
                             init_ax=init_ax)

    state_x = []
    state_y = []
    state_X = []
    state_Y = []
    state_phi = []
    state_x_dot = []
    state_y_dot = []
    state_phi_dot = []
    state_e_phi = []
    state_e_y = []
    state_s = []
    state_l = []

    a_cmd = []
    y_cmd = []
    phi_cmd = []
    delta_cmd = []

    ref_x_dot = 22.0
    real_x_dot = 20.0

    ref_l = 0.0
    real_l = 0.0

    kappa = 0.0

    lon_kp = 1.0
    lon_ki = 0.0
    lon_kd = 0.0
    lon_controller = PID(lon_kp, lon_ki, lon_kd, sample_time)

    lat_y_kp = 0.5
    lat_y_ki = 0.0
    lat_y_kd = 0.0
    lat_y_controller = PID(lat_y_kp, lat_y_ki, lat_y_kd, sample_time)

    current_phi = init_phi
    current_x = init_x
    current_y = init_y
    current_X = init_X
    current_Y = init_Y

    for i in range(steps):
        lon_control_input = lon_controller.ComputeCommand(
            ref_x_dot, real_x_dot)
        a_cmd.append(lon_control_input)
        lat_control_y_input = lat_y_controller.ComputeCommand(ref_l, real_l)
        U = np.mat([[lat_control_y_input], [lon_control_input]])
        truck_model.UpdateStateMatrix(x_dot=real_x_dot, kappa=kappa)
        truck_model.UpdateInputMatrix()
        truck_model.UpdateState(U)
        real_x_dot = truck_model.X[0].item()
        real_y_dot = truck_model.X[1].item()
        real_phi_dot = truck_model.X[2].item()
        real_l = truck_model.X[6].item()
        current_x += real_x_dot * sample_time
        current_y += real_y_dot * sample_time
        current_phi += real_phi_dot * sample_time
        current_X_dot, current_Y_dot = body_to_cartesian(
            real_x_dot, real_y_dot, current_phi)

        current_X += current_X_dot * sample_time
        current_Y += current_Y_dot * sample_time

        state_x.append(current_x)
        state_y.append(current_y)
        state_X.append(current_X)
        state_Y.append(current_Y)
        state_phi.append(current_phi)
        state_x_dot.append(truck_model.X[0].item())
        state_y_dot.append(truck_model.X[1].item())
        state_phi_dot.append(truck_model.X[2].item())
        state_e_phi.append(truck_model.X[3].item())
        state_e_y.append(truck_model.X[4].item())
        state_s.append(truck_model.X[5].item())
        state_l.append(truck_model.X[6].item())

    # print("x_dot", state_x_dot)
    fig, ax = plt.subplots()
    line, = ax.plot([], [], 'o-', lw=2)
    trajectory, = ax.plot([], [], '-', lw=1, color='blue')
    ax.set_xlim(-60, 60)
    ax.set_ylim(-60, 60)

    def init():
        line.set_data([init_x], [init_y])
        trajectory.set_data([init_x], [init_y])
        return line, trajectory

    def animate(i):
        line.set_data(state_X[i], state_Y[i])
        trajectory.set_data(state_X[:i + 1], state_Y[:i + 1])
        return line, trajectory

    ani = FuncAnimation(fig,
                        animate,
                        frames=len(state_x),
                        init_func=init,
                        blit=True,
                        repeat=False)

    ## set figure config
    if 'fontsize' in FIG_CONFIG:
        matplotlib.rcParams.update({'font.size': FIG_CONFIG['fontsize']})
    if 'figsize' in FIG_CONFIG and 'dpi' in FIG_CONFIG:
        fig = plt.figure(num=0,
                         figsize=FIG_CONFIG['figsize'],
                         dpi=FIG_CONFIG['dpi'])
    fig.canvas.set_window_title('test')

    plt.subplot(3, 2, 1)
    plt.plot(t, state_x_dot, label='x_dot')
    plt.legend()
    plt.grid()

    plt.subplot(3, 2, 2)
    plt.plot(t, state_phi, label='state_phi')
    plt.legend()
    plt.grid()

    plt.subplot(3, 2, 3)
    plt.plot(t, state_y_dot, label='y_dot')
    plt.plot(t, state_phi_dot, label='phi_dot')
    # plt.plot(t, delta_signal, label='delta_signal')
    plt.legend()
    plt.grid()

    plt.subplot(3, 2, 4)
    plt.plot(t, state_e_phi, label='e_phi')
    plt.plot(t, state_e_y, label='e_y')
    plt.legend()
    plt.grid()

    plt.subplot(3, 2, 5)
    plt.plot(state_X, state_Y, label='X_Y')
    plt.legend()
    plt.grid()

    plt.subplot(3, 2, 6)
    plt.plot(state_x, state_y, label='x_y')
    plt.legend()
    plt.grid()

    plt.show()
    # print(state)
