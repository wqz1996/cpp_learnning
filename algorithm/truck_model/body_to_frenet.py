import numpy as np


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


# Example usage:
# Vehicle position in world coordinates (meters)
vehicle_x = 10
vehicle_y = 5
vehicle_heading = np.radians(30)  # Vehicle heading in radians

# Path starting point in world coordinates (meters)
path_start_x = 0
path_start_y = 0
path_heading = np.radians(0)  # Path heading in radians (straight east)

# Calculate Frenet coordinates
s, l, e_psi, e_y = body_to_frenet_coordinates(vehicle_x, vehicle_y,
                                              vehicle_heading, path_start_x,
                                              path_start_y, path_heading)
print(f"Frenet s: {s}, l: {l}, Heading Error: {e_psi}, Lateral Error: {e_y}")
