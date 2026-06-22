import numpy as np
import matplotlib.pyplot as plt
import matplotlib
from matplotlib.animation import FuncAnimation
from casadi import SX, vertcat, DM
import do_mpc


def truck_model_setup():
    """
    Setup the truck model for MPC.
    """
    # Define the model
    model = do_mpc.model.Model('continuous')

    # Define the states and inputs
    x_dot = model.set_variable(var_type='_x', var_name='x_dot')
    y_dot = model.set_variable(var_type='_x', var_name='y_dot')
    phi_dot = model.set_variable(var_type='_x', var_name='phi_dot')
    e_phi = model.set_variable(var_type='_x', var_name='e_phi')
    e_y = model.set_variable(var_type='_x', var_name='e_y')
    s = model.set_variable(var_type='_x', var_name='s')
    l = model.set_variable(var_type='_x', var_name='l')

    delta = model.set_variable(var_type='_u', var_name='delta')
    ax = model.set_variable(var_type='_u', var_name='ax')

    # Parameters (constants)
    m = 35000.0  # mass (kg)
    Iz = 39000.0  # moment of inertia about z-axis (kg*m^2)
    Cf = 75000.0  # cornering stiffness of the front tires (N/rad)
    Cr = 107200.0  # cornering stiffness of the rear tires (N/rad)
    lf = 1.64  # distance from CG to front axle (m)
    lr = 3.9 - lf  # distance from CG to rear axle (m)
    kappa = 0.0

    # Model equations (simplified for demonstration purposes)
    # More complex dynamics should be used in practice
    dx_dot_next = ax
    dy_dot_next = -2.0 * (Cf + Cr) / (m * x_dot) * y_dot - 2.0 * (
        lf * Cf - lr * Cr) / (m * x_dot) * phi_dot + 2. * Cf / m * delta
    dphi_dot_next = -2. * (lf * Cf - lr * Cr) / (Iz * x_dot) * y_dot - 2. * (
        lf**2. * Cf +
        lr**2. * Cr) / (Iz * x_dot) * phi_dot + 2. * lf * Cf / Iz * delta
    de_phi_next = -kappa * x_dot + phi_dot
    de_y_next = y_dot + x_dot * e_phi
    ds_next = x_dot
    dl_next = y_dot

    # Set the differential equations
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
    """
    Setup MPC controller.
    """
    mpc = do_mpc.controller.MPC(model)

    setup_mpc = {
        'n_horizon': 10,
        't_step': 0.05,
        'n_robust': 0,
        'state_discretization': 'collocation',
        'collocation_type': 'radau',
        'collocation_deg': 2,
        'collocation_ni': 2,
        'store_full_solution': True,
    }

    mpc.set_param(**setup_mpc)

    q_x_dot = 0.1
    q_e_y = 0.1
    q_e_phi = 0.1
    # Define objective function
    # mterm = model.aux['x_dot']**2  # Terminal cost
    lterm = q_x_dot * model.aux['x_dot']**2 + q_e_y * model.aux[
        'e_y']**2 + q_e_phi * model.aux['e_phi']**2  # Stage cost
    mterm = 0.0
    # mpc.set_objective(mterm=mterm, lterm=lterm)
    mpc.set_objective(mterm=mterm, lterm=lterm)

    r_delta = 0.1
    r_ax = 0.1
    mpc.set_rterm(delta=r_delta, ax=r_ax)  # Input penalty

    # Define bounds and constraints
    # mpc.bounds['lower','_u','delta'] = -0.5
    # mpc.bounds['upper','_u','delta'] = 0.5
    # mpc.bounds['lower','_u','ax'] = -1.0
    # mpc.bounds['upper','_u','ax'] = 1.0

    # Setup MPC
    mpc.setup()

    return mpc


# Create model
model = truck_model_setup()

# Create MPC
mpc = mpc_setup(model)
