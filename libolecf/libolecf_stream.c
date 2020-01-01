/*
 * Stream functions
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
#include <types.h>

#include "libolecf_definitions.h"
#include "libolecf_directory_entry.h"
#include "libolecf_libcerror.h"
#include "libolecf_item.h"
#include "libolecf_io_handle.h"
#include "libolecf_stream.h"

/* Reads stream data from the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libolecf_stream_read_buffer(
         libolecf_item_t *item,
         uint8_t *buffer,
         size_t size,
         libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_stream_read_buffer";
	ssize_t read_count                      = 0;

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
	if( internal_item->directory_entry->type != LIBOLECF_ITEM_TYPE_STREAM )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid item - unsupported directory entry type: 0x%02" PRIx8 ".",
		 function,
		 internal_item->directory_entry->type );

		return( -1 );
	}
	if( internal_item->offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid item - offset value out of bounds.",
		 function );

		return( -1 );
	}
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
	if( internal_item->offset > (off64_t) internal_item->directory_entry->size )
	{
		return( 0 );
	}
	if( ( (size64_t) internal_item->offset + size ) > (size64_t) internal_item->directory_entry->size )
	{
		size = (size_t)( (off64_t) internal_item->directory_entry->size - internal_item->offset );
	}
	read_count = libolecf_io_handle_read_stream(
	              internal_item->io_handle,
	              internal_item->file_io_handle,
	              internal_item->file->sat,
	              internal_item->file->ssat,
	              internal_item->directory_entry,
	              &( internal_item->offset ),
	              buffer,
	              size,
	              error );

	if( read_count != (ssize_t) size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer from stream.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Reads stream data a specific offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libolecf_stream_read_buffer_at_offset(
         libolecf_item_t *stream,
         uint8_t *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error )
{
	static char *function = "libolecf_stream_read_buffer_at_offset";
	ssize_t read_count    = 0;

	if( libolecf_stream_seek_offset(
	     stream,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		return( -1 );
	}
	read_count = libolecf_stream_read_buffer(
	              stream,
	              buffer,
	              buffer_size,
	              error );

	if( read_count < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain offset of the stream data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libolecf_stream_seek_offset(
         libolecf_item_t *item,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_stream_seek_offset";

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
	if( internal_item->directory_entry->type != LIBOLECF_ITEM_TYPE_STREAM )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid item - unsupported directory entry type: 0x%02" PRIx8 ".",
		 function,
		 internal_item->directory_entry->type );

		return( -1 );
	}
	if( internal_item->offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid item - offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( offset > (off64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid offset value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	if( whence == SEEK_CUR )
	{
		offset += internal_item->offset;
	}
	else if( whence == SEEK_END )
	{
		offset += internal_item->directory_entry->size;
	}
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		return( -1 );
	}
	if( offset > (off64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid offset value exceeds maximum.",
		 function );

		return( -1 );
	}
	internal_item->offset = offset;

	return( offset );
}

/* Retrievs the current offset in the stream data
 * Returns 1 if successful or -1 on error
 */
int libolecf_stream_get_offset(
     libolecf_item_t *item,
     off64_t *offset,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_stream_get_offset";

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
	if( internal_item->directory_entry->type != LIBOLECF_ITEM_TYPE_STREAM )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid item - unsupported directory entry type: 0x%02" PRIx8 ".",
		 function,
		 internal_item->directory_entry->type );

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
	*offset = internal_item->offset;

	return( 1 );
}

