#include <stdio.h>

#define BUFSIZE 50

void itoa(char s[], int x);
int itoa_inner(char s[], int x, int idx);

int main() {
  char buf[BUFSIZE];
  itoa(buf, -15);
  printf("%s\n", buf);
  return 0;
}

void itoa(char s[], int x) {
  int idx = 0;
  if (x < 0) {
    x = -x;
    s[0] = '-';
    idx++;
  }
  int last = itoa_inner(s, x, idx);
  s[last] = '\0';
}

// convert integer x to string and put it in s,
// starting from idx
int itoa_inner(char s[], int x, int idx) {
  int last = idx;
  if (x / 10) {
    last = itoa_inner(s, x / 10, idx);
  }
  s[last] = x % 10 + '0';
  return last+1;
}
