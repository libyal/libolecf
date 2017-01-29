/*
 * File functions
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
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include "libolecf_codepage.h"
#include "libolecf_debug.h"
#include "libolecf_definitions.h"
#include "libolecf_directory_entry.h"
#include "libolecf_directory_tree.h"
#include "libolecf_file.h"
#include "libolecf_item.h"
#include "libolecf_io_handle.h"
#include "libolecf_libbfio.h"
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"
#include "libolecf_libcnotify.h"
#include "libolecf_libuna.h"
#include "libolecf_types.h"

/* Creates a file
 * Make sure the value file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_initialize(
     libolecf_file_t **file,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_initialize";

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
	if( *file != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file value already set.",
		 function );

		return( -1 );
	}
	internal_file = memory_allocate_structure(
	                 libolecf_internal_file_t );

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_file,
	     0,
	     sizeof( libolecf_internal_file_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	if( libolecf_io_handle_initialize(
	     &( internal_file->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	*file = (libolecf_file_t *) internal_file;

	return( 1 );

on_error:
	if( internal_file != NULL )
	{
		memory_free(
		 internal_file );
	}
	return( -1 );
}

/* Frees a file
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_free(
     libolecf_file_t **file,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_free";
	int result                              = 1;

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
	if( *file != NULL )
	{
		internal_file = (libolecf_internal_file_t *) *file;

		if( internal_file->file_io_handle != NULL )
		{
			if( libolecf_file_close(
			     *file,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close file.",
				 function );

				result = -1;
			}
		}
		*file = NULL;

		if( internal_file->io_handle != NULL )
		{
			if( libolecf_io_handle_free(
			     &( internal_file->io_handle ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free IO handle.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 internal_file );
	}
	return( result );
}

/* Signals the file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_signal_abort(
     libolecf_file_t *file,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_signal_abort";

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
	internal_file = (libolecf_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_file->io_handle->abort = 1;

	return( 1 );
}

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_open(
     libolecf_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle        = NULL;
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_open";
	size_t filename_length                  = 0;

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
	internal_file = (libolecf_internal_file_t *) file;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	filename_length = narrow_string_length(
	                   filename );

	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libolecf_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %s.",
		 function,
		 filename );

		goto on_error;
	}
	internal_file->file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_open_wide(
     libolecf_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle        = NULL;
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_open_wide";
	size_t filename_length                  = 0;

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
	internal_file = (libolecf_internal_file_t *) file;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	filename_length = wide_string_length(
	                   filename );

	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libolecf_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %ls.",
		 function,
		 filename );

		goto on_error;
	}
	internal_file->file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_open_file_io_handle(
     libolecf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_open_file_io_handle";
	int bfio_access_flags                   = 0;
	int file_io_handle_is_open              = 0;

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
	internal_file = (libolecf_internal_file_t *) file;

	if( internal_file->file_io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - file IO handle already set.",
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
	if( ( ( access_flags & LIBOLECF_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBOLECF_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBOLECF_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBOLECF_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		internal_file->file_io_handle_opened_in_library = 1;
	}
	if( libolecf_file_open_read(
	     internal_file,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file handle.",
		 function );

		goto on_error;
	}
	internal_file->file_io_handle = file_io_handle;

	return( 1 );

on_error:
	if( ( file_io_handle_is_open == 0 )
	 && ( internal_file->file_io_handle_opened_in_library != 0 ) )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );

		internal_file->file_io_handle_opened_in_library = 0;
	}
	internal_file->file_io_handle = NULL;

	return( -1 );
}

/* Closes a file
 * Returns 0 if successful or -1 on error
 */
int libolecf_file_close(
     libolecf_file_t *file,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_close";
	int result                              = 0;

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
	internal_file = (libolecf_internal_file_t *) file;

	if( internal_file->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_file->file_io_handle_created_in_library != 0 )
		{
			if( libolecf_debug_print_read_offsets(
			     internal_file->file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );

				result = -1;
			}
		}
	}
