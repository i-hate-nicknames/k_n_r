#include <stdio.h>
#include <unistd.h>

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

#define in_range(x, a, b) ((x) >= (a) && (x) <= (b))

void *my_malloc(unsigned nbytes);
void *my_calloc(unsigned n, unsigned size);
static Header *morecore(unsigned nunits);
void my_free(void *ptr);

static Header empty;

// this is entry point to the free list
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
  //  printf("want to allocated %d blocks\n", nunits);
  prev = freeptr;
  for (Header *p = get_next(prev); ; prev = p, p = get_next(p)) {
    if (get_size(p) >= nunits) {
      // big enough
      if (get_size(p) == nunits) {
        // fits exactly, remove this block from the free list
        // preventing any further allocation here
        set_next(prev, get_next(p));
      } else {
        //    printf("Found a block: %p, size: %d\n", p, get_size(p));
        
        // allocate tail end, effectively create a new block of requested
        // size within current free block. Update size accordingly
        int size_rem = get_size(p) - nunits;
        // update size of the current block to be what remains after we
        // allocate a new block in tail
        set_size(p, size_rem);
        // advance pointer to point to the newly created block of requested
        // size
        p += size_rem;
        // set size of this block
        set_size(p, nunits);
      }
      //      printf("allocated a block of %d units\n", nunits);
      freeptr = prev;
      return (void *)(p+1);
    }
    // we made a tour over all blocks in free list but didnt find a suitable
    // free block, create and add a new free block to the list
    if (p == freeptr) {
      p = morecore(nunits);
      if (p == NULL) {
        return NULL;
      }
      p = freeptr;
    }
  }
}

#define NALLOC 1024 // min number of units allocated

// Ask OS for more memory, returning address of the newly allocated block
// the block is added to freelist and the space immediately after it can
// be returned to the user
static Header *morecore(unsigned nunits) {
  char *heap_ptr;
  Header *new_block;
  unsigned size = (nunits < NALLOC) ? NALLOC : nunits;
  printf("Asking for %d blocks from the system\n", size);
  heap_ptr = sbrk(size * sizeof(Header));
  if (heap_ptr == (char *) -1) {
    return NULL;
  }
  new_block = (Header *) heap_ptr;
  set_size(new_block,  size);
  // "free" the block, effectively adding it to the freelist
  my_free((void *)(new_block + 1));
  return new_block;
}

// Frees a block located at ptr. Block header will be added
// to the free list. ptr must point to the memory that immediately
// follows the header, i.e. it could be a pointer that has been returned
// to the client by my_malloc
void my_free(void *ptr) {
  Header *to_free, *p;
  // ptr points to the space after the header, set to_free
  // to point to the header itself
  to_free = (Header *) ptr;
  to_free = to_free - 1;

  // To preserve te invariant of the free list we need to find the right place in the list for
  // the new block.
  // If the new block is physically located between two other blocks, we need to insert it
  // in the list between them
  // If the new block is outside the list, i.e. to_free is less or bigger than any other
  // block in the list
  p = freeptr;
  while (!in_range(to_free, p, get_next(p))) {
    // reached the physical end of the list, where get_next(p) points to an address smaller than
    // p. In this case we check if to_free is physically outside of the list, and when it is,
    // there is no point of traversing list any further, we can't find a spot between blocks.
    if (p >= get_next(p) && (to_free > p || to_free < get_next(p))) {
      break;
    }
    p = get_next(p);
  }
  // insert to_free between p and get_next(p)
  if (to_free + get_size(to_free) == get_next(p)) {
    // adding will result in two consecutive free blocks, merge
    // them together by eliminating get_next(p) and adding its size to to_free
    set_size(to_free, get_size(to_free) + get_size(get_next(p)));
    set_next(to_free, get_next(get_next(p)));
  } else {
    // size is less, just link to_free to the next block
    set_next(to_free, get_next(p));
  }
  
  if (p + get_size(p) == to_free) {
    // adding will result in two consecutive blocks, p and to_free
    // merge them together eliminating to_free and adding its size to p
    set_size(p, get_size(p) + get_size(to_free));
    // to_free may have been merged with next block, so we need to take
    // its next
    set_next(p, get_next(to_free));
  } else {
    set_next(p, to_free);
  }
  // point freeptr to the block previous to the newly created, to help
  // finding it sooner
  freeptr = p;
}

// exercise 8_6
void *my_calloc(unsigned n, unsigned size) {
  Header *allocated = my_malloc(n * size);
  // end points to the next address after the allocated space
  char *end = (char *) allocated + get_size(allocated-1);
  for (char *c = (char *) allocated; c < end; c++) {
    *c = 0;
  }
  return allocated;
}

int main() {
  //void *p = my_malloc(1023 * sizeof(Header));
  //void *p2 = my_malloc(1023 * sizeof(Header));
  //my_free(p);
  int *p3 = (int *) my_malloc(2045 * 4);
  int *p4 = my_calloc(2000, sizeof(int));
  int *p5 = my_calloc(2000, sizeof(int));
  my_free(p4);
  return 0;
}
