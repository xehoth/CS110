#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
  srand(time(0));
  int n = rand() % 64 + 1;
  std::cout << n << std::endl;
  int now = 0;
  for (int i = 0; i < n; ++i) {
    int d = rand() % 5;
    if (d <= 2) {
      ++now;
      std::cout << rand() % 100 << ' ';
    } else if (d == 3) {
      --now;
      std::cout << "-1 ";
    } else if (d == 4) {
      std::cout << "-2 ";
    }
  }
}