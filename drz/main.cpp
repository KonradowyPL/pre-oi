#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  long Z;
  cin >> Z;

  while (Z--) {
    int N;
    cin >> N;

    int V = 2 * N;

    // construct tree
    // node index -> [] of all node inexes it connects to
    vector<vector<int>> adj(V + 1);
    // node index -> color (index)
    vector<int> color(V + 1);

    for (int i = 0; i < V - 1; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    // assing colors
    for (int c = 1; c <= N; c++) {
      int a, b;
      cin >> a >> b;
      color[a] = c;
      color[b] = c;
    }

    // count ammonut of edges node connects to
    vector<int> degree(2 * N + 1);
    for (int i = 1; i <= 2 * N; i++) {
      degree[i] = adj[i].size();
    }

    vector<int> colorCount(N + 1, 2);
    vector<bool> removed(2 * N + 1, false); // flags removed verts
    int removedCount = 0;

    queue<int> queue;
    for (int i = 1; i <= 2 * N; i++) {
      if (degree[i] == 1) {
        queue.push(i);
      }
    }

    while (!queue.empty()) {
      int ele = queue.front();
      int nodeColor = color[ele];
      queue.pop();

      // allready deleted
      if (removed[ele]) {
        continue;
      }

      // can't delete
      if (colorCount[nodeColor] == 1) {
        continue;
      }

      // remove self
      colorCount[nodeColor]--;
      removed[ele] = true;
      removedCount++;

      for (int node : adj[ele]) {
        degree[node]--;
        if (!removed[node] && degree[node] == 1) {
          // schedule for deletion
          queue.push(node);
        }
      }
    }

    if (removedCount == N) {
      cout << "TAK\n";
      for (int i = 1; i <= 2 * N; i++) {
        cout << (removed[i] ? "0" : "1") << " ";
      }
      cout << "\n";
    } else {
      cout << "NIE\n";
    }

  }
}