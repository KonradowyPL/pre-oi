#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

struct Road {
  long len;
  long dist;
};

struct Zamek {
  std::vector<Road> connected;
  long depth;
  long parent;
};

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long T;
  cin >> T;

  while (T--) {
    long N;
    cin >> N;

    vector<Zamek> zamki(N + 1);
    vector<long long> leaves;

    long S = 0;

    for (int i = 0; i < N - 1; i++) {
      long a, b, l;
      cin >> a >> b >> l;
      S += l;
      zamki[a].connected.push_back({l, b});
      zamki[b].connected.push_back({l, a});
    }

    auto initTree = [&](auto &&self, int node, int parent, int depth) -> void {
      zamki[node].parent = parent;
      zamki[node].depth = depth;

      bool isLeaf = true;

      for (auto road : zamki[node].connected) {
        if (road.dist != parent) {
          self(self, road.dist, node, depth + road.len);
          isLeaf = false;
        }
      }
      if (isLeaf)
        leaves.push_back(depth);
    };
    initTree(initTree, 1, -1, 0);

    // sort leaves by depth
    sort(leaves.begin(), leaves.end(), greater<>());

    for (auto z : zamki) {
      cout << z.depth << "\n";
    }
    cout << "\n";

    vector<long> prefixes(leaves.size() + 1, 0);

    // prefixes[0] will allways be 0!
    for (int i = 1; i <= leaves.size(); i++) {
      prefixes[i] = prefixes[i - 1] + leaves[i - 1];
    }

    for (auto z : prefixes) {
      cout << z << "\n";
    }
    cout << "\n";

    long Q;
    cin >> Q;
    while (Q--) {
      long P;
      cin >> P;

      // TODO: binary search
      int k =
          upper_bound(leaves.begin(), leaves.end(), P, greater<long long>()) -
          leaves.begin();

      cout << "k = " << k << "\n";

      long result = (k - 1) * P + 2 * S - prefixes[k];

      cout << "res " << result << "\n";
    }

    cout << "\n\n";
  }
}