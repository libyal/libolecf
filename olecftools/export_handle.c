/*
 * Export handle
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

#include "export_handle.h"
#include "olecftools_libcerror.h"
#include "olecftools_libcfile.h"
#include "olecftools_libclocale.h"
#include "olecftools_libcnotify.h"
#include "olecftools_libcpath.h"
#include "olecftools_libolecf.h"

#define EXPORT_HANDLE_BUFFER_SIZE	32768
#define EXPORT_HANDLE_NOTIFY_STREAM	stdout

/* Creates an export handle
 * Make sure the value export_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int export_handle_initialize(
     export_handle_t **export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_initialize";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( *export_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid export handle value already set.",
		 function );

		return( -1 );
	}
	*export_handle = memory_allocate_structure(
	                  export_handle_t );

	if( *export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create export handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *export_handle,
	     0,
	     sizeof( export_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear export handle.",
		 function );

		goto on_error;
	}
	if( libolecf_file_initialize(
	     &( ( *export_handle )->input_file ),
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
	( *export_handle )->ascii_codepage = LIBOLECF_CODEPAGE_WINDOWS_1252;
	( *export_handle )->notify_stream  = EXPORT_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *export_handle != NULL )
	{
		memory_free(
		 *export_handle );

		*export_handle = NULL;
	}
	return( -1 );
}

/* Frees an export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_free(
     export_handle_t **export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_free";
	int result            = 1;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( *export_handle != NULL )
	{
		if( ( *export_handle )->input_file != NULL )
		{
			if( libolecf_file_free(
			     &( ( *export_handle )->input_file ),
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
		if( ( *export_handle )->target_path != NULL )
		{
			memory_free(
			 ( *export_handle )->target_path );
		}
		if( ( *export_handle )->items_export_path != NULL )
		{
			memory_free(
			 ( *export_handle )->items_export_path );
		}
		memory_free(
		 *export_handle );

		*export_handle = NULL;
	}
	return( result );
}

/* Signals the export handle to abort
 * Returns 1 if successful or -1 on error
 */
