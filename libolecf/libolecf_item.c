/*
 * Item functions
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
#include <memory.h>
#include <types.h>

#include "libolecf_definitions.h"
#include "libolecf_directory_entry.h"
#include "libolecf_directory_tree.h"
#include "libolecf_io_handle.h"
#include "libolecf_file.h"
#include "libolecf_item.h"
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"
#include "libolecf_libuna.h"
#include "libolecf_types.h"

/* Creates an item
 * Make sure the value item is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libolecf_item_initialize(
     libolecf_item_t **item,
     libolecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libolecf_internal_file_t *file,
     libcdata_tree_node_t *directory_tree_node,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_item_initialize";

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
	if( *item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid item value already set.",
		 function );

		return( -1 );
	}
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
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( directory_tree_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory tree node.",
		 function );

		return( -1 );
	}
	internal_item = memory_allocate_structure(
	                 libolecf_internal_item_t );

	if( internal_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create internal item.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_item,
	     0,
	     sizeof( libolecf_internal_item_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear internal item.",
		 function );

		goto on_error;
	}
	internal_item->file_io_handle      = file_io_handle;
	internal_item->io_handle           = io_handle;
	internal_item->file                = file;
	internal_item->directory_tree_node = directory_tree_node;

	if( libcdata_tree_node_get_value(
	     directory_tree_node,
	     (intptr_t **) &( internal_item->directory_entry ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value from directory tree node.",
		 function );

		goto on_error;
	}
	*item = (libolecf_item_t *) internal_item;

	return( 1 );

on_error:
	if( internal_item != NULL )
	{
		memory_free(
		 internal_item );
	}
	return( -1 );
}

/* Frees an item
 * Return 1 if successful or -1 on error
 */
int libolecf_item_free(
     libolecf_item_t **item,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_item_free";

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
	if( *item != NULL )
	{
		internal_item = (libolecf_internal_item_t *) *item;
		*item         = NULL;

		memory_free(
		 internal_item );
	}
	return( 1 );
}

/* Retrieves the type
 * Returns 1 if successful or -1 on error
 */
int libolecf_item_get_type(
     libolecf_item_t *item,
     uint8_t *type,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_item_get_type";

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing directory entry.",
		 function );

		return( -1 );
	}
	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	*type = internal_item->directory_entry->type;

	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded name of the referenced item
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libolecf_item_get_utf8_name_size(
     libolecf_item_t *item,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_item_get_utf8_name_size";

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_item->directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing directory entry.",
		 function );

		return( -1 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     internal_item->directory_entry->name,
	     internal_item->directory_entry->name_size,
	     internal_item->io_handle->byte_order,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of name as UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded name of the referenced item
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libolecf_item_get_utf8_name(
     libolecf_item_t *item,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_item_get_utf8_name";

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_item->directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing directory entry.",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_item->directory_entry->name,
	     internal_item->directory_entry->name_size,
	     internal_item->io_handle->byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to opy name to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded name of the referenced item
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libolecf_item_get_utf16_name_size(
     libolecf_item_t *item,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_item_get_utf16_name_size";

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_item->directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing directory entry.",
		 function );

		return( -1 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     internal_item->directory_entry->name,
	     internal_item->directory_entry->name_size,
	     internal_item->io_handle->byte_order,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of name as UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded name of the referenced item
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libolecf_item_get_utf16_name(
     libolecf_item_t *item,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_item_get_utf16_name";

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_item->directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing directory entry.",
		 function );

		return( -1 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_item->directory_entry->name,
	     internal_item->directory_entry->name_size,
	     internal_item->io_handle->byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to opy name to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the referenced item
 * Returns 1 if successful or -1 on error
 */
int libolecf_item_get_size(
     libolecf_item_t *item,
     uint32_t *size,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_item_get_size";

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing directory entry.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	*size = internal_item->directory_entry->size;

	return( 1 );
}

/* Retrieves the creation date and time
 * The returned time is a 64-bit version of a FILETIME value
 * Returns 1 if successful or -1 on error
 */
int libolecf_item_get_creation_time(
     libolecf_item_t *item,
     uint64_t *filetime,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_item_get_creation_time";

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing directory entry.",
		 function );

		return( -1 );
	}
	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	*filetime = internal_item->directory_entry->creation_time;

	return( 1 );
}

/* Retrieves the modification date and time
 * The returned time is a 64-bit version of a FILETIME value
 * Returns 1 if successful or -1 on error
 */
int libolecf_item_get_modification_time(
     libolecf_item_t *item,
     uint64_t *filetime,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_item_get_modification_time";

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing directory entry.",
		 function );

		return( -1 );
	}
	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	*filetime = internal_item->directory_entry->modification_time;

	return( 1 );
}

/* Retrieves the number of sub items from a item
 * Returns 1 if successful or -1 on error
 */
