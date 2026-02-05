#include <cassert>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
  long trees, days;
  cin >> trees >> days;

  std::string sequence;
  cin >> sequence;

  assert(sequence.size() == days);

  long remainingColdDays = 0, remainingHotDays = 0;

  for (auto day : sequence) {
    if (day == 'Z') {
      remainingColdDays++;
    } else {
      remainingHotDays++;
    }
  }

  set<long> treeState;
  long coins = 0;

  for (int i = 0; i < days; i++) {
    // cout << "day " << i << " " << sequence[i] << "\n";

    if(sequence[i] == 'Z') {
      // dzien zimny mozna zbierac
      if (treeState.size() > 0) {
        auto largest = *treeState.rbegin();
        // cout << "collecting " << largest << "\n";
        coins += largest;
        treeState.erase(largest);
      } else {
        // cout << "doing nothing\n";
      }
      remainingColdDays--; 
    } else {
      // dzien cieply mozna podlewac
      if (remainingColdDays >= remainingHotDays) {
        // find largest tree
        int j = trees;
        for (; j > 0; j--) {
          if (!treeState.contains(j)) {
            break;
          }
        }
        treeState.insert(j);
        // cout << "can water " << j << "\n";
      } else {
        // cout << "doing nothing\n";

      }
      remainingHotDays--; 

    }

  }
  cout << coins << " -1\n";

}