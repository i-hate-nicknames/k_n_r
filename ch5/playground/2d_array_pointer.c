#include <stdio.h>

void test(int (*arr2d)[]);
void test2(int (*arr2d)[]);

int main(void) {
  int a2d[][3] = {{1, 2, 3}, {11, 22, 33}};
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  test(a2d);
  test2(a2d);
  // with some warnings we can even pass a one-dimensional array
  // and it will be treated as two-dimensional. Basically, the data is
  // laid out sequentially anyway
  test(a);
  test2(a);
}

// [2] in the type tells compiler the size of arrays arr2d points to, without the size
// it doesn't know how to perform pointer arithmetic, e.g. I want element 1,
// the address in this case will be two integers away from the element 0
// However, as you can see the actual size passed is not checked, so I can pass arrays
// of any sizes

void test(int (*arr2d)[2]) {
  printf("%d\n", arr2d[1][1]);
}

void test2(int (*arr2d)[3]) {
  printf("%d\n", arr2d[1][1]);
}

