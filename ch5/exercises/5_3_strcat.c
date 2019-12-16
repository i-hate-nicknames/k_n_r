#include <stdio.h>

void str_cat(char *s, char *t);
void retarded_str_cat(char *s, char *t);

int main(void) {
  char s[100] = "";
  retarded_str_cat(s, "hmmm");
  retarded_str_cat(s, " more words\n");
  printf(s);
  return 0;
}

// copy string t to the end of s
// assume s has enough space to hold t
void str_cat(char *s, char *t) {
  while (*s != '\0') {
    s++;
  }
  while ((*s = *t) != '\0') {
    s++;
    t++;
  }
}

void retarded_str_cat(char *s, char *t) {
  while (*s) {
    s++;
  }
  while (*s++ = *t++);
}
