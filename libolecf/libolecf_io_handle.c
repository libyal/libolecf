/*
 * Input/Output (IO) handle functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libolecf_allocation_table.h"
#include "libolecf_codepage.h"
#include "libolecf_debug.h"
#include "libolecf_definitions.h"
#include "libolecf_directory_entry.h"
#include "libolecf_io_handle.h"
#include "libolecf_libbfio.h"
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"
#include "libolecf_libcnotify.h"
#include "libolecf_libfguid.h"
#include "libolecf_libuna.h"
#include "libolecf_notify.h"

#include "olecf_directory.h"
#include "olecf_file_header.h"

const uint8_t olecf_file_signature[ 8 ]      = { 0xd0, 0xcf, 0x11, 0xe0, 0xa1, 0xb1, 0x1a, 0xe1 };
const uint8_t olecf_beta_file_signature[ 8 ] = { 0x0e, 0x11, 0xfc, 0x0d, 0xd0, 0xcf, 0x11, 0x0e };

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libolecf_io_handle_initialize(
     libolecf_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libolecf_io_handle_initialize";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libolecf_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libolecf_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		memory_free(
		 *io_handle );

		*io_handle = NULL;

		return( -1 );
	}
	( *io_handle )->ascii_codepage = LIBOLECF_CODEPAGE_WINDOWS_1252;

	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libolecf_io_handle_free(
     libolecf_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libolecf_io_handle_free";
	int result            = 1;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( result );
}

/* Clears an IO handle
 * Returns 1 if successful or -1 on error
 */
int libolecf_io_handle_clear(
     libolecf_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libolecf_io_handle_clear";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libolecf_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	io_handle->ascii_codepage = LIBOLECF_CODEPAGE_WINDOWS_1252;

	return( 1 );
}

/* Reads a file header
 * Returns 1 if successful or -1 on error
 */
