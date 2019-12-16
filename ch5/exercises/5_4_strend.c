#include <stdio.h>

int str_end(char *s, char *t);
void test(char *s, char *t);

int main(void) {
  test("aab", "b");
  test("aba", "b");
  test("", "");
  test("kurwa", "");
  test("abcd", "ab");
  test("reeeee", "eee");
  return 0;
}

// return 1 if t occurs at the end of s, 0 otherwise
int str_end(char *s, char *t) {
  int len_s = 0, len_t = 0;
  while (*s != '\0') {
    len_s++;
    s++;
  }
  while (*t != '\0') {
    len_t++;
    t++;
  }
  if (len_t > len_s) {
    return 0;
  }
  while (len_t >= 0) {
    if (*s != *t) {
      return 0;
    }
    t--;
    s--;
    len_t--;
  }
  return 1;
}

void test(char *s, char *t) {
  if (str_end(s, t)) {
    printf("%s is at the end of %s\n", t, s);
  } else {
    printf("%s is not at the end of %s\n", t, s);
  }
}
