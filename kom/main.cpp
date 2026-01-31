#include <iostream>
using namespace std;

#define MAX_N 1000 + 1
#define MAX_M 500

const char l = 'L';
const char p = 'P';

struct komnata {
  long lewa;
  long prawa;
};

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long n; // ilosc komnat
  long m; // dlugosc mapy
  long k; // kiedy się zmęczy

  komnata komnaty[MAX_N];

  cin >> n >> m >> k;
  cin.ignore();

  for (long i = 0; i < n; i++) {
    long lewa;
    long prawa;
    cin >> lewa >> prawa;
    cin.ignore();
    komnaty[i + 1] = {lewa, prawa};
    // cout << lewa << " " << prawa << '\n';
  }

  std::string seq;
  cin >> seq;

  // cout << "seq " << seq << "\n";

  long seqIndex = 0;
  long curr = 1;

  for (long i = 0; i < k * m; i++) {
    const komnata &kom = komnaty[curr];
    char move = seq[seqIndex];
    // cout << "Jest w " << curr << " seq: " << move << "\n";

    seqIndex += 1;
    seqIndex %= m;

    // lewo
    if (move == l) {
      curr = kom.lewa;
    } else {
      curr = kom.prawa;
    }
  }

  cout << curr;
}