#endif
	if( internal_file->file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_file->file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file IO handle.",
			 function );

			result = -1;
		}
		internal_file->file_io_handle_opened_in_library = 0;
	}
	if( internal_file->file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_file->file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file IO handle.",
			 function );

			result = -1;
		}
		internal_file->file_io_handle_created_in_library = 0;
	}
	internal_file->file_io_handle = NULL;

	if( libolecf_io_handle_clear(
	     internal_file->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		result = -1;
	}
	if( internal_file->msat != NULL )
	{
		 if( libolecf_allocation_table_free(
		      &( internal_file->msat ),
		      error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free MSAT.",
			 function );

			result = -1;
		}
	}
	if( internal_file->sat != NULL )
	{
		if( libolecf_allocation_table_free(
		     &( internal_file->sat ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free SAT.",
			 function );

			result = -1;
		}
	}
	if( internal_file->ssat != NULL )
	{
		 if( libolecf_allocation_table_free(
		      &( internal_file->ssat ),
		      error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free SSAT.",
			 function );

			result = -1;
		}
	}
	if( internal_file->unallocated_block_list != NULL )
	{
		if( libcdata_range_list_free(
		     &( internal_file->unallocated_block_list ),
		     NULL,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free unallocated block list.",
			 function );

			result = -1;
		}
	}
	if( internal_file->directory_tree_root_node != NULL )
	{
		if( libcdata_tree_node_free(
		     &( internal_file->directory_tree_root_node ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libolecf_directory_entry_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free directory tree.",
			 function );

			result = -1;
		}
	}
	return( result );
}

/* Opens a file for reading
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_open_read(
     libolecf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libcdata_list_t *directory_entry_list     = NULL;
	static char *function                     = "libolecf_file_open_read";
	uint32_t msat_sector_identifier           = 0;
	uint32_t number_of_msat_sectors           = 0;
	uint32_t number_of_sat_sectors            = 0;
	uint32_t ssat_sector_identifier           = 0;
	uint32_t number_of_ssat_sectors           = 0;
	uint32_t root_directory_sector_identifier = 0;
	int result                                = 0;

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_file->msat != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - MSAT already set.",
		 function );

		return( -1 );
	}
	if( internal_file->sat != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - SAT already set.",
		 function );

		return( -1 );
	}
	if( internal_file->ssat != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - SSAT already set.",
		 function );

		return( -1 );
	}
	if( internal_file->unallocated_block_list != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - unallocated block list already set.",
		 function );

		return( -1 );
	}
	if( internal_file->directory_tree_root_node != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - directory tree root node already set.",
		 function );

		return( -1 );
	}
	if( libolecf_allocation_table_initialize(
	     &( internal_file->msat ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create MSAT.",
		 function );

		goto on_error;
	}
	if( libolecf_allocation_table_initialize(
	     &( internal_file->sat ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create SAT.",
		 function );

		goto on_error;
	}
	if( libolecf_allocation_table_initialize(
	     &( internal_file->ssat ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create SSAT.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading file header:\n" );
	}
#endif
	if( libolecf_io_handle_read_file_header(
	     internal_file->io_handle,
	     file_io_handle,
	     internal_file->msat,
	     &msat_sector_identifier,
	     &number_of_msat_sectors,
	     &number_of_sat_sectors,
	     &ssat_sector_identifier,
	     &number_of_ssat_sectors,
	     &root_directory_sector_identifier,
	     error ) != 1 )
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
		 "Reading master sector allocation table (MSAT):\n" );
	}
#endif
	if( libolecf_io_handle_read_msat(
	     internal_file->io_handle,
	     file_io_handle,
	     internal_file->msat,
	     msat_sector_identifier,
	     number_of_msat_sectors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read MSAT.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading sector allocation table (SAT):\n" );
	}
#endif
	if( libolecf_io_handle_read_sat(
	     internal_file->io_handle,
	     file_io_handle,
	     internal_file->msat,
	     internal_file->sat,
	     number_of_sat_sectors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read SAT.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading short sector allocation table (SSAT):\n" );
	}
#endif
	if( libolecf_io_handle_read_ssat(
	     internal_file->io_handle,
	     file_io_handle,
	     internal_file->sat,
	     internal_file->ssat,
	     ssat_sector_identifier,
	     number_of_ssat_sectors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read SSAT.",
		 function );

		goto on_error;
	}
	if( libcdata_list_initialize(
	     &directory_entry_list,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create directory entry list.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading directory entries:\n" );
	}
#endif
	if( libolecf_io_handle_read_directory_entries(
	     internal_file->io_handle,
	     file_io_handle,
	     internal_file->sat,
	     directory_entry_list,
	     root_directory_sector_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read directory entries.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Creating directory tree:\n" );
	}
#endif
	result = libolecf_directory_tree_create(
	          &( internal_file->directory_tree_root_node ),
	          &( internal_file->io_handle->short_sector_stream_start_sector_identifier ),
	          &( internal_file->document_summary_information_directory_entry ),
	          &( internal_file->summary_information_directory_entry ),
	          directory_entry_list,
	          internal_file->io_handle->byte_order,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create directory tree.",
		 function );

		goto on_error;
	}
	/* The directory entries are no longer managed by the list but by the tree
	 */
	if( libcdata_list_free(
	     &directory_entry_list,
	     NULL,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free directory entry list.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( internal_file->unallocated_block_list != NULL )
	{
		libcdata_range_list_free(
		 &( internal_file->unallocated_block_list ),
		 NULL,
		 NULL );
	}
	if( internal_file->directory_tree_root_node != NULL )
	{
		libcdata_tree_node_free(
		 &( internal_file->directory_tree_root_node ),
		 (int (*)(intptr_t **, libcerror_error_t **)) &libolecf_directory_entry_free,
		 NULL );
	}
	if( directory_entry_list != NULL )
	{
		libcdata_list_free(
		 &directory_entry_list,
	         (int (*)(intptr_t **, libcerror_error_t **)) &libolecf_directory_entry_free,
		 NULL );
	}
	if( internal_file->ssat != NULL )
	{
		libolecf_allocation_table_free(
		 &( internal_file->ssat ),
		 NULL );
	}
	if( internal_file->sat != NULL )
	{
		libolecf_allocation_table_free(
		 &( internal_file->sat ),
		 NULL );
	}
	if( internal_file->msat != NULL )
	{
		libolecf_allocation_table_free(
		 &( internal_file->msat ),
		 NULL );
	}
	return( -1 );
}

/* Retrieves the sector size
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_get_sector_size(
     libolecf_file_t *file,
     size32_t *sector_size,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_get_sector_size";

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
	internal_file = (libolecf_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( sector_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	if( internal_file->io_handle->sector_size > (size_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid sector size value exceeds maximum.",
		 function );

		return( -1 );
	}
	*sector_size = (size32_t) internal_file->io_handle->sector_size;

	return( 1 );
}

/* Retrieves the short sector size
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_get_short_sector_size(
     libolecf_file_t *file,
     size32_t *short_sector_size,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_get_short_sector_size";

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
	internal_file = (libolecf_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( short_sector_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	if( internal_file->io_handle->short_sector_size > (size_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid short sector size value exceeds maximum.",
		 function );

		return( -1 );
	}
	*short_sector_size = (size32_t) internal_file->io_handle->short_sector_size;

	return( 1 );
}

/* Retrieves the ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_get_ascii_codepage(
     libolecf_file_t *file,
     int *ascii_codepage,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_get_ascii_codepage";

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
	internal_file = (libolecf_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ascii_codepage == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid ASCII codepage.",
		 function );

		return( -1 );
	}
	*ascii_codepage = internal_file->io_handle->ascii_codepage;

	return( 1 );
}

/* Sets the ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_set_ascii_codepage(
     libolecf_file_t *file,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_set_ascii_codepage";

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
	internal_file = (libolecf_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ( ascii_codepage != LIBOLECF_CODEPAGE_ASCII )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_874 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_932 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_936 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_949 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_950 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_1250 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_1251 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_1252 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_1253 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_1254 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_1255 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_1256 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_1257 )
	 && ( ascii_codepage != LIBOLECF_CODEPAGE_WINDOWS_1258 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported ASCII codepage.",
		 function );

		return( -1 );
	}
	internal_file->io_handle->ascii_codepage = ascii_codepage;

	return( 1 );
}

/* Retrieves the format version
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_get_format_version(
     libolecf_file_t *file,
     uint16_t *major_version,
     uint16_t *minor_version,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_get_format_version";

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
	internal_file = (libolecf_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( major_version == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid major version.",
		 function );

		return( -1 );
	}
	if( minor_version == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid minor version.",
		 function );

		return( -1 );
	}
	*major_version = internal_file->io_handle->major_version;
	*minor_version = internal_file->io_handle->minor_version;

	return( 1 );
}

/* Retrieves the number of unallocated blocks
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_get_number_of_unallocated_blocks(
     libolecf_file_t *file,
     int *number_of_unallocated_blocks,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_get_number_of_unallocated_blocks";

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
	internal_file = (libolecf_internal_file_t *) file;

	if( internal_file->unallocated_block_list == NULL )
	{
		if( number_of_unallocated_blocks == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid number of unallocated blocks.",
			 function );

			return( -1 );
		}
		*number_of_unallocated_blocks = 0;
	}
	else
	{
		if( libcdata_range_list_get_number_of_elements(
		     internal_file->unallocated_block_list,
		     number_of_unallocated_blocks,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of elements.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves a specific unallocated block
 * Returns 1 if successful or -1 on error
 */
int libolecf_file_get_unallocated_block(
     libolecf_file_t *file,
     int unallocated_block_index,
     off64_t *offset,
     size64_t *size,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_get_unallocated_block";
	intptr_t *value                         = NULL;

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
	internal_file = (libolecf_internal_file_t *) file;

	if( libcdata_range_list_get_range_by_index(
	     internal_file->unallocated_block_list,
	     unallocated_block_index,
	     (uint64_t *) offset,
	     (uint64_t *) size,
	     &value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve unallocated block range: %d.",
		 function,
		 internal_file->unallocated_block_list );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the root item from the file
 * Returns 1 if successful, 0 if no such item or -1 on error
 */
int libolecf_file_get_root_item(
     libolecf_file_t *file,
     libolecf_item_t **root_item,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file = NULL;
	static char *function                   = "libolecf_file_get_root_item";

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
	internal_file = (libolecf_internal_file_t *) file;

	if( root_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid root item.",
		 function );

		return( -1 );
	}
	if( *root_item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: root item already set.",
		 function );

		return( -1 );
	}
	if( internal_file->directory_tree_root_node == NULL )
	{
		return( 0 );
	}
	if( libolecf_item_initialize(
	     root_item,
	     internal_file->io_handle,
	     internal_file->file_io_handle,
	     internal_file,
	     internal_file->directory_tree_root_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create root item.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the item for the specific UTF-8 encoded path
 * The path separator is the \ character
 * Returns 1 if successful, 0 if no such item or -1 on error
 */
int libolecf_file_get_item_by_utf8_path(
     libolecf_file_t *file,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libolecf_item_t **item,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file       = NULL;
	libcdata_tree_node_t *directory_tree_node     = NULL;
	libcdata_tree_node_t *sub_directory_tree_node = NULL;
	uint8_t *utf8_string_segment                  = NULL;
	static char *function                         = "libolecf_file_get_item_by_utf8_path";
	libuna_unicode_character_t unicode_character  = 0;
	size_t utf8_string_index                      = 0;
	size_t utf8_string_segment_length             = 0;
	int result                                    = 0;

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
	internal_file = (libolecf_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
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
	if( *item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: item already set.",
		 function );

		return( -1 );
	}
	directory_tree_node = internal_file->directory_tree_root_node;

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
				  internal_file->io_handle->byte_order,
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
		     item,
		     internal_file->io_handle,
		     internal_file->file_io_handle,
		     internal_file,
		     directory_tree_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create item.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the item for the specific UTF-16 encoded path
 * The path separator is the \ character
 * Returns 1 if successful, 0 if no such item or -1 on error
 */
int libolecf_file_get_item_by_utf16_path(
     libolecf_file_t *file,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libolecf_item_t **item,
     libcerror_error_t **error )
{
	libolecf_internal_file_t *internal_file       = NULL;
	libcdata_tree_node_t *directory_tree_node     = NULL;
	libcdata_tree_node_t *sub_directory_tree_node = NULL;
	uint16_t *utf16_string_segment                = NULL;
	static char *function                         = "libolecf_file_get_item_by_utf16_path";
	libuna_unicode_character_t unicode_character  = 0;
	size_t utf16_string_index                     = 0;
	size_t utf16_string_segment_length            = 0;
	int result                                    = 0;

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
	internal_file = (libolecf_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
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
	if( *item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: item already set.",
		 function );

		return( -1 );
	}
	directory_tree_node = internal_file->directory_tree_root_node;

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
				  internal_file->io_handle->byte_order,
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
		     item,
		     internal_file->io_handle,
		     internal_file->file_io_handle,
		     internal_file,
		     directory_tree_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create item.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

