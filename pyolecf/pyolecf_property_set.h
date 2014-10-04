/*
 * Python object definition of the libolecf property set
 *
 * Copyright (c) 2008-2014, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYOLECF_PROPERTY_SET_H )
#define _PYOLECF_PROPERTY_SET_H

#include <common.h>
#include <types.h>

#include "pyolecf_item.h"
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

	/* The pyolecf item object
	 */
	pyolecf_item_t *item_object;
};

extern PyMethodDef pyolecf_property_set_object_methods[];
extern PyTypeObject pyolecf_property_set_type_object;

PyObject *pyolecf_property_set_new(
           libolecf_property_set_t *property_set,
           pyolecf_item_t *item_object );

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
           pyolecf_property_set_t *pyolecf_property_set,
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

#endif
