/*
 * Python object wrapper of libolecf_file_t
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

#include "pyolecf_codepage.h"
#include "pyolecf_error.h"
#include "pyolecf_file.h"
#include "pyolecf_file_object_io_handle.h"
#include "pyolecf_item.h"
#include "pyolecf_libbfio.h"
#include "pyolecf_libcerror.h"
#include "pyolecf_libclocale.h"
#include "pyolecf_libolecf.h"
#include "pyolecf_python.h"
#include "pyolecf_stream.h"
#include "pyolecf_unused.h"

#if !defined( LIBOLECF_HAVE_BFIO )

LIBOLECF_EXTERN \
int libolecf_file_open_file_io_handle(
     libolecf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libolecf_error_t **error );

#endif /* !defined( LIBOLECF_HAVE_BFIO ) */

PyMethodDef pyolecf_file_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pyolecf_file_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the file to abort the current activity." },

	{ "open",
	  (PyCFunction) pyolecf_file_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a file." },

	{ "open_file_object",
	  (PyCFunction) pyolecf_file_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a file using a file-like object." },

	{ "close",
	  (PyCFunction) pyolecf_file_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a file." },

	{ "get_sector_size",
	  (PyCFunction) pyolecf_file_get_sector_size,
	  METH_NOARGS,
	  "get_sector_size() -> Integer or None\n"
	  "\n"
	  "Retrieves the sector size." },

	{ "get_short_sector_size",
	  (PyCFunction) pyolecf_file_get_short_sector_size,
	  METH_NOARGS,
	  "get_short_sector_size() -> Integer or None\n"
	  "\n"
	  "Retrieves the short sector size." },

	{ "get_ascii_codepage",
	  (PyCFunction) pyolecf_file_get_ascii_codepage,
	  METH_NOARGS,
	  "get_ascii_codepage() -> String\n"
	  "\n"
	  "Retrieves the codepage for ASCII strings used in the file." },

	{ "set_ascii_codepage",
	  (PyCFunction) pyolecf_file_set_ascii_codepage,
	  METH_VARARGS | METH_KEYWORDS,
	  "set_ascii_codepage(codepage) -> None\n"
	  "\n"
	  "Sets the codepage for ASCII strings used in the file.\n"
	  "Expects the codepage to be a string containing a Python codec definition." },

	{ "get_format_version",
	  (PyCFunction) pyolecf_file_get_format_version,
	  METH_NOARGS,
	  "get_format_version() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the format version." },

	{ "get_root_item",
	  (PyCFunction) pyolecf_file_get_root_item,
	  METH_NOARGS,
	  "get_root_item() -> Object or None\n"
	  "\n"
	  "Retrieves the root item." },

	{ "get_item_by_path",
	  (PyCFunction) pyolecf_file_get_item_by_path,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_item_by_path(path) -> Object or None\n"
	  "\n"
	  "Retrieves the item specified by the path." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyolecf_file_object_get_set_definitions[] = {

	{ "sector_size",
	  (getter) pyolecf_file_get_sector_size,
	  (setter) 0,
	  "The sector size.",
	  NULL },

	{ "short_sector_size",
	  (getter) pyolecf_file_get_short_sector_size,
	  (setter) 0,
	  "The short sector size.",
	  NULL },

	{ "ascii_codepage",
	  (getter) pyolecf_file_get_ascii_codepage,
	  (setter) pyolecf_file_set_ascii_codepage_setter,
	  "The codepage used for ASCII strings in the file.",
	  NULL },

	{ "format_version",
	  (getter) pyolecf_file_get_format_version,
	  (setter) 0,
	  "The format version.",
	  NULL },

	{ "root_item",
	  (getter) pyolecf_file_get_root_item,
	  (setter) 0,
	  "The root item.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyolecf_file_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyolecf.file",
	/* tp_basicsize */
	sizeof( pyolecf_file_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyolecf_file_free,
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
	"pyolecf file object (wraps libolecf_file_t)",
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
	pyolecf_file_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyolecf_file_object_get_set_definitions,
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
	(initproc) pyolecf_file_init,
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

/* Creates a new file object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_new(
           void )
{
	pyolecf_file_t *pyolecf_file = NULL;
	static char *function        = "pyolecf_file_new";

	pyolecf_file = PyObject_New(
	                struct pyolecf_file,
	                &pyolecf_file_type_object );

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	if( pyolecf_file_init(
	     pyolecf_file ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	return( (PyObject *) pyolecf_file );

on_error:
	if( pyolecf_file != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyolecf_file );
	}
	return( NULL );
}

/* Creates a new file object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_new_open(
           PyObject *self PYOLECF_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pyolecf_file = NULL;

	PYOLECF_UNREFERENCED_PARAMETER( self )

	pyolecf_file = pyolecf_file_new();

	pyolecf_file_open(
	 (pyolecf_file_t *) pyolecf_file,
	 arguments,
	 keywords );

	return( pyolecf_file );
}

/* Creates a new file object and opens it using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_new_open_file_object(
           PyObject *self PYOLECF_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pyolecf_file = NULL;

	PYOLECF_UNREFERENCED_PARAMETER( self )

	pyolecf_file = pyolecf_file_new();

	pyolecf_file_open_file_object(
	 (pyolecf_file_t *) pyolecf_file,
	 arguments,
	 keywords );

	return( pyolecf_file );
}

/* Intializes a file object
 * Returns 0 if successful or -1 on error
 */
int pyolecf_file_init(
     pyolecf_file_t *pyolecf_file )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_file_init";

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	pyolecf_file->file           = NULL;
	pyolecf_file->file_io_handle = NULL;

	if( libolecf_file_initialize(
	     &( pyolecf_file->file ),
	     &error ) != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a file object
 */
void pyolecf_file_free(
      pyolecf_file_t *pyolecf_file )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyolecf_file_free";
	int result                  = 0;

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return;
	}
	if( pyolecf_file->file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file - missing libolecf file.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyolecf_file );

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

	result = libolecf_file_free(
	          &( pyolecf_file->file ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free libolecf file.",
		 function );

		libcerror_error_free(
		 &error );
	}
	ob_type->tp_free(
	 (PyObject*) pyolecf_file );
}

/* Signals the file to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_signal_abort(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_file_signal_abort";
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_file_signal_abort(
	          pyolecf_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to signal abort.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_open(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	const char *filename_narrow  = NULL;
	static char *function        = "pyolecf_file_open";
	static char *keyword_list[]  = { "filename", "mode", NULL };
	char *mode                   = NULL;
	int result                   = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

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

		result = libolecf_file_open_wide(
		          pyolecf_file->file,
		          filename_wide,
		          LIBOLECF_OPEN_READ,
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

		result = libolecf_file_open(
		          pyolecf_file->file,
		          filename_narrow,
		          LIBOLECF_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result != 1 )
		{
			pyolecf_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open file.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
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

		result = libolecf_file_open(
		          pyolecf_file->file,
		          filename_narrow,
		          LIBOLECF_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyolecf_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open file.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Opens a file using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_open_file_object(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object       = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyolecf_file_open_file_object";
	static char *keyword_list[] = { "file_object", "mode", NULL };
	char *mode                  = NULL;
	int result                  = 0;

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	if( pyolecf_file->file_io_handle != NULL )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: invalid file - file IO handle already set.",
		 function );

		goto on_error;
	}
	if( pyolecf_file_object_initialize(
	     &( pyolecf_file->file_io_handle ),
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

	result = libolecf_file_open_file_io_handle(
	          pyolecf_file->file,
	          pyolecf_file->file_io_handle,
	          LIBOLECF_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open file.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pyolecf_file->file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &( pyolecf_file->file_io_handle ),
		 NULL );
	}
	return( NULL );
}

/* Closes a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_close(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_file_close";
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_file_close(
	          pyolecf_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to close file.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( pyolecf_file->file_io_handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_handle_free(
		          &( pyolecf_file->file_io_handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyolecf_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to free libbfio file IO handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the sector size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_get_sector_size(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_file_get_sector_size";
	size32_t sector_size     = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_file_get_sector_size(
	          pyolecf_file->file,
	          &sector_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: failed to retrieve sector size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) sector_size );

	return( integer_object );
}

/* Retrieves the short sector size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_get_short_sector_size(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object   = NULL;
	libcerror_error_t *error   = NULL;
	static char *function      = "pyolecf_file_get_short_sector_size";
	size32_t short_sector_size = 0;
	int result                 = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_file_get_short_sector_size(
	          pyolecf_file->file,
	          &short_sector_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: failed to retrieve short sector size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) short_sector_size );

	return( integer_object );
}

/* Retrieves the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_get_ascii_codepage(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	const char *codepage_string = NULL;
	static char *function       = "pyolecf_file_get_ascii_codepage";
	int ascii_codepage          = 0;
	int result                  = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_file_get_ascii_codepage(
	          pyolecf_file->file,
	          &ascii_codepage,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	codepage_string = pyolecf_codepage_to_string(
	                   ascii_codepage );

	if( codepage_string == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported ASCII codepage: %d.",
		 function,
		 ascii_codepage );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromString(
	                 codepage_string );
#else
	string_object = PyString_FromString(
	                 codepage_string );
#endif
	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert codepage string into string object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

/* Sets the codepage used for ASCII strings in the file
 * Returns 1 if successful or -1 on error
 */
int pyolecf_file_set_ascii_codepage_from_string(
     pyolecf_file_t *pyolecf_file,
     const char *codepage_string )
{
	libcerror_error_t *error      = NULL;
	static char *function         = "pyolecf_file_set_ascii_codepage_from_string";
	size_t codepage_string_length = 0;
	uint32_t feature_flags        = 0;
	int ascii_codepage            = 0;
	int result                    = 0;

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( codepage_string == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid codepage string.",
		 function );

		return( -1 );
	}
	codepage_string_length = narrow_string_length(
	                          codepage_string );

	feature_flags = LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS;

	if( libclocale_codepage_copy_from_string(
	     &ascii_codepage,
	     codepage_string,
	     codepage_string_length,
	     feature_flags,
	     &error ) != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_RuntimeError,
		 "%s: unable to determine ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_file_set_ascii_codepage(
	          pyolecf_file->file,
	          ascii_codepage,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to set ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 1 );
}

/* Sets the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_set_ascii_codepage(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments,
           PyObject *keywords )
{
	char *codepage_string       = NULL;
	static char *keyword_list[] = { "codepage", NULL };
	int result                  = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s",
	     keyword_list,
	     &codepage_string ) == 0 )
	{
		return( NULL );
	}
	result = pyolecf_file_set_ascii_codepage_from_string(
	          pyolecf_file,
	          codepage_string );

	if( result != 1 )
	{
		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Sets the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
int pyolecf_file_set_ascii_codepage_setter(
     pyolecf_file_t *pyolecf_file,
     PyObject *string_object,
     void *closure PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *utf8_string_object = NULL;
	char *codepage_string        = NULL;
	static char *function        = "pyolecf_file_set_ascii_codepage_setter";
	int result                   = 0;

	PYOLECF_UNREFERENCED_PARAMETER( closure )

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

		return( -1 );
	}
	else if( result != 0 )
	{
		/* The codepage string should only contain ASCII characters.
		 */
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pyolecf_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert unicode string to UTF-8.",
			 function );

			return( -1 );
		}
#if PY_MAJOR_VERSION >= 3
		codepage_string = PyBytes_AsString(
		                   utf8_string_object );
#else
		codepage_string = PyString_AsString(
		                   utf8_string_object );
#endif
		if( codepage_string == NULL )
		{
			return( -1 );
		}
		result = pyolecf_file_set_ascii_codepage_from_string(
		          pyolecf_file,
		          codepage_string );

		if( result != 1 )
		{
			return( -1 );
		}
		return( 0 );
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

		return( -1 );
	}
	else if( result != 0 )
	{
#if PY_MAJOR_VERSION >= 3
		codepage_string = PyBytes_AsString(
		                   string_object );
#else
		codepage_string = PyString_AsString(
		                   string_object );
#endif
		if( codepage_string == NULL )
		{
			return( -1 );
		}
		result = pyolecf_file_set_ascii_codepage_from_string(
		          pyolecf_file,
		          codepage_string );

		if( result != 1 )
		{
			return( -1 );
		}
		return( 0 );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( -1 );
}

/* Retrieves the format version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_get_format_version(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	char utf8_string[ 4 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	const char *errors       = NULL;
	static char *function    = "pyolecf_file_get_format_version";
	uint16_t major_version   = 0;
	uint16_t minor_version   = 0;
	int result               = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_file_get_format_version(
	          pyolecf_file->file,
	          &major_version,
	          &minor_version,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve format version.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( major_version > 9 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: major version out of bounds.",
		 function );

		return( NULL );
	}
	if( minor_version > 9 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: minor version out of bounds.",
		 function );

		return( NULL );
	}
	utf8_string[ 0 ] = '0' + (char) major_version;
	utf8_string[ 1 ] = '.';
	utf8_string[ 2 ] = '0' + (char) minor_version;
	utf8_string[ 3 ] = 0;

	/* Pass the string length to PyUnicode_DecodeUTF8 otherwise it makes
	 * the end of string character is part of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 utf8_string,
	                 (Py_ssize_t) 3,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 string into Unicode object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

/* Retrieves the item type object
 * Returns a Python type object if successful or NULL on error
 */
PyTypeObject *pyolecf_file_get_item_type_object(
               libolecf_item_t *item )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyolecf_file_get_item_type_object";
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
		return( &pyolecf_stream_type_object );
	}
	return( &pyolecf_item_type_object );
}

