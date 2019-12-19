#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);
void writelines (char *lineptr[], int nlines);

typedef int (*comparator)(void *, void*);

void quicksort(void *v[], int left, int right, comparator cmp, int reverse);
void swap(void *items[], int s, int t);
comparator get_comparator(int numeric, int cased, int dir);

int numcmp(char *, char *);

int main(int argc, char **argv) {

  int nlines;
  int numeric = 0;
  int reverse = 0;
  int casei = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-n") == 0) {
      if (casei) {
        printf("Can't combine options -n and -f\n");
        return 1;
      }
      numeric = 1;
    }
    if (strcmp(argv[i], "-r") == 0) {
      reverse = 1;
    }
    if (strcmp(argv[i], "-f") == 0) {
      if (numeric) {
        printf("Can't combine options -n and -f\n");
        return 1;
      }
      casei = 1;
    }
  }
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    quicksort((void**) lineptr, 0, nlines-1, get_comparator(numeric, !casei, 0), reverse);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("Input is too big to sort tbh\n");
    return 1;
  }
}

void quicksort(void *v[], int left, int right, comparator cmp, int reverse) {
  int last;
  int cmp_result;
  if (left >= right) {
    return;
  }
  swap(v, left, (left + right)/2);
  last = left;
  for (int i = left+1; i <= right; i++) {
    if (reverse) {
      cmp_result = (*cmp)(v[left], v[i]);
    } else {
      cmp_result = (*cmp)(v[i], v[left]);
    }
    if (cmp_result < 0) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  quicksort(v, left, last-1, cmp, reverse);
  quicksort(v, last+1, right, cmp, reverse);
}

void swap(void *items[], int s, int t) {
  void *item = items[s];
  items[s] = items[t];
  items[t] = item;
}

int numcmp(char *s1, char *s2) {
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);

  if (v1 < v2) {
    return -1;
  } else if (v2 > v2) {
    return 1;
  } else {
    return 0;
  }
}

int readlines(char *lineptr[], int maxlines) {
  char *line = NULL;
  int line_num = 0;
  size_t len = 0;
  while ((getline(&line, &len, stdin)) != -1) {
    if (line_num == maxlines) {
      return -1;
    }
    lineptr[line_num] = line;
    //
    len = 0;
    line = NULL;
    line_num++;
  }
  return line_num;
}

// print all lines and free them afterwards
void writelines (char *lineptr[], int nlines) {
  for (int i = 0; i < nlines; i++) {
    printf(lineptr[i]);
    free(lineptr[i]);
  }
}

comparator get_comparator(int numeric, int cased, int dir) {
  if (numeric) {
    return (comparator) numcmp;
  } else if (!cased) {
    return (comparator) strcasecmp;
  } else {
    return (comparator) strcmp;
  }
}
