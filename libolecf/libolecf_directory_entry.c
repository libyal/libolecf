/*
 * The directory entry functions
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

#include "libolecf_debug.h"
#include "libolecf_definitions.h"
#include "libolecf_directory_entry.h"
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"
#include "libolecf_libcnotify.h"
#include "libolecf_libfdatetime.h"
#include "libolecf_libfguid.h"
#include "libolecf_libuna.h"

#include "olecf_directory.h"

/* Creates a directory entry
 * Make sure the value directoyry_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libolecf_directory_entry_initialize(
     libolecf_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	static char *function = "libolecf_directory_entry_initialize";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory_entry.",
		 function );

		return( -1 );
	}
	if( *directory_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory entry value already set.",
		 function );

		return( -1 );
	}
	*directory_entry = memory_allocate_structure(
	                    libolecf_directory_entry_t );

	if( *directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create directory entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *directory_entry,
	     0,
	     sizeof( libolecf_directory_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear directory entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *directory_entry != NULL )
	{
		memory_free(
		 *directory_entry );

		*directory_entry = NULL;
	}
	return( -1 );
}

/* Frees a directory entry
 * Returns 1 if successful or -1 on error
 */
int libolecf_directory_entry_free(
     libolecf_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	static char *function = "libolecf_directory_entry_free";

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
	if( *directory_entry != NULL )
	{
		if( ( *directory_entry )->name != NULL )
		{
			memory_free(
			 ( *directory_entry )->name );
		}
		memory_free(
		 *directory_entry );

		*directory_entry = NULL;
	}
	return( 1 );
}

/* Frees a directory entry that is not part of the directory tree
 * Returns 1 if successful or -1 on error
 */
int libolecf_directory_entry_free_not_in_tree(
     libolecf_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	static char *function = "libolecf_directory_entry_free_not_in_tree";

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
	if( ( *directory_entry != NULL )
	 && ( ( *directory_entry )->set_in_tree == 0 ) )
	{
		if( ( *directory_entry )->name != NULL )
		{
			memory_free(
			 ( *directory_entry )->name );
		}
		memory_free(
		 *directory_entry );

		*directory_entry = NULL;
	}
	return( 1 );
}

/* Compares two directory entries
 * Returns LIBCDATA_COMPARE_LESS, LIBCDATA_COMPARE_EQUAL, LIBCDATA_COMPARE_GREATER if successful or -1 on error
 */
int libolecf_directory_entry_compare(
     libolecf_directory_entry_t *first_directory_entry,
     libolecf_directory_entry_t *second_directory_entry,
     libcerror_error_t **error )
{
	static char *function = "libolecf_directory_entry_compare";

	if( first_directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first directory entry.",
		 function );

		return( -1 );
	}
	if( second_directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid second directory entry.",
		 function );

		return( -1 );
	}
	if( first_directory_entry->directory_identifier < second_directory_entry->directory_identifier )
	{
		return( LIBCDATA_COMPARE_LESS );
	}
	if( first_directory_entry->directory_identifier > second_directory_entry->directory_identifier )
	{
		return( LIBCDATA_COMPARE_GREATER );
	}
	return( LIBCDATA_COMPARE_EQUAL );
}

/* Reads a directory entry
 * Returns 1 if successful, 0 if empty or -1 on error
 */