int libolecf_io_handle_read_file_header(
     libolecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libolecf_allocation_table_t *msat,
     uint32_t *msat_sector_identifier,
     uint32_t *number_of_msat_sectors,
     uint32_t *number_of_sat_sectors,
     uint32_t *ssat_sector_identifier,
     uint32_t *number_of_ssat_sectors,
     uint32_t *root_directory_sector_identifier,
     libcerror_error_t **error )
{
	olecf_file_header_t file_header;

	static char *function = "libolecf_io_handle_read_file_header";
	ssize_t read_count    = 0;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
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
		 "%s: unable to seek file header offset: 0.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &file_header,
	              sizeof( olecf_file_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( olecf_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		return( -1 );
	}
	if( libolecf_io_handle_read_file_header_data(
	     io_handle,
	     (uint8_t *) &file_header,
	     sizeof( olecf_file_header_t ),
	     msat,
	     msat_sector_identifier,
	     number_of_msat_sectors,
	     number_of_sat_sectors,
	     ssat_sector_identifier,
	     number_of_ssat_sectors,
	     root_directory_sector_identifier,
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

/* Reads a file header
 * Returns 1 if successful or -1 on error
 */
int libolecf_io_handle_read_file_header_data(
     libolecf_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libolecf_allocation_table_t *msat,
     uint32_t *msat_sector_identifier,
     uint32_t *number_of_msat_sectors,
     uint32_t *number_of_sat_sectors,
     uint32_t *ssat_sector_identifier,
     uint32_t *number_of_ssat_sectors,
     uint32_t *root_directory_sector_identifier,
     libcerror_error_t **error )
{
	uint8_t *msat_entry        = NULL;
	static char *function      = "libolecf_io_handle_read_file_header_data";
	uint16_t sector_size       = 0;
	uint16_t short_sector_size = 0;
	int msat_index             = 0;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
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
	if( msat_sector_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MSAT sector identifier.",
		 function );

		return( -1 );
	}
	if( number_of_msat_sectors == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of MSAT sectors.",
		 function );

		return( -1 );
	}
	if( number_of_sat_sectors == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of SAT sectors.",
		 function );

		return( -1 );
	}
	if( ssat_sector_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid SSAT sector identifier.",
		 function );

		return( -1 );
	}
	if( number_of_ssat_sectors == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of SSAT sectors.",
		 function );

		return( -1 );
	}
	if( root_directory_sector_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid root directory sector identifier.",
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
#endif
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
		io_handle->byte_order = LIBOLECF_ENDIAN_LITTLE;
	}
	else if( ( ( (olecf_file_header_t *) data )->byte_order[ 0 ] == 0xff )
	      && ( ( (olecf_file_header_t *) data )->byte_order[ 1 ] == 0xfe ) )
	{
		io_handle->byte_order = LIBOLECF_ENDIAN_BIG;
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
	if( io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint16_little_endian(
		 ( (olecf_file_header_t *) data )->minor_version,
		 io_handle->minor_version );

		byte_stream_copy_to_uint16_little_endian(
		 ( (olecf_file_header_t *) data )->major_version,
		 io_handle->major_version );

		byte_stream_copy_to_uint16_little_endian(
		 ( (olecf_file_header_t *) data )->sector_size,
		 sector_size );

		byte_stream_copy_to_uint16_little_endian(
		 ( (olecf_file_header_t *) data )->short_sector_size,
		 short_sector_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->number_of_sat_sectors,
		 *number_of_sat_sectors );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->root_directory_sector_identifier,
		 *root_directory_sector_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->sector_stream_minimum_data_size,
		 io_handle->sector_stream_minimum_data_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->ssat_sector_identifier,
		 *ssat_sector_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->number_of_ssat_sectors,
		 *number_of_ssat_sectors );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->msat_sector_identifier,
		 *msat_sector_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_file_header_t *) data )->number_of_msat_sectors,
		 *number_of_msat_sectors );
	}
	else if( io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint16_big_endian(
		 ( (olecf_file_header_t *) data )->minor_version,
		 io_handle->minor_version );

		byte_stream_copy_to_uint16_big_endian(
		 ( (olecf_file_header_t *) data )->major_version,
		 io_handle->major_version );

		byte_stream_copy_to_uint16_big_endian(
		 ( (olecf_file_header_t *) data )->sector_size,
		 sector_size );

		byte_stream_copy_to_uint16_big_endian(
		 ( (olecf_file_header_t *) data )->short_sector_size,
		 short_sector_size );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->number_of_sat_sectors,
		 *number_of_sat_sectors );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->root_directory_sector_identifier,
		 *root_directory_sector_identifier );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->sector_stream_minimum_data_size,
		 io_handle->sector_stream_minimum_data_size );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->ssat_sector_identifier,
		 *ssat_sector_identifier );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->number_of_ssat_sectors,
		 *number_of_ssat_sectors );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->msat_sector_identifier,
		 *msat_sector_identifier );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_file_header_t *) data )->number_of_msat_sectors,
		 *number_of_msat_sectors );
	}
	io_handle->sector_size       = 1 << sector_size;
	io_handle->short_sector_size = 1 << short_sector_size;

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
		     io_handle->byte_order,
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
		 "%s: minor version\t\t\t\t: %" PRIu16 "\n",
		 function,
		 io_handle->minor_version );

		libcnotify_printf(
		 "%s: major version\t\t\t\t: %" PRIu16 "\n",
		 function,
		 io_handle->major_version );

		libcnotify_printf(
		 "%s: byte order\t\t\t\t: 0x%02" PRIx8 " 0x%02" PRIx8 "\n",
		 function,
		 ( (olecf_file_header_t *) data )->byte_order[ 0 ],
		 ( (olecf_file_header_t *) data )->byte_order[ 1 ] );

		libcnotify_printf(
		 "%s: sector size\t\t\t\t: 0x%04" PRIx16 " (%" PRIzd ")\n",
		 function,
		 sector_size,
		 io_handle->sector_size );

		libcnotify_printf(
		 "%s: short sector size\t\t\t: 0x%04" PRIx16 " (%" PRIzd ")\n",
		 function,
		 short_sector_size,
		 io_handle->short_sector_size );

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
		 *number_of_sat_sectors );

		libcnotify_printf(
		 "%s: root directory sector identifier\t: 0x%08" PRIx32 "\n",
		 function,
		 *root_directory_sector_identifier );

		libcnotify_printf(
		 "%s: transactioning signature:\n",
		 function );
		libcnotify_print_data(
		 ( (olecf_file_header_t *) data )->transactioning_signature,
		 4,
		 0 );

		libcnotify_printf(
		 "%s: sector stream minimum data size\t: %" PRIu32 "\n",
		 function,
		 io_handle->sector_stream_minimum_data_size );
	
		libcnotify_printf(
		 "%s: SSAT sector identifier\t\t: 0x%08" PRIx32 "\n",
		 function,
		 *ssat_sector_identifier );

		libcnotify_printf(
		 "%s: number of SSAT sectors\t\t: %" PRIu32 "\n",
		 function,
		 *number_of_ssat_sectors );
	
		libcnotify_printf(
		 "%s: MSAT sector identifier\t\t: 0x%08" PRIx32 "\n",
		 function,
		 *msat_sector_identifier );

		libcnotify_printf(
		 "%s: number of MSAT sectors\t\t: %" PRIu32 "\n",
		 function,
		 *number_of_msat_sectors );
	}
