include_HEADERS = \
	libolecf.h

pkginclude_HEADERS = \
	libolecf/codepage.h \
	libolecf/definitions.h \
	libolecf/error.h \
	libolecf/extern.h \
	libolecf/features.h \
	libolecf/ole.h \
	libolecf/types.h

EXTRA_DIST = \
	libolecf.h.in \
	libolecf/definitions.h.in \
	libolecf/features.h.in \
	libolecf/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libolecf.h
	-rm -f libolecf/definitions.h
	-rm -f libolecf/features.h
	-rm -f libolecf/types.h
	-rm -f Makefile

