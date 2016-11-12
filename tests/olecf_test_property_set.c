/*
 * Library property_set type testing program
 *
 * Copyright (C) 2008-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "olecf_test_libcerror.h"
#include "olecf_test_libolecf.h"
#include "olecf_test_macros.h"
#include "olecf_test_memory.h"
#include "olecf_test_unused.h"

#include "../libolecf/libolecf_property_set.h"

#if defined( __GNUC__ )

/* Tests the libolecf_property_set_initialize function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_set_initialize(
     void )
{
	libcerror_error_t *error              = NULL;
	libolecf_property_set_t *property_set = NULL;
	int result                            = 0;

#if defined( HAVE_OLECF_TEST_MEMORY )
	int number_of_malloc_fail_tests       = 1;
	int number_of_memset_fail_tests       = 1;
	int test_number                       = 0;
#endif

	/* Test regular cases
	 */
	result = libolecf_property_set_initialize(
	          &property_set,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        OLECF_TEST_ASSERT_IS_NOT_NULL(
         "property_set",
         property_set );

        OLECF_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libolecf_property_set_free(
	          &property_set,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        OLECF_TEST_ASSERT_IS_NULL(
         "property_set",
         property_set );

        OLECF_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libolecf_property_set_initialize(
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

	property_set = (libolecf_property_set_t *) 0x12345678UL;

	result = libolecf_property_set_initialize(
	          &property_set,
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

	property_set = NULL;

#if defined( HAVE_OLECF_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libolecf_property_set_initialize with malloc failing
		 */
		olecf_test_malloc_attempts_before_fail = test_number;

		result = libolecf_property_set_initialize(
		          &property_set,
		          &error );

		if( olecf_test_malloc_attempts_before_fail != -1 )
		{
			olecf_test_malloc_attempts_before_fail = -1;

			if( property_set != NULL )
			{
				libolecf_property_set_free(
				 &property_set,
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
			 "property_set",
			 property_set );

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
		/* Test libolecf_property_set_initialize with memset failing
		 */
		olecf_test_memset_attempts_before_fail = test_number;

		result = libolecf_property_set_initialize(
		          &property_set,
		          &error );

		if( olecf_test_memset_attempts_before_fail != -1 )
		{
			olecf_test_memset_attempts_before_fail = -1;

			if( property_set != NULL )
			{
				libolecf_property_set_free(
				 &property_set,
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
			 "property_set",
			 property_set );

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
	if( property_set != NULL )
	{
		libolecf_property_set_free(
		 &property_set,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) */

/* Tests the libolecf_property_set_free function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_set_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libolecf_property_set_free(
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

#if defined( __GNUC__ )

	OLECF_TEST_RUN(
	 "libolecf_property_set_initialize",
	 olecf_test_property_set_initialize );

#endif /* defined( __GNUC__ ) */

	OLECF_TEST_RUN(
	 "libolecf_property_set_free",
	 olecf_test_property_set_free );

#if defined( __GNUC__ )

	/* TODO: add tests for libolecf_property_set_read */

#endif /* defined( __GNUC__ ) */

	/* TODO: add tests for libolecf_property_set_get_class_identifier */

	/* TODO: add tests for libolecf_property_set_get_number_of_sections */

	/* TODO: add tests for libolecf_property_set_get_section_by_index */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

