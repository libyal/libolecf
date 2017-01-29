/*
 * Python object definition of the libolecf item types
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

#if !defined( _PYOLECF_ITEM_TYPES_H )
#define _PYOLECF_ITEM_TYPES_H

#include <common.h>
#include <types.h>

#include "pyolecf_libolecf.h"
#include "pyolecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyolecf_item_types pyolecf_item_types_t;

struct pyolecf_item_types
{
	/* Python object initialization
	 */
	PyObject_HEAD
};

extern PyTypeObject pyolecf_item_types_type_object;

int pyolecf_item_types_init_type(
     PyTypeObject *type_object );

PyObject *pyolecf_item_types_new(
           void );

int pyolecf_item_types_init(
     pyolecf_item_types_t *definitions_object );

void pyolecf_item_types_free(
      pyolecf_item_types_t *definitions_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYOLECF_ITEM_TYPES_H ) */

