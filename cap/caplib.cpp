#include "caplib.h"

#ifdef __PASSWORD
#include "password.h"
#endif

#include <iostream>
#include <vector>

namespace __judge {

struct Tree {
  int n;
  std::vector<std::vector<int>> adj;
  std::vector<std::pair<int, int>> edges;
  std::vector<int> parent;
  std::vector<int> tin, tout;
  int timer;

  Tree() {}
  Tree(int _n)
      : n(_n), adj(n + 1), parent(n + 1, -1), tin(n + 1), tout(n + 1),
        timer(0) {}

  void add_edge(int u, int v) {
    edges.emplace_back(u, v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void dfs(int u, int p) {
    parent[u] = p;
    tin[u] = timer++;
    for (int v : adj[u]) {
      if (v != p) {
        dfs(v, u);
      }
    }
    tout[u] = timer;
  }

  void build() { dfs(1, -1); }

  bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
  }
};

void fail(std::string message) {
#ifdef __PASSWORD
  std::cout << PASSWORD << std::endl;
#endif
  std::cout << "WA" << std::endl;
  std::cout << message << std::endl;
  exit(0);
}

constexpr int MAX_QUERIES = 1000;

Tree tree;
int n, query = 0, capek_position = -1;

}; // namespace __judge

bool zapytaj(int x) {
  // std::cerr << "ZAPYTAJ " << x << std::endl;
  if (x < 1 || x > __judge::n)
    __judge::fail("Query value outside of range [1, n]");
  if (++__judge::query > __judge::MAX_QUERIES)
    __judge::fail("Too many queries");
  bool result = __judge::tree.is_ancestor(x, __judge::capek_position);
  if (!result) {
    if (__judge::capek_position != 1 &&
        __judge::tree.parent[__judge::capek_position] != -1) {
      __judge::capek_position = __judge::tree.parent[__judge::capek_position];
    }
  }
  return result;
}

int main() {
  int t;
  std::cin >> t;

  int max_queries_used = 0;

  for (int test = 0; test < t; test++) {
    std::cin >> __judge::n >> __judge::capek_position;

    __judge::tree = __judge::Tree(__judge::n);

    for (int i = 0; i < __judge::n - 1; i++) {
      int u, v;
      std::cin >> u >> v;
      __judge::tree.add_edge(u, v);
    }

    __judge::tree.build();

    __judge::query = 0;

    int x = znajdz_capka(__judge::n, __judge::tree.edges);
    // std::cerr << "ZWROCONO " << x << std::endl;

    if (x != __judge::capek_position)
      __judge::fail("Wrong Capek position guessed");
    max_queries_used = std::max(max_queries_used, __judge::query);
  }

#ifdef __PASSWORD
  std::cout << PASSWORD << std::endl;
#endif
  std::cout << "OK" << std::endl;
  std::cout << max_queries_used << std::endl;

  return 0;
}
