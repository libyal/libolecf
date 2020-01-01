/*
 * Item functions
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

#if !defined( _LIBOLECF_ITEM_H )
#define _LIBOLECF_ITEM_H

#include <common.h>
#include <types.h>

#include "libolecf_directory_entry.h"
#include "libolecf_extern.h"
#include "libolecf_file.h"
#include "libolecf_io_handle.h"
#include "libolecf_libbfio.h"
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"
#include "libolecf_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libolecf_internal_item libolecf_internal_item_t;

struct libolecf_internal_item
{
	/* The IO handle
	 */
	libolecf_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The file
	 */
	libolecf_internal_file_t *file;

	/* The directory tree node
	 */
	libcdata_tree_node_t *directory_tree_node;

	/* The directory entry
	 */
	libolecf_directory_entry_t *directory_entry;

	/* The current stream offset
	 */
	off64_t offset;
};

int libolecf_item_initialize(
     libolecf_item_t **item,
     libolecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libolecf_internal_file_t *file,
     libcdata_tree_node_t *directory_tree_node,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_free(
     libolecf_item_t **item,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_type(
     libolecf_item_t *item,
     uint8_t *type,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_utf8_name_size(
     libolecf_item_t *item,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_utf8_name(
     libolecf_item_t *item,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_utf16_name_size(
     libolecf_item_t *item,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_utf16_name(
     libolecf_item_t *item,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_size(
     libolecf_item_t *item,
     uint32_t *size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_creation_time(
     libolecf_item_t *item,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_modification_time(
     libolecf_item_t *item,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_number_of_sub_items(
     libolecf_item_t *item,
     int *number_of_sub_items,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_sub_item(
     libolecf_item_t *item,
     int sub_item_index,
     libolecf_item_t **sub_item,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_sub_item_by_utf8_name(
     libolecf_item_t *item,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libolecf_item_t **sub_item,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_sub_item_by_utf16_name(
     libolecf_item_t *item,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libolecf_item_t **sub_item,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_sub_item_by_utf8_path(
     libolecf_item_t *item,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libolecf_item_t **sub_item,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_item_get_sub_item_by_utf16_path(
     libolecf_item_t *item,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libolecf_item_t **sub_item,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_ITEM_H ) */

