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

  void buildBFSTree();
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
      int id = -1;
    } parentEdge;

    vector<Vertex *> adjacents;
    friend ostream &operator<<(ostream &stream, const Vertex &vertex) {
      stream << vertex.value << " " << vertex.erdos << " "
             << vertex.parentEdge.id << endl;
      return stream;
    }
  };
  vector<Vertex> vertices_;
};

void UndirectedGraph::buildBFSTree() {
  int id = 0;
  queue<Vertex *> queue;
  queue.push(&this->vertices_[0]);
  this->vertices_[0].erdos = 0;

  while (!queue.empty()) {
    Vertex *u = queue.front();
    queue.pop();
    if (u->parentEdge.parent == nullptr || u->parentEdge.id != -1) {
      for (Vertex *v : u->adjacents) {
        if (v->erdos == -1) {
          v->erdos = u->erdos + 1;
          queue.push(v);
          v->parentEdge.parent = u;
        }
      }
    } else {
      u->parentEdge.id = id;
      id++;
      for (Vertex *v : u->adjacents) {
        if (v->erdos == -1) {
          v->erdos = u->erdos + 1;
          queue.push(v);
          v->parentEdge.parent = u;
        } else if (u->parentEdge.parent == v->parentEdge.parent) {
          v->parentEdge.id = u->parentEdge.id;
        }
      }
    }
  }
}

uint32_t UndirectedGraph::querySPLength(uint32_t vertexA,
                                        uint32_t vertexB) const {
  uint32_t distance = 0;
  const Vertex *a = &this->vertices_[vertexA];
  const Vertex *b = &this->vertices_[vertexB];

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
