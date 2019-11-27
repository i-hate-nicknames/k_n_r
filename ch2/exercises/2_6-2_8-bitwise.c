#include <stdio.h>
// courtesy of stackoverflow
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define TO_BIN(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

unsigned char setbits(unsigned char x, int p, int n, unsigned char y);
void run_setbits(unsigned char x, int p, int n, unsigned char y, unsigned char expected);
unsigned char invert(unsigned char x, int p, int n);
void run_invert(unsigned char x, int p, int n, unsigned char expected);
unsigned char rightrot(unsigned char x, int n);
void run_rightrot(unsigned char x, int n, unsigned char expected);

int main() {
  run_setbits(0, 1, 1, 1, 2);
  run_setbits(1, 4, 2, 3, 25);
  run_invert(15, 1, 1, 13);
  run_invert(0, 7, 2, 128+64);
  run_rightrot(1, 1, 128);
  run_rightrot(3, 1, 129);
  run_rightrot(3, 2, 128+64);
  run_rightrot(130, 1, 65);
}

// set bits from p to p-n+1 in x, to the first n bits in y
// the rightmost bit has position 0
unsigned char setbits(unsigned char x, int p, int n, unsigned char y) {
  // number of bits from start to the end of target range
  int offset_right = p - n + 1;
  // mask with 1s at target range and 0s everywhere else
  unsigned char mask = (~(~'\0' << n)) << offset_right;
  // x & ~mask will set target range to 0 in x
  // y & mask will set everything except target range to 0 in y
  return (x & ~mask) | ((y << offset_right) & mask);
}

// invert n bits starting at position p, leave other bits unchanged
unsigned char invert(unsigned char x, int p, int n) {
  // number of bits from start to the end of target range
  int offset_right = p - n + 1;
  // mask with 1s at target range and 0s everywhere else
  unsigned char mask = (~(~'\0' << n)) << offset_right;
  // x & ~mask will set target bits to 0
  // then we write there inverted bits, that are calculated with ~x & mask
  return (x & ~mask) | (~x & mask);
}

// rotate x n positions to the right
unsigned char rightrot(unsigned char x, int n) {
  // to avoid using sizeof we can create a function that would shift
  // ~0 to the right until it's 0, to get the number of bits in the data
  int max = sizeof(unsigned char) * 8;
  return (x >> n) | (x << (max-n));
}

void run_setbits(unsigned char x, int p, int n, unsigned char y, unsigned char expected) {
  char text[] = "setting %d bits starting from %d\n"
    "x:\t\t" BYTE_TO_BINARY_PATTERN "\n"
    "y:\t\t" BYTE_TO_BINARY_PATTERN "\n"
    "result:\t\t" BYTE_TO_BINARY_PATTERN "\n"
    "expected:\t" BYTE_TO_BINARY_PATTERN "\n";

  printf(text, n, p, TO_BIN(x), TO_BIN(y), TO_BIN(setbits(x, p, n, y)),
         TO_BIN(expected));
}

void run_invert(unsigned char x, int p, int n, unsigned char expected) {
  char text[] = "Inverting %d bits starting from %d\n"
    "x: \t\t" BYTE_TO_BINARY_PATTERN "\n"
    "result:\t\t" BYTE_TO_BINARY_PATTERN "\n"
    "expected:\t" BYTE_TO_BINARY_PATTERN "\n";

  printf(text, n, p, TO_BIN(x), TO_BIN(invert(x, p, n)), TO_BIN(expected));
}

void run_rightrot(unsigned char x, int n, unsigned char expected) {
  char text[] = "Rotating %d positions to the right\n"
    "x:\t\t" BYTE_TO_BINARY_PATTERN "\n"
    "result:\t\t" BYTE_TO_BINARY_PATTERN "\n"
    "expected:\t" BYTE_TO_BINARY_PATTERN "\n";

  printf(text, n, TO_BIN(x), TO_BIN(rightrot(x, n)), TO_BIN(expected));
}
