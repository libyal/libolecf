/*
 * OSS-Fuzz target for libolecf property value type
 *
 * Copyright (C) 2008-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

#include <stdlib.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libolecf.h"

#if !defined( LIBOLECF_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_open_file_io_handle(
      libolecf_file_t *file,
      libbfio_handle_t *file_io_handle,
      int access_flags,
      libolecf_error_t **error );

#endif /* !defined( LIBOLECF_HAVE_BFIO ) */

/* Limits the size of the value and string buffers
 */
#define FUZZER_DATA_SIZE_LIMIT	( (size_t) 0x10000 )

/* Limits the number of sub items to walk to find a property set stream
 */
#define FUZZER_SUB_ITEM_LIMIT	8

/* Limits the number of property sections to query
 */
#define FUZZER_SECTION_LIMIT	8

/* Limits the number of property values to query
 */
#define FUZZER_PROPERTY_LIMIT	16

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	uint8_t *value_data    = NULL;
	uint8_t *utf8_string   = NULL;
	uint16_t *utf16_string = NULL;

	libbfio_handle_t *file_io_handle      = NULL;
	libolecf_file_t *file                 = NULL;
	libolecf_item_t *item                 = NULL;
	libolecf_item_t *property_set_stream  = NULL;
	libolecf_property_set_t *property_set      = NULL;
	libolecf_property_section_t *property_section = NULL;
	libolecf_property_value_t *property_value   = NULL;
	uint8_t value_boolean      = 0;
	uint16_t value_16bit       = 0;
	uint32_t identifier        = 0;
	uint32_t value_32bit       = 0;
	uint32_t value_type        = 0;
	uint64_t value_64bit       = 0;
	uint64_t value_filetime    = 0;
	size_t value_data_size     = 0;
	size_t utf8_string_size    = 0;
	size_t utf16_string_size   = 0;
	int number_of_properties   = 0;
	int number_of_sections     = 0;
	int number_of_sub_items    = 0;
	int property_index         = 0;
	int result                 = 0;
	int section_index          = 0;
	int sub_item_index         = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libolecf_file_initialize(
	     &file,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libolecf_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     LIBOLECF_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libolecf_file;
	}
	if( libolecf_file_get_root_item(
	     file,
	     &item,
	     NULL ) == 1 )
	{
		/* Walk the sub items to find a property set stream
		 */
		if( libolecf_item_get_number_of_sub_items(
		     item,
		     &number_of_sub_items,
		     NULL ) == 1 )
		{
			for( sub_item_index = 0;
			     sub_item_index < number_of_sub_items;
			     sub_item_index++ )
			{
				property_set = NULL;

				if( sub_item_index >= FUZZER_SUB_ITEM_LIMIT )
				{
					break;
				}
				if( libolecf_item_get_sub_item(
				     item,
				     sub_item_index,
				     &property_set_stream,
				     NULL ) != 1 )
				{
					break;
				}
				result = libolecf_property_set_stream_get_set(
					 property_set_stream,
					 &property_set,
					 NULL );
				if( ( result != 1 )
				 || ( property_set == NULL ) )
				{
					libolecf_item_free(
					 &property_set_stream,
					 NULL );
					continue;
				}
				if( libolecf_property_set_get_number_of_sections(
				     property_set,
				     &number_of_sections,
				     NULL ) == 1 )
				{
					for( section_index = 0;
					     section_index < number_of_sections;
					     section_index++ )
					{
						property_section     = NULL;
						number_of_properties = 0;

						if( section_index >= FUZZER_SECTION_LIMIT )
						{
							break;
						}
						result = libolecf_property_set_get_section_by_index(
							 property_set,
							 section_index,
							 &property_section,
							 NULL );
						if( ( result != 1 )
						 || ( property_section == NULL ) )
						{
							continue;
						}
						if( libolecf_property_section_get_number_of_properties(
						     property_section,
						     &number_of_properties,
						     NULL ) == 1 )
						{
							for( property_index = 0;
							     property_index < number_of_properties;
							     property_index++ )
							{
								property_value = NULL;

								if( property_index >= FUZZER_PROPERTY_LIMIT )
								{
									break;
								}
								result = libolecf_property_section_get_property_by_index(
									 property_section,
									 property_index,
									 &property_value,
									 NULL );
								if( ( result != 1 )
								 || ( property_value == NULL ) )
								{
									continue;
								}
								libolecf_property_value_get_identifier(
								 property_value,
								 &identifier,
								 NULL );
								libolecf_property_value_get_value_type(
								 property_value,
								 &value_type,
								 NULL );
								result = libolecf_property_value_get_data_size(
									 property_value,
									 &value_data_size,
									 NULL );
								if( ( result == 1 )
								 && ( value_data_size > 0 ) )
								{
									if( value_data_size > FUZZER_DATA_SIZE_LIMIT )
									{
										value_data_size = FUZZER_DATA_SIZE_LIMIT;
									}
									value_data = (uint8_t *) malloc( value_data_size );

									if( value_data != NULL )
									{
										if( libolecf_property_value_get_data(
										     property_value,
										     value_data,
										     value_data_size,
										     NULL ) == 1 )
										{
											/* Use the value as a sink
											 * to keep it live
											 */
											value_boolean = value_data[ 0 ];
										}
										free( value_data );
										value_data = NULL;
									}
								}
								libolecf_property_value_get_data_as_boolean(
								 property_value,
								 &value_boolean,
								 NULL );
								libolecf_property_value_get_data_as_16bit_integer(
								 property_value,
								 &value_16bit,
								 NULL );
								libolecf_property_value_get_data_as_32bit_integer(
								 property_value,
								 &value_32bit,
								 NULL );
								libolecf_property_value_get_data_as_64bit_integer(
								 property_value,
								 &value_64bit,
								 NULL );
								libolecf_property_value_get_data_as_filetime(
								 property_value,
								 &value_filetime,
								 NULL );
								result = libolecf_property_value_get_data_as_utf8_string_size(
									 property_value,
									 &utf8_string_size,
									 NULL );
								if( ( result == 1 )
								 && ( utf8_string_size > 0 ) )
								{
									if( utf8_string_size > FUZZER_DATA_SIZE_LIMIT )
									{
										utf8_string_size = FUZZER_DATA_SIZE_LIMIT;
									}
									utf8_string = (uint8_t *) malloc( utf8_string_size );

									if( utf8_string != NULL )
									{
										if( libolecf_property_value_get_data_as_utf8_string(
										     property_value,
										     utf8_string,
										     utf8_string_size,
										     NULL ) == 1 )
										{
											utf8_string[ utf8_string_size - 1 ] = 0;

											/* Use the value as a sink
											 * to keep it live
											 */
											value_boolean = utf8_string[ 0 ];
										}
										free( utf8_string );
										utf8_string = NULL;
									}
								}
								result = libolecf_property_value_get_data_as_utf16_string_size(
									 property_value,
									 &utf16_string_size,
									 NULL );
								if( ( result == 1 )
								 && ( utf16_string_size > 0 ) )
								{
									if( utf16_string_size > FUZZER_DATA_SIZE_LIMIT )
									{
										utf16_string_size = FUZZER_DATA_SIZE_LIMIT;
									}
									/* The size is the number of UTF-16
									 * characters, including the end of
									 * string character
									 */
									utf16_string = (uint16_t *) malloc( utf16_string_size * sizeof( uint16_t ) );

									if( utf16_string != NULL )
									{
										if( libolecf_property_value_get_data_as_utf16_string(
										     property_value,
										     utf16_string,
										     utf16_string_size,
										     NULL ) == 1 )
										{
											utf16_string[ utf16_string_size - 1 ] = 0;

											/* Use the value as a sink
											 * to keep it live
											 */
											value_boolean = (uint8_t) utf16_string[ 0 ];
										}
										free( utf16_string );
										utf16_string = NULL;
									}
								}
								/* The deprecated accessors
								 */
								result = libolecf_property_value_get_value_data_size(
									 property_value,
									 &value_data_size,
									 NULL );
								if( ( result == 1 )
								 && ( value_data_size > 0 ) )
								{
									if( value_data_size > FUZZER_DATA_SIZE_LIMIT )
									{
										value_data_size = FUZZER_DATA_SIZE_LIMIT;
									}
									value_data = (uint8_t *) malloc( value_data_size );

									if( value_data != NULL )
									{
										if( libolecf_property_value_get_value_data(
										     property_value,
										     value_data,
										     value_data_size,
										     NULL ) == 1 )
										{
											/* Use the value as a sink
											 * to keep it live
											 */
											value_boolean = value_data[ 0 ];
										}
										free( value_data );
										value_data = NULL;
									}
								}
								libolecf_property_value_get_value_boolean(
								 property_value,
								 &value_boolean,
								 NULL );
								libolecf_property_value_get_value_16bit(
								 property_value,
								 &value_16bit,
								 NULL );
								libolecf_property_value_get_value_32bit(
								 property_value,
								 &value_32bit,
								 NULL );
								libolecf_property_value_get_value_64bit(
								 property_value,
								 &value_64bit,
								 NULL );
								libolecf_property_value_get_value_filetime(
								 property_value,
								 &value_filetime,
								 NULL );
								result = libolecf_property_value_get_value_utf8_string_size(
									 property_value,
									 &utf8_string_size,
									 NULL );
								if( ( result == 1 )
								 && ( utf8_string_size > 0 ) )
								{
									if( utf8_string_size > FUZZER_DATA_SIZE_LIMIT )
									{
										utf8_string_size = FUZZER_DATA_SIZE_LIMIT;
									}
									utf8_string = (uint8_t *) malloc( utf8_string_size );

									if( utf8_string != NULL )
									{
										if( libolecf_property_value_get_value_utf8_string(
										     property_value,
										     utf8_string,
										     utf8_string_size,
										     NULL ) == 1 )
										{
											utf8_string[ utf8_string_size - 1 ] = 0;

											/* Use the value as a sink
											 * to keep it live
											 */
											value_boolean = utf8_string[ 0 ];
										}
										free( utf8_string );
										utf8_string = NULL;
									}
								}
								result = libolecf_property_value_get_value_utf16_string_size(
									 property_value,
									 &utf16_string_size,
									 NULL );
								if( ( result == 1 )
								 && ( utf16_string_size > 0 ) )
								{
									if( utf16_string_size > FUZZER_DATA_SIZE_LIMIT )
									{
										utf16_string_size = FUZZER_DATA_SIZE_LIMIT;
									}
									/* The size is the number of UTF-16
									 * characters, including the end of
									 * string character
									 */
									utf16_string = (uint16_t *) malloc( utf16_string_size * sizeof( uint16_t ) );

									if( utf16_string != NULL )
									{
										if( libolecf_property_value_get_value_utf16_string(
										     property_value,
										     utf16_string,
										     utf16_string_size,
										     NULL ) == 1 )
										{
											utf16_string[ utf16_string_size - 1 ] = 0;

											/* Use the value as a sink
											 * to keep it live
											 */
											value_boolean = (uint8_t) utf16_string[ 0 ];
										}
										free( utf16_string );
										utf16_string = NULL;
									}
								}
								libolecf_property_value_free(
								 &property_value,
								 NULL );
							}
						}
						libolecf_property_section_free(
						 &property_section,
						 NULL );
					}
				}
				libolecf_property_set_free(
				 &property_set,
				 NULL );
				libolecf_item_free(
				 &property_set_stream,
				 NULL );
			}
		}
		libolecf_item_free(
		 &item,
		 NULL );
	}
	libolecf_file_close(
	 file,
	 NULL );

on_error_libolecf_file:
	libolecf_file_free(
	 &file,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */
