/*
 * Python object definition of the libolecf item
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
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyolecf_datetime.h"
#include "pyolecf_error.h"
#include "pyolecf_file.h"
#include "pyolecf_integer.h"
#include "pyolecf_item.h"
#include "pyolecf_items.h"
#include "pyolecf_libcerror.h"
#include "pyolecf_libcstring.h"
#include "pyolecf_libolecf.h"
#include "pyolecf_property_set_stream.h"
#include "pyolecf_python.h"
#include "pyolecf_stream.h"
#include "pyolecf_unused.h"

PyMethodDef pyolecf_item_object_methods[] = {

	/* Functions to access the item values */

	{ "get_name",
	  (PyCFunction) pyolecf_item_get_name,
	  METH_NOARGS,
	  "get_name -> Unicode string or None\n"
	  "\n"
	  "Retrieves the name" },

	{ "get_size",
	  (PyCFunction) pyolecf_item_get_size,
	  METH_NOARGS,
	  "get_size() -> Integer\n"
	  "\n"
	  "Retrieves the size of the item data." },

	{ "get_creation_time",
	  (PyCFunction) pyolecf_item_get_creation_time,
	  METH_NOARGS,
	  "get_creation_time() -> Datetime\n"
	  "\n"
	  "Returns the creation date and time" },

	{ "get_creation_time_as_integer",
	  (PyCFunction) pyolecf_item_get_creation_time_as_integer,
	  METH_NOARGS,
	  "get_creation_time_as_integer() -> Integer\n"
	  "\n"
	  "Returns the creation date and time as a 64-bit integer containing a FILETIME value" },

	{ "get_modification_time",
	  (PyCFunction) pyolecf_item_get_modification_time,
	  METH_NOARGS,
	  "get_modification_time() -> Datetime\n"
	  "\n"
	  "Returns the modification date and time" },

	{ "get_modification_time_as_integer",
	  (PyCFunction) pyolecf_item_get_modification_time_as_integer,
	  METH_NOARGS,
	  "get_modification_time_as_integer() -> Integer\n"
	  "\n"
	  "Returns the modification date and time as a 64-bit integer containing a FILETIME value" },

	/* Functions to access the sub items */

	{ "get_number_of_sub_items",
	  (PyCFunction) pyolecf_item_get_number_of_sub_items,
	  METH_NOARGS,
	  "get_number_of_sub_items() -> Integer\n"
	  "\n"
	  "Retrieves the number of sub items" },

	{ "get_sub_item",
	  (PyCFunction) pyolecf_item_get_sub_item,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_sub_item(index) -> Object or None\n"
	  "\n"
	  "Retrieves a specific sub item" },

	{ "get_sub_item_by_name",
	  (PyCFunction) pyolecf_item_get_sub_item_by_name,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_sub_item_by_name(name) -> Object or None\n"
	  "\n"
	  "Retrieves a sub item specified by the sub item name" },

	{ "get_sub_item_by_path",
	  (PyCFunction) pyolecf_item_get_sub_item_by_path,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_sub_item_by_path(path) -> Object or None\n"
	  "\n"
	  "Retrieves a sub item specified by the sub item path" },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyolecf_item_object_get_set_definitions[] = {

	{ "name",
	  (getter) pyolecf_item_get_name,
	  (setter) 0,
	  "The name",
	  NULL },

	{ "size",
	  (getter) pyolecf_item_get_size,
	  (setter) 0,
	  "The size of the item data.",
	  NULL },

	{ "creation_time",
	  (getter) pyolecf_item_get_creation_time,
	  (setter) 0,
	  "The creation date and time",
	  NULL },

	{ "modification_time",
	  (getter) pyolecf_item_get_modification_time,
	  (setter) 0,
	  "The modification date and time",
	  NULL },

	{ "number_of_sub_items",
	  (getter) pyolecf_item_get_number_of_sub_items,
	  (setter) 0,
	  "The number of sub items",
	  NULL },

	{ "sub_items",
	  (getter) pyolecf_item_get_sub_items,
	  (setter) 0,
	  "The sub items",
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
           pyolecf_file_t *file_object )
{
	pyolecf_item_t *pyolecf_item = NULL;
	static char *function        = "pyolecf_item_new";

	if( item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
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
	if( pyolecf_item_init(
	     pyolecf_item ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize item.",
		 function );

		goto on_error;
	}
	pyolecf_item->item        = item;
	pyolecf_item->file_object = file_object;

	Py_IncRef(
	 (PyObject *) pyolecf_item->file_object );

	return( (PyObject *) pyolecf_item );

on_error:
	if( pyolecf_item != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyolecf_item );
	}
	return( NULL );
}

/* Intializes an item object
 * Returns 0 if successful or -1 on error
 */
int pyolecf_item_init(
     pyolecf_item_t *pyolecf_item )
{
	static char *function = "pyolecf_item_init";

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	/* Make sure libolecf item is set to NULL
	 */
	pyolecf_item->item = NULL;

	return( 0 );
}

/* Frees an item object
 */
void pyolecf_item_free(
      pyolecf_item_t *pyolecf_item )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyolecf_item_free";

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return;
	}
	if( pyolecf_item->item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item - missing libolecf item.",
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
	if( libolecf_item_free(
	     &( pyolecf_item->item ),
	     &error ) != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to free libolecf item.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pyolecf_item->file_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyolecf_item->file_object );
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
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	const char *errors       = NULL;
	uint8_t *name            = NULL;
	static char *function    = "pyolecf_item_get_name";
	size_t name_size         = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_utf8_name_size(
	          pyolecf_item->item,
	          &name_size,
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

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( name_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	name = (uint8_t *) PyMem_Malloc(
	                    sizeof( uint8_t ) * name_size );

	if( name == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create name.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_utf8_name(
		  pyolecf_item->item,
		  name,
		  name_size,
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

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) name,
			 (Py_ssize_t) name_size - 1,
			 errors );

	PyMem_Free(
	 name );

	return( string_object );

on_error:
	if( name != NULL )
	{
		PyMem_Free(
		 name );
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
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyolecf_item_get_size";
	uint32_t size            = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_size(
	          pyolecf_item->item,
	          &size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: failed to retrieve size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pyolecf_integer_unsigned_new_from_64bit(
	                  (uint64_t) size );

	return( integer_object );
}

/* Retrieves the creation date and time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_creation_time(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error   = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pyolecf_item_get_creation_time";
	uint64_t filetime          = 0;
	int result                 = 0;

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

	if( result != 1 )
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
	date_time_object = pyolecf_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the creation date and time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_creation_time_as_integer(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
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

	if( result != 1 )
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
	integer_object = pyolecf_integer_unsigned_new_from_64bit(
	                  filetime );

	return( integer_object );
}

/* Retrieves the modification date and time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_modification_time(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error   = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pyolecf_item_get_modification_time";
	uint64_t filetime          = 0;
	int result                 = 0;

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

	if( result != 1 )
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
	date_time_object = pyolecf_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the modification date and time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_modification_time_as_integer(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
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

	if( result != 1 )
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
	integer_object = pyolecf_integer_unsigned_new_from_64bit(
	                  filetime );

	return( integer_object );
}

/* Retrieves the number of sub items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_number_of_sub_items(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyolecf_item_get_number_of_sub_items";
	int number_of_sub_items  = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
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

/* Retrieves a specific sub item by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_sub_item_by_index(
           pyolecf_item_t *pyolecf_item,
           int sub_item_index )
{
	char error_string[ PYOLECF_ERROR_STRING_SIZE ];
	uint8_t name[ 32 ];

	libcerror_error_t *error  = NULL;
	libolecf_item_t *sub_item = NULL;
	PyObject *item_object     = NULL;
	PyTypeObject *type_object = NULL;
	static char *function     = "pyolecf_item_get_sub_item_by_index";
	size_t name_size          = 0;
	uint8_t sub_item_type     = 0;
	int result                = 0;

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_sub_item(
	          pyolecf_item->item,
	          sub_item_index,
	          &sub_item,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYOLECF_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve sub item: %d.",
			 function,
			 sub_item_index );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve sub item: %d.\n%s",
			 function,
			 sub_item_index,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_type(
	          sub_item,
	          &sub_item_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYOLECF_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve sub item type: %d.",
			 function,
			 sub_item_index );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve sub item type: %d.\n%s",
			 function,
			 sub_item_index,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	switch( sub_item_type )
	{
		case LIBOLECF_ITEM_TYPE_STREAM:
			type_object = &pyolecf_stream_type_object;
			break;

		default:
			type_object = &pyolecf_item_type_object;
			break;
	}
	if( sub_item_type == LIBOLECF_ITEM_TYPE_STREAM )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libolecf_item_get_utf8_name_size(
		          sub_item,
		          &name_size,
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

			goto on_error;
		}
		if( ( name_size == 20 )
		 || ( name_size == 28 ) )
		{
			Py_BEGIN_ALLOW_THREADS

			result = libolecf_item_get_utf8_name(
				  sub_item,
				  name,
				  name_size,
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

				goto on_error;
			}
			if( ( name_size == 20 )
			 && ( memory_compare(
			       (uint8_t *) "\005SummaryInformation",
			       name,
			       19 ) == 0 ) )
			{
				type_object = &pyolecf_property_set_stream_type_object;
			}
			else if( ( name_size == 28 )
			      && ( memory_compare(
				    (uint8_t *) "\005DocumentSummaryInformation",
				    name,
				    27 ) == 0 ) )
			{
				type_object = &pyolecf_property_set_stream_type_object;
			}
		}
	}
	item_object = pyolecf_item_new(
	               type_object,
	               sub_item,
	               pyolecf_item->file_object );

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
	              pyolecf_item,
	              sub_item_index );

	return( item_object );
}

/* Retrieves a items sequence and iterator object for the sub items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_sub_items(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error   = NULL;
	PyObject *sub_items_object = NULL;
	static char *function      = "pyolecf_item_get_sub_items";
	int number_of_sub_items    = 0;
	int result                 = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
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
	sub_items_object = pyolecf_items_new(
	                    pyolecf_item,
	                    &pyolecf_item_get_sub_item_by_index,
	                    number_of_sub_items );

	if( sub_items_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create sub items object.",
		 function );

		return( NULL );
	}
	return( sub_items_object );
}

/* Retrieves the sub item specified by the name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_item_get_sub_item_by_name(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments,
           PyObject *keywords )
{
	uint8_t name[ 32 ];

	libcerror_error_t *error    = NULL;
	libolecf_item_t *sub_item   = NULL;
	PyObject *item_object       = NULL;
	PyTypeObject *type_object   = NULL;
	char *sub_item_name         = NULL;
	static char *keyword_list[] = { "sub_item_name", NULL };
	static char *function       = "pyolecf_item_get_sub_item_by_name";
	size_t name_size            = 0;
	size_t sub_item_name_length = 0;
	uint8_t sub_item_type       = 0;
	int result                  = 0;

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s",
	     keyword_list,
	     &sub_item_name ) == 0 )
	{
		goto on_error;
	}
	sub_item_name_length = libcstring_narrow_string_length(
	                        sub_item_name );

	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_sub_item_by_utf8_name(
	           pyolecf_item->item,
	           (uint8_t *) sub_item_name,
	           sub_item_name_length,
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
	/* Check if the sub item is present
	 */
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_type(
	          sub_item,
	          &sub_item_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve sub item type.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	switch( sub_item_type )
	{
		case LIBOLECF_ITEM_TYPE_STREAM:
			type_object = &pyolecf_stream_type_object;
			break;

		default:
			type_object = &pyolecf_item_type_object;
			break;
	}
	if( sub_item_type == LIBOLECF_ITEM_TYPE_STREAM )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libolecf_item_get_utf8_name_size(
		          sub_item,
		          &name_size,
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

			goto on_error;
		}
		if( ( name_size == 20 )
		 || ( name_size == 28 ) )
		{
			Py_BEGIN_ALLOW_THREADS

			result = libolecf_item_get_utf8_name(
				  sub_item,
				  name,
				  name_size,
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

				goto on_error;
			}
			if( ( name_size == 20 )
			 && ( memory_compare(
			       (uint8_t *) "\005SummaryInformation",
			       name,
			       19 ) == 0 ) )
			{
				type_object = &pyolecf_property_set_stream_type_object;
			}
			else if( ( name_size == 28 )
			      && ( memory_compare(
				    (uint8_t *) "\005DocumentSummaryInformation",
				    name,
				    27 ) == 0 ) )
			{
				type_object = &pyolecf_property_set_stream_type_object;
			}
		}
	}
	item_object = pyolecf_item_new(
	               type_object,
	               sub_item,
	               pyolecf_item->file_object );

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
	uint8_t name[ 32 ];

	libcerror_error_t *error    = NULL;
	libolecf_item_t *sub_item   = NULL;
	PyObject *item_object       = NULL;
	PyTypeObject *type_object   = NULL;
	char *sub_item_path         = NULL;
	static char *keyword_list[] = { "sub_item_path", NULL };
	static char *function       = "pyolecf_item_get_sub_item_by_path";
	size_t name_size            = 0;
	size_t sub_item_path_length = 0;
	uint8_t sub_item_type       = 0;
	int result                  = 0;

	if( pyolecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s",
	     keyword_list,
	     &sub_item_path ) == 0 )
	{
		goto on_error;
	}
	sub_item_path_length = libcstring_narrow_string_length(
	                        sub_item_path );

	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_sub_item_by_utf8_path(
	           pyolecf_item->item,
	           (uint8_t *) sub_item_path,
	           sub_item_path_length,
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
	/* Check if the sub item is present
	 */
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_item_get_type(
	          sub_item,
	          &sub_item_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve sub item type.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	switch( sub_item_type )
	{
		case LIBOLECF_ITEM_TYPE_STREAM:
			type_object = &pyolecf_stream_type_object;
			break;

		default:
			type_object = &pyolecf_item_type_object;
			break;
	}
	if( sub_item_type == LIBOLECF_ITEM_TYPE_STREAM )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libolecf_item_get_utf8_name_size(
		          sub_item,
		          &name_size,
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

			goto on_error;
		}
		if( ( name_size == 20 )
		 || ( name_size == 28 ) )
		{
			Py_BEGIN_ALLOW_THREADS

			result = libolecf_item_get_utf8_name(
				  sub_item,
				  name,
				  name_size,
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

				goto on_error;
			}
			if( ( name_size == 20 )
			 && ( memory_compare(
			       (uint8_t *) "\005SummaryInformation",
			       name,
			       19 ) == 0 ) )
			{
				type_object = &pyolecf_property_set_stream_type_object;
			}
			else if( ( name_size == 28 )
			      && ( memory_compare(
				    (uint8_t *) "\005DocumentSummaryInformation",
				    name,
				    27 ) == 0 ) )
			{
				type_object = &pyolecf_property_set_stream_type_object;
			}
		}
	}
	item_object = pyolecf_item_new(
	               type_object,
	               sub_item,
	               pyolecf_item->file_object );

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

