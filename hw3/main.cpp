#include <vector>
#include <iostream>

void dExit(int x) {
  std::cout << "\n"
            << "Exited with error code " << x << '\n';
  exit(0);
}

struct BinaryHeap {
  std::vector<int> d;

  static void up(int *d, int k) {
    for (; k > 1 && d[k] < d[k >> 1]; k >>= 1) std::swap(d[k], d[k >> 1]);
  }
  static void down(int *d, int k, int n) {
    for (int nk; (nk = k << 1) <= n; k = nk) {
      if ((nk | 1) <= n && d[nk | 1] < d[nk]) nk |= 1;
      if (d[nk] >= d[k]) break;
      std::swap(d[nk], d[k]);
    }
  }

  void push(const int val) {
    if (size() == 32) dExit(-1);
    d.push_back(val), up(d.data() - 1, d.size());
  }
  int top() const { return d[0]; }
  int pop() {
    if (size() == 0) dExit(-1);
    int ret = top();
    return d[0] = d.back(), d.pop_back(), down(d.data() - 1, 1, d.size()), ret;
  }
  bool empty() const { return d.empty(); }
  int size() const { return d.size(); }
} d;

void print() {
  for (int i = 0; i < d.size(); ++i) {
    std::cout << d.d[i] << " \n"[i + 1 == d.size()];
  }
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0, x; i < n; ++i) {
    std::cin >> x;
    if (x >= 0) d.push(x);
    if (x == -2) print();
    if (x == -1) std::cout << d.pop() << '\n';
  }
  dExit(0);
}