#include <vector>

#include "caplib.h"

using namespace std;

struct Node {
  std::vector<int> connected;
  int capki;    // statistical amount of capeks on this node
  int childSum; // amount of children nodes
  int parent; // index of parent node
};

int znajdz_capka(int n, std::vector<std::pair<int, int>> gałęzie) {
  std::vector<Node> tree(n + 1);

  // construct tree
  for (int i = 0; i < n; i++) {
    auto [a, b] = gałęzie[i];
    tree[a].connected.push_back(b);
    tree[b].connected.push_back(a);
  }

  auto initTree = [&](auto &&self, int node, int parent) -> int {
    tree[node].capki = 1;
    tree[node].childSum = 0;
    tree[node].parent = parent;

    for (auto child : tree[node].connected) {
        if (child != parent) {
            tree[node].childSum += self(self, child, node);
        }
    }
    return tree[node].childSum;
  };

  initTree(initTree, 1, -1);


  

  return -1;
}
