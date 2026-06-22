from pickle import FALSE
import numpy as np
import do_mpc
from casadi import vertcat
# Extracting the data for plotting
from matplotlib import pyplot as plt
from do_mpc.graphics import Graphics

sample_time = 0.05  # sampling time


def TruckModel():
    ## X = [x_dot,y_dot,phi_dot,e_phi,e_y,s,l]^T
    ## u = [delta, ax]
    # Define the model parameters (as per the values given)
    m = 35000.  # mass (kg)
    Iz = 39000.  # moment of inertia about z-axis (kg*m^2)
    Cf = 75000.  # cornering stiffness of the front tires (N/rad)
    Cr = 107200.  # cornering stiffness of the rear tires (N/rad)
    lf = 1.64  # distance from CG to front axle (m)
    lr = 3.9 - lf  # distance from CG to rear axle (m)

    kappa = 0.0
    # Define the model
    model_type = 'continuous'  # or 'discrete'
    model = do_mpc.model.Model(model_type)

    # Define the state and input variables
    x_dot = model.set_variable(var_type='_x', var_name='x_dot', shape=(1, 1))
    y_dot = model.set_variable(var_type='_x', var_name='y_dot', shape=(1, 1))
    phi_dot = model.set_variable(var_type='_x',
                                 var_name='phi_dot',
                                 shape=(1, 1))
    e_phi = model.set_variable(var_type='_x', var_name='e_phi', shape=(1, 1))
    e_y = model.set_variable(var_type='_x', var_name='e_y', shape=(1, 1))
    s = model.set_variable(var_type='_x', var_name='s', shape=(1, 1))
    l = model.set_variable(var_type='_x', var_name='l', shape=(1, 1))

    delta = model.set_variable(var_type='_u', var_name='delta', shape=(1, 1))
    a_x = model.set_variable(var_type='_u', var_name='a_x', shape=(1, 1))

    # Define the continuous-time model dynamics
    # From the given state space representation

    dx_dot_next = a_x
    dy_dot_next = -2.0 * (Cf + Cr) / (m * x_dot) * y_dot - 2.0 * (
        lf * Cf - lr * Cr) / (m * x_dot) * phi_dot + 2. * Cf / m * delta
    dphi_dot_next = -2. * (lf * Cf - lr * Cr) / (Iz * x_dot) * y_dot - 2. * (
        lf**2. * Cf +
        lr**2. * Cr) / (Iz * x_dot) * phi_dot + 2. * lf * Cf / Iz * delta
    de_phi_next = -kappa * x_dot + phi_dot
    de_y_next = y_dot + x_dot * e_phi
    ds_next = x_dot
    dl_next = y_dot

    model.set_rhs('x_dot', dx_dot_next)
    model.set_rhs('y_dot', dy_dot_next)
    model.set_rhs('phi_dot', dphi_dot_next)
    model.set_rhs('e_phi', de_phi_next)
    model.set_rhs('e_y', de_y_next)
    model.set_rhs('s', ds_next)
    model.set_rhs('l', dl_next)

    # Setup model
    model.setup()

    return model


def TruckModelMpcUsed():
    ## X = [x_dot,y_dot,phi_dot,e_phi,e_y,s,l]^T
    ## u = [delta, ax]
    # Define the model parameters (as per the values given)
    m = 35000.  # mass (kg)
    Iz = 39000.  # moment of inertia about z-axis (kg*m^2)
    Cf = 75000.  # cornering stiffness of the front tires (N/rad)
    Cr = 107200.  # cornering stiffness of the rear tires (N/rad)
    lf = 1.64  # distance from CG to front axle (m)
    lr = 3.9 - lf  # distance from CG to rear axle (m)

    kappa = 0.0
    # Define the model
    model_type = 'continuous'  # or 'discrete'
    model = do_mpc.model.Model(model_type)

    # Define the state and input variables
    x_dot = model.set_variable(var_type='_x', var_name='x_dot', shape=(1, 1))
    y_dot = model.set_variable(var_type='_x', var_name='y_dot', shape=(1, 1))
    phi_dot = model.set_variable(var_type='_x',
                                 var_name='phi_dot',
                                 shape=(1, 1))
    e_phi = model.set_variable(var_type='_x', var_name='e_phi', shape=(1, 1))
    e_y = model.set_variable(var_type='_x', var_name='e_y', shape=(1, 1))
    s = model.set_variable(var_type='_x', var_name='s', shape=(1, 1))
    l = model.set_variable(var_type='_x', var_name='l', shape=(1, 1))

    delta = model.set_variable(var_type='_u', var_name='delta', shape=(1, 1))
    a_x = model.set_variable(var_type='_u', var_name='a_x', shape=(1, 1))

    # Define the continuous-time model dynamics
    # From the given state space representation

    dx_dot_next = a_x
    dy_dot_next = -2.0 * (Cf + Cr) / (m * x_dot) * y_dot - 2.0 * (
        lf * Cf - lr * Cr) / (m * x_dot) * phi_dot + 2. * Cf / m * delta
    dphi_dot_next = -2. * (lf * Cf - lr * Cr) / (Iz * x_dot) * y_dot - 2. * (
        lf**2. * Cf +
        lr**2. * Cr) / (Iz * x_dot) * phi_dot + 2. * lf * Cf / Iz * delta
    de_phi_next = -kappa * x_dot + phi_dot
    de_y_next = y_dot + x_dot * e_phi
    ds_next = x_dot
    dl_next = y_dot

    model.set_rhs('x_dot', dx_dot_next)
    model.set_rhs('y_dot', dy_dot_next)
    model.set_rhs('phi_dot', dphi_dot_next)
    model.set_rhs('e_phi', de_phi_next)
    model.set_rhs('e_y', de_y_next)
    model.set_rhs('s', ds_next)
    model.set_rhs('l', dl_next)

    # Setup model
    model.setup()

    return model


