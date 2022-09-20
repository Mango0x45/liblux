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
	mkdir -p ${PREFIX}/include ${PREFIX}/lib ${MANDIR}/man0 ${MANDIR}/man3
	cp ${outputs} ${PREFIX}/lib
	cp lux.h ${PREFIX}/include
	cp man/*.0 ${MANDIR}/man0
	cp man/*.3 ${MANDIR}/man3
	file=/usr/share/groff/current/tmac/mdoc/doc-syms; \
		grep '^\.ds doc-str-Lb-liblux' $$file > /dev/null || \
		cat man/Lb-desc.tmac >> $$file

clean:
	rm -f ${outputs} liblux.o
