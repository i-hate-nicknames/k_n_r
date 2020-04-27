#include <string.h>
#include <stdlib.h>
#include "trie.h"

struct trie *make_trie(char c) {
  struct trie *new;
  new = (struct trie *) malloc(sizeof(struct trie));
  new->c = c;
  new->hi_kid = NULL;
  new->lo_kid = NULL;
  new->eq_kid = NULL;
  new->occurrences = 0;
}

void delete_trie(struct trie *t) {
  if (t == NULL) {
    return;
  }
  delete_trie(t->lo_kid);
  delete_trie(t->eq_kid);
  delete_trie(t->hi_kid);
  free(t);
}

struct trie *insert(struct trie *t, char *word) {
  char current = word[0];
  if (t == NULL) {
    t = make_trie(current);
  }
  if (word[1] == '\0') {
    t->occurrences++;
    return t;
  }
  if (t->c < current) {
    t->lo_kid = insert(t->lo_kid, word);
  } else if (t->c > current) {
    t->hi_kid = insert(t->hi_kid, word);
  } else {
    t->eq_kid = insert(t->eq_kid, word+1);
  }
  return t;
}

int lookup(struct trie *t, char *word) {
  if (t == NULL) {
    return 0;
  }
  char current = word[0];
  if (t->c < current) {
    return lookup(t->lo_kid, word);
  } else if (t->c > current) {
    return lookup(t->hi_kid, word);
  } else {
    if (word[1] == '\0') {
      return t->occurrences;
    }
    return lookup(t->eq_kid, word+1);
  }
}
