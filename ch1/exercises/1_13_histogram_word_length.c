#include <stdio.h>
#define MAX_LENGTH 15
#define IN_WORD 1
#define OUT_WORD 0
#define HISTOGRAM_BAR_MAX 20

int main()
{
  int ch, state, current_length;
  int lengths[MAX_LENGTH];
  state = OUT_WORD;
  current_length = 0;

  for (int i = 0; i < MAX_LENGTH; ++i) {
    lengths[i] = 0;
  }
  while ((ch = getchar()) != EOF) {
    // if ch is a letter
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
      ++current_length;
      state = IN_WORD;
    } else if (state == IN_WORD) {
      if (current_length >= MAX_LENGTH) {
        current_length = MAX_LENGTH;
      }
      // we store length 1 as 0th element and so on
      // since there is no point in storing 0 length strings
      lengths[current_length-1]++;
      current_length = 0;
      state = OUT_WORD;
    }
  }

  int lengths_sum = 0;
  for (int i = 0; i < MAX_LENGTH; ++i) {
    lengths_sum += lengths[i];
  }
  for (int i = 0; i < MAX_LENGTH; ++i) {
    int freq = lengths[i] * HISTOGRAM_BAR_MAX / lengths_sum;
    if (freq == 0) {
      continue;
    }
    if (i == MAX_LENGTH-1) {
      printf("more than %d:\t", i+1);
    } else {
      printf("%d: \t\t", i+1);
    }
    for (int j = 0; j < freq; ++j) {
      printf("#");
    }
    printf("\n");
  }
  return 0;
}
