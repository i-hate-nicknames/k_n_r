#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);
int getint(int*);

int main(void) {
  int x, y;
  x = getint(&y);
  printf("x: %d, y: %d\n", x, y);
  return 0;
}

int getint(int* pn) {
  int c, sign;

  while (isspace(c = getch()));

  if (!isdigit(c) && c != EOF && c != '-' && c != '+') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    c = getch();
  }
  for (*pn = 0; isdigit(c); c = getch()) {
    *pn = 10 * *pn + (c - '0');
  }
  *pn *= sign;
  if (c != EOF) {
    ungetch(c);
  }
  return c;
}

int last_char;
int buffered = 0;

int getch() {
  if (buffered) {
    buffered = 0;
    return last_char;
  } else {
    return getchar();
  }
}

void ungetch(int c) {
  last_char = c;
  buffered = 1;
}
