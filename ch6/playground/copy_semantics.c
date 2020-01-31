#include <stdio.h>

struct point {
  int x;
  int y;
};

struct sraka {
  int x;
  struct sraka *s;
};

struct point make_point(int x, int y);
void update(struct point p);
void update2(struct point *p);
void print_point(struct point p);

int main(void) {
  struct point p1 = make_point(2, 3);
  print_point(p1);
  update(p1);
  print_point(p1);
  update2(&p1);
  print_point(p1);
}

struct point make_point(int x, int y) {
  struct point tmp = {x, y};
  return tmp;
}

void update(struct point p) {
  p.x = 5;
  p.y = 5;
}

void update2(struct point *p) {
  p->x = 15;
  p->y = 15;
}

void print_point(struct point p) {
  printf("Point %d, %d\n", p.x, p.y);
}
