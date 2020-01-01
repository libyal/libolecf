/*
 * Input/Output (IO) handle functions
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

#if !defined( _LIBOLECF_IO_HANDLE_H )
#define _LIBOLECF_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libolecf_allocation_table.h"
#include "libolecf_directory_entry.h"
#include "libolecf_libbfio.h"
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint8_t olecf_file_signature[ 8 ];
extern const uint8_t olecf_beta_file_signature[ 8 ];

typedef struct libolecf_io_handle libolecf_io_handle_t;

struct libolecf_io_handle
{
	/* The major format version
	 */
	uint16_t major_format_version;

	/* The minor format version
	 */
	uint16_t minor_format_version;

	/* The sector size
	 */
	size_t sector_size;

	/* The short-sector size
	 */
	size_t short_sector_size;

	/* The minimum sector stream data size
	 */
	uint32_t sector_stream_minimum_data_size;

	/* The byte order of the file data
	 */
	uint8_t byte_order;

	/* The short sector stream start sector identifier
	 */
	uint32_t short_sector_stream_start_sector_identifier;

	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libolecf_io_handle_initialize(
     libolecf_io_handle_t **io_handle,
     libcerror_error_t **error );

int libolecf_io_handle_free(
     libolecf_io_handle_t **io_handle,
     libcerror_error_t **error );

int libolecf_io_handle_clear(
     libolecf_io_handle_t *io_handle,
     libcerror_error_t **error );

int libolecf_io_handle_read_msat(
     libolecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libolecf_allocation_table_t *msat,
     uint32_t msat_sector_identifier,
     uint32_t number_of_msat_sectors,
     libcerror_error_t **error );

int libolecf_io_handle_read_sat(
     libolecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libolecf_allocation_table_t *msat,
     libolecf_allocation_table_t *sat,
     uint32_t number_of_sat_sectors,
     libcerror_error_t **error );

int libolecf_io_handle_read_ssat(
     libolecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libolecf_allocation_table_t *sat,
     libolecf_allocation_table_t *ssat,
     uint32_t ssat_sector_identifier,
     uint32_t number_of_ssat_sectors,
     libcerror_error_t **error );

int libolecf_io_handle_read_directory_entries(
     libolecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libolecf_allocation_table_t *sat,
     libcdata_list_t *directory_entry_list,
     uint32_t root_directory_sector_identifier,
     libcerror_error_t **error );

ssize_t libolecf_io_handle_read_stream(
         libolecf_io_handle_t *io_handle,
         libbfio_handle_t *file_io_handle,
         libolecf_allocation_table_t *sat,
         libolecf_allocation_table_t *ssat,
         libolecf_directory_entry_t *directory_entry,
         off64_t *offset,
         uint8_t *buffer,
         size_t size,
         libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_IO_HANDLE_H ) */

