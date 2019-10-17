#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main() {
  float fahr, cel;
  fahr = LOWER;
  printf("+---------------|--------+\n");
  printf("| Fahrenheit\t| Celsius|\n");
  while (fahr <= UPPER) {
    cel = 5 * (fahr-32) / 9;
    printf("+---------------|--------+\n");
    printf("| %3.1f\t\t| %6.1f |\n", fahr, cel);
    fahr += STEP;
  }
  printf("+---------------|--------+\n");

  return 0;
}
