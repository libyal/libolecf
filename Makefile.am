ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	include \
	common \
	libcerror \
	libcthreads \
	libcdata \
	libclocale \
	libcnotify \
	libcsplit \
	libuna \
	libcfile \
	libcpath \
	libbfio \
	libfdatetime \
	libfguid \
	libfole \
	libfvalue \
	libfwps \
	libolecf \
	olecftools \
	pyolecf \
	po \
	manuals \
	tests \
	ossfuzz \
	msvscpp

DPKG_FILES = \
	dpkg/changelog \
	dpkg/changelog.in \
	dpkg/compat \
	dpkg/control \
	dpkg/copyright \
	dpkg/rules \
	dpkg/libolecf.install \
	dpkg/libolecf-dev.install \
	dpkg/libolecf-python3.install \
	dpkg/libolecf-tools.install \
	dpkg/source/format

GETTEXT_FILES = \
	config.rpath \
	po/Makevars.in

PKGCONFIG_FILES = \
	libolecf.pc.in

SETUP_PY_FILES = \
	pyproject.toml \
	setup.cfg \
	setup.cfg.in \
	setup.py

SPEC_FILES = \
	libolecf.spec \
	libolecf.spec.in

EXTRA_DIST = \
	$(DPKG_FILES) \
	$(GETTEXT_FILES) \
	$(PKGCONFIG_FILES) \
	$(SETUP_PY_FILES) \
	$(SPEC_FILES)

DISTCLEANFILES = \
	config.status \
	config.cache \
	config.log \
	libolecf.pc \
	libolecf.spec \
	Makefile \
	Makefile.in \
	po/Makevars

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = \
	libolecf.pc

libtool: @LIBTOOL_DEPS@
	cd $(srcdir) && $(SHELL) ./config.status --recheck

lib: library

library:
	(cd $(srcdir)/common && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcerror && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcthreads && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcdata && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libclocale && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcnotify && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcsplit && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libuna && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcfile && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcpath && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libbfio && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfdatetime && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfguid && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfole && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfvalue && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfwps && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libolecf && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/po && $(MAKE) $(AM_MAKEFLAGS))

