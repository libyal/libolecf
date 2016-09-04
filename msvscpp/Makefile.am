MSVSCPP_FILES = \
	dokan/dokan.vcproj \
	libbfio/libbfio.vcproj \
	libcdata/libcdata.vcproj \
	libcerror/libcerror.vcproj \
	libcfile/libcfile.vcproj \
	libclocale/libclocale.vcproj \
	libcnotify/libcnotify.vcproj \
	libcpath/libcpath.vcproj \
	libcsplit/libcsplit.vcproj \
	libcstring/libcstring.vcproj \
	libcsystem/libcsystem.vcproj \
	libcthreads/libcthreads.vcproj \
	libfdatetime/libfdatetime.vcproj \
	libfguid/libfguid.vcproj \
	libfole/libfole.vcproj \
	libfvalue/libfvalue.vcproj \
	libfwps/libfwps.vcproj \
	libolecf/libolecf.vcproj \
	libuna/libuna.vcproj \
	olecf_test_error/olecf_test_error.vcproj \
	olecf_test_get_version/olecf_test_get_version.vcproj \
	olecf_test_open_close/olecf_test_open_close.vcproj \
	olecf_test_set_ascii_codepage/olecf_test_set_ascii_codepage.vcproj \
	olecfexport/olecfexport.vcproj \
	olecfinfo/olecfinfo.vcproj \
	olecfmount/olecfmount.vcproj \
	pyolecf/pyolecf.vcproj \
	libolecf.sln

SCRIPT_FILES = \
	scripts/vs2008_x64.sh \
	scripts/vs2008_x64_sln.sed \
	scripts/vs2008_x64_vcproj.sed \
	scripts/vs2010_x64.sh \
	scripts/vs2010_x64_sln.sed \
	scripts/vs2010_x64_vcxproj.sed

EXTRA_DIST = \
	$(MSVSCPP_FILES) \
	$(SCRIPT_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

