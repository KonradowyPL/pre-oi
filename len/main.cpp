#include <cassert>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  long n;
  cin >> n;

  vector<long> values(n);
  vector<long> indexes(n + 1);

  for (int i = 0; i < n; i++) {
    long a;
    cin >> a;
    values[i] = a;
    indexes[a] = i;
  }

  // dla kazdego i:
  // instnieje MAXSYMALNIE JEDNA
  // liczba mniejsza o większym indexie

  for (long value = 1; value < n + 1; value++) {
    long selfIndex = indexes[value];
    long incorrectCount = 0;

    long largestIndex = 0;
    long secondLargestIndex = 0;

    for (long j = 1; j < value; j++) {
      long secondLargestIndexIndex = indexes[j];
      if (secondLargestIndexIndex > selfIndex) {
        incorrectCount++;

        if (j > largestIndex) {
          secondLargestIndex = largestIndex;
          largestIndex = j;
        } else if (j > secondLargestIndex && j != largestIndex) {
          secondLargestIndex = j;
        }
      }
    }

    if (incorrectCount > 1) {
      cout << "has to fix " << value << " second largest index " << secondLargestIndex << "\n";
    }
  }
}
