/*
 * The directory list functions
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

#if !defined( _LIBOLECF_DIRECTORY_LIST_H )
#define _LIBOLECF_DIRECTORY_LIST_H

#include <common.h>
#include <types.h>

#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libolecf_directory_list_get_element_by_identifier(
     libcdata_list_t *directory_entry_list,
     uint32_t directory_entry_identifier,
     libolecf_directory_entry_t **directory_entry,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_DIRECTORY_LIST_H ) */

