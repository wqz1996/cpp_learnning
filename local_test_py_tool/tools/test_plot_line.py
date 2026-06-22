import matplotlib.pyplot as plt

# 定义两个点的坐标
x = [1, 4]  # 第一个点的 x 和第二个点的 x
y = [2, 7]  # 第一个点的 y 和第二个点的 y

# 创建一个图形
plt.figure()

# 绘制两个点
plt.scatter(x, y, c='red', label='Points')  # 绘制点
plt.plot(x, y, 'b-', label='Line')  # 绘制连线，'b-' 表示蓝色实线

# 添加标签和标题
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Line Between Two Points')

# 显示图例
plt.legend()

# 显示图形
plt.grid()
plt.show()
