#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

int main() {
  long n, m;
  cin >> n >> m;
  // n = rows (Y), m = columns (X)

  vector<unsigned char> board(n * m);
  vector<bool> isSpecial(n * m, false);
  vector<std::tuple<int, int, int>> routes(n * m, {0, 0, 0});

  const auto toIndex = [&](int x, int y) -> int { return y * m + x; };
  const auto shapeToBit = [&](const char &shape) -> int {
    switch (shape) {
    case '^':
      return 1;
      break;
    case 'v':
      return 2;
      break;
    case '>':
      return 4;
      break;
    case '<':
      return 8;
      break;
    default:
      assert(false);
    }
  };
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
      unsigned char c;
      cin >> c;
      board[toIndex(x, y)] = c;
    }
  }

  long q;
  cin >> q;
  std::vector<std::tuple<int, int, int, int, char>> questions(q);

  for (int i = 0; i < q; i++) {
    int shipX, shipY, anomalyX, anomalyY;
    char chr;
    cin >> shipY >> shipX >> anomalyY >> anomalyX >> chr;

    // to 0-index
    shipX--;
    shipY--;
    anomalyX--;
    anomalyY--;
    questions[i] = {shipX, shipY, anomalyX, anomalyY, chr};
    isSpecial[toIndex(anomalyX, anomalyY)] = true;
    isSpecial[toIndex(shipX, shipY)] = true;
  }

  for (int i = 0; i < q; i++) {
    auto [shipX, shipY, anomalyX, anomalyY, chr] = questions[i];

    unsigned char orig = board[toIndex(anomalyX, anomalyY)];
    board[toIndex(anomalyX, anomalyY)] = chr;

    vector<bool> visited(n * m, false);
    visited[toIndex(shipX, shipY)] = true;

    long moves = 0;

    // route
    int currRouteStartX = shipX;
    int currRouteStartY = shipY;
    int currRouteLen = 0;

    while (true) {

      // route load
      auto [endX, endY, len] = routes[toIndex(shipX, shipY)];
      if (len != 0) {
          moves += len;
          shipX = endX;
          shipY = endY;
          // reset current route
          currRouteStartX = shipX;
          currRouteStartY = shipY;
          currRouteLen = 0;
      } else {
        moveShip(shipX, shipY);
        moves++;
        currRouteLen++;
      }


      if (shipX < 0 || shipY < 0 || shipX >= m || shipY >= n) {
        break;
      }
      if (visited[toIndex(shipX, shipY)]) {
        moves = 0;
        break;
      }

      if ((currRouteLen > 32 || isSpecial[toIndex(shipX, shipY)]) && len == 0) {
        // cache current route
        routes[toIndex(currRouteStartX, currRouteStartY)] = {shipX, shipY, currRouteLen};
        currRouteStartX = shipX;
        currRouteStartY = shipY;
        currRouteLen = 0;
      }

  
      visited[toIndex(shipX, shipY)] = true;
    }

    cout << moves << "\n";

    // restore
    board[toIndex(anomalyX, anomalyY)] = orig;
  }
}
