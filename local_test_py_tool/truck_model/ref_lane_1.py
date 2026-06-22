import numpy as np
import matplotlib.pyplot as plt

def frenet_to_cartesian(s, l, curvature):
    """
    Transform from Frenet coordinates to Cartesian coordinates for a circular trajectory.
    
    Args:
    s (float): Arc-length along the lane.
    l (float): Lateral offset from the lane centerline.
    curvature (float): Curvature of the path (1/radius).
    
    Returns:
    (float, float): The Cartesian coordinates (X, Y).
    """
    # For a circle, the heading angle theta changes as a function of s
    theta = s * curvature
    
    # Calculate the position on the centerline
    X_C = radius * np.sin(theta)
    Y_C = radius * (1 - np.cos(theta))
    
    # Calculate the normal vector components at the current position on the centerline
    N_x = np.cos(theta)
    N_y = np.sin(theta)
    
    # Calculate the Cartesian coordinates
    X_P = X_C + l * N_x
    Y_P = Y_C + l * N_y
    
    return X_P, Y_P,theta



# Define a simple circular trajectory for demonstration
radius = 50  # radius of the circle in meters
arc_length = np.linspace(0, 2 * np.pi * radius, 100)  # s: arc length along the trajectory

# l: lateral offset from the circle's center (0 for this simple case)
lateral_offset = np.zeros_like(arc_length)

# For a circle, the curvature κ is the inverse of the radius
curvature = np.ones_like(arc_length) / radius

# The heading angle θ for a circle increases linearly with arc length
heading_angle = (arc_length / radius) % (2.0 * np.pi)

X_coordinate = []
Y_coordinate = []
theta_ = []
# Print curvature and heading angle information at each point
for s, l, κ, θ in zip(arc_length, lateral_offset, curvature, heading_angle):
    X,Y,theta = frenet_to_cartesian(s,l,κ)
    X_coordinate.append(X)
    Y_coordinate.append(Y)
    theta_.append(theta)
    # print(f"Arc Length: {s:.2f}, Lateral Offset: {l:.2f}, Curvature: {κ:.4f}, Heading Angle: {θ:.4f}")
    
# Plot the trajectory in s-l coordinate system
plt.figure()
plt.subplot(3,1,1)
plt.plot(arc_length, lateral_offset, label="Trajectory")
plt.xlabel("Arc Length s (m)")
plt.ylabel("Lateral Offset l (m)")
plt.title("Trajectory in s-l Coordinate System")
plt.legend()
plt.grid()

plt.subplot(3,1,2)
plt.plot(X_coordinate, Y_coordinate, label=" Trajectory")
plt.xlabel("X (m)")
plt.ylabel("Y (m)")
plt.title("Trajectory in X-Y Coordinate System")
plt.legend()
plt.grid()

plt.subplot(3,1,3)
plt.plot(theta_, label=" theta")
plt.legend()
plt.grid()

plt.show()


