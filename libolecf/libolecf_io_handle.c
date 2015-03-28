/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2008-2015, Joachim Metz <joachim.metz@gmail.com>
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
#include "libolecf_libcstring.h"
#include "libolecf_libfdatetime.h"
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

	uint8_t *msat_entry         = NULL;
	static char *function       = "libolecf_io_handle_read_file_header";
	ssize_t read_count          = 0;
	int msat_index              = 0;
	uint16_t sector_size        = 0;
	uint16_t short_sector_size  = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t guid_string[ 48 ];

	libfguid_identifier_t *guid = NULL;
	int result                  = 0;
#endif

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

			goto on_error;
		}
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

		goto on_error;
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

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &file_header,
		 sizeof( olecf_file_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( ( memory_compare(
	       file_header.signature,
	       olecf_file_signature,
	       8 ) != 0 )
	 && ( memory_compare(
	       file_header.signature,
	       olecf_beta_file_signature,
	       8 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file signature.",
		 function );

		goto on_error;
	}
	if( ( file_header.byte_order[ 0 ] == 0xfe )
	 && ( file_header.byte_order[ 1 ] == 0xff ) )
	{
		io_handle->byte_order = LIBOLECF_ENDIAN_LITTLE;
	}
	else if( ( file_header.byte_order[ 0 ] == 0xff )
	      && ( file_header.byte_order[ 1 ] == 0xfe ) )
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
		 file_header.byte_order[ 0 ],
		 file_header.byte_order[ 1 ] );

		goto on_error;
	}
	if( io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint16_little_endian(
		 file_header.minor_version,
		 io_handle->minor_version );

		byte_stream_copy_to_uint16_little_endian(
		 file_header.major_version,
		 io_handle->major_version );

		byte_stream_copy_to_uint16_little_endian(
		 file_header.sector_size,
		 sector_size );

		byte_stream_copy_to_uint16_little_endian(
		 file_header.short_sector_size,
		 short_sector_size );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.number_of_sat_sectors,
		 *number_of_sat_sectors );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.root_directory_sector_identifier,
		 *root_directory_sector_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.sector_stream_minimum_data_size,
		 io_handle->sector_stream_minimum_data_size );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.ssat_sector_identifier,
		 *ssat_sector_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.number_of_ssat_sectors,
		 *number_of_ssat_sectors );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.msat_sector_identifier,
		 *msat_sector_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.number_of_msat_sectors,
		 *number_of_msat_sectors );
	}
	else if( io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint16_big_endian(
		 file_header.minor_version,
		 io_handle->minor_version );

		byte_stream_copy_to_uint16_big_endian(
		 file_header.major_version,
		 io_handle->major_version );

		byte_stream_copy_to_uint16_big_endian(
		 file_header.sector_size,
		 sector_size );

		byte_stream_copy_to_uint16_big_endian(
		 file_header.short_sector_size,
		 short_sector_size );

		byte_stream_copy_to_uint32_big_endian(
		 file_header.number_of_sat_sectors,
		 *number_of_sat_sectors );

		byte_stream_copy_to_uint32_big_endian(
		 file_header.root_directory_sector_identifier,
		 *root_directory_sector_identifier );

		byte_stream_copy_to_uint32_big_endian(
		 file_header.sector_stream_minimum_data_size,
		 io_handle->sector_stream_minimum_data_size );

		byte_stream_copy_to_uint32_big_endian(
		 file_header.ssat_sector_identifier,
		 *ssat_sector_identifier );

		byte_stream_copy_to_uint32_big_endian(
		 file_header.number_of_ssat_sectors,
		 *number_of_ssat_sectors );

		byte_stream_copy_to_uint32_big_endian(
		 file_header.msat_sector_identifier,
		 *msat_sector_identifier );

		byte_stream_copy_to_uint32_big_endian(
		 file_header.number_of_msat_sectors,
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
		 file_header.signature,
		 8,
		 0 );

		if( libfguid_identifier_initialize(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create GUID.",
			 function );

			goto on_error;
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     file_header.class_identifier,
		     16,
		     io_handle->byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: class identifier\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 guid_string );

		if( libfguid_identifier_free(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free GUID.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: minor version\t\t\t: %" PRIu16 "\n",
		 function,
		 io_handle->minor_version );

		libcnotify_printf(
		 "%s: major version\t\t\t: %" PRIu16 "\n",
		 function,
		 io_handle->major_version );

		libcnotify_printf(
		 "%s: byte order\t\t\t\t: 0x%02" PRIx8 " 0x%02" PRIx8 "\n",
		 function,
		 file_header.byte_order[ 0 ],
		 file_header.byte_order[ 1 ] );

		libcnotify_printf(
		 "%s: sector size\t\t\t: 0x%04" PRIx16 " (%" PRIzd ")\n",
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
		 file_header.reserved1,
		 10,
		 0 );

		libcnotify_printf(
		 "%s: number of SAT sectors\t\t: %" PRIu32 "\n",
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
		 file_header.transactioning_signature,
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

		goto on_error;
	}
	if( io_handle->short_sector_size > (ssize_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid short sector size value exceeds maximum.",
		 function );

		goto on_error;
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

		goto on_error;
	}
#endif
	msat_entry = file_header.msat;

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

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
#endif
	return( -1 );
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
	number_of_msat_entries        = ( number_of_msat_sectors * ( number_of_msat_sector_entries - 1 ) )
	                              + 109;

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
		     (size_t) msat_sector_index < ( number_of_msat_sector_entries - 1 );
		     msat_sector_index++ )
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
	libolecf_directory_entry_t *directory_entry = NULL;
	uint8_t *directory_entry_data               = NULL;
	uint8_t *directory_sector                   = NULL;
	static char *function                       = "libolecf_io_handle_read_directory_entries";
	off64_t directory_sector_offset             = 0;
	size_t number_of_directory_sector_entries   = 0;
	ssize_t read_count                          = 0;
	uint32_t directory_sector_identifier        = 0;
	uint16_t name_byte_size                     = 0;
	int directory_entry_index                   = 0;
	int directory_sector_index                  = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t filetime_string[ 32 ];
	libcstring_system_character_t guid_string[ 48 ];

	libfdatetime_filetime_t *filetime           = NULL;
	libfguid_identifier_t *guid                 = NULL;
	libcstring_system_character_t *name_string  = NULL;
	size_t name_string_size                     = 0;
	uint32_t value_32bit                        = 0;
	int result                                  = 0;
#endif

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
	directory_sector_identifier = root_directory_sector_identifier;

	while( ( directory_sector_identifier != LIBOLECF_SECTOR_IDENTIFIER_END_OF_CHAIN )
	    && ( directory_sector_identifier != LIBOLECF_SECTOR_IDENTIFIER_UNUSED ) )
	{
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
			 "%s: directory sector offset\t: %" PRIu64 "\n",
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
			if( ( (olecf_directory_entry_t *) directory_entry_data )->type != LIBOLECF_ITEM_TYPE_EMPTY )
			{
				if( libolecf_directory_entry_initialize(
				     &directory_entry,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create directory entry.",
					 function );

					goto on_error;
				}
				if( io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
				{
					byte_stream_copy_to_uint16_little_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->name_byte_size,
					 name_byte_size );
				}
				else if( io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
				{
					byte_stream_copy_to_uint16_big_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->name_byte_size,
					 name_byte_size );
				}
				if( name_byte_size > 0 )
				{
					if( (size_t) name_byte_size > sizeof( olecf_directory_entry_t ) )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
						 "%s: name byte size value out of bounds.",
						 function );

						goto on_error;
					}
					directory_entry->name = (uint8_t *) memory_allocate(
					                                     sizeof( uint8_t ) * name_byte_size );

					if( directory_entry->name == NULL )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_MEMORY,
						 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
						 "%s: unable to create name.",
						 function );

						goto on_error;
					}
					if( memory_copy(
					     directory_entry->name,
					     ( (olecf_directory_entry_t *) directory_entry_data )->name,
					     name_byte_size ) == NULL )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_MEMORY,
						 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
						 "%s: unable to copy name.",
						 function );

						goto on_error;
					}
				}
				directory_entry->name_size = (size_t) name_byte_size;

				directory_entry->type = ( (olecf_directory_entry_t *) directory_entry_data )->type;

				if( io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
				{
					byte_stream_copy_to_uint32_little_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->previous_directory_identifier,
					 directory_entry->previous_directory_identifier );

					byte_stream_copy_to_uint32_little_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->next_directory_identifier,
					 directory_entry->next_directory_identifier );

					byte_stream_copy_to_uint32_little_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->sub_directory_identifier,
					 directory_entry->sub_directory_identifier );

					byte_stream_copy_to_uint64_little_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->creation_time,
					 directory_entry->creation_time );

					byte_stream_copy_to_uint64_little_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->modification_time,
					 directory_entry->modification_time );

					byte_stream_copy_to_uint32_little_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->sector_identifier,
					 directory_entry->sector_identifier );

					byte_stream_copy_to_uint32_little_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->size,
					 directory_entry->size );
				}
				else if( io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
				{
					byte_stream_copy_to_uint32_big_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->previous_directory_identifier,
					 directory_entry->previous_directory_identifier );

					byte_stream_copy_to_uint32_big_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->next_directory_identifier,
					 directory_entry->next_directory_identifier );

					byte_stream_copy_to_uint32_big_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->sub_directory_identifier,
					 directory_entry->sub_directory_identifier );

					byte_stream_copy_to_uint64_big_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->creation_time,
					 directory_entry->creation_time );

					byte_stream_copy_to_uint64_big_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->modification_time,
					 directory_entry->modification_time );

					byte_stream_copy_to_uint32_big_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->sector_identifier,
					 directory_entry->sector_identifier );

					byte_stream_copy_to_uint32_big_endian(
					 ( (olecf_directory_entry_t *) directory_entry_data )->size,
					 directory_entry->size );
				}
				directory_entry->directory_identifier = (uint32_t) directory_entry_index;

