#include <stdio.h>
#define MAXLINE 1000

int getln(char copy_to[], int limit);
int getln_and_trim(char copy_to[], int limit);
void copy(char from[], char to[]);
void print_longer_than(int len);
void print_longest_line();
void reverse(char s[]);


int main() {
  char str[MAXLINE];
  int len;
  while ((len = getln_and_trim(str, MAXLINE)) != -1) {
    if (len > 0) {
      puts(str);
    }
  }
  
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
  int ch;
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
void print_longer_than(int len) {
  char str[MAXLINE];
  int n;
  while ((n = getln(str, MAXLINE)) != 0) {
    if (n >= len) {
      fputs(str, stdout);
    }
  }
}

// 1_18
// get line from stdin, reading at most limit characters
// put read characters to copy_to
// return number of characters copied
// trim all trailing tabs and spaces
// return 0 if line is empty (only consists of empty spaces)
// return -1 when the input is exhausted
int getln_and_trim(char copy_to[], int limit) {
  char ch;
  // index of last found non-empty character in the string
  int last_nonempty = -1;
  for (int len = 0; (ch = getchar()) != EOF && ch != '\n' && len < limit-1; ++len) {
    copy_to[len] = ch;
    if (ch != ' ' && ch != '\t') {
      last_nonempty = len;
    }
  }
  // we havent found any non-empty characters and the input is over
  if (last_nonempty == -1 && ch == EOF) {
    return -1;
  }
  // null terminate our new string
  copy_to[last_nonempty+1] = '\0';
  return last_nonempty+1;
}

// 1_19
void reverse(char s[]) {
  int len = 0;
  while (s[len] != '\0') {
    ++len;
  }
  char tmp;
  for (int i = 0; i < len/2; ++i) {
    tmp = s[i];
    s[i] = s[len-i-1];
    s[len-i-1] = tmp;
  }
}
