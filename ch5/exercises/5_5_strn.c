#include <stdio.h>

char *strn_cpy(char *s, char *ct, int n);
char *strn_cat(char *s, char *ct, int n);
int strn_cmp(char *cs, char *ct, int n);
void test_cmp(char *cs, char *ct, int n);

int main(void) {
  char s[] = "abcd";
  char *t = "efgh";
  strn_cpy(s, t, 2);
  printf("%s\n", s);

  char s2[10] = "abc";
  printf("%s\n", strn_cat(s2, "efgh", 3));

  test_cmp("abc", "abd", 2);
  test_cmp("abc", "abd", 3);
  test_cmp("abc", "abd", 15);
  test_cmp("ab", "abc", 2);
  test_cmp("ab", "abc", 3);
  test_cmp("test", "abc", 0);
  test_cmp("smth", "", 5);
  return 0;
}

// copy at most n characters from ct to s
// pad with \0's if it has less than n chars
// return s
char *strn_cpy(char *s, char *ct, int n) {
  char *start = s;
  int copied = 0;
  for (; *ct != '\0' && copied < n; s++, ct++, copied++) {
    *s = *ct;
  }
  *s = '\0';
  while (copied < n) {
    *s = '\0';
    copied++;
  }
  return start;
}

// concatenate at most n characters from ct to the end of s, terminate
// s with \0 and return s
char *strn_cat(char *s, char *ct, int n) {
  char *start = s;
  while (*s != '\0') {
    s++;
  }
  int copied = 0;
  for (; copied < n && *ct != '\0'; copied++, ct++, s++) {
    *s = *ct;
  }
  *s = '\0';
  return start;
}

// compare at most n characters between cs and ct
// return < 0 if cs < ct, 0 if they are equal and > 0 if cs > ct
int strn_cmp(char *cs, char *ct, int n) {
  int compared = 0;
  for (; compared < n; compared++, cs++, ct++) {
    if (*cs != *ct) {
      return *cs - *ct;
    }
    if (*cs == '\0') {
      return 0;
    }
  }
  return 0;
}

void test_cmp(char *cs, char *ct, int n) {
  char *template = "%s is %s %s, using first %d characters\n";
  int res = strn_cmp(cs, ct, n);
  if (res < 0) {
    printf(template, cs, "less than", ct, n);
  } else if (res > 0) {
    printf(template, cs, "greater than", ct, n);
  }
  else {
    printf(template, cs, "equal to", ct, n);
  }
}
