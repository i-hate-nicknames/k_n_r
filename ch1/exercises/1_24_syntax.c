#include <stdio.h>
#define STATE_TEXT 0
#define STATE_STRING_CONST 1
#define STATE_MULTILINE_COMMENT 2
#define STATE_COMMENT 3
#define STATE_SLASH 4
#define STATE_MULTILINE_STAR 5
#define STATE_STRING_ESCAPE 6
#define STATE_CHAR_CONST 7

#define STATUS_OK 0
#define STATUS_UNFINISHED_STRING 1
#define STATUS_UNCLOSED_PAREN 2
#define STATUS_UNMATCHED_PAREN 3

int run_checker();

int main() {
  int result = run_checker();
  switch (result) {
  case STATUS_OK:
    printf("no syntax errors detected\n");
    break;
  case STATUS_UNFINISHED_STRING:
    printf("Unclosed \"");
    break;
  case STATUS_UNCLOSED_PAREN:
    printf("Unclosed (");
    break;
  case STATUS_UNMATCHED_PAREN:
    printf("Closing unmatched paren");
    break;
  }
}

// square brackets and curly braces are omitted for brevity
// character constants should also be handled better (like strings),
// again - omitted for brevity
// ideally the offending line should be reported, but this is not possible
// without shared state or compound result (status + line)

int run_checker() {

  int ch;
  int open_paren_number = 0;
  int state = STATE_TEXT;

  while ((ch = getchar()) != EOF) {
    switch (state) {
      
    case STATE_TEXT:
      if (ch == '"') {
        state = STATE_STRING_CONST;
      }
      else if (ch == '\'') {
        state = STATE_CHAR_CONST;
      } else if (ch == '/') {
        state = STATE_SLASH;
      } else if (ch == '(') {
        ++open_paren_number;
      } else if (ch == ')') {
        if (open_paren_number == 0) {
          return STATUS_UNMATCHED_PAREN;
        } else {
          --open_paren_number;
        }
      }
      break;
            
    case STATE_SLASH:
      if (ch == '*') {
        state = STATE_MULTILINE_COMMENT;
      } else if (ch == '/') {
        state = STATE_COMMENT;
      } else {
        state = STATE_TEXT;
      }
      // sadly needs to be copied or lookahead needs to be performed
      if (ch == '(') {
        ++open_paren_number;
      } else if (ch == ')') {
        if (open_paren_number == 0) {
          return STATUS_UNMATCHED_PAREN;
        } else {
          --open_paren_number;
        }
      }
      break;

    case STATE_CHAR_CONST:
      
      if (ch == '\'') {
        state = STATE_TEXT;
      }
      break;

    case STATE_COMMENT:
      if (ch == '\n') {
        state = STATE_TEXT;
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
      
    case STATE_STRING_CONST:
      if (ch == '"') {
        state = STATE_TEXT;
      } else if (ch == '\n') {
        return STATUS_UNFINISHED_STRING;
      } else if (ch == '\\') {
        state = STATE_STRING_ESCAPE;
      }
      break;
    case STATE_STRING_ESCAPE:
      if (ch == '\n') {
        return STATUS_UNFINISHED_STRING;
      } else {
        state = STATE_STRING_CONST;
      }
      break;
    }
  }
  if (open_paren_number > 0) {
    return STATUS_UNCLOSED_PAREN;
  }
  return STATUS_OK;
}
  
