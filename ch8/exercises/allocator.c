#include <stdio.h>

typedef union _hdr {
  struct {
    union _hdr *next; // next block on the free list
    unsigned size; // size of this block 
  } s;
  long __align;
} Header;

#define get_next(hptr) ((hptr)->s.next)
#define set_next(htpr, to_set) ((htpr)->s.next = (to_set))
#define get_size(hptr) ((hptr)->s.size)
#define set_size(hptr, to_set) ((hptr)->s.size = (to_set))

void *malloc(unsigned nbytes);
Header *morecore(unsigned nunits);
void free(void *ptr);

static Header empty;
static Header *freeptr = NULL;

void *malloc(unsigned nbytes) {
  Header *prev;
  unsigned nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
  // initialize empty list and point freeptr to it
  if (freeptr == NULL) {
    empty.s.next = &empty;
    empty.s.size = 0;
    freeptr = &empty;
  }
  prev = freeptr;
  for (Header *p = get_next(prev); ; prev = p, p = get_next(p)) {
    if (get_size(p) >= nunits) {
      // big enough
      if (get_size(p) == nunits) {
        // fits exactly
        set_next(prev, get_next(p));
      } else {
        // allocate tail end
        set_size(p, get_size(p) - nunits);
        p += get_size(p);
        set_size(p, nunits);
      }
      freeptr = prev;
    }
    if (p == freeptr) {
      p = morecore(nunits);
      if (p == NULL) {
        return NULL;
      }
    }
  }
}

int main() {
  printf("long %d, long long %d\n", sizeof(long), sizeof(long long));
  return 0;
}
