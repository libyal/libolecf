/*
 * Export handle
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

#if !defined( _EXPORT_HANDLE_H )
#define _EXPORT_HANDLE_H

#include <common.h>
#include <types.h>

#include "log_handle.h"
#include "olecftools_libcerror.h"
#include "olecftools_libolecf.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct export_handle export_handle_t;

struct export_handle
{
	/* The libolecf input file
	 */
	libolecf_file_t *input_file;

	/* The target path
	 */
	system_character_t *target_path;

	/* The target path size
	 */
	size_t target_path_size;

	/* The items export path
	 */
	system_character_t *items_export_path;

	/* The items export path size
	 */
	size_t items_export_path_size;

	/* The ascii codepage
	 */
	int ascii_codepage;

	/* The notification output stream
	 */
	FILE *notify_stream;
};

int export_handle_initialize(
     export_handle_t **export_handle,
     libcerror_error_t **error );

int export_handle_free(
     export_handle_t **export_handle,
     libcerror_error_t **error );

int export_handle_signal_abort(
     export_handle_t *export_handle,
     libcerror_error_t **error );

int export_handle_set_ascii_codepage(
     export_handle_t *export_handle,
     const system_character_t *string,
     libcerror_error_t **error );

int export_handle_set_target_path(
     export_handle_t *export_handle,
     const system_character_t *target_path,
     libcerror_error_t **error );

int export_handle_set_export_path(
     export_handle_t *export_handle,
     const system_character_t *base_path,
     size_t base_path_length,
     const system_character_t *suffix,
     size_t suffix_length,
     system_character_t **export_path,
     size_t *export_path_size,
     libcerror_error_t **error );

int export_handle_create_items_export_path(
     export_handle_t *export_handle,
     libcerror_error_t **error );

int export_handle_open_input(
     export_handle_t *export_handle,
     const system_character_t *filename,
     libcerror_error_t **error );

int export_handle_close(
     export_handle_t *export_handle,
     libcerror_error_t **error );

int export_handle_export_item(
     export_handle_t *export_handle,
     libolecf_item_t *item,
     int item_index,
     int number_of_items,
     const system_character_t *export_path,
     size_t export_path_length,
     log_handle_t *log_handle,
     libcerror_error_t **error );

int export_handle_export_sub_items(
     export_handle_t *export_handle,
     libolecf_item_t *item,
     const system_character_t *export_path,
     size_t export_path_length,
     log_handle_t *log_handle,
     libcerror_error_t **error );

int export_handle_export_file(
     export_handle_t *export_handle,
     log_handle_t *log_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _EXPORT_HANDLE_H ) */

