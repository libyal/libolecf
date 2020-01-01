/*
 * File header functions
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

#if !defined( _LIBOLECF_FILE_HEADER_H )
#define _LIBOLECF_FILE_HEADER_H

#include <common.h>
#include <types.h>

#include "libolecf_allocation_table.h"
#include "libolecf_libbfio.h"
#include "libolecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libolecf_file_header libolecf_file_header_t;

struct libolecf_file_header
{
	/* The byte order of the file data
	 */
	uint8_t byte_order;

	/* The major format version
	 */
	uint16_t major_format_version;

	/* The minor format version
	 */
	uint16_t minor_format_version;

	/* The minimum sector stream data size
	 */
	uint32_t sector_stream_minimum_data_size;

	/* The sector size
	 */
	size_t sector_size;

	/* The short-sector size
	 */
	size_t short_sector_size;

	/* The sector identifier of the MSAT
	 */
	uint32_t msat_sector_identifier;

	/* The number of sectors of the MSAT
	 */
	uint32_t number_of_msat_sectors;

	/* The number of sectors of the SAT
	 */
	uint32_t number_of_sat_sectors;

	/* The sector identifier of the SSAT
	 */
	uint32_t ssat_sector_identifier;

	/* The number of sectors of the SSAT
	 */
	uint32_t number_of_ssat_sectors;

	/* The sector identifier of the root directory
	 */
	uint32_t root_directory_sector_identifier;
};

int libolecf_file_header_initialize(
     libolecf_file_header_t **file_header,
     libcerror_error_t **error );

int libolecf_file_header_free(
     libolecf_file_header_t **file_header,
     libcerror_error_t **error );

int libolecf_file_header_read_data(
     libolecf_file_header_t *file_header,
     const uint8_t *data,
     size_t data_size,
     libolecf_allocation_table_t *msat,
     libcerror_error_t **error );

int libolecf_file_header_read_file_io_handle(
     libolecf_file_header_t *file_header,
     libbfio_handle_t *file_io_handle,
     libolecf_allocation_table_t *msat,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_FILE_HEADER_H ) */

