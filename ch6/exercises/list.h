#ifndef LIST_H
#define LIST_H

struct intlist {
  int item;
  struct intlist *tail;
};

extern struct intlist *nil;

struct intlist *cons(int val, struct intlist *onto);
void delete_list(struct intlist *lst);
void print_list(struct intlist *lst);

#endif
