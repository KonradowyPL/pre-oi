#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long n; // rozmiar tablicy
  long q; // ilosc zapytan
  cin >> n >> q;

  vector<long long> tablica(n + 1);

  for (long i = 0; i < n; i++) {
    long val;
    cin >> val;
    // I hate that, but it allows to use set & sort everything automatically
    // (I am lazy)
    tablica[i] = val;
  }

  for (long questionNum = 0; questionNum < q; questionNum++) {
    long l, r, m, k;
    cin >> l >> r >> m >> k;
    l--;
    r--;

    long len = r - l + 1;
    long effectiveLen = min(len, k);
    m = min(m, len);

    std::multiset<long long> memory;

    long index = 0;

    // preload memory
    for (; index < m; index++) {
      memory.insert(tablica[l + index]);
      // cout << "inserting " << tablica[l + index] << "\n";
    }

    // memory larger than subarray
    if (m == len) {
      for (int j = 0; j < k - 1; j++) {
        memory.erase(memory.begin());
      }
      cout << (*memory.begin()) << "\n";
      continue;
    }

    long extracted = 0;

    while (index < len && extracted < k - 1) {
      memory.erase(memory.begin()); // remove smallest
      memory.insert(tablica[l + index]);
      index++;
      extracted++;
    }

    // SUCCES: we successfully found k-th smallest
    if (extracted == k - 1 && !memory.empty()) {
      cout << ((*memory.begin())) << "\n";
    }
    // NO SUCCES: subarray too short
    else {
      long remaining = k - extracted - 1;
      for (int j = 0; j < remaining; j++)
        memory.erase(memory.begin());
      cout << ((*memory.begin())) << "\n";
    }
  }
}