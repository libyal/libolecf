/*
 * The compound object
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

#if !defined( _OLECF_COMPOUND_OBJECT_H )
#define _OLECF_COMPOUND_OBJECT_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct olecf_compound_object_header olecf_compound_object_header_t;

struct olecf_compound_object_header
{
	/* Reserved
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Version
	 * Consists of 4 bytes
	 */
	uint8_t version[ 4 ];

	/* Reserved
	 * Consists of 20 bytes
	 */
	uint8_t unknown2[ 20 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _OLECF_COMPOUND_OBJECT_H ) */

