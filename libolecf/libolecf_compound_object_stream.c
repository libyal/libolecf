/*
 * Compound object stream functions
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

#include "libolecf_compound_object_stream.h"
#include "libolecf_definitions.h"
#include "libolecf_directory_entry.h"
#include "libolecf_libcerror.h"
#include "libolecf_libcnotify.h"
#include "libolecf_item.h"
#include "libolecf_io_handle.h"

#include "olecf_compound_object.h"

/* Reads the compound object stream
 * Returns 1 if successful or -1 on error
 */
int libolecf_compound_object_stream_read(
     libolecf_item_t *stream,
     libcerror_error_t **error )
{
	uint8_t size_data[ 4 ];

	olecf_compound_object_header_t compound_object_header;

	libolecf_internal_item_t *internal_item = NULL;
	uint8_t *clipboard_data                 = NULL;
	uint8_t *reserved_string                = NULL;
	uint8_t *user_type_string               = NULL;
	static char *function                   = "libolecf_compound_object_stream_read";
	ssize_t read_count                      = 0;
	uint32_t clipboard_data_size            = 0;
	uint32_t reserved_string_size           = 0;
	uint32_t unicode_marker                 = 0;
	uint32_t user_type_string_size          = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint8_t *trailing_data                  = NULL;
	size_t trailing_data_size               = 0;
#endif

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_item = (libolecf_internal_item_t *) stream;

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
	if( internal_item->file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing file.",
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
	read_count = libolecf_io_handle_read_stream(
	              internal_item->io_handle,
	              internal_item->file_io_handle,
	              internal_item->file->sat,
	              internal_item->file->ssat,
	              internal_item->directory_entry,
	              &( internal_item->offset ),
	              (uint8_t *) &compound_object_header,
	              sizeof( olecf_compound_object_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( olecf_compound_object_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read compound object header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: compound object header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &compound_object_header,
		 sizeof( olecf_compound_object_header_t ),
		 0 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: compound object header unknown1:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) compound_object_header.unknown1,
		 4,
		 0 );

		libcnotify_printf(
		 "%s: compound object header version:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) compound_object_header.version,
		 4,
		 0 );

		libcnotify_printf(
		 "%s: compound object header unknown2:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) compound_object_header.unknown2,
		 20,
		 0 );
	}
#endif
	/* User type string
	 */
	read_count = libolecf_io_handle_read_stream(
	              internal_item->io_handle,
	              internal_item->file_io_handle,
	              internal_item->file->sat,
	              internal_item->file->ssat,
	              internal_item->directory_entry,
	              &( internal_item->offset ),
	              (uint8_t *) size_data,
	              4,
	              error );

	if( read_count != (ssize_t) 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read user type string size.",
		 function );

		goto on_error;
	}
	if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint32_little_endian(
		 size_data,
		 user_type_string_size );
	}
	else if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint32_big_endian(
		 size_data,
		 user_type_string_size );
	}
	if( user_type_string_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing user type string size.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: compound object user type string size\t\t: %" PRIu32 "\n",
		 function,
		 user_type_string_size );
	}
#endif
#if SIZEOF_SIZE_T <= 4
	if( user_type_string_size > (uint32_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid user type string size value exceeds maximum.",
		 function );

		goto on_error;
	}
#endif
	user_type_string = (uint8_t *) memory_allocate(
	                                sizeof( uint8_t ) * user_type_string_size );

	if( user_type_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create user type string.",
		 function );

		goto on_error;
	}
	read_count = libolecf_io_handle_read_stream(
	              internal_item->io_handle,
	              internal_item->file_io_handle,
	              internal_item->file->sat,
	              internal_item->file->ssat,
	              internal_item->directory_entry,
	              &( internal_item->offset ),
	              user_type_string,
	              user_type_string_size,
	              error );

	if( read_count != (ssize_t) user_type_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read user type string.",
		 function );

		goto on_error;
	}
/* TODO do something with string */

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: compound object user type string\t\t\t: %s\n",
		 function,
		 user_type_string );
	}
