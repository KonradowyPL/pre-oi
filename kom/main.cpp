#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

struct komnata {
  long left;
  long right;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long n; // ilosc komnat
  long m; // dlugosc mapy
  long k; // kiedy się zmęczy

  cin >> n >> m >> k;
  cin.ignore();

  komnata komnaty[n + 1];

  for (long i = 0; i < n; i++) {
    long lewa;
    long prawa;
    cin >> lewa >> prawa;
    cin.ignore();
    komnaty[i + 1] = {lewa, prawa};
  }

  std::string seq;
  cin >> seq;

  vector<long> firstSeen(m * (n + 1), -1);
  vector<long> path;
  path.reserve(m * n);

  auto stateId = [&](long si, long c) { return si * (n + 1) + c; };

  long seqIndex = 0;
  long curr = 1;
  long step = 0;

  while (true) {
    long id = stateId(seqIndex, curr);
    if (firstSeen[id] != -1) {
      long first = firstSeen[id];
      long loopLen = step - first;
      long total = m * k;
      long rem = (total - first) % loopLen;
      cout << path[first + rem];
      return 0;
    }

    firstSeen[id] = step++;
    path.push_back(curr);

    curr = (seq[seqIndex] == 'L') ? komnaty[curr].left : komnaty[curr].right;

    seqIndex = (seqIndex + 1) % m;
  }
}