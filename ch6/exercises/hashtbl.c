#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hashtbl.h"

#define TABLE_SIZE 101
// list of entries to be stored under the same
// hash value
struct nlist {
  struct nlist *next;
  char *key;
  char *value;
};

static struct nlist *table[TABLE_SIZE];

unsigned hash(char *s);
struct nlist *lookup_entry(char *key);
// delete element that has given key, return list without the
// element
struct nlist *delete_el(struct nlist *lst, char *key);

int main() {
  char *key = "test_key";
  char *val = "some val";
  add(key, val);
  char *found = lookup(key);
  if (found != NULL && (strcmp(found, val) == 0)) {
    printf("found entry: key = %s, value = %s\n", key, val);
  }
  undef(key);
  if (lookup(key) == NULL) {
    printf("key %s not found\n", key);
  }
}

unsigned hash(char *s) {
  unsigned val;
  for (val = 0; *s != '\0'; s++) {
    val = *s + 31 * val;
  }
  return val % TABLE_SIZE;
}

// lookup a string in the hash table
char *lookup(char *key) {
  struct nlist *entry = lookup_entry(key);
  if (entry == NULL) {
    return NULL;
  }
  return entry->value;
}

struct nlist *lookup_entry(char *key) {
  unsigned hashval = hash(key);
  struct nlist *item;
  for (item = table[hashval]; item != NULL; item = item->next) {
    if (strcmp(key, item->key) == 0) {
      return item;
    }
  }
  return NULL;
}

// add string to the hash table. return 0 if the operation
// failed and non-zero if it succeeded
int add(char *key, char *value) {
  unsigned hashval = hash(key);

  struct nlist *item = lookup_entry(key);
  if (item == NULL) {
    item = (struct nlist *) malloc(sizeof(struct nlist));
    if (item == NULL || (item->key = strdup(key)) == NULL) {
      // failed to allocate
      return 0;
    }
    item->next = table[hashval];
    table[hashval] = item;
  } else {
    free((void *) item->value);
  }
  if ((item->value = strdup(value)) == NULL) {
    return 0;
  }
  return 1;
}

void undef(char *key) {
  unsigned hashval = hash(key);
  table[hashval] = delete_el(table[hashval], key);
}

struct nlist *delete_el(struct nlist *lst, char *key) {
  if (lst == NULL) {
    return NULL;
  }
  if (strcmp(lst->key, key) == 0) {
    free(lst->key);
    free(lst->value);
    free(lst);
    return lst->next;
  }
  else {
    lst->next = delete_el(lst->next, key);
  }
}
