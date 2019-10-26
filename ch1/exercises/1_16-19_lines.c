#include <stdio.h>
#define MAXLINE 1000

int getln(char copy_to[], int limit);
void copy(char from[], char to[]);

int main() {
  char str[MAXLINE];
  char longest[MAXLINE];
  int len;
  int max = 0;
  while ((len = getln(str, MAXLINE)) != 0) {
    if (max < len) {
      max = len;
      copy(longest, str);
    }
  }
  if (max > 0) {
    printf(longest);
  }
  return 0;
}

int getln(char copy_to[], int limit) {
  char ch;
  int len = 0;
  for (len = 0; len < limit-1 && (ch = getchar()) != EOF && ch != '\n'; ++len) {
    copy_to[len] = ch;
  }
  if (ch == '\n') {
    copy_to[len] = '\n';
    ++len;
  }
  // null terminate our new string
  copy_to[len] = '\0';
  return len;
}

void copy(char to[], char from[]) {
  int i = 0;
  while ((to[i] = from[i]) != '\0') {
    i++;
  }
}

