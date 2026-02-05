#include <cassert>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

struct Box {
  long mass;
  long support; // AKA: wytrzymałość
};

int main() {
  long n;
  cin >> n;

  vector<Box> boxes(n);

  for (int i = 0; i < n; i++) {
    long mass, support;
    cin >> support >> mass;
    boxes[i] = {mass, support};
  }

  std::sort(boxes.begin(), boxes.end(), [](auto a, auto b) -> bool {
    return a.mass + a.support < b.mass + b.support;
  });

  vector<long> dp(n + 1, LONG_MAX);
  dp[0] = 0;
  long maxH = 0;

  for (int i = 0; i < n; i++) {
    auto [mass, support] = boxes[i];
    // cout << a.mass + a.support << "\n";

    for (long h = maxH; h >= 0; h--) {
      if (dp[h] <= support) {
        dp[h + 1] = min(dp[h + 1], dp[h] + mass);
        maxH = max(maxH, h + 1);
      }
    }
  }
  cout << maxH << "\n";
}