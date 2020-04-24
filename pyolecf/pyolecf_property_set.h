/*
 * Python object wrapper of libolecf_property_set_t
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

#if !defined( _PYOLECF_PROPERTY_SET_H )
#define _PYOLECF_PROPERTY_SET_H

#include <common.h>
#include <types.h>

#include "pyolecf_libolecf.h"
#include "pyolecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyolecf_property_set pyolecf_property_set_t;

struct pyolecf_property_set
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libolecf property set
	 */
	libolecf_property_set_t *property_set;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyolecf_property_set_object_methods[];
extern PyTypeObject pyolecf_property_set_type_object;

PyObject *pyolecf_property_set_new(
           libolecf_property_set_t *property_set,
           PyObject *parent_object );

int pyolecf_property_set_init(
     pyolecf_property_set_t *pyolecf_property_set );

void pyolecf_property_set_free(
      pyolecf_property_set_t *pyolecf_property_set );

PyObject *pyolecf_property_set_get_class_identifier(
           pyolecf_property_set_t *pyolecf_property_set,
           PyObject *arguments );

PyObject *pyolecf_property_set_get_number_of_sections(
           pyolecf_property_set_t *pyolecf_property_set,
           PyObject *arguments );

PyObject *pyolecf_property_set_get_section_by_index(
           PyObject *pyolecf_property_set,
           int section_index );

PyObject *pyolecf_property_set_get_section(
           pyolecf_property_set_t *pyolecf_property_set,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyolecf_property_set_get_sections(
           pyolecf_property_set_t *pyolecf_property_set,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYOLECF_PROPERTY_SET_H ) */

