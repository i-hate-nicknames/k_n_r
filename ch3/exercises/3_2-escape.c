#include <stdio.h>
#define BUF_SIZE 500

void escape (char s[], char t[]);
void unescape (char s[], char t[]);

int main() {
  char source[] = "This\tis\ttext.\nAlso\\slashes";
  char escaped[BUF_SIZE];
  char unescaped[BUF_SIZE*2];
  escape(source, escaped);
  printf("escaped:\n%s\n", escaped);
  unescape(escaped, unescaped);
  printf("unespcaped:\n%s\n", unescaped);
}

void escape (char s[], char t[]) {
  int j = 0;
  for (int i = 0; s[i] != '\0'; ++i, ++j) {
    switch (s[i]) {
    case '\t':
      t[j] = '\\';
      ++j;
      t[j] = 't';
      break;
    case '\n':
      t[j] = '\\';
      ++j;
      t[j] = 'n';
      break;
    case '\\':
      t[j] = '\\';
      ++j;
      t[j] = '\\';
      break;
    default:
      t[j] = s[i];
      break;
    }
  }
  t[j] = '\0';
}

void unescape (char s[], char t[]) {
  int seen_slash = 0;
  int j = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (!seen_slash) {
      if (s[i] == '\\') {
        seen_slash = 1;
      } else {
        t[j] = s[i];
        ++j;
      }
      continue;
    } else {
      switch (s[i]) {
      case 'n':
        t[j] = '\n';
        break;
      case '\\':
        t[j] = '\\';
        break;
      case 't':
        t[j] = '\t';
        break;
      default:
        t[j] = '\\';
        ++j;
        t[j] = s[i];
        break;
      }
      seen_slash = 0;
      ++j;
    }
  }
  t[j] = '\0';
}
