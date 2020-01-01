/*
 * Info handle
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
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "info_handle.h"
#include "olecftools_libcerror.h"
#include "olecftools_libclocale.h"
#include "olecftools_libfdatetime.h"
#include "olecftools_libfguid.h"
#include "olecftools_libfole.h"
#include "olecftools_libolecf.h"
#include "olecftools_libuna.h"

#define INFO_HANDLE_NOTIFY_STREAM	stdout

uint8_t info_handle_class_identifier_summary_information[ 16 ] = {
        0xe0, 0x85, 0x9f, 0xf2, 0xf9, 0x4f, 0x68, 0x10, 0xab, 0x91, 0x08, 0x00, 0x2b, 0x27, 0xb3, 0xd9 };

uint8_t info_handle_class_identifier_document_summary_information[ 16 ] = {
        0x02, 0xd5, 0xcd, 0xd5, 0x9c, 0x2e, 0x1b, 0x10, 0x93, 0x97, 0x08, 0x00, 0x2b, 0x2c, 0xf9, 0xae };

/* Creates an info handle
 * Make sure the value info_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid info handle value already set.",
		 function );

		return( -1 );
	}
	*info_handle = memory_allocate_structure(
	                info_handle_t );

	if( *info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create info handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *info_handle,
	     0,
	     sizeof( info_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear info handle.",
		 function );

		goto on_error;
	}
	if( libolecf_file_initialize(
	     &( ( *info_handle )->input_file ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input file.",
		 function );

		goto on_error;
	}
	( *info_handle )->notify_stream = INFO_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *info_handle != NULL )
	{
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( -1 );
}

/* Frees an info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( ( *info_handle )->input_file != NULL )
		{
			if( libolecf_file_free(
			     &( ( *info_handle )->input_file ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free input file.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( result );
}

/* Signals the info handle to abort
 * Returns 1 if successful or -1 on error
 */
