#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <utility>
using namespace std;

struct wyspa {
  long x;
  long y;
};

inline const bool canAcces(const wyspa &A, const wyspa &B) {
  return (A.x < B.x && A.y < B.y) || (A.x > B.x && A.y > B.y);
}

inline const bool equal(const wyspa &A, const wyspa &B) {
  return (A.x == B.x && A.y == B.y);
}

int solve(const wyspa *islands, const wyspa *upSorted, const wyspa *downSorted,
          const wyspa *leftSorted, const wyspa *rightSorted, const wyspa &A,
          const wyspa &B) {

  if (canAcces(A, B)) {
    return 1;
  }

  // find edge points
  long powA = A.x - A.y;
  long powB = B.x - B.y;

  if (powA > powB) {
    // searching in bottom-left

    // assert(false);

  } else {
    // searching in top-right
    cout << A.x << " " << A.y << "\n";
    cout << B.x << " " << B.y << "\n\n";

    int i = 0;
    int j = 0;
    wyspa topMost = upSorted[i];
    wyspa rightMost = rightSorted[j];
    while (!canAcces(A, topMost) && equal(A, topMost))
      topMost = upSorted[++i];

    while (!canAcces(A, rightMost) && equal(A, rightMost))
      rightMost = rightSorted[++j];

    cout  << "?? " << (equal(A, rightMost)) << " " << (equal(A, topMost)) << "\n";
  }

  return 0;
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long n;
  cin >> n;
  cin.ignore();

  wyspa islands[n];
  wyspa upSorted[n];
  wyspa downSorted[n];
  wyspa leftSorted[n];
  wyspa rightSorted[n];
  int sortLen = sizeof(islands) / sizeof(islands[0]);

  for (long i = 0; i < n; i++) {
    long x, y;
    cin >> x >> y;
    cin.ignore();
    islands[i] = {x, y};
    upSorted[i] = {x, y};
    downSorted[i] = {x, y};
    leftSorted[i] = {x, y};
    rightSorted[i] = {x, y};
  }

  // sort stuff

  // up first, then left
  sort(upSorted, upSorted + sortLen, [](wyspa &a, wyspa &b) {
    if (a.y != b.y)
      return a.y < b.y;
    return a.x < b.x;
  });

  // down first, then right
  sort(downSorted, downSorted + sortLen, [](wyspa &a, wyspa &b) {
    if (a.y != b.y)
      return a.y > b.y;
    return a.x > b.x;
  });

  // left first, then up
  sort(leftSorted, leftSorted + sortLen, [](wyspa &a, wyspa &b) {
    if (a.x != b.x)
      return a.x < b.x;
    return a.y < b.y;
  });

  // right first, then down
  sort(rightSorted, rightSorted + sortLen, [](wyspa &a, wyspa &b) {
    if (a.x != b.x)
      return a.x > b.x;
    return a.y > b.y;
  });

  for (long i = 0; i < n; i++) {
    wyspa curr = islands[i];
    int acc = 0;
    for (long j = 0; j < n; j++) {
      if (j == i)
        continue;
      wyspa dist = islands[j];
      acc += solve(islands, upSorted, downSorted, leftSorted, rightSorted, curr,
                   dist);
    }
    return 0;
  }
}
