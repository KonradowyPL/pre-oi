#include <cassert>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

#define ll long long
#define MOD 1'000'000'007

unsigned ll factorial(int n) {
  if (n < 0)
    return 0; // Factorial not defined for negative numbers
  unsigned ll fact = 1;
  for (int i = 1; i <= n; ++i) {
    fact *= i;
    fact %= MOD;
  }
  return fact;
}

ll modPow(ll base, ll exp) {
  ll result = 1;
  while (exp) {
    if (exp & 1)
      result = result * base % MOD;
    base = base * base % MOD;
    exp >>= 1;
  }
  return result;
}

ll modInverse(ll x) { return modPow(x, MOD - 2); }

int main() {
  long trees, days;
  cin >> trees >> days;

  std::string sequence;
  cin >> sequence;

  assert(sequence.size() == days);

  long remainingColdDays = 0, remainingHotDays = 0;

  for (auto day : sequence) {
    if (day == 'Z') {
      remainingColdDays++;
    } else {
      remainingHotDays++;
    }
  }
  // set of trees containing money
  set<long> with;
  // set of trees without money
  set<long> without;

  for (long j = 0; j < trees + 1; j++) {
    without.insert(j);
  }

  long coins = 0;
  unsigned ll totalCombinations = 1;

  // current season
  char seasonType = 'x';
  long seasonBusyDays = 0;
  long seasonLen = 0;

  for (int i = 0; i < days; i++) {
    if (seasonType != sequence[i]) {
      ll num = factorial(seasonLen);
      ll den = factorial(seasonLen - seasonBusyDays);

      ll combinations = num * modInverse(den) % MOD;

      totalCombinations *= combinations;
      totalCombinations %= MOD;

      // reset
      seasonBusyDays = 0;
      seasonLen = 0;
      seasonType = sequence[i];
    }

    if (sequence[i] == 'Z') {
      // dzien zimny mozna zbierac
      if (with.size() > 0) {
        auto largest = *with.rbegin();
        coins += largest;
        with.erase(largest);
        without.insert(largest);
        seasonBusyDays++;
      }
      remainingColdDays--;
      seasonLen++;
    } else {
      // dzien cieply mozna podlewac
      if (remainingColdDays >= remainingHotDays && without.size() > 0) {
        // find largest tree
        auto largest = *without.rbegin();
        with.insert(largest);
        without.erase(largest);
        seasonBusyDays++;
      }
      remainingHotDays--;
      seasonLen++;
    }
  }

  // end season
  auto combinations =
      factorial(seasonLen) / factorial(seasonLen - seasonBusyDays);

  totalCombinations *= combinations;
  totalCombinations %= MOD;

  cout << coins << " " << totalCombinations << "\n";
}