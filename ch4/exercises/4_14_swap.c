#include <stdio.h>

#define dprint(exp) printf(#exp " = %d\n", exp)
// exchange two arguments of type t
#define swap(t, x, y) if (1) {t tmp = x; x = y; y = tmp;}

int main() {

  int x = 5;
  int y = 10;
  int tmp = 25;
  dprint(x);
  dprint(y);
  dprint(tmp);
  printf("swapping\n");
  swap(int, x, y);
  dprint(x);
  dprint(y);
  dprint(tmp);
}
