#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
enum { STATUS_OK, STATUS_ERROR };

int dcl(void);
int dirdcl(void);
void error_recover(void);

int gettoken(void);
int tokentype; // type of last token
char token[MAXTOKEN]; // last token string
char name[MAXTOKEN]; // identifier name
char datatype[MAXTOKEN];
char out[1000];

int main(void) {
  int result;
  while(gettoken() != EOF) {
    strcpy(datatype, token);
    out[0] = '\0';
    result = dcl();
    if (result != STATUS_OK) {
      printf("syntax error\n");
      error_recover();
    } else {
      printf("%s: %s %s\n", name, out, datatype);
    }
  }
  return 0;
}

// parse dcl definition from stdin
// set token, tokentype and possibly name by calling
// gettoken
int dcl(void) {
  int ns;
  int result;
  for (ns = 0; gettoken() == '*'; ) {
    ns++;
  }
  result = dirdcl();
  if (result != STATUS_OK) {
    return result;
  }
  while (ns > 0) {
    ns--;
    strcat(out, " pointer to");
  }
  return STATUS_OK;
}

// parse dirdcl definition
// expect gettoken to be called and corresponding global variables set
int dirdcl(void) {
  int type;
  int result;
  if (tokentype == '(') {
    result = dcl();
    if (result != STATUS_OK) {
      return result;
    }
    if (tokentype != ')') {
      printf("Error: missing )\n");
      return STATUS_ERROR;
    }
  } else if (tokentype == NAME) {
    strcpy(name, token);
  } else {
    printf("Error: expected name or (dcl)\n");
    return STATUS_ERROR;
  }
  while ((type = gettoken()) == PARENS || type == BRACKETS) {
    if (type == PARENS) {
      strcat(out, " function returning");
    } else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
  return STATUS_OK;
}

int gettoken(void) {
  int getch(void);
  void ungetch(int);
  int c;
  char *p = token;
  while ((c = getch()) == ' ' || c == '\t'); //skip whitespace
  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      tokentype = PARENS;
      return PARENS;
    } else {
      ungetch(c);
      tokentype = '(';
      return tokentype;
    }
  } else if (c == '[') {
    *p++ = c;
    while ((*p++ = getch()) != ']');
    *p++ = '\0';
    tokentype = BRACKETS;
    return BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch()); ) {
      *p++ = c;
    }
    *p = '\0';
    ungetch(c);
    tokentype = NAME;
    return NAME;
  } else {
    tokentype = c;
    return c;
  }
}

void error_recover(void) {
  extern int buffered;
  while (tokentype != EOF && tokentype != '\n') {
    gettoken();
  }
  buffered = 0;
}

int buffered;
int has_char = 0;

int getch() {
  if (has_char) {
    has_char = 0;
    return buffered;
  } else {
    return getchar();
  }
}

void ungetch(int c) {
  if (has_char) {
    printf("Error: ungetch buffer limit\n");
  }
  has_char = 1;
  buffered = c;
}
