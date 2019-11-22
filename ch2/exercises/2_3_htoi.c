#include <stdio.h>
#define STATE_NUMBER 0
#define STATE_ZERO 1
#define STATE_START 2

int htoi(char s[]);
void print_conversion(char s[]);
int is_hex_digit(char c);
int convert_hex(char c);

int main() {
  print_conversion("0xff");
  return 0;
}

int htoi(char s[]) {
  int state = STATE_START;
  int result = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    switch (state) {
    case STATE_NUMBER:
      if (!is_hex_digit(s[i])) {
        return -1;
      } else {
        result = result * 16;
        result += convert_hex(s[i]);
      }
      break;
    case STATE_START:
      if (s[i] == '0') {
        state = STATE_ZERO;
        continue;
      }
      // todo: need to signal error properly
      if (!is_hex_digit(s[i])) {
        return -1;
      } else {
        state = STATE_NUMBER;
        result = result * 16;
        result += convert_hex(s[i]);
      }
      break;
    case STATE_ZERO:
      if (s[i] == 'x' || s[i] == 'X') {
        state = STATE_NUMBER;
        continue;
      } else {
        return -1;
      }
    }
  }
  return result;
}

int is_hex_digit(char c) {
  return (c >= '0' && c <= '9') ||
    (c >= 'a' && c <= 'f') ||
    (c >= 'A' && c <= 'F');
}

int convert_hex(char c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  } else if (c >= 'a' && c <= 'f') {
    return c - 'a' + 10;
  } else if (c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  }
  return -1;
}

void print_conversion(char s[]) {
  int converted = htoi(s);
  if (converted == -1) {
    printf("Error converting %s\n", s);
  } else {
    printf("Value %s = %d\n", s, htoi(s));
  }
}
