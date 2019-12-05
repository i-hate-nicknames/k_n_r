#include <stdio.h>
#define BUF_SIZE 100

int getch_top = 0;
char bufp[BUF_SIZE];

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
