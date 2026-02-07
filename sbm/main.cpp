#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  long n, m;
  cin >> n >> m;
  // n = rows (Y), m = columns (X)

  vector<unsigned char> board(n * m);

  // read board
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      cin >> board[y * m + x];
    }
  }

  long q;
  cin >> q;

  while (q--) {
    int shipX, shipY, anomalyX, anomalyY;
    char chr;
    cin >> shipX >> shipY >> anomalyX >> anomalyY >> chr;

    // to 0-index
    shipX--;
    shipY--;
    anomalyX--;
    anomalyY--;

    unsigned char orig = board[anomalyY * m + anomalyX];
    board[anomalyY * m + anomalyX] = chr;

    vector<bool> visited(n * m, false);
    visited[shipY * m + shipX] = true;

    long moves = 0;

    while (true) {
      moves++;
      char vec = board[shipY * m + shipX];
      cout << shipX << " " << shipY << " " << vec << "\n";
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
      default:
        assert(false);
      }

      if (shipX < 0 || shipY < 0 || shipX >= m || shipY >= n ||
          visited[shipY * m + shipX]) {
        break;
      }

      visited[shipY * m + shipX] = true;
    }

    cout << moves << "\n";

    // restore
    board[anomalyY * m + anomalyX] = orig;
  }
}
