/*
 * Python object wrapper of libolecf_property_value_t
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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyolecf_datetime.h"
#include "pyolecf_error.h"
#include "pyolecf_integer.h"
#include "pyolecf_libcerror.h"
#include "pyolecf_libolecf.h"
#include "pyolecf_property_value.h"
#include "pyolecf_python.h"
#include "pyolecf_unused.h"

PyMethodDef pyolecf_property_value_object_methods[] = {

	{ "get_identifier",
	  (PyCFunction) pyolecf_property_value_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Integer or None\n"
	  "\n"
	  "Retrieves the identifier." },

	{ "get_value_type",
	  (PyCFunction) pyolecf_property_value_get_value_type,
	  METH_NOARGS,
	  "get_value_type() -> Integer or None\n"
	  "\n"
	  "Retrieves the value type." },

	/* Deprecated alias of value_type */

	{ "get_type",
	  (PyCFunction) pyolecf_property_value_get_value_type,
	  METH_NOARGS,
	  "get_type() -> Integer or None\n"
	  "\n"
	  "Retrieves the value type." },

	{ "get_data",
	  (PyCFunction) pyolecf_property_value_get_data,
	  METH_NOARGS,
	  "get_data() -> Binary string or None\n"
	  "\n"
	  "Retrieves the data." },

	{ "get_data_as_boolean",
	  (PyCFunction) pyolecf_property_value_get_data_as_boolean,
	  METH_NOARGS,
	  "get_data_as_boolean() -> Integer or None\n"
	  "\n"
	  "Retrieves the data as a boolean." },

	{ "get_data_as_integer",
	  (PyCFunction) pyolecf_property_value_get_data_as_integer,
	  METH_NOARGS,
	  "get_data_as_integer() -> Integer or None\n"
	  "\n"
	  "Retrieves the data as an integer." },

	{ "get_data_as_datetime",
	  (PyCFunction) pyolecf_property_value_get_data_as_datetime,
	  METH_NOARGS,
	  "get_data_as_datetime() -> Datetime or None\n"
	  "\n"
	  "Retrieves the data as a datetime object." },

	{ "get_data_as_string",
	  (PyCFunction) pyolecf_property_value_get_data_as_string,
	  METH_NOARGS,
	  "get_data_as_string() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the data as a string." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyolecf_property_value_object_get_set_definitions[] = {

	{ "identifier",
	  (getter) pyolecf_property_value_get_identifier,
	  (setter) 0,
	  "The identifier.",
	  NULL },

	{ "value_type",
	  (getter) pyolecf_property_value_get_value_type,
	  (setter) 0,
	  "The value type.",
	  NULL },

	/* Deprecated alias of value_type */

	{ "type",
	  (getter) pyolecf_property_value_get_value_type,
	  (setter) 0,
	  "The value type.",
	  NULL },

	{ "data",
	  (getter) pyolecf_property_value_get_data,
	  (setter) 0,
	  "The data.",
	  NULL },

	{ "data_as_boolean",
	  (getter) pyolecf_property_value_get_data_as_boolean,
	  (setter) 0,
	  "The data as a boolean.",
	  NULL },

	{ "data_as_integer",
	  (getter) pyolecf_property_value_get_data_as_integer,
	  (setter) 0,
	  "The data as an integer.",
	  NULL },

	{ "data_as_datetime",
	  (getter) pyolecf_property_value_get_data_as_datetime,
	  (setter) 0,
	  "The data as a datetime object.",
	  NULL },

	{ "data_as_string",
	  (getter) pyolecf_property_value_get_data_as_string,
	  (setter) 0,
	  "The data as a string.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyolecf_property_value_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyolecf.property_value",
	/* tp_basicsize */
	sizeof( pyolecf_property_value_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyolecf_property_value_free,
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
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyolecf property value object (wraps libolecf_property_value_t)",
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
	pyolecf_property_value_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyolecf_property_value_object_get_set_definitions,
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
	(initproc) pyolecf_property_value_init,
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

/* Creates a new property value object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_new(
           PyTypeObject *type_object,
           libolecf_property_value_t *property_value,
           PyObject *parent_object )
{
	pyolecf_property_value_t *pyolecf_property_value = NULL;
	static char *function                            = "pyolecf_property_value_new";

	if( property_value == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property value.",
		 function );

		return( NULL );
	}
	pyolecf_property_value = PyObject_New(
	                          struct pyolecf_property_value,
	                          type_object );

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize property value.",
		 function );

		goto on_error;
	}
	if( pyolecf_property_value_init(
	     pyolecf_property_value ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize property value.",
		 function );

		goto on_error;
	}
	pyolecf_property_value->property_value = property_value;
	pyolecf_property_value->parent_object  = parent_object;

	Py_IncRef(
	 (PyObject *) pyolecf_property_value->parent_object );

	return( (PyObject *) pyolecf_property_value );

on_error:
	if( pyolecf_property_value != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyolecf_property_value );
	}
	return( NULL );
}

/* Intializes a property value object
 * Returns 0 if successful or -1 on error
 */
int pyolecf_property_value_init(
     pyolecf_property_value_t *pyolecf_property_value )
{
	static char *function = "pyolecf_property_value_init";

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property value.",
		 function );

		return( -1 );
	}
	/* Make sure libolecf property value is set to NULL
	 */
	pyolecf_property_value->property_value = NULL;

	return( 0 );
}

/* Frees a property value object
 */
void pyolecf_property_value_free(
      pyolecf_property_value_t *pyolecf_property_value )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyolecf_property_value_free";
	int result                  = 0;

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property value.",
		 function );

		return;
	}
	if( pyolecf_property_value->property_value == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property value - missing libolecf property value.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyolecf_property_value );

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
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_free(
	          &( pyolecf_property_value->property_value ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to free libolecf property value.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pyolecf_property_value->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyolecf_property_value->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyolecf_property_value );
}

