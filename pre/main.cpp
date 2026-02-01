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
    // I hate that, but it allows to use set & sort everything automatically (I
    // am lazy)
    tablica[i] = (val << 32) + i;
  }

  for (long questionNum = 0; questionNum < q; questionNum++) {
    long l; // start
    long r; // koniec
    long m; // rozmiar pamięci
    long k; // index liczby ktora interesuje wincentego
    cin >> l >> r >> m >> k;
    l--;
    long len = min(r - l + 1, k);
    m = min(m, len);
    // cout << "memSize " << m << "\n";
    // cout << "len " << len << "\n";

    std::set<long long> memory;

    long index = 0; // index at which we read data from original array

    // read first m bytes from original array
    for (; index < m; index++) {
      memory.insert(tablica[index + l]);
      // cout << "inserting " << (tablica[index + l] >> 32) << "\n";
    }

    long outputed = 0;

    // run computation
    for (; index <= r - l + 1 && outputed != k - 1; index++) {
      long long value = *memory.begin();
      // cout << "got value " << (value >> 32) << "\n";
      // cout << "index " << index << "\n";
      memory.erase(memory.begin());
      memory.insert(tablica[index + l]);
      outputed++;
      // cout << "inserting " << (tablica[index + l] >> 32) << "\n\n";
    }

    if (outputed == k - 1) {
      cout << "final value " << (*memory.begin() >> 32) << "\n";
    } else {
      cout << "TODO:\n";
      // for (; outputed != k - 1; index++) {
      //   long long value = *memory.begin();
      //   cout << "got value " << (value >> 32) << "\n";
      //   cout << "index " << index << "\n";
      //   memory.erase(memory.begin());
      //   outputed++;
      //   // cout << "inserting " << (tablica[index + l] >> 32) << "\n";
      // }
      // cout << "final value " << (*memory.begin() >> 32) << "\n";
    }
    // cout << "\n\n\n";

    // MA MIEJSCE:
    // z tablicy to ramu

    // NIE MA MIEJSCA:
    // dowolna liczba z pamięci -> pierwsze puste miejsce
    // usunięcie tej liczby z pamięci
    // return 0;
  }
}