// p1 says 1
// p1 says 1 && p2 says 2
// p1 says 1 && p2 says 3
// p1 says 2
// p1 says 2 && p2 says 3
// p2 says 2
// p2 says 3

#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
int n;
vector<pair<int, int>> valueRanges;
map<pair<int, int>, int> cache;

int count(int i, int minValue) {
  if (i == n)
    return 1; // reached end
  pair<int, int> key = {i, minValue};
  if (cache.count(key))
    return cache[key];

  int a = valueRanges[i].first;
  int b = valueRanges[i].second;
  long long res = 0;

  // PASS
  res += count(i + 1, minValue);
  res %= MOD;

  // person bids
  int start = max(a, minValue + 1);
  for (int x = start; x <= b; x++) {
    res += count(i + 1, x);
    res %= MOD;
  }

  // save to cache for future use
  cache[key] = res;
  return res;
}

int main() {
  cin >> n;
  valueRanges.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> valueRanges[i].first >> valueRanges[i].second;
  }

  int result = (count(0, 0) - 1 + MOD) % MOD;
  cout << result << endl;
  return 0;
}