#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

struct key {
  char* word;
  int count;
} keytab[] = {
              {"auto", 0,},
              {"break", 0,},
              {"char", 0,},
              {"const", 0,},
              {"continue", 0,},
              {"default", 0,},
              {"struct", 0,},
              {"int", 0,},
              {"while", 0,},
              {"return", 0,},
              {"void", 0,},
};

int getword(char *, int);
int find(char *, struct key *, int);

int main(void) {
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0])) {
      int idx = find(word, keytab, NKEYS);
      if (idx >= 0) {
        keytab[idx].count++;
      }
    }
  }
  for (int i = 0; i < NKEYS; i++) {
    if (keytab[i].count > 0) {
      printf("%s: %d\n", keytab[i].word, keytab[i].count);
    }
  }
  return 0;
}

int find(char *word, struct key tab[], int len) {
  // naive sequential search
  for (int i = 0; i < len; i++) {
    if (strcmp(word, tab[i].word) == 0) {
      return i;
    }
  }
  return -1;
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
