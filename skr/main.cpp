#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

struct Box {
  long mass;
  long support; // AKA: wytrzymałość

  bool operator<(const Box &b) const { return mass < b.mass; }
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

  long currMass = 0;
  priority_queue<Box, vector<Box>> queue;

  for (int i = 0; i < n; i++) {
    long mass = boxes[i].mass;
    long support = boxes[i].support;

    queue.push(boxes[i]);
    while (currMass > support) {
      auto box = queue.top();
      currMass -= box.mass;
      queue.pop();
    }
    currMass += mass;
  }

  cout << queue.size() << "\n";
}