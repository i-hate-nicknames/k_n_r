#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);
void writelines (char *lineptr[], int nlines);

void quicksort(void *items[], int left, int right, int (*comp)(void *, void *));
void swap(void *items[], int s, int t);

int numcmp(char *, char *);

int main(int argc, char **argv) {

  int nlines;
  int numeric = 0;

  if (argc > 1 && strcmp(argv[1], "-n") == 0) {
    numeric = 1;
  }
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    quicksort((void**) lineptr, 0, nlines-1,
          (int (*) (void*, void*)) (numeric ? numcmp : strcmp));
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("Input is too big to sort tbh\n");
    return 1;
  }
}

void quicksort(void *v[], int left, int right, int (*comp)(void *, void *)) {
  int last;

  if (left >= right) {
    return;
  }
  swap(v, left, (left + right)/2);
  last = left;
  for (int i = left+1; i <= right; i++) {
    if ((*comp)(v[i], v[left]) < 0) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  quicksort(v, left, last-1, comp);
  quicksort(v, last+1, right, comp);
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
