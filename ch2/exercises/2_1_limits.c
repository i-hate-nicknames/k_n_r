#include <stdio.h>
#include <limits.h>

int main() {
  printf("%s: %d\n", "CHAR_BIT", CHAR_BIT);
  printf("%s: %d\n", "INT_MIN", INT_MIN);
  printf("%s: %d\n", "INT_MAX", INT_MAX);
  printf("%s: %ld\n", "LONG_MAX", LONG_MAX);
  printf("%s: %ld\n", "LONG_MIN", LONG_MIN);
  printf("%s: %u\n", "UINT_MAX", UINT_MAX);
  printf("%s: %lu\n", "ULONG_MAX", ULONG_MAX);
  printf("%s: %u\n", "USHRT_MAX", USHRT_MAX);

  return 0;
}
