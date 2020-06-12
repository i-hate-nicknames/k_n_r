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

void *my_malloc(unsigned nbytes);
static Header *morecore(unsigned nunits);
void my_free(void *ptr);

static Header empty;
static Header *freeptr = NULL;

void *my_malloc(unsigned nbytes) {
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

#define NALLOC 1024 // min number of units allocated

static Header *morecore(unsigned nunits) {
  char *heap_ptr;
  Header *new_block;
  heap_ptr = sbrk(nunits * sizeof(Header));
  if (heap_ptr == NULL) {
    return NULL;
  }
  new_block = (Header *) heap_ptr;
  set_size(new_block, nunits);
  my_free((void *)(heap_ptr + 1));
  return new_block;
}

void my_free(void *ptr) {
  Header *to_free, *p;
  // ptr points to the space after the header, set to_free
  // to point to the header itself
  to_free = (Header *) ptr;
  to_free = to_free -1;
  for (p = freeptr; to_free <= p || to_free >= get_next(p); p = get_next(p)) {
    if (p >= get_next(p) && (to_free > p || to_free < get_next(p))) {
      break;
    }
  }

  freeptr = p;
}

int main() {
  return 0;
}
