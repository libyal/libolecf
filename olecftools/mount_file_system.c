/*
 * Mount file system
 *
 * Copyright (C) 2008-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_SYS_STAT_H )
#include <sys/stat.h>
#endif

#if defined( TIME_WITH_SYS_TIME )
#include <sys/time.h>
#include <time.h>
#elif defined( HAVE_SYS_TIME_H )
#include <sys/time.h>
#else
#include <time.h>
#endif

#include "mount_file_system.h"
#include "olecftools_libcerror.h"
#include "olecftools_libcpath.h"
#include "olecftools_libolecf.h"

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
	return( 1 );
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
	if( file_system->file != NULL )
	{
		if( libolecf_file_signal_abort(
		     file_system->file,
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
     libolecf_file_t *file,
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
	file_system->file = file;

	return( 1 );
}

/* Retrieves the file
 * Returns 1 if successful or -1 on error
 */
int mount_file_system_get_file(
     mount_file_system_t *file_system,
     libolecf_file_t **file,
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
	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	*file = file_system->file;

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
     libolecf_item_t **item,
     libcerror_error_t **error )
{
	system_character_t *item_path         = NULL;
	static char *function                 = "mount_file_system_get_item_by_path";
	size_t item_path_length               = 0;
	size_t item_path_size                 = 0;
	size_t last_item_path_seperator_index = 0;
	int result                            = 0;

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
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_length == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path length.",
		 function );

		return( -1 );
	}
	if( path_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( path[ 0 ] != LIBCPATH_SEPARATOR )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported path - path is not absolute.",
		 function );

		return( -1 );
	}
	if( mount_file_system_get_item_path(
	     file_system,
	     path,
	     path_length,
	     &item_path,
	     &item_path_size,
	     &last_item_path_seperator_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve item path.",
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
	item_path_length = system_string_length(
	                    item_path );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libolecf_file_get_item_by_utf16_path(
		  file_system->file,
		  (uint16_t *) item_path,
		  item_path_length,
		  item,
		  error );
#else
	result = libolecf_file_get_item_by_utf8_path(
		  file_system->file,
		  (uint8_t *) item_path,
		  item_path_length,
		  item,
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

#if defined( WINAPI )

/* Retrieves the item path
 * Returns 1 if successful or -1 on error
 */
int mount_file_system_get_item_path(
     mount_file_system_t *file_system,
     const system_character_t *path,
     size_t path_length,
     system_character_t **item_path,
     size_t *item_path_size,
     size_t *last_item_path_seperator_index,
     libcerror_error_t **error )
{
	system_character_t *safe_item_path = NULL;
	static char *function              = "mount_file_system_get_item_path";
	system_character_t character_value = 0;
	size_t item_path_index             = 0;
	size_t path_index                  = 0;
	size_t safe_item_path_size         = 0;

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
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( item_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item path.",
		 function );

		return( -1 );
	}
	if( item_path_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item path size.",
		 function );

		return( -1 );
	}
	if( last_item_path_seperator_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid last item path seperator index.",
		 function );

		return( -1 );
	}
	*item_path      = NULL;
	*item_path_size = 0;

	safe_item_path_size = path_length + 1;

	if( safe_item_path_size > (size_t) ( SSIZE_MAX / sizeof( system_character_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid item path size value exceeds maximum.",
		 function );

		goto on_error;
	}
	safe_item_path = system_string_allocate(
	                  safe_item_path_size );

	if( safe_item_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create item path.",
		 function );

		goto on_error;
	}
	item_path_index = 0;
	path_index      = 0;

	while( path_index < path_length )
	{
		character_value = path[ path_index ];

		if( character_value == 0x00 )
		{
			break;
		}
		if( ( item_path_index + 1 ) > safe_item_path_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid item path index value out of bounds.",
			 function );

			goto on_error;
		}
		/* Replace:
		 *   ^^ by ^
		 *   ^x5c by \
		 *   ^x## by values <= 0x1f and 0x7f
		 */
		if( character_value == (system_character_t) '\\' )
		{
			*last_item_path_seperator_index = item_path_index;

			safe_item_path[ item_path_index++ ] = (system_character_t) '\\';
		}
		else if( character_value == (system_character_t) '^' )
		{
			if( ( ( path_index + 1 ) <= path_length )
			 && ( path[ path_index + 1 ] == (system_character_t) '^' ) )
			{
				safe_item_path[ item_path_index++ ] = (system_character_t) '^';

				path_index += 1;
			}
			else if( ( ( path_index + 3 ) <= path_length )
			      && ( path[ path_index + 1 ] == (system_character_t) 'x' ) )
			{
				if( ( path[ path_index + 2 ] >= (system_character_t) '0' )
				 && ( path[ path_index + 2 ] <= (system_character_t) '9' ) )
				{
					character_value = path[ path_index + 2 ] - (system_character_t) '0';
				}
				else if( ( path[ path_index + 2 ] >= (system_character_t) 'a' )
				      && ( path[ path_index + 2 ] <= (system_character_t) 'f' ) )
				{
					character_value = path[ path_index + 2 ] - (system_character_t) 'a' + 10;
				}
				else
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid escaped character value out of bounds.",
					 function );

					goto on_error;
				}
				character_value <<= 4;

				if( ( path[ path_index + 3 ] >= (system_character_t) '0' )
				 && ( path[ path_index + 3 ] <= (system_character_t) '9' ) )
				{
					character_value |= path[ path_index + 3 ] - (system_character_t) '0';
				}
				else if( ( path[ path_index + 3 ] >= (system_character_t) 'a' )
				      && ( path[ path_index + 3 ] <= (system_character_t) 'f' ) )
				{
					character_value |= path[ path_index + 3 ] - (system_character_t) 'a' + 10;
				}
				else
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid escaped character value out of bounds.",
					 function );

					goto on_error;
				}
				if( ( character_value == 0 )
				 || ( ( character_value > 0x1f )
				  &&  ( character_value != 0x5c )
				  &&  ( character_value != 0x7f ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid escaped character value out of bounds.",
					 function );

					goto on_error;
				}
				safe_item_path[ item_path_index++ ] = character_value;

				path_index += 3;
			}
			else
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid escaped character value out of bounds.",
				 function );

				goto on_error;
			}
		}
		else
		{
			safe_item_path[ item_path_index++ ] = character_value;
		}
		path_index++;
	}
	if( item_path_index >= safe_item_path_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid item path index value out of bounds.",
		 function );

		goto on_error;
	}
	safe_item_path[ item_path_index ] = 0;

	*item_path      = safe_item_path;
	*item_path_size = safe_item_path_size;

	return( 1 );

