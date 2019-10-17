#include <stdio.h>

int main() {

  int ch;

  while ((ch = getchar()) != EOF) {
    switch (ch) {
    case '\b':
      printf("\\b");
      break;
    case '\t':
      printf("\\t");
      break;
    case '\\':
      // two backslashes
      printf("\\\\");
      break;
    default:
      putchar(ch);
    }

  }
  
  return 0;
}
