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
  int len = strlen(word);
  return insert_inner(t, word, len);
}

struct trie *insert_inner(struct trie *t, char *word, int len) {
  char current = word[0];
  if (t == NULL) {
    t = make_trie(current);
  }
  if (len == 1) {
    t->occurrences++;
    return t;
  }
  if (t->c < current) {
    t->lo_kid = insert_inner(t->lo_kid, word, len);
  } else if (t->c > current) {
    t->hi_kid = insert_inner(t->hi_kid, word, len);
  } else {
    t->eq_kid = insert_inner(t->eq_kid, word+1, len-1);
  }
  return t;
}

int lookup(struct trie *t, char *word) {
  return lookup_inner(t, word, strlen(word));
}

int lookup_inner(struct trie *t, char *word, int len) {
  if (t == NULL) {
    return 0;
  }
  char current = word[0];
  if (t->c < current) {
    return lookup_inner(t->lo_kid, word, len);
  } else if (t->c > current) {
    return lookup_inner(t->hi_kid, word, len);
  } else {
    if (len == 1) {
      return t->occurrences;
    }
    return lookup_inner(t->eq_kid, word+1, len-1);
  }
}
