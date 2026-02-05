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

  for (char c : start) {
    if (c == 'A') {
      startValue += 0;
    } else if (c == 'G') {
      startValue += 1;
    } else {
      startValue += 2;
    }
  }

  for (char c : target) {
    if (c == 'A') {
      endValue += 0;
    } else if (c == 'G') {
      endValue += 1;
    } else {
      endValue += 2;
    }
  }

  if (startValue % 3 == endValue % 3) {
    cout << "Tak\n";
  } else {
    cout << "Nie\n";
  }
}
