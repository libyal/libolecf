# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir3)"
pyexecdir = $(pyexecdir3)

if HAVE_PYTHON3
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBOLECF_DLL_IMPORT@

am_pyolecf_la_rpath = -rpath $(pyexecdir3)

BUILT_SOURCES = \
	pyolecf.c pyolecf.h \
	pyolecf_codepage.c pyolecf_codepage.h \
	pyolecf_datetime.c pyolecf_datetime.h \
	pyolecf_error.c pyolecf_error.h \
	pyolecf_file.c pyolecf_file.h \
	pyolecf_file_object_io_handle.c pyolecf_file_object_io_handle.h \
	pyolecf_guid.c pyolecf_guid.h \
	pyolecf_integer.c pyolecf_integer.h \
	pyolecf_item.c pyolecf_item.h \
	pyolecf_item_types.c pyolecf_item_types.h \
	pyolecf_items.c pyolecf_items.h \
	pyolecf_libbfio.h \
	pyolecf_libcerror.h \
	pyolecf_libclocale.h \
	pyolecf_libfguid.h \
	pyolecf_libolecf.h \
	pyolecf_property_section.c pyolecf_property_section.h \
	pyolecf_property_sections.c pyolecf_property_sections.h \
	pyolecf_property_set.c pyolecf_property_set.h \
	pyolecf_property_set_stream.c pyolecf_property_set_stream.h \
	pyolecf_property_value.c pyolecf_property_value.h \
	pyolecf_property_values.c pyolecf_property_values.h \
	pyolecf_python.h \
	pyolecf_stream.c pyolecf_stream.h \
	pyolecf_unused.h \
	pyolecf_value_types.c pyolecf_value_types.h

pyexec_LTLIBRARIES = pyolecf.la

nodist_pyolecf_la_SOURCES = $(BUILT_SOURCES)

pyolecf_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libolecf/libolecf.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFGUID_LIBADD@

pyolecf_la_CPPFLAGS = $(PYTHON3_CPPFLAGS)
pyolecf_la_LDFLAGS  = -module -avoid-version $(PYTHON3_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyolecf/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyolecf*.[ch]

distclean: clean
	/bin/rm -f Makefile

