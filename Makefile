# $Header$

BINDIR = /usr/local/bin
MANDIR = /usr/local/man/iemtools/cat1

all:		readany writeany any.1

readany:	readany.c
		cc -O readany.c -o readany

writeany:	writeany.c
		cc -O writeany.c -o writeany

install:	all
		cp -p readany writeany $(BINDIR)
		cp -p any.1 $(MANDIR)/readany.1
		ln $(MANDIR)/readany.1 $(MANDIR)/writeany.1

clean:
		rm *.o a.out core

clobber:	clean
		rm readany writeany

