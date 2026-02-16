#include <climits>
#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 200'001

vector<int> cache(MAX_N, -1);
std::string str;

long solve(long startIdx) {
  cout << "called " << startIdx << "\n";
  if (cache[startIdx] > 0) {
    return cache[startIdx];
  }

  // cout << "called " << startIdx << "\n";
  vector<long> counter(26);
  vector<long> found;

  long len = 0;

  for (long i = startIdx; i < str.size(); i++) {
    auto ch = str[i];
    int chrId = ch - 'a';
    counter[chrId]++;
    len++;

    // check if is palindrome
    bool isPalindrome = true;
    bool hasOdd = false;
    for (auto c : counter) {
      if (c % 2 != 0) {
        if (hasOdd) {
          isPalindrome = false;
          break;
        } else {
          hasOdd = true;
        }
      }
    }
    if (isPalindrome) {
      if (i == str.size() - 1) {
        cache[startIdx] = len;
        return len;
      }
      found.push_back(i + 1);
    }
  }

  for (auto c : counter) {
   cout << " " << c;
  }
  cout << "\n";
  // cout << len << "\n";
  return -1;
  
  
  long shortestSegment = 0;

  for (int j = found.size() - 1; j >= 0; j--) {
    long maxTheoreticalLen =
        min(found[j] - startIdx, long(str.size()) - found[j]);

    if (maxTheoreticalLen <= shortestSegment)
      continue;

    auto a = solve(found[j]);
    long l = min(found[j] - startIdx, a);
    shortestSegment = max(shortestSegment, l);
  }

  //   if (i == str.size() - 1) {
  //   shortestSegment = len;
  //   break;
  // }
  // // decision: split or not?
  // // try solving
  // if (len > 1 && len > minLen) {

  //   auto a = solve(i + 1, min(shortestSegment, len));
  //   long l = min(len, a);
  //   if (a > shortestSegment) {
  //     shortestSegment = l;
  //   }
  //   }

  cache[startIdx] = shortestSegment;

  // cout << "for " << startIdx << " shortest: " << shortestSegment << "\n";
  return shortestSegment;
}

int main() {
  long n;
  cin >> n;
  cin >> str;
  auto s = solve(0);
  cout << "RESULT: " << s;
}