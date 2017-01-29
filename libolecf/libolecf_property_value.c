/*
 * The property value functions
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

#include "libolecf_definitions.h"
#include "libolecf_io_handle.h"
#include "libolecf_libcerror.h"
#include "libolecf_libcnotify.h"
#include "libolecf_libfvalue.h"
#include "libolecf_ole.h"
#include "libolecf_property_value.h"
#include "libolecf_stream.h"
#include "libolecf_types.h"

#include "olecf_property_set.h"

/* Creates a property value
 * Make sure the value property_value is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_initialize(
     libolecf_property_value_t **property_value,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_initialize";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	if( *property_value != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid property value value already set.",
		 function );

		return( -1 );
	}
	internal_property_value = memory_allocate_structure(
	                           libolecf_internal_property_value_t );

	if( internal_property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create property value.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_property_value,
	     0,
	     sizeof( libolecf_internal_property_value_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear property value.",
		 function );

		goto on_error;
	}
	*property_value = (libolecf_property_value_t *) internal_property_value;

	return( 1 );

on_error:
	if( internal_property_value != NULL )
	{
		memory_free(
		 internal_property_value );
	}
	return( -1 );
}

/* Frees a property value
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_free(
     libolecf_property_value_t **property_value,
     libcerror_error_t **error )
{
	static char *function = "libolecf_property_value_free";

        if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	if( *property_value != NULL )
	{
		/* The property_value is managed elsewhere
		 */
		*property_value = NULL;
	}
        return( 1 );
}

/* Frees a property value
 * Returns 1 if successful or -1 on error
 */
