/*
 * Python object definition of the sequence and iterator object of items
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

#if !defined( _PYOLECF_ITEMS_H )
#define _PYOLECF_ITEMS_H

#include <common.h>
#include <types.h>

#include "pyolecf_libolecf.h"
#include "pyolecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyolecf_items pyolecf_items_t;

struct pyolecf_items
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pyolecf_items_type_object;

PyObject *pyolecf_items_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyolecf_items_init(
     pyolecf_items_t *items_object );

void pyolecf_items_free(
      pyolecf_items_t *items_object );

Py_ssize_t pyolecf_items_len(
            pyolecf_items_t *items_object );

PyObject *pyolecf_items_getitem(
           pyolecf_items_t *items_object,
           Py_ssize_t item_index );

PyObject *pyolecf_items_iter(
           pyolecf_items_t *items_object );

PyObject *pyolecf_items_iternext(
           pyolecf_items_t *items_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYOLECF_ITEMS_H ) */