#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: directory entry: %03d name\t\t\t\t: ",
					 function,
					 directory_entry_index );

					if( directory_entry->name != NULL )
					{
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
						result = libuna_utf16_string_size_from_utf16_stream(
						          directory_entry->name,
						          directory_entry->name_size,
						          io_handle->byte_order,
						          &( name_string_size ),
						          error );
#else
						result = libuna_utf8_string_size_from_utf16_stream(
						          directory_entry->name,
						          directory_entry->name_size,
						          io_handle->byte_order,
						          &( name_string_size ),
						          error );
#endif
						if( result != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
							 "%s: unable to determine name size.",
							 function );

							goto on_error;
						}
						name_string = libcstring_system_string_allocate(
						               name_string_size );

						if( name_string == NULL )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_MEMORY,
							 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
							 "%s: unable to create name string.",
							 function );

							goto on_error;
						}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
						result = libuna_utf16_string_copy_from_utf16_stream(
							  (uint16_t *) name_string,
							  name_string_size,
							  directory_entry->name,
							  directory_entry->name_size,
							  io_handle->byte_order,
							  error );
#else
						result = libuna_utf8_string_copy_from_utf16_stream(
							  (uint8_t *) name_string,
							  name_string_size,
							  directory_entry->name,
							  directory_entry->name_size,
							  io_handle->byte_order,
							  error );
