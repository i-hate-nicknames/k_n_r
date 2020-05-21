#include <stdio.h>
#include <stdarg.h>

void miniprintf(char *fmt, ...);

int main() {
  miniprintf("%d, %f, %s\n", 12, 15.5, "test");
}

void miniprintf(char *fmt, ...) {
  va_list ap;

  char *p;
  va_start(ap, fmt);
  int ival;
  double dval;
  char *sval;
  for (p = fmt; *p != '\0'; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    p++;
    switch (*p) {
    case 'd':
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case 's':
      sval = va_arg(ap, char *);
      printf("%s", sval);
      break;
    }
  }
  va_end(ap);
}