#endif
	memory_free(
	 user_type_string );

	user_type_string = NULL;

	/* Clipboard data
	 */
	read_count = libolecf_io_handle_read_stream(
	              internal_item->io_handle,
	              internal_item->file_io_handle,
	              internal_item->file->sat,
	              internal_item->file->ssat,
	              internal_item->directory_entry,
	              &( internal_item->offset ),
	              (uint8_t *) size_data,
	              4,
	              error );

	if( read_count != (ssize_t) 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read clipboard data size.",
		 function );

		goto on_error;
	}
	if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint32_little_endian(
		 size_data,
		 clipboard_data_size );
	}
	else if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint32_big_endian(
		 size_data,
		 clipboard_data_size );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: compound object clipboard data size\t\t: 0x%08" PRIx32 " (%" PRIi32 ")\n",
		 function,
		 clipboard_data_size,
		 clipboard_data_size );
	}
#endif
	if( ( clipboard_data_size == 0xffffffeUL )
	 || ( clipboard_data_size == 0xfffffffUL ) )
	{
		/* TODO change this quick-fix */
		clipboard_data_size = 4;
	}
	/* TODO change this quick-fix: add else */
	if( clipboard_data_size > 0x190 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported clipboard data size: 0x%08" PRIx32 ".",
		 function,
		 clipboard_data_size );

		goto on_error;
	}
	else if( clipboard_data_size > 0 )
	{
#if SIZEOF_SIZE_T <= 4
		if( clipboard_data_size > (uint32_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid clipboard data size value exceeds maximum.",
			 function );

			goto on_error;
		}
#endif
		clipboard_data = (uint8_t *) memory_allocate(
					      sizeof( uint8_t ) * clipboard_data_size );

		if( clipboard_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create clipboard data.",
			 function );

			goto on_error;
		}
		read_count = libolecf_io_handle_read_stream(
			      internal_item->io_handle,
			      internal_item->file_io_handle,
		              internal_item->file->sat,
		              internal_item->file->ssat,
			      internal_item->directory_entry,
			      &( internal_item->offset ),
			      clipboard_data,
			      clipboard_data_size,
			      error );

		if( read_count != (ssize_t) clipboard_data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read clipboard data.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: compound object clipboard data:\n",
			 function );
			libcnotify_print_data(
			 clipboard_data,
			 clipboard_data_size,
			 0 );
		}
#endif
		memory_free(
		 clipboard_data );

		clipboard_data = NULL;
	}
	/* Reserved string
	 */
	read_count = libolecf_io_handle_read_stream(
		      internal_item->io_handle,
		      internal_item->file_io_handle,
	              internal_item->file->sat,
	              internal_item->file->ssat,
		      internal_item->directory_entry,
		      &( internal_item->offset ),
		      (uint8_t *) size_data,
		      4,
		      error );

	if( read_count != (ssize_t) 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read reserved string size.",
		 function );

		goto on_error;
	}
	if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint32_little_endian(
		 size_data,
		 reserved_string_size );
	}
	else if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint32_big_endian(
		 size_data,
		 reserved_string_size );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: compound object reserved string size\t\t: %" PRIu32 "\n",
		 function,
		 reserved_string_size );
	}
#endif
	if( reserved_string_size > 0 )
	{
#if SIZEOF_SIZE_T <= 4
		if( reserved_string_size > (uint32_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid reserved string size value exceeds maximum.",
			 function );

			goto on_error;
		}
#endif
		reserved_string = (uint8_t *) memory_allocate(
					       sizeof( uint8_t ) * reserved_string_size );

		if( reserved_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create reserved string.",
			 function );

			goto on_error;
		}
		read_count = libolecf_io_handle_read_stream(
			      internal_item->io_handle,
			      internal_item->file_io_handle,
		              internal_item->file->sat,
		              internal_item->file->ssat,
			      internal_item->directory_entry,
			      &( internal_item->offset ),
			      reserved_string,
			      reserved_string_size,
			      error );

		if( read_count != (ssize_t) reserved_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read reserved string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: compound object reserved string:\n",
			 function );
			libcnotify_print_data(
			 reserved_string,
			 reserved_string_size,
			 0 );
		}
#endif
		memory_free(
		 reserved_string );

		reserved_string = NULL;
	}
	if( internal_item->offset < (off64_t) internal_item->directory_entry->size )
	{
		/* Unicode user type string
		 */
		read_count = libolecf_io_handle_read_stream(
			      internal_item->io_handle,
			      internal_item->file_io_handle,
		              internal_item->file->sat,
		              internal_item->file->ssat,
			      internal_item->directory_entry,
			      &( internal_item->offset ),
			      (uint8_t *) size_data,
			      4,
			      error );

		if( read_count != (ssize_t) 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read unicode marker.",
			 function );

			goto on_error;
		}
		if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
		{
			byte_stream_copy_to_uint32_little_endian(
			 size_data,
			 unicode_marker );
		}
		else if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
		{
			byte_stream_copy_to_uint32_big_endian(
			 size_data,
			 unicode_marker );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: compound object unicode marker\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 unicode_marker );
		}
