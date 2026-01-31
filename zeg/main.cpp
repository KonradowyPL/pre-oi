#include <algorithm>
#include <iostream>
using namespace std;

struct wyspa {
  long x;
  long y;
};

inline const bool canAcces(const wyspa &A, const wyspa &B) {
  return (A.x < B.x && A.y < B.y) || (A.x > B.x && A.y > B.y);
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long n;
  cin >> n;
  cin.ignore();

  wyspa islands[n];
  wyspa originalOrder[n];

  for (long i = 0; i < n; i++) {
    long x, y;
    cin >> x >> y;
    cin.ignore();
    islands[i] = {x, y};
    originalOrder[i] = {x, y};
  }

  std::sort(islands, islands + (sizeof(islands) / sizeof(islands[0])),
            [](wyspa a, wyspa b) { return a.x + a.y < b.x + b.y; });

  // for (long i = 0; i < n; i++) {
  //   cout << islands[i].x << " " << islands[i].y << "\n";
  // }

  for (long i = 0; i < n; i++) {
    long acc = 0;

    for (long j = 0; j < n; j++) {
      if (i == j)
        continue;

      // direct acces
      if (canAcces(originalOrder[i], originalOrder[j])) {
        acc++;
        continue;
      }

      // find 
    }
    cout << "to acces " << i << " " << acc << " moves\n"; 
  }

}