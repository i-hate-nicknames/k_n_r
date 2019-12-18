#include <stdio.h>
#include <stdlib.h>

#define TAB_SIZE 8
#define MAX_STOPS 25

int run_entab(int num_stops, int *stops);
int is_tab_stop(int column, int num_stops, int *stops);

int main(int argc, char **argv) {
  int stops[MAX_STOPS];
  int num_stops = 0;
  if (argc > MAX_STOPS+1) {
    printf("Error: too many tab stops, maximum is %d\n", MAX_STOPS);
    return 1;
  }
  if (argc > 1) {
    argv++;
    argc--;
    for (; argc > 0; num_stops++, argc--, argv++) {
      stops[num_stops] = atoi(*argv);
    }
  }
  return run_entab(num_stops, stops);
}

int run_entab(int num_stops, int *stops) {
  int ch;
  int spaces_num = 0;
  int current_column = 0;
  while ((ch = getchar()) != EOF) {
    // if we have the right to do so, put a tab
    if (spaces_num > 1 && is_tab_stop(current_column, num_stops, stops)) {
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

int is_tab_stop(int column, int num_stops, int *stops) {
  if (num_stops == 0) {
    return (column % TAB_SIZE) == 0;
  } else {
    // run through all tab stops and check if current column is a tab stop
    for (int i = 0; i < num_stops; i++) {
      if (stops[i] == column) {
        return 1;
      }
    }
  }
  return 0;
}
