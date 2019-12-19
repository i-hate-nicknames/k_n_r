#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000
#define DEFAULT_LEN 5
#define USAGE "Usage: find [-n num]\n"

int main(int argc, char **argv) {
  int len = DEFAULT_LEN;
  char *buf[MAX_LEN];
  char *line = NULL;
  size_t len_read = 0;
  ssize_t nread;
  int current_line = 0;

  if (argc > 1 && argc != 3) {
    printf(USAGE);
    return 0;
  }
  // omit error checking for brevity
  if (argc == 3) {
    if (strcmp("-n", argv[1])) {
      printf(USAGE);
      return 0;
    }
    len = atoi(argv[2]);
    len = len > MAX_LEN ? MAX_LEN : len;
  }
  while ((nread = getline(&line, &len_read, stdin)) != -1) {
    buf[current_line % len] = line;
    current_line++;
    // required to be reset for getline to allocate a new object instead of reusing
    // previous one
    line = NULL;
    len_read = 0;
  }
  if (current_line >= len) {
    for (int i = current_line % len; i < len; i++) {
      printf(buf[i]);
      free(buf[i]);
    }
  }
  for (int i = 0; i < current_line % len; i++) {
    printf(buf[i]);
    free(buf[i]);
  }
}
