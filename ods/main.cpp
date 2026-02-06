#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  long N, S;
  cin >> N >> S;

  vector<int> board(N * N, 0);

  for (int i = 0; i < S; i++) {
    long x,y;
    cin >> x >> y;
    board[x * N + y] = 1;
  }
  
}