#include <stdio.h>
#define TAB_SIZE 8

int main() {
  char ch;
  int spaces_num = 0;
  int current_column = 0;
  while ((ch = getchar()) != EOF) {
    // if we have the right to do so, put a tab
    int till_stop = current_column % TAB_SIZE;
    if (spaces_num > 1 && till_stop == 0) {
      putchar('\t');
      spaces_num = 0;
    }
    if (ch == ' ') {
      ++spaces_num;
    }
    // otherwise, print whatever spaces we already encountered and print
    // the character itself
    else {
      for (int i = 0; i < spaces_num; ++i) {
        putchar(' ');
      }
      putchar(ch);
      spaces_num = 0;
    }
    ++current_column;
  }
  return 0;
}
