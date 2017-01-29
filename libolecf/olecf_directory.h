/*
 * The directory definition
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

#if !defined( _OLECF_DIRECTORY_H )
#define _OLECF_DIRECTORY_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct olecf_directory_entry olecf_directory_entry_t;

struct olecf_directory_entry
{
	/* The directory name
	 * Consists of 64 bytes
	 */
 	uint8_t name[ 64 ];

	/* The size of the directory name data
	 * Consists of 2 bytes
	 */
	uint8_t name_data_size[ 2 ];

	/* The directory type
	 * Consists of 1 byte
	 */
	uint8_t type;

	/* The node color (red or black)
	 * the directory entry is part of a red or black tree
	 * Consists of 1 byte
	 */
	uint8_t node_color;

	/* The previous directory identifier
	 * Consists of 4 bytes
	 */
	uint8_t previous_directory_identifier[ 4 ];

	/* The next directory identifier
	 * Consists of 4 bytes
	 */
	uint8_t next_directory_identifier[ 4 ];

	/* The sub directory identifier
	 * Consists of 4 bytes
	 */
	uint8_t sub_directory_identifier[ 4 ];

	/* The class identifier
	 * Consists of 16 bytes
	 */
	uint8_t class_identifier[ 16 ];

	/* The user flags
	 * Consists of 4 bytes
	 */
	uint8_t user_flags[ 4 ];

	/* Creation time
	 * Consists of 8 bytes
	 */
	uint8_t creation_time[ 8 ];

	/* Modification time
	 * Consists of 8 bytes
	 */
	uint8_t modification_time[ 8 ];

	/* Sector identifier
	 * Consists of 4 bytes
	 */
	uint8_t sector_identifier[ 4 ];

	/* Directory size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* Reserved
	 * Consists of 4 bytes
	 */
	uint8_t reserved1[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _OLECF_DIRECTORY_H ) */

