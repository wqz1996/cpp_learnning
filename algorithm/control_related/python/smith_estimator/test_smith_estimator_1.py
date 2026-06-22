import numpy as np
import matplotlib.pyplot as plt

# 定义系统参数
K = 1.0  # 系统增益
T = 2.0  # 时间常数
theta = 1.0  # 系统延迟时间

# 定义模拟参数
dt = 0.1  # 时间步长
time = np.arange(0, 20, dt)
n = len(time)
delay_steps = theta / dt

# 使用双线性变换（Tustin方法）将连续时间系统转换为离散时间系统
a_discrete = (2 * T - dt) / (2 * T + dt)
b_discrete = K * (2 * dt) / (2 * T + dt)

# 初始化数组
output = np.zeros(n)  # 系统输出
control_signal = np.zeros(n)  # PID控制器的控制信号
error = np.zeros(n)  # 误差信号
model_output = np.zeros(n)  # 模型输出（用于Smith预测器）
predicted_output = np.zeros(n)

# PID控制器参数
Kp = 1.5  # 比例增益
Ki = 0.5  # 积分增益，暂时设为0以减少积分饱和风险
Kd = 0.0  # 微分增益，暂时设为0以减少噪声放大风险

# 设定点
setpoint = np.ones(n)

# 模拟主循环
for i in range(1, n):
    # 计算误差
    error[i] = setpoint[i] - output[i - 1]

    # PID控制器
    control_signal[i] = Kp * error[i] + Ki * sum(
        error[:i]) * dt + Kd * (error[i] - error[i - 1]) / dt

    # 更新模型输出（不包括延迟）
    model_output[
        i] = a_discrete * model_output[i - 1] + b_discrete * control_signal[i]

    # 使用Smith预测器计算预测输出
    if i >= delay_steps:
        predicted_output[i] = model_output[i] - model_output[int(
            i - delay_steps)] + output[int(i - delay_steps)]
    else:
        predicted_output[i] = model_output[i]

    control_signal[i] += Kp * (predicted_output[i] - output[i - 1])

    # 应用控制信号到实际系统（包含延迟）
    if i >= delay_steps:
        output[i] = a_discrete * output[i - 1] + b_discrete * control_signal[
            int(i - delay_steps)]
    else:
        output[i] = output[i - 1]  # 在延迟期间，输出不变

# 绘制结果
plt.figure(figsize=(12, 5))

# 绘制系统输出
plt.subplot(1, 2, 1)
plt.plot(time, output, label='output')
plt.plot(time, setpoint, label='setpoint', linestyle='--')
plt.title('with smith predictor system output')
plt.xlabel('time(s)')
plt.ylabel('output')
plt.legend()

# 绘制控制信号
plt.subplot(1, 2, 2)
plt.plot(time, control_signal, label='control signal')
plt.title('control signal')
plt.xlabel('time(s)')
plt.ylabel('control signal')
plt.legend()

plt.tight_layout()
plt.show()