def mpc_setup(model):
    # Configure MPC controller
    mpc = do_mpc.controller.MPC(model)

    setup_mpc = {
        'n_horizon': 10,
        't_step': sample_time,
        'n_robust': 1,
        'store_full_solution': True,
    }
    mpc.set_param(**setup_mpc)

    ref_x_dot = 22.0

    q_x_dot = 0.1
    q_e_phi = 0.1
    q_e_y = 0.5
    # Define the objective function
    mpc.set_objective(mterm=0.0 * (model._x['e_phi']**2 + model._x['e_y']**2),
                      lterm=q_x_dot * (ref_x_dot - model._x['x_dot'])**2 +
                      q_e_phi * model._x['e_phi']**2 +
                      q_e_y * model._x['e_y']**2)

    r_delta = 0.1
    r_ax = 0.1
    mpc.set_rterm(delta=r_delta, a_x=r_ax)  # Input penalty

    # Define the constraints
    mpc.bounds['lower', '_u', 'delta'] = -np.pi / 6
    mpc.bounds['upper', '_u', 'delta'] = np.pi / 6
    mpc.bounds['lower', '_u', 'a_x'] = -3.0
    mpc.bounds['upper', '_u', 'a_x'] = 2.0

    mpc.setup()
    return mpc


model_mpc_used = TruckModelMpcUsed()

actual_model = TruckModel()

truck_mpc = mpc_setup(model_mpc_used)

# Create an estimator:
estimator = do_mpc.estimator.StateFeedback(model_mpc_used)

# Create a simulator
actual_simulator = do_mpc.simulator.Simulator(actual_model)
actual_simulator.set_param(t_step=sample_time)
actual_simulator.setup()

# Set initial state
## x = [x_dot,y_dot,phi_dot,e_phi,e_y,s,l]^T
## u = [delta, ax]
# 在初始状态中引入误差
x0_actual = np.array([20.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.1]).reshape(-1, 1)
x0_mpc = np.array([20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]).reshape(-1,
                                                                1)  # 引入初始误差

truck_mpc.x0 = x0_mpc
actual_simulator.x0 = x0_actual  # 使用实际状态作为模拟器的初始状态
estimator.x0 = x0_mpc  # 使用带误差的状态作为估计器的初始状态

truck_mpc.set_initial_guess()

num_steps = 100
actual_states = np.zeros((num_steps, 7))
mpc_states = np.zeros((num_steps, 7))

# Run MPC main loop:
for k in range(num_steps):
    # 记录实际状态
    actual_states[k, :] = x0_actual.flatten()

    # 记录MPC预测状态
    mpc_states[k, :] = x0_mpc.flatten()

    u0 = truck_mpc.make_step(x0_mpc)
    print("u0 {}".format(u0))
    y_next = actual_simulator.make_step(u0)
    x0_actual = estimator.make_step(y_next)
    x0_mpc = estimator.make_step(y_next)

# # 绘制实际状态和MPC预测状态
# fig, axs = plt.subplots(7, sharex=True, figsize=(20, 18))
# axs = axs.flatten()

# for i, state_name in enumerate(
#     ['x_dot', 'y_dot', 'phi_dot', 'e_phi', 'e_y', 's', 'l']):
#     axs[i].plot(actual_states[:, i],
#                 label='Actual ' + state_name,
#                 linestyle='--')
#     axs[i].plot(mpc_states[:, i], label='MPC Predicted ' + state_name)
#     axs[i].set_title(state_name)
#     axs[i].legend()

# axs[6].set_xlabel('Time Steps')

# plt.tight_layout()
# plt.show()

sim_graphics = Graphics(actual_simulator.data)

fig, ax = plt.subplots(4, 2, sharex=True, figsize=(20, 12))
ax = ax.flatten()  # 将2D数组的子图对象转换为1D数组，以便于迭代

mpc_graphics = Graphics(truck_mpc.data)
mpc_graphics.add_line(var_type='_x',
                      var_name='x_dot',
                      axis=ax[0],
                      label='x_dot')

mpc_graphics.add_line(var_type='_x',
                      var_name='y_dot',
                      axis=ax[1],
                      label='y_dot')

mpc_graphics.add_line(var_type='_x',
                      var_name='phi_dot',
                      axis=ax[1],
                      label='phi_dot')

mpc_graphics.add_line(var_type='_x',
                      var_name='e_phi',
                      axis=ax[3],
                      label='e_phi')

mpc_graphics.add_line(var_type='_x', var_name='e_y', axis=ax[3], label='e_y')

mpc_graphics.add_line(var_type='_x', var_name='s', axis=ax[2], label='s')

mpc_graphics.add_line(var_type='_x', var_name='l', axis=ax[4], label='l')

mpc_graphics.add_line(var_type='_u',
                      var_name='delta',
                      axis=ax[5],
                      label='delta')

mpc_graphics.add_line(var_type='_u', var_name='a_x', axis=ax[7], label='a_x')

mpc_graphics.plot_results()
mpc_graphics.plot_predictions()
mpc_graphics.reset_axes()

# 为每个子图添加图例
for a in ax:
    a.legend()
    a.grid()
plt.show()