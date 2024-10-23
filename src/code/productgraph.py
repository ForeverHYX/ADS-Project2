import networkx as nx
import random

def generate_connected_graph(n, m):
    """Generate a connected graph with m edges and n nodes"""
    if m < n - 1 or m > n * (n - 1) // 2:
        raise ValueError("Number of edges m must satisfy n-1 <= m <= n*(n-1)/2")

    G = nx.Graph()  # Create an empty graph
    G.add_nodes_from(range(n))  # Add n nodes to the graph

    # Ensure the graph is connected by adding n-1 edges to form a tree
    edges = list(nx.utils.pairwise(range(n)))  # Create a chain of connected nodes
    random.shuffle(edges)  # Shuffle the edges randomly
    G.add_edges_from(edges[:n - 1])  # Add the first n-1 edges to ensure connectivity

    # Add remaining edges to meet the required number of edges m
    additional_edges = [(i, j) for i in range(n) for j in range(i + 1, n)]  # All possible edges
    random.shuffle(additional_edges)  # Shuffle the edge list

    for edge in additional_edges[:m - (n - 1)]:  # Add the extra edges to the graph
        G.add_edge(*edge)

    return G

def print_graph_edges_linear(G, n):
    """Print edges of the linear graph along with their lengths to a file"""
    filepath = 'ADS/ads-project/ADS-P2-carry/ADS-Project2/src/code/linear_graph8.txt'
    with open(filepath, mode='w', encoding='utf-8') as file_obj:
        total_edges = G.number_of_edges()  # Get the total number of edges
        file_obj.write(f"{n} {2 * total_edges}\n")  # Write the node and edge count

        for u, v in G.edges():
            length = random.randint(1, 100)  # Randomly generate a length between 1 and 100
            file_obj.write(f"a {u + 1} {v + 1} {length}\n")  # Write the edge details (directed)
            file_obj.write(f"a {v + 1} {u + 1} {length}\n")  # Write the reverse edge (since it's undirected)

def print_graph_edges_root(G, n):
    """Print edges of the quadratic root graph along with their lengths to a file"""
    filepath = 'ADS/ads-project/ADS-P2-carry/ADS-Project2/src/code/quadratic_root_graph8.txt'
    with open(filepath, mode='w', encoding='utf-8') as file_obj:
        total_edges = G.number_of_edges()  # Get the total number of edges
        file_obj.write(f"{n} {2 * total_edges}\n")  # Write the node and edge count

        for u, v in G.edges():
            length = random.randint(1, 100)  # Randomly generate a length between 1 and 100
            file_obj.write(f"a {u + 1} {v + 1} {length}\n")  # Write the edge details (directed)
            file_obj.write(f"a {v + 1} {u + 1} {length}\n")  # Write the reverse edge (since it's undirected)

def print_graph_edges_quadratic(G, n):
    """Print edges of the quadratic graph along with their lengths to a file"""
    filepath = 'ADS/ads-project/ADS-P2-carry/ADS-Project2/src/code/quadratic_graph8.txt'
    with open(filepath, mode='w', encoding='utf-8') as file_obj:
        total_edges = G.number_of_edges()  # Get the total number of edges
        file_obj.write(f"{n} {2 * total_edges}\n")  # Write the node and edge count

        for u, v in G.edges():
            length = random.randint(1, 100)  # Randomly generate a length between 1 and 100
            file_obj.write(f"a {u + 1} {v + 1} {length}\n")  # Write the edge details (directed)
            file_obj.write(f"a {v + 1} {u + 1} {length}\n")  # Write the reverse edge (since it's undirected)

# Generate the graphs
n = 50  # Number of nodes

# m = Θ(n)
m_linear = n  # For linear graph, the number of edges is proportional to n
linear_graph = generate_connected_graph(n, m_linear)
print_graph_edges_linear(linear_graph, n)  # Print the linear graph edges

# m = Θ(n^1.5)
m_quadratic_root = int(n**1.5)  # For root quadratic graph, the number of edges is proportional to n^1.5
quadratic_root_graph = generate_connected_graph(n, m_quadratic_root)
print_graph_edges_root(quadratic_root_graph, n)  # Print the root quadratic graph edges

# m = Θ(n^2)
m_quadratic = n * (n - 1) // 2  # For quadratic graph, the number of edges is proportional to n^2 (complete graph)
quadratic_graph = generate_connected_graph(n, m_quadratic)
print_graph_edges_quadratic(quadratic_graph, n)  # Print the quadratic graph edges
