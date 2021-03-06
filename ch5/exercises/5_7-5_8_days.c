#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int year_day, int *m, int *d);
int is_leap(int year);
int pday_of_year(int year, int month, int day);
int pmonth_day(int year, int year_day, int *m, int *d);

static char daytab[2][13] = {
 {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
 {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int main(void) {
  printf("%d\n", day_of_year(1965, 5, 13));
  printf("%d\n", pday_of_year(1965, 5, 13));
  int m, d;
  month_day(1965, 133, &m, &d);
  printf("m: %d, d: %d\n", m, d);
  pmonth_day(1965, 134, &m, &d);
  printf("m: %d, d: %d\n", m, d);
}

int day_of_year(int year, int month, int day) {
  int i, leap;
  leap = is_leap(year);
  if (month < 1 || month > 12) {
    printf("Error: incorrect month: %d\n", month);
  }
  if (day < 1 || day > daytab[leap][month]) {
    printf("Error: incorrect day of the month: %d\n", day);
  }
  for (i = 1; i < month; i++) {
    day += daytab[leap][i];
  }
  return day;
}

int month_day(int year, int year_day, int *m, int *d) {
  int i, leap;
  leap = is_leap(year);
  if (year_day < 1 || year_day > (365 + leap)) {
    printf("Error: incorrect year: %d\n", year_day);
    return -1;
  }
  for (i = 1; year_day > daytab[leap][i]; i++) {
    year_day -= daytab[leap][i];
  }
  *m = i;
  *d = year_day;
  return 0;
}

static char *pdays[] = {daytab[0], daytab[1]};

int is_leap(int year) {
  return (year %4 == 0 && year % 100 != 0) || year %400 == 0;
}

int pday_of_year(int year, int month, int day) {
  int i, leap;
  leap = is_leap(year);
  char *days_tab = pdays[leap];
  for (i = 1; i < month; i++) {
    day += *(days_tab+i);
  }
  return day;
  
}

int pmonth_day(int year, int year_day, int *m, int *d) {
  int i, leap;
  leap = is_leap(year);
  char *days_tab = pdays[leap];
  for (i = 1; year_day > days_tab[i]; i++) {
    year_day -= days_tab[i];
  }
  *m = i;
  *d = year_day;
  return 0;
}
