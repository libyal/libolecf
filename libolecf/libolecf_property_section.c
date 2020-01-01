/*
 * The property section functions
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
#include "libolecf_io_handle.h"
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"
#include "libolecf_libcnotify.h"
#include "libolecf_libfguid.h"
#include "libolecf_libfole.h"
#include "libolecf_libfwps.h"
#include "libolecf_property_section.h"
#include "libolecf_property_value.h"
#include "libolecf_stream.h"
#include "libolecf_types.h"

#include "olecf_property_set.h"

/* Creates a property section
 * Make sure the value property_section is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_section_initialize(
     libolecf_property_section_t **property_section,
     libcerror_error_t **error )
{
	libolecf_internal_property_section_t *internal_property_section = NULL;
	static char *function                                           = "libolecf_property_section_initialize";

	if( property_section == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property section.",
		 function );

		return( -1 );
	}
	if( *property_section != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid property section value already set.",
		 function );

		return( -1 );
	}
	internal_property_section = memory_allocate_structure(
	                             libolecf_internal_property_section_t );

	if( internal_property_section == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create property section.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_property_section,
	     0,
	     sizeof( libolecf_internal_property_section_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear property section.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_property_section->properties ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create properties array.",
		 function );

		goto on_error;
	}
	*property_section = (libolecf_property_section_t *) internal_property_section;

	return( 1 );

on_error:
	if( internal_property_section != NULL )
	{
		memory_free(
		 internal_property_section );
	}
	return( -1 );
}

/* Frees a property section
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_section_free(
     libolecf_property_section_t **property_section,
     libcerror_error_t **error )
{
	static char *function = "libolecf_property_section_free";

        if( property_section == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property section.",
		 function );

		return( -1 );
	}
	if( *property_section != NULL )
	{
		/* The property_section is managed elsewhere
		 */
		*property_section = NULL;
	}
        return( 1 );
}

/* Frees a property section
 * Returns 1 if successful or -1 on error
 */
int libolecf_internal_property_section_free(
     libolecf_internal_property_section_t **internal_property_section,
     libcerror_error_t **error )
{
	static char *function = "libolecf_internal_property_section_free";
	int result            = 1;

        if( internal_property_section == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property section.",
		 function );

		return( -1 );
	}
	if( *internal_property_section != NULL )
	{
		if( libcdata_array_free(
		     &( ( *internal_property_section )->properties ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libolecf_internal_property_value_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free properties array.",
			 function );

			result = -1;
		}
		memory_free(
		 *internal_property_section );

		*internal_property_section = NULL;
	}
        return( result );
}

