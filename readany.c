/* $Header$ */

#include <stdio.h>
#include <fcntl.h>

#define BUFSIZE 0x40000

char buf[BUFSIZE];

main(argc,argv)
int argc;
char **argv;
{
  int fd;
  long place,size;

  if (argc != 4) {
    fprintf(stderr, "usage: %s <filename> <start position> <length>\n", argv[0]);
    exit(1);
  }
  if (-1 == (fd = open(argv[1], O_RDONLY))) {
    perror("open");
    exit(2);
  }
  place = strtol(argv[2], (char **)NULL, 0);
  size  = strtol(argv[3], (char **)NULL, 0);
  if (-1 == lseek(fd, place, 0)) {
    perror("seek");
    exit(2);
  }
  while (size>0) {
    unsigned thissize;
    long actual;
    thissize = size>BUFSIZE ? BUFSIZE : size;
    if (thissize != (actual=read(fd, buf, thissize))) {
      fprintf(stderr, "%s: read: at 0x%x tried 0x%x got 0x%x\n", argv[0], place, thissize, actual);
      perror("read from device");
      exit(2);
    }
    if (thissize != write(1, buf, thissize)) {
      fprintf(stderr, "%s: write: not enough bytes\n", argv[0]);
      perror("write to stdout");
      exit(2);
    }
    place += thissize;
    size  -= thissize;
  }
}
