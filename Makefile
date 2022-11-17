.POSIX:

PREFIX  = /usr
DPREFIX = ${DESTDIR}${PREFIX}
MANDIR  = ${DPREFIX}/share/man

GFILE = /usr/share/groff/site-tmac/mdoc.local

all:
	@echo 'run `tup` to build the library' >&2

install:
	mkdir -p ${DPREFIX}/include ${DPREFIX}/lib \
	         ${MANDIR}/man3 ${MANDIR}/man3head
	cp src/liblux.a src/liblux.so ${DPREFIX}/lib
	cp src/lux.h                  ${DPREFIX}/include
	cp man/*.3     ${MANDIR}/man3
	cp man/*.3head ${MANDIR}/man3head
	sed  -i '/^\.ds doc-str-Lb-liblux/d' ${GFILE}
	grep -v '^\.\\"' man/Lb-desc.tmac >> ${GFILE}

clean:
	rm -rf .tup/ src/*.[ao] src/*.so
