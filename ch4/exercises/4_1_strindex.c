#include <stdio.h>

int strindex(char s[], char t[]);

int main() {
  char search[] = "key";
  char text[] = "the key to efficient communication is bla bla well the key";
  printf("src: %s\nsearch: %s\nindex:%d\n", text, search, strindex(text, search));
}

int strindex(char s[], char t[]) {
  int k = -1;
  int last_idx = -1;
  for (int i = 0; s[i] != '\0'; ++i) {
    for (int j = 0; t[j] != '\0'; ++j) {
      k = i;
      if (s[i+j] != t[j]) {
        k = -1;
        break;
      }
    }
    if (k != -1) {
      last_idx = k;
    }
  }
  return last_idx;
}
