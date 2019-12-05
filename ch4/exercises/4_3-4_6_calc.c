#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'
#define STRING 'a'

int getop(char buf[]);
void push (double);
double pop(void);
void clear_stack(void);
void print_top(void);
void dup(void);
void clear(void);
void swap(void);
void handle_command(char command[]);

int main(void) {
  int type;
  double op2;
  char op_read_buf[MAXOP];
  while ((type = getop(op_read_buf)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(op_read_buf));
      break;
    case STRING:
      handle_command(op_read_buf);
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
    case '%':
      op2 = pop();
      if (op2 != 0.0) {
        push((int) pop() % (int) op2);
      } else {
        printf("Error: division by 0\n");
      }
      break;
    case '\n':
      /* printf("Result: %f\n", peek()); */
      break;
    default:
      printf("Error: unknown command: %s\n", op_read_buf);
      break;
    }
  }
  return 0;
}

// HANDLING VARIABLES AND COMMANDS

double vars[26];

void store_var(char var, double val) {
  vars[(int) var] = val;
}

double lookup_var(char var) {
  return vars[(int) var];
}

#include <string.h>
#include <math.h>

void handle_command(char command[]) {
  double op2;
  
  if (strstr(command, "sin") != NULL) {
    push(sin(pop()));
    return;
  }
  if (strstr(command, "exp") != NULL) {
    push(exp(pop()));
    return;
  }
  if (strstr(command, "pow") != NULL) {
    op2 = pop();
    push(pow(pop(), op2));
    return;
  }
  if (strstr(command, "print") != NULL) {
    print_top();
  }
  if (strstr(command, "dup") != NULL) {
    dup();
  }
  if (strstr(command, "swap") != NULL) {
    swap();
  }
  if (strstr(command, "clear") != NULL) {
    clear();
  }
  if (strlen(command) == 1) {
    push(lookup_var(command[0]));
  }
}

// STACK

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

void clear() {
  sp = 0;
  printf("Stack cleared\n");
}

void dup() {
  if (sp > 0) {
    stack[sp] = stack[sp-1];
    sp++;
    printf("Top element on the stack has been duplicated\n");
  } else {
    printf("Error: the stack is empty, cannot duplicate\n");
  }
}

void print_top() {
  if (sp == 0) {
    printf("The stack is empty\n");
  } else {
    printf("Current stack state:\n");
    for (int i = 0, t = sp-1; i < 3 && t >= 0; ++i, --t) {
      if (i == 0) {
        store_var('p', stack[t]);
      }
      printf("%d: %f\n", t, stack[t]);
    }
  }
}

void swap() {
  if (sp < 2) {
    printf("Error: not enough elemets to swap\n");
  } else {
    double tmp = stack[sp-1];
    stack[sp-1] = stack[sp-2];
    stack[sp-2] = tmp;
  }
}

// PARSING OP

#include <ctype.h>

int getch(void);
void ungetch(int c);

int getop(char buf[]) {
  int i, c, type;
  // get next character or numeric operand
  // return the char or NUMBER in case of number
  // buf should contain string repr of the number
  while ((buf[0] = c = getch()) == '\t' || c == ' ') { }
  buf[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-' && !islower(c)) {
    return c;
  }
  i = 1;
  // all commands start with lowercase letter
  if (islower(c)) {
    while (islower(buf[i++] = c = getch()));
    type = STRING;
  }
  if (isdigit(c) || c == '.') {
    while(isdigit(buf[i++] = c = getch()));
    if (c == '.' || c == '-') {
      while(isdigit(buf[i++] = c = getch()));
    }
    type = NUMBER;
  }
  // last character is not a part of the digit/command
  buf[i-1] = '\0';
  if (c != EOF) {
    ungetch(c);
  }
  return type;
}

int get_command(char buf[]) {
  return 0;
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

// for 4_10
// Read until newline, return resulting string
// use this string for command parsing, the state
// now is represented as a position in the string
// instead of ungetch just decrement the position
// too lazy to implement it and copy around all other code