#endif

	if( io_handle->sector_size > (ssize_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid sector size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( io_handle->short_sector_size > (ssize_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid short sector size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if SIZEOF_SIZE_T <= 4
	if( io_handle->sector_stream_minimum_data_size > (uint32_t) SSIZE_MAX )
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
		if( io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
		{
			byte_stream_copy_to_uint32_little_endian(
			 msat_entry,
			 msat->sector_identifier[ msat_index ] );
		}
		else if( io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
		{
			byte_stream_copy_to_uint32_big_endian(
			 msat_entry,
			 msat->sector_identifier[ msat_index ] );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: MSAT entry: %03d sector identifier\t: 0x%08" PRIx32 "\n",
			 function,
			 msat_index,
			 msat->sector_identifier[ msat_index ] );
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

/* Reads the MSAT
 * This function assumes the first 109 MSAT sector identifiers in the file header are read into the MSAT
 * Returns 1 if successful or -1 on error
 */
int libolecf_io_handle_read_msat(
     libolecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libolecf_allocation_table_t *msat,
     uint32_t msat_sector_identifier,
     uint32_t number_of_msat_sectors,
     libcerror_error_t **error )
{
	uint8_t *msat_sector                 = NULL;
	uint8_t *msat_entry                  = NULL;
	static char *function                = "libolecf_io_handle_read_msat";
	off64_t msat_sector_offset           = 0;
	size_t number_of_msat_sector_entries = 0;
	ssize_t read_count                   = 0;
	int number_of_msat_entries           = 0;
	int msat_index                       = 109;
	int msat_sector_index                = 0;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( io_handle->sector_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - missing sector size.",
		 function );

		return( -1 );
	}
	if( io_handle->sector_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid IO handle - sector size value exceeds maximum.",
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
	if( msat->number_of_sector_identifiers < 109 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid IO handle - invalid MSAT - number of sector identifiers too small.",
		 function );

		return( -1 );
	}
	/* Check if the MSAT is already fully read
	 */
	if( ( msat_sector_identifier == LIBOLECF_SECTOR_IDENTIFIER_END_OF_CHAIN )
	 && ( number_of_msat_sectors == 0 ) )
	{
		return( 1 );
	}
	if( msat_sector_identifier == LIBOLECF_SECTOR_IDENTIFIER_END_OF_CHAIN )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid MSAT sector identifier.",
		 function );

		return( -1 );
	}
	if( number_of_msat_sectors == 0 )
	{
#if defined( HAVE_VERBOSE_OUTPUT ) || defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: mismatch between number of MSAT sectors and MSAT sector identifier\n",
			 function );
		}
#endif
		number_of_msat_sectors = 1;
	}
	number_of_msat_sector_entries = io_handle->sector_size / 4;

	if( number_of_msat_sector_entries == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of MSAT sector entries value out of bounds.",
		 function );

		goto on_error;
	}
	/* The last MSAT entry is reserved for the next MSAT sector identifier.
	 */
	number_of_msat_sector_entries -= 1;

	number_of_msat_entries = 109 + ( number_of_msat_sectors * number_of_msat_sector_entries );

	if( msat->number_of_sector_identifiers < number_of_msat_entries )
	{
		if( libolecf_allocation_table_resize(
		     msat,
		     number_of_msat_entries,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
			 "%s: unable to resize MSAT.",
			 function );

			goto on_error;
		}
	}
	msat_sector = (uint8_t *) memory_allocate(
	                           sizeof( uint8_t ) * io_handle->sector_size );

	if( msat_sector == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create MSAT sector.",
		 function );

		goto on_error;
	}
	while( msat_sector_identifier != LIBOLECF_SECTOR_IDENTIFIER_END_OF_CHAIN )
	{
		if( msat_index >= msat->number_of_sector_identifiers )
		{
			break;
		}
		msat_sector_offset = ( msat_sector_identifier + 1 ) * io_handle->sector_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: MSAT sector offset\t\t\t: %" PRIu64 "\n",
			 function,
			 msat_sector_offset );
		}
