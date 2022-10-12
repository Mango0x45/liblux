.POSIX:

PREFIX  = /usr
DPREFIX = ${DESTDIR}${PREFIX}
MANDIR  = ${DPREFIX}/share/man

all:
	@echo 'run `tup` to build the library' >&2

install:
	mkdir -p ${DPREFIX}/include ${DPREFIX}/lib ${MANDIR}/man0 ${MANDIR}/man3
	cp src/liblux.a src/liblux.so ${DPREFIX}/lib
	cp src/lux.h ${DPREFIX}/include
	cp man/*.0 ${MANDIR}/man0
	cp man/*.3 ${MANDIR}/man3
	file=/usr/share/groff/site-tmac/mdoc.local; \
		grep '^\.ds doc-str-Lb-liblux' $$file > /dev/null || \
		cat man/Lb-desc.tmac >> $$file

clean:
	rm -rf .tup/ src/*.[ao] src/*.so
