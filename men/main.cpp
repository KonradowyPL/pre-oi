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

  // vector<std::pair<long, long>> data(n);
  int bufferIndex = 0;
  vector<std::pair<long, long>> buffer(10, {0, LONG_MAX});
  // SCORE , SPICE

  long acc = 0;

  long maxScore = 0;
  long currSpice = LONG_MAX;

  for (int i = 0; i < n; i++) {
    long spice, score;
    cin >> spice >> score;

    if (spice > maxSpice)
      continue;

    if (spice != currSpice) {

      auto prev = buffer[(bufferIndex - 1) % 10];
      auto prevPrev = buffer[(bufferIndex - 2) % 10];
      // check if previous was negative && prevprev is not same as curr spice
      if (prev.first < 0 && prevPrev.second != currSpice) {
        // undo that negative

        acc -= prev.first;
        bufferIndex--;
      }

      // check if previous was negative and 1 further was the same
      // and we are loosing score by keeping negative
      if (prev.first < 0 && prevPrev.second == currSpice &&
          (prev.first + prevPrev.first + maxScore <
           max(prevPrev.first, maxScore))) {

        // undo negative
        acc -= prev.first;
        bufferIndex--;
        // add gained score
        acc += max(prevPrev.first, maxScore) - prevPrev.first;

      } else {
        buffer[(bufferIndex++) % 10] = {maxScore, currSpice};
        acc += maxScore;
      }

      maxScore = score;
      currSpice = spice;
    } else {
      maxScore = max(score, maxScore);
    }
  }

  auto prev = buffer[(bufferIndex - 1) % 10];
  auto prevPrev = buffer[(bufferIndex - 2) % 10];
  // check if previous was negative && prevprev is not same as curr spice
  if (prev.first < 0 && prevPrev.second != currSpice) {
    // undo that negative

    acc -= prev.first;
    bufferIndex--;
  }

  // check if previous was negative and 1 further was the same
  // and we are loosing score by keeping negative
  if (prev.first < 0 && prevPrev.second == currSpice &&
      (prev.first + prevPrev.first + maxScore <
       max(prevPrev.first, maxScore))) {

    // undo negative
    acc -= prev.first;
    bufferIndex--;
    // add gained score
    acc += max(prevPrev.first, maxScore) - prevPrev.first;

  } else {
    buffer[(bufferIndex++) % 10] = {maxScore, currSpice};

    // do not count last if negative
    acc += max(0L, maxScore);
  }

  cout << acc << "\n";
}