#endif
		if( libbfio_handle_seek_offset(
		     file_io_handle,
		     msat_sector_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek value offset: %" PRIu64 ".",
			 function,
			 msat_sector_offset );

			 goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      msat_sector,
			      io_handle->sector_size,
			      error );

		if( read_count != (ssize_t) io_handle->sector_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read MSAT sector.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: MSAT sector:\n",
			 function );
			libcnotify_print_data(
			 msat_sector,
			 io_handle->sector_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		msat_entry = msat_sector;

		for( msat_sector_index = 0;
		     (size_t) msat_sector_index < number_of_msat_sector_entries;
		     msat_sector_index++ )
		{
			if( ( msat_index < 0 )
			 || ( msat_index >= msat->number_of_sector_identifiers ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid MSAT entry: %04d value out of bounds.",
				 function,
				 msat_index );

				goto on_error;
			}
			if( io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
			{
				byte_stream_copy_to_uint32_little_endian(
				 msat_entry,
				 msat->sector_identifier[ msat_index ] );
			}
			else if( io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
			{
				byte_stream_copy_to_uint32_big_endian(
				 msat_entry,
				 msat->sector_identifier[ msat_index ] );
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: MSAT entry: %03d sector identifier\t: 0x%08" PRIx32 "\n",
				 function,
				 msat_index,
				 msat->sector_identifier[ msat_index ] );
			}
#endif
			msat_entry += 4;

			msat_index++;
		}
		if( io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
		{
			byte_stream_copy_to_uint32_little_endian(
			 msat_entry,
			 msat_sector_identifier );
		}
		else if( io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
		{
			byte_stream_copy_to_uint32_big_endian(
			 msat_entry,
			 msat_sector_identifier );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: MSAT sector identifier\t\t: 0x%08" PRIx32 "\n",
			 function,
			 msat_sector_identifier );
			libcnotify_printf(
			 "\n" );
		}
#endif
	}
	memory_free(
	 msat_sector );

	return( 1 );

on_error:
	if( msat_sector != NULL )
	{
		memory_free(
		 msat_sector );
	}
	return( -1 );

}

/* Reads the SAT
 * This function requires that the MSAT was read
 * Returns 1 if successful or -1 on error
 */
int libolecf_io_handle_read_sat(
     libolecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libolecf_allocation_table_t *msat,
     libolecf_allocation_table_t *sat,
     uint32_t number_of_sat_sectors,
     libcerror_error_t **error )
{
	uint8_t *sat_sector                 = NULL;
	uint8_t *sat_entry                  = NULL;
	static char *function               = "libolecf_io_handle_read_sat";
	off64_t sat_sector_offset           = 0;
	size_t number_of_sat_sector_entries = 0;
	ssize_t read_count                  = 0;
	int number_of_sat_entries           = 0;
	int msat_index                      = 0;
	int sat_index                       = 0;
	int sat_sector_index                = 0;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( io_handle->sector_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - missing sector size.",
		 function );

		return( -1 );
	}
	if( io_handle->sector_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid IO handle - sector size value exceeds maximum.",
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
	if( sat == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid SAT.",
		 function );

		return( -1 );
	}
	number_of_sat_sector_entries = io_handle->sector_size / 4;
	number_of_sat_entries        = number_of_sat_sectors * number_of_sat_sector_entries;

	if( sat->number_of_sector_identifiers < number_of_sat_entries )
	{
		if( libolecf_allocation_table_resize(
		     sat,
		     number_of_sat_entries,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
			 "%s: unable to resize SAT.",
			 function );

			goto on_error;
		}
	}
	sat_sector = (uint8_t *) memory_allocate(
	                          sizeof( uint8_t ) * io_handle->sector_size );

	if( sat_sector == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create SAT sector.",
		 function );

		goto on_error;
	}
	for( msat_index = 0;
	     msat_index < msat->number_of_sector_identifiers;
	     msat_index++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: MSAT entry: %03d sector identifier\t\t: 0x%08" PRIx32 "\n",
			 function,
			 msat_index,
			 msat->sector_identifier[ msat_index ] );
		}
#endif
		/* Skip empty sector identifiers
		 */
		if( msat->sector_identifier[ msat_index ] == LIBOLECF_SECTOR_IDENTIFIER_UNUSED )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "\n" );
			}
#endif
			continue;
		}
		if( sat_index >= sat->number_of_sector_identifiers )
		{
			break;
		}
		sat_sector_offset = ( msat->sector_identifier[ msat_index ] + 1 ) * io_handle->sector_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: SAT sector offset\t\t\t\t: %" PRIu64 "\n",
			 function,
			 sat_sector_offset );
		}
