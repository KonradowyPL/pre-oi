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
    vector<long> firstIndex(m + 1);
    vector<long> lastIndex(m + 1);

    // fill firstIndex with -1
    for (int j = 0; j < m + 1; j++) {
      firstIndex[j] = -1;
    }

    for (int j = 0; j < n; j++) {
      long col;
      cin >> col;
      points[j] = col;
      counter[col]++;
      lastIndex[col] = j;
      if (firstIndex[col] == -1) {
        firstIndex[col] = j;
      }
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

      long start = min(firstIndex[a], firstIndex[b]);
      long end = max(lastIndex[a], lastIndex[b]);

      for (long p = start; p < end; p++) {
        auto ele = points[p];
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
        } else {
          acc += activeSum;
          continue;
        }

        // skip skipping logic
        if (remainingA > 1 || remainingB > 1) {
          acc += activeSum;
          continue;
        }

        // skip when any remaining is equal to 0
        if (remainingA != remainingB) {
          acc += (end - p) * activeSum;
          break;
        }

        long newPos = min(lastIndex[a], lastIndex[b]);
        acc += (newPos - p) * activeSum;

        if (points[newPos] == a) {
          // remainingA = 0
          acc += (end - newPos) * counter[a];
        } else {
          // remainingB = 0
          acc += (end - newPos) * counter[b];
        }
        break;
      }
      cout << acc << "\n";
    }
  }
}