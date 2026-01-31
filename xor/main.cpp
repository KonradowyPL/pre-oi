#include <cassert>
#include <iostream>
using namespace std;

bool solve(const long *line, long n, long A, long x, long &variations) {
  // base case:
  if (n == 1) {
    long B = line[0];
    return (A ^ B) >= x;
  }

  long B = line[0];

  for (long j = 0; j < n; j++) {
    long A = line[j];

    cout << "vals: " << A << " " << B << " " << (A ^ B)
         << ((A ^ B) >= x ? " TAK" : " NIE") << "\n";
    if (solve(line + j, n - j, A, x ,variations)) {
      variations++;
    }
  }
  return false;
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