#endif
		if( libbfio_handle_seek_offset(
		     file_io_handle,
		     sat_sector_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek value offset: %" PRIu64 ".",
			 function,
			 sat_sector_offset );

			 goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      sat_sector,
			      io_handle->sector_size,
			      error );

		if( read_count != (ssize_t) io_handle->sector_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read SAT sector.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: SAT sector:\n",
			 function );
			libcnotify_print_data(
			 sat_sector,
			 io_handle->sector_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		sat_entry = sat_sector;

		for( sat_sector_index = 0;
		     (size_t) sat_sector_index < number_of_sat_sector_entries;
		     sat_sector_index++ )
		{
			if( io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
			{
				byte_stream_copy_to_uint32_little_endian(
				 sat_entry,
				 sat->sector_identifier[ sat_index ] );
			}
			else if( io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
			{
				byte_stream_copy_to_uint32_big_endian(
				 sat_entry,
				 sat->sector_identifier[ sat_index ] );
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: SAT entry: %04d sector identifier\t\t: 0x%08" PRIx32 "\n",
				 function,
				 sat_index,
				 sat->sector_identifier[ sat_index ] );
			}
#endif
			sat_entry += 4;

			sat_index++;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
	}
	memory_free(
	 sat_sector );

	return( 1 );

on_error:
	if( sat_sector != NULL )
	{
		memory_free(
		 sat_sector );
	}
	return( 1 );
}

/* Reads the SSAT
 * This function requires that the SAT was read
 * Returns 1 if successful or -1 on error
 */
int libolecf_io_handle_read_ssat(
     libolecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libolecf_allocation_table_t *sat,
     libolecf_allocation_table_t *ssat,
     uint32_t ssat_sector_identifier,
     uint32_t number_of_ssat_sectors,
     libcerror_error_t **error )
{
	uint8_t *ssat_sector                 = NULL;
	uint8_t *ssat_entry                  = NULL;
	static char *function                = "libolecf_io_handle_read_ssat";
	off64_t ssat_sector_offset           = 0;
	size_t number_of_ssat_sector_entries = 0;
	ssize_t read_count                   = 0;
	uint32_t ssat_sector_index           = 0;
	int number_of_ssat_entries           = 0;
	int ssat_index                       = 0;
	int ssat_sector_entry_index          = 0;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( io_handle->sector_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - missing sector size.",
		 function );

		return( -1 );
	}
	if( io_handle->sector_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid IO handle - sector size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( sat == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid SAT.",
		 function );

		return( -1 );
	}
	if( ssat == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid SSAT.",
		 function );

		return( -1 );
	}
	number_of_ssat_sector_entries = io_handle->sector_size / 4;
	number_of_ssat_entries        = number_of_ssat_sectors * number_of_ssat_sector_entries;

	if( ssat->number_of_sector_identifiers < number_of_ssat_entries )
	{
		if( libolecf_allocation_table_resize(
		     ssat,
		     number_of_ssat_entries,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
			 "%s: unable to resize SSAT.",
			 function );

			goto on_error;
		}
	}
	ssat_sector = (uint8_t *) memory_allocate(
	                           sizeof( uint8_t ) * io_handle->sector_size );

	if( ssat_sector == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create SSAT sector.",
		 function );

		goto on_error;
	}
	while( ssat_sector_identifier != LIBOLECF_SECTOR_IDENTIFIER_END_OF_CHAIN )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: SSAT sector identifier\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 ssat_sector_identifier );
		}
#endif
		if( ssat_sector_index >= number_of_ssat_sectors )
		{
			break;
		}
		/* Skip empty sector identifiers
		 */
		if( ssat_sector_identifier == LIBOLECF_SECTOR_IDENTIFIER_UNUSED )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "\n" );
			}
#endif
			ssat_sector_index++;

			continue;
		}
		ssat_sector_offset = ( ssat_sector_identifier + 1 ) * io_handle->sector_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: SSAT sector offset\t\t\t: %" PRIu64 "\n",
			 function,
			 ssat_sector_offset );
		}
