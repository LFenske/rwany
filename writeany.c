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
  if (-1 == (fd = open(argv[1], O_WRONLY))) {
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
    long index;
    long actual;
    thissize = size>BUFSIZE ? BUFSIZE : size;
    index = 0;
    while (index<thissize) {
      if ((actual = read(0, buf+index, thissize-index)) <= 0) {
	fprintf(stderr, "%s: read: not enough bytes\n", argv[0]);
	if (actual < 0)
	  perror("read from stdin");
	exit(2);
      }
      index += actual;
    }
    if (thissize != (actual=write(fd, buf, thissize))) {
      fprintf(stderr, "%s: write: at 0x%x tried 0x%x got 0x%x\n", argv[0], place, thissize, actual);
      perror("write to device");
      exit(2);
    }
    place += thissize;
    size  -= thissize;
  }
}
