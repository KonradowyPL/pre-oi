#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  long trees, days;
  cin >> trees >> days;

  std::string sequence;
  cin >> sequence;

  assert(sequence.size() == days);


  long coldDays = 0, hotDays = 0;

  for (auto day : sequence) {
    if (day == 'Z') {
      coldDays++;
    } else {
      hotDays++;
    }
  }

  vector<long> treeState(trees, 0);

}