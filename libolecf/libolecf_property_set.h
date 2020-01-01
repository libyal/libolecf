/*
 * The property set functions
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

#if !defined( _LIBOLECF_PROPERTY_SET_H )
#define _LIBOLECF_PROPERTY_SET_H

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

typedef struct libolecf_internal_property_set libolecf_internal_property_set_t;

struct libolecf_internal_property_set
{
	/* The byte order
	 */
	uint8_t byte_order;

	/* The format
	 */
	uint16_t format;

	/* The system version
	 */
	uint32_t system_version;

	/* The number of sections
	 */
	uint16_t number_of_sections;

	/* The class indentifier
	 */
	uint8_t class_identifier[ 16 ];

	/* The sections array
	 */
	libcdata_array_t *sections;
};

int libolecf_property_set_initialize(
     libolecf_property_set_t **property_set,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_set_free(
     libolecf_property_set_t **property_set,
     libcerror_error_t **error );

int libolecf_property_set_read_header_data(
     libolecf_internal_property_set_t *internal_property_set,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libolecf_property_set_read(
     libolecf_property_set_t *property_set,
     libolecf_io_handle_t *io_handle,
     libolecf_item_t *property_set_stream,
     libcerror_error_t **error );

/* TODO get format */
/* TODO get system version */

LIBOLECF_EXTERN \
int libolecf_property_set_get_class_identifier(
     libolecf_property_set_t *property_set,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_set_get_number_of_sections(
     libolecf_property_set_t *property_set,
     int *number_of_sections,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_set_get_section_by_index(
     libolecf_property_set_t *property_set,
     int section_index,
     libolecf_property_section_t **property_section,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_PROPERTY_SET_H ) */

