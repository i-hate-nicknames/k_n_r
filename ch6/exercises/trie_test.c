#include <stdio.h>
#include "trie.h"

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
