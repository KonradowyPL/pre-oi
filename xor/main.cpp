#include <cassert>
#include <iostream>
using namespace std;

void solve(const long *line, long n, long A, long x, long &variations) {
  // base case:
  // if (n == 1) {
  //   long B = line[0];
  //   return (A ^ B) >= x;
  // }

  // long B = line[0];

  if (n == 3) {

    bool all = true;

    for (long j = 0; j < n; j++) {
      long A = line[j];
      for (long i = j + 1; i < n; i++) {

        long B = line[i];
        cout << "vals: " << A << " " << B << " " << (A ^ B)
             << ((A ^ B) >= x ? " TAK" : " NIE") << "\n";
        if ((A ^ B) >= x) {
          variations++;
        } else {
          all = false;
        }
      }
    }
    if (all) {
      variations++;
    }
  } else {
    long B = line[0];
    const long *newLine = line + 1;
    solve(newLine, n - 1, B, x, variations);
  }
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long Z;
  cin >> Z;
  cin.ignore();

  for (long z = 0; z < Z; z++) {
    long n, x;
    cin >> n >> x;
    cin.ignore();

    cout << "num " << n << " minval " << x << "\n";

    long line[n];
    for (long j = 0; j < n; j++) {
      cin >> line[j];
    }
    cin.ignore();

    // SOLVE PART
    long variations = n;
    solve(line, n, 0, x, variations);

    cout << "variations: " << variations << "\n";
  }
}