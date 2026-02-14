#include <iostream>
#include <vector>
using namespace std;

int main() {
  long n;
  std::string str;
  cin >> n;
  cin >> str;

  vector<long> counter(26);
  long lastPalindrome = 0;

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
    cout << isPalindrome << "\n";
    if (isPalindrome) {
      lastPalindrome = i;
    }
    if (i == n - 1) {
      cout << "p at " << lastPalindrome << "\n";
      // clear out counter
      for (int j = 0; j < 26; j++) {
        counter[j] = 0;
      }
      // 
      i = lastPalindrome;
    }
  }
}