import networkx as nx
import matplotlib.pyplot as plt
import re

# Example input
connections = """
in_oscl(1) -> in_bord(4)
neutral(10) -> o_movx(5)
neutral(8) -> neutral(9)
in_bord(4) -> o_movx(5)
neutral(8) -> o_movx(5)
neutral(8) -> o_movx(5)
in_bord(4) -> neutral(8)
neutral(9) -> neutral(9)
"""

def parse_connections(input_text):
    """Parses connections from input text and returns a list of (source, target) tuples."""
    pattern = re.compile(r"(\w+\(\d+\))\s*->\s*(\w+\(\d+\))")
    return pattern.findall(input_text)

def visualize_connections(connections):
    """Visualizes neuron connections as a directed graph."""
    G = nx.DiGraph()

    # Extract connections
    edges = parse_connections(connections)

    # Add nodes and edges
    for src, dst in edges:
        G.add_node(src)  # Ensure nodes exist
        G.add_node(dst)
        G.add_edge(src, dst)

    # Draw the graph
    plt.figure(figsize=(8, 6))
    pos = nx.spring_layout(G, seed=42)  # Position nodes with a layout algorithm
    nx.draw(G, pos, with_labels=True, node_color="skyblue", edge_color="black",
            node_size=300, font_size=10, font_weight="bold", arrows=True)

    # Show the graph
    plt.title("Neuron Connections")
    plt.show()

# Run visualization
visualize_connections(connections)
