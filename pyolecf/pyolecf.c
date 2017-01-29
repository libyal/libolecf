/*
 * Python bindings module for libolecf (pyolecf)
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
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyolecf.h"
#include "pyolecf_error.h"
#include "pyolecf_file.h"
#include "pyolecf_file_object_io_handle.h"
#include "pyolecf_item.h"
#include "pyolecf_item_types.h"
#include "pyolecf_items.h"
#include "pyolecf_libcerror.h"
#include "pyolecf_libolecf.h"
#include "pyolecf_property_section.h"
#include "pyolecf_property_sections.h"
#include "pyolecf_property_set.h"
#include "pyolecf_property_set_stream.h"
#include "pyolecf_property_value.h"
#include "pyolecf_property_values.h"
#include "pyolecf_python.h"
#include "pyolecf_stream.h"
#include "pyolecf_unused.h"
#include "pyolecf_value_types.h"

#if !defined( LIBOLECF_HAVE_BFIO )
LIBOLECF_EXTERN \
int libolecf_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libolecf_error_t **error );
#endif

/* The pyolecf module methods
 */
PyMethodDef pyolecf_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pyolecf_get_version,
	  METH_NOARGS,
	  "get_version() -> String\n"
	  "\n"
	  "Retrieves the version." },

	{ "check_file_signature",
	  (PyCFunction) pyolecf_check_file_signature,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_file_signature(filename) -> Boolean\n"
	  "\n"
	  "Checks if a file has an Object Linking and Embedding (OLE) Compound File (CF) signature." },

	{ "check_file_signature_file_object",
	  (PyCFunction) pyolecf_check_file_signature_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_file_signature_file_object(file_object) -> Boolean\n"
	  "\n"
	  "Checks if a file has an Object Linking and Embedding (OLE) Compound File (CF) signature using a file-like object." },

	{ "open",
	  (PyCFunction) pyolecf_file_new_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> Object\n"
	  "\n"
	  "Opens a file." },

	{ "open_file_object",
	  (PyCFunction) pyolecf_file_new_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> Object\n"
	  "\n"
	  "Opens a file using a file-like object." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

/* Retrieves the pyolecf/libolecf version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_get_version(
           PyObject *self PYOLECF_ATTRIBUTE_UNUSED,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	const char *errors           = NULL;
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYOLECF_UNREFERENCED_PARAMETER( self )
	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = libolecf_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = narrow_string_length(
	                         version_string );

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) version_string_length,
	         errors ) );
}

/* Checks if the file has an Object Linking and Embedding (OLE) Compound File (CF) signature
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_check_file_signature(
           PyObject *self PYOLECF_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	static char *function        = "pyolecf_check_file_signature";
	static char *keyword_list[]  = { "filename", NULL };
	const char *filename_narrow  = NULL;
	int result                   = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	PYOLECF_UNREFERENCED_PARAMETER( self )

	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|O",
	     keyword_list,
	     &string_object ) == 0 )
	{
		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pyolecf_error_fetch_and_raise(
	         PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
		Py_BEGIN_ALLOW_THREADS

		result = libolecf_check_file_signature_wide(
		          filename_wide,
		          &error );

		Py_END_ALLOW_THREADS
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pyolecf_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
				   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
				   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libolecf_check_file_signature(
		          filename_narrow,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result == -1 )
		{
			pyolecf_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to check file signature.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( result != 0 )
		{
			Py_IncRef(
			 (PyObject *) Py_True );

			return( Py_True );
		}
		Py_IncRef(
		 (PyObject *) Py_False );

		return( Py_False );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
		  string_object,
		  (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
		  string_object,
		  (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pyolecf_error_fetch_and_raise(
	         PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
				   string_object );
#else
		filename_narrow = PyString_AsString(
				   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libolecf_check_file_signature(
		          filename_narrow,
		          &error );

		Py_END_ALLOW_THREADS

		if( result == -1 )
		{
			pyolecf_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to check file signature.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( result != 0 )
		{
			Py_IncRef(
			 (PyObject *) Py_True );

			return( Py_True );
		}
		Py_IncRef(
		 (PyObject *) Py_False );

		return( Py_False );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Checks if the file has a Object Linking and Embedding (OLE) Compound File (CF) signature using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_check_file_signature_file_object(
           PyObject *self PYOLECF_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error         = NULL;
	libbfio_handle_t *file_io_handle = NULL;
	PyObject *file_object            = NULL;
	static char *function            = "pyolecf_check_file_signature_file_object";
	static char *keyword_list[]      = { "file_object", NULL };
	int result                       = 0;

	PYOLECF_UNREFERENCED_PARAMETER( self )

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|O",
	     keyword_list,
	     &file_object ) == 0 )
	{
		return( NULL );
	}
	if( pyolecf_file_object_initialize(
	     &file_io_handle,
	     file_object,
	     &error ) != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_check_file_signature_file_io_handle(
	          file_io_handle,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to check file signature.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( libbfio_handle_free(
	     &file_io_handle,
	     &error ) != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( result != 0 )
	{
		Py_IncRef(
		 (PyObject *) Py_True );

		return( Py_True );
	}
	Py_IncRef(
	 (PyObject *) Py_False );

	return( Py_False );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( NULL );
}

#if PY_MAJOR_VERSION >= 3

/* The pyolecf module definition
 */
PyModuleDef pyolecf_module_definition = {
	PyModuleDef_HEAD_INIT,

	/* m_name */
	"pyolecf",
	/* m_doc */
	"Python libolecf module (pyolecf).",
	/* m_size */
	-1,
	/* m_methods */
	pyolecf_module_methods,
	/* m_reload */
	NULL,
	/* m_traverse */
	NULL,
	/* m_clear */
	NULL,
	/* m_free */
	NULL,
};

#endif /* PY_MAJOR_VERSION >= 3 */

/* Initializes the pyolecf module
 */
#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_pyolecf(
                void )
