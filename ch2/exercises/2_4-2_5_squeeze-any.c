#include <stdio.h>

void squeeze(char s[], char blacklist[]);
int in_str(char c, char str[]);
int any(char s1[], char s2[]);

int main() {
  char line[] = "this is the line to be squeezed\n";
  squeeze(line, "aeiou");
  printf(line);
  printf("%d\n", any("kurwa", "abud"));
}

// 2_4
void squeeze(char s[], char blacklist[]) {
  int j = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (!in_str(s[i], blacklist)) {
      s[j] = s[i];
      ++j;
    }
  }
  s[j] = '\0';
  return;
}

// 2_5 return index of first occurence of a char c
// in s1. Char c is any character in s2.
int any(char s1[], char s2[]) {
  for (int i = 0; s1[i] != '\0'; ++i) {
    if (in_str(s1[i], s2)) {
      return i;
    }
  }
  return -1;
}

int in_str(char c, char str[]) {
  for (int i = 0; str[i] != '\0'; ++i) {
    if (c == str[i]) {
      return 1;
    }
  }
  return 0;
}
