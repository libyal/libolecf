/*
 * File functions
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

#if !defined( _LIBOLECF_FILE_H )
#define _LIBOLECF_FILE_H

#include <common.h>
#include <types.h>

#include "libolecf_allocation_table.h"
#include "libolecf_directory_entry.h"
#include "libolecf_extern.h"
#include "libolecf_io_handle.h"
#include "libolecf_libbfio.h"
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"
#include "libolecf_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libolecf_internal_file libolecf_internal_file_t;

struct libolecf_internal_file
{
	/* The io handle
	 */
	libolecf_io_handle_t *io_handle;

	/* The file io handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The master sector allocation table (MSAT)
	 */
	libolecf_allocation_table_t *msat;

	/* The sector allocation table (SAT)
	 */
	libolecf_allocation_table_t *sat;

	/* The short-sector allocation table (SSAT)
	 */
	libolecf_allocation_table_t *ssat;

	/* The unallocated block list
	 */
	libcdata_range_list_t *unallocated_block_list;

	/* The directory tree root node
	 */
	libcdata_tree_node_t *directory_tree_root_node;

	/* A reference to the summary information directory entry
	 */
	libolecf_directory_entry_t *summary_information_directory_entry;

	/* A reference to the document summary information directory entry
	 */
	libolecf_directory_entry_t *document_summary_information_directory_entry;
};

LIBOLECF_EXTERN \
int libolecf_file_initialize(
     libolecf_file_t **file,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_free(
     libolecf_file_t **file,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_signal_abort(
     libolecf_file_t *file,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_open(
     libolecf_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBOLECF_EXTERN \
int libolecf_file_open_wide(
     libolecf_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBOLECF_EXTERN \
int libolecf_file_open_file_io_handle(
     libolecf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_close(
     libolecf_file_t *file,
     libcerror_error_t **error );

int libolecf_file_open_read(
     libolecf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_get_sector_size(
     libolecf_file_t *file,
     size32_t *sector_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_get_short_sector_size(
     libolecf_file_t *file,
     size32_t *short_sector_size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_get_ascii_codepage(
     libolecf_file_t *file,
     int *ascii_codepage,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_set_ascii_codepage(
     libolecf_file_t *file,
     int ascii_codepage,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_get_format_version(
     libolecf_file_t *file,
     uint16_t *major_version,
     uint16_t *minor_version,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_get_number_of_unallocated_blocks(
     libolecf_file_t *file,
     int *number_of_unallocated_blocks,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_get_unallocated_block(
     libolecf_file_t *file,
     int unallocated_block_index,
     off64_t *offset,
     size64_t *size,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_get_root_item(
     libolecf_file_t *file,
     libolecf_item_t **root_item,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_get_item_by_utf8_path(
     libolecf_file_t *file,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libolecf_item_t **item,
     libcerror_error_t **error );

LIBOLECF_EXTERN \
int libolecf_file_get_item_by_utf16_path(
     libolecf_file_t *file,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libolecf_item_t **item,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_FILE_H ) */

