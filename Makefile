# $Header$

BINDIR = /usr/ih/bin
MANDIR = /usr/ih/man/cat1

all:		readany writeany any.1

readany:	readany.c
		$(CC) -O readany.c -o readany

writeany:	writeany.c
		$(CC) -O writeany.c -o writeany

install:	all
		cp -p readany writeany $(BINDIR)
		cp -p any.1 $(MANDIR)/readany.1
		ln $(MANDIR)/readany.1 $(MANDIR)/writeany.1

clean:
		rm -f *.o a.out core

clobber:	clean
		rm -f readany writeany

