#include <stdio.h>

int bitcount(unsigned int x);
void run_bitcount(int x);

int main() {
  run_bitcount(-1);
  run_bitcount(0);
  run_bitcount(3);
  run_bitcount(255);
  run_bitcount(256);
}

// x &= (x-1) unsets rightmost 1 because:
// suppose the position of rightmost 1 is k
// (x-1) sets bit at k to 0, and all following bits to 1s (by definition of subtraction)
// bits from k to 0 look like this in x: 100...0, and like this in (x-1) 011...1.
// ANDing these two results in 0, so all bits from k to 0 are now set to 0
// since we started with k as the rightmost 1, it got effectively deleted

int bitcount(unsigned int x) {
  int count = 0;
  while (x != 0) {
    x &= (x-1);
    ++count;
  }
  return count;
}

void run_bitcount(int x) {
  printf("bit count of %d is %d\n", x, bitcount(x));
}
