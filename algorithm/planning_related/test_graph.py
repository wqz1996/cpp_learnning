import networkx as nx
import matplotlib.pyplot as plt

# 创建有向图
G = nx.DiGraph()

# 添加节点
G.add_node("A")
G.add_node("B")
G.add_node("C")
G.add_node("D")
G.add_node("E")

# 添加边
G.add_edge("A", "B")
G.add_edge("A", "C")
G.add_edge("B", "D")
G.add_edge("C", "D")
G.add_edge("D", "E")

# 绘制图形
pos = nx.spring_layout(G)  # 定义节点位置
nx.draw(G, pos, with_labels=True, node_size=1000,
        node_color='lightblue')  # 绘制节点
nx.draw_networkx_edges(G, pos, arrowstyle='->', arrowsize=10)  # 绘制边箭头

# 显示图形
plt.show()