/*
 * Python object definition of the libolecf value types
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

#if !defined( _PYOLECF_VALUE_TYPES_H )
#define _PYOLECF_VALUE_TYPES_H

#include <common.h>
#include <types.h>

#include "pyolecf_libolecf.h"
#include "pyolecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyolecf_value_types pyolecf_value_types_t;

struct pyolecf_value_types
{
	/* Python object initialization
	 */
	PyObject_HEAD
};

extern PyTypeObject pyolecf_value_types_type_object;

int pyolecf_value_types_init_type(
     PyTypeObject *type_object );

PyObject *pyolecf_value_types_new(
           void );

int pyolecf_value_types_init(
     pyolecf_value_types_t *pyolecf_value_types );

void pyolecf_value_types_free(
      pyolecf_value_types_t *pyolecf_value_types );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYOLECF_VALUE_TYPES_H ) */

