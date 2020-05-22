#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_LINE 500

void diff_line(char *name1, char* name2);
FILE *open_or_fail(char *filename);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Please, provide two filenames as arguments\n");
    exit(1);
  }
  diff_line(argv[1], argv[2]);
}

void diff_line(char *name1, char* name2) {
  FILE *f1, *f2;
  f1 = open_or_fail(name1);
  f2 = open_or_fail(name2);
  char buf1[MAX_LINE], buf2[MAX_LINE];
  char *line1, *line2;
  int lineNum = 1;
  // ugly as my life, but too lazy to refactor
  for (;;) {
    line1 = fgets(buf1, MAX_LINE, f1);
    line2 = fgets(buf2, MAX_LINE, f2);
    if (line1 == NULL) {
      if (line2 == NULL) {
        printf("files are identical\n");
      } else {
        printf("extra line in file %s:\n", name2);
        printf("%s", line2);
      }
      return;
    }
    if (line2 == NULL) {
      printf("extra line in file %s:\n", name1);
      printf("%s", line1);
      return;
    }
    if (strcmp(line1, line2) != 0) {
      printf("Files differ at line %d\n", lineNum);
      printf("%s:\n%s", name1, line1);
      printf("%s:\n%s", name2, line2);
      return;
    }   
  }
}

FILE *open_or_fail(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Failed to open %s, errno:%d\n", filename, errno);
    exit(1);
  }
  return fp;
}

int cmp_lines(char *line1, char *line2) {
  
}
