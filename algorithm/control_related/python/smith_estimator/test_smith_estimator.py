import numpy as np
import matplotlib.pyplot as plt

# 系统参数
K = 1.0  # 系统增益
T = 2.0  # 时间常数
system_delay_time = 1.0  #系统纯延迟时间
smith_predictor_delay_time = 1.0  #smith预估的延迟时间

# 时间设置
dt = 0.1  # 时间步长
time = np.arange(0, 20, dt)
n = len(time)
L_system = int(system_delay_time / dt)
L_smith = int(smith_predictor_delay_time / dt)

a = (2 * T - dt) / (2 * T + dt)
b = (2 * K * dt) / (2 * T + dt)

# 初始化
output_without_smith = np.zeros(n)  # 不带史密斯预估器的系统输出
output_with_smith = np.zeros(n)  # 带史密斯预估器的系统输出
predicted_output = np.zeros(n)  # 预估器的输出
control = np.zeros(n)  # 控制信号
error_without_smith = np.zeros(n)  # 不带史密斯预估器的误差
error_with_smith = np.zeros(n)  # 带史密斯预估器的误差
delay_buffer_without_smith = np.zeros(L_system)  # 不带史密斯预估器的延迟缓冲区
delay_buffer_with_smith = np.zeros(L_smith)  # 带史密斯预估器的延迟缓冲区
predicted_change = np.zeros(n)
control_signal_without_smith_compensation = np.zeros(n)
control_signal_with_smith_compensation = np.zeros(n)
delayed_control_signal_baseline = np.zeros(n)
delayed_control_signal_with_smith_compensation = np.zeros(n)
control_signal_baseline = np.zeros(n)
compensation_value = np.zeros(n)
# PID控制器参数
Kp = 1.0
Ki = 0.2
Kd = 0.0

# 带smith预估器的PID控制器参数
Kp_smith = 1.0
Ki_smith = 0.2
Kd_smith = 0.0

compensation_gain = 2.0

# 目标值
setpoint = 1

for i in range(1, n):
    # 计算不带史密斯预估器的系统误差
    # print("step {}".format(i))
    # print("without smith")
    error_without_smith[i] = setpoint - output_without_smith[i - 1]

    # PID控制器
    P_without_smith = Kp * error_without_smith[i]
    I_without_smith = Ki * sum(error_without_smith[:i]) * dt
    D_without_smith = Kd * (error_without_smith[i] -
                            error_without_smith[i - 1]) / dt

    control_signal_baseline[
        i] = P_without_smith + I_without_smith + D_without_smith
    # print(
    #     "error_without_smith[i] {} control_signal_baseline {} P_without_smith {} I_without_smith {} D_without_smith {}"
    #     .format(error_without_smith[i], control_signal_baseline[i],
    #             P_without_smith, I_without_smith, D_without_smith))

    # 更新不带史密斯预估器的延迟缓冲区
    delay_buffer_without_smith = np.roll(delay_buffer_without_smith, -1)
    delay_buffer_without_smith[-1] = control_signal_baseline[i]
    delayed_control_signal_baseline[i] = delay_buffer_without_smith[0]

    # 不带史密斯预估器的系统更新
    output_without_smith[i] = a * output_without_smith[i - 1] + b * (
        delayed_control_signal_baseline[i] +
        delayed_control_signal_baseline[i - 1])

    # print("with smith")

    # 计算带史密斯预估器的系统误差
    error_with_smith[i] = setpoint - output_with_smith[i - 1]

    P_with_smith = Kp_smith * error_with_smith[i]
    I_with_smith = Ki_smith * sum(error_with_smith[:i]) * dt
    D_with_smith = Kd_smith * (error_with_smith[i] -
                               error_with_smith[i - 1]) / dt
    control_signal_without_smith_compensation[
        i] = P_with_smith + I_with_smith + D_with_smith

    # print(
    #     "error_with_smith[i] {} control_signal_without_smith_compensation {} P_with_smith {} I_with_smith {} D_with_smith {}"
    #     .format(error_with_smith[i],
    #             control_signal_without_smith_compensation[i], P_with_smith,
    #             I_with_smith, D_with_smith))

    # 史密斯预估器的预测
    # predicted_change[i] = (
    #     dt / T) * (-predicted_output[i - 1] +
    #                K * control_signal_without_smith_compensation[i])
    # predicted_output[i] = predicted_output[i - 1] + predicted_change[i]

    predicted_output[i] = a * predicted_output[i - 1] + b * (
        control_signal_without_smith_compensation[i] +
        control_signal_without_smith_compensation[i - 1])

    predicted_change[i] = predicted_output[i] - predicted_output[i - 1]

    compensation_value[i] = compensation_gain * predicted_change[i]

    control_signal_with_smith_compensation[
        i] = control_signal_without_smith_compensation[i] + compensation_value[
            i]

    # 更新不带史密斯预估器的延迟缓冲区
    delay_buffer_with_smith = np.roll(delay_buffer_with_smith, -1)
    delay_buffer_with_smith[-1] = control_signal_with_smith_compensation[i]
    delayed_control_signal_with_smith_compensation[
        i] = delay_buffer_with_smith[0]

    # 带史密斯预估器的系统更新
    output_with_smith[i] = a * output_with_smith[i - 1] + b * (
        delayed_control_signal_with_smith_compensation[i] +
        delayed_control_signal_with_smith_compensation[i - 1])

# 绘制结果
plt.figure(figsize=(20, 15))
plt.subplot(2, 1, 1)
plt.plot(time, output_without_smith, label='Without Smith Predictor')
plt.plot(time, output_with_smith, label='With Smith Predictor')
plt.plot(time, predicted_change, label='Predict Change')
plt.plot(time, predicted_output, label='Predict Output')
plt.axhline(y=setpoint, color='r', linestyle='--', label='Setpoint')
plt.xlabel('Time (seconds)')
plt.ylabel('Output')
plt.title('Comparison of Systems With and Without Smith Predictor')
plt.legend()
plt.grid()

plt.subplot(2, 1, 2)
# plt.plot(time,
#          control_signal_with_smith_compensation,
#          label='control_signal_with_smith_compensation')
plt.plot(time,
         control_signal_without_smith_compensation,
         label='control_signal_without_smith_compensation')
plt.plot(time, control_signal_baseline, label='control_signal_baseline')
plt.plot(time, compensation_value, label='compensation_value')
plt.xlabel('Time (seconds)')
plt.ylabel('Control Command')
# plt.title('Comparison of Systems With and Without Smith Predictor')
plt.legend()
plt.grid()
plt.plot()
plt.show()
