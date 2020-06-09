#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define EOF (-1)
#define BUF_SIZE 1024
#define OPEN_MAX 20
#define PERMS 0666

typedef struct _iobuf {
  int fd; // file descriptor
  char *base; // location of the buffer
  char *ptr; // next char pos
  int flag; // mode of file access
  int chars_left;
} FILE;

enum _flags {
             _READ = 01,
             _WRITE = 02,
             _UNBUF = 04,
             _EOF = 010,
             _ERR = 020
};

FILE _iob[OPEN_MAX] = {
                       {0, (char *) 0, (char *) 0, _READ, 0},
                       {0, (char *) 0, (char *) 0, _READ, 0},
                       {0, (char *) 0, (char *) 0, _READ, 0}
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define stdin (&_iob[0]);
#define stdout (&_iob[1]);
#define stderr (&_iob[2]);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->chars_left >= 0                         \
                 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x, p) (--(p)->chars_left >=0                       \
                    ? *(p)->ptr++ = (x) : _flushbuf((x), (p)))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

FILE *fopen(char *name, char *mode) {
  int fd;
  FILE *fp;
  int free_idx = -1;
  if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
    return NULL;
  }

  for (int i = 0; i < OPEN_MAX; i++) {
    if ((fp->flag & (_READ | _WRITE)) == 0) {
      free_idx = i;
      break;
    }
  }

  if (free_idx == -1) {
    return NULL;
  }
  fp = &(_iob[free_idx]);

  if (*mode == 'w') {
    fd = creat(name, PERMS);
  }
  else if (*mode == 'a') {
    if ((fd = open(name, O_WRONLY, 0)) == -1) {
      fd = creat(name, PERMS);
    }
    lseek(fd, 0L, SEEK_SET);
  }
  else {
    fd = open(name, O_RDONLY, 0);
  }
  if (fd == -1) {
    return NULL;
  }
  fp->fd = fd;
  fp->chars_left = 0;
  fp->base = NULL;
  fp->flag = (*mode == 'r') ? _READ : _WRITE;
  return fp;
}

/** allocate and fill the input buffer */
int _fillbuf(FILE *fp) {
  int bufsize;
  int result;
  if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
    return EOF;
  }
  bufsize = (fp->flag & _UNBUF) ? 1 : BUF_SIZE;
  if (fp->base == NULL) {
    fp->base = (char *) malloc(bufsize);
    if (fp->base == NULL) {
      return EOF;
    }
  }
  fp->ptr = fp->base;
  fp->chars_left = read(fp->fd, fp->ptr, bufsize);
  if (fp->chars_left <= 0) {
    if (fp->chars_left == 0) {
      fp->flag |= _EOF;
    } else {
      fp->flag |= _ERR;
    }
    fp->chars_left = 0;
    return EOF;
  }
  // take first character and advance buffer
  result = *fp->ptr;
  fp->ptr++;
  fp->chars_left--;
  return result;
}

int main() {
  FILE *fp = fopen("test.test", "r");
  int val = _fillbuf(fp);
  return val;
}
