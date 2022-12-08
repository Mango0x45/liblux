.POSIX:

PREFIX  = /usr
DPREFIX = ${DESTDIR}${PREFIX}
MANDIR  = ${DPREFIX}/share/man

GDIR = /usr/share/groff/site-tmac
DGDIR = ${DESTDIR}${GDIR}

all:
	@echo 'run `tup` to build the library' >&2

install:
	mkdir -p ${DPREFIX}/include ${DPREFIX}/lib \
	         ${MANDIR}/man3 ${MANDIR}/man3head \
		 ${DGDIR}
	cp src/liblux.a src/liblux.so ${DPREFIX}/lib
	cp src/lux.h ${DPREFIX}/include
	cp man/*.3 ${MANDIR}/man3
	cp man/*.3head ${MANDIR}/man3head
	sed '/^\.ds doc-str-Lb-liblux/d' ${GDIR}/mdoc.local >${DGDIR}/mdoc.local
	grep -v '^\.\\"' man/Lb-desc.tmac >>${DGDIR}/mdoc.local

clean:
	rm -rf .tup/ src/*.[ao] src/*.so