int libolecf_internal_property_value_free(
     libolecf_internal_property_value_t **internal_property_value,
     libcerror_error_t **error )
{
	static char *function = "libolecf_internal_property_set_free";
	int result            = 1;

        if( internal_property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	if( *internal_property_value != NULL )
	{
		if( ( *internal_property_value )->data_value != NULL )
		{
			if( libfvalue_value_free(
			     &( ( *internal_property_value )->data_value ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free data value.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *internal_property_value );

		*internal_property_value = NULL;
	}
        return( result );
}

/* Reads the property value data from the property set stream
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_read_data(
     libolecf_internal_property_value_t *internal_property_value,
     libolecf_item_t *property_set_stream,
     libolecf_io_handle_t *io_handle,
     uint32_t property_data_offset,
     uint8_t byte_order,
     libcerror_error_t **error )
{
	uint8_t property_value_buffer[ 4 ];

	uint8_t *data                  = NULL;
	static char *function          = "libolecf_property_value_read_data";
	ssize_t read_count             = 0;
	uint32_t aligment_padding_size = 0;
	uint32_t number_of_values      = 0;
	uint32_t read_size             = 0;
	uint32_t string_size           = 0;
	uint32_t value_data_end_offset = 0;
	uint32_t value_data_size       = 0;
	uint32_t value_index           = 0;
	uint8_t is_multi_value         = 0;
	uint8_t is_variable_size       = 0;
	uint8_t value_type             = 0;
	int value_encoding             = 0;

	if( internal_property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	if( property_set_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property set stream.",
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
	if( ( byte_order != LIBOLECF_ENDIAN_BIG )
	 && ( byte_order != LIBOLECF_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order: 0x%02" PRIx8 ".",
		 function,
		 byte_order );

		return( -1 );
	}
	if( property_data_offset >= (uint32_t) ( UINT32_MAX - 4 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid property data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( libolecf_stream_seek_offset(
	     property_set_stream,
	     (off64_t) property_data_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek data at offset: %" PRIu32 ".",
		 function,
		 property_data_offset );

		goto on_error;
	}
	read_count = libolecf_stream_read_buffer(
		      property_set_stream,
		      property_value_buffer,
		      4,
		      error );

	if( read_count != (ssize_t) 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read type.",
		 function );

		goto on_error;
	}
	property_data_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type data:\n",
		 function );
		libcnotify_print_data(
		 property_value_buffer,
		 4,
		 0 );
	}
#endif
	if( byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint32_little_endian(
		 property_value_buffer,
		 internal_property_value->value_type );
	}
	else if( byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint32_big_endian(
		 property_value_buffer,
		 internal_property_value->value_type );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: property value type\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_property_value->value_type );
	}
#endif
	if( byte_order == LIBOLECF_ENDIAN_BIG )
	{
		value_encoding = LIBFVALUE_ENDIAN_BIG;
	}
	else if( byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		value_encoding = LIBFVALUE_ENDIAN_LITTLE;
	}
	switch( internal_property_value->value_type )
	{
		case LIBOLECF_VALUE_TYPE_BOOLEAN:
			value_type      = LIBFVALUE_VALUE_TYPE_BOOLEAN;
			value_data_size = 1;
			break;

		case LIBOLECF_VALUE_TYPE_INTEGER_8BIT_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_8BIT_UNSIGNED:
			value_type      = LIBFVALUE_VALUE_TYPE_INTEGER_8BIT;
			value_data_size = 1;
			break;

		case LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_16BIT_UNSIGNED:
			value_type      = LIBFVALUE_VALUE_TYPE_INTEGER_16BIT;
			value_data_size = 2;
			break;

		case LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_32BIT_UNSIGNED:
		case LIBOLECF_VALUE_TYPE_ERROR:
		case LIBOLECF_VALUE_TYPE_INTEGER_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_UNSIGNED:
			value_type      = LIBFVALUE_VALUE_TYPE_INTEGER_32BIT;
			value_data_size = 4;
			break;

		case LIBOLECF_VALUE_TYPE_FLOAT_32BIT:
			value_type      = LIBFVALUE_VALUE_TYPE_FLOATING_POINT_32BIT;
			value_data_size = 4;
			break;

		case LIBOLECF_VALUE_TYPE_DOUBLE_64BIT:
			value_type      = LIBFVALUE_VALUE_TYPE_FLOATING_POINT_64BIT;
			value_data_size = 8;
			break;

		case LIBOLECF_VALUE_TYPE_INTEGER_64BIT_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_64BIT_UNSIGNED:
			value_type      = LIBFVALUE_VALUE_TYPE_INTEGER_64BIT;
			value_data_size = 8;
			break;

		case LIBOLECF_VALUE_TYPE_APPLICATION_TIME:
		case LIBOLECF_VALUE_TYPE_CURRENCY:
			value_type      = LIBFVALUE_VALUE_TYPE_BINARY_DATA;
			value_data_size = 8;
			break;

		case LIBOLECF_VALUE_TYPE_FILETIME:
			value_type      = LIBFVALUE_VALUE_TYPE_FILETIME;
			value_data_size = 8;
			break;

		case LIBOLECF_VALUE_TYPE_GUID:
			value_type      = LIBFVALUE_VALUE_TYPE_GUID;
			value_data_size = 16;
			break;

		case LIBOLECF_VALUE_TYPE_FIXED_POINT_128BIT:
			value_type      = LIBFVALUE_VALUE_TYPE_BINARY_DATA;
			value_data_size = 16;
			break;

		case LIBOLECF_VALUE_TYPE_STRING_ASCII:
			value_type       = LIBFVALUE_VALUE_TYPE_STRING_BYTE_STREAM;
			value_encoding   = io_handle->ascii_codepage;
			is_variable_size = 1;
			break;

		case LIBOLECF_VALUE_TYPE_STRING_UNICODE:
			value_type       = LIBFVALUE_VALUE_TYPE_STRING_UTF16;
			value_encoding   = LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN;
			is_variable_size = 1;
			break;

		case LIBOLECF_VALUE_TYPE_BINARY_DATA:
		case LIBOLECF_VALUE_TYPE_CLIPBOARD_FORMAT:
			value_type       = LIBFVALUE_VALUE_TYPE_BINARY_DATA;
			is_variable_size = 1;
			break;

/* TODO handle multi values */
		case LIBOLECF_VALUE_TYPE_MULTI_VALUE_STRING_ASCII:
		case LIBOLECF_VALUE_TYPE_MULTI_VALUE_STRING_UNICODE:
			value_type     = LIBFVALUE_VALUE_TYPE_BINARY_DATA;
			is_multi_value = 1;
			break;

		case LIBOLECF_VALUE_TYPE_EMPTY:
		case LIBOLECF_VALUE_TYPE_NULL:
		case LIBOLECF_VALUE_TYPE_BINARY_STRING:
		case LIBOLECF_VALUE_TYPE_IDISPATCH:
		case LIBOLECF_VALUE_TYPE_VARIANT:
		case LIBOLECF_VALUE_TYPE_IUNKNOWN:
		case LIBOLECF_VALUE_TYPE_VOID:
		case LIBOLECF_VALUE_TYPE_HRESULT:
		case LIBOLECF_VALUE_TYPE_POINTER:
		case LIBOLECF_VALUE_TYPE_SAFE_ARRAY:
		case LIBOLECF_VALUE_TYPE_ARRAY:
		case LIBOLECF_VALUE_TYPE_USER_DEFINED:
		case LIBOLECF_VALUE_TYPE_STREAM:
		case LIBOLECF_VALUE_TYPE_STORAGE:
		case LIBOLECF_VALUE_TYPE_STREAMED_OBJECT:
		case LIBOLECF_VALUE_TYPE_STORED_OBJECT:
		case LIBOLECF_VALUE_TYPE_BINARY_DATA_OBJECT:
		case LIBOLECF_VALUE_TYPE_VERSIONED_STREAM:
		case LIBOLECF_VALUE_TYPE_MULTI_VALUE_VARIANT:
			value_type       = LIBFVALUE_VALUE_TYPE_BINARY_DATA;
			is_variable_size = 1;
			break;

		default:
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: unsupported property value type: 0x%08" PRIx32 ".\n",
				 function,
				 internal_property_value->value_type );
			}
#endif
			value_type = LIBFVALUE_VALUE_TYPE_UNDEFINED;
			break;
	}
/* TODO handle multi values */
	if( is_multi_value != 0 )
	{
		if( property_data_offset >= (uint32_t) ( UINT32_MAX - 4 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid property data offset value out of bounds.",
			 function );

			goto on_error;
		}
		read_count = libolecf_stream_read_buffer(
			      property_set_stream,
			      property_value_buffer,
			      4,
			      error );

		if( read_count != (ssize_t) 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data size.",
			 function );

			goto on_error;
		}
		property_data_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: number of values data:\n",
			 function );
			libcnotify_print_data(
			 property_value_buffer,
			 4,
			 0 );
		}
