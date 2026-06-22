import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

# Sampled S-T data
s_data = np.array([0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0])  # S data
t_data = np.array([0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0])  # T data
v_data = np.array([0.0, 5.0, 10.0, 12.0, 15.0, 18.0, 20.0])  # Velocity data

# Perform fifth-order polynomial interpolation
fifth_order_poly = interp1d(t_data, v_data, kind='cubic')

# Create a finer S data range for the smoothed curve
t_smooth = np.linspace(min(t_data), max(t_data), num=1000)

# Calculate the smoothed velocity data
v_smooth = fifth_order_poly(t_smooth)

# Plotting
plt.figure(figsize=(8, 6))
plt.plot(t_data,
         v_data,
         label='Original Velocity',
         color='blue',
         marker='o',
         linestyle='-',
         markersize=6)
plt.plot(t_smooth,
         v_smooth,
         label='Smoothed Velocity',
         color='red',
         linewidth=2)
plt.xlabel('Time (s)')
plt.ylabel('Velocity (m/s)')
plt.title('V-T Velocity Profile with Fifth-Order Polynomial Smoothing')
plt.legend()
plt.grid()
plt.show()
