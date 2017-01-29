/*
 * Python object wrapper of libolecf_file_t
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

#if !defined( _PYOLECF_FILE_H )
#define _PYOLECF_FILE_H

#include <common.h>
#include <types.h>

#include "pyolecf_libbfio.h"
#include "pyolecf_libolecf.h"
#include "pyolecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyolecf_file pyolecf_file_t;

struct pyolecf_file
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libolecf file
	 */
	libolecf_file_t *file;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pyolecf_file_object_methods[];
extern PyTypeObject pyolecf_file_type_object;

PyObject *pyolecf_file_new(
           void );

PyObject *pyolecf_file_new_open(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyolecf_file_new_open_file_object(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

int pyolecf_file_init(
     pyolecf_file_t *pyolecf_file );

void pyolecf_file_free(
      pyolecf_file_t *pyolecf_file );

PyObject *pyolecf_file_signal_abort(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments );

PyObject *pyolecf_file_open(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyolecf_file_open_file_object(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyolecf_file_close(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments );

PyObject *pyolecf_file_get_sector_size(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments );

PyObject *pyolecf_file_get_short_sector_size(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments );

PyObject *pyolecf_file_get_ascii_codepage(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments );

int pyolecf_file_set_ascii_codepage_from_string(
     pyolecf_file_t *pyolecf_file,
     const char *codepage_string );

PyObject *pyolecf_file_set_ascii_codepage(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments,
           PyObject *keywords );

int pyolecf_file_set_ascii_codepage_setter(
     pyolecf_file_t *pyolecf_file,
     PyObject *string_object,
     void *closure );

PyObject *pyolecf_file_get_format_version(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments );

PyObject *pyolecf_file_get_root_item(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments );

PyObject *pyolecf_file_get_item_by_path(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments,
           PyObject *keywords );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYOLECF_FILE_H ) */

