/* $Header$ */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "common.h"


void usage(progname)
char *progname;
{
  fprintf(stderr, "\
usage: %s <filename> <start pos> <end pos>\n\
\n\
Positions can have the forms <number>, +<number>, or -<number> meaning\n\
absolute position, relative to previous parameter, relative to end of file.\n\
Positions can be of the form hour:minute:second.frame for CD wav offsets.\n\
", progname);
}


int main(argc,argv)
int argc;
char **argv;
{
  int fd;
  long place,size;

  if (argc != 4) {
    usage(argv[0]);
    exit(1);
  }
  if (-1 == (fd = open(argv[1], O_WRONLY))) {
    perror("open");
    exit(2);
  }
  place = getpos(argv[2],fd,0);
  size  = getpos(argv[3],fd,place)-place;
  if (size < 0) {
    fprintf(stderr, "<start pos> must be before <end pos>\n\n");
    usage(argv[0]);
    exit(1);
  }
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
      fprintf(stderr, "%s: write: at 0x%lx tried 0x%x got 0x%lx\n",
              argv[0], place, thissize, actual);
      perror("write to device");
      exit(2);
    }
    place += thissize;
    size  -= thissize;
  }
  return(0);
}
