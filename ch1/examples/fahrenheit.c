#include <stdio.h>

int main() {
  float fahr, cel;
  float lower, upper, step;
  lower = 0;
  upper = 300;
  step = 20;
  fahr = lower;
  printf("+---------------|--------+\n");
  printf("| Fahrenheit\t| Celsius|\n");
  while (fahr <= upper) {
    cel = 5 * (fahr-32) / 9;
    printf("+---------------|--------+\n");
    printf("| %3.1f\t\t| %6.1f |\n", fahr, cel);
    fahr += step;
  }
  printf("+---------------|--------+\n");

  return 0;
}
