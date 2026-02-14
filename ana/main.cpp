#include <iostream>
#include <vector>
using namespace std;

int main() {
  long n;
  std::string str;
  cin >> n;
  cin >> str;

  vector<long> counter(26);
  vector<std::pair<long,long>> found;
  long lastPalindrome = 0;

  long startIdx = 0;

  for (long i = 0; i < n; i++) {
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
      lastPalindrome = i;
    }
    if (i == n - 1) {
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

  cout << longest + 1<< "\n";
  cout << found.size() << "\n";

  for (auto p : found) {
    cout << p.first + 1 << " " << p.second + 1 << "\n";
  }
}