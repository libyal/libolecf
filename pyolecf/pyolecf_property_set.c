/*
 * Python object wrapper of libolecf_property_set_t
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
#include "pyolecf_property_sections.h"
#include "pyolecf_property_set.h"
#include "pyolecf_python.h"
#include "pyolecf_unused.h"

PyMethodDef pyolecf_property_set_object_methods[] = {

	{ "get_class_identifier",
	  (PyCFunction) pyolecf_property_set_get_class_identifier,
	  METH_NOARGS,
	  "get_class_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the class identifier." },

	{ "get_number_of_sections",
	  (PyCFunction) pyolecf_property_set_get_number_of_sections,
	  METH_NOARGS,
	  "get_number_of_sections() -> Integer or None\n"
	  "\n"
	  "Retrieves the number of sections." },

	{ "get_section",
	  (PyCFunction) pyolecf_property_set_get_section,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_section(section_index) -> Object or None\n"
	  "\n"
	  "Retrieves the section specified by the index." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyolecf_property_set_object_get_set_definitions[] = {

	{ "class_identifier",
	  (getter) pyolecf_property_set_get_class_identifier,
	  (setter) 0,
	  "The class identifier.",
	  NULL },

	{ "number_of_sections",
	  (getter) pyolecf_property_set_get_number_of_sections,
	  (setter) 0,
	  "The number of sections.",
	  NULL },

	{ "sections",
	  (getter) pyolecf_property_set_get_sections,
	  (setter) 0,
	  "The sections.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyolecf_property_set_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyolecf.property_set",
	/* tp_basicsize */
	sizeof( pyolecf_property_set_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyolecf_property_set_free,
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
	"pyolecf property set object (wraps libolecf_property_set_t)",
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
	pyolecf_property_set_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyolecf_property_set_object_get_set_definitions,
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
	(initproc) pyolecf_property_set_init,
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

/* Creates a new property set object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_set_new(
           libolecf_property_set_t *property_set,
           PyObject *parent_object )
{
	pyolecf_property_set_t *pyolecf_property_set = NULL;
	static char *function                        = "pyolecf_property_set_new";

	if( property_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property set.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyolecf_property_set = PyObject_New(
	                        struct pyolecf_property_set,
	                        &pyolecf_property_set_type_object );

	if( pyolecf_property_set == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize property set.",
		 function );

		goto on_error;
	}
	pyolecf_property_set->property_set  = property_set;
	pyolecf_property_set->parent_object = parent_object;

	if( pyolecf_property_set->parent_object != NULL )
	{
		Py_IncRef(
		 pyolecf_property_set->parent_object );
	}
	return( (PyObject *) pyolecf_property_set );

on_error:
	if( pyolecf_property_set != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyolecf_property_set );
	}
	return( NULL );
}

/* Initializes a property set object
 * Returns 0 if successful or -1 on error
 */
int pyolecf_property_set_init(
     pyolecf_property_set_t *pyolecf_property_set )
{
	static char *function = "pyolecf_property_set_init";

	if( pyolecf_property_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property set.",
		 function );

		return( -1 );
	}
	/* Make sure libolecf property set is set to NULL
	 */
	pyolecf_property_set->property_set = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of property set not supported.",
	 function );

	return( -1 );
}

/* Frees a property set object
 */
void pyolecf_property_set_free(
      pyolecf_property_set_t *pyolecf_property_set )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyolecf_property_set_free";
	int result                  = 0;

	if( pyolecf_property_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property set.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyolecf_property_set );

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
	if( pyolecf_property_set->property_set != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libolecf_property_set_free(
		          &( pyolecf_property_set->property_set ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyolecf_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libolecf property set.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyolecf_property_set->parent_object != NULL )
	{
		Py_DecRef(
		 pyolecf_property_set->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyolecf_property_set );
}

/* Retrieves the class identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_set_get_class_identifier(
           pyolecf_property_set_t *pyolecf_property_set,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_property_set_get_class_identifier";
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property set.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_set_get_class_identifier(
	          pyolecf_property_set->property_set,
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

/* Retrieves the number of sections
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_set_get_number_of_sections(
           pyolecf_property_set_t *pyolecf_property_set,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_property_set_get_number_of_sections";
	int number_of_sections   = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property set.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_set_get_number_of_sections(
	          pyolecf_property_set->property_set,
	          &number_of_sections,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of sections.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_sections );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_sections );
#endif
	return( integer_object );
}

/* Retrieves a specific section by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_set_get_section_by_index(
           PyObject *pyolecf_property_set,
           int section_index )
{
	PyObject *section_object             = NULL;
	libcerror_error_t *error             = NULL;
	libolecf_property_section_t *section = NULL;
	static char *function                = "pyolecf_property_set_get_section_by_index";
	int result                           = 0;

	if( pyolecf_property_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property set.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_set_get_section_by_index(
	          ( (pyolecf_property_set_t *) pyolecf_property_set )->property_set,
	          section_index,
	          &section,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve section: %d.",
		 function,
		 section_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	section_object = pyolecf_property_section_new(
	                  section,
	                  (PyObject *) pyolecf_property_set );

	if( section_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create property section object.",
		 function );

		goto on_error;
	}
	return( section_object );

on_error:
	if( section != NULL )
	{
		libolecf_property_section_free(
		 &section,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific section
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_set_get_section(
           pyolecf_property_set_t *pyolecf_property_set,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *section_object    = NULL;
	static char *keyword_list[] = { "section_index", NULL };
	int section_index           = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &section_index ) == 0 )
	{
		return( NULL );
	}
	section_object = pyolecf_property_set_get_section_by_index(
	                  (PyObject *) pyolecf_property_set,
	                  section_index );

	return( section_object );
}

/* Retrieves a sequence and iterator object for the sections
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_set_get_sections(
           pyolecf_property_set_t *pyolecf_property_set,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyolecf_property_set_get_sections";
	int number_of_sections    = 0;
	int result                = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_property_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property set.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_property_set_get_number_of_sections(
	          pyolecf_property_set->property_set,
	          &number_of_sections,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of sections.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyolecf_property_sections_new(
	                   (PyObject *) pyolecf_property_set,
	                   &pyolecf_property_set_get_section_by_index,
	                   number_of_sections );

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