#endif
		if( byte_order == LIBOLECF_ENDIAN_LITTLE )
		{
			byte_stream_copy_to_uint32_little_endian(
			 property_value_buffer,
			 number_of_values );
		}
		else if( byte_order == LIBOLECF_ENDIAN_BIG )
		{
			byte_stream_copy_to_uint32_big_endian(
			 property_value_buffer,
			 number_of_values );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: number of values\t\t\t: %" PRIu32 "\n",
			 function,
			 number_of_values );
		}
#endif
		for( value_index = 0;
		     value_index < number_of_values;
		     value_index++ )
		{
/* TODO handle different types of multi values differently */
			if( property_data_offset >= (uint32_t) ( UINT32_MAX - 4 ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid property data offset value out of bounds.",
				 function );

				goto on_error;
			}
			read_count = libolecf_stream_read_buffer(
				      property_set_stream,
				      property_value_buffer,
				      4,
				      error );

			if( read_count != (ssize_t) 4 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read data size.",
				 function );

				goto on_error;
			}
			property_data_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: value: %" PRIu32 " data size data:\n",
				 function,
				 value_index );
				libcnotify_print_data(
				 property_value_buffer,
				 4,
				 0 );
			}
#endif
			if( byte_order == LIBOLECF_ENDIAN_LITTLE )
			{
				byte_stream_copy_to_uint32_little_endian(
				 property_value_buffer,
				 value_data_size );
			}
			else if( byte_order == LIBOLECF_ENDIAN_BIG )
			{
				byte_stream_copy_to_uint32_big_endian(
				 property_value_buffer,
				 value_data_size );
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: value: %" PRIu32 " data size\t\t\t: %" PRIu32 "\n",
				 function,
				 value_index,
				 value_data_size );
			}
#endif
			if( property_data_offset >= (uint32_t) ( UINT32_MAX - value_data_size ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid property data offset value out of bounds.",
				 function );

				goto on_error;
			}
/* TODO
			if( ( internal_property_value->value_type == LIBOLECF_VALUE_TYPE_MULTI_VALUE_STRING_ASCII )
			 || ( internal_property_value->value_type == LIBOLECF_VALUE_TYPE_MULTI_VALUE_STRING_UNICODE ) )
			{
				value_data_end_offset = property_data_offset + value_data_size;
				aligment_padding_size = value_data_end_offset % 16;

				if( aligment_padding_size != 0 )
				{
					aligment_padding_size = 16 - aligment_padding_size;
				}
			}
			else
*/
			{
				aligment_padding_size = 0;
			}
			read_size = value_data_size + aligment_padding_size;

#if SIZEOF_SIZE_T <= 4
			if( read_size > (uint32_t) SSIZE_MAX )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid value data size value exceeds maximum.",
				 function );

				goto on_error;
			}
