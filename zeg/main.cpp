#include <cassert>
#include <iostream>
#include <unordered_set>
using namespace std;

struct island {
  long x;
  long y;

  bool operator==(const island &p) const { return x == p.x && y == p.y; }
};

struct wyspaHash {
  std::size_t operator()(const island &p) const {
    return std::hash<long>()(p.x) ^ (std::hash<long>()(p.y) << 8);
  }
};

inline const bool canAcces(const island &A, const island &B) {
  return (A.x < B.x && A.y < B.y) || (A.x > B.x && A.y > B.y);
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long n;
  cin >> n;
  cin.ignore();

  island islands[n];
  int sortLen = sizeof(islands) / sizeof(islands[0]);

  for (long i = 0; i < n; i++) {
    long x, y;
    cin >> x >> y;
    cin.ignore();
    islands[i] = {x, y};
  }

  for (long i = 0; i < n; i++) {
    island curr = islands[i];
    cout << "curr " << curr.x << " " << curr.y << "\n";
    int acc = n - 1;
    long currEnergy = curr.x - curr.y;

    std::unordered_set<island, wyspaHash> topRight;
    std::unordered_set<island, wyspaHash> bottomLeft;

    long topRightTop = curr.y;
    long topRightRight = curr.x;

    long bottomLeftBottom = curr.y;
    long bottomLeftLeft = curr.x;

    for (long j = 0; j < n; j++) {

      if (j == i)
        continue;
      island is = islands[j];
      long energy = is.x - is.y;
      bool side = energy < currEnergy;

      if (canAcces(curr, is)) {
        // cout << "canaccess " << is.x << " " << is.y << "\n";

        topRightRight = max(topRightRight, is.x);
        topRightTop = min(topRightTop, is.y);

        bottomLeftLeft = max(bottomLeftLeft, is.x);
        bottomLeftBottom = min(bottomLeftBottom, is.y);
      } else {
        if (side) {
          topRight.insert(is);
        } else {
          bottomLeft.insert(is);
        }
      }
    }

    // cout << topRight.size() << " " << bottomLeft.size() << "\n";
    // cout << "bonuds " << bottomLeftLeft << " " << bottomLeftBottom << "\n";

    // BOTTOM LEFT LOOP
    do {

      long newBottomLeftBottom = bottomLeftBottom;
      long newBottomLeftLeft = bottomLeftLeft;
      acc += bottomLeft.size();

      // bottomLeft calculations
      for (auto it = bottomLeft.begin(); it != bottomLeft.end();) {
        auto is = *it;
        if (is.x < bottomLeftLeft || is.y > bottomLeftBottom) {
          // cout << "new acc " << is.x << " " << is.y << "\n";

          newBottomLeftLeft = max(newBottomLeftLeft, is.x);
          newBottomLeftBottom = min(newBottomLeftBottom, is.y);
          // cout << "bounds " << bottomLeftLeft << " " << bottomLeftBottom
          //      << "\n";

          it = bottomLeft.erase(it);
        } else {
          it++;
        }
      }

      bottomLeftBottom = newBottomLeftBottom;
      bottomLeftLeft = newBottomLeftLeft;
      // cout << "iteration\n";

    } while (bottomLeft.size() > 0);

    // TOP RIGHT LOOP
    do {

      long newTopRightTop = topRightTop;
      long newTopRightRight = topRightRight;
      acc += topRight.size();

      // topRight calculations
      for (auto it = topRight.begin(); it != topRight.end();) {
        auto is = *it;
        if (is.x < topRightRight || is.y > topRightTop) {
          // cout << "new acc " << is.x << " " << is.y << "\n";

          newTopRightRight = max(newTopRightRight, is.x);
          newTopRightTop = min(newTopRightTop, is.y);

          it = topRight.erase(it);
        } else {
          it++;
        }
      }

      topRightTop = newTopRightTop;
      topRightRight = newTopRightRight;

    } while (topRight.size() > 0);


    cout << acc << "\n";
  }
}