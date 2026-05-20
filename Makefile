PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

install: terry.h
	mkdir -p ${DESTDIR}${PREFIX}/include
	cp -f $+ ${DESTDIR}${PREFIX}/include
