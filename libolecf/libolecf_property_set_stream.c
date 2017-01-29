/*
 * Property set stream functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libolecf_definitions.h"
#include "libolecf_libcerror.h"
#include "libolecf_libcnotify.h"
#include "libolecf_item.h"
#include "libolecf_property_set.h"
#include "libolecf_property_set_stream.h"

/* Reads the property set stream
 * Returns 1 if successful or -1 on error
 */
int libolecf_property_set_stream_get_set(
     libolecf_item_t *property_set_stream,
     libolecf_property_set_t **property_set,
     libcerror_error_t **error )
{
	libolecf_internal_item_t *internal_item = NULL;
	static char *function                   = "libolecf_property_set_stream_get_set";

	if( property_set_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property set stream.",
		 function );

		return( -1 );
	}
	internal_item = (libolecf_internal_item_t *) property_set_stream;

	if( property_set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property set.",
		 function );

		return( -1 );
	}
	if( *property_set != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: property set already set.",
		 function );

		return( -1 );
	}
	if( libolecf_property_set_initialize(
	     property_set,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create property set.",
		 function );

		goto on_error;
	}
	if( libolecf_property_set_read(
	     *property_set,
	     internal_item->io_handle,
	     property_set_stream,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read property set.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *property_set != NULL )
	{
		libolecf_property_set_free(
		 property_set,
		 NULL );
	}
	return( -1 );
}

