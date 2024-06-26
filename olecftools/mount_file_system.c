/*
 * Mount file system
 *
 * Copyright (C) 2008-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_SYS_STAT_H )
#include <sys/stat.h>
#endif

#if defined( HAVE_SYS_TIME_H )
#include <sys/time.h>
#endif

#include <time.h>

#include "mount_file_system.h"
#include "mount_path_string.h"
#include "olecftools_libcerror.h"
#include "olecftools_libcpath.h"
#include "olecftools_libolecf.h"
#include "olecftools_libuna.h"

/* Creates a file system
 * Make sure the value file_system is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int mount_file_system_initialize(
     mount_file_system_t **file_system,
     libcerror_error_t **error )
{
#if defined( WINAPI )
	FILETIME filetime;
	SYSTEMTIME systemtime;

#elif defined( HAVE_CLOCK_GETTIME )
	struct timespec time_structure;
#endif

	static char *function = "mount_file_system_initialize";

#if defined( WINAPI )
	DWORD error_code      = 0;
#else
	int64_t timestamp     = 0;
#endif

	if( file_system == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file system.",
		 function );

		return( -1 );
	}
	if( *file_system != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file system value already set.",
		 function );

		return( -1 );
	}
	*file_system = memory_allocate_structure(
	                mount_file_system_t );

	if( *file_system == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file system.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_system,
	     0,
	     sizeof( mount_file_system_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file system.",
		 function );

		memory_free(
		 *file_system );

		*file_system = NULL;

		return( -1 );
	}
#if defined( WINAPI )
	if( memory_set(
	     &systemtime,
	     0,
	     sizeof( SYSTEMTIME ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear systemtime.",
		 function );

		goto on_error;
	}
	GetSystemTime(
	 &systemtime );

	if( SystemTimeToFileTime(
	     &systemtime,
	     &filetime ) == 0 )
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 error_code,
		 "%s: unable to retrieve FILETIME of current time.",
		 function );

		goto on_error;
	}
	( *file_system )->mounted_timestamp = ( (uint64_t) filetime.dwHighDateTime << 32 ) | filetime.dwLowDateTime;

#elif defined( HAVE_CLOCK_GETTIME )
	if( clock_gettime(
	     CLOCK_REALTIME,
	     &time_structure ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve current time structure.",
		 function );

		goto on_error;
	}
	timestamp = ( (int64_t) time_structure.tv_sec * 1000000000 ) + time_structure.tv_nsec;

	( *file_system )->mounted_timestamp = (uint64_t) timestamp;

#else
	timestamp = (int64_t) time( NULL );

	if( timestamp == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve current time.",
		 function );

		goto on_error;
	}
	timestamp *= 1000000000;

	( *file_system )->mounted_timestamp = (uint64_t) timestamp;

#endif /* defined( HAVE_CLOCK_GETTIME ) */

	return( 1 );

on_error:
	if( *file_system != NULL )
	{
		memory_free(
		 *file_system );

		*file_system = NULL;
	}
	return( -1 );
}

/* Frees a file system
 * Returns 1 if successful or -1 on error
 */
int mount_file_system_free(
     mount_file_system_t **file_system,
     libcerror_error_t **error )
{
	static char *function = "mount_file_system_free";
	int result            = 1;

	if( file_system == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file system.",
		 function );

		return( -1 );
	}
	if( *file_system != NULL )
	{
		memory_free(
		 *file_system );

		*file_system = NULL;
	}
	return( result );
}

/* Signals the mount file system to abort
 * Returns 1 if successful or -1 on error
 */
