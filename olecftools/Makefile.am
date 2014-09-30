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
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFOLE_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBFUSE_CPPFLAGS@ \
	@LIBOLECF_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	olecfexport \
	olecfinfo \
	olecfmount

olecfexport_SOURCES = \
	export_handle.c export_handle.h \
	log_handle.c log_handle.h \
	olecfexport.c \
	olecfoutput.c olecfoutput.h \
	olecftools_libbfio.h \
	olecftools_libcerror.h \
	olecftools_libcfile.h \
	olecftools_libclocale.h \
	olecftools_libcnotify.h \
	olecftools_libcpath.h \
	olecftools_libcsystem.h \
	olecftools_libfdatetime.h \
	olecftools_libfguid.h \
	olecftools_libolecf.h \
	olecftools_libuna.h

olecfexport_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	../libolecf/libolecf.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

olecfinfo_SOURCES = \
	info_handle.c info_handle.h \
	olecfinfo.c \
	olecfoutput.c olecfoutput.h \
	olecftools_libbfio.h \
	olecftools_libcerror.h \
	olecftools_libclocale.h \
	olecftools_libcnotify.h \
	olecftools_libcsystem.h \
	olecftools_libfdatetime.h \
	olecftools_libfguid.h \
	olecftools_libfole.h \
	olecftools_libolecf.h \
	olecftools_libuna.h

olecfinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBFOLE_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBUNA_LIBADD@ \
	../libolecf/libolecf.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

olecfmount_SOURCES = \
	mount_handle.c mount_handle.h \
	olecfmount.c \
	olecfoutput.c olecfoutput.h \
	olecftools_libcerror.h \
	olecftools_libclocale.h \
	olecftools_libcnotify.h \
	olecftools_libcstring.h \
	olecftools_libcsystem.h \
	olecftools_libfdatetime.h \
	olecftools_libolecf.h

olecfmount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBCSYSTEM_LIBADD@ \
	../libolecf/libolecf.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on olecfexport ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(olecfexport_SOURCES)
	@echo "Running splint on olecfinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(olecfinfo_SOURCES)
	@echo "Running splint on olecfmount ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(olecfmount_SOURCES)

