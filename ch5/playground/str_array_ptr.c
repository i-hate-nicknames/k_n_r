#include <stdio.h>

void test_ptr(char *s, char *type);
void test_arr(char s[], char *type);

int main(void) {
  char s_arr1[] = "abc";
  char s_arr2[] = "abc";
  char *s_ptr1 = "abc";
  char *s_ptr2 = "abc";
  // these two will modify the character properly
  test_arr(s_arr1, "arr");
  test_ptr(s_arr2, "arr");
  // these two will segfault
  test_ptr(s_ptr2, "ptr");
  test_arr(s_ptr1, "ptr");
}

void test_ptr(char *s, char *type) {
  printf("ptr argument, called on %s var before:\n", type);
  printf("%s\n", s);
  s[0] = 'e';
  printf("ptr argument, called on %s var after:\n", type);
  printf("%s\n", s);
}

void test_arr(char s[], char *type) {
  printf("arr argument, called on %s var before:\n", type);
  printf("%s\n", s);
  s[0] = 'e';
  printf("arr argument, called on %s var after:\n", type);
  printf("%s\n", s);
}
