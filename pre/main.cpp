#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct Node {
  long sum;
  Node *left, *right;
  Node(long s = 0, Node *l = nullptr, Node *r = nullptr)
      : sum(s), left(l), right(r) {}
};

Node *build(int start, int end) {
  if (start == end) {
    return new Node(0);
  }
  int mid = (start + end) / 2;
  return new Node(0, build(start, mid), build(mid + 1, end));
}

Node *update(Node *prev, int start, int end, int pos) {
  if (start == end) {
    return new Node(prev->sum + 1);
  }

  int mid = (start + end) / 2;
  if (pos <= mid) {
    return new Node(prev->sum + 1, update(prev->left, start, mid, pos),
                    prev->right);
  } else {
    return new Node(prev->sum + 1, prev->left,
                    update(prev->right, mid + 1, end, pos));
  }
}

int query(Node *leftRoot, Node *rightRoot, int start, int end, long k) {
  if (start == end) {
    return start;
  }

  int mid = (start + end) / 2;
  int countLeft = rightRoot->left->sum - leftRoot->left->sum;

  if (k <= countLeft) {
    return query(leftRoot->left, rightRoot->left, start, mid, k);
  } else {
    return query(leftRoot->right, rightRoot->right, mid + 1, end,
                 k - countLeft);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long n; // rozmiar tablicy
  long q; // ilosc zapytan
  cin >> n >> q;

  vector<long> tablica(n + 1);

  for (long i = 0; i < n; i++) {
    long val;
    cin >> val;
    tablica[i + 1] = val;
  }

  // create presistent segment tree
  vector<long> values = tablica;
  sort(values.begin(), values.end());
  values.erase(unique(values.begin(), values.end()), values.end());

  auto getCompressed = [&](long x) {
    return lower_bound(values.begin(), values.end(), x) - values.begin() + 1;
  };

  int num = tablica.size();
  int maxVal = values.size();

  vector<Node *> roots(num + 1);
  roots[0] = build(1, maxVal);
  for (int i = 1; i <= num; i++) {
    roots[i] = update(roots[i - 1], 1, maxVal, getCompressed(tablica[i - 1]));
  }

  // MAIN LOOP
  for (long questionNum = 0; questionNum < q; questionNum++) {
    long l; // start
    long r; // koniec
    long m; // rozmiar pamięci
    long k; // index liczby ktora interesuje wincentego
    cin >> l >> r >> m >> k;

    long p = l + k + m - 2;
    long len = r - l + 1;

    if (p > r) {
      int compressedIndex = query(roots[l], roots[r + 1], 1, maxVal, k);

      long result = values[compressedIndex - 1];
      cout << result << "\n";
    } else {
      int compressedIndex = query(roots[l], roots[p + 1], 1, maxVal, k);
      long result = values[compressedIndex - 1];
      long val = min(result, tablica[p]);
      cout << val << "\n";
    }
  }
}