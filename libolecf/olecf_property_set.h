/*
 * The property set
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

#if !defined( _OLECF_PROPERTY_SET_H )
#define _OLECF_PROPERTY_SET_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct olecf_property_set_header olecf_property_set_header_t;

struct olecf_property_set_header
{
	/* Byte order
	 * Consists of 2 bytes
	 */
	uint8_t byte_order[ 2 ];

	/* Format
	 * Consists of 2 bytes
	 */
	uint8_t format[ 2 ];

	/* System version
	 * Consists of 4 bytes
	 */
	uint8_t system_version[ 4 ];

	/* Class identifier
	 * Consists of 16 bytes
	 */
	uint8_t class_identifier[ 16 ];

	/* The number of sections
	 * Consists of 4 bytes
	 */
	uint8_t number_of_sections[ 4 ];
};

typedef struct olecf_property_section_list_entry olecf_property_section_list_entry_t;

struct olecf_property_section_list_entry
{
	/* The class identifier
	 * Consists of 16 bytes
	 */
	uint8_t class_identifier[ 16 ];

	/* The section set offset
	 * The offset is relative from the start of the property set header
	 * Consists of 4 bytes
	 */
	uint8_t offset[ 4 ];
};

typedef struct olecf_property_section_header olecf_property_section_header_t;

struct olecf_property_section_header
{
	/* The (properties) data size
	 * Consists of 4 bytes
	 */
	uint8_t data_size[ 4 ];

	/* The number of properties
	 * Consists of 4 bytes
	 */
	uint8_t number_of_properties[ 4 ];
};

typedef struct olecf_property_set_property_list_entry olecf_property_set_property_list_entry_t;

struct olecf_property_set_property_list_entry
{
	/* The (property) identifier
	 * Consists of 4 bytes
	 */
	uint8_t identifier[ 4 ];

	/* The data offset
	 * The offset is relative from the start of the property set header
	 * Consists of 4 bytes
	 */
	uint8_t offset[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _OLECF_PROPERTY_SET_H ) */

