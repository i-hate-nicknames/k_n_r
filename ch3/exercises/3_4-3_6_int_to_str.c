#include <stdio.h>
#define BUF_SIZE 500

void itoa(int n, char s[], int min_width);
void itob(int n, char s[]);
void reverse(char s[]);
void leftpad(char s[], int len);
void run_itoa(int x);
int str_len(char s[]);

int main() {
  run_itoa(1<<31);
  int x = -33;
  run_itoa(x % 10);

  char bit_str[BUF_SIZE];
  itob(5, bit_str);
  printf("%s\n", bit_str);
}

void run_itoa(int x) {
  char str[BUF_SIZE];
  printf("Number: %d\n", x);
  itoa(x, str, 1);
  printf("Itoa: %s\n", str);
}

// 3_4 the problem with printing value -2^(wordsize-1) is that
// it can't be converted to a positive value, because the biggest
// positive value that can be represented is 2^(wordsize-1)-1, due
// to the sign bit. So, conversion n = -n fails, after which
// we still deal with a negative number. The result of n % 10 now
// becomes machine-dependent, because it operates on a negative
// number, and the result of % operator can be negative
// if number is too small, pad it with spaces to be at least min_width
// wide (3_6)
void itoa(int n, char s[], int min_width) {
  int sign = n;
  int borrowed = 0;
  if (n < 0) {
    n = -n;
    // if the value can't be converted to positive (can't fit), convert
    // n+1 and remember the "borrowed" 1
    if (n < 0) {
      n = -(n+1);
      borrowed = 1;
    }
  }
  int i = 0, digit = 0;
  do {
    digit = (n % 10);
    if (borrowed != 0) {
      digit += borrowed;
      borrowed = 0;
    }
    s[i] = digit + '0';
    n = n / 10;
    ++i;
  } while (n != 0);
  if (sign < 0) {
    s[i] = '-';
    ++i;
  }
  // would've been more efficient to pad here before reverse
  // but less clean (too many responsibilities for a function)
  s[i] = '\0';
  reverse(s);
  if (i < min_width) {
    leftpad(s, min_width-i);
  }
}

void itob(int n, char s[]) {
  int shifts = sizeof(int) * 8 - 1;
  for (int i = 0; i < shifts; ++i) {
    if (n & 1) {
      s[i] = '1';
    } else {
      s[i] = '0';
    }
    n = n >> 1;
  }
  reverse(s);
}

void reverse(char s[]) {
  int len = str_len(s);
  for (int i = 0; i < len/2; ++i) {
    char tmp = s[i];
    s[i] = s[len-1-i];
    s[len-1-i] = tmp;
  }
}

// part of 3_6
// pads given string to the left with enough space characters
// for it to have length len.
// assume array size of s is greater or equal to length of string
// s + length of padding
void leftpad(char s[], int len) {
  int s_len = str_len(s);
  for (int i = s_len; i >= 0; --i) {
    s[i+len] = s[i];
  }
  for (int i = 0; i < len; ++i) {
    s[i] = ' ';
  }
}

int str_len(char s[]) {
  int i = 0;
  int len = 0;
  while (s[i] != '\0') {
    ++len;
    ++i;
  }
  return len;
}
