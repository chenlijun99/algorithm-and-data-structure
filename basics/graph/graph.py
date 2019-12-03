class Graph:
    def __init__(self):
        self.nodes = {}

    def vertices(self):
        return self.nodes.keys()

    def size(self):
        return len(self.nodes)

    def adj(self, u):
        if u in self.nodes:
            return list(self.nodes[u])

    def insertNode(self, u):
        if u not in self.nodes:
            self.nodes[u] = {}

    def insertEdge(self, u, v, w = 0):
        raise NotImplementedError

    def __str__(self):
        return str(self.nodes)

class DirectedGraph(Graph):
    def insertEdge(self, u, v, w = 0):
        self.insertNode(u)
        self.insertNode(v)
        self.nodes[u][v] = w

class UndirectedGraph(Graph):
    def insertEdge(self, u, v, w = 0):
        self.insertNode(u)
        self.insertNode(v)
        self.nodes[u][v] = w
        self.nodes[v][u] = w
