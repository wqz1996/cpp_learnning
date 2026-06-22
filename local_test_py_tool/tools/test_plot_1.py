import matplotlib.pyplot as plt
from matplotlib.patches import Polygon

# 定义平行四边形的四个顶点坐标
vertices = [(2, 30), (2, 32), (6, 72), (6, 70)]

# 创建一个Polygon对象
parallelogram = Polygon(vertices,
                        closed=True,
                        edgecolor='none',
                        facecolor='blue',
                        alpha=0.3)

# 创建一个坐标轴
fig, ax = plt.subplots()

# 将Polygon对象添加到坐标轴上
ax.add_patch(parallelogram)

# 定义直线的斜率和截距
slope = 0.5
intercept = 0.5

# 定义x范围
x_range = [0, 100]

# 绘制直线
plt.plot(x_range, [slope * x + intercept for x in x_range],
         color='red',
         label='Line')

# 设置坐标轴范围
ax.set_xlim(0, 10)
ax.set_ylim(0, 100)

# 添加标签和图例
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Parallelogram and Line Example')
plt.grid(True)
plt.legend()

plt.show()
