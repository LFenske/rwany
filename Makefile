# $Header$

BINDIR = /usr/ih/bin
MANDIR = /usr/ih/man/cat1

all:		readany writeany any.1

readany:	readany.c  common.o common.h
		$(CC) -O readany.c  common.o -o readany

writeany:	writeany.c common.o common.h
		$(CC) -O writeany.c common.o -o writeany

common.o:	common.c common.h
		$(CC) -O -c common.c

install:	all
		cp -p readany writeany $(BINDIR)
		cp -p any.1 $(MANDIR)/readany.1
		ln $(MANDIR)/readany.1 $(MANDIR)/writeany.1

clean:
		rm -f *.o a.out core

clobber:	clean
		rm -f readany writeany

