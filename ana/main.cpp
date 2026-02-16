#include <climits>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 200'001

std::vector<std::pair<long, long>> cache(MAX_N, {-1, -1});
std::string str;

std::pair<long, long> solve(long startIdx, long minLen = 0) {
  if (cache[startIdx].first > 0) {
    return cache[startIdx];
  }

  // cout << "called " << startIdx << "\n";
  // vector<long> counter(26);
  long long counter = 0;
  long long oddCount = 0;
  vector<long> found;

  long len = 0;

  for (long i = startIdx; i < str.size(); i++) {
    auto ch = str[i];
    int chrId = ch - 'a';
    len++;
    counter ^= 1L << chrId;
    if ((counter & (1L << chrId)) == 0) {
      oddCount--;
    } else {
      oddCount++;
    }

    // check if is palindrome
    bool isPalindrome = (oddCount <= 1);

    if (isPalindrome) {
      if (i == str.size() - 1) {
        cache[startIdx].first = len;
        cache[startIdx].second = i + 1;
        return cache[startIdx];
      }
      found.push_back(i + 1);
    }
  }

  long shortestSegment = 0;
  long segmentEnd = -1;

  for (int j = found.size() - 1; j >= 0; j--) {
    long maxTheoreticalLen =
        min(found[j] - startIdx, long(str.size()) - found[j]);

    if (maxTheoreticalLen <= shortestSegment || maxTheoreticalLen < minLen)
      continue;

    const auto& [solLen, end] = solve(found[j], max(shortestSegment, minLen));
    long l = min(found[j] - startIdx, solLen);
    if (l > shortestSegment) {
      shortestSegment = l;
      segmentEnd = found[j];
    }
  }

  cache[startIdx].first = shortestSegment;
  cache[startIdx].second = segmentEnd;

  // cout << "for " << startIdx << " shortest: " << shortestSegment << "\n";
  return cache[startIdx];
}

int main() {
  long n;
  cin >> n;
  cin >> str;
  auto s = solve(0);
  long i = 0;
  vector<long> segments;
  while (i != str.size()) {
    segments.push_back(i);
    i = cache[i].second;
  }
  segments.push_back(i);


  cout << s.first << "\n";
  cout << segments.size() - 1 << "\n";
  auto prev = 0;
  for( auto s : segments) {
    if (s == 0) continue;

    cout << prev + 1 << " " << s << "\n";

    prev = s;
  }
}