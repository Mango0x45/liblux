.POSIX:

CFLAGS = -std=c11 -pipe -O3 -Wall -Wextra -Werror -pedantic
PREFIX = /usr
MANDIR = ${PREFIX}/share/man

sources = liblux.o lux.h
outputs = liblux.so liblux.a

all: ${outputs}

liblux.o: liblux.c

liblux.a: ${sources}
	${AR} ${ARFLAGS} $@ liblux.o

liblux.so: ${sources}
	${CC} ${CFLAGS} -o $@ -fPIC -shared liblux.o

install:
	mkdir -p ${PREFIX}/include ${PREFIX}/lib ${MANDIR}/man3
	cp ${outputs} ${PREFIX}/lib
	cp lux.h ${PREFIX}/include
	cp man/* ${MANDIR}/man3

clean:
	rm -f ${outputs} liblux.o