int libolecf_directory_entry_read_data(
     libolecf_directory_entry_t *directory_entry,
     int directory_entry_index,
     const uint8_t *data,
     size_t data_size,
     uint8_t byte_order,
     libcerror_error_t **error )
{
	static char *function   = "libolecf_directory_entry_read_data";
	uint16_t name_data_size = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

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
	if( ( data_size < sizeof( olecf_directory_entry_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBOLECF_ENDIAN_BIG )
	 && ( byte_order != LIBOLECF_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	directory_entry->type = ( (olecf_directory_entry_t *) data )->type;

/* TODO use memory compare */
	if( directory_entry->type == LIBOLECF_ITEM_TYPE_EMPTY )
	{
		return( 0 );
	}
	if( byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint16_little_endian(
		 ( (olecf_directory_entry_t *) data )->name_data_size,
		 name_data_size );
	}
	else if( byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint16_big_endian(
		 ( (olecf_directory_entry_t *) data )->name_data_size,
		 name_data_size );
	}
	if( name_data_size > 0 )
	{
		if( (size_t) name_data_size > sizeof( olecf_directory_entry_t ) )
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
		                                     sizeof( uint8_t ) * name_data_size );

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
		     ( (olecf_directory_entry_t *) data )->name,
		     name_data_size ) == NULL )
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
	directory_entry->directory_identifier = (uint32_t) directory_entry_index;
	directory_entry->name_size            = (size_t) name_data_size;

	if( byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_directory_entry_t *) data )->previous_directory_identifier,
		 directory_entry->previous_directory_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_directory_entry_t *) data )->next_directory_identifier,
		 directory_entry->next_directory_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_directory_entry_t *) data )->sub_directory_identifier,
		 directory_entry->sub_directory_identifier );

		byte_stream_copy_to_uint64_little_endian(
		 ( (olecf_directory_entry_t *) data )->creation_time,
		 directory_entry->creation_time );

		byte_stream_copy_to_uint64_little_endian(
		 ( (olecf_directory_entry_t *) data )->modification_time,
		 directory_entry->modification_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_directory_entry_t *) data )->sector_identifier,
		 directory_entry->sector_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_directory_entry_t *) data )->size,
		 directory_entry->size );
	}
	else if( byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_directory_entry_t *) data )->previous_directory_identifier,
		 directory_entry->previous_directory_identifier );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_directory_entry_t *) data )->next_directory_identifier,
		 directory_entry->next_directory_identifier );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_directory_entry_t *) data )->sub_directory_identifier,
		 directory_entry->sub_directory_identifier );

		byte_stream_copy_to_uint64_big_endian(
		 ( (olecf_directory_entry_t *) data )->creation_time,
		 directory_entry->creation_time );

		byte_stream_copy_to_uint64_big_endian(
		 ( (olecf_directory_entry_t *) data )->modification_time,
		 directory_entry->modification_time );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_directory_entry_t *) data )->sector_identifier,
		 directory_entry->sector_identifier );

		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_directory_entry_t *) data )->size,
		 directory_entry->size );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: identifier\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 directory_entry->directory_identifier );

		if( libolecf_debug_print_utf16_string_value(
		     function,
		     "name\t\t\t\t",
		     directory_entry->name,
		     directory_entry->name_size,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print UTF-16 string value.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "\n" );

		libcnotify_printf(
		 "%s: name data size\t\t\t: %" PRIu16 "\n",
		 function,
		 name_data_size );

		libcnotify_printf(
		 "%s: type\t\t\t\t: 0x%02" PRIx8 " (%s)\n",
		 function,
		 directory_entry->type,
		 libolecf_debug_print_item_type(
		  directory_entry->type ) );

		libcnotify_printf(
		 "%s: node color\t\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 ( (olecf_directory_entry_t *) data )->node_color );

		libcnotify_printf(
		 "%s: previous directory identifier\t: 0x%08" PRIx32 "\n",
		 function,
		 directory_entry->previous_directory_identifier );

		libcnotify_printf(
		 "%s: next directory identifier\t\t: 0x%08" PRIx32 "\n",
		 function,
		 directory_entry->next_directory_identifier );

		libcnotify_printf(
		 "%s: sub directory identifier\t\t: 0x%08" PRIx32 "\n",
		 function,
		 directory_entry->sub_directory_identifier );

		if( libolecf_debug_print_guid_value(
		     function,
		     "class identifier\t\t\t",
		     ( (olecf_directory_entry_t *) data )->class_identifier,
		     16,
		     byte_order,
		     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			goto on_error;
		}
		if( byte_order == LIBOLECF_ENDIAN_LITTLE )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (olecf_directory_entry_t *) data )->user_flags,
			 value_32bit );
		}
		else if( byte_order == LIBOLECF_ENDIAN_BIG )
		{
			byte_stream_copy_to_uint32_big_endian(
			 ( (olecf_directory_entry_t *) data )->user_flags,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: user flags\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( libolecf_debug_print_filetime_value(
		     function,
		     "directory entry creation time\t",
		     ( (olecf_directory_entry_t *) data )->creation_time,
		     8,
		     byte_order,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print filetime value.",
			 function );

			goto on_error;
		}
		if( libolecf_debug_print_filetime_value(
		     function,
		     "directory entry modification time\t",
		     ( (olecf_directory_entry_t *) data )->modification_time,
		     8,
		     byte_order,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print filetime value.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: sector identifier\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 directory_entry->sector_identifier );
		libcnotify_printf(
		 "%s: size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 directory_entry->size );

		libcnotify_printf(
		 "%s: reserved1:\n",
		 function );
		libcnotify_print_data(
		 ( (olecf_directory_entry_t *) data )->reserved1,
		 4,
		 0 );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );

on_error:
	if( directory_entry->name != NULL )
	{
		memory_free(
		 directory_entry->name );

		directory_entry->name = NULL;
	}
	directory_entry->name_size = 0;

	return( -1 );
}

