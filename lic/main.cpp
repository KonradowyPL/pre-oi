// p1 says 1
// p1 says 1 && p2 says 2
// p1 says 1 && p2 says 3
// p1 says 2
// p1 says 2 && p2 says 3
// p2 says 2
// p2 says 3

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
    segments[i * 2 + 1] = b;
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
    auto [bidMin, bidMax] = valueRanges[p];
    // step 1:

    // step 2: add 1 for every way someone can reach in their range

    long long segmentStart = 0;
    for (int i = 1; i < numSegments; i++) {
      long long segmentEnd = segments[i];

      // can bid:
      if (segmentStart >= bidMin && segmentEnd <= bidMax) {
        variations[i] += segmentEnd - segmentStart + 1;
      }
      segmentStart = segmentEnd;
    }
  }

  for (int x : variations) {
    std::cout << x << " ";
  }
  cout << "\n";
}