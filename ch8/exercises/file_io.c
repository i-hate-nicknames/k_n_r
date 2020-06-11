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
                       {1, (char *) 0, (char *) 0, _WRITE, 0},
                       {2, (char *) 0, (char *) 0, _WRITE | _UNBUF, 0}
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int fflush(FILE *);
int fclose(FILE *);
int fseek(FILE *, long, int);
int get_bufsize(FILE *);

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->chars_left >= 0                         \
                 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x, p) (--(p)->chars_left >= 0                       \
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
    lseek(fd, 0L, SEEK_END);
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

int _flushbuf(int ch, FILE *fp) {
  int bufsize;
  int result;
  if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE) {
    return EOF;
  }
  bufsize = get_bufsize(fp);
  // initializing fresh fp, create a new buffer
  if (fp->base == NULL) {
    fp->base = (char *) malloc(bufsize);
    if (fp->base == NULL) {
      return EOF;
    }
    fp->ptr = fp->base;
    fp->chars_left = bufsize - 1;
  }

  *fp->ptr++ = (unsigned char) ch;
  // flush the buffer when it's full
  if (fp->chars_left <= 0) {
    if (fflush(fp) != 0) {
      return EOF;
    }
  }
  return ch;
}

int fflush(FILE *fp) {
  if (fp->flag & _UNBUF) {
    return 0;
  }
  if (fp->flag & (_EOF | _ERR)) {
    return EOF;
  }
  if (fp->flag & _READ) {
    fp->ptr = fp->base;
    fp->chars_left = get_bufsize(fp);
  }
  // for write mode files, dump buffer to fd
  if (fp->flag & _WRITE) {
    int to_write = BUF_SIZE - fp->chars_left;
    int written = write(fp->fd, fp->base, to_write);
    fp->ptr = fp->base;
    fp->chars_left = get_bufsize(fp);
    if (written != to_write) {
      if (written == -1) {
        fp->flag |= _ERR;
      } else {
        fp->flag |= _EOF;
      }
      return EOF;
    }
  }
  return 0;
}

int fclose(FILE *fp) {
  int flush_result = fflush(fp);
  int close_result = close(fp->fd);
  free(fp->base);
  fp->base = NULL;
  fp->ptr = NULL;
  fp->chars_left = 0;
  fp->flag = 0;
  if (flush_result || close_result) {
    return EOF;
  }
  return 0;
}

int _fseek_read(FILE *fp, long offset) {

}

int _fseek_write(FILE *fp, long offset) {

}

long _calc_seek_offset(FILE *fp, long offset, int whence) {
  int bufsize = get_bufsize(fp);
  // for writes, we first write in the buffer, so the effective
  // position in the file is position of fd plus the number of
  // characters we wrote to the buffer
  // Return requested offset plus the actual position
  if (fp->flag & _WRITE) {
    return offset + bufsize - fp->chars_left;
  }
  // for reads, we read a chunk into the buffer, so the position
  // in fd is actually bigger than the "actual" position in the file.
  // We need to substract the number of characters we haven't consumed
  // yet from the buffer
  if (fp->flag & _READ) {
    return offset - fp->chars_left;
  }
}

int fseek(FILE *fp, long offset, int whence) {
  int final_offset = offset;
  // the position is related to current position, so we need to count
  // in buffering
  if (whence == SEEK_CUR) {
    final_offset = _calc_seek_offset(fp, offset, whence);
  }
  fflush(fp);
  fp->flag &= ~_EOF; // clear EOF flag as per specification
  return lseek(fp->fd, final_offset, whence);
}

int get_bufsize(FILE *fp) {
  return (fp->flag & _UNBUF) ? 1 : BUF_SIZE;
}

int main() {
  FILE *fp = fopen("test.test", "r");
  for (int i = 0; i < 20; i++) {
    /* fseek(fp, 1, SEEK_SET); */
    fflush(fp); // todo: fix fflush bug before proceeding with fseek
    int c = getc(fp);
    putc(c, stdout);
  }
  fflush(stdout);
  fclose(fp);
  return 0;
  
  fp = fopen("test.test", "w");
  /* int val = _fillbuf(fp); */
  for (int i = 0; i < 10; i++) {
    for (char c = '0'; c <= '9'; c++) {
      putc(c, fp);
    }
  }
  fclose(fp);
}
