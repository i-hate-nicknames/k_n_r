#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_WORD_LEN 200
#define MAX_WORDS 2

struct entry {
  char *word;
  struct intlist *lines;
};

struct reference {
  int len;
  struct entry *entries[MAX_WORDS];
};

int getword(char *buf, int max_lan);
// add line number for this word in the given reference
// do nothing if the reference is full
void add_line(struct reference *ref, char *word, int line);
struct reference *make_reference();
// insert a new word in the given reference, return reference entry for the word
struct entry *insert_word(char *word, struct reference *ref);
struct entry *make_entry(char *word);

int main() {
  char buf[MAX_WORD_LEN];
  char c;
  struct reference *ref = make_reference();
  int line = 0;
  while (EOF != (c = getword(buf, MAX_WORD_LEN))) {
    add_line(ref, buf, line);
    if (c == '\n') {
      line++;
    }
  }
  for (int i = 0; i < ref->len; i++) {
    printf("%s: ", ref->entries[i]->word);
    print_list(ref->entries[i]->lines);
    printf("\n");
  }
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

struct entry *make_entry(char *word) {
  char *str = (char *) malloc((sizeof (char)) * strlen(word));
  strcpy(str, word);
  struct entry *e = (struct entry *) malloc(sizeof(struct entry));
  e->word = str;
  e->lines = nil;
  return e;
}

struct entry *insert_word(char *word, struct reference *ref) {
  if (ref->len >= MAX_WORDS) {
    fprintf(stderr, "Reference capacity overflow! Trying to insert %s\n", word);
    return NULL;
  }
  struct entry *e = make_entry(word);
  ref->entries[ref->len] = e;
  ref->len++;
  return e;
}

void add_line(struct reference *ref, char *word, int line) {
  struct entry *e = NULL;
  for (int i = 0; i < ref->len; i++) {
    if (0 == strcmp(ref->entries[i]->word, word)) {
      e = ref->entries[i];      
      break;
    }
  }
  if (e == NULL) {
    e = insert_word(word, ref);
  }
  if (e == NULL) {
    return;
  }
  e->lines = cons(line, e->lines);
}