int export_handle_signal_abort(
     export_handle_t *export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_signal_abort";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( export_handle->input_file != NULL )
	{
		if( libolecf_file_signal_abort(
		     export_handle->input_file,
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
int export_handle_set_ascii_codepage(
     export_handle_t *export_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function  = "export_handle_set_ascii_codepage";
	size_t string_length   = 0;
	uint32_t feature_flags = 0;
	int result             = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	feature_flags = LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_KOI8
	              | LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS;

	string_length = system_string_length(
	                 string );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libclocale_codepage_copy_from_string_wide(
	          &( export_handle->ascii_codepage ),
	          string,
	          string_length,
	          feature_flags,
	          error );
#else
	result = libclocale_codepage_copy_from_string(
	          &( export_handle->ascii_codepage ),
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

/* Sets the target path
 * Returns 1 if successful or -1 on error
 */
int export_handle_set_target_path(
     export_handle_t *export_handle,
     const system_character_t *target_path,
     libcerror_error_t **error )
{
	static char *function                = "export_handle_set_target_path";
	size_t target_path_length            = 0;

#if defined( WINAPI )
	system_character_t *full_target_path = NULL;
        size_t full_target_path_size         = 0;
	int result                           = 0;
#endif

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( target_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path.",
		 function );

		return( -1 );
	}
	if( export_handle->target_path != NULL )
	{
		memory_free(
		 export_handle->target_path );

		export_handle->target_path      = NULL;
		export_handle->target_path_size = 0;
	}
	target_path_length = system_string_length(
	                      target_path );

#if defined( WINAPI )
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcpath_path_get_full_path_wide(
	          target_path,
	          target_path_length,
	          &full_target_path,
	          &full_target_path_size,
	          error );
#else
	result = libcpath_path_get_full_path(
	          target_path,
	          target_path_length,
	          &full_target_path,
	          &full_target_path_size,
	          error );
#endif
        if( result == -1 )
        {
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create full target path.",
		 function );

		goto on_error;
        }
        else if( result != 0 )
        {
                target_path        = full_target_path;
                target_path_length = full_target_path_size - 1;
        }
#endif
	if( target_path_length > 0 )
	{
		export_handle->target_path = system_string_allocate(
		                              target_path_length + 1 );

		if( export_handle->target_path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create target path.",
			 function );

			goto on_error;
		}
		if( system_string_copy(
		     export_handle->target_path,
		     target_path,
		     target_path_length ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy target path.",
			 function );

			goto on_error;
		}
		( export_handle->target_path )[ target_path_length ] = 0;

		export_handle->target_path_size = target_path_length + 1;
	}
#if defined( WINAPI )
	memory_free(
	 full_target_path );

	full_target_path = NULL;
#endif
	return( 1 );

on_error:
#if defined( WINAPI )
	if( full_target_path != NULL )
	{
		memory_free(
		 full_target_path );
	}
#endif
	if( export_handle->target_path != NULL )
	{
		memory_free(
		 export_handle->target_path );

		export_handle->target_path = NULL;
	}
	export_handle->target_path_size = 0;

	return( -1 );
}

/* Sets an export path consisting of a base path and a suffix
 * Returns 1 if successful or -1 on error
 */
int export_handle_set_export_path(
     export_handle_t *export_handle,
     const system_character_t *base_path,
     size_t base_path_length,
     const system_character_t *suffix,
     size_t suffix_length,
     system_character_t **export_path,
     size_t *export_path_size,
     libcerror_error_t **error )
{
	static char *function = "export_handle_set_export_path";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( base_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base path.",
		 function );

		return( -1 );
	}
	if( base_path_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base path length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( suffix == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid suffix.",
		 function );

		return( -1 );
	}
	if( suffix_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid suffix length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( export_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path.",
		 function );

		return( -1 );
	}
	if( export_path_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path size.",
		 function );

		return( -1 );
	}
	if( *export_path != NULL )
	{
		memory_free(
		 *export_path );

		*export_path      = NULL;
		*export_path_size = 0;
	}
	*export_path_size = base_path_length + suffix_length + 1;

	*export_path = system_string_allocate(
	                *export_path_size );

	if( *export_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create export path.",
		 function );

		goto on_error;
	}
	if( system_string_copy(
	     *export_path,
	     base_path,
	     base_path_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy base path to item export path.",
		 function );

		goto on_error;
	}
	if( system_string_copy(
	     &( ( *export_path )[ base_path_length ] ),
	     suffix,
	     suffix_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy suffix to item export path.",
		 function );

		goto on_error;
	}
	( *export_path )[ *export_path_size - 1 ] = 0;

	return( 1 );

on_error:
	if( *export_path != NULL )
	{
		memory_free(
		 *export_path );

		*export_path      = NULL;
		*export_path_size = 0;
	}
	return( -1 );
}

/* Creates the items export path
 * Returns 1 if successful, 0 if already exists or -1 on error
 */
