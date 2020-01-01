/*
 * The file header definition
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

#if !defined( _OLECF_FILE_HEADER_H )
#define _OLECF_FILE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct olecf_file_header olecf_file_header_t;

struct olecf_file_header
{
	/* The magic signature of the OLECF compound file
	 * Consists of 8 bytes
	 * This should be 0xd0 0xcf 0x11 0xe0 0xa1 0xb1 0x1a 0xe1
	 * or 0x0e 0x11 0xfc 0x0d 0xd0 0xcf 0x11 0x0e
	 */
	uint8_t signature[ 8 ];

	/* The class identifier
	 * Consists of 16 bytes
	 */
	uint8_t class_identifier[ 16 ];

	/* The minor version of the OLECF format used
	 * Consists of 2 bytes
	 */
	uint8_t minor_format_version[ 2 ];

	/* The major verion of the OLECF format used
	 * also used refered to as DLL version
	 * Consists of 2 bytes
	 */
	uint8_t major_format_version[ 2 ];

	/* The byte order within the file
	 * 0xfffe indicates little endian
	 * 0xfeff indicates big endian
	 * Consists of 2 bytes
	 */
	uint8_t byte_order[ 2 ];

	/* The sector (block) size within the file
	 * also refered to as sector shift
	 * Consists of 2 bytes
	 * default is 9 indicating 2^9 = 512
	 */
	uint8_t sector_size[ 2 ];

	/* The short (mini) sector (block) size within the file
	 * also refered to as mini sector shift
	 * Consists of 2 bytes
	 * default is 6 indicating 2^6 = 64
	 */
	uint8_t short_sector_size [ 2 ];

	/* Reserved
	 * Consists of 2 bytes
	 * Should contain 0 bytes
	 */
	uint8_t reserved1[ 2 ];

	/* Reserved
	 * Consists of 4 bytes
	 * Should contain 0 bytes
	 */
	uint8_t reserved2[ 4 ];

	/* Reserved
	 * Consists of 4 bytes
	 * Should contain 0 bytes
	 */
	uint8_t reserved3[ 4 ];

	/* The number of SAT sectors
	 * Consists of 4 bytes
	 */
	uint8_t number_of_sat_sectors[ 4 ];

	/* The sector identifier of the sector that contains the root directory
	 * Consists of 4 bytes
	 */
	uint8_t root_directory_sector_identifier[ 4 ];

	/* Signature used for transactioning
	 * Consists of 4 bytes
	 */
	uint8_t transactioning_signature[ 4 ];

	/* The minimum data size in a sector stream
	 * otherwise a short-sector stream is used
	 * Consists of 4 bytes
	 */
	uint8_t sector_stream_minimum_data_size[ 4 ];

	/* The sector identifier of the sector that contains the first SSAT
	 * Consists of 4 bytes
	 */
	uint8_t ssat_sector_identifier[ 4 ];

	/* The number of SSAT sectors
	 * Consists of 4 bytes
	 */
	uint8_t number_of_ssat_sectors[ 4 ];

	/* The sector identifier of the sector that contains the first MSAT
	 * Consists of 4 bytes
	 */
	uint8_t msat_sector_identifier[ 4 ];

	/* The number of MSAT sectors
	 * Consists of 4 bytes
	 */
	uint8_t number_of_msat_sectors[ 4 ];

	/* The first 109 MSAT sector identifiers
	 * Consists of 436 bytes
	 */
	uint8_t msat[ 436 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _OLECF_FILE_HEADER_H ) */