on_error:
	if( safe_item_path != NULL )
	{
		memory_free(
		 safe_item_path );
	}
	return( -1 );
}

#else

/* Retrieves the item path
 * Returns 1 if successful or -1 on error
 */
int mount_file_system_get_item_path(
     mount_file_system_t *file_system,
     const system_character_t *path,
     size_t path_length,
     system_character_t **item_path,
     size_t *item_path_size,
     size_t *last_item_path_seperator_index,
     libcerror_error_t **error )
{
	system_character_t *safe_item_path = NULL;
	static char *function              = "mount_file_system_get_item_path";
	system_character_t character_value = 0;
	size_t item_path_index             = 0;
	size_t path_index                  = 0;
	size_t safe_item_path_size         = 0;

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
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( item_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item path.",
		 function );

		return( -1 );
	}
	if( item_path_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item path size.",
		 function );

		return( -1 );
	}
	if( last_item_path_seperator_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid last item path seperator index.",
		 function );

		return( -1 );
	}
	*item_path      = NULL;
	*item_path_size = 0;

	safe_item_path_size = path_length + 1;

	if( safe_item_path_size > (size_t) ( SSIZE_MAX / sizeof( system_character_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid item path size value exceeds maximum.",
		 function );

		goto on_error;
	}
	safe_item_path = system_string_allocate(
	                  safe_item_path_size );

	if( safe_item_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create item path.",
		 function );

		goto on_error;
	}
	item_path_index = 0;
	path_index      = 0;

	while( path_index < path_length )
	{
		character_value = path[ path_index ];

		if( character_value == 0x00 )
		{
			break;
		}
		if( ( item_path_index + 1 ) > safe_item_path_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid item path index value out of bounds.",
			 function );

			goto on_error;
		}
		/* Replace:
		 *   / by \
		 *   \\ by \
		 *   \x2f by /
		 *   \x## by values <= 0x1f and 0x7f
		 */
		if( character_value == (system_character_t) '/' )
		{
			*last_item_path_seperator_index = item_path_index;

			safe_item_path[ item_path_index++ ] = (system_character_t) '\\';
		}
		else if( character_value == (system_character_t) '\\' )
		{
			if( ( ( path_index + 1 ) <= path_length )
			 && ( path[ path_index + 1 ] == (system_character_t) '\\' ) )
			{
				safe_item_path[ item_path_index++ ] = (system_character_t) '\\';

				path_index += 1;
			}
			else if( ( ( path_index + 3 ) <= path_length )
			      && ( path[ path_index + 1 ] == (system_character_t) 'x' ) )
			{
				if( ( path[ path_index + 2 ] >= (system_character_t) '0' )
				 && ( path[ path_index + 2 ] <= (system_character_t) '9' ) )
				{
					character_value = path[ path_index + 2 ] - (system_character_t) '0';
				}
				else if( ( path[ path_index + 2 ] >= (system_character_t) 'a' )
				      && ( path[ path_index + 2 ] <= (system_character_t) 'f' ) )
				{
					character_value = path[ path_index + 2 ] - (system_character_t) 'a' + 10;
				}
				else
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid escaped character value out of bounds.",
					 function );

					goto on_error;
				}
				character_value <<= 4;

				if( ( path[ path_index + 3 ] >= (system_character_t) '0' )
				 && ( path[ path_index + 3 ] <= (system_character_t) '9' ) )
				{
					character_value |= path[ path_index + 3 ] - (system_character_t) '0';
				}
				else if( ( path[ path_index + 3 ] >= (system_character_t) 'a' )
				      && ( path[ path_index + 3 ] <= (system_character_t) 'f' ) )
				{
					character_value |= path[ path_index + 3 ] - (system_character_t) 'a' + 10;
				}
				else
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid escaped character value out of bounds.",
					 function );

					goto on_error;
				}
				if( ( character_value == 0 )
				 || ( ( character_value > 0x1f )
				  &&  ( character_value != 0x2f )
				  &&  ( character_value != 0x7f ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid escaped character value out of bounds.",
					 function );

					goto on_error;
				}
				safe_item_path[ item_path_index++ ] = character_value;

				path_index += 3;
			}
			else
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid escaped character value out of bounds.",
				 function );

				goto on_error;
			}
		}
		else
		{
			safe_item_path[ item_path_index++ ] = character_value;
		}
		path_index++;
	}
	if( item_path_index >= safe_item_path_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid item path index value out of bounds.",
		 function );

		goto on_error;
	}
	safe_item_path[ item_path_index ] = 0;

	*item_path      = safe_item_path;
	*item_path_size = safe_item_path_size;

	return( 1 );

