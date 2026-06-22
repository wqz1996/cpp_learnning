from pickle import FALSE
import numpy as np
import do_mpc
from casadi import vertcat
# Extracting the data for plotting
from matplotlib import pyplot as plt
from do_mpc.graphics import Graphics

## X = [x_dot,y_dot,phi_dot,e_phi,e_y,s,l]^T
## u = [delta, ax]
# Define the model parameters (as per the values given)
m = 35000.  # mass (kg)
Iz = 39000.  # moment of inertia about z-axis (kg*m^2)
Cf = 75000.  # cornering stiffness of the front tires (N/rad)
Cr = 107200.  # cornering stiffness of the rear tires (N/rad)
lf = 1.64  # distance from CG to front axle (m)
lr = 3.9 - lf  # distance from CG to rear axle (m)
sample_time = 0.05  # sampling time
kappa = 0.0
# Define the model
model_type = 'continuous'  # or 'discrete'
model = do_mpc.model.Model(model_type)

# Define the state and input variables
x_dot = model.set_variable(var_type='_x', var_name='x_dot', shape=(1, 1))
y_dot = model.set_variable(var_type='_x', var_name='y_dot', shape=(1, 1))
phi_dot = model.set_variable(var_type='_x', var_name='phi_dot', shape=(1, 1))
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
    lf**2. * Cf + lr**2. * Cr) / (Iz *
                                  x_dot) * phi_dot + 2. * lf * Cf / Iz * delta
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

r_x_dot = 1.0
r_e_phi = 0.1
r_e_y = 0.5
# Define the objective function
mpc.set_objective(mterm=0.0 * (e_phi**2 + e_y**2),
                  lterm=r_x_dot * (ref_x_dot - x_dot)**2 + r_e_phi * e_phi**2 +
                  r_e_y * e_y**2)

r_delta = 0.1
r_ax = 0.1
mpc.set_rterm(delta=r_delta, a_x=r_ax)  # Input penalty

# Define the constraints
mpc.bounds['lower', '_u', 'delta'] = -np.pi / 6
mpc.bounds['upper', '_u', 'delta'] = np.pi / 6
mpc.bounds['lower', '_u', 'a_x'] = -3.0
mpc.bounds['upper', '_u', 'a_x'] = 2.0

mpc.setup()

# Create an estimator:
estimator = do_mpc.estimator.StateFeedback(model)

# Create a simulator
simulator = do_mpc.simulator.Simulator(model)
simulator.set_param(t_step=sample_time)
simulator.setup()

# Set initial state
## x = [x_dot,y_dot,phi_dot,e_phi,e_y,s,l]^T
## u = [delta, ax]
x0 = np.array([20.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0]).reshape(-1, 1)
mpc.x0 = x0
simulator.x0 = x0
estimator.x0 = x0

mpc.set_initial_guess()

# Run MPC main loop:
for k in range(100):
    u0 = mpc.make_step(x0)
    y_next = simulator.make_step(u0)
    x0 = estimator.make_step(y_next)

# sim_graphics = Graphics(simulator.data)

fig, ax = plt.subplots(4, 2, sharex=True, figsize=(20, 12))
ax = ax.flatten()  # 将2D数组的子图对象转换为1D数组，以便于迭代

mpc_graphics = Graphics(mpc.data)
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