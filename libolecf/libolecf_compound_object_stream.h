/*
 * Compound object stream functions
 *
 * Copyright (C) 2008-2022, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBOLECF_COMPOUND_OBJECT_STREAM_H )
#define _LIBOLECF_COMPOUND_OBJECT_STREAM_H

#include <common.h>
#include <types.h>

#include "libolecf_extern.h"
#include "libolecf_libcerror.h"
#include "libolecf_item.h"

#if defined( __cplusplus )
extern "C" {
#endif

/* TODO remove as external function */
LIBOLECF_EXTERN \
int libolecf_compound_object_stream_read(
     libolecf_item_t *stream,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_COMPOUND_OBJECT_STREAM_H ) */

