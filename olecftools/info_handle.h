/*
 * Info handle
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

#if !defined( _INFO_HANDLE_H )
#define _INFO_HANDLE_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "olecftools_libcerror.h"
#include "olecftools_libolecf.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct info_handle info_handle_t;

struct info_handle
{
	/* The libolecf input file
	 */
	libolecf_file_t *input_file;

	/* The libolecf root item
	 */
	libolecf_item_t *root_item;

	/* The ascii codepage
	 */
	int ascii_codepage;

	/* The notification output stream
	 */
	FILE *notify_stream;
};

int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error );

int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error );

int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_set_ascii_codepage(
     info_handle_t *info_handle,
     const system_character_t *string,
     libcerror_error_t **error );

int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error );

int info_handle_close(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_file_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_items_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_item_fprint(
     info_handle_t *info_handle,
     libolecf_item_t *item,
     int indentation_level,
     libcerror_error_t **error );

int info_handle_unallocated_blocks_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_compound_object_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_property_value_fprint(
     info_handle_t *info_handle,
     const uint8_t *class_identifier,
     libolecf_property_value_t *property_value,
     libcerror_error_t **error );

int info_handle_property_section_fprint(
     info_handle_t *info_handle,
     libolecf_property_section_t *property_section,
     libcerror_error_t **error );

int info_handle_property_set_fprint(
     info_handle_t *info_handle,
     libolecf_property_set_t *property_set,
     libcerror_error_t **error );

int info_handle_property_set_stream_fprint(
     info_handle_t *info_handle,
     libolecf_item_t *property_set_stream,
     libcerror_error_t **error );

int info_handle_document_summary_information_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_summary_information_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _INFO_HANDLE_H ) */

