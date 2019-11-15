#include <stdio.h>
#define STATE_TEXT 0
#define STATE_SINGLE_COMMENT 1
#define STATE_CHAR_CONST 2
#define STATE_STRING_CONST 3
#define STATE_MULTILINE_COMMENT 4
#define STATE_TEXT_SLASH 5 //seen a single / when in text
#define STATE_MULTILINE_STAR 6 // seen a star when in multiline comment

/**
 * Remove all comments from the C program text in stdin
 * Correctly ignore comment sequences in "string constants"
 * and 'character constants'
 */
int main() {
  int state = STATE_TEXT;
  int ch;
  while ((ch = getchar()) != EOF) {
    switch (state) {
    case STATE_TEXT:
      if (ch == '/') {
        state = STATE_TEXT_SLASH;
        continue;
      }
      putchar(ch);
      if (ch == '\'') {
        state = STATE_CHAR_CONST;
      } else if (ch == '"') {
        state = STATE_STRING_CONST;
      }
      break;
    case STATE_TEXT_SLASH:
      if (ch == '*') {
        state = STATE_MULTILINE_COMMENT;
      } else if (ch == '/') {
        state = STATE_SINGLE_COMMENT;
      }
      else {
        putchar('/');
        putchar(ch);
      }
      break;
    case STATE_MULTILINE_COMMENT:
      if (ch == '*') {
        state = STATE_MULTILINE_STAR;
      }
      break;
    case STATE_MULTILINE_STAR:
      if (ch == '/') {
        state = STATE_TEXT;
      } else if (ch != '*') {
        state = STATE_MULTILINE_COMMENT;
      }
      break;
    case STATE_SINGLE_COMMENT:
      if (ch == '\n') {
        putchar('\n');
        state = STATE_TEXT;
      }
      break;
    case STATE_CHAR_CONST:
      putchar(ch);
      if (ch == '\'') {
        state = STATE_TEXT;
      }
      break;
    case STATE_STRING_CONST:
      putchar(ch);
      if (ch == '"') {
        state = STATE_TEXT;
      }
      break;
    }
  }
  return 0;
}
