#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <ratio>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

constexpr size_t MAX_VERTICES_COUNT = 50000;
constexpr size_t MAX_EDGES_COUNT = 500000;

struct Query {
  Query(size_t a_start_node_index, size_t a_end_node_index)
      : start_node_index(a_start_node_index),
        end_node_index(a_end_node_index),
        original_indexes{-1, -1} {}
  size_t start_node_index;
  size_t end_node_index;
  ssize_t original_indexes[2];
  bool operator<(const Query& rhs) const {
	  return this->start_node_index < rhs.start_node_index;
  }

  friend std::ostream &operator<<(std::ostream &stream, const Query &q) {
    stream << '[' << q.start_node_index << " " << q.end_node_index << ']';
    return stream;
  }
};

using Cycle = std::bitset<20>;

template <typename Func>
void measureTime(const std::string &funName, Func f) {
  auto start = std::chrono::system_clock::now();
  f();
  auto end = std::chrono::system_clock::now();
  std::cout << funName << ": "
            << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                     start)
                   .count()
            << "us\n";
}

class UndirectedGraph {
 public:
  struct Vertex {
    Vertex(uint32_t v = UINT32_MAX)
        : adjacents({}), cycle(NULL), parent(NULL), value(v) {}
    uint32_t value;
    std::vector<Vertex *> adjacents;
    Vertex *parent;
    const Cycle *cycle;
    friend std::ostream &operator<<(std::ostream &stream,
                                    const Vertex &vertex) {
      stream << vertex.value;
      return stream;
    }
  };

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
  std::vector<Vertex> &vertices() { return this->vertices_; }
  std::vector<Vertex *> &adjacents(const Vertex &vertex) {
    return this->vertices_[vertex.value].adjacents;
  }
  const std::vector<Vertex> &vertices() const { return this->vertices_; }
  const std::vector<Vertex *> &adjacents(const Vertex &vertex) const {
    return this->vertices_[vertex.value].adjacents;
  }
  /**
   * @brief For each vertex, it computes to which maximal cycle it belongs
   */
  void computeCycles() {
#if 0
    std::stack<Vertex*> stack;
    std::vector<bool> visited(this->vertices_.size(), false);
    stack.push(&this->vertices()[0]);
    while (!stack.empty()) {
      Vertex* v = stack.top();
      stack.pop();
	  std::cout << *v << "\n";
      if (!visited[v->value]) {
        visited[v->value] = true;
        for (Vertex* adj : v->adjacents) {
          if (!visited[adj->value]) {
            adj->parent = v;
          }
		  stack.push(adj);
        }
      } else {
        this->cycles_.push_back(Cycle());
        Cycle& cycle = cycles_.back();
        Vertex* p = v;
		while (p) {
			cycle.set(p->value);
			p = p->parent;
		}
		std::cout << cycle << std::endl;
      }
    }
#endif
  }
  friend std::ostream &operator<<(std::ostream &stream,
                                  const UndirectedGraph &graph);

 private:
  std::vector<Vertex> vertices_;
  std::vector<Cycle> cycles_;
};

std::ostream &operator<<(std::ostream &stream, const UndirectedGraph &graph) {
  for (auto &n : graph.vertices()) {
    stream << n << ": ";
    for (auto &adj : graph.adjacents(n)) {
      stream << adj->value << " ";
    }
    stream << "\n";
  }
  return stream;
}

uint32_t shortest_distance(const UndirectedGraph &graph,
                           const UndirectedGraph::Vertex &a,
                           const UndirectedGraph::Vertex &b) {
  std::queue<UndirectedGraph::Vertex> vertices;
}

std::vector<uint32_t> query_shortest_path_lengths(
    const UndirectedGraph &graph, const std::vector<Query> &queries) {
  std::vector<uint32_t> results;
  results.reserve(queries.size());

  // assert(results.size() == queries.size());
  return results;
}

int main(int argc, char *argv[]) {
  const char *input = "input.txt";
  if (argc == 2) {
    input = argv[1];
  } else if (argc != 1) {
    std::cerr << "Usage: ./a.out [input]" << std::endl;
    return -1;
  }

  std::fstream fin(input);

  uint32_t vertices_count, edges_count, queries_count;
  fin >> vertices_count >> edges_count >> queries_count;

  UndirectedGraph graph(vertices_count);

  uint32_t a, b;
  for (size_t i = 0; i < edges_count; ++i) {
    fin >> a >> b;
    graph.insertEdge(a, b);
  }

  std::map<Query, std::vector<ssize_t>> queries;
  // std::vector<Query> queries;
  measureTime("Query insertion + sort", [queries_count, &fin, &queries]() {
    uint32_t a, b;
    for (size_t i = 0; i < queries_count; ++i) {
      fin >> a >> b;
	  queries[Query(std::min(a, b), std::max(a, b))].push_back(i);
      // queries.push_back(Query(a, b));
    }
    //std::sort(queries.begin(), queries.end(),
              //[](const Query &lhs, const Query &rhs) {
                //return lhs.start_node_index < rhs.start_node_index;
              //});
  });

  //std::vector<uint32_t> results = query_shortest_path_lengths(graph, queries);

  // std::ofstream fout("output.txt");
  // for (auto& result : results) {
  // fout << result << "\n";
  //}
  return 0;
}
