/*
 * Python object definition of the sequence and iterator object of property sections
 *
 * Copyright (C) 2008-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYOLECF_PROPERTY_SECTIONS_H )
#define _PYOLECF_PROPERTY_SECTIONS_H

#include <common.h>
#include <types.h>

#include "pyolecf_libolecf.h"
#include "pyolecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyolecf_property_sections pyolecf_property_sections_t;

struct pyolecf_property_sections
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get property section by index callback function
	 */
	PyObject* (*get_property_section_by_index)(
	             PyObject *parent_object,
	             int property_section_index );

	/* The (current) property section index
	 */
	int property_section_index;

	/* The number of property sections
	 */
	int number_of_property_sections;
};

extern PyTypeObject pyolecf_property_sections_type_object;

PyObject *pyolecf_property_sections_new(
           PyObject *parent_object,
           PyObject* (*get_property_section_by_index)(
                        PyObject *parent_object,
                        int property_section_index ),
           int number_of_property_sections );

int pyolecf_property_sections_init(
     pyolecf_property_sections_t *pyolecf_property_sections );

void pyolecf_property_sections_free(
      pyolecf_property_sections_t *pyolecf_property_sections );

Py_ssize_t pyolecf_property_sections_len(
            pyolecf_property_sections_t *pyolecf_property_sections );

PyObject *pyolecf_property_sections_getitem(
           pyolecf_property_sections_t *pyolecf_property_sections,
           Py_ssize_t item_index );

PyObject *pyolecf_property_sections_iter(
           pyolecf_property_sections_t *pyolecf_property_sections );

PyObject *pyolecf_property_sections_iternext(
           pyolecf_property_sections_t *pyolecf_property_sections );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYOLECF_PROPERTY_SECTIONS_H ) */