/* Retrieves the identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_get_identifier(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_property_value_get_identifier";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property value.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_identifier(
	          pyolecf_property_value->property_value,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

/* Retrieves the value type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_get_value_type(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_property_value_get_value_type";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property value.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_value_type(
	          pyolecf_property_value->property_value,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve value type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

/* Retrieves the data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_get_data(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *bytes_object   = NULL;
	libcerror_error_t *error = NULL;
	char *data               = NULL;
	static char *function    = "pyolecf_property_value_get_data";
	size_t data_size         = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property value.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_data_size(
	          pyolecf_property_value->property_value,
	          &data_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( data_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	data = (char *) PyMem_Malloc(
	                 sizeof( char ) * data_size );

	if( data == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_data(
	          pyolecf_property_value->property_value,
	          (uint8_t *) data,
	          data_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* This is a binary string so include the full size
	 */
#if PY_MAJOR_VERSION >= 3
	bytes_object = PyBytes_FromStringAndSize(
	                data,
	                (Py_ssize_t) data_size );
#else
	bytes_object = PyString_FromStringAndSize(
	                data,
	                (Py_ssize_t) data_size );
#endif
	if( bytes_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert data into Bytes object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 data );

	return( bytes_object );

on_error:
	if( data != NULL )
	{
		PyMem_Free(
		 data );
	}
	return( NULL );
}

