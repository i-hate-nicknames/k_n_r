#include <string.h>
#include <stdlib.h>
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
    if (0 == strcmp(key, item->key)) {
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
