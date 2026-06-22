#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt

x_init = np.array([0, 1])
P_init = np.diag([1, 1])

Q = np.diag([0.01, 0.01])

R = np.array([[0.05]])

dt = 0.05
t = np.arange(0, 10, dt)

true_velocity = np.sin(t)
true_acceleration = np.cos(t)

observed_velocity = true_velocity + np.random.normal(0, np.sqrt(0.05), len(t))
observed_acceleration = true_acceleration + np.random.normal(
    0, np.sqrt(0.05), len(t))

x_est = np.zeros((len(t), 2))
P_est = np.zeros((len(t), 2, 2))

x_est[0] = x_init
P_est[0] = P_init

for i in range(1, len(t)):

    A = np.array([[1, dt], [0, 1]])
    x_pred = A @ x_est[i - 1]
    P_pred = A @ P_est[i - 1] @ A.T + Q

    H = np.array([[1, 0]])
    y = observed_velocity[i] - H @ x_pred
    S = H @ P_pred @ H.T + R
    K = P_pred @ H.T @ np.linalg.inv(S)

    x_est[i] = x_pred + K @ y
    P_est[i] = (np.eye(2) - K @ H) @ P_pred

plt.figure(figsize=(12, 6))
plt.plot(t, true_velocity, label='True Velocity')
plt.plot(t, observed_velocity, label='Observed Velocity')
plt.plot(t, true_acceleration, label='True Acceleration')
plt.plot(t, observed_acceleration, label='Observed Acceleration')
plt.plot(t, x_est[:, 0], label='Estimated Velocity')
plt.plot(t, x_est[:, 1], label='Estimated Acceleration')
plt.xlabel('Time')
plt.ylabel('v or a')
plt.legend()
plt.show()