#endif
	}
	if( ( internal_item->offset < (off64_t) internal_item->directory_entry->size )
	 && ( unicode_marker == 0x71b239f4 ) )
	{
		/* Unicode user type string
		 */
		read_count = libolecf_io_handle_read_stream(
			      internal_item->io_handle,
			      internal_item->file_io_handle,
		              internal_item->file->sat,
		              internal_item->file->ssat,
			      internal_item->directory_entry,
			      &( internal_item->offset ),
			      (uint8_t *) size_data,
			      4,
			      error );

		if( read_count != (ssize_t) 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read unicode user type string size.",
			 function );

			goto on_error;
		}
		if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
		{
			byte_stream_copy_to_uint32_little_endian(
			 size_data,
			 user_type_string_size );
		}
		else if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
		{
			byte_stream_copy_to_uint32_big_endian(
			 size_data,
			 user_type_string_size );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: compound object unicode user type string size\t: %" PRIu32 "\n",
			 function,
			 user_type_string_size );
		}
#endif
		if( user_type_string_size > 0 )
		{
#if SIZEOF_SIZE_T <= 4
			if( user_type_string_size > (uint32_t) SSIZE_MAX )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid user type string size value exceeds maximum.",
				 function );

				goto on_error;
			}
#endif
			user_type_string = (uint8_t *) memory_allocate(
							sizeof( uint8_t ) * user_type_string_size );

			if( user_type_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create unicode user type string.",
				 function );

				goto on_error;
			}
			read_count = libolecf_io_handle_read_stream(
				      internal_item->io_handle,
				      internal_item->file_io_handle,
			              internal_item->file->sat,
			              internal_item->file->ssat,
				      internal_item->directory_entry,
				      &( internal_item->offset ),
				      user_type_string,
				      user_type_string_size,
				      error );

			if( read_count != (ssize_t) user_type_string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read unicode user type string.",
				 function );

				goto on_error;
			}
			/* TODO do something with string */

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: compound object unicode user type string\t: %s\n",
				 function,
				 user_type_string );
			}
#endif
			memory_free(
			 user_type_string );

			user_type_string = NULL;
		}
		/* Unicode clipboard data
		 */
		read_count = libolecf_io_handle_read_stream(
			      internal_item->io_handle,
			      internal_item->file_io_handle,
		              internal_item->file->sat,
		              internal_item->file->ssat,
			      internal_item->directory_entry,
			      &( internal_item->offset ),
			      (uint8_t *) size_data,
			      4,
			      error );

		if( read_count != (ssize_t) 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read unicode clipboard data size.",
			 function );

			goto on_error;
		}
		if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
		{
			byte_stream_copy_to_uint32_little_endian(
			 size_data,
			 clipboard_data_size );
		}
		else if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
		{
			byte_stream_copy_to_uint32_big_endian(
			 size_data,
			 clipboard_data_size );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: compound object unicode clipboard data size\t: 0x%08" PRIx32 " (%" PRIi32 ")\n",
			 function,
			 clipboard_data_size,
			 clipboard_data_size );
		}
#endif
		if( ( clipboard_data_size == 0xffffffeUL )
		 || ( clipboard_data_size == 0xfffffffUL ) )
		{
			/* TODO change this quick-fix */
			clipboard_data_size = 4;
		}
		/* TODO change this quick-fix: add else */
		if( clipboard_data_size > 0x190 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported unicode clipboard data size: 0x%08" PRIx32 ".",
			 function,
			 clipboard_data_size );

			goto on_error;
		}
		else if( clipboard_data_size > 0 )
		{
#if SIZEOF_SIZE_T <= 4
			if( clipboard_data_size > (uint32_t) SSIZE_MAX )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid clipboard data size value exceeds maximum.",
				 function );

				goto on_error;
			}