/* Retrieves the data as a boolean value
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_get_data_as_boolean(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_property_value_get_data_as_boolean";
	uint8_t value_boolean    = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property value.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_data_as_boolean(
	          pyolecf_property_value->property_value,
	          &value_boolean,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve boolean value.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( value_boolean != 0x00 )
	{
		Py_IncRef(
		 Py_True );

		return( Py_True );
	}
	Py_IncRef(
	 Py_False );

	return( Py_False );
}

/* Retrieves the data as an integer value
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_get_data_as_integer(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_property_value_get_data_as_integer";
	uint64_t value_64bit     = 0;
	int64_t integer_value    = 0;
	uint32_t value_32bit     = 0;
	uint32_t value_type      = 0;
	uint16_t value_16bit     = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property value.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_value_type(
	          pyolecf_property_value->property_value,
	          &value_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve value type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	switch( value_type )
	{
		case LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_16BIT_UNSIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libolecf_property_value_get_data_as_16bit_integer(
			          pyolecf_property_value->property_value,
			          &value_16bit,
			          &error );

			Py_END_ALLOW_THREADS

			if( value_type == LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED )
			{
				/* Interpret the 16-bit value as signed
				 */
				integer_value = (int16_t) value_16bit;
			}
			else
			{
				integer_value = value_16bit;
			}
			break;

		case LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_32BIT_UNSIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libolecf_property_value_get_data_as_32bit_integer(
			          pyolecf_property_value->property_value,
			          &value_32bit,
			          &error );

			Py_END_ALLOW_THREADS

			if( value_type == LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED )
			{
				/* Interpret the 32-bit value as signed
				 */
				integer_value = (int32_t) value_32bit;
			}
			else
			{
				integer_value = value_32bit;
			}
			break;

		case LIBOLECF_VALUE_TYPE_INTEGER_64BIT_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_64BIT_UNSIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libolecf_property_value_get_data_as_64bit_integer(
			          pyolecf_property_value->property_value,
			          &value_64bit,
			          &error );

			Py_END_ALLOW_THREADS

			if( value_type == LIBOLECF_VALUE_TYPE_INTEGER_64BIT_SIGNED )
			{
				/* Interpret the 64-bit value as signed
				 */
				integer_value = (int64_t) value_64bit;
			}
			else
			{
				integer_value = value_64bit;
			}
			break;

		case LIBOLECF_VALUE_TYPE_FILETIME:
			Py_BEGIN_ALLOW_THREADS

			result = libolecf_property_value_get_data_as_filetime(
			          pyolecf_property_value->property_value,
			          &value_64bit,
			          &error );

			Py_END_ALLOW_THREADS

			integer_value = value_64bit;

			break;

		default:
			PyErr_Format(
			 PyExc_IOError,
			 "%s: value is not an integer type.",
			 function );

			return( NULL );
	}
	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve integer value.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	switch( value_type )
	{
		case LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_64BIT_SIGNED:
			integer_object = pyolecf_integer_signed_new_from_64bit(
			                  integer_value );
			break;

		case LIBOLECF_VALUE_TYPE_INTEGER_16BIT_UNSIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_32BIT_UNSIGNED:
		case LIBOLECF_VALUE_TYPE_INTEGER_64BIT_UNSIGNED:
		case LIBOLECF_VALUE_TYPE_FILETIME:
			integer_object = pyolecf_integer_unsigned_new_from_64bit(
			                  integer_value );
			break;
	}
	return( integer_object );
}

/* Retrieves the data as an datetime value
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_get_data_as_datetime(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *datetime_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyolecf_property_value_get_data_as_datetime";
	uint64_t value_64bit      = 0;
	uint32_t value_type       = 0;
	int result                = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property value.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_value_type(
	          pyolecf_property_value->property_value,
	          &value_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve value type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	switch( value_type )
	{
		case LIBOLECF_VALUE_TYPE_FILETIME:
			Py_BEGIN_ALLOW_THREADS

			result = libolecf_property_value_get_data_as_filetime(
			          pyolecf_property_value->property_value,
			          &value_64bit,
			          &error );

			Py_END_ALLOW_THREADS

			datetime_object = pyolecf_datetime_new_from_filetime(
			                   value_64bit );
			break;

		default:
			PyErr_Format(
			 PyExc_IOError,
			 "%s: value is not an datetime type.",
			 function );

			return( NULL );
	}
	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve datetime value.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( datetime_object );
}

/* Retrieves the data as a string
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_get_data_as_string(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	const char *errors       = NULL;
	static char *function    = "pyolecf_value_get_data_as_string";
	char *utf8_string        = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property value.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_data_as_utf8_string_size(
	          pyolecf_property_value->property_value,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of data as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( utf8_string_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	utf8_string = (char *) PyMem_Malloc(
	                        sizeof( char ) * utf8_string_size );

	if( utf8_string == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_data_as_utf8_string(
	          pyolecf_property_value->property_value,
	          (uint8_t *) utf8_string,
	          utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8 otherwise it makes
	 * the end of string character is part of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 utf8_string,
	                 (Py_ssize_t) utf8_string_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 string into Unicode object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 utf8_string );

	return( string_object );

on_error:
	if( utf8_string != NULL )
	{
		PyMem_Free(
		 utf8_string );
	}
	return( NULL );
}

