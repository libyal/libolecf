/*
 * Python object definition of the libolecf value types
 *
 * Copyright (C) 2009-2014, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyolecf_libolecf.h"
#include "pyolecf_python.h"
#include "pyolecf_unused.h"
#include "pyolecf_value_types.h"

PyTypeObject pyolecf_value_types_type_object = {
	PyObject_HEAD_INIT( NULL )

	/* ob_size */
	0,
	/* tp_name */
	"pyolecf.value_types",
	/* tp_basicsize */
	sizeof( pyolecf_value_types_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyolecf_value_types_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_types */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyolecf value types object (wraps LIBOLECF_VALUE_TYPES)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	0,
	/* tp_members */
	0,
	/* tp_getset */
	0,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyolecf_value_types_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Initializes the type object
 * Returns 1 if successful or -1 on error
 */
int pyolecf_value_types_init_type(
     PyTypeObject *type_object )
{
	if( type_object == NULL )
	{
		return( -1 );
	}
	type_object->tp_dict = PyDict_New();

	if( type_object->tp_dict == NULL )
	{
		return( -1 );
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "EMPTY",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_EMPTY ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "NULL",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_NULL ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_16BIT_SIGNED",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_32BIT_SIGNED",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "FLOAT_32BIT",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_FLOAT_32BIT ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "DOUBLE_64BIT",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_DOUBLE_64BIT ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "CURRENCY",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_CURRENCY ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "APPLICATION_TIME",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_APPLICATION_TIME ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "BINARY_STRING",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_BINARY_STRING ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "IDISPATCH",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_IDISPATCH ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "ERROR",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_ERROR ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "BOOLEAN",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_BOOLEAN ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "VARIANT",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_VARIANT ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "IUNKNOWN",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_IUNKNOWN ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "FIXED_POINT_128BIT",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_FIXED_POINT_128BIT ) ) != 0 )
	{
		goto on_error;
	}

	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_8BIT_SIGNED",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_INTEGER_8BIT_SIGNED ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_8BIT_UNSIGNED",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_INTEGER_8BIT_UNSIGNED ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_16BIT_UNSIGNED",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_INTEGER_16BIT_UNSIGNED ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_32BIT_UNSIGNED",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_INTEGER_32BIT_UNSIGNED ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_64BIT_SIGNED",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_INTEGER_64BIT_SIGNED ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_64BIT_UNSIGNED",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_INTEGER_64BIT_UNSIGNED ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_SIGNED",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_INTEGER_SIGNED ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_UNSIGNED",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_INTEGER_UNSIGNED ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "VOID",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_VOID ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "HRESULT",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_HRESULT ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "POINTER",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_POINTER ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "SAFE_ARRAY",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_SAFE_ARRAY ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "ARRAY",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_ARRAY ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "USER_DEFINED",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_USER_DEFINED ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "STRING_ASCII",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_STRING_ASCII ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "STRING_UNICODE",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_STRING_UNICODE ) ) != 0 )
	{
		goto on_error;
	}

	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "FILETIME",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_FILETIME ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "BINARY_DATA",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_BINARY_DATA ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "STREAM",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_STREAM ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "STORAGE",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_STORAGE ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "STREAMED_OBJECT",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_STREAMED_OBJECT ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "STORED_OBJECT",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_STORED_OBJECT ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "BINARY_DATA_OBJECT",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_BINARY_DATA_OBJECT ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "CLIPBOARD_FORMAT",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_CLIPBOARD_FORMAT ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "GUID",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_GUID ) ) != 0 )
	{
		goto on_error;
	}
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "VERSIONED_STREAM",
	     PyInt_FromLong(
	      LIBOLECF_VALUE_TYPE_VERSIONED_STREAM ) ) != 0 )
	{
		goto on_error;
	}

	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "MULTI_VALUE",
	     PyInt_FromLong(
	      0x00001000UL ) ) != 0 )
	{
		goto on_error;
	}
	return( 1 );

on_error:
	if( type_object->tp_dict != NULL )
	{
		Py_DecRef(
		 type_object->tp_dict );

		type_object->tp_dict = NULL;
	}
	return( -1 );
}

/* Creates a new value types object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_value_types_new(
           void )
{
	pyolecf_value_types_t *pyolecf_value_types = NULL;
	static char *function                      = "pyolecf_value_types_new";

	pyolecf_value_types = PyObject_New(
	                        struct pyolecf_value_types,
	                        &pyolecf_value_types_type_object );

	if( pyolecf_value_types == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize value types.",
		 function );

		goto on_error;
	}
	if( pyolecf_value_types_init(
	     pyolecf_value_types ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize value types.",
		 function );

		goto on_error;
	}
	return( (PyObject *) pyolecf_value_types );

on_error:
	if( pyolecf_value_types != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyolecf_value_types );
	}
	return( NULL );
}

/* Intializes a value types object
 * Returns 0 if successful or -1 on error
 */
int pyolecf_value_types_init(
     pyolecf_value_types_t *pyolecf_value_types )
{
	static char *function = "pyolecf_value_types_init";

	if( pyolecf_value_types == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid value types.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Frees a value types object
 */
void pyolecf_value_types_free(
      pyolecf_value_types_t *pyolecf_value_types )
{
	static char *function = "pyolecf_value_types_free";

	if( pyolecf_value_types == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid value types.",
		 function );

		return;
	}
	if( pyolecf_value_types->ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid value types - missing ob_type.",
		 function );

		return;
	}
	if( pyolecf_value_types->ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid value types - invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	pyolecf_value_types->ob_type->tp_free(
	 (PyObject*) pyolecf_value_types );
}