#endif
			clipboard_data = (uint8_t *) memory_allocate(
						      sizeof( uint8_t ) * clipboard_data_size );

			if( clipboard_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create unicode clipboard data.",
				 function );

				goto on_error;
			}
			read_count = libolecf_io_handle_read_stream(
				      internal_item->io_handle,
				      internal_item->file_io_handle,
			              internal_item->file->sat,
			              internal_item->file->ssat,
				      internal_item->directory_entry,
				      &( internal_item->offset ),
				      clipboard_data,
				      clipboard_data_size,
				      error );

			if( read_count != (ssize_t) clipboard_data_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read unicode clipboard data.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: compound object unicode clipboard data:\n",
				 function );
				libcnotify_print_data(
				 clipboard_data,
				 clipboard_data_size,
				 0 );
			}
#endif
			memory_free(
			 clipboard_data );

			clipboard_data = NULL;
		}
		/* Unicode reserved string
		 */
		read_count = libolecf_io_handle_read_stream(
			      internal_item->io_handle,
			      internal_item->file_io_handle,
		              internal_item->file->sat,
		              internal_item->file->ssat,
			      internal_item->directory_entry,
			      &( internal_item->offset ),
			      (uint8_t *) size_data,
			      4,
			      error );

		if( read_count != (ssize_t) 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read reserved string size.",
			 function );

			goto on_error;
		}
		if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_LITTLE )
		{
			byte_stream_copy_to_uint32_little_endian(
			 size_data,
			 reserved_string_size );
		}
		else if( internal_item->io_handle->byte_order == LIBOLECF_ENDIAN_BIG )
		{
			byte_stream_copy_to_uint32_big_endian(
			 size_data,
			 reserved_string_size );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: compound object unicode reserved string size\t: %" PRIu32 "\n",
			 function,
			 reserved_string_size );
		}
#endif
		if( reserved_string_size > 0 )
		{
#if SIZEOF_SIZE_T <= 4
			if( reserved_string_size > (uint32_t) SSIZE_MAX )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid reserved string size value exceeds maximum.",
				 function );

				goto on_error;
			}
#endif
			reserved_string = (uint8_t *) memory_allocate(
						       sizeof( uint8_t ) * reserved_string_size );

			if( reserved_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create reserved string.",
				 function );

				goto on_error;
			}
			read_count = libolecf_io_handle_read_stream(
				      internal_item->io_handle,
				      internal_item->file_io_handle,
			              internal_item->file->sat,
			              internal_item->file->ssat,
				      internal_item->directory_entry,
				      &( internal_item->offset ),
				      reserved_string,
				      reserved_string_size,
				      error );

			if( read_count != (ssize_t) reserved_string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read reserved string.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: compound object reserved string:\n",
				 function );
				libcnotify_print_data(
				 reserved_string,
				 reserved_string_size,
				 0 );
			}
#endif
			memory_free(
			 reserved_string );

			reserved_string = NULL;
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	/* Check if there is more data in the stream
	 */
	if( internal_item->offset < (off64_t) internal_item->directory_entry->size )
	{
		trailing_data_size = internal_item->directory_entry->size - internal_item->offset;

		if( trailing_data_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid trailing data size value exceeds maximum.",
			 function );

			goto on_error;
		}
		trailing_data = (uint8_t *) memory_allocate(
		                             sizeof( uint8_t ) * trailing_data_size );

		if( trailing_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create trailing data.",
			 function );

			goto on_error;
		}
		read_count = libolecf_io_handle_read_stream(
			      internal_item->io_handle,
			      internal_item->file_io_handle,
		              internal_item->file->sat,
		              internal_item->file->ssat,
			      internal_item->directory_entry,
			      &( internal_item->offset ),
			      trailing_data,
			      trailing_data_size,
			      error );

		if( read_count != (ssize_t) trailing_data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read trailing data.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: compound object trailing data:\n",
			 function );
			libcnotify_print_data(
			 trailing_data,
			 trailing_data_size,
			 0 );
		}
#endif
		memory_free(
		 trailing_data );

		trailing_data = NULL;
	}
#endif
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( trailing_data != NULL )
	{
		memory_free(
		 trailing_data );
	}
#endif
	if( reserved_string != NULL )
	{
		memory_free(
		 reserved_string );
	}
	if( clipboard_data != NULL )
	{
		memory_free(
		 clipboard_data );
	}
	if( user_type_string != NULL )
	{
		memory_free(
		 user_type_string );
	}
	return( -1 );
}