/* Reads the property section list entry
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_section_read_list_entry(
     libolecf_internal_property_section_t *internal_property_section,
     libolecf_item_t *property_set_stream,
     uint8_t byte_order,
     uint32_t *section_header_offset,
     libcerror_error_t **error )
{
	uint8_t property_section_list_entry_data[ sizeof( olecf_property_section_list_entry_t ) ];

	static char *function = "libolecf_property_section_read_list_entry";
	ssize_t read_count    = 0;

	if( internal_property_section == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property section.",
		 function );

		return( -1 );
	}
	read_count = libolecf_stream_read_buffer(
		      property_set_stream,
		      property_section_list_entry_data,
		      sizeof( olecf_property_section_list_entry_t ),
		      error );

	if( read_count != (ssize_t) sizeof( olecf_property_section_list_entry_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read list entry.",
		 function );

		return( -1 );
	}
	if( libolecf_property_section_read_list_entry_data(
	     internal_property_section,
	     property_section_list_entry_data,
	     sizeof( olecf_property_section_list_entry_t ),
	     byte_order,
	     section_header_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read list entry.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the property section list entry
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_section_read_list_entry_data(
     libolecf_internal_property_section_t *internal_property_section,
     const uint8_t *data,
     size_t data_size,
     uint8_t byte_order,
     uint32_t *section_header_offset,
     libcerror_error_t **error )
{
	static char *function = "libolecf_property_section_read_list_entry_data";

	if( internal_property_section == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property section.",
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
	if( data_size < sizeof( olecf_property_section_list_entry_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
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
	if( section_header_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid section header offset.",
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
		 data,
		 sizeof( olecf_property_section_list_entry_t ),
		 0 );
	}
#endif
	if( byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (olecf_property_section_list_entry_t *) data )->offset,
		 *section_header_offset );
	}
	else if( byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint32_big_endian(
		 ( (olecf_property_section_list_entry_t *) data )->offset,
		 *section_header_offset );
	}
	if( memory_copy(
	     internal_property_section->class_identifier,
	     ( (olecf_property_section_list_entry_t *) data )->class_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy class identifier.",
		 function );

		return( -1 );
	}
/* TODO make sure the class identifier is set in little endian */

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libolecf_debug_print_guid_value(
		     function,
		     "class identifier\t",
		     internal_property_section->class_identifier,
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

			return( -1 );
		}
		libcnotify_printf(
		 "%s: class name\t\t: %s (%s)\n",
		 function,
                 libfwps_format_class_identifier_get_identifier(
                  internal_property_section->class_identifier ),
                 libfwps_format_class_identifier_get_description(
                  internal_property_section->class_identifier ) );

		libcnotify_printf(
		 "%s: section header offset\t: %" PRIu32 "\n",
		 function,
		 *section_header_offset );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads the property section
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_section_read(
     libolecf_internal_property_section_t *internal_property_section,
     libolecf_io_handle_t *io_handle,
     libolecf_item_t *property_set_stream,
     uint32_t section_header_offset,
     uint8_t byte_order,
     libcerror_error_t **error )
{
	olecf_property_section_header_t property_section_header;

	libolecf_property_value_t *property_value = NULL;
	static char *function                     = "libolecf_property_section_read";
	ssize_t read_count                        = 0;
	off64_t property_values_list_entry_offset = 0;
	uint32_t number_of_properties             = 0;
	uint32_t property_index                   = 0;
	uint32_t property_value_data_offset       = 0;
	uint32_t section_data_size                = 0;
	int properties_entry                      = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t property_value_identifier        = 0;
	uint32_t property_value_type              = 0;
#endif

	if( internal_property_section == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property section.",
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
	if( libolecf_stream_seek_offset(
	     property_set_stream,
	     (off64_t) section_header_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek header at offset: %" PRIu32 ".",
		 function,
		 section_header_offset );

		goto on_error;
	}
	read_count = libolecf_stream_read_buffer(
		      property_set_stream,
		      (uint8_t *) &property_section_header,
		      sizeof( olecf_property_section_header_t ),
		      error );

	if( read_count != (ssize_t) sizeof( olecf_property_section_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: header data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &property_section_header,
		 sizeof( olecf_property_section_header_t ),
		 0 );
	}
#endif
	if( byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint32_little_endian(
		 property_section_header.data_size,
		 section_data_size );

		byte_stream_copy_to_uint32_little_endian(
		 property_section_header.number_of_properties,
		 number_of_properties );
	}
	else if( byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint32_big_endian(
		 property_section_header.data_size,
		 section_data_size );

		byte_stream_copy_to_uint32_big_endian(
		 property_section_header.number_of_properties,
		 number_of_properties );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 section_data_size );

		libcnotify_printf(
		 "%s: number of properties\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_properties );

		libcnotify_printf(
		 "\n" );
	}
#endif
	property_values_list_entry_offset = section_header_offset
	                                  + sizeof( olecf_property_section_header_t );

	for( property_index = 0;
	     property_index < number_of_properties;
	     property_index++ )
	{
		if( libolecf_stream_seek_offset(
		     property_set_stream,
		     property_values_list_entry_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek property values list entry: %d offset: %" PRIi64 ".",
			 function,
			 property_index,
			 property_values_list_entry_offset );

			goto on_error;
		}
		if( libolecf_property_value_initialize(
		     &property_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create property value: %d.",
			 function,
			 property_index );

			goto on_error;
		}
		if( libolecf_property_value_read_list_entry(
		     (libolecf_internal_property_value_t *) property_value,
		     property_set_stream,
		     byte_order,
		     &property_value_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read property values list entry: %d.",
			 function,
			 property_index );

			goto on_error;
		}
/* TODO check upper bound with stream size, section_data_size is not the right upper bound ? */
		if( property_value_data_offset <= sizeof( olecf_property_section_header_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid property value data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( libolecf_stream_get_offset(
		     property_set_stream,
		     &property_values_list_entry_offset,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to retrieve property values list entry offset.",
			 function );

			goto on_error;
		}
		if( libolecf_property_value_read_data(
		     (libolecf_internal_property_value_t *) property_value,
		     property_set_stream,
		     io_handle,
		     section_header_offset + property_value_data_offset,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read property value: %d at offset: %" PRIu32 ".",
			 function,
			 property_index,
			 section_header_offset + property_value_data_offset );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libolecf_property_value_get_identifier(
			     property_value,
			     &property_value_identifier,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve property value: %d identifier.",
				 function,
				 property_index );

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
				 "%s: unable to retrieve property value: %d type.",
				 function,
				 property_index );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: property identifier\t\t\t: 0x%08" PRIx32 " (%s : %s)\n",
			 function,
			 property_value_identifier,
			 libfwps_property_identifier_get_identifier(
			  internal_property_section->class_identifier,
			  property_value_identifier,
			  property_value_type ),
			 libfwps_property_identifier_get_description(
			  internal_property_section->class_identifier,
			  property_value_identifier,
			  property_value_type ) );

			libcnotify_printf(
			 "%s: property value type\t\t\t: 0x%08" PRIx32 " (%s : %s)\n",
			 function,
			 property_value_type,
			 libfole_value_type_get_identifier(
			  property_value_type ),
			 libfole_value_type_get_description(
			  property_value_type ) );

			libcnotify_printf(
			 "\n" );
		}
#endif
		if( libcdata_array_append_entry(
		     internal_property_section->properties,
		     &properties_entry,
		     (intptr_t *) property_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append property value: %d to properties array.",
			 function,
			 property_index );

			goto on_error;
		}
		property_value = NULL;
	}
	return( 1 );

on_error:
	if( property_value != NULL )
	{
		libolecf_internal_property_value_free(
		 (libolecf_internal_property_value_t **) &property_value,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the class identifier
 * The identifier is a GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_section_get_class_identifier(
     libolecf_property_section_t *property_section,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	libolecf_internal_property_section_t *internal_property_section = NULL;
	static char *function                                           = "libolecf_property_section_get_number_of_sections";

	if( property_section == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property section.",
		 function );

		return( -1 );
	}
	internal_property_section = (libolecf_internal_property_section_t *) property_section;

	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( guid_data_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: GUID data size too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     internal_property_section->class_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy class identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of properties
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_section_get_number_of_properties(
     libolecf_property_section_t *property_section,
     int *number_of_properties,
     libcerror_error_t **error )
{
	libolecf_internal_property_section_t *internal_property_section = NULL;
	static char *function                                           = "libolecf_property_section_get_number_of_properties";

	if( property_section == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property section.",
		 function );

		return( -1 );
	}
	internal_property_section = (libolecf_internal_property_section_t *) property_section;

	if( libcdata_array_get_number_of_entries(
	     internal_property_section->properties,
	     number_of_properties,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries in properties array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific property
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_section_get_property_by_index(
     libolecf_property_section_t *property_section,
     int property_index,
     libolecf_property_value_t **property_value,
     libcerror_error_t **error )
{
	libolecf_internal_property_section_t *internal_property_section = NULL;
	static char *function                                           = "libolecf_property_section_get_property_by_index";

	if( property_section == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property section.",
		 function );

		return( -1 );
	}
	internal_property_section = (libolecf_internal_property_section_t *) property_section;

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
		 "%s: property value already set.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_property_section->properties,
	     property_index,
	     (intptr_t **) property_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve property value: %d.",
		 function,
		 property_index );

		return( -1 );
	}
	return( 1 );
}

