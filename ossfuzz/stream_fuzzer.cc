/*
 * OSS-Fuzz target for libolecf stream type
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

/* Limits the size of the data buffer
 */
#define FUZZER_DATA_SIZE_LIMIT	( (size_t) 0x10000 )

/* Limits the number of sub items to walk to find a stream type item
 */
#define FUZZER_SUB_ITEM_LIMIT	8

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	uint8_t *buffer    = NULL;
	off64_t offset     = 0;
	ssize_t read_count = 0;

	libbfio_handle_t *file_io_handle = NULL;
	libolecf_file_t *file            = NULL;
	libolecf_item_t *item            = NULL;
	libolecf_item_t *stream          = NULL;
	uint8_t item_type                = 0;
	int number_of_sub_items         = 0;
	int result                      = 0;
	int sub_item_index              = 0;

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
		buffer = (uint8_t *) malloc( FUZZER_DATA_SIZE_LIMIT );

		if( buffer != NULL )
		{
			/* Walk the sub items to find a stream type item
			 */
			if( libolecf_item_get_number_of_sub_items(
			     item,
			     &number_of_sub_items,
			     NULL ) == 1 )
			{
				for( sub_item_index = 0;
				     sub_item_index < number_of_sub_items;
				     sub_item_index++ )
				{
					item_type = 0;

					if( sub_item_index >= FUZZER_SUB_ITEM_LIMIT )
					{
						break;
					}
					if( libolecf_item_get_sub_item(
					     item,
					     sub_item_index,
					     &stream,
					     NULL ) != 1 )
					{
						break;
					}
					result = libolecf_item_get_type(
					         stream,
					         &item_type,
					         NULL );
					if( ( result == 1 )
					 && ( item_type == LIBOLECF_ITEM_TYPE_STREAM ) )
					{
						libolecf_stream_get_offset(
						 stream,
						 &offset,
						 NULL );
						libolecf_stream_read_buffer(
						 stream,
						 buffer,
						 FUZZER_DATA_SIZE_LIMIT,
						 NULL );
						libolecf_stream_seek_offset(
						 stream,
						 0,
						 SEEK_SET,
						 NULL );
						read_count = libolecf_stream_read_buffer_at_offset(
							 stream,
							 buffer,
							 FUZZER_DATA_SIZE_LIMIT,
							 (off64_t) 0,
							 NULL );
						if( ( read_count > 0 )
						 && ( read_count <= (ssize_t) FUZZER_DATA_SIZE_LIMIT ) )
						{
							/* Use the value as a sink
							 * to keep it live
							 */
							offset = (off64_t) buffer[ 0 ];
						}
						/* Attempt other seek operations
						 * to trigger the error paths
						 */
						libolecf_stream_seek_offset(
						 stream,
						 1,
						 SEEK_CUR,
						 NULL );
						libolecf_stream_seek_offset(
						 stream,
						 -1,
						 SEEK_END,
						 NULL );
						libolecf_stream_seek_offset(
						 stream,
						 -1,
						 SEEK_SET,
						 NULL );
						/* An invalid whence value should
						 * trigger an unsupported error
						 */
						libolecf_stream_seek_offset(
						 stream,
						 0,
						 8,
						 NULL );
						libolecf_stream_get_offset(
						 stream,
						 &offset,
						 NULL );
					}
					libolecf_item_free(
					 &stream,
					 NULL );
				}
			}
		}
		free( buffer );
		buffer = NULL;
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
