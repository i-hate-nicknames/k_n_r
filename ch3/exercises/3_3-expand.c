#include <stdio.h>
#define BUF_SIZE 500

void expand(char s1[], char s2[]);
void run_expand(char shorthand[]);

int main() {
  run_expand("z-a");
  run_expand("a-zA-Z0-9");
  run_expand("-a-z-");
  run_expand("0-z");
  return 0;
}

// expand shortcut sequence into a string:
// a-z -> abcd...z
// a-z0-9 -> abcd...z0...9
// a-d-f -> abcdef
// Leading or trailing - is taken literally: -a-c -> -abc
// only supports ascii letters of any case, digits and dash `-'
// invalid sequences like z-a will result in za
// no check is performed when jumping over sequences, i.e. 0-a will
// print more characters than 0-9a
void expand(char s1[], char s2[]) {
  
  int i = 0, j = 0;
  int should_expand = 0;
  char prev_char = 0;
  if (s1[0] == '-') {
    s2[0] = '-';
    ++i, ++j;
  }
  while (s1[i] != '\0') {
    if (s1[i] == '-') {
      should_expand = 1;
      ++i;
      continue;
    }
    if (should_expand) {
      for (char ch = prev_char+1; ch < s1[i]; ++ch) {
        s2[j] = ch;
        ++j;
      }
      should_expand = 0;
    }
    prev_char = s1[i];
    s2[j] = s1[i];
    ++i, ++j;
  }
  // add trailing dash only when there is no leading dash
  if (should_expand && s2[0] != '-') {
    s2[j] = '-';
    ++j;
  }
  s2[j] = '\0';
}

void run_expand(char shorthand[]) {
  char expanded[BUF_SIZE];
  expand(shorthand, expanded);
  printf("Shorthand: %s\nExpanded: %s\n", shorthand, expanded); 
}
