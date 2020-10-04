/*
 * Python object wrapper of libolecf_item_t
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

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyolecf_datetime.h"
#include "pyolecf_error.h"
#include "pyolecf_integer.h"
#include "pyolecf_item.h"
#include "pyolecf_items.h"
#include "pyolecf_libcerror.h"
#include "pyolecf_libolecf.h"
#include "pyolecf_property_set_stream.h"
#include "pyolecf_python.h"
#include "pyolecf_stream.h"
#include "pyolecf_unused.h"

PyMethodDef pyolecf_item_object_methods[] = {

	{ "get_name",
	  (PyCFunction) pyolecf_item_get_name,
	  METH_NOARGS,
	  "get_name() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the name." },

	{ "get_size",
	  (PyCFunction) pyolecf_item_get_size,
	  METH_NOARGS,
	  "get_size() -> Integer or None\n"
	  "\n"
	  "Retrieves the size." },

	{ "get_creation_time",
	  (PyCFunction) pyolecf_item_get_creation_time,
	  METH_NOARGS,
	  "get_creation_time() -> Datetime or None\n"
	  "\n"
	  "Retrieves the creation time." },

	{ "get_creation_time_as_integer",
	  (PyCFunction) pyolecf_item_get_creation_time_as_integer,
	  METH_NOARGS,
	  "get_creation_time_as_integer() -> Integer or None\n"
	  "\n"
	  "Retrieves the creation time as a 64-bit integer containing a FILETIME value." },

	{ "get_modification_time",
	  (PyCFunction) pyolecf_item_get_modification_time,
	  METH_NOARGS,
	  "get_modification_time() -> Datetime or None\n"
	  "\n"
	  "Retrieves the modification time." },

	{ "get_modification_time_as_integer",
	  (PyCFunction) pyolecf_item_get_modification_time_as_integer,
	  METH_NOARGS,
	  "get_modification_time_as_integer() -> Integer or None\n"
	  "\n"
	  "Retrieves the modification time as a 64-bit integer containing a FILETIME value." },

	{ "get_number_of_sub_items",
	  (PyCFunction) pyolecf_item_get_number_of_sub_items,
	  METH_NOARGS,
	  "get_number_of_sub_items() -> Integer or None\n"
	  "\n"
	  "Retrieves the number of sub items." },

	{ "get_sub_item",
	  (PyCFunction) pyolecf_item_get_sub_item,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_sub_item(sub_item_index) -> Object or None\n"
	  "\n"
	  "Retrieves the sub item specified by the index." },

	{ "get_sub_item_by_name",
	  (PyCFunction) pyolecf_item_get_sub_item_by_name,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_sub_item_by_name(name) -> Object or None\n"
	  "\n"
	  "Retrieves the sub item specified by the name." },

	{ "get_sub_item_by_path",
	  (PyCFunction) pyolecf_item_get_sub_item_by_path,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_sub_item_by_path(path) -> Object or None\n"
	  "\n"
	  "Retrieves the sub item specified by the path." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyolecf_item_object_get_set_definitions[] = {

	{ "name",
	  (getter) pyolecf_item_get_name,
	  (setter) 0,
	  "The name.",
	  NULL },

	{ "size",
	  (getter) pyolecf_item_get_size,
	  (setter) 0,
	  "The size.",
	  NULL },

	{ "creation_time",
	  (getter) pyolecf_item_get_creation_time,
	  (setter) 0,
	  "The creation time.",
	  NULL },

	{ "modification_time",
	  (getter) pyolecf_item_get_modification_time,
	  (setter) 0,
	  "The modification time.",
	  NULL },

	{ "number_of_sub_items",
	  (getter) pyolecf_item_get_number_of_sub_items,
	  (setter) 0,
	  "The number of sub items.",
	  NULL },

	{ "sub_items",
	  (getter) pyolecf_item_get_sub_items,
	  (setter) 0,
	  "The sub items.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyolecf_item_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyolecf.item",
	/* tp_basicsize */
	sizeof( pyolecf_item_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyolecf_item_free,
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
	"pyolecf item object (wraps libolecf_item_t)",
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
	pyolecf_item_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyolecf_item_object_get_set_definitions,
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
	(initproc) pyolecf_item_init,
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

/* Creates a new item object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_new(
           PyTypeObject *type_object,
           libolecf_item_t *item,
           PyObject *parent_object )
{
	pyolecf_item_t *pyolecf_item = NULL;
	static char *function        = "pyolecf_item_new";

	if( item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyolecf_item = PyObject_New(
	                struct pyolecf_item,
	                type_object );

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize item.",
		 function );

		goto on_error;
	}
	pyolecf_item->item          = item;
	pyolecf_item->parent_object = parent_object;

	if( pyolecf_item->parent_object != NULL )
	{
		Py_IncRef(
		 pyolecf_item->parent_object );
	}
	return( (PyObject *) pyolecf_item );

on_error:
	if( pyolecf_item != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyolecf_item );
	}
	return( NULL );
}

/* Initializes an item object
 * Returns 0 if successful or -1 on error
 */
int pyolecf_item_init(
     pyolecf_item_t *pyolecf_item )
{
	static char *function = "pyolecf_item_init";

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	/* Make sure libolecf item is set to NULL
	 */
	pyolecf_item->item = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of item not supported.",
	 function );

	return( -1 );
}

