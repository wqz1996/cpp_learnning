import numpy as np


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


# Example usage for a lane with a heading angle of 30 degrees
s = 100.0  # 100 meters along the lane
l = 5.0  # 5 meters lateral offset from the centerline
lane_heading = np.radians(30)  # Convert heading angle to radians

X, Y = frenet_to_cartesian(s, l, lane_heading)
print(f"Cartesian coordinates: X = {X}, Y = {Y}")
