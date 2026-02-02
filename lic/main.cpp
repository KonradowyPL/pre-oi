// p1 says 1
// p1 says 1 && p2 says 2
// p1 says 1 && p2 says 3
// p1 says 2
// p1 says 2 && p2 says 3
// p2 says 2
// p2 says 3

#include <iostream>
#include <vector>
using namespace std;

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long n;
  cin >> n;

  vector<std::pair<long, long>> values(n + 1);

  for (int i = 0; i < n; i++) {
    long a, b;
    cin >> a >> b;
    values[i] = {a, b};
    cout << (b - a) << "??\n";

  }
  long long acc = 0;

  for (int i = 0; i < n; i++) {
    auto [a, b] = values[i];
    acc += (b - a + 1); // inclusive
  }

  // p2 can bid minimum max(curr, selfMin)
  // p2 can bid maximum min(curr, selfMax)
  // sum([max(0, max(i, selfMin) - min(selfMax, i)) for i in range(prevMin, prevMax  inslusive)])

  cout << "val " << acc << "\n";
}