#else
PyMODINIT_FUNC initpyolecf(
                void )
#endif
{
	PyObject *module                              = NULL;
	PyTypeObject *file_type_object                = NULL;
	PyTypeObject *item_type_object                = NULL;
	PyTypeObject *item_types_type_object          = NULL;
	PyTypeObject *items_type_object               = NULL;
	PyTypeObject *stream_type_object              = NULL;
	PyTypeObject *property_section_type_object    = NULL;
	PyTypeObject *property_sections_type_object   = NULL;
	PyTypeObject *property_set_type_object        = NULL;
	PyTypeObject *property_set_stream_type_object = NULL;
	PyTypeObject *property_value_type_object      = NULL;
	PyTypeObject *property_values_type_object     = NULL;
	PyTypeObject *value_types_type_object         = NULL;
	PyGILState_STATE gil_state                    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libolecf_notify_set_stream(
	 stderr,
	 NULL );
	libolecf_notify_set_verbose(
	 1 );
#endif

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
#if PY_MAJOR_VERSION >= 3
	module = PyModule_Create(
	          &pyolecf_module_definition );
#else
	module = Py_InitModule3(
	          "pyolecf",
	          pyolecf_module_methods,
	          "Python libolecf module (pyolecf)." );
#endif
	if( module == NULL )
	{
#if PY_MAJOR_VERSION >= 3
		return( NULL );
#else
		return;
#endif
	}
	PyEval_InitThreads();

	gil_state = PyGILState_Ensure();

	/* Setup the file type object
	 */
	pyolecf_file_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyolecf_file_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyolecf_file_type_object );

	file_type_object = &pyolecf_file_type_object;

	PyModule_AddObject(
	 module,
	 "file",
	 (PyObject *) file_type_object );

	/* Setup the items type object
	 */
	pyolecf_items_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyolecf_items_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyolecf_items_type_object );

	items_type_object = &pyolecf_items_type_object;

	PyModule_AddObject(
	 module,
	 "_items",
	 (PyObject *) items_type_object );

	/* Setup the item type object
	 */
	pyolecf_item_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyolecf_item_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyolecf_item_type_object );

	item_type_object = &pyolecf_item_type_object;

	PyModule_AddObject(
	 module,
	 "item",
	 (PyObject *) item_type_object );

	/* Setup the stream type object
	 */
	pyolecf_stream_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyolecf_stream_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyolecf_stream_type_object );

	stream_type_object = &pyolecf_stream_type_object;

	PyModule_AddObject(
	 module,
	 "stream",
	 (PyObject *) stream_type_object );

	/* Setup the property set stream type object
	 */
	pyolecf_property_set_stream_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyolecf_property_set_stream_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyolecf_property_set_stream_type_object );

	property_set_stream_type_object = &pyolecf_property_set_stream_type_object;

	PyModule_AddObject(
	 module,
	 "property_set_stream",
	 (PyObject *) property_set_stream_type_object );

	/* Setup the property set type object
	 */
	pyolecf_property_set_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyolecf_property_set_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyolecf_property_set_type_object );

	property_set_type_object = &pyolecf_property_set_type_object;

	PyModule_AddObject(
	 module,
	 "property_set",
	 (PyObject *) property_set_type_object );

	/* Setup the property sections type object
	 */
	pyolecf_property_sections_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyolecf_property_sections_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyolecf_property_sections_type_object );

	property_sections_type_object = &pyolecf_property_sections_type_object;

	PyModule_AddObject(
	 module,
	 "_property_sections",
	 (PyObject *) property_sections_type_object );

	/* Setup the property section type object
	 */
	pyolecf_property_section_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyolecf_property_section_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyolecf_property_section_type_object );

	property_section_type_object = &pyolecf_property_section_type_object;

	PyModule_AddObject(
	 module,
	 "property_section",
	 (PyObject *) property_section_type_object );

	/* Setup the property values type object
	 */
	pyolecf_property_values_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyolecf_property_values_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyolecf_property_values_type_object );

	property_values_type_object = &pyolecf_property_values_type_object;

	PyModule_AddObject(
	 module,
	 "_property_values",
	 (PyObject *) property_values_type_object );

	/* Setup the property value type object
	 */
	pyolecf_property_value_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyolecf_property_value_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyolecf_property_value_type_object );

	property_value_type_object = &pyolecf_property_value_type_object;

	PyModule_AddObject(
	 module,
	 "property_value",
	 (PyObject *) property_value_type_object );

	/* Setup the item types type object
	 */
	pyolecf_item_types_type_object.tp_new = PyType_GenericNew;

	if( pyolecf_item_types_init_type(
	     &pyolecf_item_types_type_object ) != 1 )
	{
		goto on_error;
	}
	if( PyType_Ready(
	     &pyolecf_item_types_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyolecf_item_types_type_object );

	item_types_type_object = &pyolecf_item_types_type_object;

	PyModule_AddObject(
	 module,
	 "item_types",
	 (PyObject *) item_types_type_object );

	/* Setup the value types type object
	 */
	pyolecf_value_types_type_object.tp_new = PyType_GenericNew;

	if( pyolecf_value_types_init_type(
	     &pyolecf_value_types_type_object ) != 1 )
	{
		goto on_error;
	}
	if( PyType_Ready(
	     &pyolecf_value_types_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyolecf_value_types_type_object );

	value_types_type_object = &pyolecf_value_types_type_object;

	PyModule_AddObject(
	 module,
	 "value_types",
	 (PyObject *) value_types_type_object );

	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( module );
#else
	return;
#endif

on_error:
	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( NULL );
#else
	return;
#endif
}