#endif
			data = (uint8_t *) memory_allocate(
			                    sizeof( uint8_t ) * read_size );

			if( data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create data.",
				 function );

				goto on_error;
			}
			read_count = libolecf_stream_read_buffer(
				      property_set_stream,
				      data,
				      (size_t) read_size,
				      error );

			if( read_count != (ssize_t) read_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read data.",
				 function );

				goto on_error;
			}
			property_data_offset += read_size;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: value: %" PRIu32 " data:\n",
				 function,
				 value_index );
				libcnotify_print_data(
				 data,
				 (size_t) value_data_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

				if( aligment_padding_size > 0 )
				{
					libcnotify_printf(
					 "%s: value: %" PRIu32 " alignment padding:\n",
					 function,
					 value_index );
					libcnotify_print_data(
					 &( data[ value_data_size ] ),
					 (size_t) aligment_padding_size,
					 0 );
				}
			}
#endif
/* TODO set up multi value */
			memory_free(
			 data );

			data = NULL;
		}
	}
	else if( value_type != LIBFVALUE_VALUE_TYPE_UNDEFINED )
	{
		if( is_variable_size != 0 )
		{
			read_count = libolecf_stream_read_buffer(
				      property_set_stream,
				      property_value_buffer,
				      4,
				      error );

			if( read_count != (ssize_t) 4 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read data size.",
				 function );

				goto on_error;
			}
			property_data_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: data size data:\n",
				 function );
				libcnotify_print_data(
				 property_value_buffer,
				 4,
				 0 );
			}
#endif
			if( byte_order == LIBOLECF_ENDIAN_LITTLE )
			{
				byte_stream_copy_to_uint32_little_endian(
				 property_value_buffer,
				 value_data_size );
			}
			else if( byte_order == LIBOLECF_ENDIAN_BIG )
			{
				byte_stream_copy_to_uint32_big_endian(
				 property_value_buffer,
				 value_data_size );
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: property data size\t\t\t: %" PRIu32 "\n",
			 function,
			 value_data_size );
		}
#endif
		if( value_data_size > 0 )
		{
#if SIZEOF_SIZE_T <= 4
			if( value_data_size > (uint32_t) SSIZE_MAX )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid value data size value exceeds maximum.",
				 function );

				goto on_error;
			}
#endif
			data = (uint8_t *) memory_allocate(
			                    sizeof( uint8_t ) * value_data_size );

			if( data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create data.",
				 function );

				goto on_error;
			}
			read_count = libolecf_stream_read_buffer(
				      property_set_stream,
				      data,
				      (size_t) value_data_size,
				      error );

			if( read_count != (ssize_t) value_data_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read data.",
				 function );

				goto on_error;
			}
			property_data_offset += value_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: data:\n",
				 function );
				libcnotify_print_data(
				 data,
				 (size_t) value_data_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
			/* Make sure to determine the correct string size
			 */
			if( internal_property_value->value_type == LIBOLECF_VALUE_TYPE_STRING_ASCII )
			{
				string_size = 0;

				for( string_size = 0;
				     string_size < value_data_size;
				     string_size++ )
				{
					if( data[ string_size ] == 0 )
					{
						string_size++;

						break;
					}
				}
				value_data_size = string_size;
			}
			else if( internal_property_value->value_type == LIBOLECF_VALUE_TYPE_STRING_UNICODE )
			{
				string_size = 0;

				for( string_size = 0;
				     string_size < value_data_size;
				     string_size += 2 )
				{
					if( ( data[ string_size ] == 0 )
					 && ( data[ string_size + 1 ] == 0 ) )
					{
						string_size += 2;

						break;
					}
				}
				value_data_size = string_size;
			}
		}
		if( libfvalue_value_type_initialize(
		     &( internal_property_value->data_value ),
		     value_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create data value.",
			 function );

			goto on_error;
		}
		if( value_data_size > 0 )
		{
			if( libfvalue_value_set_data(
			     internal_property_value->data_value,
			     data,
			     (size_t) value_data_size,
			     value_encoding,
			     LIBFVALUE_VALUE_DATA_FLAG_MANAGED | LIBFVALUE_VALUE_DATA_FLAG_CLONE_BY_REFERENCE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set data value data.",
				 function );

				goto on_error;
			}
			data = NULL;
		}
	}
	return( 1 );

on_error:
	if( internal_property_value->data_value != NULL )
	{
		libfvalue_value_free(
		 &( internal_property_value->data_value ),
		 NULL );
	}
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	return( -1 );
}

