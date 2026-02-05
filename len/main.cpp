#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  long n;
  cin >> n;

  // vector<long> values(n + 1);
  vector<long> indexes(n + 1);

  for (int i = 0; i < n; i++) {
    long a;
    cin >> a;
    // values[i] = a;
    indexes[a] = i;
  }

  // dla kazdego i:
  // instnieje MAXSYMALNIE JEDNA
  // liczba mniejsza o większym indexie

  for (int i = 0; i < n + 1; i++) {
    cout << i <<" has index " << indexes[i] << "\n";
  }
  cout << "\n";

  for (long value = 1; value < n + 1; value++) {
    long selfIndex = indexes[value];

    vector<long> filteredIndexes;

    for (long j = 1; j < value; j++) {
      long secondIndex = indexes[j];
      if (secondIndex > selfIndex) {
        filteredIndexes.push_back(secondIndex);
      }
    }

    if (filteredIndexes.size() > 1) {
      std::sort(filteredIndexes.begin(), filteredIndexes.end());

      long secondLargest = filteredIndexes[filteredIndexes.size() - 2];

      cout << "computed value " << value << "\n";
      cout << "second larges index " << secondLargest << "\n";
      cout << "moving from " << selfIndex << " to " << secondLargest << "\n";

      cout << "diff: " << secondLargest - selfIndex << "\n";
      // accually move element:

      for (long j = 1; j < n + 1; j++) {
        long secondIndex = indexes[j];
        if (secondIndex >= selfIndex && secondIndex <= secondLargest) {
          indexes[j]--;
        }
        indexes[value] = secondLargest;
      }


      for (int i = 0; i < n + 1; i++) {
        cout << i <<" has index " << indexes[i] << "\n";
      }
      cout << "\n";
    }
  }
}
