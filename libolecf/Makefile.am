AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
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
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFOLE_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@LIBFWPS_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBOLECF_DLL_EXPORT@

lib_LTLIBRARIES = libolecf.la

libolecf_la_SOURCES = \
	libolecf.c \
	libolecf_allocation_table.c libolecf_allocation_table.h \
	libolecf_codepage.h \
	libolecf_compound_object_stream.c libolecf_compound_object_stream.h \
	libolecf_debug.c libolecf_debug.h \
	libolecf_directory_entry.c libolecf_directory_entry.h \
	libolecf_directory_list.c libolecf_directory_list.h \
	libolecf_directory_tree.c libolecf_directory_tree.h \
	libolecf_definitions.h \
	libolecf_error.c libolecf_error.h \
	libolecf_extern.h \
	libolecf_file.c libolecf_file.h \
	libolecf_file_header.c libolecf_file_header.h \
	libolecf_io_handle.c libolecf_io_handle.h \
	libolecf_item.c libolecf_item.h \
	libolecf_libbfio.h \
	libolecf_libcdata.h \
	libolecf_libcerror.h \
	libolecf_libclocale.h \
	libolecf_libcnotify.h \
	libolecf_libfdatetime.h \
	libolecf_libfguid.h \
	libolecf_libfole.h \
	libolecf_libfvalue.h \
	libolecf_libfwps.h \
	libolecf_libuna.h \
	libolecf_notify.c libolecf_notify.h \
	libolecf_ole.h \
	libolecf_property_section.c libolecf_property_section.h \
	libolecf_property_set.c libolecf_property_set.h \
	libolecf_property_set_stream.c libolecf_property_set_stream.h \
	libolecf_property_value.c libolecf_property_value.h \
	libolecf_stream.c libolecf_stream.h \
	libolecf_support.c libolecf_support.h \
	libolecf_types.h \
	libolecf_unused.h \
	olecf_compound_object.h \
	olecf_directory.h \
	olecf_file_header.h \
	olecf_property_set.h

libolecf_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFOLE_LIBADD@ \
	@LIBFVALUE_LIBADD@ \
	@LIBFWPS_LIBADD@ \
	@PTHREAD_LIBADD@

libolecf_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libolecf_definitions.h.in \
	libolecf.rc \
	libolecf.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libolecf_definitions.h
	/bin/rm -f libolecf.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libolecf ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libolecf_la_SOURCES)