#endif
						if( result != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_CONVERSION,
							 LIBCERROR_CONVERSION_ERROR_GENERIC,
							 "%s: unable to set name string.",
							 function );

							goto on_error;
						}
						libcnotify_printf(
						 "%" PRIs_LIBCSTRING_SYSTEM "",
						 name_string );

						memory_free(
						 name_string );

						name_string = NULL;
					}
					libcnotify_printf(
					 "\n" );

					libcnotify_printf(
					 "%s: directory entry: %03d name byte size\t\t\t: %" PRIu16 "\n",
					 function,
					 directory_entry_index,
					 name_byte_size );
					libcnotify_printf(
					 "%s: directory entry: %03d type\t\t\t\t: 0x%02" PRIx8 " (%s)\n",
					 function,
					 directory_entry_index,
					 directory_entry->type,
					 libolecf_debug_print_item_type(
					  directory_entry->type ) );
					libcnotify_printf(
					 "%s: directory entry: %03d node color\t\t\t: 0x%02" PRIx8 "\n",
					 function,
					 directory_entry_index,
					 ( (olecf_directory_entry_t *) directory_entry_data )->node_color );

					libcnotify_printf(
					 "%s: directory entry: %03d previous directory identifier\t: 0x%08" PRIx32 "\n",
					 function,
					 directory_entry_index,
					 directory_entry->previous_directory_identifier );
					libcnotify_printf(
					 "%s: directory entry: %03d next directory identifier\t: 0x%08" PRIx32 "\n",
					 function,
					 directory_entry_index,
					 directory_entry->next_directory_identifier );
					libcnotify_printf(
					 "%s: directory entry: %03d sub directory identifier\t: 0x%08" PRIx32 "\n",
					 function,
					 directory_entry_index,
					 directory_entry->sub_directory_identifier );

					if( libfguid_identifier_initialize(
					     &guid,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
						 "%s: unable to create GUID.",
						 function );

						goto on_error;
					}
					if( libfguid_identifier_copy_from_byte_stream(
					     guid,
					     ( (olecf_directory_entry_t *) directory_entry_data )->class_identifier,
					     16,
					     io_handle->byte_order,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
						 "%s: unable to copy byte stream to GUID.",
						 function );

						goto on_error;
					}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libfguid_identifier_copy_to_utf16_string(
						  guid,
						  (uint16_t *) guid_string,
						  48,
						  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
						  error );
