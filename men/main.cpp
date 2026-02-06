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
      maxScore = 0;
      currSpice = spice;
    }

    maxScore = max(maxScore, score);
  }
  segments.push_back({maxScore, currSpice});
  segments.push_back({0, LONG_MAX});

  long acc = 0;

  for (int i = 1; i < segments.size() - 1; i++) {
    auto [score, spice] = segments[i];

    // cout << "se " << score << " " << spice << "\n";

    if (score >= 0) {
      acc += score;
    } else {
      // negative score
      // if previous has the same spice as next
      if (segments[i - 1].second == segments[i + 1].second) {
        // and it is worth adding both
        if ((segments[i - 1].first + segments[i + 1].first + score) >
            max(segments[i - 1].first, segments[i + 1].first)) {
          acc += score;
        } else {
          // it is worth adding only one
          if ((segments[i - 1].first < segments[i + 1].first)) {
            // previous was larger, skip next one
            i++;
          } else {
            // next is larger, undo previous
            acc -= segments[i - 1].first;
          }
        }
      }
    }
  }

  cout << acc << "\n";
}