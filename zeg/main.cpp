#include <iostream>
#include <unordered_map>
#include <utility>
using namespace std;

struct wyspa {
  long x;
  long y;
};

inline const bool canAcces(const wyspa &A, const wyspa &B) {
  return (A.x < B.x && A.y < B.y) || (A.x > B.x && A.y > B.y);
}

struct PairHash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);
    return h1 ^ (h2 << 1);
  }
};

struct PairEqual {
  template <class T1, class T2>
  bool operator()(const std::pair<T1, T2> &p1,
                  const std::pair<T1, T2> &p2) const {
    return p1.first == p2.first && p1.second == p2.second;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long n;
  cin >> n;
  cin.ignore();

  wyspa islands[n];

  for (long i = 0; i < n; i++) {
    long x, y;
    cin >> x >> y;
    cin.ignore();
    islands[i] = {x, y};
  }

  unordered_map<std::pair<int, int>, int, PairHash, PairEqual> data;

  // first pass
  for (long i = 0; i < n; i++) {
    for (long j = i; j < n; j++) {
      if (!data.contains(std::make_pair(i, j)) &&
          canAcces(islands[i], islands[j])) {
        data[std::make_pair(i, j)] = 1;
        data[std::make_pair(j, i)] = 1;
      }
    }
  }

  // connect stuff
  while (data.size() < n * n - n) {
    for (const auto &[key, stepsA] : data) {
      auto [from, via] = key;

      for (const auto &[key, stepsB] : data) {
        auto [to, via2] = key;
        if (via != via2)
          continue;
        if (from == to)
          continue;

        // connect!
        if (!data.contains(std::make_pair(from, to))) {
          data[std::make_pair(from, to)] = stepsA + stepsB;
          data[std::make_pair(to, from)] = stepsA + stepsB;
        } else {
          int numSteps = data[std::make_pair(from, to)];
          if (stepsA + stepsB < numSteps) {
            data[std::make_pair(from, to)] = stepsA + stepsB;
            data[std::make_pair(to, from)] = stepsA + stepsB;
          }
        }
      }
    }
  }

  // print data
  for (int i = 0; i < n; i++) {
    int acc = 0;

    for (const auto &[key, value] : data) {
      auto [a, b] = key;
      if (a == i) {
        acc += value;
      }
    }
    cout << acc << "\n";
  }
}