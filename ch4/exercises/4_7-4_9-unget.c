#include <stdio.h>
#include <strings.h>
#define BUF_SIZE 100

int getch(void);
void ungetch(int c);
void ungets(char s[]);
int getch_one(void);
void ungetch_one(int c);

int ungotten;
int has_ch = 0;

int getch_top = 0;
// 2_9 to handle EOF I switched to integers to fit EOF properly
// otherwise char255 would pass as EOF
int bufp[BUF_SIZE];

int main() {
  ungets("some string to be ungotten");
  for (int i = 0; i < 5; ++i) {
    putchar(getch());
  }
  ungetch(EOF);
  ungetch('a');
  ungetch(255);
  ungetch('c');
  int c;
  while ((c = getch()) != EOF) {
    putchar(c);
  }
  return 0;
}

int getch() {
  if (getch_top == 0) {
    return getchar();
  } else {
    getch_top--;
    return bufp[getch_top];
  }
}

void ungetch(int c) {
  if (getch_top >= BUF_SIZE) {
    printf("Error: no size for ungetch\n");
  }
  bufp[getch_top] = c;
  getch_top++;
}

void ungets(char s[]) {
  int c, i = 0;
  while ((c = s[i]) != '\0') {
    i++;
  }
  i--;
  while (i >= 0) {
    ungetch(s[i]);
    i--;
  }
}

void ungetch_one(int c) {
  ungotten = c;
  has_ch = 1;
}

int getch_one() {
  if (has_ch) {
    has_ch = 0;
    return ungotten;
  } else {
    return getchar();
  }
}
