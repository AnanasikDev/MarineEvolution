import networkx as nx
import matplotlib.pyplot as plt
import re

# Example input
connections = """
in_rand(0) -> in_posy(3)
in_posx(2) -> o_oscf(8)
neutral(9) -> neutral(10)
in_posx(2) -> o_movx(6)
in_rand(0) -> neutral(9)
in_posy(3) -> in_oscl(1)
in_bord(4) -> o_movx(6)
in_posy(3) -> neutral(10)
o_movy(7) -> in_rand(0)
o_movx(6) -> in_pplt(5)
neutral(9) -> in_bord(4)
in_oscl(1) -> in_pplt(5)
o_oscf(8) -> o_oscf(8)
in_pplt(5) -> in_bord(4)
in_bord(4) -> in_posx(2)
in_oscl(1) -> neutral(11)
in_posy(3) -> in_oscl(1)
neutral(11) -> o_movy(7)
neutral(10) -> in_posx(2)
o_oscf(8) -> in_posx(2)
neutral(10) -> neutral(11)
o_movy(7) -> neutral(10)
o_movy(7) -> in_oscl(1)
neutral(10) -> in_bord(4)
in_posx(2) -> neutral(10)
in_posx(2) -> in_posy(3)
o_oscf(8) -> o_movx(6)
neutral(9) -> neutral(10)
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
    pos = nx.spring_layout(G)  # Position nodes with a layout algorithm
    nx.draw(G, pos, with_labels=True, node_color="skyblue", edge_color="black",
            node_size=250, font_size=7, font_weight="bold", arrows=True)

    # Show the graph
    plt.title("Neuron Connections")
    plt.show()

# Run visualization
visualize_connections(connections)
