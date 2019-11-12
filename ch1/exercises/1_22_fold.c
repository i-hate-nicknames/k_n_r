#include <stdio.h>
#define LINE_MAX 5
#define NOT_FOUND 0

void print_buf(char buf[], int len);
void rearrange_buf(char buf[], int pos, int len);

int main() {
  char ch;
  int current_col = 0;
  int last_space_idx = 0;
  char current_line[LINE_MAX];

  // The idea is to collect characters into a buffer, and remember last
  // space position
  // if we cannot write current character (violates line length), we print
  // everything up to previous space and rearrange line buffer: put whatever
  // remains to the front
  // if there is no space, we print a hyphen and start new line

  // sadly, can't write it any better than this, because too much state is
  // present to abstract it out into functions
  
  while ((ch = getchar()) != EOF) {

    if (ch == '\n') {
      print_buf(current_line, current_col);
      putchar('\n');
      current_col = 0;
      last_space_idx = NOT_FOUND;
    }
    else if (current_col == LINE_MAX) {
      if (last_space_idx != NOT_FOUND) {
        print_buf(current_line, last_space_idx);
        putchar('\n');
        rearrange_buf(current_line, last_space_idx, LINE_MAX);
        current_col = current_col-last_space_idx;
        current_line[current_col] = ch;
        ++current_col;
        last_space_idx = NOT_FOUND;
      } else {
        print_buf(current_line, current_col+1);
        printf("%c-\n", ch);
        current_col = 0;
      }
    } else {
      current_line[current_col] = ch;
      if (ch == ' ' || ch == '\t') {
        last_space_idx = current_col;
      }
      ++current_col;
    }
  }
  print_buf(current_line, current_col);
  return 0;

}

void print_buf(char buf[], int len) {
  for (int i = 0; i < len; ++i) {
    putchar(buf[i]);
  }
}


void rearrange_buf(char buf[], int pos, int len) {
  for (int i = pos; i < len; ++i) {
    buf[i-pos] = buf[i];
  }
}
