#include <cstdlib>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

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

      if (a == b) {
        cout << 0 << "\n";
        continue;
      }

      long acc = 0;

      long activeA = 0;
      long activeB = 0;
      long activeSum = 0;

      long passedA = 0;
      long passedB = 0;

      long remainingA = counter[a];
      long remainingB = counter[b];

      for (auto ele : points) {
        if (ele == a) {
          activeA -= passedB;
          activeSum -= passedB;

          activeB += remainingB;
          activeSum += remainingB;

          passedA++;
          remainingA--;
        } else if (ele == b) {
          activeB -= passedA;
          activeSum -= passedA;

          activeA += remainingA;
          activeSum += remainingA;

          passedB++;
          remainingB--;
        }

        acc += activeSum;
      }

      cout << acc << "\n";
    }
  }
}