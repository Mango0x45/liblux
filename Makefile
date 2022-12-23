.POSIX:

PREFIX  = /usr
DPREFIX = ${DESTDIR}${PREFIX}
MANDIR  = ${DPREFIX}/share/man

GDIR = /usr/share/groff/site-tmac

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
	@>&2 printf '\n\nIn order to ensure that manual pages render properly, run the following command:\n\n    $$ echo '"'%s'"' \\\n          >${GDIR}/mdoc.local\n' "`grep '^\.ds' man/Lb-desc.tmac`"

clean:
	rm -rf .tup/ src/*.[ao] src/*.so
