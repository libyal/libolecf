/*
 * Python object definition of the libolecf property set stream
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

#include "pyolecf_error.h"
#include "pyolecf_libcerror.h"
#include "pyolecf_libolecf.h"
#include "pyolecf_property_set.h"
#include "pyolecf_property_set_stream.h"
#include "pyolecf_python.h"
#include "pyolecf_stream.h"
#include "pyolecf_unused.h"

PyMethodDef pyolecf_property_set_stream_object_methods[] = {

	/* Functions to access the property set stream values */

	{ "get_set",
	  (PyCFunction) pyolecf_property_set_stream_get_set,
	  METH_NOARGS,
	  "get_set() -> Object or None\n"
	  "\n"
	  "Retrieves the property set." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyolecf_property_set_stream_object_get_set_definitions[] = {

	{ "set",
	  (getter) pyolecf_property_set_stream_get_set,
	  (setter) 0,
	  "The property set",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyolecf_property_set_stream_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyolecf.property_set_stream",
	/* tp_basicsize */
	sizeof( pyolecf_item_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	0,
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
	"pyolecf propery set stream object (wraps libolecf_item_t type 0x02)",
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
	pyolecf_property_set_stream_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyolecf_property_set_stream_object_get_set_definitions,
	/* tp_base */
	&pyolecf_stream_type_object,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	0,
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

/* Retrieves the property set
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_property_set_stream_get_set(
           pyolecf_item_t *pyolecf_item,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error              = NULL;
	libolecf_property_set_t *property_set = NULL;
	PyObject *property_set_object         = NULL;
	static char *function                 = "pyolecf_property_set_stream_get_set";
	int result                            = 0;

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

	result = libolecf_property_set_stream_get_set(
	          pyolecf_item->item,
	          &property_set,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve property set.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	property_set_object = pyolecf_property_set_new(
	                       &pyolecf_property_set_type_object,
	                       property_set,
	                       (PyObject *) pyolecf_item );

	if( property_set_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create property set object.",
		 function );

		goto on_error;
	}
	return( property_set_object );

on_error:
	if( property_set != NULL )
	{
		libolecf_property_set_free(
		 &property_set,
		 NULL );
	}
	return( NULL );
}