#else
					result = libfguid_identifier_copy_to_utf8_string(
						  guid,
						  (uint8_t *) guid_string,
						  48,
						  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
						  error );
#endif
					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
						 "%s: unable to copy GUID to string.",
						 function );

						goto on_error;
					}
					libcnotify_printf(
					 "%s: directory entry: %03d class identifier\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 directory_entry_index,
					 guid_string );

					if( libfguid_identifier_free(
					     &guid,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
						 "%s: unable to free GUID.",
						 function );

						goto on_error;
					}
					if( io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
					{
						byte_stream_copy_to_uint32_little_endian(
						 ( (olecf_directory_entry_t *) directory_entry_data )->user_flags,
						 value_32bit );
					}
					else if( io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
					{
						byte_stream_copy_to_uint32_big_endian(
						 ( (olecf_directory_entry_t *) directory_entry_data )->user_flags,
						 value_32bit );
					}
					libcnotify_printf(
					 "%s: directory entry: %03d user flags\t\t\t: 0x%08" PRIx32 "\n",
					 function,
					 directory_entry_index,
					 value_32bit );

					if( libfdatetime_filetime_initialize(
					     &filetime,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
						 "%s: unable to create filetime.",
						 function );

						goto on_error;
					}
					if( libfdatetime_filetime_copy_from_byte_stream(
					     filetime,
					     ( (olecf_directory_entry_t *) directory_entry_data )->creation_time,
					     8,
					     io_handle->byte_order,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set creation filetime.",
						 function );

						goto on_error;
					}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libfdatetime_filetime_copy_to_utf16_string(
					          filetime,
					          (uint16_t *) filetime_string,
					          32,
					          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
					          error );
#else
					result = libfdatetime_filetime_copy_to_utf8_string(
					          filetime,
					          (uint8_t *) filetime_string,
					          32,
					          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
					          error );
#endif
					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to create set creation date time string.",
						 function );

						goto on_error;
					}
					libcnotify_printf(
					 "%s: directory entry: %03d creation time\t\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
					 function,
					 directory_entry_index,
					 filetime_string );

					if( libfdatetime_filetime_copy_from_byte_stream(
					     filetime,
					     ( (olecf_directory_entry_t *) directory_entry_data )->modification_time,
					     8,
					     io_handle->byte_order,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set modification filetime.",
						 function );

						goto on_error;
					}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libfdatetime_filetime_copy_to_utf16_string(
					          filetime,
					          (uint16_t *) filetime_string,
					          32,
					          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
					          error );
#else
					result = libfdatetime_filetime_copy_to_utf8_string(
					          filetime,
					          (uint8_t *) filetime_string,
					          32,
					          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
					          error );
#endif
					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to create set modification date time string.",
						 function );

						goto on_error;
					}
					libcnotify_printf(
					 "%s: directory entry: %03d modification time\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
					 function,
					 directory_entry_index,
					 filetime_string );

					if( libfdatetime_filetime_free(
					     &filetime,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
						 "%s: unable to free filetime.",
						 function );

						goto on_error;
					}
					libcnotify_printf(
					 "%s: directory entry: %03d sector identifier\t\t: 0x%08" PRIx32 "\n",
					 function,
					 directory_entry_index,
					 directory_entry->sector_identifier );
					libcnotify_printf(
					 "%s: directory entry: %03d size\t\t\t\t: %" PRIu32 "\n",
					 function,
					 directory_entry_index,
					 directory_entry->size );

					libcnotify_printf(
					 "%s: directory entry: %03d reserved1:\n",
					 function,
					 directory_entry_index );
					libcnotify_print_data(
					 ( (olecf_directory_entry_t *) directory_entry_data )->reserved1,
					 4,
					 0 );
				}
#endif
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

				directory_entry_index++;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			else if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: directory sector entry: %d is empty (type is empty).\n",
				 function,
				 directory_sector_index );
			}
#endif
			directory_entry_data += sizeof( olecf_directory_entry_t );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
		if( directory_sector_identifier >= sat->number_of_sector_identifiers )
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
	memory_free(
	 directory_sector );

	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( name_string != NULL )
	{
		memory_free(
		 name_string );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
#endif
	if( directory_entry != NULL )
	{
		libolecf_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	if( directory_sector != NULL )
	{
		memory_free(
		 directory_sector );
	}
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
		if( sector_identifier >= allocation_table->number_of_sector_identifiers )
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
				if( short_sector_stream_sector_identifier >= sat->number_of_sector_identifiers )
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

		if( sector_identifier >= allocation_table->number_of_sector_identifiers )
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