/* Retrieves the root item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_get_root_item(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments PYOLECF_ATTRIBUTE_UNUSED )
{
	PyObject *item_object      = NULL;
	PyTypeObject *type_object  = NULL;
	libcerror_error_t *error   = NULL;
	libolecf_item_t *root_item = NULL;
	static char *function      = "pyolecf_file_get_root_item";
	int result                 = 0;

	PYOLECF_UNREFERENCED_PARAMETER( arguments )

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libolecf_file_get_root_item(
	          pyolecf_file->file,
	          &root_item,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve root item.",
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
	type_object = pyolecf_file_get_item_type_object(
	               root_item );

	if( type_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to retrieve root item type object.",
		 function );

		goto on_error;
	}
	item_object = pyolecf_item_new(
	               type_object,
	               root_item,
	               (PyObject *) pyolecf_file );

	if( item_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create item object.",
		 function );

		goto on_error;
	}
	return( item_object );

on_error:
	if( root_item != NULL )
	{
		libolecf_item_free(
		 &root_item,
		 NULL );
	}
	return( NULL );
}

/* Retrieves the item specified by the path
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyolecf_file_get_item_by_path(
           pyolecf_file_t *pyolecf_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *item_object       = NULL;
	PyTypeObject *type_object   = NULL;
	libcerror_error_t *error    = NULL;
	libolecf_item_t *item       = NULL;
	static char *function       = "pyolecf_file_get_item_by_path";
	static char *keyword_list[] = { "path", NULL };
	char *utf8_path             = NULL;
	size_t utf8_path_length     = 0;
	int result                  = 0;

	if( pyolecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
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

	result = libolecf_file_get_item_by_utf8_path(
	          pyolecf_file->file,
	          (uint8_t *) utf8_path,
	          utf8_path_length,
	          &item,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyolecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve item.",
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
	type_object = pyolecf_file_get_item_type_object(
	               item );

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
	               item,
	               (PyObject *) pyolecf_file );

	if( item_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create item object.",
		 function );

		goto on_error;
	}
	return( item_object );

on_error:
	if( item != NULL )
	{
		libolecf_item_free(
		 &item,
		 NULL );
	}
	return( NULL );
}

