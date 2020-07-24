/*
 * File header functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libolecf_allocation_table.h"
#include "libolecf_debug.h"
#include "libolecf_definitions.h"
#include "libolecf_file_header.h"
#include "libolecf_io_handle.h"
#include "libolecf_libcerror.h"
#include "libolecf_libcnotify.h"
#include "libolecf_libfguid.h"

#include "olecf_file_header.h"

/* Creates file header
 * Make sure the value file_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_header_initialize(
     libolecf_file_header_t **file_header,
     libcerror_error_t **error )
{
	static char *function = "libolecf_file_header_initialize";

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file header value already set.",
		 function );

		return( -1 );
	}
	*file_header = memory_allocate_structure(
	                libolecf_file_header_t );

	if( *file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_header,
	     0,
	     sizeof( libolecf_file_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file_header != NULL )
	{
		memory_free(
		 *file_header );

		*file_header = NULL;
	}
	return( -1 );
}

/* Frees file header
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_header_free(
     libolecf_file_header_t **file_header,
     libcerror_error_t **error )
{
	static char *function = "libolecf_file_header_free";

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		memory_free(
		 *file_header );

		*file_header = NULL;
	}
	return( 1 );
}

/* Reads the file header data
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_header_read_data(
     libolecf_file_header_t *file_header,
     const uint8_t *data,
     size_t data_size,
     libolecf_allocation_table_t *msat,
     libcerror_error_t **error )
{
	const uint8_t *msat_entry  = NULL;
	static char *function      = "libolecf_file_header_read_data";
	uint16_t sector_size       = 0;
	uint16_t short_sector_size = 0;
	int msat_index             = 0;

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size < sizeof( olecf_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( msat == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MSAT.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) data,
		 sizeof( olecf_file_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( ( memory_compare(
	       ( (olecf_file_header_t *) data )->signature,
	       olecf_file_signature,
	       8 ) != 0 )
	 && ( memory_compare(
	       ( (olecf_file_header_t *) data )->signature,
	       olecf_beta_file_signature,
	       8 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file signature.",
		 function );

		return( -1 );
	}
	if( ( ( (olecf_file_header_t *) data )->byte_order[ 0 ] == 0xfe )
	 && ( ( (olecf_file_header_t *) data )->byte_order[ 1 ] == 0xff ) )
	{
		file_header->byte_order = LIBOLECF_ENDIAN_LITTLE;
	}
	else if( ( ( (olecf_file_header_t *) data )->byte_order[ 0 ] == 0xff )
	      && ( ( (olecf_file_header_t *) data )->byte_order[ 1 ] == 0xfe ) )
	{
		file_header->byte_order = LIBOLECF_ENDIAN_BIG;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order: 0x%02" PRIx8 " 0x%02" PRIx8 ".",
		 function,
		 ( (olecf_file_header_t *) data )->byte_order[ 0 ],
		 ( (olecf_file_header_t *) data )->byte_order[ 1 ] );

		return( -1 );
	}
	if( file_header->byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint16_little_endian(
		 ( (olecf_file_header_t *) data )->minor_format_version,
		 file_header->minor_format_version );

		byte_stream_copy_to_uint16_little_endian(
		 ( (olecf_file_header_t *) data )->major_format_version,
		 file_header->major_format_version );

		byte_stream_copy_to_uint16_little_endian(
		 ( (olecf_file_header_t *) data )->sector_size,
		 sector_size );

		byte_stream_copy_to_uint16_little_endian(
		 ( (olecf_file_header_t *) data )->short_sector_size,
		 short_sector_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->number_of_sat_sectors,
		 file_header->number_of_sat_sectors );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->root_directory_sector_identifier,
		 file_header->root_directory_sector_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->sector_stream_minimum_data_size,
		 file_header->sector_stream_minimum_data_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->ssat_sector_identifier,
		 file_header->ssat_sector_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->number_of_ssat_sectors,
		 file_header->number_of_ssat_sectors );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->msat_sector_identifier,
		 file_header->msat_sector_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->number_of_msat_sectors,
		 file_header->number_of_msat_sectors );
	}
	else if( file_header->byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint16_big_endian(
		 ( (olecf_file_header_t *) data )->minor_format_version,
		 file_header->minor_format_version );

		byte_stream_copy_to_uint16_big_endian(
		 ( (olecf_file_header_t *) data )->major_format_version,
		 file_header->major_format_version );

		byte_stream_copy_to_uint16_big_endian(
		 ( (olecf_file_header_t *) data )->sector_size,
		 sector_size );

		byte_stream_copy_to_uint16_big_endian(
		 ( (olecf_file_header_t *) data )->short_sector_size,
		 short_sector_size );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->number_of_sat_sectors,
		 file_header->number_of_sat_sectors );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->root_directory_sector_identifier,
		 file_header->root_directory_sector_identifier );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->sector_stream_minimum_data_size,
		 file_header->sector_stream_minimum_data_size );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->ssat_sector_identifier,
		 file_header->ssat_sector_identifier );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->number_of_ssat_sectors,
		 file_header->number_of_ssat_sectors );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->msat_sector_identifier,
		 file_header->msat_sector_identifier );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->number_of_msat_sectors,
		 file_header->number_of_msat_sectors );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature:\n",
		 function );
		libcnotify_print_data(
		 ( (olecf_file_header_t *) data )->signature,
		 8,
		 0 );

		if( libolecf_debug_print_guid_value(
		     function,
		     "class identifier\t\t\t",
		     ( (olecf_file_header_t *) data )->class_identifier,
		     16,
		     file_header->byte_order,
		     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 "%s: minor format version\t\t\t: %" PRIu16 "\n",
		 function,
		 file_header->minor_format_version );

		libcnotify_printf(
		 "%s: major format version\t\t\t: %" PRIu16 "\n",
		 function,
		 file_header->major_format_version );

		libcnotify_printf(
		 "%s: byte order\t\t\t\t: 0x%02" PRIx8 " 0x%02" PRIx8 "\n",
		 function,
		 ( (olecf_file_header_t *) data )->byte_order[ 0 ],
		 ( (olecf_file_header_t *) data )->byte_order[ 1 ] );

		libcnotify_printf(
		 "%s: sector size\t\t\t\t: %" PRIu16 " (%" PRIzd ")\n",
		 function,
		 sector_size,
		 1 << sector_size );

		libcnotify_printf(
		 "%s: short sector size\t\t\t: %" PRIu16 " (%" PRIzd ")\n",
		 function,
		 short_sector_size,
		 1 << short_sector_size );

		libcnotify_printf(
		 "%s: reserved:\n",
		 function );
		libcnotify_print_data(
		 ( (olecf_file_header_t *) data )->reserved1,
		 10,
		 0 );

		libcnotify_printf(
		 "%s: number of SAT sectors\t\t\t: %" PRIu32 "\n",
		 function,
		 file_header->number_of_sat_sectors );

		libcnotify_printf(
		 "%s: root directory sector identifier\t: 0x%08" PRIx32 "\n",
		 function,
		 file_header->root_directory_sector_identifier );

		libcnotify_printf(
		 "%s: transactioning signature:\n",
		 function );
		libcnotify_print_data(
		 ( (olecf_file_header_t *) data )->transactioning_signature,
		 4,
		 0 );

		libcnotify_printf(
		 "%s: sector stream minimum data size\t\t: %" PRIu32 "\n",
		 function,
		 file_header->sector_stream_minimum_data_size );
	
		libcnotify_printf(
		 "%s: SSAT sector identifier\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_header->ssat_sector_identifier );

		libcnotify_printf(
		 "%s: number of SSAT sectors\t\t\t: %" PRIu32 "\n",
		 function,
		 file_header->number_of_ssat_sectors );
	
		libcnotify_printf(
		 "%s: MSAT sector identifier\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_header->msat_sector_identifier );

		libcnotify_printf(
		 "%s: number of MSAT sectors\t\t\t: %" PRIu32 "\n",
		 function,
		 file_header->number_of_msat_sectors );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( sector_size > 15 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid sector size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( short_sector_size > 15 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid short sector size value exceeds maximum.",
		 function );

		return( -1 );
	}
	file_header->sector_size       = 1 << sector_size;
	file_header->short_sector_size = 1 << short_sector_size;

#if SIZEOF_SIZE_T <= 4
	if( file_header->sector_stream_minimum_data_size > (uint32_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid sector stream minimum size value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
	if( msat->number_of_sector_identifiers < 109 )
	{
		if( libolecf_allocation_table_resize(
		     msat,
		     109,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
			 "%s: unable to resize MSAT.",
			 function );

			return( -1 );
		}
	}
	msat_entry = ( (olecf_file_header_t *) data )->msat;

	for( msat_index = 0;
	     msat_index < 109;
	     msat_index++ )
	{
		if( file_header->byte_order == LIBOLECF_ENDIAN_LITTLE )
		{
			byte_stream_copy_to_uint32_little_endian(
			 msat_entry,
			 msat->sector_identifiers[ msat_index ] );
		}
		else if( file_header->byte_order == LIBOLECF_ENDIAN_BIG )
		{
			byte_stream_copy_to_uint32_big_endian(
			 msat_entry,
			 msat->sector_identifiers[ msat_index ] );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: MSAT entry: %03d sector identifier\t: 0x%08" PRIx32 "\n",
			 function,
			 msat_index,
			 msat->sector_identifiers[ msat_index ] );
		}
#endif
		msat_entry += 4;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_header_read_file_io_handle(
     libolecf_file_header_t *file_header,
     libbfio_handle_t *file_io_handle,
     libolecf_allocation_table_t *msat,
     libcerror_error_t **error )
{
	uint8_t file_header_data[ sizeof( olecf_file_header_t ) ];

	static char *function = "libolecf_file_header_read_file_io_handle";
	ssize_t read_count    = 0;

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0 (0x00000000).",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              file_header_data,
	              sizeof( olecf_file_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( olecf_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header data.",
		 function );

		return( -1 );
	}
	if( libolecf_file_header_read_data(
	     file_header,
	     file_header_data,
	     sizeof( olecf_file_header_t ),
	     msat,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		return( -1 );
	}
	return( 1 );
}

