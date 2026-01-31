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
    int acc = n - 1;
    int depth = 1;

    island LeftMost = curr;
    island RightMost = curr;
    island UppMost = curr;
    island DownMost = curr;

    std::unordered_set<island, wyspaHash> cantacces;

    for (long j = 0; j < n; j++) {
      if (j == i)
        continue;
      island is = islands[j];
      if (canAcces(curr, is)) {
        if (is.x < LeftMost.x)
          LeftMost = is;
        if (is.y < UppMost.y)
          UppMost = is;
        if (is.x > RightMost.x)
          RightMost = is;
        if (is.y > DownMost.y)
          DownMost = is;
      } else {
        cantacces.insert(is);
      }
    }

    do {
      // copy variables
      std::unordered_set<island, wyspaHash> newCantacces;
      island newLeftMost = LeftMost;
      island newRightMost = RightMost;
      island newUppMost = UppMost;
      island newDownMost = DownMost;

      acc += cantacces.size();
      depth++;

      // run logic
      for (const auto &is : cantacces) {
        // cout << is.x << " " << is.y << "\n";
        // cout << "from " << curr.x << " " << curr.y << "\n";
        // cout << "leftmost " << LeftMost.x << " " << LeftMost.y << "\n";
        // cout << "rightmost " << RightMost.x << " " << RightMost.y << "\n";
        // cout << "downmost " << DownMost.x << " " << DownMost.y << "\n";
        // cout << "upmose " << UppMost.x << " " << UppMost.y << "\n";

        if (canAcces(curr, is) || canAcces(LeftMost, is) ||
            canAcces(RightMost, is) || canAcces(UppMost, is) ||
            canAcces(DownMost, is)) {
          if (is.x < newLeftMost.x)
            newLeftMost = is;
          if (is.y < newUppMost.y)
            newUppMost = is;
          if (is.x > newRightMost.x)
            newRightMost = is;
          if (is.y > newDownMost.y)
            newDownMost = is;
        } else {
          newCantacces.insert(is);
        }
      }

      // set new variables
      cantacces = newCantacces;
      UppMost = newUppMost;
      DownMost = newDownMost;
      LeftMost = newLeftMost;
      RightMost = newRightMost;
      // cout << "running  " << cantacces.size() << " " << depth << "\n";

    } while (cantacces.size() > 0);

    cout << acc << "\n";
  }
}