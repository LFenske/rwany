# $Header$

all:	readany writeany

readany:	readany.c
		cc -O readany.c -o readany

writeany:	writeany.c
		cc -O writeany.c -o writeany

install:	readany writeany
		cp -p readany writeany /usr/local/bin

clean:
		rm *.o a.out core

clobber:	clean
		rm readany writeany

