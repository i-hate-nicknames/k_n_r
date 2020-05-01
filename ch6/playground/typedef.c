#include <stdio.h>
#include <stdlib.h>

typedef int Length;

typedef struct tree {
  int val;
  struct tree *left;
  struct tree *right;
} Tree;

typedef struct tree *Treeptr;

int add(int a, int b);

int main() {
  Length x;
  int y;
  x = 5;
  y = 10;
  printf("x + y = %d\n", x + y);
  printf("add(x, y) = %d\n", add(x, y));

  Treeptr t = (Treeptr) malloc(sizeof(Tree));
  t->val = 5;

  Tree *t2 = (Tree *) malloc(sizeof(Tree));
  t2->val = 10;
}

int add (int a, int b) { return a + b; }


