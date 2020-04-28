#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct intlist *nil = NULL;

struct intlist *cons(int val, struct intlist *onto) {
  struct intlist *node = (struct intlist *) malloc(sizeof(struct intlist));
  node->item = val;
  node->tail = onto;
}

void delete_list(struct intlist *lst) {
  if (lst == NULL) {
    return;
  }
  delete_list(lst->tail);
  free(lst);
}

void print_list(struct intlist *lst) {
  printf("[");
  for (struct intlist *node = lst; node != NULL; node = node->tail) {
    printf("%d", node->item);
    if (node->tail != NULL) {
      printf(", ");
    }
  }
  printf("]");
}
