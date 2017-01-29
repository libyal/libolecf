/*
 * Python object definition of the libolecf value types
 *
 * Copyright (C) 2009-2017, Joachim Metz <joachim.metz@gmail.com>
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
	PyVarObject_HEAD_INIT( NULL, 0 )

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
	PyObject *value_object = NULL;

	if( type_object == NULL )
	{
		return( -1 );
	}
	type_object->tp_dict = PyDict_New();

	if( type_object->tp_dict == NULL )
	{
		return( -1 );
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_EMPTY );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_EMPTY );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "EMPTY",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_NULL );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_NULL );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "NULL",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_16BIT_SIGNED",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_32BIT_SIGNED",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_FLOAT_32BIT );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_FLOAT_32BIT );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "FLOAT_32BIT",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_DOUBLE_64BIT );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_DOUBLE_64BIT );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "DOUBLE_64BIT",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_CURRENCY );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_CURRENCY );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "CURRENCY",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_APPLICATION_TIME );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_APPLICATION_TIME );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "APPLICATION_TIME",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_BINARY_STRING );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_BINARY_STRING );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "BINARY_STRING",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_IDISPATCH );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_IDISPATCH );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "IDISPATCH",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_ERROR );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_ERROR );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "ERROR",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_BOOLEAN );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_BOOLEAN );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "BOOLEAN",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_VARIANT );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_VARIANT );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "VARIANT",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_IUNKNOWN );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_IUNKNOWN );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "IUNKNOWN",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_FIXED_POINT_128BIT );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_FIXED_POINT_128BIT );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "FIXED_POINT_128BIT",
	     value_object ) != 0 )
	{
		goto on_error;
	}

#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_8BIT_SIGNED );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_8BIT_SIGNED );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_8BIT_SIGNED",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_8BIT_UNSIGNED );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_8BIT_UNSIGNED );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_8BIT_UNSIGNED",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_16BIT_UNSIGNED );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_16BIT_UNSIGNED );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_16BIT_UNSIGNED",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_32BIT_UNSIGNED );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_32BIT_UNSIGNED );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_32BIT_UNSIGNED",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_64BIT_SIGNED );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_64BIT_SIGNED );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_64BIT_SIGNED",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_64BIT_UNSIGNED );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_64BIT_UNSIGNED );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_64BIT_UNSIGNED",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_SIGNED );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_SIGNED );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_SIGNED",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_UNSIGNED );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_INTEGER_UNSIGNED );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "INTEGER_UNSIGNED",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_VOID );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_VOID );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "VOID",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_HRESULT );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_HRESULT );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "HRESULT",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_POINTER );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_POINTER );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "POINTER",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_SAFE_ARRAY );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_SAFE_ARRAY );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "SAFE_ARRAY",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_ARRAY );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_ARRAY );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "ARRAY",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_USER_DEFINED );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_USER_DEFINED );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "USER_DEFINED",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_STRING_ASCII );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_STRING_ASCII );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "STRING_ASCII",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_STRING_UNICODE );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_STRING_UNICODE );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "STRING_UNICODE",
	     value_object ) != 0 )
	{
		goto on_error;
	}

#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_FILETIME );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_FILETIME );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "FILETIME",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_BINARY_DATA );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_BINARY_DATA );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "BINARY_DATA",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_STREAM );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_STREAM );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "STREAM",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_STORAGE );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_STORAGE );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "STORAGE",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_STREAMED_OBJECT );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_STREAMED_OBJECT );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "STREAMED_OBJECT",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_STORED_OBJECT );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_STORED_OBJECT );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "STORED_OBJECT",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_BINARY_DATA_OBJECT );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_BINARY_DATA_OBJECT );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "BINARY_DATA_OBJECT",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_CLIPBOARD_FORMAT );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_CLIPBOARD_FORMAT );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "CLIPBOARD_FORMAT",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_GUID );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_GUID );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "GUID",
	     value_object ) != 0 )
	{
		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                LIBOLECF_VALUE_TYPE_VERSIONED_STREAM );
#else
	value_object = PyInt_FromLong(
	                LIBOLECF_VALUE_TYPE_VERSIONED_STREAM );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "VERSIONED_STREAM",
	     value_object ) != 0 )
	{
		goto on_error;
	}

#if PY_MAJOR_VERSION >= 3
	value_object = PyLong_FromLong(
	                0x00001000UL );
#else
	value_object = PyInt_FromLong(
	                0x00001000UL );
#endif
	if( PyDict_SetItemString(
	     type_object->tp_dict,
	     "MULTI_VALUE",
	     value_object ) != 0 )
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
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyolecf_value_types_free";

	if( pyolecf_value_types == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid value types.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyolecf_value_types );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	ob_type->tp_free(
	 (PyObject*) pyolecf_value_types );
}

