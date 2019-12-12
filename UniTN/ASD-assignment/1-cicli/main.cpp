#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
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
  Query(size_t a_start_node_index, size_t a_end_node_index, size_t index)
      : start_node_index{a_start_node_index},
        end_node_index{a_end_node_index},
        original_index{index} {}
  size_t start_node_index;
  size_t end_node_index;
  size_t original_index;

  friend std::ostream &operator<<(std::ostream &stream, const Query &q) {
    stream << q.start_node_index << " " << q.end_node_index;
    return stream;
  }
};

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
    Vertex(uint32_t v = UINT32_MAX) : adjacents({}), value(v) {}
    uint32_t value;
    std::vector<Vertex *> adjacents;
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
  /**
   * @brief Get the adjacents vertices of the given vertex
   */
  const std::vector<Vertex> &vertices() const { return this->vertices_; }
  /**
   * @brief Get the adjacents vertices of the given vertex
   */
  const std::vector<Vertex *> &adjacents(const Vertex &vertex) const {
    return this->vertices_[vertex.value].adjacents;
  }
  /**
   * @brief Get a reference to the vertex at the given @p index
   */
  Vertex &operator[](size_t index) { return this->vertices()[index]; }
  /**
   * @brief Get a const reference to the vertex at the given @p index
   */
  const Vertex &operator[](size_t index) const {
    return this->vertices()[index];
  }
  friend std::ostream &operator<<(std::ostream &stream,
                                  const UndirectedGraph &graph);

 private:
  std::vector<Vertex> vertices_;
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

template <class QueryListIterator>
void bfs(const UndirectedGraph &graph, size_t sourceIndex,
         QueryListIterator start, QueryListIterator end,
         std::vector<uint32_t> &results) {
  using Vertex = UndirectedGraph::Vertex;
  std::map<uint32_t, std::vector<size_t>> queries;
  for (auto i = start; i != end; ++i) {
    queries[i->end_node_index].push_back(i->original_index);
  }

  // std::cout << end - start << ":";

  std::queue<const Vertex *> queue;
  std::vector<bool> visited(graph.vertices().size(), false);
  std::vector<uint32_t> distanceFromSource(graph.vertices().size(), UINT32_MAX);
  distanceFromSource[sourceIndex] = 0;
  queue.push(&graph[sourceIndex]);
  while (!queue.empty()) {
    const Vertex *v = queue.front();
    queue.pop();
    if (!visited[v->value]) {
      visited[v->value] = true;

      for (const Vertex *u : v->adjacents) {
        if (!visited[u->value]) {
          queue.push(u);
          distanceFromSource[u->value] = distanceFromSource[v->value] + 1;

          decltype(queries.begin()) it;
          if ((it = queries.find(v->value)) != queries.end()) {
            results[it->second[0]] = distanceFromSource[v->value];
            if (it->second.size() > 1) {
              results[it->second[1]] = distanceFromSource[v->value];
            }
            queries.erase(it);
            if (queries.size() == 0) {
              return;
            }
          }
        }
      }
    }
  }
}

std::vector<uint32_t> query_shortest_path_lengths(
    const UndirectedGraph &graph, const std::vector<Query> &queries) {
  std::vector<uint32_t> results(queries.size());

  {
    size_t last_source;
    decltype(queries.begin()) start_it;
    for (auto it = queries.begin(); it != queries.end();) {
      last_source = it->start_node_index;
      start_it = it;
      while (it->start_node_index == last_source) {
        it++;
      }
      bfs(graph, last_source, start_it, it, results);
    }
  }

  assert(results.size() == queries.size());
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

  std::vector<Query> queries;
  queries.reserve(queries_count);
  for (size_t i = 0; i < queries_count; ++i) {
    fin >> a >> b;
    queries.push_back(Query(std::min(a, b), std::max(a, b), i));
  }
  std::sort(queries.begin(), queries.end(),
            [](const Query &lhs, const Query &rhs) {
              return lhs.start_node_index < rhs.start_node_index ||
                     (lhs.start_node_index == rhs.start_node_index &&
                      lhs.end_node_index < rhs.end_node_index);
            });
  // for (auto& a: queries) {
  // std::cout << a << "\n";
  //}

  std::vector<uint32_t> results = query_shortest_path_lengths(graph, queries);

  std::ofstream fout("output.txt");
  for (auto &result : results) {
    fout << result << "\n";
  }
  return 0;
}
