#include <stdio.h>

int smth(int *a[]);

int main(void) {
  // wont compile
  //int arr[];
  int a[] = {1, 2, 3, 4, 5};
  smth(a);
  return 0;
}

int smth(int *a[]) {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += a[i];
  }
  printf("sum: %d\n", sum);
  return 0;
}
