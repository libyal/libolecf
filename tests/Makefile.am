AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@

if HAVE_PYTHON
TESTS_PYOLECF  = \
	test_pyolecf_set_ascii_codepage.sh \
	test_pyolecf_open_close.sh
endif

TESTS = \
	test_set_ascii_codepage.sh \
	test_open_close.sh \
	test_olecfinfo.sh \
	test_olecfexport.sh \
	$(TESTS_PYOLECF)

check_SCRIPTS = \
	pyolecf_test_open_close.py \
	pyolecf_test_set_ascii_codepage.py \
	test_olecfinfo.sh \
	test_olecfexport.sh \
	test_open_close.sh \
	test_pyolecf_open_close.sh \
	test_pyolecf_set_ascii_codepage.sh \
	test_runner.sh \
	test_set_ascii_codepage.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS =  \
	olecf_test_open_close \
	olecf_test_set_ascii_codepage

olecf_test_open_close_SOURCES = \
	olecf_test_libcerror.h \
	olecf_test_libolecf.h \
	olecf_test_libcstring.h \
	olecf_test_open_close.c

olecf_test_open_close_LDADD = \
	../libolecf/libolecf.la \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

olecf_test_set_ascii_codepage_SOURCES = \
	olecf_test_libcerror.h \
	olecf_test_libclocale.h \
	olecf_test_libolecf.h \
	olecf_test_libcstring.h \
	olecf_test_set_ascii_codepage.c

olecf_test_set_ascii_codepage_LDADD = \
	../libolecf/libolecf.la \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

