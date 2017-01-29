/*
 * The directory tree functions
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

#if !defined( _LIBOLECF_DIRECTORY_TREE_H )
#define _LIBOLECF_DIRECTORY_TREE_H

#include <common.h>
#include <types.h>

#include "libolecf_directory_entry.h"
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libolecf_directory_tree_create(
     libcdata_tree_node_t **directory_tree_root_node,
     uint32_t *short_sector_stream_start_sector_identifier,
     libolecf_directory_entry_t **document_summary_information_directory_entry,
     libolecf_directory_entry_t **summary_information_directory_entry,
     libcdata_list_t *directory_entry_list,
     uint8_t byte_order,
     libcerror_error_t **error );

int libolecf_directory_tree_create_process_entry(
     libcdata_tree_node_t *directory_tree_node,
     const libolecf_directory_entry_t *root_directory_entry,
     libolecf_directory_entry_t **document_summary_information_directory_entry,
     libolecf_directory_entry_t **summary_information_directory_entry,
     libcdata_list_t *directory_entry_list,
     libolecf_directory_entry_t *directory_entry,
     uint8_t byte_order,
     libcerror_error_t **error );

int libolecf_directory_tree_get_sub_node_by_utf8_name(
     libcdata_tree_node_t *directory_tree_node,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     uint8_t byte_order,
     libcdata_tree_node_t **sub_directory_tree_node,
     libcerror_error_t **error );

int libolecf_directory_tree_get_sub_node_by_utf16_name(
     libcdata_tree_node_t *directory_tree_node,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     uint8_t byte_order,
     libcdata_tree_node_t **sub_directory_tree_node,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_DIRECTORY_TREE_H ) */

