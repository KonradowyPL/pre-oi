#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  int Z;
  cin >> Z;

  for (int i = 0; i < Z; i++) {
    long n, m, q;
    // n == ilość punktow
    // m == liczba kolorow
    // q == ilosc zapytań

    cin >> n >> m >> q;
    vector<long> points(n);
    for (int j = 0; j < n; j++) {
      cin >> points[j];
    }
    for (int j = 0; j < q; j++) {
      long a, b;
      cin >> a >> b;
      long acc = 0;
      long aCount = 0;
      long bCount = 0;
      // first pass: count elements
      for (auto ele : points) {
        if (ele == a)
          aCount++;
        if (ele == b)
          bCount++;
      }
    }
  }
}