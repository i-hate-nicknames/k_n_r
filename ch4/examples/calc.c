#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char buf[]);
void push (double);
double pop(void);

int main(void) {
  int type;
  double op2;
  char op_read_buf[MAXOP];
  while ((type = getop(op_read_buf)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(op_read_buf));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      // order matters and since order of function calls is not guaranteed, save
      // to a variable
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0) {
        push(pop() / op2);
      } else {
        printf("Error: division by 0\n");
      }
      break;
    case '\n':
      printf("Result: %f\n", pop());
      break;
    default:
      printf("Error: unknown command: %s\n", op_read_buf);
      break;
    }
  }
  return 0;
}

#define STACK_SIZE 100

int sp = 0;
double stack[STACK_SIZE];

void push(double x) {
  if (sp < STACK_SIZE) {
    stack[sp] = x;
    sp++;
  } else {
    printf("Error: stack is full, cannot push %g\n", x);
  }
}

double pop() {
  if (sp > 0) {
    return stack[--sp];
  } else {
    printf("Error: popping from the empty stack\n");
    return 0.0;
  }
}

#include <ctype.h>

int getch(void);
void ungetch(int c);

int getop(char buf[]) {
  int i, c;
  // get next character or numeric operand
  // return the char or NUMBER in case of number
  // buf should contain string repr of the number
  while ((buf[0] = c = getch()) == '\t' || c == ' ') { }
  buf[1] = '\0';
  if (!isdigit(c) && c != '.') {
    return c;
  }
  i = 1;
  if (isdigit(c)) {
    while(isdigit(buf[i++] = c = getch()));
  }
  if (c == '.') {
    while(isdigit(buf[i++] = c = getch()));
  }
  // last character is not a digit so overwrite it
  buf[i-1] = '\0';
  if (c != EOF) {
    ungetch(c);
  }
  return NUMBER;
}

#define BUF_SIZE 100

int getch_top = 0;
char bufp[BUF_SIZE];

int getch() {
  if (getch_top == 0) {
    return getchar();
  } else {
    getch_top--;
    return bufp[getch_top];
  }
}

void ungetch(int c) {
  if (getch_top >= BUF_SIZE) {
    printf("Error: no size for ungetch\n");
  }
  bufp[getch_top] = c;
  getch_top++;
}