int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_file != NULL )
	{
		if( libolecf_file_signal_abort(
		     info_handle->input_file,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input file to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the ascii codepage
 * Returns 1 if successful or -1 on error
 */
int info_handle_set_ascii_codepage(
     info_handle_t *info_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function  = "info_handle_set_ascii_codepage";
	size_t string_length   = 0;
	uint32_t feature_flags = 0;
	int result             = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	feature_flags = LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_KOI8
	              | LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS;

	string_length = system_string_length(
	                 string );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libclocale_codepage_copy_from_string_wide(
	          &( info_handle->ascii_codepage ),
	          string,
	          string_length,
	          feature_flags,
	          error );
#else
	result = libclocale_codepage_copy_from_string(
	          &( info_handle->ascii_codepage ),
	          string,
	          string_length,
	          feature_flags,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine ASCII codepage.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Opens the input of the info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "info_handle_open_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libolecf_file_open_wide(
	     info_handle->input_file,
	     filename,
	     LIBOLECF_OPEN_READ,
	     error ) != 1 )
#else
	if( libolecf_file_open(
	     info_handle->input_file,
	     filename,
	     LIBOLECF_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input file.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes the info handle
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_close";
	int result            = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->root_item != NULL )
	{
		if( libolecf_item_free(
		     &( info_handle->root_item ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free root item.",
			 function );

			result = -1;
		}
	}
	if( libolecf_file_close(
	     info_handle->input_file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Prints the file information to a stream
 * Returns 1 if successful or -1 on error
 */
int info_handle_file_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function      = "info_handle_file_fprint";
	size32_t sector_size       = 0;
	size32_t short_sector_size = 0;
	uint16_t major_version     = 0;
	uint16_t minor_version     = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libolecf_file_get_format_version(
	     info_handle->input_file,
	     &major_version,
	     &minor_version,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve format version.",
		 function );

		return( -1 );
	}
	if( libolecf_file_get_sector_size(
	     info_handle->input_file,
	     &sector_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sector size.",
		 function );

		return( -1 );
	}
	if( libolecf_file_get_short_sector_size(
	     info_handle->input_file,
	     &short_sector_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve short sector size.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "OLE Compound File information:\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tVersion\t\t\t: %" PRIu16 ".%" PRIu16 "\n",
	 major_version,
	 minor_version );

	fprintf(
	 info_handle->notify_stream,
	 "\tSector size\t\t: %" PRIu32 "\n",
	 sector_size );

	fprintf(
	 info_handle->notify_stream,
	 "\tShort sector size\t: %" PRIu32 "\n",
	 short_sector_size );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );
}

/* Prints the items to a stream
 * Returns 1 if successful or -1 on error
 */
int info_handle_items_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_items_fprint";
	int result            = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->root_item == NULL )
	{
		result = libolecf_file_get_root_item(
		          info_handle->input_file,
		          &( info_handle->root_item ),
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve root item.",
			 function );

			return( -1 );
		}
	}
	if( info_handle->root_item == NULL )
	{
		fprintf(
		 info_handle->notify_stream,
		 "No storage and stream items\n" );
	}
	else
	{
		fprintf(
		 info_handle->notify_stream,
		 "Storage and stream items:\n" );

		if( info_handle_item_fprint(
		     info_handle,
		     info_handle->root_item,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print root item.",
			 function );

			return( -1 );
		}
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );
}

/* Prints an item to a stream
 * Returns 1 if successful or -1 on error
 */
int info_handle_item_fprint(
     info_handle_t *info_handle,
     libolecf_item_t *item,
     int indentation_level,
     libcerror_error_t **error )
{
	libolecf_item_t *sub_item = NULL;
	system_character_t *name  = NULL;
	static char *function     = "info_handle_item_fprint";
	size_t name_index         = 0;
	size_t name_size          = 0;
	uint32_t size             = 0;
	int indentation_iterator  = 0;
	int number_of_sub_items   = 0;
	int result                = 0;
	int sub_item_index        = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libolecf_item_get_utf16_name_size(
	          item,
	          &name_size,
	          error );
#else
	result = libolecf_item_get_utf8_name_size(
	          item,
	          &name_size,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve item name size.",
		 function );

		goto on_error;
	}
	name = system_string_allocate(
	        name_size );

	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create name.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libolecf_item_get_utf16_name(
	          item,
	          (uint16_t *) name,
	          name_size,
	          error );
#else
	result = libolecf_item_get_utf8_name(
	          item,
	          (uint8_t *) name,
	          name_size,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve item name.",
		 function );

		goto on_error;
	}
	if( libolecf_item_get_size(
	     item,
	     &size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve item size.",
		 function );

		goto on_error;
	}
	for( indentation_iterator = 0;
	     indentation_iterator < indentation_level;
	     indentation_iterator++ )
	{
		fprintf(
		 info_handle->notify_stream,
		 "  " );
	}
	for( name_index = 0;
	     name_index < ( name_size - 1 );
	     name_index++ )
	{
		/* Print control characters as hexadecimal values
		 */
		if( ( name[ name_index ] < 0x20 )
		 || ( name[ name_index ] == 0x7f ) )
		{
			fprintf(
			 info_handle->notify_stream,
			 "\\x%02" PRIx8 "",
			 (uint8_t) name[ name_index ] );
		}
		else
		{
			fprintf(
			 info_handle->notify_stream,
			 "%" PRIc_SYSTEM "",
			 name[ name_index ] );
		}
	}
	fprintf(
	 info_handle->notify_stream,
	 " (%" PRIu32 " bytes)\n",
	 size );

	memory_free(
	 name );

	name = NULL;

	if( libolecf_item_get_number_of_sub_items(
	     item,
	     &number_of_sub_items,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sub items.",
		 function );

		goto on_error;
	}
	for( sub_item_index = 0;
	     sub_item_index < number_of_sub_items;
	     sub_item_index++ )
	{
		if( libolecf_item_get_sub_item(
		     item,
		     sub_item_index,
		     &sub_item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve sub item: %d.",
			 function,
			 sub_item_index );

			goto on_error;
		}
		if( info_handle_item_fprint(
		     info_handle,
		     sub_item,
		     indentation_level + 1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print sub item: %d.",
			 function,
			 sub_item_index );

			libolecf_item_free(
			 &sub_item,
			 NULL );

			goto on_error;
		}
		if( libolecf_item_free(
		     &sub_item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free sub item: %d.",
			 function,
			 sub_item_index );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( name != NULL )
	{
		memory_free(
		 name );
	}
	return( -1 );
}

/* Prints the unallocaated blocks to a stream
 * Returns 1 if successful or -1 on error
 */
int info_handle_unallocated_blocks_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function            = "info_handle_unallocated_blocks_fprint";
	off64_t offset                   = 0;
	size64_t size                    = 0;
	int block_index                  = 0;
	int number_of_unallocated_blocks = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libolecf_file_get_number_of_unallocated_blocks(
	     info_handle->input_file,
	     &number_of_unallocated_blocks,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of unallocated blocks.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Unallocated blocks:\n" );

	for( block_index = 0;
	     block_index < number_of_unallocated_blocks;
	     block_index++ )
	{
		if( libolecf_file_get_unallocated_block(
		     info_handle->input_file,
		     block_index,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve unallocated block: %d.",
			 function,
			 block_index );

			return( -1 );
		}
		fprintf(
		 info_handle->notify_stream,
		 "\t%08" PRIi64 " (0x%08" PRIx64 ") - %08" PRIi64 " (0x%08" PRIx64 ") size: %" PRIu64 "\n",
		 offset,
		 offset,
		 offset + (off64_t) size,
		 offset + (off64_t) size,
		 size );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );
}

/* Prints the compound object data to a stream
 * Returns 1 if successful or -1 on error
 */
int info_handle_compound_object_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_compound_object_fprint";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Compound object:\n" );

#if defined( TODO )
	/* TODO find the corresponding item */

	/* TODO move this into separate info handle functions */
	if( ( name_size == 9 )
	 && ( memory_compare(
	       "\001CompObj",
	       name,
	       8 ) == 0 ) )
	{
		/* TODO implement means to retrieve compound object
		 */
		if( libolecf_compound_object_stream_read(
		     item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read compound object stream.",
			 function );

			goto on_error;
		}
	}
	/* TODO print the data*/
#endif
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );
}

