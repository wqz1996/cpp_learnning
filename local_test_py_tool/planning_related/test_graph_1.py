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

# 初始化图形
fig, ax = plt.subplots()
pos = nx.spring_layout(G)
nx.draw(G, pos, with_labels=True, node_size=1000, node_color='lightblue')
edge_labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edges(G, pos, arrowstyle='->', arrowsize=10)
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

# 遍历节点
nodes_to_traverse = ['A', 'B', 'C', 'D', 'E']
for i, node in enumerate(nodes_to_traverse):
    # 高亮当前节点
    node_color = ['lightblue'] * G.number_of_nodes()
    node_color[i] = 'red'
    nx.draw(G, pos, with_labels=True, node_size=1000, node_color=node_color)

    # 更新图形
    plt.pause(1)  # 延迟1秒
    plt.clf()

# 显示最终结果
nx.draw(G, pos, with_labels=True, node_size=1000, node_color='lightblue')
nx.draw_networkx_edges(G, pos, arrowstyle='->', arrowsize=10)
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
plt.show()
