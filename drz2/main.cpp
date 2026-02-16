#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

auto getParent = [](long index) -> long { return (index - 1) / 2; };
auto getLeft = [](long index) -> long { return 2 * index + 1; };
auto getRight = [](long index) -> long { return 2 * index + 2; };
auto getLeaf = [](long index, int n) -> long { return (1L << n) - 1 + index; };

bool solve(long indexA, long indexB, const vector<array<int, 26>> &currTree,
           const vector<array<int, 26>> &preTree) {

  if (indexA >= currTree.size() || indexB >= preTree.size())
    return true;

  auto a = currTree[indexA];
  auto b = preTree[indexB];
  if (a != b) {
    return false;
  }
  return (
             // check normal
             solve(getLeft(indexA), getLeft(indexB), currTree, preTree) &&
             solve(getRight(indexA), getRight(indexB), currTree, preTree)) ||
         //  check swapped
         (solve(getLeft(indexA), getRight(indexB), currTree, preTree) &&
          solve(getRight(indexA), getLeft(indexB), currTree, preTree));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  long q;
  cin >> n >> q;

  std::string currNaz;
  cin >> currNaz;

  std::string preNaz;
  cin >> preNaz;

  // 2 ^ (n + 1) - 1
  long treeSize = (1L << (n + 1)) - 1;
  cout << "size " << treeSize << "\n";

  vector<array<int, 26>> currTree(treeSize);
  vector<array<int, 26>> preTree(treeSize);

  // construct trees
  for (long i = 0; i < preNaz.size(); i++) {
    unsigned char c1 = currNaz[i];
    unsigned char c2 = preNaz[i];
    long index = getLeaf(i, n);
    for (int j = 0; j <= n; j++) {
      currTree[index][c1 - 97]++;
      preTree[index][c2 - 97]++;
      cout << "index " << index << "\n";
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
    unsigned char c;
    cin >> c;
    if (t == 1) {
      // changing curr
      auto index = getLeaf(k, n);
      auto origChar = currNaz[k];
      currNaz[k] = c;

      for (int j = 0; j <= n; j++) {
        currTree[index][c - 97]++;
        currTree[index][origChar - 97]--;
        index = getParent(index);
      }
    } else {
      // t == 2; changing pre
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