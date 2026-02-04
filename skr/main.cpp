#include <cassert>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

struct Box {
  long mass;
  long support; // AKA: wytrzymałość
};

int main() {
  long n;
  cin >> n;

  vector<Box> boxes(n);

  for (int i = 0; i < n; i++) {
    long m, w;
    cin >> w >> m;
    boxes[i] = {m, w};
  }

  std::sort(boxes.begin(), boxes.end(),
            [](auto a, auto b) -> bool { return a.support < b.support; });

  for (int i = 0; i < n; i++) {
    cout << boxes[i].support << " " << boxes[i].mass << "\n";
  }

  long currMass = 0;

  vector<Box> stack;

  for (int i = 0; i < n; i++) {
    long mass = boxes[i].mass;
    long support = boxes[i].support;

    currMass += mass;
    stack.push_back(boxes[i]);
    cout << "adding " << i << "\n";
    while (currMass > support) {
      int idx = 0;
      for (int j = 1; j < stack.size(); j++) {
        if (stack[j].mass > stack[idx].mass)
          idx = j;
      }
      currMass -= stack[idx].mass;
      stack.erase(stack.begin() + idx);
      cout << "erasing " << idx << "\n";
    }
  }

  cout << "STACK: " << stack.size() << "\n";
}