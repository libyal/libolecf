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

#if !defined( _LIBOLECF_PROPERTY_SECTION_H )
#define _LIBOLECF_PROPERTY_SECTION_H

#include <common.h>
#include <types.h>

#include "libolecf_extern.h"
#include "libolecf_io_handle.h"
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"
#include "libolecf_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libolecf_internal_property_section libolecf_internal_property_section_t;

struct libolecf_internal_property_section
{
	/* The class indentifier
	 */
	uint8_t class_identifier[ 16 ];

	/* The properties data
	 */
	libcdata_array_t *properties;
};

int libolecf_property_section_initialize(
     libolecf_property_section_t **property_section,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_section_free(
     libolecf_property_section_t **property_section,
     libcerror_error_t **error );

int libolecf_internal_property_section_free(
     libolecf_internal_property_section_t **internal_property_section,
     libcerror_error_t **error );

int libolecf_property_section_read_list_entry(
     libolecf_internal_property_section_t *internal_property_section,
     libolecf_item_t *property_set_stream,
     uint8_t byte_order,
     uint32_t *section_header_offset,
     libcerror_error_t **error );

int libolecf_property_section_read_list_entry_data(
     libolecf_internal_property_section_t *internal_property_section,
     const uint8_t *data,
     size_t data_size,
     uint8_t byte_order,
     uint32_t *section_header_offset,
     libcerror_error_t **error );

int libolecf_property_section_read(
     libolecf_internal_property_section_t *internal_property_section,
     libolecf_io_handle_t *io_handle,
     libolecf_item_t *property_set_stream,
     uint32_t section_header_offset,
     uint8_t byte_order,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_section_get_class_identifier(
     libolecf_property_section_t *property_section,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_section_get_number_of_properties(
     libolecf_property_section_t *property_section,
     int *number_of_properties,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_section_get_property_by_index(
     libolecf_property_section_t *property_section,
     int property_index,
     libolecf_property_value_t **property_value,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_PROPERTY_SECTION_H ) */

