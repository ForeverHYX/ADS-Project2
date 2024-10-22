'''
Author: ForeverHYX 2937532336@qq.com
Date: 2024-10-22 13:54:49
LastEditors: ForeverHYX 2937532336@qq.com
LastEditTime: 2024-10-22 14:01:54
FilePath: /code/productgraph.py
Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
'''
import networkx as nx
import random

def generate_connected_graph(n, m):
    """生成一个连通图，边数为m，节点数为n"""
    if m < n - 1 or m > n * (n - 1) // 2:
        raise ValueError("边数 m 必须满足 n-1 <= m <= n*(n-1)/2")

    G = nx.Graph()
    G.add_nodes_from(range(n))

    # 确保图是连通的，先添加 n-1 条边形成树
    edges = list(nx.utils.pairwise(range(n)))  # 形成初步的连通图
    random.shuffle(edges)
    G.add_edges_from(edges[:n - 1])  # 添加初步的连通边

    # 添加剩余的边
    additional_edges = [(i, j) for i in range(n) for j in range(i + 1, n)]
    random.shuffle(additional_edges)

    for edge in additional_edges[:m - (n - 1)]:
        G.add_edge(*edge)

    return G

def print_graph_edges_linear(G,n):
    """打印图的边及其长度"""
<<<<<<< HEAD
    filepath='ADS/ads-project/ADS-P2-carry/ADS-Project2/src/code/linear_graph1.txt'
=======
    filepath='linear_graph10.txt'
>>>>>>> 43e0be296c3369939d233e833eff0e01783f8e62
    with open(filepath,mode='w',encoding='utf-8') as file_obj:
        total_edges = G.number_of_edges()
        file_obj.write(f"{n} {2*total_edges}\n")

        for u, v in G.edges():
            length = random.randint(1, 10)  # 随机生成长度，范围为 1 到 10
            file_obj.write(f"a {u+1} {v+1} {length}\n")
            file_obj.write(f"a {v+1} {u+1} {length}\n")
def print_graph_edges_root(G,n):
    """打印图的边及其长度"""
<<<<<<< HEAD
    filepath='ADS/ads-project/ADS-P2-carry/ADS-Project2/src/code/quadratic_root_graph1.txt'
=======
    filepath='quadratic_root_graph10.txt'
>>>>>>> 43e0be296c3369939d233e833eff0e01783f8e62
    with open(filepath,mode='w',encoding='utf-8') as file_obj:
        total_edges = G.number_of_edges()
        file_obj.write(f"{n} {2*total_edges}\n")

        for u, v in G.edges():
            length = random.randint(1, 10)  # 随机生成长度，范围为 1 到 10
            file_obj.write(f"a {u+1} {v+1} {length}\n")
            file_obj.write(f"a {v+1} {u+1} {length}\n")
def print_graph_edges_quadratic(G,n):
    """打印图的边及其长度"""
<<<<<<< HEAD
    filepath='ADS/ads-project/ADS-P2-carry/ADS-Project2/src/code/quadratic_graph1.txt'
=======
    filepath='quadratic_graph10.txt'
>>>>>>> 43e0be296c3369939d233e833eff0e01783f8e62
    with open(filepath,mode='w',encoding='utf-8') as file_obj:
        total_edges = G.number_of_edges()
        file_obj.write(f"{n} {2*total_edges}\n")

        for u, v in G.edges():
            length = random.randint(1, 10)  # 随机生成长度，范围为 1 到 10
            file_obj.write(f"a {u+1} {v+1} {length}\n")
            file_obj.write(f"a {v+1} {u+1} {length}\n")

# 生成图s
n = 1000  # 节点数量

# m = Θ(n)
m_linear = n
linear_graph = generate_connected_graph(n, m_linear)
print_graph_edges_linear(linear_graph,n)

# m = Θ(n^1.5)
m_quadratic_root = int(n**1.5)
quadratic_root_graph = generate_connected_graph(n, m_quadratic_root)
print_graph_edges_root(quadratic_root_graph,n)

# m = Θ(n^2)
m_quadratic = n * (n - 1) // 2  # 完全图的边数
quadratic_graph = generate_connected_graph(n, m_quadratic)
print_graph_edges_quadratic(quadratic_graph,n)

