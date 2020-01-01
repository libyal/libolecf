/*
 * The property value functions
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

#if !defined( _LIBOLECF_PROPERTY_VALUE_H )
#define _LIBOLECF_PROPERTY_VALUE_H

#include <common.h>
#include <types.h>

#include "libolecf_extern.h"
#include "libolecf_io_handle.h"
#include "libolecf_libcerror.h"
#include "libolecf_libfvalue.h"
#include "libolecf_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libolecf_internal_property_value libolecf_internal_property_value_t;

struct libolecf_internal_property_value
{
	/* The identifier
	 */
	uint32_t identifier;

	/* The value type
	 */
	uint32_t value_type;

	/* The data value
	 */
	libfvalue_value_t *data_value;
};

int libolecf_property_value_initialize(
     libolecf_property_value_t **property_value,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_free(
     libolecf_property_value_t **property_value,
     libcerror_error_t **error );

int libolecf_internal_property_value_free(
     libolecf_internal_property_value_t **internal_property_value,
     libcerror_error_t **error );

int libolecf_property_value_read_data(
     libolecf_internal_property_value_t *internal_property_value,
     libolecf_item_t *property_set_stream,
     libolecf_io_handle_t *io_handle,
     uint32_t property_data_offset,
     uint8_t byte_order,
     libcerror_error_t **error );

int libolecf_property_value_read_list_entry(
     libolecf_internal_property_value_t *internal_property_value,
     libolecf_item_t *property_set_stream,
     uint8_t byte_order,
     uint32_t *property_data_offset,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_identifier(
     libolecf_property_value_t *property_value,
     uint32_t *identifier,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_value_type(
     libolecf_property_value_t *property_value,
     uint32_t *value_type,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_data_size(
     libolecf_property_value_t *property_value,
     size_t *data_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_data(
     libolecf_property_value_t *property_value,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_boolean(
     libolecf_property_value_t *property_value,
     uint8_t *value_boolean,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_16bit_integer(
     libolecf_property_value_t *property_value,
     uint16_t *value_16bit,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_32bit_integer(
     libolecf_property_value_t *property_value,
     uint32_t *value_32bit,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_64bit_integer(
     libolecf_property_value_t *property_value,
     uint64_t *value_64bit,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_filetime(
     libolecf_property_value_t *property_value,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_utf8_string_size(
     libolecf_property_value_t *property_value,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_utf8_string(
     libolecf_property_value_t *property_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_utf16_string_size(
     libolecf_property_value_t *property_value,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_utf16_string(
     libolecf_property_value_t *property_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

/* -------------------------------------------------------------------------
 * Deprecated
 * ------------------------------------------------------------------------- */

LIBOLECF_EXTERN \
int libolecf_property_value_get_value_data_size(
     libolecf_property_value_t *property_value,
     size_t *value_data_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_value_data(
     libolecf_property_value_t *property_value,
     uint8_t *value_data,
     size_t value_data_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_value_boolean(
     libolecf_property_value_t *property_value,
     uint8_t *value_boolean,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_value_16bit(
     libolecf_property_value_t *property_value,
     uint16_t *value_16bit,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_value_32bit(
     libolecf_property_value_t *property_value,
     uint32_t *value_32bit,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_value_64bit(
     libolecf_property_value_t *property_value,
     uint64_t *value_64bit,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_value_filetime(
     libolecf_property_value_t *property_value,
     uint64_t *value_filetime,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_value_utf8_string_size(
     libolecf_property_value_t *property_value,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_value_utf8_string(
     libolecf_property_value_t *property_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_value_utf16_string_size(
     libolecf_property_value_t *property_value,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_property_value_get_value_utf16_string(
     libolecf_property_value_t *property_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_PROPERTY_VALUE_H ) */

