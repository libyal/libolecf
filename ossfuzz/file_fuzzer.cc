/*
 * OSS-Fuzz target for libolecf file type
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

/* Limits on the number of unallocated blocks to query
 */
#define FUZZER_UNALLOCATED_BLOCKS_LIMIT	8

/* Limits the size of the query strings used to look up items
 */
#define FUZZER_PATH_SIZE_LIMIT		( (size_t) 0x100 )

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	libbfio_handle_t *file_io_handle = NULL;
	libolecf_file_t *file            = NULL;
	libolecf_item_t *item            = NULL;
	size32_t sector_size             = 0;
	size32_t short_sector_size       = 0;
	uint16_t major_version           = 0;
	uint16_t minor_version           = 0;
	int ascii_codepage               = 0;
	int number_of_unallocated_blocks = 0;
	int unallocated_block_index      = 0;
	off64_t offset                   = 0;
	size64_t unallocated_block_size  = 0;
	size_t query_size                = 0;

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
#if defined( LIBOLECF_HAVE_BFIO )
	if( libolecf_check_file_signature_file_io_handle(
	     file_io_handle,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
#endif /* defined( LIBOLECF_HAVE_BFIO ) */
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
	/* Use the value as a sink to keep it live
	 */
	ascii_codepage = 0;

	libolecf_file_get_sector_size(
	 file,
	 &sector_size,
	 NULL );
	libolecf_file_get_short_sector_size(
	 file,
	 &short_sector_size,
	 NULL );
	libolecf_file_get_ascii_codepage(
	 file,
	 &ascii_codepage,
	 NULL );
	/* Attempt to set an unsupported and a supported ASCII codepage
	 * to trigger the validation
	 */
	libolecf_file_set_ascii_codepage(
	 file,
	 0x004e,
	 NULL );
	libolecf_file_set_ascii_codepage(
	 file,
	 LIBOLECF_CODEPAGE_WINDOWS_1252,
	 NULL );
	libolecf_file_get_ascii_codepage(
	 file,
	 &ascii_codepage,
	 NULL );
	libolecf_file_get_format_version(
	 file,
	 &major_version,
	 &minor_version,
	 NULL );
	libolecf_file_signal_abort(
	 file,
	 NULL );
	if( libolecf_file_get_number_of_unallocated_blocks(
	     file,
	     &number_of_unallocated_blocks,
	     NULL ) == 1 )
	{
		for( unallocated_block_index = 0;
		     unallocated_block_index < number_of_unallocated_blocks;
		     unallocated_block_index++ )
		{
			offset = 0;
			unallocated_block_size = 0;

			if( unallocated_block_index >= FUZZER_UNALLOCATED_BLOCKS_LIMIT )
			{
				break;
			}
			libolecf_file_get_unallocated_block(
			 file,
			 unallocated_block_index,
			 &offset,
			 &unallocated_block_size,
			 NULL );
		}
	}
	if( ( data != NULL )
	 && ( size > 0 ) )
	{
		query_size = size;

		if( query_size > FUZZER_PATH_SIZE_LIMIT )
		{
			query_size = FUZZER_PATH_SIZE_LIMIT;
		}
		/* Use the value as a sink to keep it live
		 */
		ascii_codepage = data[ 0 ];
		libolecf_file_get_item_by_utf8_path(
		 file,
		 data,
		 query_size,
		 &item,
		 NULL );
		if( item != NULL )
		{
			libolecf_item_free(
			 &item,
			 NULL );
		}
		item = NULL;
		if( query_size >= 2 )
		{
			libolecf_file_get_item_by_utf16_path(
			 file,
			 (const uint16_t *) data,
			 query_size / 2,
			 &item,
			 NULL );
			if( item != NULL )
			{
				libolecf_item_free(
				 &item,
				 NULL );
			}
		}
	}
	libolecf_file_get_root_item(
	 file,
	 &item,
	 NULL );
	if( item != NULL )
	{
		libolecf_item_free(
		 &item,
		 NULL );
	}
	libolecf_file_close(
	 file,
	 NULL );
	/* Attempt to open with unsupported access flags
	 * to trigger the validation
	 */
	libolecf_file_open_file_io_handle(
	 file,
	 file_io_handle,
	 LIBOLECF_OPEN_WRITE,
	 NULL );
	libolecf_file_open_file_io_handle(
	 file,
	 file_io_handle,
	 0,
	 NULL );
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