/* Prints the property value
 * Returns 1 if successful or -1 on error
 */
int info_handle_property_value_fprint(
     info_handle_t *info_handle,
     const uint8_t *class_identifier,
     libolecf_property_value_t *property_value,
     libcerror_error_t **error )
{
	system_character_t date_time_string[ 48 ];

	libfdatetime_filetime_t *filetime            = NULL;
	system_character_t *value_string             = NULL;
	static char *function                        = "info_handle_property_value_fprint";
	const char *property_value_identifier_string = NULL;
	size_t value_string_size                     = 0;
	uint64_t value_64bit                         = 0;
	uint32_t property_value_identifier           = 0;
	uint32_t property_value_type                 = 0;
	uint32_t value_32bit                         = 0;
	uint16_t value_16bit                         = 0;
	uint8_t value_boolean                        = 0;
	int result                                   = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libolecf_property_value_get_identifier(
	     property_value,
	     &property_value_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to identifier.",
		 function );

		goto on_error;
	}
	if( libolecf_property_value_get_value_type(
	     property_value,
	     &property_value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to value type.",
		 function );

		goto on_error;
	}
	property_value_identifier_string = NULL;

	if( memory_compare(
	     class_identifier,
	     info_handle_class_identifier_document_summary_information,
	     16 ) == 0 )
	{
		switch( property_value_type )
		{
			case LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED:
				switch( property_value_identifier )
				{
					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_CODEPAGE:
						property_value_identifier_string = "PIDDSI_CODEPAGE";
						break;

					default:
						break;
				}
				break;

			case LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED:
				switch( property_value_identifier )
				{
					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_BYTE_COUNT:
						property_value_identifier_string = "PIDDSI_BYTECOUNT";
						break;

					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_LINE_COUNT:
						property_value_identifier_string = "PIDDSI_LINECOUNT";
						break;

					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_PARAGRAPH_COUNT:
						property_value_identifier_string = "PIDDSI_PARCOUNT";
						break;

					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_SLIDE_COUNT:
						property_value_identifier_string = "PIDDSI_SLIDECOUNT";
						break;

					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_NOTE_COUNT:
						property_value_identifier_string = "PIDDSI_NOTECOUNT";
						break;

					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_HIDDEN_SLIDE_COUNT:
						property_value_identifier_string = "PIDDSI_HIDDENCOUNT";
						break;

					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_MMCLIP_COUNT:
						property_value_identifier_string = "PIDDSI_MMCLIPCOUNT";
						break;

					default:
						break;
				}
				break;

			case LIBOLECF_VALUE_TYPE_BOOLEAN:
				switch( property_value_identifier )
				{
					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_SCALE:
						property_value_identifier_string = "PIDDSI_SCALE";
						break;

					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_LINKS_DIRTY:
						property_value_identifier_string = "PIDDSI_LINKSDIRTY";
						break;

					default:
						break;
				}
				break;

			case LIBOLECF_VALUE_TYPE_STRING_ASCII:
			case LIBOLECF_VALUE_TYPE_STRING_UNICODE:
				switch( property_value_identifier )
				{
					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_CATEGORY	:
						property_value_identifier_string = "PIDDSI_CATEGORY";
						break;

					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_PRESENTATION_TARGET:
						property_value_identifier_string = "PIDDSI_PRESFORMAT";
						break;

					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_MANAGER:
						property_value_identifier_string = "PIDDSI_MANAGER";
						break;

					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_COMPANY:
						property_value_identifier_string = "PIDDSI_COMPANY";
						break;

					default:
						break;
				}
				break;

			case LIBOLECF_VALUE_TYPE_MULTI_VALUE_VARIANT:
				switch( property_value_identifier )
				{
					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_HEADING_PAIRS:
						property_value_identifier_string = "PIDDSI_HEADINGPAIR";
						break;

					default:
						break;
				}
				break;

			case LIBOLECF_VALUE_TYPE_MULTI_VALUE_STRING_ASCII:
			case LIBOLECF_VALUE_TYPE_MULTI_VALUE_STRING_UNICODE:
				switch( property_value_identifier )
				{
					case LIBOLECF_DOCUMENT_SUMMARY_INFORMATION_PID_DOCUMENT_PARTS:
						property_value_identifier_string = "PIDDSI_DOCPARTS";
						break;

					default:
						break;
				}
				break;

			default:
				break;
		}
	}
	else if( memory_compare(
	          class_identifier,
	          info_handle_class_identifier_summary_information,
	          16 ) == 0 )
	{
		switch( property_value_type )
		{
			case LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED:
				switch( property_value_identifier )
				{
					case LIBOLECF_SUMMARY_INFORMATION_PID_CODEPAGE:
						property_value_identifier_string = "PIDSI_CODEPAGE";
						break;

					default:
						break;
				}
				break;

			case LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED:
				switch( property_value_identifier )
				{
					case LIBOLECF_SUMMARY_INFORMATION_PID_NUMBER_OF_PAGES:
						property_value_identifier_string = "PIDSI_PAGECOUNT";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_NUMBER_OF_WORDS:
						property_value_identifier_string = "PIDSI_WORDCOUNT";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_NUMBER_OF_CHARACTERS:
						property_value_identifier_string = "PIDSI_CHARCOUNT";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_SECURITY:
						property_value_identifier_string = "PIDSI_SECURITY";
						break;

					default:
						break;
				}
				break;

			case LIBOLECF_VALUE_TYPE_STRING_ASCII:
			case LIBOLECF_VALUE_TYPE_STRING_UNICODE:
				switch( property_value_identifier )
				{
					case LIBOLECF_SUMMARY_INFORMATION_PID_TITLE:
						property_value_identifier_string = "PIDSI_TITLE";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_SUBJECT:
						property_value_identifier_string = "PIDSI_SUBJECT";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_AUTHOR:
						property_value_identifier_string = "PIDSI_AUTHOR";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_KEYWORDS:
						property_value_identifier_string = "PIDSI_KEYWORDS";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_COMMENTS:
						property_value_identifier_string = "PIDSI_COMMENTS";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_TEMPLATE:
						property_value_identifier_string = "PIDSI_TEMPLATE";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_LAST_SAVED_BY:
						property_value_identifier_string = "PIDSI_LASTAUTHOR";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_REVISION_NUMBER:
						property_value_identifier_string = "PIDSI_REVNUMBER";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_APPLICATION_NAME:
						property_value_identifier_string = "PIDSI_APPNAME";
						break;

					default:
						break;
				}
				break;

			case LIBOLECF_VALUE_TYPE_FILETIME:
				switch( property_value_identifier )
				{
					case LIBOLECF_SUMMARY_INFORMATION_PID_EDITING_TIME:
						property_value_identifier_string = "PIDSI_EDITTIME";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_LAST_PRINTED_TIME:
						property_value_identifier_string = "PIDSI_LASTPRINTED";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_CREATION_TIME:
						property_value_identifier_string = "PIDSI_CREATE_DTM";
						break;

					case LIBOLECF_SUMMARY_INFORMATION_PID_LAST_WRITTEN_TIME:
						property_value_identifier_string = "PIDSI_LASTSAVE_DTM";
						break;

					default:
						break;
				}
				break;

			case LIBOLECF_VALUE_TYPE_CLIPBOARD_FORMAT:
				switch( property_value_identifier )
				{
					case LIBOLECF_SUMMARY_INFORMATION_PID_THUMBNAIL:
						property_value_identifier_string = "PIDSI_THUMBNAIL";
						break;

					default:
						break;
				}
				break;

			default:
				break;
		}
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tValue identifier\t: " );

	if( property_value_identifier_string != NULL )
	{
		fprintf(
		 info_handle->notify_stream,
		 "%s (",
		 property_value_identifier_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "0x%08" PRIx32 "",
	 property_value_identifier );

	if( property_value_identifier_string != NULL )
	{
		fprintf(
		 info_handle->notify_stream,
		 ")" );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tValue type\t\t: %s (0x%08" PRIx32 ")\n",
	 libfole_value_type_get_identifier(
	  property_value_type ),
	 property_value_type );

	switch( property_value_type )
	{
		case LIBOLECF_VALUE_TYPE_BOOLEAN:
			if( libolecf_property_value_get_data_as_boolean(
			     property_value,
			     &value_boolean,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve boolean value.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tValue data\t\t: %s\n",
			 (value_boolean != 0) ? "true" : "false" );

			break;

		case LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_16BIT_UNSIGNED:
			if( libolecf_property_value_get_data_as_16bit_integer(
			     property_value,
			     &value_16bit,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve 16-bit integer value.",
				 function );

				goto on_error;
			}
			if( property_value_type == LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED )
			{
				fprintf(
				 info_handle->notify_stream,
				 "\tValue data\t\t: %" PRIi16 "\n",
				 (int16_t) value_16bit );
			}
			else
			{
				fprintf(
				 info_handle->notify_stream,
				 "\tValue data\t\t: %" PRIu16 "\n",
				 value_16bit );
			}
			break;

		case LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_32BIT_UNSIGNED:
			if( libolecf_property_value_get_data_as_32bit_integer(
			     property_value,
			     &value_32bit,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve 32-bit integer value.",
				 function );

				goto on_error;
			}
			if( property_value_type == LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED )
			{
				fprintf(
				 info_handle->notify_stream,
				 "\tValue data\t\t: %" PRIi32 "\n",
				 (int32_t) value_32bit );
			}
			else
			{
				fprintf(
				 info_handle->notify_stream,
				 "\tValue data\t\t: %" PRIu32 "\n",
				 value_32bit );
			}
			break;

		case LIBOLECF_VALUE_TYPE_INTEGER_64BIT_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_64BIT_UNSIGNED:
			if( libolecf_property_value_get_data_as_64bit_integer(
			     property_value,
			     &value_64bit,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve 64-bit integer value.",
				 function );

				goto on_error;
			}
			if( property_value_type == LIBOLECF_VALUE_TYPE_INTEGER_64BIT_SIGNED )
			{
				fprintf(
				 info_handle->notify_stream,
				 "\tValue data\t\t: %" PRIi64 "\n",
				 (int64_t) value_64bit );
			}
			else
			{
				fprintf(
				 info_handle->notify_stream,
				 "\tValue data\t\t: %" PRIu64 "\n",
				 value_64bit );
			}
			break;

		case LIBOLECF_VALUE_TYPE_STRING_ASCII:
		case LIBOLECF_VALUE_TYPE_STRING_UNICODE:
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libolecf_property_value_get_data_as_utf16_string_size(
			          property_value,
			          &value_string_size,
			          error );
#else
			result = libolecf_property_value_get_data_as_utf8_string_size(
			          property_value,
			          &value_string_size,
			          error );
#endif
			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve string value size.",
				 function );

				goto on_error;
			}
			else if( result != 0 )
			{
				if( ( value_string_size > (size_t) SSIZE_MAX )
				 || ( ( sizeof( system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
					 "%s: invalid string value size value exceeds maximum.",
					 function );

					goto on_error;
				}
				value_string = system_string_allocate(
				                value_string_size );

				if( value_string == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create string.",
					 function );

					goto on_error;
				}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libolecf_property_value_get_data_as_utf16_string(
				          property_value,
				          (uint16_t *) value_string,
				          value_string_size,
				          error );
#else
				result = libolecf_property_value_get_data_as_utf8_string(
				          property_value,
				          (uint8_t *) value_string,
				          value_string_size,
				          error );
#endif
				if( result == -1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve string value.",
					 function );

					goto on_error;
				}
				fprintf(
				 info_handle->notify_stream,
				 "\tValue data\t\t: %" PRIs_SYSTEM "\n",
				 value_string );

				memory_free(
				 value_string );

				value_string = NULL;
			}
			break;

		case LIBOLECF_VALUE_TYPE_FILETIME:
			if( libolecf_property_value_get_data_as_filetime(
			     property_value,
			     &value_64bit,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to FILETIME value.",
				 function );

				goto on_error;
			}
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
			if( libfdatetime_filetime_copy_from_64bit(
			     filetime,
			     value_64bit,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy 64-bit value to filetime.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libfdatetime_filetime_copy_to_utf16_string(
				  filetime,
				  (uint16_t *) date_time_string,
				  48,
				  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
				  error );
#else
			result = libfdatetime_filetime_copy_to_utf8_string(
				  filetime,
				  (uint8_t *) date_time_string,
				  48,
				  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy filetime to string.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tValue data\t\t: %" PRIs_SYSTEM " UTC\n",
			 date_time_string );

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
			break;

		case LIBOLECF_VALUE_TYPE_CLIPBOARD_FORMAT:
		default:
/* TODO print as data */
			break;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the property section
 * Returns 1 if successful or -1 on error
 */
int info_handle_property_section_fprint(
     info_handle_t *info_handle,
     libolecf_property_section_t *property_section,
     libcerror_error_t **error )
{
	system_character_t guid_string[ 48 ];
	uint8_t guid_data[ 16 ];

	libfguid_identifier_t *guid               = NULL;
	libolecf_property_value_t *property_value = NULL;
	static char *function                     = "info_handle_property_section_fprint";
	int number_of_properties                  = 0;
	int property_value_index                  = 0;
	int result                                = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
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
	if( libolecf_property_section_get_class_identifier(
	     property_section,
	     guid_data,
	     16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve property section class identifier.",
		 function );

		goto on_error;
	}
	if( libfguid_identifier_copy_from_byte_stream(
	     guid,
	     guid_data,
	     16,
	     LIBFGUID_ENDIAN_LITTLE,
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
	fprintf(
	 info_handle->notify_stream,
	 "\tClass identifier\t: %" PRIs_SYSTEM "\n",
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
	if( libolecf_property_section_get_number_of_properties(
	     property_section,
	     &number_of_properties,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of properties.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tNumber of properties\t: %d\n",
	 number_of_properties );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	for( property_value_index = 0;
	     property_value_index < number_of_properties;
	     property_value_index++ )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tProperty: %d\n",
		 property_value_index + 1 );

		if( libolecf_property_section_get_property_by_index(
		     property_section,
		     property_value_index,
		     &property_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve property value: %d.",
			 function,
			 property_value_index );

			goto on_error;
		}
		if( info_handle_property_value_fprint(
		     info_handle,
		     guid_data,
		     property_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print property value: %d.",
			 function,
			 property_value_index );

			goto on_error;
		}
		if( libolecf_property_value_free(
		     &property_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free property value: %d.",
			 function,
			 property_value_index );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( property_value != NULL )
	{
		libolecf_property_value_free(
		 &property_value,
		 NULL );
	}
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	return( -1 );
}

/* Prints the property set
 * Returns 1 if successful or -1 on error
 */
int info_handle_property_set_fprint(
     info_handle_t *info_handle,
     libolecf_property_set_t *property_set,
     libcerror_error_t **error )
{
	system_character_t guid_string[ 48 ];
	uint8_t guid_data[ 16 ];

	libfguid_identifier_t *guid                   = NULL;
	libolecf_property_section_t *property_section = NULL;
	static char *function                         = "info_handle_property_set_fprint";
	int number_of_sections                        = 0;
	int result                                    = 0;
	int section_index                             = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
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
	if( libolecf_property_set_get_class_identifier(
	     property_set,
	     guid_data,
	     16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve property set class identifier.",
		 function );

		goto on_error;
	}
	if( libfguid_identifier_copy_from_byte_stream(
	     guid,
	     guid_data,
	     16,
	     LIBFGUID_ENDIAN_LITTLE,
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
	fprintf(
	 info_handle->notify_stream,
	 "\tClass identifier\t: %" PRIs_SYSTEM "\n",
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
	if( libolecf_property_set_get_number_of_sections(
	     property_set,
	     &number_of_sections,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sections.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tNumber of sections\t: %d\n",
	 number_of_sections );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	for( section_index = 0;
	     section_index < number_of_sections;
	     section_index++ )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tSection: %d\n",
		 section_index + 1 );

		if( libolecf_property_set_get_section_by_index(
		     property_set,
		     section_index,
		     &property_section,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve property set section: %d.",
			 function,
			 section_index );

			goto on_error;
		}
		if( info_handle_property_section_fprint(
		     info_handle,
		     property_section,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print property section: %d.",
			 function,
			 section_index );

			goto on_error;
		}
		if( libolecf_property_section_free(
		     &property_section,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free property section.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( property_section != NULL )
	{
		libolecf_property_section_free(
		 &property_section,
		 NULL );
	}
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	return( -1 );
}

/* Prints the property set stream
 * Returns 1 if successful or -1 on error
 */
int info_handle_property_set_stream_fprint(
     info_handle_t *info_handle,
     libolecf_item_t *property_set_stream,
     libcerror_error_t **error )
{
	libolecf_property_set_t *property_set = NULL;
	static char *function                 = "info_handle_property_set_stream_fprint";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libolecf_property_set_stream_get_set(
	     property_set_stream,
	     &property_set,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve property set stream.",
		 function );

		goto on_error;
	}
	if( info_handle_property_set_fprint(
	     info_handle,
	     property_set,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print property set.",
		 function );

		goto on_error;
	}
	if( libolecf_property_set_free(
	     &property_set,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free property set.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( property_set != NULL )
	{
		libolecf_property_set_free(
		 &property_set,
		 NULL );
	}
	return( -1 );
}

/* Prints the document summary information to a stream
 * Returns 1 if successful or -1 on error
 */
int info_handle_document_summary_information_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libolecf_item_t *property_set_stream = NULL;
	static char *function                = "info_handle_document_summary_information_fprint";
	int result                           = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->root_item == NULL )
	{
		result = libolecf_file_get_root_item(
		          info_handle->input_file,
		          &( info_handle->root_item ),
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve root item.",
			 function );

			return( -1 );
		}
		else if( result == 0 )
		{
			return( 1 );
		}
	}
	/* Using \005 because \x05 also absorbes the D
	 */
	result = libolecf_item_get_sub_item_by_utf8_name(
	          info_handle->root_item,
	          (uint8_t *) "\005DocumentSummaryInformation",
	          27,
	          &property_set_stream,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sub item.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Document summary information:\n" );

		if( info_handle_property_set_stream_fprint(
		     info_handle,
		     property_set_stream,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print property set stream.",
			 function );

			goto on_error;
		}
		if( libolecf_item_free(
		     &property_set_stream,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free property set stream.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( property_set_stream != NULL )
	{
		libolecf_item_free(
		 &property_set_stream,
		 NULL );
	}
	return( -1 );
}

/* Prints the summary information to a stream
 * Returns 1 if successful or -1 on error
 */
int info_handle_summary_information_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libolecf_item_t *property_set_stream = NULL;
	static char *function                = "info_handle_summary_information_fprint";
	int result                           = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->root_item == NULL )
	{
		result = libolecf_file_get_root_item(
		          info_handle->input_file,
		          &( info_handle->root_item ),
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve root item.",
			 function );

			return( -1 );
		}
		else if( result == 0 )
		{
			return( 1 );
		}
	}
	result = libolecf_item_get_sub_item_by_utf8_name(
	          info_handle->root_item,
	          (uint8_t *) "\005SummaryInformation",
	          19,
	          &property_set_stream,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sub item.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Summary information:\n" );

		if( info_handle_property_set_stream_fprint(
		     info_handle,
		     property_set_stream,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print property set stream.",
			 function );

			goto on_error;
		}
		if( libolecf_item_free(
		     &property_set_stream,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free property set stream.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( property_set_stream != NULL )
	{
		libolecf_item_free(
		 &property_set_stream,
		 NULL );
	}
	return( -1 );
}

