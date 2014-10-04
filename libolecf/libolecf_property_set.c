/*
 * The property set functions
 *
 * Copyright (c) 2008-2014, Joachim Metz <joachim.metz@gmail.com>
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
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"
#include "libolecf_libcnotify.h"
#include "libolecf_libfguid.h"
#include "libolecf_property_section.h"
#include "libolecf_property_set.h"
#include "libolecf_stream.h"
#include "libolecf_types.h"

#include "olecf_property_set.h"

/* Creates a property set
 * Make sure the value property_set is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_set_initialize(
     libolecf_property_set_t **property_set,
     libcerror_error_t **error )
{
	libolecf_internal_property_set_t *internal_property_set = NULL;
	static char *function                                   = "libolecf_property_set_initialize";

	if( property_set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property set.",
		 function );

		return( -1 );
	}
	if( *property_set != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid property set value already set.",
		 function );

		return( -1 );
	}
	internal_property_set = memory_allocate_structure(
	                         libolecf_internal_property_set_t );

	if( internal_property_set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create property set.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_property_set,
	     0,
	     sizeof( libolecf_internal_property_set_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear property set.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_property_set->sections ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sections array.",
		 function );

		goto on_error;
	}
	*property_set = (libolecf_property_set_t *) internal_property_set;

	return( 1 );

on_error:
	if( internal_property_set != NULL )
	{
		memory_free(
		 internal_property_set );
	}
	return( -1 );
}

/* Frees a property set
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_set_free(
     libolecf_property_set_t **property_set,
     libcerror_error_t **error )
{
	libolecf_internal_property_set_t *internal_property_set = NULL;
	static char *function                                   = "libolecf_property_set_free";
	int result                                              = 1;

        if( property_set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property set.",
		 function );

		return( -1 );
	}
	if( *property_set != NULL )
	{
		internal_property_set = (libolecf_internal_property_set_t *) *property_set;
		*property_set         = NULL;

		if( libcdata_array_free(
		     &( internal_property_set->sections ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libolecf_internal_property_section_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free sections array.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_property_set );
	}
        return( result );
}

/* Reads the property set from the property set stream
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_set_read(
     libolecf_property_set_t *property_set,
     libolecf_io_handle_t *io_handle,
     libolecf_item_t *property_set_stream,
     libcerror_error_t **error )
{
	olecf_property_set_header_t property_set_header;

	libolecf_internal_property_set_t *internal_property_set = NULL;
	libolecf_property_section_t *property_section           = NULL;
	static char *function                                   = "libolecf_property_set_read";
	off64_t section_list_entry_offset                       = 0;
	ssize_t read_count                                      = 0;
	uint32_t section_header_offset                          = 0;
	uint16_t number_of_sections                             = 0;
	uint16_t section_index                                  = 0;
	int sections_entry                                      = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t guid_string[ 48 ];

	libfguid_identifier_t *guid                             = NULL;
	int result                                              = 0;
#endif

	if( property_set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property set.",
		 function );

		return( -1 );
	}
	internal_property_set = (libolecf_internal_property_set_t *) property_set;

	if( libolecf_stream_seek_offset(
	     property_set_stream,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek property set header offset: 0.",
		 function );

		goto on_error;
	}
	read_count = libolecf_stream_read_buffer(
	              property_set_stream,
	              (uint8_t *) &property_set_header,
	              sizeof( olecf_property_set_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( olecf_property_set_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read property set header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: property set header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &property_set_header,
		 sizeof( olecf_property_set_header_t ),
		 0 );
	}
#endif
	if( ( property_set_header.byte_order[ 0 ] == 0xfe )
	 && ( property_set_header.byte_order[ 1 ] == 0xff ) )
	{
		internal_property_set->byte_order = LIBOLECF_ENDIAN_LITTLE;
	}
	else if( ( property_set_header.byte_order[ 0 ] == 0xff )
	      && ( property_set_header.byte_order[ 1 ] == 0xfe ) )
	{
		internal_property_set->byte_order = LIBOLECF_ENDIAN_BIG;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order: 0x%02" PRIx8 " 0x%02" PRIx8 ".",
		 function,
		 property_set_header.byte_order[ 0 ],
		 property_set_header.byte_order[ 1 ] );

		goto on_error;
	}
	if( internal_property_set->byte_order == LIBOLECF_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint16_little_endian(
		 property_set_header.format,
		 internal_property_set->format );

		byte_stream_copy_to_uint32_little_endian(
		 property_set_header.system_version,
		 internal_property_set->system_version );

		byte_stream_copy_to_uint16_little_endian(
		 property_set_header.number_of_sections,
		 number_of_sections );
	}
	else if( internal_property_set->byte_order == LIBOLECF_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint16_big_endian(
		 property_set_header.format,
		 internal_property_set->format );

		byte_stream_copy_to_uint32_big_endian(
		 property_set_header.system_version,
		 internal_property_set->system_version );

		byte_stream_copy_to_uint16_big_endian(
		 property_set_header.number_of_sections,
		 number_of_sections );
	}
	if( memory_copy(
	     internal_property_set->class_identifier,
	     property_set_header.class_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy class identifier.",
		 function );

		goto on_error;
	}
/* TODO make sure the class identifier is set in little endian */

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: property set header byte order\t\t: 0x%02" PRIx8 " 0x%02" PRIx8 "\n",
		 function,
		 property_set_header.byte_order[ 0 ],
		 property_set_header.byte_order[ 1 ] );

		libcnotify_printf(
		 "%s: property set header format\t\t\t: %" PRIu16 "\n",
		 function,
		 internal_property_set->format );
		
		libcnotify_printf(
		 "%s: property set header system version\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_property_set->system_version );

		if( libfguid_identifier_initialize(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create GUID.",
			 function );

			goto on_error;
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     internal_property_set->class_identifier,
		     16,
		     internal_property_set->byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: property set header class identifier\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 guid_string );

		if( libfguid_identifier_free(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free GUID.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: property set header number of sections\t: %" PRIu16 "\n",
		 function,
		 number_of_sections );

		libcnotify_printf(
		 "\n" );
	}
#endif
	section_list_entry_offset = sizeof( olecf_property_set_header_t );

	for( section_index = 0;
	     section_index < (int) number_of_sections;
	     section_index++ )
	{
		if( libolecf_property_section_initialize(
		     &property_section,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create property section: %d.",
			 function,
			 section_index );

			goto on_error;
		}
		if( libolecf_stream_seek_offset(
		     property_set_stream,
		     section_list_entry_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek property section list entry: %d offset: %" PRIi64 ".",
			 function,
			 section_index,
			 section_list_entry_offset );

			goto on_error;
		}
		if( libolecf_property_section_read_list_entry(
		     (libolecf_internal_property_section_t *) property_section,
		     property_set_stream,
		     internal_property_set->byte_order,
		     &section_header_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read property section list entry: %d.",
			 function,
			 section_index );

			goto on_error;
		}
		if( libolecf_stream_get_offset(
		     property_set_stream,
		     &section_list_entry_offset,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to retrieve property section list entry offset.",
			 function );

			goto on_error;
		}
		if( libolecf_property_section_read(
		     (libolecf_internal_property_section_t *) property_section,
		     io_handle,
		     property_set_stream,
		     section_header_offset,
		     internal_property_set->byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read property section: %d at offset: %" PRIu32 ".",
			 function,
			 section_index,
			 section_header_offset );

			goto on_error;
		}
		if( libcdata_array_append_entry(
		     internal_property_set->sections,
		     &sections_entry,
		     (intptr_t *) property_section,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append property section: %d to sections array.",
			 function,
			 section_index );

			goto on_error;
		}
		property_section = NULL;
	}
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
#endif
	if( property_section != NULL )
	{
		libolecf_property_section_free(
		 &property_section,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the class identifier
 * The identifier is a GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_set_get_class_identifier(
     libolecf_property_set_t *property_set,
     uint8_t *class_identifier,
     size_t size,
     libcerror_error_t **error )
{
	libolecf_internal_property_set_t *internal_property_set = NULL;
	static char *function                                   = "libolecf_property_set_get_number_of_sections";

	if( property_set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property set.",
		 function );

		return( -1 );
	}
	internal_property_set = (libolecf_internal_property_set_t *) property_set;

	if( class_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid class identifier.",
		 function );

		return( -1 );
	}
	if( size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: class identifier too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     class_identifier,
	     internal_property_set->class_identifier,
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

/* Retrieves the number of sections in the property set
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_set_get_number_of_sections(
     libolecf_property_set_t *property_set,
     int *number_of_sections,
     libcerror_error_t **error )
{
	libolecf_internal_property_set_t *internal_property_set = NULL;
	static char *function                                   = "libolecf_property_set_get_number_of_sections";

	if( property_set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property set.",
		 function );

		return( -1 );
	}
	internal_property_set = (libolecf_internal_property_set_t *) property_set;

	if( libcdata_array_get_number_of_entries(
	     internal_property_set->sections,
	     number_of_sections,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries in sections array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific section
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_set_get_section_by_index(
     libolecf_property_set_t *property_set,
     int section_index,
     libolecf_property_section_t **property_section,
     libcerror_error_t **error )
{
	libolecf_internal_property_set_t *internal_property_set = NULL;
	static char *function                                   = "libolecf_property_set_get_section_by_index";

	if( property_set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property set.",
		 function );

		return( -1 );
	}
	internal_property_set = (libolecf_internal_property_set_t *) property_set;

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
		 "%s: property section already set.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_property_set->sections,
	     section_index,
	     (intptr_t **) property_section,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve section: %d.",
		 function,
		 section_index );

		return( -1 );
	}
	return( 1 );
}
