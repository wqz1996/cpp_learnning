import matplotlib.pyplot as plt

# 读取数据
with open(
        '/home/wu/local_test_py_tool/control_related/C++/iir_filter/debug_file/data.txt',
        'r') as file:
    lines = file.readlines()

# 提取输入信号和输出信号
time = [float(val) for val in lines[1].split()]
input_signal = [float(val) for val in lines[3].split()]
output_signal = [float(val) for val in lines[5].split()]

# 绘制图形
plt.figure(figsize=(10, 6))
plt.plot(time, input_signal, label='Input Signal')
plt.plot(time, output_signal, label='Output Signal', alpha=0.7)
plt.title('Input and Output Signals')
plt.xlabel('Sample')
plt.ylabel('Amplitude')
plt.legend()
plt.grid(True)
plt.show()