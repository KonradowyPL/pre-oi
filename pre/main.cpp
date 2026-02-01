#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long n; // rozmiar tablicy
  long q; // ilosc zapytan
  cin >> n >> q;

  vector<long> tablica(n + 1);

  for (long i = 0; i < n; i++) {
    long val;
    cin >> val;
    tablica[i + 1] = val;
  }

  for (long questionNum = 0; questionNum < q; questionNum++) {
    long l; // start
    long r; // koniec
    long m; // rozmiar pamięci
    long k; // index liczby ktora interesuje wincentego
    cin >> l >> r >> m >> k;

    long p = l + k + m - 2;
    long len = r - l + 1;

    if (p > r) {
      std::vector<long> subvector(tablica.begin() + l, tablica.begin() + r + 1);
      std::sort(subvector.begin(), subvector.end());
      cout << subvector[k - 1] << "\n";
    } else {
      std::vector<long> subvector(tablica.begin() + l, tablica.begin() + p + 1);
      std::sort(subvector.begin(), subvector.end());

      long val = min(subvector[k - 1], tablica[p]);
      cout << val << "\n";
    }
  }
}