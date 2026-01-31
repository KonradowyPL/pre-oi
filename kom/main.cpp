#include <cassert>
#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX_N 1000 + 1
#define MAX_M 500

const char l = 'L';
const char p = 'P';

struct komnata {
  long lewa;
  long prawa;
};

struct cachePoint {
  long seqIndex;
  long curr;

  bool operator==(const cachePoint &b) const {
    return (curr == b.curr && seqIndex == b.seqIndex);
  }
};

struct CachePointHash {
  size_t operator()(const cachePoint &p) const noexcept {
    return std::hash<long>{}(p.seqIndex) ^ (std::hash<long>{}(p.curr) << 1);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long n; // ilosc komnat
  long m; // dlugosc mapy
  long k; // kiedy się zmęczy

  komnata komnaty[MAX_N];

  cin >> n >> m >> k;
  cin.ignore();

  for (long i = 0; i < n; i++) {
    long lewa;
    long prawa;
    cin >> lewa >> prawa;
    cin.ignore();
    komnaty[i + 1] = {lewa, prawa};
  }

  std::string seq;
  cin >> seq;

  std::unordered_map<cachePoint, long, CachePointHash> moveCache;

  long seqIndex = 0;
  long curr = 1;

  for (long i = 0; i < k * m; i++) {

    // has reached this point before
    if (moveCache.contains({seqIndex, curr})) {
      long firstOccurence = moveCache[{seqIndex, curr}];
      long loopDuration = i - firstOccurence;
      // calculate how many times we can complete loop before getting exhausted
      long loopCount = (m * k - i) / loopDuration;
      i += loopDuration * loopCount;
      if (i == k * m)
        break;
    } else {
      moveCache[{seqIndex, curr}] = i;
    }


    const komnata &kom = komnaty[curr];
    char move = seq[seqIndex];

    seqIndex += 1;
    seqIndex %= m;

    if (move == l) {
      // lewo
      curr = kom.lewa;
    } else {
      // prawo
      curr = kom.prawa;
    }
  }

  cout << curr;
}