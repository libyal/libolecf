/*
 * Python object definition of the libolecf property set stream
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

#if !defined( _PYOLECF_PROPERTY_SET_STREAM_H )
#define _PYOLECF_PROPERTY_SET_STREAM_H

#include <common.h>
#include <types.h>

#include "pyolecf_item.h"
#include "pyolecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern PyMethodDef pyolecf_property_set_stream_object_methods[];
extern PyTypeObject pyolecf_property_set_stream_type_object;

PyObject *pyolecf_property_set_stream_get_set(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYOLECF_PROPERTY_SET_STREAM_H ) */

