#include <stdio.h>
#include "stack.h"
#include "calc.h"

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