#endif
		if( libbfio_handle_seek_offset(
		     file_io_handle,
		     ssat_sector_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek value offset: %" PRIu64 ".",
			 function,
			 ssat_sector_offset );

			 goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      ssat_sector,
			      io_handle->sector_size,
			      error );

		if( read_count != (ssize_t) io_handle->sector_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read SSAT sector.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: SSAT sector:\n",
			 function );
			libcnotify_print_data(
			 ssat_sector,
			 io_handle->sector_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		ssat_entry = ssat_sector;

		for( ssat_sector_entry_index = 0;
		     (size_t) ssat_sector_entry_index < number_of_ssat_sector_entries;
		     ssat_sector_entry_index++ )
		{
			if( ( ssat_index < 0 )
			 || ( ssat_index >= ssat->number_of_sector_identifiers ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid SSAT entry: %04d value out of bounds.",
				 function,
				 ssat_index );

				goto on_error;
			}
			if( io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ssat_entry,
				 ssat->sector_identifier[ ssat_index ] );
			}
			else if( io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
			{
				byte_stream_copy_to_uint32_big_endian(
				 ssat_entry,
				 ssat->sector_identifier[ ssat_index ] );
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: SSAT entry: %04d sector identifier\t: 0x%08" PRIx32 "\n",
				 function,
				 ssat_index,
				 ssat->sector_identifier[ ssat_index ] );
			}
#endif
			ssat_entry += 4;

			ssat_index++;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
#if SIZE_OF_INT <= 4
		if( ssat_sector_identifier >= (uint32_t) sat->number_of_sector_identifiers )
#else
		if( (int) ssat_sector_identifier >= sat->number_of_sector_identifiers )
#endif
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid short sector identifier: 0x%08" PRIx32 " value out of bounds.",
			 function,
			 ssat_sector_identifier );

			goto on_error;
		}
		ssat_sector_identifier = sat->sector_identifier[ ssat_sector_identifier ];

		ssat_sector_index++;
	}
	memory_free(
	 ssat_sector );

	return( 1 );

on_error:
	if( ssat_sector == NULL )
	{
		memory_free(
		 ssat_sector );
	}
	return( 1 );
}

/* Reads the directory entries
 * This function requires that the SAT was read
 * Returns 1 if successful or -1 on error
 */
int libolecf_io_handle_read_directory_entries(
     libolecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libolecf_allocation_table_t *sat,
     libcdata_list_t *directory_entry_list,
     uint32_t root_directory_sector_identifier,
     libcerror_error_t **error )
{
	libcdata_range_list_t *read_directory_sector_list = NULL;
	libolecf_directory_entry_t *directory_entry       = NULL;
	uint8_t *directory_entry_data                     = NULL;
	uint8_t *directory_sector                         = NULL;
	static char *function                             = "libolecf_io_handle_read_directory_entries";
	off64_t directory_sector_offset                   = 0;
	size_t number_of_directory_sector_entries         = 0;
	ssize_t read_count                                = 0;
	uint32_t directory_sector_identifier              = 0;
	int directory_entry_index                         = 0;
	int directory_sector_index                        = 0;
	int result                                        = 0;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( io_handle->sector_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - missing sector size.",
		 function );

		return( -1 );
	}
	if( io_handle->sector_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid IO handle - sector size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( sat == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid SAT.",
		 function );

		return( -1 );
	}
	if( directory_entry_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry list.",
		 function );

		return( -1 );
	}
	if( root_directory_sector_identifier == LIBOLECF_SECTOR_IDENTIFIER_END_OF_CHAIN )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid root directory sector identifier.",
		 function );

		return( -1 );
	}
	number_of_directory_sector_entries = io_handle->sector_size / sizeof( olecf_directory_entry_t );

	directory_sector = (uint8_t *) memory_allocate(
	                                sizeof( uint8_t ) * io_handle->sector_size );

	if( directory_sector == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create directory sector.",
		 function );

		goto on_error;
	}
	if( libcdata_range_list_initialize(
	     &read_directory_sector_list,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create read directory sector list.",
		 function );

		goto on_error;
	}
	directory_sector_identifier = root_directory_sector_identifier;

	while( ( directory_sector_identifier != LIBOLECF_SECTOR_IDENTIFIER_END_OF_CHAIN )
	    && ( directory_sector_identifier != LIBOLECF_SECTOR_IDENTIFIER_UNUSED ) )
	{
		result = libcdata_range_list_range_is_present(
		          read_directory_sector_list,
		          (uint64_t) directory_sector_identifier,
		          (uint64_t) 1,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine if directory sector is in range list.",
			 function );

			goto on_error;
		}
		else if( result != 0 )
		{
			break;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: directory sector identifier\t: 0x%08" PRIx32 "\n",
			 function,
			 directory_sector_identifier );
		}
#endif
		directory_sector_offset = ( directory_sector_identifier + 1 ) * io_handle->sector_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: directory sector offset\t: 0x%08" PRIx64 "\n",
			 function,
			 directory_sector_offset );
		}
