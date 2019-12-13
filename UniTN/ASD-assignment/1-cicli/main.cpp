#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
using Query = pair<uint32_t, uint32_t>;

template <typename Func>
void measureTime(const string &funName, Func f) {
  auto start = chrono::system_clock::now();
  f();
  auto end = chrono::system_clock::now();
  cout << funName << ": "
       << chrono::duration_cast<chrono::microseconds>(end - start).count()
       << "us\n";
}

class UndirectedGraph {
 public:
  UndirectedGraph(size_t init_size) : vertices_(init_size) {}

  void insertVertex(uint32_t vertex) {
    if (this->vertices_[vertex].value == UINT32_MAX) {
      this->vertices_[vertex] = Vertex(vertex);
    }
  }

  void insertEdge(uint32_t a, uint32_t b) {
    insertVertex(a);
    insertVertex(b);
    this->vertices_[a].adjacents.push_back(&this->vertices_[b]);
    this->vertices_[b].adjacents.push_back(&this->vertices_[a]);
  }

  /**
   * Build BFS tree and get the optimal data structure on which queries can
   * be run quickly.
   */
  void buildBFSTree();
  /**
   * Query the length of the shortest path betweeen \p vertexA and \p vertexB.
   */
  uint32_t querySPLength(uint32_t vertexA, uint32_t vertexB) const;

  friend ostream &operator<<(ostream &stream, const UndirectedGraph &graph) {
    for (auto &n : graph.vertices_) {
      stream << n;
    }
    return stream;
  }

 private:
  struct Vertex {
    Vertex(uint32_t v = UINT32_MAX) : adjacents({}), value(v) {}
    uint32_t value;
    int erdos = -1;

    struct {
      Vertex *parent = nullptr;
      /*
       * Each edge has an unique incremental id.
       * Exception: edges of the same clique have the same id.
       */
      int id = -1;
    } parentEdge;
    /**
     * Special case optimization: if the SP query is between two vertex with
     * the same farthestDirectlyReachableAncestor (i.e. the two vertex are in a
     * path in the BFS tree were all vertices have degree 1, i.e. only one
     * children) then there's no need to go up the BFS tree. Just get the
     * difference between their distance from source (a.k.a. erdos number).
     */
    Vertex *farthestDirectlyReachableAncestor = nullptr;

    vector<Vertex *> adjacents;
    friend ostream &operator<<(ostream &stream, const Vertex &vertex) {
      stream << "Vertex: " << vertex.value << ", erdos: " << vertex.erdos
             << ", parent: " << vertex.parentEdge.id << ", ancestor: "
             << (vertex.farthestDirectlyReachableAncestor
                     ? vertex.farthestDirectlyReachableAncestor->value
                     : UINT32_MAX)
             << endl;
      return stream;
    }
  };
  vector<Vertex> vertices_;
};

