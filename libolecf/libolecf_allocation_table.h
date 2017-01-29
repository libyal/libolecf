/*
 * Allocation table functions
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

#if !defined( _LIBOLECF_ALLOCATION_TABLE_H )
#define _LIBOLECF_ALLOCATION_TABLE_H

#include <common.h>
#include <types.h>

#include "libolecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libolecf_allocation_table libolecf_allocation_table_t;

struct libolecf_allocation_table
{
	/* The number of sector identifiers
	 */
	int number_of_sector_identifiers;

	/* The sector identifiers
	 */
	uint32_t *sector_identifier;
};

int libolecf_allocation_table_initialize(
     libolecf_allocation_table_t **allocation_table,
     int number_of_sector_identifiers,
     libcerror_error_t **error );

int libolecf_allocation_table_free(
     libolecf_allocation_table_t **allocation_table,
     libcerror_error_t **error );

int libolecf_allocation_table_resize(
     libolecf_allocation_table_t *allocation_table,
     int number_of_sector_identifiers,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_ALLOCATION_TABLE_H ) */

