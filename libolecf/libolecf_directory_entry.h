/*
 * The directory entry functions
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

#if !defined( _LIBOLECF_DIRECTORY_ENTRY_H )
#define _LIBOLECF_DIRECTORY_ENTRY_H

#include <common.h>
#include <types.h>

#include "libolecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libolecf_directory_entry libolecf_directory_entry_t;

struct libolecf_directory_entry
{
	/* The directory name
	 */
	uint8_t *name;

	/* The size of the directory name
	 */
	size_t name_size;

	/* Creation time
	 */
	uint64_t creation_time;

	/* Modification time
	 */
	uint64_t modification_time;

	/* The sector identifier
	 */
	uint32_t sector_identifier;

	/* The size
	 */
	uint32_t size;

	/* The type
	 */
	uint8_t type;

	/* The directory identifier
	 */
	uint32_t directory_identifier;

	/* The previous directory identifier
	 */
	uint32_t previous_directory_identifier;

	/* The next directory identifier
	 */
	uint32_t next_directory_identifier;

	/* The sub directory identifier
	 */
	uint32_t sub_directory_identifier;

	/* Value to indicate the directory entry was set in the tree
	 */
	uint8_t set_in_tree;
};

int libolecf_directory_entry_initialize(
     libolecf_directory_entry_t **directory_entry,
     libcerror_error_t **error );

int libolecf_directory_entry_free(
     libolecf_directory_entry_t **directory_entry,
     libcerror_error_t **error );

int libolecf_directory_entry_compare(
     libolecf_directory_entry_t *first_directory_entry,
     libolecf_directory_entry_t *second_directory_entry,
     libcerror_error_t **error );

int libolecf_directory_entry_read_data(
     libolecf_directory_entry_t *directory_entry,
     int directory_entry_index,
     const uint8_t *data,
     size_t data_size,
     uint8_t byte_order,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_DIRECTORY_ENTRY_H ) */

