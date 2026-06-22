import numpy as np


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


# Example usage:
x_dot = 10.0  # Forward velocity in m/s
y_dot = 2.0  # Lateral velocity in m/s
psi = np.radians(30)  # Vehicle's yaw angle in degrees converted to radians

X_dot, Y_dot = body_to_cartesian(x_dot, y_dot, psi)
print(f"World frame velocity: X_dot = {X_dot}, Y_dot = {Y_dot}")
