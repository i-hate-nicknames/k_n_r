#include <stdio.h>

/**
 * Exercise 1-8
 */
int main() {

  int tabs = 0, newlines = 0, spaces = 0;
  int ch;

  while ((ch = getchar()) != EOF) {
    switch (ch) {
        case ' ':
          ++spaces;
          break;
        case '\t':
          ++tabs;
          break;
        case '\n':
          ++newlines;
          break;
      }
  }

  printf("tabs: %d, newlines: %d, spaces: %d\n", tabs, newlines, spaces);

  return 0;
}
