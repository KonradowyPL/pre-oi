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

      for (auto road : zamki[node].connected) {
        if (road.dist != parent) {
          self(self, road.dist, node, depth + road.len);
        }
      }
    };
    initTree(initTree, 1, -1, 0);

    // sort leaves by depth (this obviously breaks ordering, but who cares)
    std::sort(zamki.begin(), zamki.end(),
              [](auto a, auto b) -> bool { return a.depth > b.depth; });

    for (auto z : zamki) {
      cout << z.depth << "\n";
    }
    cout << "\n";

    vector<long> prefixes(N + 1, 0);

    // prefixes[0] will allways be 0!
    for (int i = 1; i < N + 1; i++) {
      prefixes[i] = prefixes[i - 1] + zamki[i - 1].depth;
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
      long k = 1;
      while (zamki[k].depth > P) {
        k++;
      }
      k--;

      cout << "k = " << k << "\n";

      long result = (k - 1) * P + 2 * S - prefixes[k];

      cout << "res " << result << "\n";
    }

    return 0;
  }
}