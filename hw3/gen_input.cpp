#include <iostream>

int main() {
  int n;
  std::cin >> n;
  std::cout << ".data\n.globl input\ninput:\n.word ";
  for (int i = 0, x; i < n; ++i) {
    std::cin >> x;
    std::cout << x << ' ';
  }
  std::cout << "\n.globl input_len\ninput_len:\n.word " << n << '\n';
  std::cout << R"(
.globl	heap
heap:
	.word	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

# Global variable that holds the current length of the heap
# You should modify this variable accordingly when inserting or popping elements.
.globl	len
len:
	.word	0
  )";
}