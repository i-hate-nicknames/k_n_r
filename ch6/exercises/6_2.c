// basically create a trie, a tree that has chars as nodes. Whenever a "word" is stored,
// put some additional mark, like number of such words
// traverse it and when on depth 6 (or whatever) collect all variables with the
// "prefix"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

#define PREFIX_LEN 3
#define MAX_LEN 100

int getword(char *buf, int max_len);
void print_trie(struct trie *t, int current_depth, char *word);

int main() {
  struct trie *t;
  char word_buf[MAX_LEN];
  while (getword(word_buf, MAX_LEN) != EOF) {
    if (strlen(word_buf) < 3) {
      continue;
    }
    t = insert(t, word_buf);
  }
  print_trie(t, 0, word_buf);
  return 0;
}

void print_trie(struct trie *t, int current_depth, char *word) {
  if (t == NULL || current_depth >= MAX_LEN) {
    return;
  }
  print_trie(t->lo_kid, current_depth, word);
  word[current_depth] = t->c;
  if (current_depth == PREFIX_LEN-1) {
    word[current_depth+1] = '\0';
    printf("Prefix %s\n", word);
    printf("----------------\n");
  }
  if (current_depth >= PREFIX_LEN-1 && t->occurrences > 0) {
    word[current_depth+1] = '\0';
    printf("word: %s, occurrences: %d\n", word, t->occurrences);
    
  }
  print_trie(t->eq_kid, current_depth+1, word);
  // all of the things in the eq_kid are in our prefix, and
  // the length is guaranteed to be increasing, so we will only
  // print one line of ----, right after the group is over
  if (current_depth == PREFIX_LEN-1) {
    printf("----------------\n");
  }
  print_trie(t->hi_kid, current_depth, word);
  
}

int getword(char *buf, int max_len) {
  char *w = buf;
  int c;

  while (isspace(c = getchar()));
  if (c != EOF) {
    *w++ = c;
  }
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for (int i = 0; i < max_len; i++) {
    if (!isalnum(*w = getchar())) {
      ungetc(*w, stdin);
      break;
    }
    w++;
  }
  *w = '\0';
  return buf[0];
}

