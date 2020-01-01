/*
 * Library item type test program
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

#include "olecf_test_libcerror.h"
#include "olecf_test_libolecf.h"
#include "olecf_test_macros.h"
#include "olecf_test_memory.h"
#include "olecf_test_unused.h"

#include "../libolecf/libolecf_item.h"

/* Tests the libolecf_item_free function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_item_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libolecf_item_free(
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

#if defined( __GNUC__ ) && !defined( LIBOLECF_DLL_IMPORT )

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

	/* TODO: add tests for libolecf_item_initialize */

#endif /* defined( __GNUC__ ) && !defined( LIBOLECF_DLL_IMPORT ) */

	OLECF_TEST_RUN(
	 "libolecf_item_free",
	 olecf_test_item_free );

#if defined( __GNUC__ ) && !defined( LIBOLECF_DLL_IMPORT )

	/* TODO: add tests for libolecf_item_get_type */

	/* TODO: add tests for libolecf_item_get_utf8_name_size */

	/* TODO: add tests for libolecf_item_get_utf8_name */

	/* TODO: add tests for libolecf_item_get_utf16_name_size */

	/* TODO: add tests for libolecf_item_get_utf16_name */

	/* TODO: add tests for libolecf_item_get_size */

	/* TODO: add tests for libolecf_item_get_creation_time */

	/* TODO: add tests for libolecf_item_get_modification_time */

	/* TODO: add tests for libolecf_item_get_number_of_sub_items */

	/* TODO: add tests for libolecf_item_get_sub_item */

	/* TODO: add tests for libolecf_item_get_sub_item_by_utf8_name */

	/* TODO: add tests for libolecf_item_get_sub_item_by_utf16_name */

	/* TODO: add tests for libolecf_item_get_sub_item_by_utf8_path */

	/* TODO: add tests for libolecf_item_get_sub_item_by_utf16_path */

#endif /* defined( __GNUC__ ) && !defined( LIBOLECF_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

