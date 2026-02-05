// A - 0
// G - 1
// S - 2
#include <iostream>
using namespace std;

int main() {
  long n;
  cin >> n;

  std::string start;
  std::string target;
  cin >> start;
  cin >> target;

  long startValue = 0;
  long endValue = 0;

  long cntA1 = 0, cntG1 = 0, cntS1 = 0;
  long cntA2 = 0, cntG2 = 0, cntS2 = 0;

  for (char c : start) {
    if (c == 'A') {
      startValue += 0;
      cntA1++;
    } else if (c == 'G') {
      startValue += 1;
      cntG1++;
    } else {
      startValue += 2;
      cntS1++;
    }
  }

  for (char c : target) {
    if (c == 'A') {
      endValue += 0;
      cntA2++;
    } else if (c == 'G') {
      endValue += 1;
      cntG2++;
    } else {
      endValue += 2;
      cntS2++;
    }
  }

  if (startValue % 3 == endValue % 3) {
    long dA = cntA2 - cntA1;
    long dG = cntG2 - cntG1;
    long dS = cntS2 - cntS1;
    long count = (abs(dA) + abs(dG) + abs(dS)) / 4;
    cout << "Tak\n" << count << "\n";
  } else {
    cout << "Nie\n";
  }
}
