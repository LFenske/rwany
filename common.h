#ifndef __common_h
#define __common_h

#define BUFSIZE (0x10*0x10000)

#ifdef __common_c
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL char buf[BUFSIZE];

long getpos(char *arg, int fd, long prev);

#endif /* __common_h */
