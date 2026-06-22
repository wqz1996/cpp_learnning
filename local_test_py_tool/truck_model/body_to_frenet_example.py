import matplotlib.pyplot as plt
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

# Plotting
fig, ax = plt.subplots()

# Draw the path
path_x = [path_start_x, path_start_x + 15]
path_y = [path_start_y, path_start_y]
ax.plot(path_x, path_y, 'k--', label='Path')

# Draw the vehicle position
ax.plot(vehicle_x, vehicle_y, 'ro', label='Vehicle')

# Draw the vehicle heading direction
vehicle_heading_x = vehicle_x + np.cos(vehicle_heading)
vehicle_heading_y = vehicle_y + np.sin(vehicle_heading)
ax.plot([vehicle_x, vehicle_heading_x], [vehicle_y, vehicle_heading_y],
        'r-',
        label='Vehicle Heading')

# Draw the path heading direction
path_heading_x = path_start_x + np.cos(path_heading)
path_heading_y = path_start_y + np.sin(path_heading)
ax.plot([path_start_x, path_heading_x], [path_start_y, path_heading_y],
        'k-',
        label='Path Heading')

# Draw the projected point on the path
projected_x = path_start_x + s * np.cos(path_heading)
projected_y = path_start_y + s * np.sin(path_heading)
ax.plot(projected_x, projected_y, 'bx', label='Projected Point')

# Draw the line representing the lateral displacement (l)
if l >= 0:
    ax.plot([vehicle_x, projected_x], [vehicle_y, projected_y],
            'g-',
            label='Lateral Displacement (l)')
else:
    ax.plot([vehicle_x, projected_x], [vehicle_y, projected_y],
            'g--',
            label='Lateral Displacement (l)')

# Draw error angles
ax.annotate('',
            xy=(vehicle_x, vehicle_y),
            xytext=(projected_x, projected_y),
            arrowprops=dict(arrowstyle="<->", color='green'))
ax.annotate('',
            xy=(vehicle_heading_x, vehicle_heading_y),
            xytext=(vehicle_x, vehicle_y),
            arrowprops=dict(arrowstyle="<->", color='red'))
ax.annotate('',
            xy=(projected_x, projected_y),
            xytext=(path_start_x, path_start_y),
            arrowprops=dict(arrowstyle="<->", color='blue'))

# Labels, title and legend
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_title('Vehicle Coordinate to Frenet Coordinate Transformation')
ax.legend()
ax.axis('equal')

# Show plot
plt.show()
