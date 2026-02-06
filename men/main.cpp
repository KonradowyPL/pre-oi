#include <cassert>
#include <climits>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  long n;
  cin >> n;

  long maxSpice;
  cin >> maxSpice;

  vector<std::pair<long, long>> data(n);

  for (int i = 0; i < n; i++) {
    long spice, score;
    cin >> spice >> score;
    data[i] = {spice, score};
  }

  long maxScore = 0;
  long currSpice = LONG_MAX;

  vector<std::pair<long, long>> segments;

  for (int i = 0; i < n; i++) {
    auto [spice, score] = data[i];

    if (spice > maxSpice) {
      continue; // remove to spicy dishes
    }

    // clear acc
    if (spice != currSpice) {
      segments.push_back({maxScore, currSpice});
      maxScore = LONG_MIN;
      currSpice = spice;
    }

    maxScore = max(maxScore, score);
  }
  segments.push_back({maxScore, currSpice});
  segments.push_back({0, LONG_MAX});

  vector<std::pair<long, long>> newSegments;
  newSegments.push_back({0, LONG_MAX});

  for (int i = 1; i < segments.size() - 1; i++) {
    auto [score, spice] = segments[i];

    if (score >= 0) {
      if (newSegments[newSegments.size() - 1].second == spice) {

        newSegments[newSegments.size() - 1].first =
            max(newSegments[newSegments.size() - 1].first, score);

      } else {
        newSegments.push_back({score, spice});
        // cerr << "adding " << score << " " << spice << "\n";
      }
    } else {
      auto next = segments[i + 1];
      auto prev = segments[i - 1];

      if (next.second == prev.second) {
        // check if it is optimal to add negative

        if (next.first + prev.first + score > max(next.first, prev.first)) {
          // yes
          newSegments.push_back({score, spice});
        }
      }
    }
  }

  long acc = 0;

  for (auto seg : newSegments) {
    acc += seg.first;
  }

  cout << acc << "\n";
}