/* Reads the property value list entry from the property set stream
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_read_list_entry(
     libolecf_internal_property_value_t *internal_property_value,
     libolecf_item_t *property_set_stream,
     uint8_t byte_order,
     uint32_t *property_data_offset,
     libcerror_error_t **error )
{
	olecf_property_set_property_list_entry_t property_list_entry;

	static char *function = "libolecf_property_value_read_list_entry";
	ssize_t read_count    = 0;

	if( internal_property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBOLECF_ENDIAN_BIG )
	 && ( byte_order != LIBOLECF_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order: 0x%02" PRIx8 ".",
		 function,
		 byte_order );

		return( -1 );
	}
	if( property_data_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property data offset.",
		 function );

		return( -1 );
	}
	read_count = libolecf_stream_read_buffer(
		      property_set_stream,
		      (uint8_t *) &property_list_entry,
		      sizeof( olecf_property_set_property_list_entry_t ),
		      error );

	if( read_count != (ssize_t) sizeof( olecf_property_set_property_list_entry_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read list entry.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: list entry data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &property_list_entry,
		 sizeof( olecf_property_set_property_list_entry_t ),
		 0 );
	}
#endif
	if( byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint32_little_endian(
		 property_list_entry.identifier,
		 internal_property_value->identifier );

		byte_stream_copy_to_uint32_little_endian(
		 property_list_entry.offset,
		 *property_data_offset );
	}
	else if( byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint32_big_endian(
		 property_list_entry.identifier,
		 internal_property_value->identifier );

		byte_stream_copy_to_uint32_big_endian(
		 property_list_entry.offset,
		 *property_data_offset );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: property identifier\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_property_value->identifier );

		libcnotify_printf(
		 "%s: property data offset\t\t: %" PRIu32 "\n",
		 function,
		 *property_data_offset );

		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

/* Retrieves the identifier
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_identifier(
     libolecf_property_value_t *property_value,
     uint32_t *identifier,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_identifier";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	*identifier = internal_property_value->identifier;

	return( 1 );
}

/* Retrieves the value type
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_value_type(
     libolecf_property_value_t *property_value,
     uint32_t *value_type,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_value_type";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( value_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value type.",
		 function );

		return( -1 );
	}
	*value_type = internal_property_value->value_type;

	return( 1 );
}

/* Retrieves the data size
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_data_size(
     libolecf_property_value_t *property_value,
     size_t *data_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_data_size";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( libfvalue_value_get_data_size(
	     internal_property_value->data_value,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_data(
     libolecf_property_value_t *property_value,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_data";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( libfvalue_value_copy_data(
	     internal_property_value->data_value,
	     data,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data as a boolean value
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_data_as_boolean(
     libolecf_property_value_t *property_value,
     uint8_t *value_boolean,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_data_as_boolean";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_BOOLEAN )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	/* Using copy to 8-bit here not to impose the libfvalue boolean logic on to the OLE boolean value
	 */
	if( libfvalue_value_copy_to_8bit(
	     internal_property_value->data_value,
	     0,
	     value_boolean,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to boolean value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data as a 16-bit integer value
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_data_as_16bit_integer(
     libolecf_property_value_t *property_value,
     uint16_t *value_16bit,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_data_as_16bit_integer";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_INTEGER_16BIT_UNSIGNED ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_copy_to_16bit(
	     internal_property_value->data_value,
	     0,
	     value_16bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to 16-bit value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data as a 32-bit integer value
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_data_as_32bit_integer(
     libolecf_property_value_t *property_value,
     uint32_t *value_32bit,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_data_as_32bit_integer";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_INTEGER_32BIT_UNSIGNED ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_copy_to_32bit(
	     internal_property_value->data_value,
	     0,
	     value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to 32-bit value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data as a 64-bit integer value
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_data_as_64bit_integer(
     libolecf_property_value_t *property_value,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_data_as_64bit_integer";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_INTEGER_64BIT_SIGNED )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_INTEGER_64BIT_UNSIGNED ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_copy_to_64bit(
	     internal_property_value->data_value,
	     0,
	     value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to 64-bit value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data as a 64-bit filetime value
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_data_as_filetime(
     libolecf_property_value_t *property_value,
     uint64_t *filetime,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_data_as_filetime";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_FILETIME )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_copy_to_64bit(
	     internal_property_value->data_value,
	     0,
	     filetime,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to 64-bit filetime value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the data as an UTF-8 string value
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_data_as_utf8_string_size(
     libolecf_property_value_t *property_value,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_data_as_utf8_string_size";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_ASCII )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_get_utf8_string_size(
	     internal_property_value->data_value,
	     0,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine UTF-8 string size of value data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data as an UTF-8 string value
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_data_as_utf8_string(
     libolecf_property_value_t *property_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_data_as_utf8_string";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_ASCII )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_copy_to_utf8_string(
	     internal_property_value->data_value,
	     0,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the data as an UTF-16 string value
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_data_as_utf16_string_size(
     libolecf_property_value_t *property_value,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_data_as_utf16_string_size";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_ASCII )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_get_utf16_string_size(
	     internal_property_value->data_value,
	     0,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine UTF-16 string size of value data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data as an UTF-16 string value
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_data_as_utf16_string(
     libolecf_property_value_t *property_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_data_as_utf16_string";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_ASCII )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_copy_to_utf16_string(
	     internal_property_value->data_value,
	     0,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* -------------------------------------------------------------------------
 * Deprecated
 * ------------------------------------------------------------------------- */

/* Retrieves the value data size
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_value_data_size(
     libolecf_property_value_t *property_value,
     size_t *data_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_value_data_size";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( libfvalue_value_get_data_size(
	     internal_property_value->data_value,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value data size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the value data
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_value_data(
     libolecf_property_value_t *property_value,
     uint8_t *value_data,
     size_t value_data_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_value_data";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( libfvalue_value_copy_data(
	     internal_property_value->data_value,
	     value_data,
	     value_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the boolean value
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_value_boolean(
     libolecf_property_value_t *property_value,
     uint8_t *value_boolean,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_value_boolean";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_BOOLEAN )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	/* Using copy to 8-bit here not to impose the libfvalue boolean logic on to the OLE boolean value
	 */
	if( libfvalue_value_copy_to_8bit(
	     internal_property_value->data_value,
	     0,
	     value_boolean,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to boolean value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the 16-bit value
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_value_16bit(
     libolecf_property_value_t *property_value,
     uint16_t *value_16bit,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_value_16bit";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_INTEGER_16BIT_UNSIGNED ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_copy_to_16bit(
	     internal_property_value->data_value,
	     0,
	     value_16bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to 16-bit value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the 32-bit value
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_value_32bit(
     libolecf_property_value_t *property_value,
     uint32_t *value_32bit,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_value_32bit";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_INTEGER_32BIT_UNSIGNED ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_copy_to_32bit(
	     internal_property_value->data_value,
	     0,
	     value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to 32-bit value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the 64-bit value
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_value_64bit(
     libolecf_property_value_t *property_value,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_value_64bit";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_INTEGER_64BIT_SIGNED )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_INTEGER_64BIT_UNSIGNED ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_copy_to_64bit(
	     internal_property_value->data_value,
	     0,
	     value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to 64-bit value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the 64-bit filetime value
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_value_filetime(
     libolecf_property_value_t *property_value,
     uint64_t *value_filetime,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_value_filetime";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_FILETIME )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_copy_to_64bit(
	     internal_property_value->data_value,
	     0,
	     value_filetime,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to 64-bit filetime value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 string size
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_value_utf8_string_size(
     libolecf_property_value_t *property_value,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_value_utf8_string_size";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_ASCII )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_get_utf8_string_size(
	     internal_property_value->data_value,
	     0,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine UTF-8 string size of value data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 string value
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_value_utf8_string(
     libolecf_property_value_t *property_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_value_utf8_string";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_ASCII )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_copy_to_utf8_string(
	     internal_property_value->data_value,
	     0,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 string size
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_value_utf16_string_size(
     libolecf_property_value_t *property_value,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_value_utf16_string_size";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_ASCII )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_get_utf16_string_size(
	     internal_property_value->data_value,
	     0,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine UTF-16 string size of value data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 string value
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_value_get_value_utf16_string(
     libolecf_property_value_t *property_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_value_t *internal_property_value = NULL;
	static char *function                                       = "libolecf_property_value_get_value_utf16_string";

	if( property_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	internal_property_value = (libolecf_internal_property_value_t *) property_value;

	if( ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_ASCII )
	 && ( internal_property_value->value_type != LIBOLECF_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string value type: 0x%04" PRIx32 ".",
		 function,
		 internal_property_value->value_type );

		return( -1 );
	}
	if( libfvalue_value_copy_to_utf16_string(
	     internal_property_value->data_value,
	     0,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}


