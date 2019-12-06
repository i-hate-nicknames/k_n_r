#include <stdio.h>

void reverse(char s[]);
int reverse_inner(char s[], int n);

int main() {
  char s[] = "abc";
  reverse(s);
  printf("%s\n", s);
}

void reverse(char s[]) {
  int target = reverse_inner(s, 0);
  s[target] = '\0';
}

// reverse string s, starting at from index
// return target index in the string, where
// next character should be inserted
// remove '\0' from the string, which should be
// inserted by caller
int reverse_inner(char s[], int from) {
  if (s[from] == '\0') {
    return 0;
  }
  char c = s[from];
  int target = reverse_inner(s, from+1);
  s[target] = c;
  return target+1;
}
