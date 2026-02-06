#include <iostream>
#include <vector>

#include "caplib.h"

using namespace std;

struct Zamek {
  std::vector<int> connected;
  int capki;    // amount of capkis on self
  int childSum; // sum of capkis on self and children
  int parent;   // index of parent node
};

// void printTree(const std::vector<Node> &tree, int node,
//                const std::string &prefix = "", bool isLast = true) {
//   std::cout << prefix;

//   if (tree[node].parent != -1) {
//     std::cout << (isLast ? "└── " : "├── ");
//   }

//   std::cout << node << " (capki=" << tree[node].capki
//             << ", sum=" << tree[node].childSum
//             << ", parent=" << tree[node].parent << ")\n";

//   std::string newPrefix = prefix;
//   if (tree[node].parent != -1) {
//     newPrefix += (isLast ? "    " : "│   ");
//   }

//   for (size_t i = 0; i < tree[node].connected.size(); ++i) {
//     int child = tree[node].connected[i];
//     bool lastChild = (i + 1 == tree[node].connected.size());
//     printTree(tree, child, newPrefix, lastChild);
//   }
// }

int znajdz_capka(int n, std::vector<std::pair<int, int>> gałęzie) {
  std::vector<Zamek> tree(n + 1);

  // construct tree
  for (int i = 0; i < n - 1; i++) {
    auto [a, b] = gałęzie[i];
    tree[a].connected.push_back(b);
    tree[b].connected.push_back(a);
  }

  auto initTree = [&](auto &&self, int node, int parent) -> int {
    tree[node].capki = 1;
    tree[node].childSum = 1; // 1 since it includes self
    tree[node].parent = parent;

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

  initTree(initTree, 1, 0);

  int TREE_ROOT = 1;

  while (tree[TREE_ROOT].childSum != tree[TREE_ROOT].capki) {
    // printTree(tree, TREE_ROOT);

    long long total = tree[TREE_ROOT].childSum;

    long long highestScore = -1;
    int highestScoreNode = TREE_ROOT;

    auto prepareQuestion = [&](auto &&self, int node) -> void {
      if (tree[node].childSum <= 0) {
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
        self(self, child);
      }
    };

    prepareQuestion(prepareQuestion, TREE_ROOT);

    // cout << "highest score " << highestScore << " node: " << highestScoreNode
    // << "\n";

    if (highestScoreNode == TREE_ROOT) {
      break; // possibly infinite loop
    }

    bool succes = zapytaj(highestScoreNode);
    // cout << "result: " << succes << "\n";

    if (succes) {
      // root node is now that node
      TREE_ROOT = highestScoreNode;
      //   cout << "tree root is now " << TREE_ROOT << "\n";
    } else {
      // remove branch

      long capkis = tree[highestScoreNode].childSum;
      tree[highestScoreNode].capki = 0;
      
      while (highestScoreNode != TREE_ROOT && highestScoreNode) {
        tree[highestScoreNode].childSum -= capkis;
        highestScoreNode = tree[highestScoreNode].parent;
      }

      tree[highestScoreNode].childSum -= capkis;

      tree[tree[TREE_ROOT].parent].capki = 0;
      tree[tree[TREE_ROOT].parent].childSum = tree[TREE_ROOT].childSum;
      //   cout << "after branch deletion:\n";
      //   printTree(tree, TREE_ROOT);

      //   move all capkis to parent
      auto moveDown = [&](auto &&self, int node) -> void {
        if (tree[node].childSum <= 0) {
          return;
        }

        if (node != 1) {
          tree[tree[node].parent].capki += tree[node].capki;
          tree[node].childSum -= tree[node].capki;
          tree[node].capki = 0;
        }

        for (auto child : tree[node].connected) {
          self(self, child);
        }
      };

      moveDown(moveDown, TREE_ROOT);



      int newRoot = tree[TREE_ROOT].parent;
      if (newRoot == 0) {
        continue;
      }
      for (auto child : tree[newRoot].connected) {
        if (child != TREE_ROOT) {
          tree[child].capki = 0;
          tree[child].childSum = 0;
        }
      }

      // move tree root 1 down
      TREE_ROOT = newRoot;
      //   cout << "tree root is now " << TREE_ROOT << "\n";
    }
  }

  //   cout << "IS IN " << TREE_ROOT << "\n";
  return TREE_ROOT;
}