int export_handle_create_items_export_path(
     export_handle_t *export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_create_items_export_path";
	int result            = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( export_handle_set_export_path(
	     export_handle,
	     export_handle->target_path,
	     export_handle->target_path_size - 1,
	     _SYSTEM_STRING( ".export" ),
	     7,
	     &( export_handle->items_export_path ),
	     &( export_handle->items_export_path_size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set items export path.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcfile_file_exists_wide(
		  export_handle->items_export_path,
		  error );
#else
	result = libcfile_file_exists(
		  export_handle->items_export_path,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_SYSTEM " exists.",
		 function,
		 export_handle->items_export_path );

		return( -1 );
	}
	else if( result == 1 )
	{
		return( 0 );
	}
	return( 1 );
}

/* Opens the input of the export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_open_input(
     export_handle_t *export_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "export_handle_open_input";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libolecf_file_open_wide(
	     export_handle->input_file,
	     filename,
	     LIBOLECF_OPEN_READ,
	     error ) != 1 )
#else
	if( libolecf_file_open(
	     export_handle->input_file,
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

/* Closes the export handle
 * Returns the 0 if succesful or -1 on error
 */
int export_handle_close(
     export_handle_t *export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_close";
	int result            = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( libolecf_file_close(
	     export_handle->input_file,
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

/* Exports the item
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_item(
     export_handle_t *export_handle,
     libolecf_item_t *item,
     int item_index,
     int number_of_items,
     const system_character_t *export_path,
     size_t export_path_length,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	libcfile_file_t *stream_data_file  = NULL;
	system_character_t *item_name      = NULL;
	system_character_t *item_path      = NULL;
	system_character_t *sanitized_name = NULL;
	system_character_t *target_path    = NULL;
	uint8_t *buffer                    = NULL;
	static char *function              = "export_handle_export_item";
	size_t buffer_size                 = EXPORT_HANDLE_BUFFER_SIZE;
	size_t item_name_size              = 0;
	size_t item_path_size              = 0;
	size_t minimum_item_name_size      = 0;
	size_t read_size                   = 0;
	size_t sanitized_name_size         = 0;
	size_t target_path_size            = 0;
	ssize_t read_count                 = 0;
	ssize_t write_count                = 0;
	uint32_t stream_data_size          = 0;
	int print_count                    = 0;
	int result                         = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
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
	if( export_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path.",
		 function );

		return( -1 );
	}
	log_handle_printf(
	 log_handle,
	 "Processing item: %05d in path: %" PRIs_SYSTEM "%c\n",
	 item_index,
	 export_path,
	 LIBCPATH_SEPARATOR );

	/* Create the storage or stream directory
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libolecf_item_get_utf16_name_size(
	          item,
	          &item_name_size,
	          error );
#else
	result = libolecf_item_get_utf8_name_size(
	          item,
	          &item_name_size,
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
	minimum_item_name_size = item_name_size;

	if( minimum_item_name_size < 10 )
	{
		minimum_item_name_size = 10;
	}
	item_name = system_string_allocate(
	             minimum_item_name_size );

	if( item_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create the item name.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libolecf_item_get_utf16_name(
	          item,
	          (uint16_t *) item_name,
	          item_name_size,
	          error );
#else
	result = libolecf_item_get_utf8_name(
	          item,
	          (uint8_t *) item_name,
	          item_name_size,
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libcpath_path_get_sanitized_filename_wide(
	     item_name,
	     item_name_size - 1,
	     &sanitized_name,
	     &sanitized_name_size,
	     error ) != 1 )
#else
	if( libcpath_path_get_sanitized_filename(
	     item_name,
	     item_name_size - 1,
	     &sanitized_name,
	     &sanitized_name_size,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to sanitize item name.",
		 function );

		goto on_error;
	}
	memory_free(
	 item_name );

	item_name           = sanitized_name;
	item_name_size      = sanitized_name_size;
	sanitized_name      = NULL;
	sanitized_name_size = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcpath_path_join_wide(
	          &item_path,
	          &item_path_size,
	          export_path,
	          export_path_length,
	          item_name,
	          item_name_size - 1,
	          error );
#else
	result = libcpath_path_join(
	          &item_path,
	          &item_path_size,
	          export_path,
	          export_path_length,
	          item_name,
	          item_name_size - 1,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create item path.",
		 function );

		goto on_error;
	}
	if( item_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item path.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcfile_file_exists_wide(
	          item_path,
	          error );
#else
	result = libcfile_file_exists(
	          item_path,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_SYSTEM " exists.",
		 function,
		 item_path );

		goto on_error;
	}
	else if( result == 1 )
	{
		memory_free(
		 item_path );

		item_path = NULL;

		print_count = system_string_sprintf(
		               item_name,
		               10,
		               _SYSTEM_STRING( "Item%05d" ),
		               item_index + 1 );

		if( ( print_count < 0 )
		 || ( print_count > 12 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set item name.",
			 function );

			goto on_error;
		}
		item_name[ 9 ] = 0;
		item_name_size = 10;

		log_handle_printf(
		 log_handle,
		 "Item already exists defaulting to: %" PRIs_SYSTEM "\n",
		 item_name );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libcpath_path_join_wide(
			  &item_path,
			  &item_path_size,
			  export_path,
			  export_path_length,
			  item_name,
			  item_name_size - 1,
			  error );
#else
		result = libcpath_path_join(
			  &item_path,
			  &item_path_size,
			  export_path,
			  export_path_length,
			  item_name,
			  item_name_size - 1,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create item path.",
			 function );

			goto on_error;
		}
		if( item_path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid item path.",
			 function );

			goto on_error;
		}
	}
	memory_free(
	 item_name );

	item_name = NULL;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcpath_path_make_directory_wide(
	          item_path,
	          error );
#else
	result = libcpath_path_make_directory(
	          item_path,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to make directory: %" PRIs_SYSTEM ".",
		 function,
		 item_path );

		goto on_error;
	}
	log_handle_printf(
	 log_handle,
	 "Created directory: %" PRIs_SYSTEM ".\n",
	 item_path );

	/* Create the item file
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcpath_path_join_wide(
	          &target_path,
	          &target_path_size,
	          item_path,
	          item_path_size - 1,
	          L"StreamData.bin",
	          14,
	          error );
#else
	result = libcpath_path_join(
	          &target_path,
	          &target_path_size,
	          item_path,
	          item_path_size - 1,
	          "StreamData.bin",
	          14,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create target path.",
		 function );

		goto on_error;
	}
	if( target_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcfile_file_exists_wide(
	          target_path,
	          error );
#else
	result = libcfile_file_exists(
	          target_path,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_SYSTEM " exists.",
		 function,
		 target_path );

		goto on_error;
	}
	else if( result != 0 )
	{
		log_handle_printf(
		 log_handle,
		 "Skipping item: %" PRIs_SYSTEM " it already exists.\n",
		 target_path );

		memory_free(
		 target_path );
		memory_free(
		 item_path );

		return( 1 );
	}
	if( libolecf_item_get_size(
	     item,
	     &stream_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve item stream data size.",
		 function );

		goto on_error;
	}
	if( libcfile_file_initialize(
	     &stream_data_file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create stream data file.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcfile_file_open_wide(
		  stream_data_file,
		  target_path,
		  LIBCFILE_OPEN_WRITE,
		  error );
#else
	result = libcfile_file_open(
		  stream_data_file,
		  target_path,
		  LIBCFILE_OPEN_WRITE,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open: %" PRIs_SYSTEM ".",
		 function,
		 target_path );

		goto on_error;
	}
	memory_free(
	 target_path );

	target_path = NULL;

	if( stream_data_size > 0 )
	{
		buffer = (uint8_t *) memory_allocate(
		                      sizeof( uint8_t ) * buffer_size );

		if( buffer == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create the buffer.",
			 function );

			goto on_error;
		}
		while( stream_data_size > 0 )
		{
			read_size = buffer_size;

			if( read_size > stream_data_size )
			{
				read_size = stream_data_size;
			}
			read_count = libolecf_stream_read_buffer(
			              item,
			              buffer,
			              read_size,
			              error );

			if( read_count != (ssize_t) read_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read stream data from item.",
				 function );

				goto on_error;
			}
			stream_data_size -= read_size;

			write_count = libcfile_file_write_buffer(
			               stream_data_file,
			               buffer,
			               read_size,
			               error );

			if( write_count != (ssize_t) read_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_WRITE_FAILED,
				 "%s: unable to write stream data to file.",
				 function );

				goto on_error;
			}
		}
		memory_free(
		 buffer );

		buffer = NULL;
	}
	if( libcfile_file_close(
	     stream_data_file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to stream data file.",
		 function );

		goto on_error;
	}
	if( libcfile_file_free(
	     &stream_data_file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free stream data file.",
		 function );

		goto on_error;
	}
	/* Export the sub items
	 */
	if( export_handle_export_sub_items(
	     export_handle,
	     item,
	     item_path,
	     item_path_size - 1,
	     log_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_OUTPUT,
		 LIBCERROR_OUTPUT_ERROR_GENERIC,
		 "%s: unable to export sub items.",
		 function );

		goto on_error;
	}
	memory_free(
	 item_path );

	item_path = NULL;

	return( 1 );

on_error:
	if( buffer != NULL )
	{
		memory_free(
		 buffer );
	}
	if( stream_data_file != NULL )
	{
		libcfile_file_free(
		 &stream_data_file,
		 NULL );
	}
	if( target_path != NULL )
	{
		memory_free(
		 target_path );
	}
	if( item_path != NULL )
	{
		memory_free(
		 item_path );
	}
	if( sanitized_name != NULL )
	{
		memory_free(
		 sanitized_name );
	}
	if( item_name != NULL )
	{
		memory_free(
		 item_name );
	}
	return( -1 );
}

/* Exports the sub items
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_sub_items(
     export_handle_t *export_handle,
     libolecf_item_t *item,
     const system_character_t *export_path,
     size_t export_path_length,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	libolecf_item_t *sub_item = NULL;
	static char *function     = "export_handle_export_sub_items";
	int number_of_sub_items   = 0;
	int sub_item_iterator     = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
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
	if( export_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path.",
		 function );

		return( -1 );
	}
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

		return( -1 );
	}
	for( sub_item_iterator = 0;
	     sub_item_iterator < number_of_sub_items;
	     sub_item_iterator++ )
	{
		if( libolecf_item_get_sub_item(
		     item,
		     sub_item_iterator,
		     &sub_item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve sub item: %d.",
			 function,
			 sub_item_iterator + 1 );

			return( -1 );
		}
		if( export_handle_export_item(
		     export_handle,
		     sub_item,
		     sub_item_iterator,
		     number_of_sub_items,
		     export_path,
		     export_path_length,
		     log_handle,
		     error ) != 1 )
		{
			fprintf(
			 stdout,
			 "Unable to export item %d out of %d.\n",
			 sub_item_iterator + 1,
			 number_of_sub_items );

			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: unable to export sub item: %d.\n",
				 function,
				 sub_item_iterator + 1 );
			}
			if( ( error != NULL )
			 && ( *error != NULL ) )
			{
				libcnotify_print_error_backtrace(
				 *error );
			}
			libcerror_error_free(
			 error );

			log_handle_printf(
			 log_handle,
			 "Unable to export sub item: %d.\n",
			 sub_item_iterator + 1 );
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
			 sub_item_iterator + 1 );

			return( -1 );
		}
	}
	return( 1 );
}

/* Exports the file
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_file(
     export_handle_t *export_handle,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	libolecf_item_t *root_item = NULL;
	static char *function      = "export_handle_export_file";
	int result                 = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 export_handle->notify_stream,
	 "Exporting items.\n" );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcpath_path_make_directory_wide(
	          export_handle->items_export_path,
	          error );
#else
	result = libcpath_path_make_directory(
	          export_handle->items_export_path,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to create directory: %" PRIs_SYSTEM "",
		 function,
		 export_handle->items_export_path );

		goto on_error;
	}
	log_handle_printf(
	 log_handle,
	 "Created directory: %" PRIs_SYSTEM ".\n",
	 export_handle->items_export_path );

	result = libolecf_file_get_root_item(
	          export_handle->input_file,
	          &root_item,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve root item.",
		 function );

		goto on_error;
	}
	else if( result == 0 )
	{
		return( 1 );
	}
	if( export_handle_export_sub_items(
	     export_handle,
	     root_item,
	     export_handle->items_export_path,
	     export_handle->items_export_path_size - 1,
	     log_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_OUTPUT,
		 LIBCERROR_OUTPUT_ERROR_GENERIC,
		 "%s: unable to export root item.",
		 function );

		goto on_error;
	}
	if( libolecf_item_free(
	     &root_item,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free root item.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( root_item != NULL )
	{
		libolecf_item_free(
		 &root_item,
		 NULL );
	}
	return( -1 );
}

