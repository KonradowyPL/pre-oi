#include <cstdlib>
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
    vector<long> counter(m + 1);
    for (int j = 0; j < n; j++) {
      long col;
      cin >> col;
      points[j] = col;
      counter[col]++;
    }

    for (int j = 0; j < q; j++) {
      long a, b;
      cin >> a >> b;
      long acc = 0;
      long activeA = 0;
      long activeB = 0;
      long passedA = 0;
      long passedB = 0;
      long aCount = counter[a];
      long bCount = counter[b];

      for (auto ele : points) {
        if (ele == a) {
          activeA -= passedB;
          activeB += bCount - passedB; // remaining B
          passedA++;
        } else if (ele == b) {
          activeB -= passedA;
          activeA += aCount - passedA; // remaining A
          passedB++;
        }
        acc += activeB + activeA;
      }
      cout << acc << "\n";
    }
  }
}