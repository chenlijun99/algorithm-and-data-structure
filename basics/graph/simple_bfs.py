from graph import Graph, UndirectedGraph, DirectedGraph

def bfs(g: Graph, source):
    visited = {}
    visited[source] = True
    queue = [source]

    while len(queue) > 0:
        vertex = queue.pop(0)
        print(f"Visiting vertex {vertex}")
        for adj in g.adj(vertex):
            print(f"Visiting edge {vertex, adj}")
            if (adj in visited) == False:
                visited[adj] = True
                queue.append(adj)

if __name__ == "__main__":
    g = UndirectedGraph()
    g.insertEdge(1, 2)
    g.insertEdge(1, 3)
    g.insertEdge(2, 3)
    g.insertEdge(2, 5)
    g.insertEdge(3, 4)
    g.insertEdge(3, 5)
    source = 5
    print(f"Given this undirected graph:\n{g}\n\n"
            f"It's BFS log with source vertex {source}:")
    bfs(g, source)

    g = DirectedGraph()
    g.insertEdge(1, 2)
    g.insertEdge(1, 3)
    g.insertEdge(2, 3)
    g.insertEdge(2, 5)
    g.insertEdge(3, 4)
    g.insertEdge(3, 5)
    source = 2
    print(f"Given this directed graph:\n{g}\n\n"
            f"It's BFS log with source vertex {source}:")
    bfs(g, source)

