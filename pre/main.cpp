#include <cstdlib>
#include <iostream>
#include <unordered_set>
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
    cin >> tablica[i];
  }

  for (long questionNum = 0; questionNum < q; questionNum++) {
    long l; // start
    long r; // koniec
    long m; // rozmiar pamięci
    long k; // index liczby ktora interesuje wincentego
    cin >> l >> r >> m >> k;

    m = min(m , r - l + 1);
    vector<long> subBoard(r - l + 1);
    vector<long> newBoard(r - l + 1);
    vector<long> memory(m);

    long newBoardIndex = 0;

    for (long j = 0, index = l - 1; index < r; j++) {
      subBoard[j] = tablica[index++];
    }

    // prefill memory
    long index = 0;

    for (; index < m; index++) {
      memory[index] = subBoard[index];
    }

    // run computation
    for (; index <= r - l; index++) {
      // cout << "got value " << subBoard[index] << " " << index << "\n";
      auto minElement = std::min_element(memory.begin(), memory.end());
      newBoard[newBoardIndex++] = *minElement;
      // cout << "min element " << *minElement << "\n";
      *minElement = subBoard[index];
    }

    // wypisanie wartości
    for (; newBoardIndex < r - l + 1;) {
      auto minElement = std::min_element(memory.begin(), memory.end());
      newBoard[newBoardIndex++] = *minElement;
      *minElement = 0xffffffff;
    }
    // cout << "wartosc: " << newBoard[k - 1]  << " " << questionNum << "\n";
    cout << newBoard[k - 1] << "\n";

    // MA MIEJSCE:
    // z tablicy to ramu

    // NIE MA MIEJSCA:
    // dowolna liczba z pamięci -> pierwsze puste miejsce
    // usunięcie tej liczby z pamięci
    // return 0;
  }
}