void UndirectedGraph::buildBFSTree() {
  // incremental edge ids
  int id = 0;
  /*
   * From where we start is arbitrary
   */
  queue<Vertex *> queue;
  queue.push(&this->vertices_[0]);
  this->vertices_[0].erdos = 0;

  /*
   * We use these two variables to tell whether a vertex could have a directly
   * reachable ancestor.
   */
  Vertex *lastExploredAdj = nullptr;
  size_t exploredAdjCount = 0;

  while (!queue.empty()) {
    Vertex *u = queue.front();
    queue.pop();

    lastExploredAdj = nullptr;
    exploredAdjCount = 0;

    if (
        // u is the source node
        u->parentEdge.parent == nullptr || u->parentEdge.id != -1) {
      for (Vertex *v : u->adjacents) {
        // for each non-explored vertex
        if (v->erdos == -1) {
          lastExploredAdj = v;
          ++exploredAdjCount;

          v->erdos = u->erdos + 1;
          queue.push(v);

          /*
           * Establish the parent-child relationship between u and v in the BFS
           * tree. The id will be assigned when visiting v, so that we know
           * which id to assign to the parentEdge based on the adjacents of
           * v (i.e. whether there is a clique or not).
           */
          v->parentEdge.parent = u;
        }
      }
    } else {
      /*
       * We're here:
       * => u has a parent but not an id
       *   => u is the first adjacent vertex  that we visit in the clique
       *   (so except their common parent in the BFS tree)
       *   => or u is a normal vertex
       */

      // assign incremental id
      u->parentEdge.id = id;
      id++;
      for (Vertex *v : u->adjacents) {
        if (v->erdos == -1) {
          lastExploredAdj = v;
          ++exploredAdjCount;

          v->erdos = u->erdos + 1;
          queue.push(v);
          v->parentEdge.parent = u;
        } else if (u->parentEdge.parent == v->parentEdge.parent) {
          /*
           * u and the adjacent v have the same parent => their are in the same
           * clique.
           * The first adjacent vertex of the common parent (which is the first
           * visited vertex of the clique) takes care to assign id to all the
           * siblings of the clique.
           */
          v->parentEdge.id = u->parentEdge.id;
        }
      }
    }
    if (lastExploredAdj && exploredAdjCount == 1) {
      /*
       * if the current vertex has only explored a new vertex, we can say that
       * in the BFS tree either the current vertex or the
       * farthestDirectlyReachableAncestor of the current vertex is the
       * farthestDirectlyReachableAncestor of the new vertex.
       */
      lastExploredAdj->farthestDirectlyReachableAncestor =
          u->farthestDirectlyReachableAncestor
              ? u->farthestDirectlyReachableAncestor
              : u;
    }
  }
}

uint32_t UndirectedGraph::querySPLength(uint32_t vertexA,
                                        uint32_t vertexB) const {
  uint32_t distance = 0;
  const Vertex *a = &this->vertices_[vertexA];
  const Vertex *b = &this->vertices_[vertexB];

  // special case optimization
  if (a->farthestDirectlyReachableAncestor != nullptr &&
      (a->farthestDirectlyReachableAncestor ==
       b->farthestDirectlyReachableAncestor)) {
    return (std::max(a->erdos, b->erdos) - std::min(a->erdos, b->erdos));
  }

  // otherwise: go up the BFS tree until a common vertex is reached.j
  while (a->erdos > b->erdos) {
    a = a->parentEdge.parent;
    ++distance;
  }
  while (b->erdos > a->erdos) {
    b = b->parentEdge.parent;
    ++distance;
  }
  while (a != b) {
    ++distance;
    if (a->parentEdge.id != b->parentEdge.id) {
      ++distance;
    }
    a = a->parentEdge.parent;
    b = b->parentEdge.parent;
  }
  return distance;
}

vector<uint32_t> query_shortest_path_lengths(const UndirectedGraph &graph,
                                             const vector<Query> &queries) {
  vector<uint32_t> results;
  results.reserve(queries.size());
  for (auto &query : queries) {
    results.push_back(graph.querySPLength(query.first, query.second));
  }
  assert(results.size() == queries.size());
  return results;
}

int main(int argc, char *argv[]) {
  const char *input = "input.txt";
  if (argc == 2) {
    input = argv[1];
  } else if (argc != 1) {
    cerr << "Usage: ./a.out [input]" << endl;
    return -1;
  }

  ifstream fin(input);

  uint32_t vertices_count, edges_count, queries_count;
  fin >> vertices_count >> edges_count >> queries_count;

  UndirectedGraph graph(vertices_count);

  uint32_t a, b;
  for (size_t i = 0; i < edges_count; ++i) {
    fin >> a >> b;
    graph.insertEdge(a, b);
  }
  graph.buildBFSTree();

  vector<Query> queries;
  queries.reserve(queries_count);
  for (size_t i = 0; i < queries_count; ++i) {
    fin >> a >> b;
    queries.push_back(Query(a, b));
  }

  vector<uint32_t> results = query_shortest_path_lengths(graph, queries);

  ofstream fout("output.txt");
  for (auto &result : results) {
    fout << result << "\n";
  }
  return 0;
}
