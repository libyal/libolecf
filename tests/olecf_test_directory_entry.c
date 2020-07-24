/*
 * Library directory_entry type test program
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

#include "olecf_test_libcdata.h"
#include "olecf_test_libcerror.h"
#include "olecf_test_libolecf.h"
#include "olecf_test_macros.h"
#include "olecf_test_memory.h"
#include "olecf_test_unused.h"

#include "../libolecf/libolecf_directory_entry.h"

#if defined( __GNUC__ ) && !defined( LIBOLECF_DLL_IMPORT )

/* Tests the libolecf_directory_entry_initialize function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_directory_entry_initialize(
     void )
{
	libcerror_error_t *error                    = NULL;
	libolecf_directory_entry_t *directory_entry = NULL;
	int result                                  = 0;

#if defined( HAVE_OLECF_TEST_MEMORY )
	int number_of_malloc_fail_tests             = 1;
	int number_of_memset_fail_tests             = 1;
	int test_number                             = 0;
#endif

	/* Test regular cases
	 */
	result = libolecf_directory_entry_initialize(
	          &directory_entry,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "directory_entry",
	 directory_entry );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libolecf_directory_entry_free(
	          &directory_entry,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "directory_entry",
	 directory_entry );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libolecf_directory_entry_initialize(
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

	directory_entry = (libolecf_directory_entry_t *) 0x12345678UL;

	result = libolecf_directory_entry_initialize(
	          &directory_entry,
	          &error );

	directory_entry = NULL;

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
		/* Test libolecf_directory_entry_initialize with malloc failing
		 */
		olecf_test_malloc_attempts_before_fail = test_number;

		result = libolecf_directory_entry_initialize(
		          &directory_entry,
		          &error );

		if( olecf_test_malloc_attempts_before_fail != -1 )
		{
			olecf_test_malloc_attempts_before_fail = -1;

			if( directory_entry != NULL )
			{
				libolecf_directory_entry_free(
				 &directory_entry,
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
			 "directory_entry",
			 directory_entry );

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
		/* Test libolecf_directory_entry_initialize with memset failing
		 */
		olecf_test_memset_attempts_before_fail = test_number;

		result = libolecf_directory_entry_initialize(
		          &directory_entry,
		          &error );

		if( olecf_test_memset_attempts_before_fail != -1 )
		{
			olecf_test_memset_attempts_before_fail = -1;

			if( directory_entry != NULL )
			{
				libolecf_directory_entry_free(
				 &directory_entry,
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
			 "directory_entry",
			 directory_entry );

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
	if( directory_entry != NULL )
	{
		libolecf_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_directory_entry_free function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_directory_entry_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libolecf_directory_entry_free(
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

/* Tests the libolecf_directory_entry_compare function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_directory_entry_compare(
     void )
{
	libcerror_error_t *error                           = NULL;
	libolecf_directory_entry_t *first_directory_entry  = NULL;
	libolecf_directory_entry_t *second_directory_entry = NULL;
	int result                                         = 0;

	/* Initialize test
	 */
	result = libolecf_directory_entry_initialize(
	          &first_directory_entry,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "first_directory_entry",
	 first_directory_entry );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libolecf_directory_entry_initialize(
	          &second_directory_entry,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "second_directory_entry",
	 second_directory_entry );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_directory_entry_compare(
	          first_directory_entry,
	          second_directory_entry,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBCDATA_COMPARE_EQUAL );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libolecf_directory_entry_compare(
	          NULL,
	          second_directory_entry,
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

	result = libolecf_directory_entry_compare(
	          first_directory_entry,
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

	/* Clean up
	 */
	result = libolecf_directory_entry_free(
	          &second_directory_entry,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "second_directory_entry",
	 second_directory_entry );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libolecf_directory_entry_free(
	          &first_directory_entry,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "first_directory_entry",
	 first_directory_entry );

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
	if( second_directory_entry != NULL )
	{
		libolecf_directory_entry_free(
		 &second_directory_entry,
		 NULL );
	}
	if( first_directory_entry != NULL )
	{
		libolecf_directory_entry_free(
		 &first_directory_entry,
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
	 "libolecf_directory_entry_initialize",
	 olecf_test_directory_entry_initialize );

	OLECF_TEST_RUN(
	 "libolecf_directory_entry_free",
	 olecf_test_directory_entry_free );

	/* TODO: add tests for libolecf_directory_entry_free_not_in_tree */

	OLECF_TEST_RUN(
	 "libolecf_directory_entry_compare",
	 olecf_test_directory_entry_compare );

	/* TODO: add tests for libolecf_directory_entry_read_data */

#endif /* defined( __GNUC__ ) && !defined( LIBOLECF_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

