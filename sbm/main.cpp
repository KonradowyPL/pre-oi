#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long n, m;
  cin >> n >> m;

  vector<unsigned char> board(n * m);
  // board has: x [0, n]
  //            y [0, m]

  // read board
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      unsigned char c;
      cin >> c;
      board[i * m + j] = c;
    }
  }

  long q;
  cin >> q;
  cout << "q is" << q << "\n";

  while (q--) {
    cout << "HERE!";
    int shipX, shipY, anomalyX, anomalyY;
    char chr;
    cin >> shipX >> shipY >> anomalyX >> anomalyY >> chr;
    cout << "before: " << shipX << " " << shipY << " " << anomalyX << " "
         << anomalyY << "\n";

    // make 0-indexed instead of 1-indexed
    shipX--;
    shipY--;
    anomalyX--;
    anomalyY--;
    cout << shipX << " " << shipY << " " << anomalyX << " " << anomalyY << "\n";

    const char unsigned orig = board[anomalyX * n + anomalyY];

    board[anomalyX * n + anomalyY] = chr;
    vector<bool> visited(n * m, 0);
    visited[shipX * n + shipY] = true;
    long moves = 0;
    while (1) {
      moves++;
      auto vec = board[shipX * m + shipY];
      switch (vec) {
      case '^':
        shipY--;
        break;
      case 'v':
        shipY++;
        break;
      case '>':
        shipX++;
        break;
      case '<':
        shipX--;
        break;
      }

      if (shipY < 0 || shipX < 0 || shipX >= n || shipY >= m ||
          visited[shipX * n + shipY]) {
        break;
      }
      visited[shipX * n + shipY] = true;
    }

    cout << "HER2E!";
    cout << moves << "\n";
    // restore
    board[anomalyX * n + anomalyY] = orig;
    cout << "HER3E!";
  }
}