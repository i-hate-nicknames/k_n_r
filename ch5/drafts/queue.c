#include <stdio.h>

#define DEFAULT_LEN 10
#define MAX_LEN 200

void inc_ptr(int **stack_ptr, int *start_a, int *start_b, int *end_a, int *end_b);
int is_within(int *ptr, int *q, int *p);
void print_all(int *q, int *p, int *start_a, int *start_b, int *end_a, int *end_b);
void print_between(int *q, int *p);

int main(int argc, char **argv) {
  int stack_a[MAX_LEN];
  int stack_b[MAX_LEN];
  int *start_a = &stack_a[0], *start_b = &stack_b[0],
    *end_a = &stack_a[MAX_LEN-1], *end_b = &stack_b[MAX_LEN-1];
  int *first = start_a, *last = start_a;
  
}

void put(int x, int **p, int **q, int *start_a, int *start_b, int *end_a, int *end_b) {
  
}

// update given pointer to point to the next element
// within the same stack add 1 to its address
// when the top of stack is reached, reassign pointer to the start
// of another stack
void inc_ptr(int **stack_ptr, int *start_a, int *start_b, int *end_a, int *end_b) {
  
}

int is_within(int *ptr, int *q, int *p) {
  return (q <= ptr && ptr <= p);
}

// print all values between q and p, given stacks a and b, specified by their
// q and p boundaries
// when q is in one stack and p is in another, print all values between q and
// top of its stack, and all the values between q of b stack and p
void print_all(int *q, int *p, int *start_a, int *start_b, int *end_a, int *end_b) {
  int q_in_a = is_within(q, start_a, end_a), q_in_b = is_within(q, start_a, start_b);
  int p_in_a = is_within(p, start_a, end_a), p_in_b = is_within(p, start_b, end_b);
  
  if (!q_in_a || !q_in_b) {
    printf("Error: q pointer is not within any of the stacks (print_all)\n");
    return;
  }
  if (!p_in_a || !p_in_b) {
    printf("Error: p pointer is not within any of the stacks (print_all)\n");
    return;
  }

  if ((q_in_a && p_in_a) || (q_in_b && p_in_b)) {
    // print trivially
    if (q > p) {
      printf("Error: q > p (print_all)\n");
      return;
    }
    return;
  }

  int *q_end, p_start;
  if (q_in_a) {
    q_end = end_a;
    p_start = start_b;
  } else {
    q_end = end_b;
    p_start = start_a;
  }
  print_between(q, q_end);
  print_between(p_start, p);
}

void print_between(int *q, int *p) {
  while (q <= p) {
    printf("%d\n", *q);
    q++;
  }
}
