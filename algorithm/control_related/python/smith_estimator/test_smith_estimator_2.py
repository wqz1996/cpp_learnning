import numpy as np
import matplotlib.pyplot as plt

# system param
K = 1.0
tau = 1.0

# PID controller param
Kp = 1.0
Ki = 0.5
Kd = 0.0

# simulation param
dt = 0.1
T = 20.0
n = int(T / dt)
delay_time_of_output = 0.5  # s
delay_time_of_control_cmd = 0.5  # s

output = np.zeros(n)
error = np.zeros(n)
time = np.arange(0, T, dt)
control_cmd = np.zeros(n)
delayed_control_cmd = np.zeros(n)

delay_buffer_of_output = np.zeros(int(delay_time_of_output / dt))
delay_buffer_of_control_cmd = np.zeros(int(delay_time_of_control_cmd / dt))

# bilinear transformation
a = (2 * tau - dt) / (2 * tau + dt)
b = (2 * K * dt) / (2 * tau + dt)

setpoint = 1.0
for i in range(1, n):
    error[i] = setpoint - output[i - 1]
    P_cmd = Kp * error[i]
    I_cmd = Ki * sum(error[:i]) * dt
    D_cmd = Kd * (error[i] - error[i - 1]) / dt

    control_cmd[i] = P_cmd + I_cmd + D_cmd

    delay_buffer_of_control_cmd = np.roll(delay_buffer_of_control_cmd, -1)
    delay_buffer_of_control_cmd[-1] = control_cmd[i]
    delayed_control_cmd[i] = delay_buffer_of_control_cmd[0]

    output[i] = a * output[i - 1] + b * (delayed_control_cmd[i] +
                                         delayed_control_cmd[i - 1])

# variables with smith
Kp_smith = 1.0
Ki_smith = 0.5
Kd_smith = 0.0
delay_time_of_output_smith = 0.5  # s
delay_time_of_control_cmd_smith = 1.0  # s
delay_time_of_control_cmd_real = 0.5

error_smith = np.zeros(n)
output_smith = np.zeros(n)
control_cmd_smith = np.zeros(n)
delayed_control_cmd_smith = np.zeros(n)
delayed_control_cmd_real = np.zeros(n)
delayed_control_cmd_smith_with_comp = np.zeros(n)
delay_buffer_of_control_cmd_smith = np.zeros(
    int(delay_time_of_control_cmd_smith / dt))
delay_buffer_of_control_cmd_real = np.zeros(
    int(delay_time_of_control_cmd_real / dt))

predict_output_without_delay = np.zeros(n)
predict_output_with_delay = np.zeros(n)
smith_compensation = np.zeros(n)

for i in range(1, n):
    error_smith[i] = setpoint - output_smith[
        i -
        1] - predict_output_without_delay[i -
                                          1] + predict_output_with_delay[i - 1]

    # error_smith[i] = setpoint - predict_output_without_delay[i - 1]

    P_cmd_smith = Kp_smith * error_smith[i]
    I_cmd_smith = Ki_smith * sum(error_smith[:i]) * dt
    D_cmd_smith = Kd_smith * (error_smith[i] - error_smith[i - 1]) / dt

    control_cmd_smith[i] = P_cmd_smith + I_cmd_smith + D_cmd_smith

    delay_buffer_of_control_cmd_smith = np.roll(
        delay_buffer_of_control_cmd_smith, -1)
    delay_buffer_of_control_cmd_smith[-1] = control_cmd_smith[i]
    delayed_control_cmd_smith[i] = delay_buffer_of_control_cmd_smith[0]

    delay_buffer_of_control_cmd_real = np.roll(
        delay_buffer_of_control_cmd_real, -1)
    delay_buffer_of_control_cmd_real[-1] = control_cmd_smith[i]
    delayed_control_cmd_real[i] = delay_buffer_of_control_cmd_real[0]

    # smith predictor
    # without delay
    predict_output_without_delay[i] = a * predict_output_without_delay[
        i - 1] + b * (control_cmd_smith[i] + control_cmd_smith[i - 1])

    # with delay
    predict_output_with_delay[i] = a * predict_output_with_delay[i - 1] + b * (
        delayed_control_cmd_smith[i] + delayed_control_cmd_smith[i - 1])

    output_smith[i] = a * output_smith[i - 1] + b * (
        delayed_control_cmd_real[i] + delayed_control_cmd_real[i - 1])

plt.figure(figsize=(20, 15))
# plt.subplost(2, 1, 1)
plt.plot(time, output, label='output')
plt.plot(time, output_smith, label='output_smith')
plt.axhline(y=setpoint, color='r', linestyle='--', label='Setpoint')
plt.xlabel('Time (s)')
plt.ylabel('output')
plt.title('Smith predictor')
plt.grid()
plt.legend()
plt.show()