/*
 * Property set stream functions
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

#if !defined( _LIBOLECF_PROPERTY_SET_STREAM_H )
#define _LIBOLECF_PROPERTY_SET_STREAM_H

#include <common.h>
#include <types.h>

#include "libolecf_extern.h"
#include "libolecf_libcerror.h"
#include "libolecf_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBOLECF_EXTERN \
int libolecf_property_set_stream_get_set(
     libolecf_item_t *property_set_stream,
     libolecf_property_set_t **property_set,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_PROPERTY_SET_STREAM_H ) */

