/*
 * Library file_header type test program
 *
 * Copyright (C) 2008-2020, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "olecf_test_functions.h"
#include "olecf_test_libbfio.h"
#include "olecf_test_libcerror.h"
#include "olecf_test_libolecf.h"
#include "olecf_test_macros.h"
#include "olecf_test_memory.h"
#include "olecf_test_unused.h"

#include "../libolecf/libolecf_allocation_table.h"
#include "../libolecf/libolecf_file_header.h"

uint8_t olecf_test_file_header_data1[ 512 ] = {
	0xd0, 0xcf, 0x11, 0xe0, 0xa1, 0xb1, 0x1a, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0xfe, 0xff, 0x09, 0x00,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

uint8_t olecf_test_file_header_error_data1[ 512 ] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0xfe, 0xff, 0x09, 0x00,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

#if defined( __GNUC__ ) && !defined( LIBOLECF_DLL_IMPORT )

/* Tests the libolecf_file_header_initialize function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_file_header_initialize(
     void )
{
	libcerror_error_t *error            = NULL;
	libolecf_file_header_t *file_header = NULL;
	int result                          = 0;

#if defined( HAVE_OLECF_TEST_MEMORY )
	int number_of_malloc_fail_tests     = 1;
	int number_of_memset_fail_tests     = 1;
	int test_number                     = 0;
#endif

	/* Test regular cases
	 */
	result = libolecf_file_header_initialize(
	          &file_header,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libolecf_file_header_free(
	          &file_header,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libolecf_file_header_initialize(
	          NULL,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	file_header = (libolecf_file_header_t *) 0x12345678UL;

	result = libolecf_file_header_initialize(
	          &file_header,
	          &error );

	file_header = NULL;

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_OLECF_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libolecf_file_header_initialize with malloc failing
		 */
		olecf_test_malloc_attempts_before_fail = test_number;

		result = libolecf_file_header_initialize(
		          &file_header,
		          &error );

		if( olecf_test_malloc_attempts_before_fail != -1 )
		{
			olecf_test_malloc_attempts_before_fail = -1;

			if( file_header != NULL )
			{
				libolecf_file_header_free(
				 &file_header,
				 NULL );
			}
		}
		else
		{
			OLECF_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			OLECF_TEST_ASSERT_IS_NULL(
			 "file_header",
			 file_header );

			OLECF_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libolecf_file_header_initialize with memset failing
		 */
		olecf_test_memset_attempts_before_fail = test_number;

		result = libolecf_file_header_initialize(
		          &file_header,
		          &error );

		if( olecf_test_memset_attempts_before_fail != -1 )
		{
			olecf_test_memset_attempts_before_fail = -1;

			if( file_header != NULL )
			{
				libolecf_file_header_free(
				 &file_header,
				 NULL );
			}
		}
		else
		{
			OLECF_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			OLECF_TEST_ASSERT_IS_NULL(
			 "file_header",
			 file_header );

			OLECF_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_OLECF_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_header != NULL )
	{
		libolecf_file_header_free(
		 &file_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_file_header_free function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_file_header_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libolecf_file_header_free(
	          NULL,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libolecf_file_header_read_data function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_file_header_read_data(
     void )
{
	libcerror_error_t *error            = NULL;
	libolecf_allocation_table_t *msat   = NULL;
	libolecf_file_header_t *file_header = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libolecf_file_header_initialize(
	          &file_header,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libolecf_allocation_table_initialize(
	          &msat,
	          0,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "msat",
	 msat );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_file_header_read_data(
	          file_header,
	          olecf_test_file_header_data1,
	          512,
	          msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libolecf_file_header_read_data(
	          NULL,
	          olecf_test_file_header_data1,
	          512,
	          msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libolecf_file_header_read_data(
	          file_header,
	          NULL,
	          512,
	          msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libolecf_file_header_read_data(
	          file_header,
	          olecf_test_file_header_data1,
	          0,
	          msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libolecf_file_header_read_data(
	          file_header,
	          olecf_test_file_header_data1,
	          (size_t) SSIZE_MAX + 1,
	          msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libolecf_file_header_read_data(
	          file_header,
	          olecf_test_file_header_data1,
	          512,
	          NULL,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test error case where signature is invalid
	 */
	result = libolecf_file_header_read_data(
	          file_header,
	          olecf_test_file_header_error_data1,
	          512,
	          msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libolecf_allocation_table_free(
	          &msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "msat",
	 msat );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libolecf_file_header_free(
	          &file_header,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( msat != NULL )
	{
		libolecf_allocation_table_free(
		 &msat,
		 NULL );
	}
	if( file_header != NULL )
	{
		libolecf_file_header_free(
		 &file_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_file_header_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_file_header_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle    = NULL;
	libcerror_error_t *error            = NULL;
	libolecf_allocation_table_t *msat   = NULL;
	libolecf_file_header_t *file_header = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libolecf_file_header_initialize(
	          &file_header,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libolecf_allocation_table_initialize(
	          &msat,
	          0,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "msat",
	 msat );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = olecf_test_open_file_io_handle(
	          &file_io_handle,
	          olecf_test_file_header_data1,
	          512,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_file_header_read_file_io_handle(
	          file_header,
	          file_io_handle,
	          msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libolecf_file_header_read_file_io_handle(
	          NULL,
	          file_io_handle,
	          msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libolecf_file_header_read_file_io_handle(
	          file_header,
	          NULL,
	          msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libolecf_file_header_read_file_io_handle(
	          file_header,
	          file_io_handle,
	          NULL,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up file IO handle
	 */
	result = olecf_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test data too small
	 */
	result = olecf_test_open_file_io_handle(
	          &file_io_handle,
	          olecf_test_file_header_data1,
	          8,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libolecf_file_header_read_file_io_handle(
	          file_header,
	          file_io_handle,
	          msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = olecf_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test data invalid
	 */
	result = olecf_test_open_file_io_handle(
	          &file_io_handle,
	          olecf_test_file_header_error_data1,
	          512,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libolecf_file_header_read_file_io_handle(
	          file_header,
	          file_io_handle,
	          msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = olecf_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libolecf_allocation_table_free(
	          &msat,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "msat",
	 msat );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libolecf_file_header_free(
	          &file_header,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( msat != NULL )
	{
		libolecf_allocation_table_free(
		 &msat,
		 NULL );
	}
	if( file_header != NULL )
	{
		libolecf_file_header_free(
		 &file_header,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBOLECF_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc OLECF_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] OLECF_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc OLECF_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] OLECF_TEST_ATTRIBUTE_UNUSED )
#endif
{
	OLECF_TEST_UNREFERENCED_PARAMETER( argc )
	OLECF_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBOLECF_DLL_IMPORT )

	OLECF_TEST_RUN(
	 "libolecf_file_header_initialize",
	 olecf_test_file_header_initialize );

	OLECF_TEST_RUN(
	 "libolecf_file_header_free",
	 olecf_test_file_header_free );

	OLECF_TEST_RUN(
	 "libolecf_file_header_read_data",
	 olecf_test_file_header_read_data );

	OLECF_TEST_RUN(
	 "libolecf_file_header_read_file_io_handle",
	 olecf_test_file_header_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBOLECF_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

