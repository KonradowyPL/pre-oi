#include <iostream>
#include <map>
#include <utility>
using namespace std;

struct wyspa {
  long x;
  long y;
};

inline const bool canAcces(const wyspa &A, const wyspa &B) {
  return (A.x < B.x && A.y < B.y) || (A.x > B.x && A.y > B.y);
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long n;
  cin >> n;
  cin.ignore();

  wyspa wyspy[n];

  for (long i = 0; i < n; i++) {
    long x, y;
    cin >> x >> y;
    cin.ignore();
    wyspy[i] = {x, y};
  }

  map<std::pair<int, int>, int> data;

  // first pass
  for (long i = 0; i < n; i++) {
    for (long j = i; j < n; j++) {
      if (!data.contains(std::make_pair(i, j)) &&
          canAcces(wyspy[i], wyspy[j])) {
        data[std::make_pair(i, j)] = 1;
        data[std::make_pair(j, i)] = 1;
      }
    }
  }

  // dump cache
  for (const auto &[key, value] : data) {
    auto [a, b] = key;
    std::cout << a << " -> " << b << ": " << value << std::endl;
  }
}