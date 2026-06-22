import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Initialize figure for animation
fig, ax = plt.subplots()

# Set up initial plot objects
vehicle, = ax.plot([], [], 'o-', lw=2, color='gray')
trajectory, = ax.plot([], [], '-', lw=1, color='blue')
ax.set_xlim(-100, 100)
ax.set_ylim(-100, 100)
ax.set_aspect('equal')
ax.grid()

# Assuming the truck model and simulation loop are defined elsewhere in the code,
# and state_x and state_y contain the X, Y positions of the vehicle at each timestep.

# Here we create example data to represent the X, Y positions for the animation.
# In a real scenario, you would use the output from your truck model simulation.
state_x = np.cumsum(np.cos(np.linspace(0, 2 * np.pi, 100)))  # Example data
state_y = np.cumsum(np.sin(np.linspace(0, 2 * np.pi, 100)))  # Example data


# Initialize the animation frame
def init():
    vehicle.set_data([], [])
    trajectory.set_data([], [])
    return vehicle, trajectory


# Animation update function
def update(frame):
    # Update the vehicle position
    vehicle.set_data(state_x[frame], state_y[frame])

    # Update the trajectory line
    trajectory.set_data(state_x[:frame + 1], state_y[:frame + 1])

    # Optionally, update the plot limits dynamically
    ax.set_xlim(state_x[frame] - 10, state_x[frame] + 10)
    ax.set_ylim(state_y[frame] - 10, state_y[frame] + 10)

    return vehicle, trajectory


# Create the animation object
ani = FuncAnimation(fig,
                    update,
                    frames=len(state_x),
                    init_func=init,
                    blit=True,
                    interval=100)

# Show the animation
plt.show()
# If you want to save the animation as a video file, uncomment the following line
# ani.save('truck_trajectory.mp4', writer='ffmpeg', fps=30)

# Note: The above code assumes that `state_x` and `state_y` are the X, Y coordinates
# of the truck at each time step, which would be obtained from the TruckModel simulation.
# Replace the example data with the actual truck model state data.