#endif
		if( libbfio_handle_seek_offset(
		     file_io_handle,
		     directory_sector_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek value offset: %" PRIu64 ".",
			 function,
			 directory_sector_offset );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      directory_sector,
			      io_handle->sector_size,
			      error );

		if( read_count != (ssize_t) io_handle->sector_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read directory sector.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: directory sector:\n",
			 function );
			libcnotify_print_data(
			 directory_sector,
			 io_handle->sector_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		directory_entry_data = directory_sector;

		for( directory_sector_index = 0;
		     (size_t) directory_sector_index < number_of_directory_sector_entries;
		     directory_sector_index++ )
		{
			if( libolecf_directory_entry_initialize(
			     &directory_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create directory entry: %d.",
				 function,
				 directory_sector_index );

				goto on_error;
			}
			result = libolecf_directory_entry_read_data(
			          directory_entry,
			          directory_entry_index,
			          directory_entry_data,
			          sizeof( olecf_directory_entry_t ),
			          io_handle->byte_order,
			          error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read directory entry: %d.",
				 function,
				 directory_sector_index );

				goto on_error;
			}
			if( directory_entry->type == LIBOLECF_ITEM_TYPE_EMPTY )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: directory sector entry: %d is empty (type is empty).\n",
					 function,
					 directory_sector_index );
				}
#endif
				if( libolecf_directory_entry_free(
				     &directory_entry,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free directory entry.",
					 function );

					goto on_error;
				}
			}
			else
			{
				if( libcdata_list_append_value(
				     directory_entry_list,
				     (intptr_t *) directory_entry,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append directory entry.",
					 function );

					goto on_error;
				}
				directory_entry = NULL;
			}
			directory_entry_index++;

			directory_entry_data += sizeof( olecf_directory_entry_t );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
		if( libcdata_range_list_insert_range(
		     read_directory_sector_list,
		     (uint64_t) directory_sector_identifier,
		     (uint64_t) 1,
		     NULL,
		     NULL,
		     NULL,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to insert directory sector into range list.",
			 function );

			goto on_error;
		}
#if SIZE_OF_INT <= 4
		if( directory_sector_identifier >= (uint32_t) sat->number_of_sector_identifiers )
#else
		if( (int) directory_sector_identifier >= sat->number_of_sector_identifiers )
#endif
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid directory sector identifier: 0x%08" PRIx32 " value out of bounds.",
			 function,
			 directory_sector_identifier );

			goto on_error;
		}
		directory_sector_identifier = sat->sector_identifier[ directory_sector_identifier ];
	}
	if( libcdata_range_list_free(
	     &read_directory_sector_list,
	     NULL,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free read directory sector list.",
		 function );

		goto on_error;
	}
	memory_free(
	 directory_sector );

	directory_sector = NULL;

	return( 1 );

on_error:
	if( directory_entry != NULL )
	{
		libolecf_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	if( read_directory_sector_list != NULL )
	{
		libcdata_range_list_free(
		 &read_directory_sector_list,
		 NULL,
		 NULL );
	}
	if( directory_sector != NULL )
	{
		memory_free(
		 directory_sector );
	}
	libcdata_list_empty(
	 directory_entry_list,
         (int (*)(intptr_t **, libcerror_error_t **)) &libolecf_directory_entry_free,
	 NULL );

	return( -1 );
}

/* Reads a buffer from the stream
 * This function requires that the SAT and SSAT were read
 * Returns 1 if successful or -1 on error
 */
ssize_t libolecf_io_handle_read_stream(
         libolecf_io_handle_t *io_handle,
         libbfio_handle_t *file_io_handle,
         libolecf_allocation_table_t *sat,
         libolecf_allocation_table_t *ssat,
         libolecf_directory_entry_t *directory_entry,
         off64_t *offset,
         uint8_t *buffer,
         size_t size,
         libcerror_error_t **error )
{
	libolecf_allocation_table_t *allocation_table  = NULL;
	static char *function                          = "libolecf_io_handle_read_stream";
	off64_t read_offset                            = 0;
	off64_t sector_boundary_offset                 = 0;
	size_t buffer_offset                           = 0;
	size_t read_size                               = 0;
	size_t sector_size                             = 0;
	ssize_t read_count                             = 0;
	uint32_t sector_identifier                     = 0;
	uint32_t short_sector_stream_sector_identifier = 0;
	int sector_identifier_index                    = 0;
	int sector_identifier_iterator                 = 0;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	if( *offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid offset value out of bounds.",
		 function );

		return( -1 );
	}
