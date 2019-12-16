#include <stdio.h>

int main(void) {

  int x = 5;
  int *px = &x, *p = NULL;
  printf("px: %d\n", px);
  printf("object of px: %d\n", *px);
  printf("p: %d\n", p);
  printf("object of p: %d\n", *p);
  return 0;
}
