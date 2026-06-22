import numpy as np
import matplotlib.pyplot as plt

# Define the path parameters
path_length = 100  # Total path length
curve_length = 50  # Length of the curved section of the path
radius = 30  # Radius of the curve for the circular section

# Generate the straight section
straight_x = np.linspace(0, path_length - curve_length, num=100)
straight_y = np.zeros_like(straight_x)
straight_kappa = np.zeros_like(straight_x)  # Curvature of a straight line is 0

# Generate the curved section
theta = np.linspace(0, np.pi, num=100)  # Half circle
curve_x = radius * (1 - np.cos(theta)) + straight_x[-1]
curve_y = radius * np.sin(theta)
curve_kappa = np.ones_like(theta) / radius  # Constant curvature for a circle

# Concatenate the sections to form the full path
path_x = np.concatenate([straight_x, curve_x, straight_x + curve_x[-1]])
path_y = np.concatenate([straight_y, curve_y, straight_y + curve_y[-1]])
path_kappa = np.concatenate([straight_kappa, curve_kappa, straight_kappa])

# Calculate the heading angle (psi) along the path
psi = np.arctan2(np.gradient(path_y), np.gradient(path_x))

# Plot the reference path with curvature
plt.figure()
plt.subplot(2, 1, 1)
plt.plot(path_x, path_y, label='Reference Path')
plt.quiver(path_x[::10],
           path_y[::10],
           np.cos(psi[::10]),
           np.sin(psi[::10]),
           scale=20,
           color='red',
           label='Heading')
plt.xlabel('X position [m]')
plt.ylabel('Y position [m]')
plt.title('Reference Path with Heading')
plt.legend()
plt.grid(True)

# Plot the curvature along the path
plt.subplot(2, 1, 2)
plt.plot(path_x, path_kappa, label='Curvature')
plt.xlabel('X position [m]')
plt.ylabel('Curvature [1/m]')
plt.title('Curvature Along the Path')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
