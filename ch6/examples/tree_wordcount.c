#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NELEMS(a) (sizeof(a) / sizeof(a[0]))

struct tree {
  char *word;
  int count;
  struct tree *left;
  struct tree *right;
};

typedef void (*tree_visitor) (char *, int);
struct tree *inc(struct tree *root, char *word);
struct tree *make_tree(char *word);
void walk_tree(struct tree *root, tree_visitor visitor);
int lookup(struct tree *t, char *word);
void tree_printer(char *word, int count);

int main() {
  char *words[] = {"a", "abc", "a", "kurwa", "e", "aaa", "abc", "a"};
  struct tree *t = NULL;
  for (int i = 0; i < NELEMS(words); i++) {
    t = inc(t, words[i]);
  }
  walk_tree(t, tree_printer);
  return 0;
}

struct tree *inc(struct tree *root, char *word) {
  if (NULL == root) {
    root = make_tree(word);
    return root;
  }
  int cmp = strcmp(root->word, word); 
  if (0 == cmp) {
    root->count++;
    return root;
  } else if (cmp < 0) {
    root->left = inc(root->left, word);
  } else {
    root->right = inc(root->right, word);
  }
  return root;
}

int lookup(struct tree *root, char *word) {
  if (NULL == root) {
    return 0;
  }
  int cmp = strcmp(root->word, word); 
  if (0 == cmp) {
    return root->count;
  } else if (cmp < 0) {
    return lookup(root->left, word);
  } else {
    return lookup(root->right, word);
  }
}

struct tree *make_tree(char *word) {
  struct tree *t = (struct tree *) malloc(sizeof(struct tree));
  t->word = word;
  t->count = 1;
  return t;
}

// walk tree in a preorder fashion, first left subtree, then current node
// and then right subtree
// call tree visitor on values of every node
void walk_tree(struct tree *root, tree_visitor visitor) {
  if (NULL == root) return;
  walk_tree(root->left, visitor);
  (*visitor)(root->word, root->count);
  walk_tree(root->right, visitor);
}

void tree_printer(char *word, int count) {
  printf("Word %s has occured %d times\n", word, count);
}
