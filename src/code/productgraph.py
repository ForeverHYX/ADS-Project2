import networkx as nx
import random

def generate_connected_graph(n, m):
    if m < n - 1 or m > n * (n - 1) // 2:
        raise ValueError("边数 m 必须满足 n-1 <= m <= n*(n-1)/2")

    G = nx.Graph()
    G.add_nodes_from(range(n))

    edges = list(nx.utils.pairwise(range(n))) 
    random.shuffle(edges)
    G.add_edges_from(edges[:n - 1])
    additional_edges = [(i, j) for i in range(n) for j in range(i + 1, n)]
    random.shuffle(additional_edges)

    for edge in additional_edges[:m - (n - 1)]:
        G.add_edge(*edge)

    return G

def print_graph_edges_linear(G,n):
    filepath='ADS/ads-project/ADS-P2-carry/ADS-Project2/src/code/linear_graph.txt'
    with open(filepath,mode='w',encoding='utf-8') as file_obj:
        total_edges = G.number_of_edges()
        file_obj.write(f"{n} {2*total_edges}\n")

        for u, v in G.edges():
            length = random.randint(1, 10)
            file_obj.write(f"a {u+1} {v+1} {length}\n")
            file_obj.write(f"a {v+1} {u+1} {length}\n")
def print_graph_edges_root(G,n):
    filepath='ADS/ads-project/ADS-P2-carry/ADS-Project2/src/code/quadratic_root_graph.txt'
    with open(filepath,mode='w',encoding='utf-8') as file_obj:
        total_edges = G.number_of_edges()
        file_obj.write(f"{n} {2*total_edges}\n")

        for u, v in G.edges():
            length = random.randint(1, 10) 
            file_obj.write(f"a {u+1} {v+1} {length}\n")
            file_obj.write(f"a {v+1} {u+1} {length}\n")
def print_graph_edges_quadratic(G,n):
    filepath='ADS/ads-project/ADS-P2-carry/ADS-Project2/src/code/quadratic_graph.txt'
    with open(filepath,mode='w',encoding='utf-8') as file_obj:
        total_edges = G.number_of_edges()
        file_obj.write(f"{n} {2*total_edges}\n")

        for u, v in G.edges():
            length = random.randint(1, 10)
            file_obj.write(f"a {u+1} {v+1} {length}\n")
            file_obj.write(f"a {v+1} {u+1} {length}\n")

n = 1000  

m_linear = n
linear_graph = generate_connected_graph(n, m_linear)
print_graph_edges_linear(linear_graph,n)

m_quadratic_root = int(n**1.5)
quadratic_root_graph = generate_connected_graph(n, m_quadratic_root)
print_graph_edges_root(quadratic_root_graph,n)

m_quadratic = n * (n - 1) // 2  
quadratic_graph = generate_connected_graph(n, m_quadratic)
print_graph_edges_quadratic(quadratic_graph,n)