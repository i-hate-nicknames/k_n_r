/**
 * Hash map module, maps strings to strings
 * Simplified implementation, uses one global hash map
 */
#ifndef HASHTBH_H
#define HASHTBH_H

// lookup a string in the hash table. Return value stored
// or NULL if the key is not in the table
char *lookup(char *key);
// add string to the hash table. Return 0 if the operation
// failed and non-zero if it succeeded
int add(char *key, char *value);

#endif
