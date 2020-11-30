#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libolecf/.libs/libolecf.1.dylib && test -f ./pyolecf/.libs/pyolecf.so;
then
	install_name_tool -change /usr/local/lib/libolecf.1.dylib ${PWD}/libolecf/.libs/libolecf.1.dylib ./pyolecf/.libs/pyolecf.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

