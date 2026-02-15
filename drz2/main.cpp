#include <cassert>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

auto getParent = [](long index) -> long { return (index - 1) / 2; };
auto getLeft = [](long index) -> long { return 2 * index + 1; };
auto getRight = [](long index) -> long { return 2 * index + 2; };
auto getLeaf = [](long index, int n) -> long { return pow(2, n) - 1 + index; };

bool solve() {}

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
    cout << "leaf index " << index << ":\n";
    currTree[index][c - 97]++;
    for (int j = 0; j < n; j++) {
      index = getParent(index);
      currTree[index][c - 97]++;
      cout << "index " << index << "\n";
    }
  }
  cout << "second:\n";
  // construct second
  for (long i = 0; i < preNaz.size(); i++) {
    unsigned char c = preNaz[i];
    long index = getLeaf(i, n);
    cout << "leaf index " << index << ":\n";
    preTree[index][c - 97]++;
    for (int j = 0; j < n; j++) {
      index = getParent(index);
      preTree[index][c - 97]++;
      cout << "index " << index << "\n";
    }
  }
}