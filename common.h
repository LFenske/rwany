#ifndef __common_h
#define __common_h

#define BUFSIZE 0x40000

#ifdef __common_c
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL char buf[BUFSIZE];

int getpos(char *arg, int fd, int prev);

#endif /* __common_h */
