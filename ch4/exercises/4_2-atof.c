#include <stdio.h>
#include <ctype.h>

double atof(char s[]);
double pow(double x, int exp);

int main(void) {
  printf("%f\n", atof("-2.3"));
  printf("%f\n", atof("0"));
  printf("%f\n", atof("-0"));
  printf("%f\n", atof("10.3e-5"));
  printf("%f\n", atof("2.3e5"));
  return 0;
}

double atof(char s[]) {
  int sign = 1, power = 1, exp_sign = 1, exp = 0;
  double value = 0.0;
  int i = 0;
  while (isspace(s[i])) {
    ++i;
  }
  if (s[i] == '-') {
    sign = -1;
  }
  if (s[i] == '-' || s[i] == '+') {
    ++i;
  }
  for (; isdigit(s[i]); ++i) {
    value = 10.0 * value + (s[i] - '0');
  }
  if (s[i] == '.') {
    ++i;
    for (; isdigit(s[i]); ++i) {
      value = 10.0 * value + (s[i] - '0');
      power *= 10;
    }
  }
  if (s[i] == 'e' || s[i] == 'E') {
    // quite a bit of code repetition for reading next signed integer
    // if we knew pointers already I'd move this to a different routine
    // and just read next (possibly signed) integer three times:
    // initially, after the dot and after exponent.
    ++i;
    exp_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+') {
      ++i;
    }
    for (; isdigit(s[i]); ++i) {
      exp = 10.0 * exp + (s[i] - '0');
    }
    exp = exp_sign * exp;
  }
  return sign * (value / power) * pow(10, exp);
}

// naïve implementation of power, linear complexity
double pow(double x, int exp) {
  int sign = (exp > 0) ? 1 : -1;
  int exp_val = (sign > 0) ? exp : -exp;
  double result = 1.0;
  if (exp == 0) {
    return 1.0;
  }
  if (exp == 1) {
    return x;
  }
  for (int i = 0; i < exp_val; ++i) {
    result *= x;
  }
  if (sign < 0) {
    result = 1 / result;
  }
  return result;
}
