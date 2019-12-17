#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *line = NULL;
  char *pattern = NULL;
  int total_lines = 0;
  int print_line_n = 0, print_matched = 1;
  size_t len = 0;
  ssize_t nread;

  // skip first argument - the name of the program
  argv++;
  argc--;
  // if an argument starts with '-'
  // (*argv)[0] is the first character of the string argv points to
  while (argc > 0 && (*argv)[0] == '-') {
    char c;
    int i = 1;
    // read the argument char by char until the string is over
    // (*argv)[i] is the ith character of the string argv points to
    while ((c = (*argv)[i]) != '\0') {
      switch (c) {
      case 'x':
        print_matched = 0;
        break;
      case 'n':
        print_line_n = 1;
        break;
      default:
        printf("Error: unsupported flag %c\n", c);
        return 1;
      }
      i++;
    }
    // advance argv to the next argument
    argv++;
    argc--;
  }
  // last argument that didn't start with a dash is our pattern
  pattern = *argv;

  if (argc != 1) {
    printf("Usage: find [options] pattern\n");
    return 1;
  }
  
  while ((nread = getline(&line, &len, stdin)) != -1) {
    total_lines++;
    if ((strstr(line, pattern) != NULL) == print_matched) {
      if (print_line_n) {
        printf("%1d: ", total_lines);
      }
      printf("%s", line);
    }
  }
  free(line);
  return 0;
}
