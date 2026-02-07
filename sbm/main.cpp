#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  long n, m;
  cin >> n >> m;
  // n = rows (Y), m = columns (X)

  vector<unsigned char> board(n * m);

  const auto toIndex = [&](int x, int y) -> int { return y * m + x; };
  const auto moveShip = [&](int &shipX, int &shipY) -> void { 
    char vec = board[toIndex(shipX, shipY)];
    // cout << shipX << " " << shipY << " " << vec << "\n";
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
   };

  // read board
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      cin >> board[toIndex(x, y)];
    }
  }

  long q;
  cin >> q;

  while (q--) {
    int shipX, shipY, anomalyX, anomalyY;
    char chr;
    cin >> shipY >> shipX >> anomalyY >> anomalyX >> chr;

    // to 0-index
    shipX--;
    shipY--;
    anomalyX--;
    anomalyY--;

    unsigned char orig = board[toIndex(anomalyX, anomalyY)];
    board[toIndex(anomalyX, anomalyY)] = chr;

    vector<bool> visited(n * m, false);
    visited[toIndex(shipX, shipY)] = true;

    long moves = 0;

    while (true) {
      moves++;
      moveShip(shipX, shipY);

      if (shipX < 0 || shipY < 0 || shipX >= m || shipY >= n) {
        break;
      } 
      if (visited[toIndex(shipX, shipY)])  {
        moves = 0;
        break;
      }

      visited[toIndex(shipX, shipY)] = true;
    }

    cout << moves << "\n";

    // restore
    board[toIndex(anomalyX, anomalyY)] = orig;
  }
}
