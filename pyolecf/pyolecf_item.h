/*
 * Python object wrapper of libolecf_item_t
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

#if !defined( _PYOLECF_ITEM_H )
#define _PYOLECF_ITEM_H

#include <common.h>
#include <types.h>

#include "pyolecf_libolecf.h"
#include "pyolecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyolecf_item pyolecf_item_t;

struct pyolecf_item
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libolecf item
	 */
	libolecf_item_t *item;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyolecf_item_object_methods[];
extern PyTypeObject pyolecf_item_type_object;

PyObject *pyolecf_item_new(
           PyTypeObject *type_object,
           libolecf_item_t *item,
           PyObject *parent_object );

int pyolecf_item_init(
     pyolecf_item_t *pyolecf_item );

void pyolecf_item_free(
      pyolecf_item_t *pyolecf_item );

PyObject *pyolecf_item_get_name(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments );

PyObject *pyolecf_item_get_size(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments );

PyObject *pyolecf_item_get_creation_time(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments );

PyObject *pyolecf_item_get_creation_time_as_integer(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments );

PyObject *pyolecf_item_get_modification_time(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments );

PyObject *pyolecf_item_get_modification_time_as_integer(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments );

PyObject *pyolecf_item_get_number_of_sub_items(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments );

PyObject *pyolecf_item_get_sub_item_by_index(
           PyObject *pyolecf_item,
           int sub_item_index );

PyObject *pyolecf_item_get_sub_item(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyolecf_item_get_sub_items(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments );

PyObject *pyolecf_item_get_sub_item_by_name(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyolecf_item_get_sub_item_by_path(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments,
           PyObject *keywords );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYOLECF_ITEM_H ) */

