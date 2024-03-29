/*
 * Python object definition of the libolecf stream
 *
 * Copyright (C) 2008-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYOLECF_STREAM_H )
#define _PYOLECF_STREAM_H

#include <common.h>
#include <types.h>

#include "pyolecf_item.h"
#include "pyolecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern PyMethodDef pyolecf_stream_object_methods[];
extern PyTypeObject pyolecf_stream_type_object;

PyObject *pyolecf_stream_read_buffer(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyolecf_stream_read_buffer_at_offset(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyolecf_stream_seek_offset(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyolecf_stream_get_offset(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYOLECF_STREAM_H ) */

