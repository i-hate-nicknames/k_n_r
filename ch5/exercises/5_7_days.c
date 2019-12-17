#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int year_day, int *m, int *d);

static char daytab[2][13] = {
 {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
 {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int main(void) {
  printf("%d\n", day_of_year(1965, 5, 13));
  int m, d;
  month_day(1965, 133, &m, &d);
  printf("m: %d, d: %d\n", m, d);
}

int day_of_year(int year, int month, int day) {
  int i, leap;
  leap = (year %4 == 0 && year % 100 != 0) || year %400 == 0;
  for (i = 1; i < month; i++) {
    day += daytab[leap][i];
  }
  return day;
}

void month_day(int year, int year_day, int *m, int *d) {
  int i, leap;
  leap = (year %4 == 0 && year % 100 != 0) || year %400 == 0;
  for (i = 1; year_day > daytab[leap][i]; i++) {
    year_day -= daytab[leap][i];
  }
  *m = i;
  *d = year_day;
}
