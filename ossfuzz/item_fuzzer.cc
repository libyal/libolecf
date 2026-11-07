/*
 * OSS-Fuzz target for libolecf item type
 *
 * Copyright (C) 2008-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

#include <stdlib.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libolecf.h"

#if !defined( LIBOLECF_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_open_file_io_handle(
      libolecf_file_t *file,
      libbfio_handle_t *file_io_handle,
      int access_flags,
      libolecf_error_t **error );

#endif /* !defined( LIBOLECF_HAVE_BFIO ) */

/* Limits the size of the name and query buffers
 */
#define FUZZER_DATA_SIZE_LIMIT	( (size_t) 0x10000 )
#define FUZZER_PATH_SIZE_LIMIT	( (size_t) 0x100 )

/* Limits the number of sub items to query
 */
#define FUZZER_SUB_ITEM_LIMIT	8

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	libolecf_item_t *lookup_item = NULL;
	uint8_t *utf8_name          = NULL;
	uint16_t *utf16_name        = NULL;

	libbfio_handle_t *file_io_handle = NULL;
	libolecf_file_t *file            = NULL;
	libolecf_item_t *item            = NULL;
	libolecf_item_t *sub_item        = NULL;
	uint8_t item_type                = 0;
	uint32_t item_size               = 0;
	uint64_t filetime                = 0;
	size_t utf8_name_size           = 0;
	size_t utf16_name_size          = 0;
	size_t name_buffer_size         = 0;
	size_t query_size               = 0;
	size_t unicode_query_size       = 0;
	int number_of_sub_items         = 0;
	int result                      = 0;
	int sub_item_index              = 0;
	int sub_number_of_sub_items     = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libolecf_file_initialize(
	     &file,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libolecf_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     LIBOLECF_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libolecf_file;
	}
	if( libolecf_file_get_root_item(
	     file,
	     &item,
	     NULL ) == 1 )
	{
		libolecf_item_get_type(
		 item,
		 &item_type,
		 NULL );
		libolecf_item_get_size(
		 item,
		 &item_size,
		 NULL );
		libolecf_item_get_creation_time(
		 item,
		 &filetime,
		 NULL );
		libolecf_item_get_modification_time(
		 item,
		 &filetime,
		 NULL );
		result = libolecf_item_get_utf8_name_size(
		         item,
		         &utf8_name_size,
		         NULL );
		if( ( result == 1 )
		 && ( utf8_name_size > 0 ) )
		{
			name_buffer_size = utf8_name_size;

			if( name_buffer_size > FUZZER_DATA_SIZE_LIMIT )
			{
				name_buffer_size = FUZZER_DATA_SIZE_LIMIT;
			}
			utf8_name = (uint8_t *) malloc( name_buffer_size );

			if( utf8_name != NULL )
			{
				if( libolecf_item_get_utf8_name(
				     item,
				     utf8_name,
				     name_buffer_size,
				     NULL ) == 1 )
				{
					utf8_name[ name_buffer_size - 1 ] = 0;

					/* Use the value as a sink to keep it live
					 */
					filetime = utf8_name[ 0 ];
				}
				free( utf8_name );
				utf8_name = NULL;
			}
		}
		result = libolecf_item_get_utf16_name_size(
		         item,
		         &utf16_name_size,
		         NULL );
		if( ( result == 1 )
		 && ( utf16_name_size > 0 ) )
		{
			name_buffer_size = utf16_name_size;

			if( name_buffer_size > FUZZER_DATA_SIZE_LIMIT )
			{
				name_buffer_size = FUZZER_DATA_SIZE_LIMIT;
			}
			/* The size is the number of UTF-16 characters,
			 * including the end of string character
			 */
			utf16_name = (uint16_t *) malloc( name_buffer_size * sizeof( uint16_t ) );

			if( utf16_name != NULL )
			{
				if( libolecf_item_get_utf16_name(
				     item,
				     utf16_name,
				     name_buffer_size,
				     NULL ) == 1 )
				{
					utf16_name[ name_buffer_size - 1 ] = 0;

					/* Use the value as a sink to keep it live
					 */
					filetime = (uint64_t) utf16_name[ 0 ];
				}
				free( utf16_name );
				utf16_name = NULL;
			}
		}
		if( libolecf_item_get_number_of_sub_items(
		     item,
		     &number_of_sub_items,
		     NULL ) == 1 )
		{
			/* Query the sub items
			 */
			for( sub_item_index = 0;
			     sub_item_index < number_of_sub_items;
			     sub_item_index++ )
			{
				utf8_name_size    = 0;
				utf16_name_size   = 0;

				if( sub_item_index >= FUZZER_SUB_ITEM_LIMIT )
				{
					break;
				}
				if( libolecf_item_get_sub_item(
				     item,
				     sub_item_index,
				     &sub_item,
				     NULL ) != 1 )
				{
					break;
				}
				libolecf_item_get_type(
				 sub_item,
				 &item_type,
				 NULL );
				libolecf_item_get_size(
				 sub_item,
				 &item_size,
				 NULL );
				libolecf_item_get_creation_time(
				 sub_item,
				 &filetime,
				 NULL );
				libolecf_item_get_modification_time(
				 sub_item,
				 &filetime,
				 NULL );
				result = libolecf_item_get_utf8_name_size(
				         sub_item,
				         &utf8_name_size,
				         NULL );
				if( ( result == 1 )
				 && ( utf8_name_size > 0 ) )
				{
					name_buffer_size = utf8_name_size;

					if( name_buffer_size > FUZZER_DATA_SIZE_LIMIT )
					{
						name_buffer_size = FUZZER_DATA_SIZE_LIMIT;
					}
					utf8_name = (uint8_t *) malloc( name_buffer_size );

					if( utf8_name != NULL )
					{
						if( libolecf_item_get_utf8_name(
						     sub_item,
						     utf8_name,
						     name_buffer_size,
						     NULL ) == 1 )
						{
							utf8_name[ name_buffer_size - 1 ] = 0;

							/* Use the value as a sink
							 * to keep it live
							 */
							filetime = utf8_name[ 0 ];
						}
						free( utf8_name );
						utf8_name = NULL;
					}
				}
				result = libolecf_item_get_utf16_name_size(
				         sub_item,
				         &utf16_name_size,
				         NULL );
				if( ( result == 1 )
				 && ( utf16_name_size > 0 ) )
				{
					name_buffer_size = utf16_name_size;

					if( name_buffer_size > FUZZER_DATA_SIZE_LIMIT )
					{
						name_buffer_size = FUZZER_DATA_SIZE_LIMIT;
					}
					/* The size is the number of UTF-16
					 * characters, including the end of
					 * string character
					 */
					utf16_name = (uint16_t *) malloc( name_buffer_size * sizeof( uint16_t ) );

					if( utf16_name != NULL )
					{
						if( libolecf_item_get_utf16_name(
						     sub_item,
						     utf16_name,
						     name_buffer_size,
						     NULL ) == 1 )
						{
							utf16_name[ name_buffer_size - 1 ] = 0;

							/* Use the value as a sink
							 * to keep it live
							 */
							filetime = (uint64_t) utf16_name[ 0 ];
						}
						free( utf16_name );
						utf16_name = NULL;
					}
				}
				/* Query the number of sub items
				 */
				sub_number_of_sub_items = 0;
				libolecf_item_get_number_of_sub_items(
				 sub_item,
				 &sub_number_of_sub_items,
				 NULL );
				libolecf_item_free(
				 &sub_item,
				 NULL );
			}
			/* Attempt to retrieve a sub item out of range
			 * to trigger the error handler
			 */
			sub_item = NULL;
			libolecf_item_get_sub_item(
			 item,
			 number_of_sub_items,
			 &sub_item,
			 NULL );
			if( sub_item != NULL )
			{
				libolecf_item_free(
				 &sub_item,
				 NULL );
			}
		}
		/* Look up sub items by name and path using the fuzzer
		 * data as the query strings
		 */
		if( ( data != NULL )
		 && ( size > 0 ) )
		{
			query_size = size;

			if( query_size > FUZZER_PATH_SIZE_LIMIT )
			{
				query_size = FUZZER_PATH_SIZE_LIMIT;
			}
			unicode_query_size = query_size / 2;
			lookup_item = NULL;
			libolecf_item_get_sub_item_by_utf8_name(
			 item,
			 data,
			 query_size,
			 &lookup_item,
			 NULL );
			if( lookup_item != NULL )
			{
				libolecf_item_free(
				 &lookup_item,
				 NULL );
			}
			lookup_item = NULL;
			libolecf_item_get_sub_item_by_utf8_path(
			 item,
			 data,
			 query_size,
			 &lookup_item,
			 NULL );
			if( lookup_item != NULL )
			{
				libolecf_item_free(
				 &lookup_item,
				 NULL );
			}
			lookup_item = NULL;
			if( unicode_query_size > 0 )
			{
				libolecf_item_get_sub_item_by_utf16_name(
				 item,
				 (const uint16_t *) data,
				 unicode_query_size,
				 &lookup_item,
				 NULL );
				if( lookup_item != NULL )
				{
					libolecf_item_free(
					 &lookup_item,
					 NULL );
				}
				lookup_item = NULL;
				libolecf_item_get_sub_item_by_utf16_path(
				 item,
				 (const uint16_t *) data,
				 unicode_query_size,
				 &lookup_item,
				 NULL );
				if( lookup_item != NULL )
				{
					libolecf_item_free(
					 &lookup_item,
					 NULL );
				}
			}
		}
		libolecf_item_free(
		 &item,
		 NULL );
	}
	libolecf_file_close(
	 file,
	 NULL );

on_error_libolecf_file:
	libolecf_file_free(
	 &file,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */
