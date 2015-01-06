/*
 * Python object definition of the libolecf property value
 *
 * Copyright (C) 2008-2015, Joachim Metz <joachim.metz@gmail.com>
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

#include "pyolecf_error.h"
#include "pyolecf_guid.h"
#include "pyolecf_integer.h"
#include "pyolecf_libcerror.h"
#include "pyolecf_libcstring.h"
#include "pyolecf_libolecf.h"
#include "pyolecf_property_section.h"
#include "pyolecf_property_value.h"
#include "pyolecf_python.h"
#include "pyolecf_unused.h"

PyMethodDef pyolecf_property_value_object_methods[] = {

	/* Functions to access the property value values */

	{ "get_identifier",
	  (PyCFunction) pyolecf_property_value_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Integer\n"
	  "\n"
	  "Retrieves the identifier." },

	{ "get_type",
	  (PyCFunction) pyolecf_property_value_get_type,
	  METH_NOARGS,
	  "get_type() -> Integer\n"
	  "\n"
	  "Retrieves the type." },

	{ "get_data",
	  (PyCFunction) pyolecf_property_value_get_data,
	  METH_NOARGS,
	  "get_name -> String or None\n"
	  "\n"
	  "Retrieves the data as a binary string." },

	{ "get_data_as_boolean",
	  (PyCFunction) pyolecf_property_value_get_data_as_boolean,
	  METH_NOARGS,
	  "get_data_as_boolean -> Boolean\n"
	  "\n"
	  "Retrieves the data as a boolean." },

	{ "get_data_as_integer",
	  (PyCFunction) pyolecf_property_value_get_data_as_integer,
	  METH_NOARGS,
	  "get_data_as_integer -> Integer\n"
	  "\n"
	  "Retrieves the data as an integer." },

	{ "get_data_as_string",
	  (PyCFunction) pyolecf_property_value_get_data_as_string,
	  METH_NOARGS,
	  "get_data_as_string -> Unicode string or None\n"
	  "\n"
	  "Retrieves the data as a string." },

	/* Functions to access the values */

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyolecf_property_value_object_get_set_definitions[] = {

	{ "identifier",
	  (getter) pyolecf_property_value_get_identifier,
	  (setter) 0,
	  "The identifier.",
	  NULL },

	{ "type",
	  (getter) pyolecf_property_value_get_type,
	  (setter) 0,
	  "The type.",
	  NULL },

	{ "data",
	  (getter) pyolecf_property_value_get_data,
	  (setter) 0,
	  "The data.",
	  NULL },

	{ "data_as_boolean",
	  (getter) pyolecf_property_value_get_data_as_boolean,
	  (setter) 0,
	  "The data represented as a boolean.",
	  NULL },

	{ "data_as_integer",
	  (getter) pyolecf_property_value_get_data_as_integer,
	  (setter) 0,
	  "The data represented as an integer.",
	  NULL },

	{ "data_as_string",
	  (getter) pyolecf_property_value_get_data_as_string,
	  (setter) 0,
	  "The data represented as a string.",
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
           libolecf_property_value_t *property_value,
           pyolecf_property_section_t *property_section_object )
{
	pyolecf_property_value_t *pyolecf_property_value = NULL;
	static char *function                            = "pyolecf_property_value_new";

	if( property_value == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid property value.",
		 function );

		return( NULL );
	}
	pyolecf_property_value = PyObject_New(
	                          struct pyolecf_property_value,
	                          &pyolecf_property_value_type_object );

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
	pyolecf_property_value->property_value          = property_value;
	pyolecf_property_value->property_section_object = property_section_object;

	Py_IncRef(
	 (PyObject *) pyolecf_property_value->property_section_object );

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
		 PyExc_TypeError,
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
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyolecf_property_value_free";

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid property value.",
		 function );

		return;
	}
	if( pyolecf_property_value->property_value == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
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
	if( libolecf_property_value_free(
	     &( pyolecf_property_value->property_value ),
	     &error ) != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to free libolecf property value.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pyolecf_property_value->property_section_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyolecf_property_value->property_section_object );
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
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyolecf_property_value_get_identifier";
	uint32_t identifier      = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid property value.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_identifier(
	          pyolecf_property_value->property_value,
	          &identifier,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
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
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) identifier );
#else
	integer_object = PyInt_FromLong(
	                  (long) identifier );
#endif
	return( integer_object );
}

/* Retrieves the type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_get_type(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyolecf_property_value_get_type";
	uint32_t type            = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid property value.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_value_type(
	          pyolecf_property_value->property_value,
	          &type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) type );
#else
	integer_object = PyInt_FromLong(
	                  (long) type );
#endif
	return( integer_object );
}

/* Retrieves the data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_get_data(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	uint8_t *data            = NULL;
	static char *function    = "pyolecf_property_value_get_data";
	size_t data_size         = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid property value.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_value_data_size(
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
	data = (uint8_t *) PyMem_Malloc(
	                    sizeof( uint8_t ) * data_size );

	if( data == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_value_data(
		  pyolecf_property_value->property_value,
		  data,
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
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
			 (char *) data,
			 (Py_ssize_t) data_size );
#else
	string_object = PyString_FromStringAndSize(
			 (char *) data,
			 (Py_ssize_t) data_size );
#endif
	PyMem_Free(
	 data );

	return( string_object );

on_error:
	if( data != NULL )
	{
		PyMem_Free(
		 data );
	}
	return( NULL );
}

/* Retrieves the data represented as a boolean
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_get_data_as_boolean(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *boolean_object = NULL;
	static char *function    = "pyolecf_property_value_get_data_as_boolean";
	uint32_t value_type      = 0;
	uint8_t boolean_value    = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid proverty value.",
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
		 "%s: unable to retrieve property value type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	switch( value_type )
	{
		case LIBOLECF_VALUE_TYPE_BOOLEAN:
			Py_BEGIN_ALLOW_THREADS

			result = libolecf_property_value_get_value_boolean(
				  pyolecf_property_value->property_value,
				  &boolean_value,
				  &error );

			Py_END_ALLOW_THREADS

			break;

		default:
			PyErr_Format(
			 PyExc_IOError,
			 "%s: value is not a boolean type.",
			 function );

			return( NULL );
	}
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
	if( boolean_value == 0x00 )
	{
		boolean_object = Py_False;
	}
	else
	{
		boolean_object = Py_True;
	}
	Py_IncRef(
	 boolean_object );

	return( boolean_object );
}

/* Retrieves the data represented as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_get_data_as_integer(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
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
		 PyExc_TypeError,
		 "%s: invalid proverty value.",
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
		 "%s: unable to retrieve property value type.",
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

			result = libolecf_property_value_get_value_16bit(
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

			result = libolecf_property_value_get_value_32bit(
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

			result = libolecf_property_value_get_value_64bit(
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

			result = libolecf_property_value_get_value_filetime(
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

/* Retrieves the data represented as a string
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_value_get_data_as_string(
           pyolecf_property_value_t *pyolecf_property_value,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	const char *errors       = NULL;
	uint8_t *value_string    = NULL;
	static char *function    = "pyolecf_value_get_data_as_string";
	size_t value_string_size = 0;
	uint32_t value_type      = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_value == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
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
	if( ( value_type != LIBOLECF_VALUE_TYPE_STRING_ASCII )
	 && ( value_type != LIBOLECF_VALUE_TYPE_STRING_UNICODE ) )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: value is not a string type.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_value_utf8_string_size(
	          pyolecf_property_value->property_value,
	          &value_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve value string size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( value_string_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	value_string = (uint8_t *) PyMem_Malloc(
	                            sizeof( uint8_t ) * value_string_size );

	if( value_string == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create value string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_value_get_value_utf8_string(
		  pyolecf_property_value->property_value,
		  value_string,
		  value_string_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve value string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) value_string,
			 (Py_ssize_t) value_string_size - 1,
			 errors );

	PyMem_Free(
	 value_string );

	return( string_object );

on_error:
	if( value_string != NULL )
	{
		PyMem_Free(
		 value_string );
	}
	return( NULL );
}

