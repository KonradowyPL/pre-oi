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
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

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
        cout << "canaccess " << is.x << " " << is.y << "\n";

        if (side) {
          topRightTop = min(topRightTop, is.x);
          topRightRight = min(topRightRight, is.y);
        } else {
          bottomLeftLeft = max(bottomLeftLeft, is.x);
          bottomLeftBottom = max(bottomLeftBottom, is.y);
        }
      } else {
        if (side) {
          topRight.insert(is);
        } else {
          bottomLeft.insert(is);
        }
      }
    }

    cout << topRight.size() << " " << bottomLeft.size() << "\n";
    cout << bottomLeftLeft << " " << bottomLeftBottom << "\n";

    // do {
    //   // copy variables
    //   std::unordered_set<island, wyspaHash> newCantacces;

    //   acc += topLeft.size();

    //   // run logic
    //   for (const auto &is : topLeft) {
    //     // cout << is.x << " " << is.y << "\n";
    //     // cout << "from " << curr.x << " " << curr.y << "\n";
    //     // cout << "leftmost " << LeftMost.x << " " << LeftMost.y << "\n";
    //     // cout << "rightmost " << RightMost.x << " " << RightMost.y << "\n";
    //     // cout << "downmost " << DownMost.x << " " << DownMost.y << "\n";
    //     // cout << "upmose " << UppMost.x << " " << UppMost.y << "\n";

    //     if (canAcces(curr, is) || canAcces(LeftMost, is) ||
    //         canAcces(RightMost, is) || canAcces(UppMost, is) ||
    //         canAcces(DownMost, is)) {
    //       if (is.x < newLeftMost.x)
    //         newLeftMost = is;
    //       if (is.y < newUppMost.y)
    //         newUppMost = is;
    //       if (is.x > newRightMost.x)
    //         newRightMost = is;
    //       if (is.y > newDownMost.y)
    //         newDownMost = is;
    //     } else {
    //       newCantacces.insert(is);
    //     }
    //   }

    //   // set new variables
    //   topLeft = newCantacces;
    //   UppMost = newUppMost;
    //   DownMost = newDownMost;
    //   LeftMost = newLeftMost;
    //   RightMost = newRightMost;
    //   // cout << "running  " << cantacces.size() << " " << depth << "\n";

    // } while (topLeft.size() > 0);

    cout << acc << "\n";
    return 0;
  }
}