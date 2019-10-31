#include <stdio.h>
#define MAXLINE 1000

int getln(char copy_to[], int limit);
void copy(char from[], char to[]);
void print_longer_than(int len);
void print_longest_line();


int main() {
  print_longer_than(80);
  return 0;
}

// 1_16 print the longest line in the input
// together with its length
void print_longest_line() {
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
    puts(longest);
    printf("Length is: %d\n", max);
  }
}

// 1_16
// copy all characters from the input to copy_to until next newline or EOF
// stop copying if the number of characters exceeds limit
// return TOTAL number of characters in this line (which can be bigger than limit)
int getln(char copy_to[], int limit) {
  char ch;
  int len;
  int copied_len = 0;
  for (len = 0; (ch = getchar()) != EOF && ch != '\n'; ++len) {
    // -2 to account for both \n and \0 additions
    if (len < limit-2) {
      copy_to[len] = ch;
      copied_len = len+1;
    }
  }
  if (ch == '\n') {
    copy_to[copied_len] = '\n';
    ++copied_len;
    ++len;
  }
  // null terminate our new string
  copy_to[copied_len] = '\0';
  //printf(copy_to);
  return len;
}

void copy(char to[], char from[]) {
  int i = 0;
  while ((to[i] = from[i]) != '\0') {
    i++;
  }
}

// 1_17
// print all input lines that have length at least len
void print_longer_than(int len)
{
  char str[MAXLINE];
  int n;
  while ((n = getln(str, MAXLINE)) != 0) {
    if (n >= len) {
      fputs(str, stdout);
    }
  }
}
