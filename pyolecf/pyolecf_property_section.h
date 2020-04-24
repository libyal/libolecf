/*
 * Python object wrapper of libolecf_property_section_t
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

#if !defined( _PYOLECF_PROPERTY_SECTION_H )
#define _PYOLECF_PROPERTY_SECTION_H

#include <common.h>
#include <types.h>

#include "pyolecf_libolecf.h"
#include "pyolecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyolecf_property_section pyolecf_property_section_t;

struct pyolecf_property_section
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libolecf property section
	 */
	libolecf_property_section_t *property_section;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyolecf_property_section_object_methods[];
extern PyTypeObject pyolecf_property_section_type_object;

PyObject *pyolecf_property_section_new(
           libolecf_property_section_t *property_section,
           PyObject *parent_object );

int pyolecf_property_section_init(
     pyolecf_property_section_t *pyolecf_property_section );

void pyolecf_property_section_free(
      pyolecf_property_section_t *pyolecf_property_section );

PyObject *pyolecf_property_section_get_class_identifier(
           pyolecf_property_section_t *pyolecf_property_section,
           PyObject *arguments );

PyObject *pyolecf_property_section_get_number_of_properties(
           pyolecf_property_section_t *pyolecf_property_section,
           PyObject *arguments );

PyObject *pyolecf_property_section_get_property_by_index(
           PyObject *pyolecf_property_section,
           int property_index );

PyObject *pyolecf_property_section_get_property(
           pyolecf_property_section_t *pyolecf_property_section,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyolecf_property_section_get_properties(
           pyolecf_property_section_t *pyolecf_property_section,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYOLECF_PROPERTY_SECTION_H ) */

