/*
 * Python object wrapper of libolecf_property_value_t
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

#if !defined( _PYOLECF_PROPERTY_VALUE_H )
#define _PYOLECF_PROPERTY_VALUE_H

#include <common.h>
#include <types.h>

#include "pyolecf_libolecf.h"
#include "pyolecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyolecf_property_value pyolecf_property_value_t;

struct pyolecf_property_value
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libolecf property value
	 */
	libolecf_property_value_t *property_value;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyolecf_property_value_object_methods[];
extern PyTypeObject pyolecf_property_value_type_object;

PyObject *pyolecf_property_value_new(
           libolecf_property_value_t *property_value,
           PyObject *parent_object );

int pyolecf_property_value_init(
     pyolecf_property_value_t *pyolecf_property_value );

void pyolecf_property_value_free(
      pyolecf_property_value_t *pyolecf_property_value );

PyObject *pyolecf_property_value_get_identifier(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments );

PyObject *pyolecf_property_value_get_value_type(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments );

PyObject *pyolecf_property_value_get_data(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments );

PyObject *pyolecf_property_value_get_data_as_boolean(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments );

PyObject *pyolecf_property_value_get_data_as_integer(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments );

PyObject *pyolecf_property_value_get_data_as_datetime(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments );

PyObject *pyolecf_property_value_get_data_as_string(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYOLECF_PROPERTY_VALUE_H ) */

