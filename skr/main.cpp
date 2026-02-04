#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

struct Box {
  long mass;
  long support; // AKA: wytrzymałość
};

int main() {
  long n;
  cin >> n;

  vector<Box> boxes(n + 1);

  long maxSupport = 0;
  long maxSupportIndex = 0;

  for (int i = 0; i < n; i++) {
    long m, w;
    cin >> w >> m;
    boxes[i] = {m, w};

    if (w > maxSupport) {
      maxSupport = w;
      maxSupportIndex = i;
    }
  }

  cout << "first box: " << maxSupportIndex + 1 << " with max support "
       << maxSupport << "\n";
}