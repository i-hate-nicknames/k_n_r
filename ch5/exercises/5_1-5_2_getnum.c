#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);
int getint(int*);
int getfloat(double*);

int main(void) {
  int status, x;
  double t;
  printf("Enter an integer: \n");
  status = getint(&x);
  printf("status: %d, y: %d\n", status, x);
  printf("Enter a float, values between 0 and 1 should start with 0.: \n");
  status = getfloat(&t);
  printf("status: %d, y: %f\n", status, t);
  return 0;
}

int getint(int* pn) {
  int c, sign;

  while (isspace(c = getch()));

  if (!isdigit(c) && c != EOF && c != '-' && c != '+') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    char sign = c;
    c = getch();
    if (!isdigit(c)) {
      // 5_1
      // handle a sign char that doesn't have a number after it
      ungetch(c);
      ungetch(sign);
      return 0;
    }
  }
  for (*pn = 0; isdigit(c); c = getch()) {
    *pn = 10 * *pn + (c - '0');
  }
  *pn *= sign;
  if (c != EOF) {
    ungetch(c);
  }
  return c;
}

// 5_2, elegant but can't handle numbers like -.35, .21 etc
int getfloat(double* pn) {
  int c, num_part, status, sign;
  status = getint(&num_part);
  if (status == EOF) {
    return status;
  }
  sign = (num_part > 0) ? 1 : -1;
  // assign the whole part
  *pn = num_part;
  c = getch();
  if (c != '.') {
    ungetch(c);
    return c;
  }
  status = getint(&num_part);
  if (status <= 0) { // not a number or EOF
    ungetch('.');
    return status;
  }
  // calculate the actual fractional part given the number after dot
  double fractional_part = num_part;
  while (fractional_part > 1) {
    fractional_part /= 10;
  }
  *pn += (sign * fractional_part);
  return c;
}

#define BUF_SIZE 100
int buf[BUF_SIZE];
int bufp = 0;

int getch() {
  if (bufp > 0) {
    return buf[--bufp];
  } else {
    return getchar();
  }
}

void ungetch(int c) {
  buf[bufp++] = c;
}
