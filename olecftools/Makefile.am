AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
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
	olecftools_getopt.c olecftools_getopt.h \
	olecftools_i18n.h \
	olecftools_libbfio.h \
	olecftools_libcerror.h \
	olecftools_libcfile.h \
	olecftools_libclocale.h \
	olecftools_libcnotify.h \
	olecftools_libcpath.h \
	olecftools_libfdatetime.h \
	olecftools_libfguid.h \
	olecftools_libolecf.h \
	olecftools_libuna.h \
	olecftools_output.c olecftools_output.h \
	olecftools_signal.c olecftools_signal.h \
	olecftools_unused.h

olecfexport_LDADD = \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libolecf/libolecf.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

olecfinfo_SOURCES = \
	info_handle.c info_handle.h \
	olecfinfo.c \
	olecftools_getopt.c olecftools_getopt.h \
	olecftools_i18n.h \
	olecftools_libbfio.h \
	olecftools_libcerror.h \
	olecftools_libclocale.h \
	olecftools_libcnotify.h \
	olecftools_libfdatetime.h \
	olecftools_libfguid.h \
	olecftools_libfole.h \
	olecftools_libolecf.h \
	olecftools_libuna.h \
	olecftools_output.c olecftools_output.h \
	olecftools_signal.c olecftools_signal.h \
	olecftools_unused.h

olecfinfo_LDADD = \
	@LIBFOLE_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libolecf/libolecf.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

olecfmount_SOURCES = \
	mount_dokan.c mount_dokan.h \
	mount_file_entry.c mount_file_entry.h \
	mount_file_system.c mount_file_system.h \
	mount_fuse.c mount_fuse.h \
	mount_handle.c mount_handle.h \
	olecfmount.c \
	olecftools_getopt.c olecftools_getopt.h \
	olecftools_i18n.h \
	olecftools_libcerror.h \
	olecftools_libclocale.h \
	olecftools_libcnotify.h \
	olecftools_libcpath.h \
	olecftools_libfdatetime.h \
	olecftools_libolecf.h \
	olecftools_output.c olecftools_output.h \
	olecftools_signal.c olecftools_signal.h \
	olecftools_unused.h

olecfmount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libolecf/libolecf.la \
	@LIBCERROR_LIBADD@ \
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

