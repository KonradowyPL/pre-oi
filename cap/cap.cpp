#include <iostream>
#include <vector>

#include "caplib.h"

using namespace std;

struct Node {
  std::vector<int> connected;
  int capki;    // statistical amount of capeks on this node
  int childSum; // amount of children nodes
  int parent;   // index of parent node
  int original;   // original index of node
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
    tree[node].childSum = 1; // 1 since it includes self
    tree[node].parent = parent;
    tree[node].original = node;

    // remove parent
    tree[node].connected.erase(std::remove(tree[node].connected.begin(),
                                           tree[node].connected.end(), parent),
                               tree[node].connected.end());

    for (auto child : tree[node].connected) {
      // Assumes tree does not contain any loops
      tree[node].childSum += self(self, child, node);
    }
    return tree[node].childSum;
  };

  initTree(initTree, 1, -1);

  cout << "root has " << tree[1].childSum << "\n";

  for (auto child : tree[1].connected) {
    cout << "child " << child << " has " << tree[child].childSum << "\n";
  }

  while (tree[1].childSum != 1) 
  {

    long long total = tree[1].childSum;

    long long highestScore = 0;
    int highestScoreNode = 0;

    auto prepareQuestion = [&](auto &&self, int node) -> void {
      if (tree[node].childSum == 0) {
        return;
      }

      long long cs = tree[node].childSum;

      long long ifTrue = total - cs;
      long long ifFalse = cs;

      long long score = ifTrue * cs + ifFalse * (total - cs);

      if (score > highestScore) {
        highestScore = score;
        highestScoreNode = node;
      }

      for (auto child : tree[node].connected) {
        if (child != tree[node].parent) {
          self(self, child);
        }
      }
    };

    prepareQuestion(prepareQuestion, 1);

    cout << "highest score " << highestScore << " node: " << highestScoreNode
         << "\n";

    bool succes = zapytaj(highestScoreNode);
    cout << "result: " << succes << "\n";

    if (succes) {
      // root node is now that node
      tree[1] = tree[highestScoreNode];
    } else {
        zapytaj(-1);
    }
  }

  return tree[1].original;
}
