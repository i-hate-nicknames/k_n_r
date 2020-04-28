#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_WORD_LEN 200
#define MAX_WORDS 400

struct entry {
  char *name;
  struct intlist *lines;
};

struct reference {
  int len;
  struct entry *entries[MAX_WORDS];
};

int getword(char *buf, int max_lan);
void insert_word(char *word, struct reference *ref);
struct reference *make_reference();

int main() {
  struct intlist *list = cons(1, cons(2, nil));
  /* print_list(list); */
  delete_list(list);
  char buf[MAX_WORD_LEN];
  char c;
  struct reference *ref = make_reference();
  while (EOF != (c = getword(buf, MAX_WORDS))) {
    insert_word(buf, ref);
    printf("%s ", buf);
    if (c == '\n') {
      printf("\n newline!\n");
    }
  }
  printf("\n");
}

int getword(char *buf, int max_len) {
  char c;
  while (!isalpha((c = getchar())) && c != EOF);
  if (c == EOF) {
    return c;
  }
  int len = 0;
  for (; isalpha(c) && len < max_len; c = getchar(), len++) {
    *buf++ = c;
  }
  ungetc(c, stdin);
  *buf = '\0';
  return c;
}

struct reference *make_reference() {
  struct reference *new;
  new = (struct reference *) malloc(sizeof(struct reference));
  new->len = 0;
  return new;
}

void insert_word(char *word, struct reference *ref) {
  if (ref->len >= MAX_WORDS) {
    return;
  }
  char *str = (char *) malloc((sizeof (char)) * strlen(word));
  strcpy(str, word);
  struct entry *e = (struct entry *) malloc(sizeof(struct entry));
  e->name = str;
  e->lines = nil;
  ref->entries[ref->len] = e;
  ref->len++;
}
