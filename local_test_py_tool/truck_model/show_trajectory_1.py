import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Assuming state_x and state_y are lists or arrays with the X, Y coordinates of the truck
# For this example, I will generate a circular trajectory as placeholder data
angle = np.linspace(0, 2 * np.pi, 100)
state_x = 50 * np.cos(angle)
state_y = 50 * np.sin(angle)

fig, ax = plt.subplots()
line, = ax.plot([], [], 'o-', lw=2)
trajectory, = ax.plot([], [], '-', lw=1, color='blue')
ax.set_xlim(-60, 60)
ax.set_ylim(-60, 60)


def init():
    line.set_data([], [])
    trajectory.set_data([], [])
    return line, trajectory


def animate(i):
    line.set_data(state_x[i], state_y[i])
    trajectory.set_data(state_x[:i + 1], state_y[:i + 1])
    return line, trajectory


ani = FuncAnimation(fig,
                    animate,
                    frames=len(state_x),
                    init_func=init,
                    blit=True,
                    repeat=False)
# 保存到gif中
# ani.save('truck_trajectory.gif', writer='pillow', fps=30)

plt.show()