int libolecf_item_get_number_of_sub_items(
     libolecf_item_t *item,
     int *number_of_sub_items,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_item_get_number_of_sub_items";

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
	internal_item = (libolecf_internal_item_t *) item;

	if( libcdata_tree_node_get_number_of_sub_nodes(
	     internal_item->directory_tree_node,
	     number_of_sub_items,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sub items.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the sub item for the specific index from a item
 * Returns 1 if successful or -1 on error
 */
int libolecf_item_get_sub_item(
     libolecf_item_t *item,
     int sub_item_index,
     libolecf_item_t **sub_item,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item       = NULL;
	libcdata_tree_node_t *sub_directory_tree_node = NULL;
	static char *function                         = "libolecf_item_get_sub_item";

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->directory_tree_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing directory tree node.",
		 function );

		return( -1 );
	}
	if( sub_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub item.",
		 function );

		return( -1 );
	}
	if( *sub_item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: sub item already set.",
		 function );

		return( -1 );
	}
	if( libcdata_tree_node_get_sub_node_by_index(
	     internal_item->directory_tree_node,
             sub_item_index,
             &sub_directory_tree_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sub directory tree node: %d.",
		 function,
		 sub_item_index );

		return( -1 );
	}
	if( sub_directory_tree_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid sub directory tree node: %d.",
		 function,
		 sub_item_index );

		return( -1 );
	}
	if( libolecf_item_initialize(
	     sub_item,
	     internal_item->io_handle,
	     internal_item->file_io_handle,
	     internal_item->file,
	     sub_directory_tree_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sub item.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the sub item for the specific UTF-8 encoded name
 * Returns 1 if successful, 0 if no such sub item or -1 on error
 */
int libolecf_item_get_sub_item_by_utf8_name(
     libolecf_item_t *item,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libolecf_item_t **sub_item,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item       = NULL;
	libcdata_tree_node_t *sub_directory_tree_node = NULL;
	static char *function                         = "libolecf_item_get_sub_item_by_utf8_name";
	int result                                    = 0;

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing IO handle.",
		 function );

		return( -1 );
	}
	if( sub_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub item.",
		 function );

		return( -1 );
	}
	if( *sub_item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: sub item already set.",
		 function );

		return( -1 );
	}
	result = libolecf_directory_tree_get_sub_node_by_utf8_name(
	          internal_item->directory_tree_node,
	          utf8_string,
	          utf8_string_length,
	          internal_item->io_handle->byte_order,
	          &sub_directory_tree_node,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve directory tree sub node by UTF-8 name.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( sub_directory_tree_node == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid sub directory tree node.",
			 function );

			return( -1 );
		}
		if( libolecf_item_initialize(
		     sub_item,
		     internal_item->io_handle,
		     internal_item->file_io_handle,
		     internal_item->file,
		     sub_directory_tree_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create sub item.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the sub item for the specific UTF-16 encoded name
 * Returns 1 if successful, 0 if no such sub item or -1 on error
 */
int libolecf_item_get_sub_item_by_utf16_name(
     libolecf_item_t *item,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libolecf_item_t **sub_item,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item       = NULL;
	libcdata_tree_node_t *sub_directory_tree_node = NULL;
	static char *function                         = "libolecf_item_get_sub_item_by_utf16_name";
	int result                                    = 0;

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing IO handle.",
		 function );

		return( -1 );
	}
	if( sub_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub item.",
		 function );

		return( -1 );
	}
	if( *sub_item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: sub item already set.",
		 function );

		return( -1 );
	}
	result = libolecf_directory_tree_get_sub_node_by_utf16_name(
	          internal_item->directory_tree_node,
	          utf16_string,
	          utf16_string_length,
	          internal_item->io_handle->byte_order,
	          &sub_directory_tree_node,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve directory tree sub node by UTF-16 name.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( sub_directory_tree_node == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid sub directory tree node.",
			 function );

			return( -1 );
		}
		if( libolecf_item_initialize(
		     sub_item,
		     internal_item->io_handle,
		     internal_item->file_io_handle,
		     internal_item->file,
		     sub_directory_tree_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create sub item.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the sub item for the specific UTF-8 encoded path
 * The path separator is the \ character
 * Returns 1 if successful, 0 if no such item or -1 on error
 */
int libolecf_item_get_sub_item_by_utf8_path(
     libolecf_item_t *item,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libolecf_item_t **sub_item,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item       = NULL;
	libcdata_tree_node_t *directory_tree_node     = NULL;
	libcdata_tree_node_t *sub_directory_tree_node = NULL;
	uint8_t *utf8_string_segment                  = NULL;
	static char *function                         = "libolecf_item_get_sub_item_by_utf8_path";
	libuna_unicode_character_t unicode_character  = 0;
	size_t utf8_string_index                      = 0;
	size_t utf8_string_segment_length             = 0;
	int result                                    = 0;

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing IO handle.",
		 function );

		return( -1 );
	}
	if( sub_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub item.",
		 function );

		return( -1 );
	}
	if( *sub_item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: sub item already set.",
		 function );

		return( -1 );
	}
	directory_tree_node = internal_item->directory_tree_node;

	if( utf8_string_length > 0 )
	{
		/* Ignore a leading separator
		 */
		if( utf8_string[ utf8_string_index ] == (uint8_t) LIBOLECF_SEPARATOR )
		{
			utf8_string_index++;
		}
	}
	if( ( utf8_string_length == 0 )
	 || ( utf8_string_length == 1 ) )
	{
		result = 1;
	}
	else while( utf8_string_index < utf8_string_length )
	{
		utf8_string_segment        = (uint8_t *) &( utf8_string[ utf8_string_index ] );
		utf8_string_segment_length = utf8_string_index;

		while( utf8_string_index < utf8_string_length )
		{
			if( libuna_unicode_character_copy_from_utf8(
			     &unicode_character,
			     utf8_string,
			     utf8_string_length,
			     &utf8_string_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy UTF-8 string to Unicode character.",
				 function );

				return( -1 );
			}
			if( ( unicode_character == (libuna_unicode_character_t) LIBOLECF_SEPARATOR )
			 || ( unicode_character == 0 ) )
			{
				utf8_string_segment_length += 1;

				break;
			}
		}
		utf8_string_segment_length = utf8_string_index - utf8_string_segment_length;

		if( utf8_string_segment_length == 0 )
		{
			result = 0;
		}
		else
		{
			result = libolecf_directory_tree_get_sub_node_by_utf8_name(
				  directory_tree_node,
				  utf8_string_segment,
				  utf8_string_segment_length,
				  internal_item->io_handle->byte_order,
				  &sub_directory_tree_node,
				  error );
		}
		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve directory tree sub node by UTF-8 name.",
			 function );

			return( -1 );
		}
		else if( result == 0 )
		{
			break;
		}
		directory_tree_node = sub_directory_tree_node;
	}
	if( result != 0 )
	{
		if( libolecf_item_initialize(
		     sub_item,
		     internal_item->io_handle,
		     internal_item->file_io_handle,
		     internal_item->file,
		     directory_tree_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create sub item.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the sub item for the specific UTF-16 encoded path
 * The path separator is the \ character
 * Returns 1 if successful, 0 if no such item or -1 on error
 */
int libolecf_item_get_sub_item_by_utf16_path(
     libolecf_item_t *item,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libolecf_item_t **sub_item,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item       = NULL;
	libcdata_tree_node_t *directory_tree_node     = NULL;
	libcdata_tree_node_t *sub_directory_tree_node = NULL;
	uint16_t *utf16_string_segment                = NULL;
	static char *function                         = "libolecf_item_get_sub_item_by_utf16_path";
	libuna_unicode_character_t unicode_character  = 0;
	size_t utf16_string_index                     = 0;
	size_t utf16_string_segment_length            = 0;
	int result                                    = 0;

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
	internal_item = (libolecf_internal_item_t *) item;

	if( internal_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing IO handle.",
		 function );

		return( -1 );
	}
	if( sub_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub item.",
		 function );

		return( -1 );
	}
	if( *sub_item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: sub item already set.",
		 function );

		return( -1 );
	}
	directory_tree_node = internal_item->directory_tree_node;

	if( utf16_string_length > 0 )
	{
		/* Ignore a leading separator
		 */
		if( utf16_string[ utf16_string_index ] == (uint16_t) LIBOLECF_SEPARATOR )
		{
			utf16_string_index++;
		}
	}
	if( ( utf16_string_length == 0 )
	 || ( utf16_string_length == 1 ) )
	{
		result = 1;
	}
	else while( utf16_string_index < utf16_string_length )
	{
		utf16_string_segment        = (uint16_t *) &( utf16_string[ utf16_string_index ] );
		utf16_string_segment_length = utf16_string_index;

		while( utf16_string_index < utf16_string_length )
		{
			if( libuna_unicode_character_copy_from_utf16(
			     &unicode_character,
			     utf16_string,
			     utf16_string_length,
			     &utf16_string_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy UTF-16 string to Unicode character.",
				 function );

				return( -1 );
			}
			if( ( unicode_character == (libuna_unicode_character_t) LIBOLECF_SEPARATOR )
			 || ( unicode_character == 0 ) )
			{
				utf16_string_segment_length += 1;

				break;
			}
		}
		utf16_string_segment_length = utf16_string_index - utf16_string_segment_length;

		if( utf16_string_segment_length == 0 )
		{
			result = 0;
		}
		else
		{
			result = libolecf_directory_tree_get_sub_node_by_utf16_name(
				  directory_tree_node,
				  utf16_string_segment,
				  utf16_string_segment_length,
				  internal_item->io_handle->byte_order,
				  &sub_directory_tree_node,
				  error );
		}
		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve directory tree sub node by UTF-16 name.",
			 function );

			return( -1 );
		}
		else if( result == 0 )
		{
			break;
		}
		directory_tree_node = sub_directory_tree_node;
	}
	if( result != 0 )
	{
		if( libolecf_item_initialize(
		     sub_item,
		     internal_item->io_handle,
		     internal_item->file_io_handle,
		     internal_item->file,
		     directory_tree_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create sub item.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

