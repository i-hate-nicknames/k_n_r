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
    char sign = c;
    c = getch();
    if (!isdigit(c)) {
      // 5_1
      // handle a sign char that doesn't have a number after it
      ungetch(c);
      ungetch(sign);
      return 0;
    }
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

#define BUF_SIZE 100
int buf[BUF_SIZE];
int bufp = 0;

int getch() {
  if (bufp > 0) {
    return buf[--bufp];
  } else {
    return getchar();
  }
}

void ungetch(int c) {
  buf[bufp++] = c;
}
