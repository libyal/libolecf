/*
 * Tools mount_path_string functions test program
 *
 * Copyright (C) 2008-2024, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "olecf_test_libcerror.h"
#include "olecf_test_libcpath.h"
#include "olecf_test_libolecf.h"
#include "olecf_test_macros.h"
#include "olecf_test_unused.h"

#include "../olecftools/mount_path_string.h"

#if defined( WINAPI )
#define ESCAPE_CHARACTER (system_character_t) '^'
#else
#define ESCAPE_CHARACTER (system_character_t) '\\'
#endif

/* Tests the mount_path_string_copy_hexadecimal_to_integer_32_bit function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_tools_mount_path_string_copy_hexadecimal_to_integer_32_bit(
     void )
{
	system_character_t error_string[ 5 ] = { '2', '0', 'Z', '8', 0 };
	system_character_t string[ 5 ]       = { '2', '0', '2', '8', 0 };
	libcerror_error_t *error             = NULL;
	uint32_t value_32bit                 = 0;
	int result                           = 0;

	/* Test regular cases
	 */
	result = mount_path_string_copy_hexadecimal_to_integer_32_bit(
	          string,
	          4,
	          &value_32bit,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_EQUAL_UINT32(
	 "value_32bit",
	 value_32bit,
	 (uint32_t) 0x2028 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = mount_path_string_copy_hexadecimal_to_integer_32_bit(
	          NULL,
	          4,
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

	result = mount_path_string_copy_hexadecimal_to_integer_32_bit(
	          string,
	          0,
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

	result = mount_path_string_copy_hexadecimal_to_integer_32_bit(
	          string,
	          (size_t) SSIZE_MAX + 1,
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

	result = mount_path_string_copy_hexadecimal_to_integer_32_bit(
	          string,
	          4,
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

	result = mount_path_string_copy_hexadecimal_to_integer_32_bit(
	          error_string,
	          4,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the mount_path_string_copy_from_item_path function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_tools_mount_path_string_copy_from_item_path(
     void )
{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	system_character_t item_path3[ 5 ]      = { 't', 'e', 0x2028, 't', 0 };
	system_character_t item_path4[ 5 ]      = { 't', 'e', '\\', 't', 0 };
	system_character_t item_path5[ 5 ]      = { 't', 'e', ESCAPE_CHARACTER, 't', 0 };
	system_character_t expected_path2[ 8 ]  = { 't', 'e', ESCAPE_CHARACTER, 'x', '0', '3', 't', 0 };
	system_character_t expected_path3[ 14 ] = { 't', 'e', ESCAPE_CHARACTER, 'U', '0', '0', '0', '0', '2', '0', '2', '8', 't', 0 };
	system_character_t expected_path4[ 8 ]  = { 't', 'e', ESCAPE_CHARACTER, 'x', '5', 'c', 't', 0 };
	system_character_t expected_path5[ 6 ]  = { 't', 'e', ESCAPE_CHARACTER, ESCAPE_CHARACTER, 't', 0 };
#else
	system_character_t item_path3[ 7 ]      = { 't', 'e', 0xe2, 0x80, 0xa8, 't', 0 };
	system_character_t item_path4[ 5 ]      = { 't', 'e', LIBCPATH_SEPARATOR, 't', 0 };
	system_character_t item_path5[ 5 ]      = { 't', 'e', ESCAPE_CHARACTER, 't', 0 };
	system_character_t expected_path2[ 8 ]  = { 't', 'e', ESCAPE_CHARACTER, 'x', '0', '3', 't', 0 };
	system_character_t expected_path3[ 14 ] = { 't', 'e', ESCAPE_CHARACTER, 'U', '0', '0', '0', '0', '2', '0', '2', '8', 't', 0 };
#if defined( WINAPI )
	system_character_t expected_path4[ 8 ]  = { 't', 'e', ESCAPE_CHARACTER, 'x', '5', 'c', 't', 0 };
#else
	system_character_t expected_path4[ 8 ]  = { 't', 'e', ESCAPE_CHARACTER, 'x', '2', 'f', 't', 0 };
#endif
	system_character_t expected_path5[ 6 ]  = { 't', 'e', ESCAPE_CHARACTER, ESCAPE_CHARACTER, 't', 0 };
#endif

	system_character_t item_path1[ 5 ]      = { 't', 'e', 's', 't', 0 };
	system_character_t item_path2[ 5 ]      = { 't', 'e', 0x03, 't', 0 };
	system_character_t expected_path1[ 5 ]  = { 't', 'e', 's', 't', 0 };
	libcerror_error_t *error                = NULL;
	system_character_t *path                = NULL;
	size_t path_size                        = 0;
	int result                              = 0;

	/* Test regular cases
	 */
	result = mount_path_string_copy_from_item_path(
	          &path,
	          &path_size,
	          item_path1,
	          4,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

	OLECF_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 41 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          path,
	          expected_path1,
	          5 );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	result = mount_path_string_copy_from_item_path(
	          &path,
	          &path_size,
	          item_path2,
	          4,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

	OLECF_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 41 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          path,
	          expected_path2,
	          8 );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = mount_path_string_copy_from_item_path(
	          &path,
	          &path_size,
	          item_path3,
	          4,
	          &error );
#else
	result = mount_path_string_copy_from_item_path(
	          &path,
	          &path_size,
	          item_path3,
	          6,
	          &error );
#endif
	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	OLECF_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 41 );
#else
	OLECF_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 61 );
#endif
	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          path,
	          expected_path3,
	          14 );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	result = mount_path_string_copy_from_item_path(
	          &path,
	          &path_size,
	          item_path4,
	          4,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

	OLECF_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 41 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          path,
	          expected_path4,
	          8 );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	result = mount_path_string_copy_from_item_path(
	          &path,
	          &path_size,
	          item_path5,
	          4,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

	OLECF_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 41 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          path,
	          expected_path5,
	          6 );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	/* Test error cases
	 */
	result = mount_path_string_copy_from_item_path(
	          NULL,
	          &path_size,
	          item_path1,
	          4,
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

	result = mount_path_string_copy_from_item_path(
	          &path,
	          NULL,
	          item_path1,
	          4,
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

	result = mount_path_string_copy_from_item_path(
	          &path,
	          &path_size,
	          NULL,
	          4,
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

	result = mount_path_string_copy_from_item_path(
	          &path,
	          &path_size,
	          item_path1,
	          0,
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

	result = mount_path_string_copy_from_item_path(
	          &path,
	          &path_size,
	          item_path1,
	          (size_t) SSIZE_MAX + 1,
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
	if( path != NULL )
	{
		memory_free(
		 path );
	}
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the mount_path_string_copy_to_item_path function
 * Returns 1 if successful or 0 if not
 */
int olecf_test_tools_mount_path_string_copy_to_item_path(
     void )
{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	system_character_t expected_item_path3[ 6 ] = { LIBOLECF_SEPARATOR, 't', 'e', 0x2028, 't', 0 };
	system_character_t expected_item_path4[ 6 ] = { LIBOLECF_SEPARATOR, 't', 'e', ESCAPE_CHARACTER, 't', 0 };
	system_character_t path2[ 9 ]               = { LIBCPATH_SEPARATOR, 't', 'e', ESCAPE_CHARACTER, 'x', '0', '3', 't', 0 };
	system_character_t path3[ 15 ]              = { LIBCPATH_SEPARATOR, 't', 'e', ESCAPE_CHARACTER, 'U', '0', '0', '0', '0', '2', '0', '2', '8', 't', 0 };
	system_character_t path4[ 7 ]               = { LIBCPATH_SEPARATOR, 't', 'e', ESCAPE_CHARACTER, ESCAPE_CHARACTER, 't', 0 };
#else
	system_character_t expected_item_path3[ 8 ] = { LIBOLECF_SEPARATOR, 't', 'e', 0xe2, 0x80, 0xa8, 't', 0 };
	system_character_t expected_item_path4[ 6 ] = { LIBOLECF_SEPARATOR, 't', 'e', ESCAPE_CHARACTER, 't', 0 };
	system_character_t path2[ 9 ]               = { LIBCPATH_SEPARATOR, 't', 'e', ESCAPE_CHARACTER, 'x', '0', '3', 't', 0 };
	system_character_t path3[ 15 ]              = { LIBCPATH_SEPARATOR, 't', 'e', ESCAPE_CHARACTER, 'U', '0', '0', '0', '0', '2', '0', '2', '8', 't', 0 };
	system_character_t path4[ 7 ]               = { LIBCPATH_SEPARATOR, 't', 'e', ESCAPE_CHARACTER, ESCAPE_CHARACTER, 't', 0 };
#endif

	system_character_t expected_item_path1[ 6 ] = { LIBOLECF_SEPARATOR, 't', 'e', 's', 't', 0 };
	system_character_t expected_item_path2[ 6 ] = { LIBOLECF_SEPARATOR, 't', 'e', 0x03, 't', 0 };
	system_character_t expected_item_path5[ 6 ] = { LIBOLECF_SEPARATOR, 't', 'e', LIBOLECF_SEPARATOR, 't', 0 };
	system_character_t path1[ 6 ]               = { LIBCPATH_SEPARATOR, 't', 'e', 's', 't', 0 };
	system_character_t path5[ 6 ]               = { LIBCPATH_SEPARATOR, 't', 'e', LIBCPATH_SEPARATOR, 't', 0 };
	libcerror_error_t *error                    = NULL;
	system_character_t *item_path               = NULL;
	size_t item_path_size                       = 0;
	int result                                  = 0;

	/* Test regular cases
	 */
	result = mount_path_string_copy_to_item_path(
	          path1,
	          5,
	          &item_path,
	          &item_path_size,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "item_path",
	 item_path );

	OLECF_TEST_ASSERT_EQUAL_SIZE(
	 "item_path_size",
	 item_path_size,
	 (size_t) 6 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          item_path,
	          expected_item_path1,
	          6 );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 item_path );

	item_path = NULL;

	result = mount_path_string_copy_to_item_path(
	          path2,
	          8,
	          &item_path,
	          &item_path_size,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "item_path",
	 item_path );

	OLECF_TEST_ASSERT_EQUAL_SIZE(
	 "item_path_size",
	 item_path_size,
	 (size_t) 9 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          item_path,
	          expected_item_path2,
	          6 );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 item_path );

	item_path = NULL;

	result = mount_path_string_copy_to_item_path(
	          path3,
	          14,
	          &item_path,
	          &item_path_size,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "item_path",
	 item_path );

	OLECF_TEST_ASSERT_EQUAL_SIZE(
	 "item_path_size",
	 item_path_size,
	 (size_t) 15 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = memory_compare(
	          item_path,
	          expected_item_path3,
	          6 );
#else
	result = memory_compare(
	          item_path,
	          expected_item_path3,
	          8 );
#endif
	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 item_path );

	item_path = NULL;

	result = mount_path_string_copy_to_item_path(
	          path4,
	          6,
	          &item_path,
	          &item_path_size,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "item_path",
	 item_path );

	OLECF_TEST_ASSERT_EQUAL_SIZE(
	 "item_path_size",
	 item_path_size,
	 (size_t) 7 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          item_path,
	          expected_item_path4,
	          6 );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 item_path );

	item_path = NULL;

	result = mount_path_string_copy_to_item_path(
	          path5,
	          6,
	          &item_path,
	          &item_path_size,
	          &error );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	OLECF_TEST_ASSERT_IS_NOT_NULL(
	 "item_path",
	 item_path );

	OLECF_TEST_ASSERT_EQUAL_SIZE(
	 "item_path_size",
	 item_path_size,
	 (size_t) 7 );

	OLECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          item_path,
	          expected_item_path5,
	          6 );

	OLECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 item_path );

	item_path = NULL;

	/* Test error cases
	 */
	result = mount_path_string_copy_to_item_path(
	          NULL,
	          5,
	          &item_path,
	          &item_path_size,
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

	result = mount_path_string_copy_to_item_path(
	          path1,
	          0,
	          &item_path,
	          &item_path_size,
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

	result = mount_path_string_copy_to_item_path(
	          path1,
	          (size_t) SSIZE_MAX + 1,
	          &item_path,
	          &item_path_size,
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

	result = mount_path_string_copy_to_item_path(
	          path1,
	          5,
	          NULL,
	          &item_path_size,
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

	result = mount_path_string_copy_to_item_path(
	          path1,
	          5,
	          &item_path,
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
	if( item_path != NULL )
	{
		memory_free(
		 item_path );
	}
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

	OLECF_TEST_RUN(
	 "mount_path_string_copy_hexadecimal_to_integer_32_bit",
	 olecf_test_tools_mount_path_string_copy_hexadecimal_to_integer_32_bit )

	OLECF_TEST_RUN(
	 "mount_path_string_copy_from_item_path",
	 olecf_test_tools_mount_path_string_copy_from_item_path )

	OLECF_TEST_RUN(
	 "mount_path_string_copy_to_item_path",
	 olecf_test_tools_mount_path_string_copy_to_item_path )

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

