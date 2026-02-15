#include <iostream>
#include <vector>
using namespace std;

long solve(const std::string &str, long startIdx) {
  vector<long> counter(26);
  vector<std::pair<long, long>> found;
  long lastPalindrome = 0;

  for (long i = 0; i < str.size(); i++) {
    auto ch = str[i];
    int chrId = ch - 97;
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
      // decision: split or not?
      lastPalindrome = i;
    }
    if (i == str.size() - 1) {
      // clear out counter
      for (int j = 0; j < 26; j++) {
        counter[j] = 0;
      }
      found.push_back({startIdx, lastPalindrome});
      //
      i = lastPalindrome;
      startIdx = i + 1;
    }
  }

  long longest = 0;
  for (auto p : found) {
    longest = max(longest, p.second - p.first);
  }

  return longest;
}

int main() {
  long n;
  std::string str;
  cin >> n;
  cin >> str;

  auto s = solve(str, 0);
}