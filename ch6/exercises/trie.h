#ifndef TRIE_H
#define TRIE_H

struct trie {
  char c;
  int occurrences;
  struct trie *lo_kid, *hi_kid, *eq_kid;
};

struct trie *make_trie(char c);
void delete_trie(struct trie *t);
struct trie *insert(struct trie *t, char *word);
struct trie *insert_inner(struct trie *t, char *word, int len);
int lookup(struct trie *t, char *word);
int lookup_inner(struct trie *t, char *word, int len);

#endif
