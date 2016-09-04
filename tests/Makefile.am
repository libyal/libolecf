AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBOLECF_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYOLECF = \
	test_python_functions.sh \
	test_pyolecf_set_ascii_codepage.sh
endif

TESTS = \
	test_api_functions.sh \
	test_set_ascii_codepage.sh \
	test_olecfinfo.sh \
	test_olecfexport.sh \
	$(TESTS_PYOLECF)

check_SCRIPTS = \
	pyolecf_test_get_version.py \
	pyolecf_test_open_close.py \
	pyolecf_test_set_ascii_codepage.py \
	test_api_functions.sh \
	test_olecfinfo.sh \
	test_olecfexport.sh \
	test_pyolecf_set_ascii_codepage.sh \
	test_python_functions.sh \
	test_runner.sh \
	test_set_ascii_codepage.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	olecf_test_error \
	olecf_test_get_version \
	olecf_test_open_close \
	olecf_test_set_ascii_codepage

olecf_test_error_SOURCES = \
	olecf_test_error.c \
	olecf_test_libcstring.h \
	olecf_test_libolecf.h \
	olecf_test_macros.h \
	olecf_test_unused.h

olecf_test_error_LDADD = \
	../libolecf/libolecf.la \
	@LIBCSTRING_LIBADD@

olecf_test_get_version_SOURCES = \
	olecf_test_get_version.c \
	olecf_test_libcstring.h \
	olecf_test_libolecf.h \
	olecf_test_macros.h \
	olecf_test_unused.h

olecf_test_get_version_LDADD = \
	../libolecf/libolecf.la \
	@LIBCSTRING_LIBADD@

olecf_test_open_close_SOURCES = \
	olecf_test_libcerror.h \
	olecf_test_libcstring.h \
	olecf_test_libcsystem.h \
	olecf_test_libolecf.h \
	olecf_test_open_close.c

olecf_test_open_close_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libolecf/libolecf.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

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

