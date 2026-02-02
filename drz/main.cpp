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
    // // node index -> [] of all node inexes it connects to
    vector<vector<int>> adj(V + 1);
    // node index -> color (index)
    vector<int> color(V + 1);
    // color * 2 -> first node
    // color * 2  + 1-> second node
    vector<int> colorMap(V + 2);

    vector<int> colorCount(N + 1, 2);

    // construct tree
    for (int i = 0; i < V - 1; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    // assign colors
    for (int c = 1; c <= N; c++) {
      int a, b;
      cin >> a >> b;
      color[a] = c;
      color[b] = c;

      colorMap[c * 2] = a;
      colorMap[c * 2 + 1] = b;
    }

    vector<int> degree(V + 1);
    for (int i = 1; i <= V; i++) {
      degree[i] = adj[i].size();
    }

    vector<bool> removed(V + 1, false);
    int removedCount = 0;

    queue<int> q;

    for (int i = 1; i <= V; i++) {
      if (degree[i] == 1 && colorCount[color[i]] > 1) {
        q.push(i);
      }
    }

    while (!q.empty()) {
      int element = q.front();
      q.pop();

      // allready deleted
      if (removed[element])
        continue;
      // not a leaf
      if (degree[element] != 1)
        continue;

      int c = color[element];
      // second from pair has been allready deleted
      if (colorCount[c] == 1)
        continue;

      removed[element] = true;
      removedCount++;
      colorCount[c]--;

      int other;
      if (colorMap[c * 2] == element) {
        other = colorMap[c * 2 + 1];
      } else {
        other = colorMap[c * 2];
      }

      if (!removed[other] && degree[other] == 1) {
        q.push(other);
      }

      for (int u : adj[element]) {
        if (removed[u])
          continue;
        degree[u]--;
        if (degree[u] == 1 && colorCount[color[u]] > 1) {
          q.push(u);
        }
      }
    }

    if (removedCount == N) {
      cout << "TAK\n";
      for (int i = 1; i <= V; i++) {
        cout << (removed[i] ? "0 " : "1 ");
      }
      cout << "\n";
    } else {
      cout << "NIE\n";
    }
  }
}