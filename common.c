#define __common_c
#include "common.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int
getpos(char *arg, int fd, int prev)
{
  int value;
  int rel;
  int sign = 1;
  int relative = 0;
  switch (*arg) {
  case '+':
    rel = prev;
    relative = 1;
    arg++;
    break;
  case '-':
  {
    struct stat buf;
    if (0 != fstat(fd, &buf)) {
      perror("fstat");
      exit(2);
    }
    rel = buf.st_size;
    sign = -1;
    relative = 1;
    arg++;
    break;
  }
  default:
    rel = 0;
    break;
  }
  if (strchr(arg, ':') || strchr(arg, '.')) {
    int hour = 0, min = 0, sec = 0, frame = 0;
    char *p = arg;
    int curval = 0;
    while (1) {
      if (*p == ':' || *p == '.' || *p == '\0') {
        hour = min ;
        min  = sec ;
        sec  = curval;
        curval = 0;
        if (*p == '.') {
          frame = atoi(p+1);
          break;
        }
        if (*p == '\0') {
          break;
        }
      } else {
        curval = curval*10 + *p - '0';
      }
      p++;
    }
    value = (relative ? 0 : 44) + (((hour*60+min)*60+sec)*75+frame)*2352;
    /*fprintf(stderr, "%d:%.2d:%.2d.%.2d = %d\n", hour, min, sec, frame, value);*/
  } else {
    value = strtol(arg, (char **)NULL, 0);
  }
  return rel + sign*value;
}