on_error:
	if( safe_item_path != NULL )
	{
		memory_free(
		 safe_item_path );
	}
	return( -1 );
}

#endif /* defined( WINAPI ) */

#if defined( WINAPI )

/* Retrieves the sanitized filename
 * Returns 1 if successful or -1 on error
 */
int mount_file_system_get_sanitized_filename(
     mount_file_system_t *file_system,
     const system_character_t *item_name,
     size_t item_name_length,
     system_character_t **sanitized_name,
     size_t *sanitized_name_size,
     libcerror_error_t **error )
{
	system_character_t *safe_sanitized_name = NULL;
	static char *function                   = "mount_file_system_get_sanitized_filename";
	system_character_t character_value      = 0;
	system_character_t hex_digit            = 0;
	size_t item_name_index                  = 0;
	size_t safe_sanitized_name_size         = 0;
	size_t sanitized_name_index             = 0;

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
	if( item_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item name.",
		 function );

		return( -1 );
	}
	if( item_name_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid item name length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( sanitized_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sanitized name.",
		 function );

		return( -1 );
	}
	if( sanitized_name_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sanitized name size.",
		 function );

		return( -1 );
	}
	*sanitized_name      = NULL;
	*sanitized_name_size = 0;

	safe_sanitized_name_size = ( item_name_length * 4 ) + 1;

	if( safe_sanitized_name_size > (size_t) ( SSIZE_MAX / sizeof( system_character_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid sanitized name size value exceeds maximum.",
		 function );

		goto on_error;
	}
	safe_sanitized_name = system_string_allocate(
	                       safe_sanitized_name_size );

	if( safe_sanitized_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create sanitized name.",
		 function );

		goto on_error;
	}
	sanitized_name_index = 0;

	for( item_name_index = 0;
	     item_name_index < item_name_length;
	     item_name_index++ )
	{
		character_value = item_name[ item_name_index ];

		if( character_value == 0x00 )
		{
			break;
		}
		/* Replace:
		 *   values <= 0x1f and 0x7f by ^x##
		 *   \ by ^x5c
		 *   ^ by ^^
		 */
		if( ( character_value <= 0x1f )
		 || ( character_value == (system_character_t) '\\' )
		 || ( character_value == 0x7f ) )
		{
			if( ( sanitized_name_index + 4 ) > safe_sanitized_name_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid sanitized name index value out of bounds.",
				 function );

				goto on_error;
			}
			safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) '^';
			safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) 'x';

			hex_digit = character_value >> 4;

			if( hex_digit <= 0x09 )
			{
				safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) '0' + hex_digit;
			}
			else
			{
				safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) 'a' + hex_digit - 10;
			}
			hex_digit = character_value & 0x0f;

			if( hex_digit <= 0x09 )
			{
				safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) '0' + hex_digit;
			}
			else
			{
				safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) 'a' + hex_digit - 10;
			}
		}
		else if( character_value == (system_character_t) '^' )
		{
			if( ( sanitized_name_index + 2 ) > safe_sanitized_name_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid sanitized name index value out of bounds.",
				 function );

				goto on_error;
			}
			safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) '^';
			safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) '^';
		}
		else
		{
			if( ( sanitized_name_index + 1 ) > safe_sanitized_name_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid sanitized name index value out of bounds.",
				 function );

				goto on_error;
			}
			safe_sanitized_name[ sanitized_name_index++ ] = character_value;
		}
	}
	if( sanitized_name_index >= safe_sanitized_name_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sanitized name index value out of bounds.",
		 function );

		goto on_error;
	}
	safe_sanitized_name[ sanitized_name_index ] = 0;

	*sanitized_name      = safe_sanitized_name;
	*sanitized_name_size = safe_sanitized_name_size;

	return( 1 );

