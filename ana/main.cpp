#include <climits>
#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 200'001

vector<int> cache(MAX_N, -1);  
std::string str;

long solve(long startIdx) {
  if (cache[startIdx] > 0) {
    return cache[startIdx];
  }

  // cout << "called " << startIdx << "\n";
  vector<long> counter(26);

  long shortestSegment = 0;

  for (long i = startIdx; i < str.size(); i++) {
    auto ch = str[i];
    int chrId = ch - 'a';
    counter[chrId]++;

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
        shortestSegment = i - startIdx + 1;
        break;
      }
      // decision: split or not?
      // try solving
      auto a = solve(i + 1);
      long l = min(i - startIdx + 1, a);
      if (a > shortestSegment) {
        shortestSegment = l;
      }
    }
  }
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