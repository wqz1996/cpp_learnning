from scipy import signal

# 设定滤波器参数
order = 7  # 滤波器阶数
cutoff_frequency = 0.5  # 截止频率
sample_frequency = 20.0  # 采样频率
nyquist_frequency = 0.5 * sample_frequency  # nyquist频率为采样频率的一半
normalized_frequency = cutoff_frequency / nyquist_frequency  # 归一化截止频率

# 设计巴特沃斯低通滤波器
numerators, denominators = signal.iirfilter(order,
                                            normalized_frequency,
                                            btype='lowpass',
                                            analog=False,
                                            ftype='butter')
print("numerators coefficients:")
for val in numerators:
    print("{},".format(val))

print("denominators coefficients:", denominators)
for val in denominators:
    print("{},".format(val))