on_error:
	if( safe_sanitized_name != NULL )
	{
		memory_free(
		 safe_sanitized_name );
	}
	return( -1 );
}

#else

/* Retrieves the sanitized filename
 * Returns 1 if successful or -1 on error
 */
int mount_file_system_get_sanitized_filename(
     mount_file_system_t *file_system,
     const system_character_t *item_name,
     size_t item_name_length,
     system_character_t **sanitized_name,
     size_t *sanitized_name_size,
     libcerror_error_t **error )
{
	system_character_t *safe_sanitized_name = NULL;
	static char *function                   = "mount_file_system_get_sanitized_filename";
	system_character_t character_value      = 0;
	system_character_t hex_digit            = 0;
	size_t item_name_index                  = 0;
	size_t safe_sanitized_name_size         = 0;
	size_t sanitized_name_index             = 0;

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
	if( item_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item name.",
		 function );

		return( -1 );
	}
	if( item_name_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid item name length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( sanitized_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sanitized name.",
		 function );

		return( -1 );
	}
	if( sanitized_name_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sanitized name size.",
		 function );

		return( -1 );
	}
	*sanitized_name      = NULL;
	*sanitized_name_size = 0;

	safe_sanitized_name_size = ( item_name_length * 4 ) + 1;

	if( safe_sanitized_name_size > (size_t) ( SSIZE_MAX / sizeof( system_character_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid sanitized name size value exceeds maximum.",
		 function );

		goto on_error;
	}
	safe_sanitized_name = system_string_allocate(
	                       safe_sanitized_name_size );

	if( safe_sanitized_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create sanitized name.",
		 function );

		goto on_error;
	}
	sanitized_name_index = 0;

	for( item_name_index = 0;
	     item_name_index < item_name_length;
	     item_name_index++ )
	{
		character_value = item_name[ item_name_index ];

		if( character_value == 0x00 )
		{
			break;
		}
		/* Replace:
		 *   values <= 0x1f and 0x7f by \x##
		 *   / by \x2f
		 *   \ by \\
		 */
		if( ( character_value <= 0x1f )
		 || ( character_value == (system_character_t) '/' )
		 || ( character_value == 0x7f ) )
		{
			if( ( sanitized_name_index + 4 ) > safe_sanitized_name_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid sanitized name index value out of bounds.",
				 function );

				goto on_error;
			}
			safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) '\\';
			safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) 'x';

			hex_digit = character_value >> 4;

			if( hex_digit <= 0x09 )
			{
				safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) '0' + hex_digit;
			}
			else
			{
				safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) 'a' + hex_digit - 10;
			}
			hex_digit = character_value & 0x0f;

			if( hex_digit <= 0x09 )
			{
				safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) '0' + hex_digit;
			}
			else
			{
				safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) 'a' + hex_digit - 10;
			}
		}
		else if( character_value == (system_character_t) '\\' )
		{
			if( ( sanitized_name_index + 2 ) > safe_sanitized_name_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid sanitized name index value out of bounds.",
				 function );

				goto on_error;
			}
			safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) '\\';
			safe_sanitized_name[ sanitized_name_index++ ] = (system_character_t) '\\';
		}
		else
		{
			if( ( sanitized_name_index + 1 ) > safe_sanitized_name_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid sanitized name index value out of bounds.",
				 function );

				goto on_error;
			}
			safe_sanitized_name[ sanitized_name_index++ ] = character_value;
		}
	}
	if( sanitized_name_index >= safe_sanitized_name_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sanitized name index value out of bounds.",
		 function );

		goto on_error;
	}
	safe_sanitized_name[ sanitized_name_index ] = 0;

	*sanitized_name      = safe_sanitized_name;
	*sanitized_name_size = safe_sanitized_name_size;

	return( 1 );

on_error:
	if( safe_sanitized_name != NULL )
	{
		memory_free(
		 safe_sanitized_name );
	}
	return( -1 );
}

#endif /* defined( WINAPI ) */

