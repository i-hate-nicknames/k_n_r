#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct trie {
  char c;
  int occurrences;
  struct trie *lo_kid, *hi_kid, *eq_kid;
};

struct trie *insert(struct trie *t, char *word);
struct trie *insert_inner(struct trie *t, char *word, int len);
int lookup(struct trie *t, char *word);
int lookup_inner(struct trie *t, char *word, int len);
void test(struct trie *t, char *word);

int main() {
  struct trie *t = NULL;
  t = insert(t, "cyka");
  t = insert(t, "cyka");
  test(t, "cyka");
  test(t, "kurwa");
  return 0;
}

void test(struct trie *t, char *word) {
  int res = lookup(t, word);
  printf("%s occurs %d times\n", word, res);
}

struct trie *insert(struct trie *t, char *word) {
  int len = strlen(word);
  return insert_inner(t, word, len);
}

struct trie *insert_inner(struct trie *t, char *word, int len) {
  char current = word[0];
  if (t == NULL) {
    t = (struct trie *) malloc(sizeof(struct trie));
    t->c = current;
    t->hi_kid = NULL;
    t->lo_kid = NULL;
    t->eq_kid = NULL;
    t->occurrences = 0;
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
