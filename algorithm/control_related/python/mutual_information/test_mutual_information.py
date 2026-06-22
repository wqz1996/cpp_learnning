import numpy as np
from scipy.stats import entropy


def align_signals(signal1, signal2, max_delay):
    best_delay = 0
    best_mi = -np.inf

    for delay in range(-max_delay, max_delay + 1):
        shifted_signal2 = np.roll(signal2, delay)

        # 计算互信息
        mi = calculate_mutual_information(signal1, shifted_signal2)

        # 更新最佳延迟和互信息
        if mi > best_mi:
            best_mi = mi
            best_delay = delay

    return best_delay


def calculate_mutual_information(signal1, signal2):
    # 计算信号的概率分布
    p_signal1 = np.histogram(signal1, bins=10, density=True)[0]
    p_signal2 = np.histogram(signal2, bins=10, density=True)[0]

    # 计算信号的熵
    entropy_signal1 = entropy(p_signal1)
    entropy_signal2 = entropy(p_signal2)

    # 计算联合概率分布
    p_joint = np.histogram2d(signal1, signal2, bins=10,
                             density=True)[0].flatten()

    # 计算联合熵
    entropy_joint = entropy(p_joint)

    # 计算互信息
    mutual_information = entropy_signal1 + entropy_signal2 - entropy_joint
    return mutual_information


# 示例用法
signal1 = [1, 2, 3, 4, 5]
signal2 = [2, 4, 6, 8, 10]
max_delay = 2

aligned_delay = align_signals(signal1, signal2, max_delay)
print("最佳延迟:", aligned_delay)
