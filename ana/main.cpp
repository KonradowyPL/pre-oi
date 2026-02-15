#include <iostream>
#include <vector>
using namespace std;

long solve(const std::string &str, long startIdx) {
  cout << "called with " << startIdx << "\n";
  vector<long> counter(26);
  vector<std::pair<long, long>> found;

  long longestSol = 0;

  for (long i = startIdx; i < str.size(); i++) {
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
      // try solving
      auto a = solve(str, i + 1);
      longestSol = max(longestSol, a);
    }
  }

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
    return longestSol;
  }
  return -1;
}

int main() {
  long n;
  std::string str;
  cin >> n;
  cin >> str;

  auto s = solve(str, 0);
  cout << "RESULT: " << s;
}