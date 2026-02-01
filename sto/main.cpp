#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

int longsetStack(const vector<int> &a, int start) {
  int n = a.size();
  vector<int> stack;
  int maxOnStack = -1;

  for (int i = start; i < n; i++) {
    int x = a[i];

    if (!stack.empty()) {
      if (x < maxOnStack) {
        return i;
      }
    }

    while (!stack.empty() && stack.back() < x) {
      maxOnStack = max(maxOnStack, stack.back());
      stack.pop_back();
    }

    stack.push_back(x);
  }

  return n;
}

int main() {
  int n;
  cin >> n;

  vector<int> arr(n);
  
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  int start = 0;
  int acc = 0;

  while (start < n) {
    start = longsetStack(arr, start);
    acc++;
  }
  cout << acc << "\n";
}