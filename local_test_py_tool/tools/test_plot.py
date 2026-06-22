import matplotlib

matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

width = 15
height = 5
data = {
    '1': {
        '20210101': 1,
        '20210102': 5,
        '20210103': 3,
        '20210104': 8
    },
    '2': {
        '20210101': 1,
        '20210102': 5,
        '20210103': 3,
        '20210104': 8
    },
    '3': {
        '20210101': 1,
        '20210102': 5,
        '20210103': 3,
        '20210104': 8
    },
    '4': {
        '20210101': 1,
        '20210102': 5,
        '20210103': 3,
        '20210104': 8
    }
}
#创建画布column_len宽,row_len长
fig = plt.figure(figsize=(width, height))
#设置画布背景色
fig.patch.set_facecolor('gray')

c = 1
for group, dates in data.items():
    x = []
    y = []
    for date, val in dates.items():
        x.append(date)
        y.append(val)

    #画子图图,在2 * 2的方格里的c位置
    plt.subplot(2, 2, c)
    #设置x轴和y轴
    plt.plot(x, y)
    #子图title
    plt.title(f"{group}", fontsize='xx-large', fontweight='heavy')
    #在y轴指定坐标添加水平直线, ls 线条样式,c 线条颜色

    plt.axhline(y=5, ls=":", c="r")

    #子图间距自适应
    plt.tight_layout()

    c += 1
plt.show()