/* TODO offset upper boundary check ? */
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( directory_entry->size < io_handle->sector_stream_minimum_data_size )
	{
		if( ssat == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid SSAT.",
			 function );

			return( -1 );
		}
		allocation_table = ssat;
		sector_size      = io_handle->short_sector_size;
	}
	else
	{
		if( sat == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid SAT.",
			 function );

			return( -1 );
		}
		allocation_table = sat;
		sector_size      = io_handle->sector_size;
	}
	sector_identifier_index = (int) ( *offset / sector_size );

	if( ( sector_identifier_index < 0 )
	 || ( sector_identifier_index >= allocation_table->number_of_sector_identifiers ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sector identifier index value out of bounds.",
		 function );

		return( -1 );
	}
	sector_identifier = directory_entry->sector_identifier;

	for( sector_identifier_iterator = sector_identifier_index;
	     sector_identifier_iterator > 0;
	     sector_identifier_iterator-- )
	{
		if( sector_identifier == LIBOLECF_SECTOR_IDENTIFIER_END_OF_CHAIN )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid sector identifier.",
			 function );

			return( -1 );
		}
#if SIZE_OF_INT <= 4
		if( sector_identifier >= (uint32_t) allocation_table->number_of_sector_identifiers )
#else
		if( (int) sector_identifier >= allocation_table->number_of_sector_identifiers )
#endif
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid sector identifier: 0x%08" PRIx32 " value out of bounds.",
			 function,
			 sector_identifier );

			return( -1 );
		}
		sector_identifier = allocation_table->sector_identifier[ sector_identifier ];
	}
	while( size > 0 )
	{
		if( sector_identifier == LIBOLECF_SECTOR_IDENTIFIER_END_OF_CHAIN )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid sector identifier.",
			 function );

			return( -1 );
		}
		sector_boundary_offset = (off64_t) ( sector_identifier_index * sector_size );

		/* Determine start offset and read size
		 */
		if( directory_entry->size < io_handle->sector_stream_minimum_data_size )
		{
			read_offset = sector_identifier * sector_size;

			short_sector_stream_sector_identifier = io_handle->short_sector_stream_start_sector_identifier;

			while( read_offset >= (off64_t) io_handle->sector_size )
			{
#if SIZE_OF_INT <= 4
				if( short_sector_stream_sector_identifier >= (uint32_t) sat->number_of_sector_identifiers )
#else
				if( (int) short_sector_stream_sector_identifier >= sat->number_of_sector_identifiers )
#endif
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid short sector stream sector identifier: 0x%08" PRIx32 " value out of bounds.",
					 function,
					 short_sector_stream_sector_identifier );

					return( -1 );
				}
				short_sector_stream_sector_identifier = sat->sector_identifier[ short_sector_stream_sector_identifier ];

				read_offset -= io_handle->sector_size;
			}
			read_offset += ( short_sector_stream_sector_identifier + 1 ) * io_handle->sector_size;
		}
		else
		{
			read_offset = ( sector_identifier + 1 ) * sector_size;
		}
		read_size = sector_size;

		if( *offset > sector_boundary_offset )
		{
			read_offset += *offset - sector_boundary_offset;
			read_size   -= (size_t) ( *offset - sector_boundary_offset );
		}
		if( read_size > size )
		{
			read_size = size;
		}
		/* Read sector data into the buffer
		 */
		if( libbfio_handle_seek_offset(
		     file_io_handle,
		     read_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek value offset: %" PRIu64 ".",
			 function,
			 read_offset );

			 return( -1 );
		}
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      &( buffer[ buffer_offset ] ),
			      read_size,
			      error );

		if( read_count != (ssize_t) read_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read sector: %" PRIu32 ".",
			 function,
			 sector_identifier );

			return( -1 );
		}
		buffer_offset += read_size;
		*offset       += read_size;
		size          -= read_size;

#if SIZE_OF_INT <= 4
		if( sector_identifier >= (uint32_t) allocation_table->number_of_sector_identifiers )
#else
		if( (int) sector_identifier >= allocation_table->number_of_sector_identifiers )
#endif
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid sector identifier: 0x%08" PRIx32 " value out of bounds.",
			 function,
			 sector_identifier );

			return( -1 );
		}
		sector_identifier = allocation_table->sector_identifier[ sector_identifier ];

		sector_identifier_index++;

	}
	return( (ssize_t) buffer_offset );
}

