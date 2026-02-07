#include <cassert>
#include <climits>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long n, m;
  cin >> n >> m;
  // n = rows (Y), m = columns (X)

  vector<unsigned char> board(n * m);
  vector<bool> isSpecial(n * m, false);
  vector<std::tuple<int, int, int>> routes(n * m, {0, 0, 0});

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
    long _hadToWalk = 0;
    int shipIndex = toIndex(shipX, shipY);

    // route
    bool previousWasSpecial = isSpecial[shipIndex];
    int currRouteStartX = shipX;
    int currRouteStartY = shipY;
    int currRouteLen = previousWasSpecial ? INT_MIN : 0;
    int currRouteStartIndex = shipIndex;

    while (true) {

      // route load
      auto [endX, endY, len] = routes[shipIndex];
      if (len != 0) {
        moves += len & 0xffff;
        shipX = endX;
        shipY = endY;
        // cout << "cache: saving " << len << " tiles\n";

        if (len > (0x1 << 15)) {
          break;
        }

        // reset current route
        currRouteLen = INT_MIN;
        shipIndex = toIndex(shipX, shipY);

        if (visited[shipIndex]) {
          moves = 0;
          break;
        }
      } else {
        moveShip(shipX, shipY);
        shipIndex = toIndex(shipX, shipY);

        moves++;
        _hadToWalk++;
        currRouteLen++;

        if (shipX < 0 || shipY < 0 || shipX >= m || shipY >= n) {
          // reached edge

          if (currRouteLen > 0) {
            // cout << currRouteStartIndex << "idx\n";
            routes[currRouteStartIndex] = {shipX, shipY,
                                           currRouteLen + (0x1 << 16)};
          }

          break;
        }

        if (visited[shipIndex]) {
          // loop detected,
          // will never reach edge
          moves = 0;

          if (currRouteLen > 0) {
            routes[currRouteStartIndex] = {shipX, shipY, currRouteLen};
          }

          break;
        }

        // route start
        if (previousWasSpecial && !isSpecial[shipIndex]) {
          currRouteStartX = shipX;
          currRouteStartY = shipY;
          currRouteLen = 0;
          currRouteStartIndex = shipIndex;
        } else

          // route store
          if (isSpecial[shipIndex] && currRouteLen > 0) {
            routes[currRouteStartIndex] = {shipX, shipY, currRouteLen};
            currRouteLen = INT_MIN;
          }
      }

      visited[shipIndex] = true;
      previousWasSpecial = isSpecial[shipIndex];
    }

    cout << moves << "\n";

    // restore
    board[toIndex(anomalyX, anomalyY)] = orig;
  }
}
