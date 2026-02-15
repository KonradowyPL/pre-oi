#include <cassert>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// tree const: (2 ^ (n + 1) - 1) * n => n * 2 ^ n
// single quest: avg n, max 2^n

auto getParent = [](long index) -> long { return (index - 1) / 2; };
auto getLeft = [](long index) -> long { return 2 * index + 1; };
auto getRight = [](long index) -> long { return 2 * index + 2; };
auto getLeaf = [](long index, int n) -> long { return pow(2, n) - 1 + index; };

bool solve(long indexA, long indexB, const vector<vector<long>> &currTree,
           const vector<vector<long>> &preTree) {

  if (indexA >= currTree.size() || indexB >= preTree.size())
    return true;

  auto a = currTree[indexA];
  auto b = preTree[indexB];
  if (a != b) {
    return false;
  }

  return solve(getLeft(indexA), getLeft(indexB), currTree, preTree) ||
         solve(getLeft(indexA), getRight(indexB), currTree, preTree);
}

int main() {
  int n;
  long q;
  cin >> n >> q;

  std::string currNaz;
  cin >> currNaz;

  std::string preNaz;
  cin >> preNaz;

  // 2 ^ (n + 1) - 1
  long treeSize = pow(2, n + 1) - 1;

  vector<vector<long>> currTree(treeSize, std::vector<long>(26, 0));
  vector<vector<long>> preTree(treeSize, std::vector<long>(26, 0));

  // construct tree
  for (long i = 0; i < currNaz.size(); i++) {
    unsigned char c = currNaz[i];
    long index = getLeaf(i, n);
    for (int j = 0; j <= n; j++) {
      currTree[index][c - 97]++;
      index = getParent(index);
    }
  }
  // construct second
  for (long i = 0; i < preNaz.size(); i++) {
    unsigned char c = preNaz[i];
    long index = getLeaf(i, n);
    for (int j = 0; j <= n; j++) {
      preTree[index][c - 97]++;
      index = getParent(index);
    }
  }

  auto r = solve(0, 0, currTree, preTree);
  if (r) {
    cout << "TAK\n";
  } else {
    cout << "NIE\n";
  }

  while (q--) {
    long t, k;
    cin >> t >> k;
    k--; // to 0 indexed
    char c;
    cin >> c;
    if (t == 1) {
      auto index = getLeaf(k, n);
      auto origChar = currNaz[k];
      currNaz[k] = c;

      for (int j = 0; j <= n; j++) {
        currTree[index][c - 97]++;
        currTree[index][origChar - 97]--;
        index = getParent(index);
      }
    } else {
      auto index = getLeaf(k, n);
      auto origChar = preNaz[k];
      preNaz[k] = c;

      for (int j = 0; j <= n; j++) {
        preTree[index][c - 97]++;
        preTree[index][origChar - 97]--;
        index = getParent(index);
      }
    }
    auto r = solve(0, 0, currTree, preTree);
    if (r) {
      cout << "TAK\n";
    } else {
      cout << "NIE\n";
    }
  }
}