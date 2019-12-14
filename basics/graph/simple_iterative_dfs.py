from graph import Graph, UndirectedGraph, DirectedGraph

def dfs(g: Graph):
    visited = {}

    def dfs_from_source(source):
        stack = [source]
        while len(stack) > 0:
            u = stack.pop()
            if u not in visited:
                visited[u] = True
                print(f"Visiting vertex {u}")
                for v in g.adj(u):
                    print(f"Visiting edge ({u},{v})")
                    stack.append(v)

    for v in g.vertices():
        if (v not in visited):
            dfs_from_source(v)


if __name__ == "__main__":
    g = UndirectedGraph()
    g.insertEdge(1, 2)
    g.insertEdge(1, 3)
    g.insertEdge(2, 3)
    g.insertEdge(2, 5)
    g.insertEdge(3, 4)
    g.insertEdge(3, 5)
    source = 5
    print(f"Given this undirected graph:\n{g}\n"
          f"It's DFS log:")
    dfs(g)

    g = DirectedGraph()
    g.insertEdge(1, 2)
    g.insertEdge(1, 3)
    g.insertEdge(2, 3)
    g.insertEdge(2, 5)
    g.insertEdge(3, 4)
    g.insertEdge(3, 5)
    source = 2
    print(f"\n\nGiven this directed graph:\n{g}\n"
          f"It's DFS log:")
    dfs(g)
