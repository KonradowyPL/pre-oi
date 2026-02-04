// p1 says 1
// p1 says 1 && p2 says 2
// p1 says 1 && p2 says 3
// p1 says 2
// p1 says 2 && p2 says 3
// p2 says 2
// p2 says 3

#include <cassert>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
using namespace std;

long long mod_inverse(long long a, long long m) {
  long long m0 = m, u = 1, v = 0;
  while (a > 1) {
    long long t = a / m;
    a -= t * m;
    std::swap(a, m);
    u -= t * v;
    std::swap(u, v);
  }
  if (u < 0)
    u += m0;
  return u;
}

static const long long MOD = 1000000007;

long long modPow(long long a, long long e) {
  long long r = 1;
  while (e) {
    if (e & 1)
      r = r * a % MOD;
    a = a * a % MOD;
    e >>= 1;
  }
  return r;
}

long long inv(long long x) { return modPow(x, MOD - 2); }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<pair<long long, long long>> a(n + 1);
  vector<long long> S;

  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
    S.push_back(a[i].first);
    S.push_back(a[i].second + 1);
  }

  sort(S.begin(), S.end());
  S.erase(unique(S.begin(), S.end()), S.end());

  int m = (int)S.size() - 1; // liczba kubełków
  vector<long long> L(m);
  for (int i = 0; i < m; i++) {
    L[i] = S[i + 1] - S[i];
  }

  // D[k][i]  – do i-tego kubełka włącznie
  // Dp[k][i] – dokładnie w i-tym kubełku
  vector<vector<long long>> D(n + 1, vector<long long>(m, 0));
  vector<vector<long long>> Dp(n + 1, vector<long long>(m, 0));

  // baza: 0 osób → dokładnie 1 pusty przebieg
  for (int i = 0; i < m; i++)
    D[0][i] = 1;

  for (int k = 1; k <= n; k++) {
    for (int i = 0; i < m; i++) {

      long long w = 1; // W(L[i], 0)
      int r = 0;

      // cofamy się po j
      for (int j = k; j >= 1; j--) {

        // POPRAWNY WARUNEK: część wspólna przedziałów
        if (a[j].first < S[i + 1] && a[j].second >= S[i]) {

          r++;
          if (r > 1) {
            // W(L, r) = W(L, r-1) * (L + r - 1) / r
            w = w * (L[i] + r - 1) % MOD * inv(r) % MOD;
          }

          long long prev;
          if (j == 1) {
            prev = 1;
          } else if (i == 0) {
            prev = 1;
          } else {
            prev = D[j - 1][i - 1];
          }

          Dp[k][i] = (Dp[k][i] + prev * w) % MOD;
        }
      }

      D[k][i] = Dp[k][i];
      if (i > 0) {
        D[k][i] = (D[k][i] + D[k][i - 1]) % MOD;
      }
    }
  }

  // odejmujemy pustą licytację
  long long ans = (D[n][m - 1] - 1 + MOD) % MOD;
  cout << ans << "\n";

  return 0;
}