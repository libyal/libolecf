/*
 * Python object definition of the property sections sequence and iterator
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

#include "pyolecf_libcerror.h"
#include "pyolecf_libolecf.h"
#include "pyolecf_property_section.h"
#include "pyolecf_property_sections.h"
#include "pyolecf_property_set.h"
#include "pyolecf_python.h"

PySequenceMethods pyolecf_property_sections_sequence_methods = {
	/* sq_length */
	(lenfunc) pyolecf_property_sections_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyolecf_property_sections_getitem,
	/* sq_slice */
	0,
	/* sq_ass_item */
	0,
	/* sq_ass_slice */
	0,
	/* sq_contains */
	0,
	/* sq_inplace_concat */
	0,
	/* sq_inplace_repeat */
	0
};

PyTypeObject pyolecf_property_sections_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyolecf._property_sections",
	/* tp_basicsize */
	sizeof( pyolecf_property_sections_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyolecf_property_sections_free,
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
	&pyolecf_property_sections_sequence_methods,
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
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_ITER,
	/* tp_doc */
	"internal pyolecf property sections sequence and iterator object",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyolecf_property_sections_iter,
	/* tp_iternext */
	(iternextfunc) pyolecf_property_sections_iternext,
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
	(initproc) pyolecf_property_sections_init,
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

/* Creates a new property sections object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_sections_new(
           pyolecf_property_set_t *property_set_object,
           PyObject* (*get_property_section_by_index)(
                        pyolecf_property_set_t *property_set_object,
                        int property_section_index ),
           int number_of_property_sections )
{
	pyolecf_property_sections_t *pyolecf_property_sections = NULL;
	static char *function                                  = "pyolecf_property_sections_new";

	if( property_set_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property set object.",
		 function );

		return( NULL );
	}
	if( get_property_section_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get property section by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the property sections values are initialized
	 */
	pyolecf_property_sections = PyObject_New(
	                             struct pyolecf_property_sections,
	                             &pyolecf_property_sections_type_object );

	if( pyolecf_property_sections == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize property sections.",
		 function );

		goto on_error;
	}
	if( pyolecf_property_sections_init(
	     pyolecf_property_sections ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize property sections.",
		 function );

		goto on_error;
	}
	pyolecf_property_sections->property_set_object           = property_set_object;
	pyolecf_property_sections->get_property_section_by_index = get_property_section_by_index;
	pyolecf_property_sections->number_of_property_sections   = number_of_property_sections;

	Py_IncRef(
	 (PyObject *) pyolecf_property_sections->property_set_object );

	return( (PyObject *) pyolecf_property_sections );

on_error:
	if( pyolecf_property_sections != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyolecf_property_sections );
	}
	return( NULL );
}

/* Intializes a property sections object
 * Returns 0 if successful or -1 on error
 */
int pyolecf_property_sections_init(
     pyolecf_property_sections_t *pyolecf_property_sections )
{
	static char *function = "pyolecf_property_sections_init";

	if( pyolecf_property_sections == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property sections.",
		 function );

		return( -1 );
	}
	/* Make sure the property sections values are initialized
	 */
	pyolecf_property_sections->property_set_object           = NULL;
	pyolecf_property_sections->get_property_section_by_index = NULL;
	pyolecf_property_sections->property_section_index        = 0;
	pyolecf_property_sections->number_of_property_sections   = 0;

	return( 0 );
}

/* Frees a property sections object
 */
void pyolecf_property_sections_free(
      pyolecf_property_sections_t *pyolecf_property_sections )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyolecf_property_sections_free";

	if( pyolecf_property_sections == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property sections.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyolecf_property_sections );

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
	if( pyolecf_property_sections->property_set_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyolecf_property_sections->property_set_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyolecf_property_sections );
}

/* The property sections len() function
 */
Py_ssize_t pyolecf_property_sections_len(
            pyolecf_property_sections_t *pyolecf_property_sections )
{
	static char *function = "pyolecf_property_sections_len";

	if( pyolecf_property_sections == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property sections.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pyolecf_property_sections->number_of_property_sections );
}

/* The property sections getitem() function
 */
PyObject *pyolecf_property_sections_getitem(
           pyolecf_property_sections_t *pyolecf_property_sections,
           Py_ssize_t property_section_index )
{
	PyObject *property_section_object = NULL;
	static char *function             = "pyolecf_property_sections_getitem";

	if( pyolecf_property_sections == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property sections.",
		 function );

		return( NULL );
	}
	if( pyolecf_property_sections->get_property_section_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property sections - missing get property section by index function.",
		 function );

		return( NULL );
	}
	if( pyolecf_property_sections->number_of_property_sections < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property sections - invalid number of property sections.",
		 function );

		return( NULL );
	}
	if( ( property_section_index < 0 )
	 || ( property_section_index >= (Py_ssize_t) pyolecf_property_sections->number_of_property_sections ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid property section index value out of bounds.",
		 function );

		return( NULL );
	}
	property_section_object = pyolecf_property_sections->get_property_section_by_index(
	                           pyolecf_property_sections->property_set_object,
	                           (int) property_section_index );

	return( property_section_object );
}

/* The property sections iter() function
 */
PyObject *pyolecf_property_sections_iter(
           pyolecf_property_sections_t *pyolecf_property_sections )
{
	static char *function = "pyolecf_property_sections_iter";

	if( pyolecf_property_sections == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property sections.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pyolecf_property_sections );

	return( (PyObject *) pyolecf_property_sections );
}

/* The property sections iternext() function
 */
PyObject *pyolecf_property_sections_iternext(
           pyolecf_property_sections_t *pyolecf_property_sections )
{
	PyObject *property_section_object = NULL;
	static char *function             = "pyolecf_property_sections_iternext";

	if( pyolecf_property_sections == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property sections.",
		 function );

		return( NULL );
	}
	if( pyolecf_property_sections->get_property_section_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property sections - missing get property section by index function.",
		 function );

		return( NULL );
	}
	if( pyolecf_property_sections->property_section_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property sections - invalid property section index.",
		 function );

		return( NULL );
	}
	if( pyolecf_property_sections->number_of_property_sections < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid property sections - invalid number of property sections.",
		 function );

		return( NULL );
	}
	if( pyolecf_property_sections->property_section_index >= pyolecf_property_sections->number_of_property_sections )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	property_section_object = pyolecf_property_sections->get_property_section_by_index(
	                           pyolecf_property_sections->property_set_object,
	                           pyolecf_property_sections->property_section_index );

	if( property_section_object != NULL )
	{
		pyolecf_property_sections->property_section_index++;
	}
	return( property_section_object );
}

