#include <stdio.h>
#include <stdbool.h>

/**
 * Exercise 1-9
 */

int main() {

  int ch;
  bool space_before = false;

  while ((ch = getchar()) != EOF) {
    if (ch == ' ') {
      if (space_before) {
        continue;
      }
      space_before = true;
    } else {
      space_before = false;
    }
    putchar(ch);
  }
  return 0;
}
