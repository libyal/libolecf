/*
 * Library property_value type test program
 *
 * Copyright (C) 2008-2017, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libolecf/libolecf_property_value.h"

#if defined( __GNUC__ )

/* Tests the libolecf_property_value_initialize function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_initialize(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	int result                                = 0;

#if defined( HAVE_OLECF_TEST_MEMORY )
	int number_of_malloc_fail_tests           = 1;
	int number_of_memset_fail_tests           = 1;
	int test_number                           = 0;
#endif

	/* Test regular cases
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        OLECF_TEST_ASSERT_IS_NOT_NULL(
         "property_value",
         property_value );

        OLECF_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        OLECF_TEST_ASSERT_IS_NULL(
         "property_value",
         property_value );

        OLECF_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libolecf_property_value_initialize(
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

	property_value = (libolecf_property_value_t *) 0x12345678UL;

	result = libolecf_property_value_initialize(
	          &property_value,
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

	property_value = NULL;

#if defined( HAVE_OLECF_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libolecf_property_value_initialize with malloc failing
		 */
		olecf_test_malloc_attempts_before_fail = test_number;

		result = libolecf_property_value_initialize(
		          &property_value,
		          &error );

		if( olecf_test_malloc_attempts_before_fail != -1 )
		{
			olecf_test_malloc_attempts_before_fail = -1;

			if( property_value != NULL )
			{
				libolecf_property_value_free(
				 &property_value,
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
			 "property_value",
			 property_value );

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
		/* Test libolecf_property_value_initialize with memset failing
		 */
		olecf_test_memset_attempts_before_fail = test_number;

		result = libolecf_property_value_initialize(
		          &property_value,
		          &error );

		if( olecf_test_memset_attempts_before_fail != -1 )
		{
			olecf_test_memset_attempts_before_fail = -1;

			if( property_value != NULL )
			{
				libolecf_property_value_free(
				 &property_value,
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
			 "property_value",
			 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) */

/* Tests the libolecf_property_value_free function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libolecf_property_value_free(
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

#if defined( __GNUC__ )

/* Tests the libolecf_property_value_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_identifier(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	uint32_t identifier                       = 0;
	int identifier_is_set                     = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_identifier(
	          property_value,
	          &identifier,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	identifier_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_identifier(
	          NULL,
	          &identifier,
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

	if( identifier_is_set != 0 )
	{
		result = libolecf_property_value_get_identifier(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_value_type function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_value_type(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	uint32_t value_type                       = 0;
	int result                                = 0;
	int value_type_is_set                     = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_value_type(
	          property_value,
	          &value_type,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	value_type_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_value_type(
	          NULL,
	          &value_type,
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

	if( value_type_is_set != 0 )
	{
		result = libolecf_property_value_get_value_type(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_data_size function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_data_size(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	size_t data_size                          = 0;
	int data_size_is_set                      = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_data_size(
	          property_value,
	          &data_size,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	data_size_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_data_size(
	          NULL,
	          &data_size,
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

	if( data_size_is_set != 0 )
	{
		result = libolecf_property_value_get_data_size(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_data_as_boolean function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_data_as_boolean(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	uint8_t data_as_boolean                   = 0;
	int data_as_boolean_is_set                = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_data_as_boolean(
	          property_value,
	          &data_as_boolean,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	data_as_boolean_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_data_as_boolean(
	          NULL,
	          &data_as_boolean,
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

	if( data_as_boolean_is_set != 0 )
	{
		result = libolecf_property_value_get_data_as_boolean(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_data_as_16bit_integer function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_data_as_16bit_integer(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	uint16_t data_as_16bit_integer            = 0;
	int data_as_16bit_integer_is_set          = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_data_as_16bit_integer(
	          property_value,
	          &data_as_16bit_integer,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	data_as_16bit_integer_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_data_as_16bit_integer(
	          NULL,
	          &data_as_16bit_integer,
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

	if( data_as_16bit_integer_is_set != 0 )
	{
		result = libolecf_property_value_get_data_as_16bit_integer(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_data_as_32bit_integer function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_data_as_32bit_integer(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	uint32_t data_as_32bit_integer            = 0;
	int data_as_32bit_integer_is_set          = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_data_as_32bit_integer(
	          property_value,
	          &data_as_32bit_integer,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	data_as_32bit_integer_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_data_as_32bit_integer(
	          NULL,
	          &data_as_32bit_integer,
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

	if( data_as_32bit_integer_is_set != 0 )
	{
		result = libolecf_property_value_get_data_as_32bit_integer(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_data_as_64bit_integer function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_data_as_64bit_integer(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	uint64_t data_as_64bit_integer            = 0;
	int data_as_64bit_integer_is_set          = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_data_as_64bit_integer(
	          property_value,
	          &data_as_64bit_integer,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	data_as_64bit_integer_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_data_as_64bit_integer(
	          NULL,
	          &data_as_64bit_integer,
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

	if( data_as_64bit_integer_is_set != 0 )
	{
		result = libolecf_property_value_get_data_as_64bit_integer(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_data_as_filetime function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_data_as_filetime(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	uint64_t data_as_filetime                 = 0;
	int data_as_filetime_is_set               = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_data_as_filetime(
	          property_value,
	          &data_as_filetime,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	data_as_filetime_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_data_as_filetime(
	          NULL,
	          &data_as_filetime,
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

	if( data_as_filetime_is_set != 0 )
	{
		result = libolecf_property_value_get_data_as_filetime(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_data_as_utf8_string_size function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_data_as_utf8_string_size(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	size_t data_as_utf8_string_size           = 0;
	int data_as_utf8_string_size_is_set       = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_data_as_utf8_string_size(
	          property_value,
	          &data_as_utf8_string_size,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	data_as_utf8_string_size_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_data_as_utf8_string_size(
	          NULL,
	          &data_as_utf8_string_size,
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

	if( data_as_utf8_string_size_is_set != 0 )
	{
		result = libolecf_property_value_get_data_as_utf8_string_size(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_data_as_utf16_string_size function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_data_as_utf16_string_size(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	size_t data_as_utf16_string_size          = 0;
	int data_as_utf16_string_size_is_set      = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_data_as_utf16_string_size(
	          property_value,
	          &data_as_utf16_string_size,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	data_as_utf16_string_size_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_data_as_utf16_string_size(
	          NULL,
	          &data_as_utf16_string_size,
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

	if( data_as_utf16_string_size_is_set != 0 )
	{
		result = libolecf_property_value_get_data_as_utf16_string_size(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_value_data_size function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_value_data_size(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	size_t value_data_size                    = 0;
	int result                                = 0;
	int value_data_size_is_set                = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_value_data_size(
	          property_value,
	          &value_data_size,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	value_data_size_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_value_data_size(
	          NULL,
	          &value_data_size,
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

	if( value_data_size_is_set != 0 )
	{
		result = libolecf_property_value_get_value_data_size(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_value_boolean function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_value_boolean(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	uint8_t value_boolean                     = 0;
	int result                                = 0;
	int value_boolean_is_set                  = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_value_boolean(
	          property_value,
	          &value_boolean,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	value_boolean_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_value_boolean(
	          NULL,
	          &value_boolean,
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

	if( value_boolean_is_set != 0 )
	{
		result = libolecf_property_value_get_value_boolean(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_value_16bit function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_value_16bit(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	uint16_t value_16bit                      = 0;
	int result                                = 0;
	int value_16bit_is_set                    = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_value_16bit(
	          property_value,
	          &value_16bit,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	value_16bit_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_value_16bit(
	          NULL,
	          &value_16bit,
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

	if( value_16bit_is_set != 0 )
	{
		result = libolecf_property_value_get_value_16bit(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_value_32bit function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_value_32bit(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	uint32_t value_32bit                      = 0;
	int result                                = 0;
	int value_32bit_is_set                    = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_value_32bit(
	          property_value,
	          &value_32bit,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	value_32bit_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_value_32bit(
	          NULL,
	          &value_32bit,
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

	if( value_32bit_is_set != 0 )
	{
		result = libolecf_property_value_get_value_32bit(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_value_64bit function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_value_64bit(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	uint64_t value_64bit                      = 0;
	int result                                = 0;
	int value_64bit_is_set                    = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_value_64bit(
	          property_value,
	          &value_64bit,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	value_64bit_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_value_64bit(
	          NULL,
	          &value_64bit,
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

	if( value_64bit_is_set != 0 )
	{
		result = libolecf_property_value_get_value_64bit(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_value_filetime function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_value_filetime(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	uint64_t value_filetime                   = 0;
	int result                                = 0;
	int value_filetime_is_set                 = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_value_filetime(
	          property_value,
	          &value_filetime,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	value_filetime_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_value_filetime(
	          NULL,
	          &value_filetime,
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

	if( value_filetime_is_set != 0 )
	{
		result = libolecf_property_value_get_value_filetime(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_value_utf8_string_size function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_value_utf8_string_size(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	size_t value_utf8_string_size             = 0;
	int result                                = 0;
	int value_utf8_string_size_is_set         = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_value_utf8_string_size(
	          property_value,
	          &value_utf8_string_size,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	value_utf8_string_size_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_value_utf8_string_size(
	          NULL,
	          &value_utf8_string_size,
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

	if( value_utf8_string_size_is_set != 0 )
	{
		result = libolecf_property_value_get_value_utf8_string_size(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libolecf_property_value_get_value_utf16_string_size function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_property_value_get_value_utf16_string_size(
     void )
{
	libcerror_error_t *error                  = NULL;
	libolecf_property_value_t *property_value = NULL;
	size_t value_utf16_string_size            = 0;
	int result                                = 0;
	int value_utf16_string_size_is_set        = 0;

	/* Initialize test
	 */
	result = libolecf_property_value_initialize(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "property_value",
	 property_value );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libolecf_property_value_get_value_utf16_string_size(
	          property_value,
	          &value_utf16_string_size,
	          &error );

	OLECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	value_utf16_string_size_is_set = result;

	/* Test error cases
	 */
	result = libolecf_property_value_get_value_utf16_string_size(
	          NULL,
	          &value_utf16_string_size,
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

	if( value_utf16_string_size_is_set != 0 )
	{
		result = libolecf_property_value_get_value_utf16_string_size(
		          property_value,
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
	}
	/* Clean up
	 */
	result = libolecf_property_value_free(
	          &property_value,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "property_value",
	 property_value );

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
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) */

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
	 "libolecf_property_value_initialize",
	 olecf_test_property_value_initialize );

#endif /* defined( __GNUC__ ) */

	OLECF_TEST_RUN(
	 "libolecf_property_value_free",
	 olecf_test_property_value_free );

#if defined( __GNUC__ ) && defined( TODO )

	/* TODO: add tests for libolecf_property_value_read_data */

	/* TODO: add tests for libolecf_property_value_read_list_entry */

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_identifier",
	 olecf_test_property_value_get_identifier );

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_value_type",
	 olecf_test_property_value_get_value_type );

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_data_size",
	 olecf_test_property_value_get_data_size );

	/* TODO: add tests for libolecf_property_value_get_data */

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_data_as_boolean",
	 olecf_test_property_value_get_data_as_boolean );

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_data_as_16bit_integer",
	 olecf_test_property_value_get_data_as_16bit_integer );

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_data_as_32bit_integer",
	 olecf_test_property_value_get_data_as_32bit_integer );

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_data_as_64bit_integer",
	 olecf_test_property_value_get_data_as_64bit_integer );

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_data_as_filetime",
	 olecf_test_property_value_get_data_as_filetime );

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_data_as_utf8_string_size",
	 olecf_test_property_value_get_data_as_utf8_string_size );

	/* TODO: add tests for libolecf_property_value_get_data_as_utf8_string */

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_data_as_utf16_string_size",
	 olecf_test_property_value_get_data_as_utf16_string_size );

	/* TODO: add tests for libolecf_property_value_get_data_as_utf16_string */

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_value_data_size",
	 olecf_test_property_value_get_value_data_size );

	/* TODO: add tests for libolecf_property_value_get_value_data */

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_value_boolean",
	 olecf_test_property_value_get_value_boolean );

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_value_16bit",
	 olecf_test_property_value_get_value_16bit );

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_value_32bit",
	 olecf_test_property_value_get_value_32bit );

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_value_64bit",
	 olecf_test_property_value_get_value_64bit );

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_value_filetime",
	 olecf_test_property_value_get_value_filetime );

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_value_utf8_string_size",
	 olecf_test_property_value_get_value_utf8_string_size );

	/* TODO: add tests for libolecf_property_value_get_value_utf8_string */

	OLECF_TEST_RUN(
	 "libolecf_property_value_get_value_utf16_string_size",
	 olecf_test_property_value_get_value_utf16_string_size );

	/* TODO: add tests for libolecf_property_value_get_value_utf16_string */

#endif /* defined( __GNUC__ ) && defined( TODO ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

