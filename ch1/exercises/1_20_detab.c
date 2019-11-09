#include <stdio.h>
#define TAB_SIZE 4

int spaces_to_stop(int current_column, int tab_size);

int main() {
  int current_column = 0;
  char c;
  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      int spaces = spaces_to_stop(current_column, TAB_SIZE);
      for (int i = 0; i < spaces; ++i) {
        putchar(' ');
        ++current_column;
      }
      // put n spaces
    } else {
      putchar(c);
      ++current_column;
    }
    if (c == '\n') {
      current_column = 0;
    }
  }
  return 0;
}

int spaces_to_stop(int current_column, int tab_size) {
  return tab_size - (current_column % tab_size);
}