/* Frees an item object
 */
void pyolecf_item_free(
      pyolecf_item_t *pyolecf_item )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyolecf_item_free";
	int result                  = 0;

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyolecf_item );

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
	if( pyolecf_item->item != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libolecf_item_free(
		          &( pyolecf_item->item ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyolecf_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libolecf item.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyolecf_item->parent_object != NULL )
	{
		Py_DecRef(
		 pyolecf_item->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyolecf_item );
}

/* Retrieves the name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_name(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	const char *errors       = NULL;
	static char *function    = "pyolecf_item_get_name";
	char *utf8_string        = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_utf8_name_size(
	          pyolecf_item->item,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of name as UTF-8 string.",
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

	result = libolecf_item_get_utf8_name(
	          pyolecf_item->item,
	          (uint8_t *) utf8_string,
	          utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve name as UTF-8 string.",
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

/* Retrieves the size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_size(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_item_get_size";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_size(
	          pyolecf_item->item,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve size.",
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

/* Retrieves the creation time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_creation_time(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *datetime_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyolecf_item_get_creation_time";
	uint64_t filetime         = 0;
	int result                = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_creation_time(
	          pyolecf_item->item,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve creation time.",
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
	datetime_object = pyolecf_datetime_new_from_filetime(
	                   filetime );

	return( datetime_object );
}

/* Retrieves the creation time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_creation_time_as_integer(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_item_get_creation_time_as_integer";
	uint64_t filetime        = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_creation_time(
	          pyolecf_item->item,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve creation time.",
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
	integer_object = pyolecf_integer_unsigned_new_from_64bit(
	                  (uint64_t) filetime );

	return( integer_object );
}

/* Retrieves the modification time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_modification_time(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *datetime_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyolecf_item_get_modification_time";
	uint64_t filetime         = 0;
	int result                = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_modification_time(
	          pyolecf_item->item,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve modification time.",
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
	datetime_object = pyolecf_datetime_new_from_filetime(
	                   filetime );

	return( datetime_object );
}

/* Retrieves the modification time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_modification_time_as_integer(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_item_get_modification_time_as_integer";
	uint64_t filetime        = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_modification_time(
	          pyolecf_item->item,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve modification time.",
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
	integer_object = pyolecf_integer_unsigned_new_from_64bit(
	                  (uint64_t) filetime );

	return( integer_object );
}

/* Retrieves the number of sub items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_number_of_sub_items(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_item_get_number_of_sub_items";
	int number_of_sub_items  = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_number_of_sub_items(
	          pyolecf_item->item,
	          &number_of_sub_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of sub items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_sub_items );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_sub_items );
#endif
	return( integer_object );
}

/* Retrieves the item type object
 * Returns a Python type object if successful or NULL on error
 */
PyTypeObject *pyolecf_item_get_item_type_object(
               libolecf_item_t *item )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_item_get_item_type_object";
	size_t utf8_string_size  = 0;
	uint8_t item_type        = 0;
	int result               = 0;

	if( item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_type(
	          item,
	          &item_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve item type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( item_type == LIBOLECF_ITEM_TYPE_STREAM )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libolecf_item_get_utf8_name_size(
		          item,
		          &utf8_string_size,
		          &error );

		Py_END_ALLOW_THREADS

		if( result == -1 )
		{
			pyolecf_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to retrieve name size.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( ( utf8_string_size == 20 )
		 || ( utf8_string_size == 28 ) )
		{
			Py_BEGIN_ALLOW_THREADS

			result = libolecf_item_get_utf8_name(
			          item,
			          utf8_string,
			          utf8_string_size,
			          &error );

			Py_END_ALLOW_THREADS

			if( result != 1 )
			{
				pyolecf_error_raise(
				 error,
				 PyExc_IOError,
				 "%s: unable to retrieve name.",
				 function );

				libcerror_error_free(
				 &error );

				return( NULL );
			}
			if( utf8_string_size == 20 )
			{
				if( narrow_string_compare(
				     "\005SummaryInformation",
				     utf8_string,
				     19 ) == 0 )
				{
					return( &pyolecf_property_set_stream_type_object );
				}
			}
			else if( utf8_string_size == 28 )
			{
				if( narrow_string_compare(
				     "\005DocumentSummaryInformation",
				     utf8_string,
				     27 ) == 0 )
				{
					return( &pyolecf_property_set_stream_type_object );
				}
			}
		}
		return( &pyolecf_stream_type_object );
	}
	return( &pyolecf_item_type_object );
}

/* Retrieves a specific sub item by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_sub_item_by_index(
           PyObject *pyolecf_item,
           int sub_item_index )
{
	PyObject *item_object     = NULL;
	PyTypeObject *type_object = NULL;
	libcerror_error_t *error  = NULL;
	libolecf_item_t *sub_item = NULL;
	static char *function     = "pyolecf_item_get_sub_item_by_index";
	int result                = 0;

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_sub_item(
	          ( (pyolecf_item_t *) pyolecf_item )->item,
	          sub_item_index,
	          &sub_item,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve sub item: %d.",
		 function,
		 sub_item_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	type_object = pyolecf_item_get_item_type_object(
	               sub_item );

	if( type_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to retrieve item type object.",
		 function );

		goto on_error;
	}
	item_object = pyolecf_item_new(
	               type_object,
	               sub_item,
	               ( (pyolecf_item_t *) pyolecf_item )->parent_object );

	if( item_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create sub item object.",
		 function );

		goto on_error;
	}
	return( item_object );

on_error:
	if( sub_item != NULL )
	{
		libolecf_item_free(
		 &sub_item,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific sub item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_sub_item(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *item_object       = NULL;
	static char *keyword_list[] = { "sub_item_index", NULL };
	int sub_item_index          = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &sub_item_index ) == 0 )
	{
		return( NULL );
	}
	item_object = pyolecf_item_get_sub_item_by_index(
	               (PyObject *) pyolecf_item,
	               sub_item_index );

	return( item_object );
}

/* Retrieves a sequence and iterator object for the sub items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_sub_items(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyolecf_item_get_sub_items";
	int number_of_sub_items   = 0;
	int result                = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_number_of_sub_items(
	          pyolecf_item->item,
	          &number_of_sub_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of sub items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyolecf_items_new(
	                   (PyObject *) pyolecf_item,
	                   &pyolecf_item_get_sub_item_by_index,
	                   number_of_sub_items );

	if( sequence_object == NULL )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

/* Retrieves the sub item specified by the name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_sub_item_by_name(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *item_object       = NULL;
	PyTypeObject *type_object   = NULL;
	libcerror_error_t *error    = NULL;
	libolecf_item_t *sub_item   = NULL;
	static char *function       = "pyolecf_item_get_sub_item_by_name";
	static char *keyword_list[] = { "name", NULL };
	char *utf8_name             = NULL;
	size_t utf8_name_length     = 0;
	int result                  = 0;

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s",
	     keyword_list,
	     &utf8_name ) == 0 )
	{
		goto on_error;
	}
	utf8_name_length = narrow_string_length(
	                    utf8_name );

	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_sub_item_by_utf8_name(
	          pyolecf_item->item,
	          (uint8_t *) utf8_name,
	          utf8_name_length,
	          &sub_item,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve sub item.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	type_object = pyolecf_item_get_item_type_object(
	               sub_item );

	if( type_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to retrieve item type object.",
		 function );

		goto on_error;
	}
	item_object = pyolecf_item_new(
	               type_object,
	               sub_item,
	               pyolecf_item->parent_object );

	if( item_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create sub item object.",
		 function );

		goto on_error;
	}
	return( item_object );

on_error:
	if( sub_item != NULL )
	{
		libolecf_item_free(
		 &sub_item,
		 NULL );
	}
	return( NULL );
}

/* Retrieves the sub item specified by the path
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_sub_item_by_path(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *item_object       = NULL;
	PyTypeObject *type_object   = NULL;
	libcerror_error_t *error    = NULL;
	libolecf_item_t *sub_item   = NULL;
	static char *function       = "pyolecf_item_get_sub_item_by_path";
	static char *keyword_list[] = { "path", NULL };
	char *utf8_path             = NULL;
	size_t utf8_path_length     = 0;
	int result                  = 0;

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s",
	     keyword_list,
	     &utf8_path ) == 0 )
	{
		goto on_error;
	}
	utf8_path_length = narrow_string_length(
	                    utf8_path );

	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_sub_item_by_utf8_path(
	          pyolecf_item->item,
	          (uint8_t *) utf8_path,
	          utf8_path_length,
	          &sub_item,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve sub item.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	type_object = pyolecf_item_get_item_type_object(
	               sub_item );

	if( type_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to retrieve item type object.",
		 function );

		goto on_error;
	}
	item_object = pyolecf_item_new(
	               type_object,
	               sub_item,
	               pyolecf_item->parent_object );

	if( item_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create sub item object.",
		 function );

		goto on_error;
	}
	return( item_object );

on_error:
	if( sub_item != NULL )
	{
		libolecf_item_free(
		 &sub_item,
		 NULL );
	}
	return( NULL );
}