int mount_file_system_signal_abort(
     mount_file_system_t *file_system,
     libcerror_error_t **error )
{
	static char *function = "mount_file_system_signal_abort";

	if( file_system == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file system.",
		 function );

		return( -1 );
	}
	if( file_system->olecf_file != NULL )
	{
		if( libolecf_file_signal_abort(
		     file_system->olecf_file,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal file to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the file
 * Returns 1 if successful or -1 on error
 */
int mount_file_system_set_file(
     mount_file_system_t *file_system,
     libolecf_file_t *olecf_file,
     libcerror_error_t **error )
{
	static char *function = "mount_file_system_set_file";

	if( file_system == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file system.",
		 function );

		return( -1 );
	}
	file_system->olecf_file = olecf_file;

	return( 1 );
}

/* Retrieves the file
 * Returns 1 if successful or -1 on error
 */
int mount_file_system_get_file(
     mount_file_system_t *file_system,
     libolecf_file_t **olecf_file,
     libcerror_error_t **error )
{
	static char *function = "mount_file_system_get_file";

	if( file_system == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file system.",
		 function );

		return( -1 );
	}
	if( olecf_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	*olecf_file = file_system->olecf_file;

	return( 1 );
}

/* Retrieves the mounted timestamp
 * On Windows the timestamp is an unsigned 64-bit FILETIME timestamp
 * otherwise the timestamp is a signed 64-bit POSIX date and time value in number of nanoseconds
 * Returns 1 if successful or -1 on error
 */
int mount_file_system_get_mounted_timestamp(
     mount_file_system_t *file_system,
     uint64_t *mounted_timestamp,
     libcerror_error_t **error )
{
	static char *function = "mount_file_system_get_mounted_timestamp";

	if( file_system == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file system.",
		 function );

		return( -1 );
	}
	if( mounted_timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid mounted timestamp.",
		 function );

		return( -1 );
	}
	*mounted_timestamp = file_system->mounted_timestamp;

	return( 1 );
}

/* Retrieves the item of a specific path
 * Returns 1 if successful, 0 if no such item or -1 on error
 */
int mount_file_system_get_item_by_path(
     mount_file_system_t *file_system,
     const system_character_t *path,
     size_t path_length,
     libolecf_item_t **olecf_item,
     libcerror_error_t **error )
{
	system_character_t *item_path = NULL;
	static char *function         = "mount_file_system_get_item_by_path";
	size_t item_path_length       = 0;
	size_t item_path_size         = 0;
	int result                    = 0;

	if( file_system == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file system.",
		 function );

		return( -1 );
	}
	if( mount_path_string_copy_to_item_path(
	     path,
	     path_length,
	     &item_path,
	     &item_path_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy path to item path.",
		 function );

		goto on_error;
	}
	if( item_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing item path.",
		 function );

		goto on_error;
	}
	/* Need to determine length here since size is based on the worst case
	 */
	item_path_length = system_string_length(
	                    item_path );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libolecf_file_get_item_by_utf16_path(
	          file_system->olecf_file,
	          (uint16_t *) item_path,
	          item_path_length,
	          olecf_item,
	          error );
#else
	result = libolecf_file_get_item_by_utf8_path(
	          file_system->olecf_file,
	          (uint8_t *) item_path,
	          item_path_length,
	          olecf_item,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve item ",
		 function );

		goto on_error;
	}
	memory_free(
	 item_path );

	return( result );

on_error:
	if( item_path != NULL )
	{
		memory_free(
		 item_path );
	}
	return( -1 );
}

/* Retrieves the filename from an item
 * Returns 1 if successful or -1 on error
 */
int mount_file_system_get_filename_from_item(
     mount_file_system_t *file_system,
     libolecf_item_t *olecf_item,
     system_character_t **filename,
     size_t *filename_size,
     libcerror_error_t **error )
{
	system_character_t *item_name = NULL;
	static char *function         = "mount_file_system_get_filename_from_item";
	size_t item_name_size         = 0;
	int result                    = 0;

	if( file_system == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file system.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libolecf_item_get_utf16_name_size(
	          olecf_item,
	          &item_name_size,
	          error );
#else
	result = libolecf_item_get_utf8_name_size(
	          olecf_item,
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
	if( ( item_name_size == 0 )
	 || ( item_name_size > SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid item name size value out of bounds.",
		 function );

		goto on_error;
	}
	item_name = system_string_allocate(
	             item_name_size );

	if( item_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create item name string.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libolecf_item_get_utf16_name(
	          olecf_item,
	          (uint16_t *) item_name,
	          item_name_size,
	          error );
#else
	result = libolecf_item_get_utf8_name(
	          olecf_item,
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
	if( mount_path_string_copy_from_item_path(
	     filename,
	     filename_size,
	     item_name,
	     item_name_size - 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy filename from the item name.",
		 function );

		goto on_error;
	}
	memory_free(
	 item_name );

	return( 1 );

on_error:
	if( item_name != NULL )
	{
		memory_free(
		 item_name );
	}
	return( -1 );
}

