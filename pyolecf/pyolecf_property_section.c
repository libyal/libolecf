/*
 * Python object wrapper of libolecf_property_section_t
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyolecf_error.h"
#include "pyolecf_guid.h"
#include "pyolecf_libcerror.h"
#include "pyolecf_libolecf.h"
#include "pyolecf_property_section.h"
#include "pyolecf_property_value.h"
#include "pyolecf_property_values.h"
#include "pyolecf_python.h"
#include "pyolecf_unused.h"

PyMethodDef pyolecf_property_section_object_methods[] = {

	{ "get_class_identifier",
	  (PyCFunction) pyolecf_property_section_get_class_identifier,
	  METH_NOARGS,
	  "get_class_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the class identifier." },

	{ "get_number_of_properties",
	  (PyCFunction) pyolecf_property_section_get_number_of_properties,
	  METH_NOARGS,
	  "get_number_of_properties() -> Integer or None\n"
	  "\n"
	  "Retrieves the number of properties." },

	{ "get_property",
	  (PyCFunction) pyolecf_property_section_get_property,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_property(property_index) -> Object or None\n"
	  "\n"
	  "Retrieves the property specified by the index." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyolecf_property_section_object_get_set_definitions[] = {

	{ "class_identifier",
	  (getter) pyolecf_property_section_get_class_identifier,
	  (setter) 0,
	  "The class identifier.",
	  NULL },

	{ "number_of_properties",
	  (getter) pyolecf_property_section_get_number_of_properties,
	  (setter) 0,
	  "The number of properties.",
	  NULL },

	{ "properties",
	  (getter) pyolecf_property_section_get_properties,
	  (setter) 0,
	  "The properties.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyolecf_property_section_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyolecf.property_section",
	/* tp_basicsize */
	sizeof( pyolecf_property_section_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyolecf_property_section_free,
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
	"pyolecf property section object (wraps libolecf_property_section_t)",
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
	pyolecf_property_section_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyolecf_property_section_object_get_set_definitions,
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
	(initproc) pyolecf_property_section_init,
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

/* Creates a new property section object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_section_new(
           libolecf_property_section_t *property_section,
           PyObject *parent_object )
{
	pyolecf_property_section_t *pyolecf_property_section = NULL;
	static char *function                                = "pyolecf_property_section_new";

	if( property_section == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property section.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyolecf_property_section = PyObject_New(
	                            struct pyolecf_property_section,
	                            &pyolecf_property_section_type_object );

	if( pyolecf_property_section == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize property section.",
		 function );

		goto on_error;
	}
	pyolecf_property_section->property_section = property_section;
	pyolecf_property_section->parent_object    = parent_object;

	if( pyolecf_property_section->parent_object != NULL )
	{
		Py_IncRef(
		 pyolecf_property_section->parent_object );
	}
	return( (PyObject *) pyolecf_property_section );

on_error:
	if( pyolecf_property_section != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyolecf_property_section );
	}
	return( NULL );
}

/* Initializes a property section object
 * Returns 0 if successful or -1 on error
 */
int pyolecf_property_section_init(
     pyolecf_property_section_t *pyolecf_property_section )
{
	static char *function = "pyolecf_property_section_init";

	if( pyolecf_property_section == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property section.",
		 function );

		return( -1 );
	}
	/* Make sure libolecf property section is set to NULL
	 */
	pyolecf_property_section->property_section = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of property section not supported.",
	 function );

	return( -1 );
}

/* Frees a property section object
 */
void pyolecf_property_section_free(
      pyolecf_property_section_t *pyolecf_property_section )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyolecf_property_section_free";
	int result                  = 0;

	if( pyolecf_property_section == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property section.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyolecf_property_section );

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
	if( pyolecf_property_section->property_section != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libolecf_property_section_free(
		          &( pyolecf_property_section->property_section ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyolecf_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libolecf property section.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyolecf_property_section->parent_object != NULL )
	{
		Py_DecRef(
		 pyolecf_property_section->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyolecf_property_section );
}

/* Retrieves the class identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_section_get_class_identifier(
           pyolecf_property_section_t *pyolecf_property_section,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_property_section_get_class_identifier";
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_section == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property section.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_section_get_class_identifier(
	          pyolecf_property_section->property_section,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve class identifier.",
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
	string_object = pyolecf_string_new_from_guid(
	                 guid_data,
	                 16 );

	return( string_object );
}

/* Retrieves the number of properties
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_section_get_number_of_properties(
           pyolecf_property_section_t *pyolecf_property_section,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_property_section_get_number_of_properties";
	int number_of_properties = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_section == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property section.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_section_get_number_of_properties(
	          pyolecf_property_section->property_section,
	          &number_of_properties,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of properties.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_properties );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_properties );
#endif
	return( integer_object );
}

/* Retrieves a specific property by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_section_get_property_by_index(
           PyObject *pyolecf_property_section,
           int property_index )
{
	PyObject *property_object           = NULL;
	libcerror_error_t *error            = NULL;
	libolecf_property_value_t *property = NULL;
	static char *function               = "pyolecf_property_section_get_property_by_index";
	int result                          = 0;

	if( pyolecf_property_section == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property section.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_section_get_property_by_index(
	          ( (pyolecf_property_section_t *) pyolecf_property_section )->property_section,
	          property_index,
	          &property,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve property: %d.",
		 function,
		 property_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	property_object = pyolecf_property_value_new(
	                   property,
	                   (PyObject *) pyolecf_property_section );

	if( property_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create property value object.",
		 function );

		goto on_error;
	}
	return( property_object );

on_error:
	if( property != NULL )
	{
		libolecf_property_value_free(
		 &property,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific property
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_section_get_property(
           pyolecf_property_section_t *pyolecf_property_section,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *property_object   = NULL;
	static char *keyword_list[] = { "property_index", NULL };
	int property_index          = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &property_index ) == 0 )
	{
		return( NULL );
	}
	property_object = pyolecf_property_section_get_property_by_index(
	                   (PyObject *) pyolecf_property_section,
	                   property_index );

	return( property_object );
}

/* Retrieves a sequence and iterator object for the properties
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_section_get_properties(
           pyolecf_property_section_t *pyolecf_property_section,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyolecf_property_section_get_properties";
	int number_of_properties  = 0;
	int result                = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_section == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property section.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_section_get_number_of_properties(
	          pyolecf_property_section->property_section,
	          &number_of_properties,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of properties.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyolecf_property_values_new(
	                   (PyObject *) pyolecf_property_section,
	                   &pyolecf_property_section_get_property_by_index,
	                   number_of_properties );

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

