// p1 says 1
// p1 says 1 && p2 says 2
// p1 says 1 && p2 says 3
// p1 says 2
// p1 says 2 && p2 says 3
// p2 says 2
// p2 says 3

#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<long long> segments(n * 2 + 2);
  vector<std::pair<long long, long long>> valueRanges(n + 1);

  for (int i = 0; i < n; i++) {
    long a, b;
    cin >> a >> b;
    segments[i * 2] = a;
    segments[i * 2 + 1] = b + 1; // inclusive
    valueRanges[i] = {a, b};
  }
  std::sort(segments.begin(), segments.end());

  auto it = std::unique(segments.begin(), segments.end());
  segments.erase(it, segments.end());

  for (int x : segments) {
    std::cout << x << " ";
  }
  cout << "\n";

  int numSegments = segments.size();

  
  vector<long long> variations(numSegments + 1);

  for (int p = 0; p < n; p++) {
    cout << "starting bider " << p << "\n";
    auto [bidMin, bidMax] = valueRanges[p];
    // step 1: add on top of previous bidders
    long long segmentStart = 0;
    for (int i = 1; i < numSegments; i++) {
      long long segmentEnd = segments[i];
      // can bid:
      if (segmentStart >= bidMin && segmentEnd <= bidMax) {
        long long previousSegmentStart = 0;
        for (int j = 1; j <= i; j++) {
          long long previousSegmentEnd = segments[j];

          if (i == j) {
            // overlapping segment
            long long segmentLen = segmentEnd - segmentStart;
            long long value = (segmentLen - 1) * segmentLen / 2;
            variations[i] *= max(value, (long long)1);
            cout << "overlapping segment: " << i << " len " << segmentLen
                 << " mult: " << value << " got: " << variations[i] << "\n";
          } else {
            // calculate
            variations[i] *= max(variations[j], (long long)1);
            cout << "multiplying by: " << variations[j] << "\n";
          }

          previousSegmentStart = previousSegmentEnd;
        }
      }
      segmentStart = segmentEnd;
    }

    // step 2: add 1 for every way someone can reach in their range
    // this assumes this person will be the first to bid
    segmentStart = 0;
    for (int i = 1; i < numSegments; i++) {
      long long segmentEnd = segments[i];

      // can bid:
      if (segmentStart >= bidMin && segmentEnd <= bidMax + 1) {
        variations[i - 1] += segmentEnd - segmentStart;
        cout << "adding: " << segmentEnd - segmentStart << "\n";
      }
      segmentStart = segmentEnd;
    }

    cout << "arr: ";
    for (int x : variations) {
      std::cout << x << " ";
    }
    cout << "\n";
  }
  long long acc;
  for (int x : variations) {
    std::cout << x << " ";
    acc += x;
  }
  cout << "\n";
  cout << "acc " << acc << "\n";
}