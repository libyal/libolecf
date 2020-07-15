/*
 * The directory list functions
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

#include "libolecf_directory_entry.h"
#include "libolecf_directory_list.h"
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"

/* Retrieves a specific directory element from the list
 * Returns 1 if successful, 0 if not found or -1 on error
 */
int libolecf_directory_list_get_element_by_identifier(
     libcdata_list_t *directory_entry_list,
     uint32_t directory_entry_identifier,
     libolecf_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	libcdata_list_element_t *list_element            = NULL;
	libolecf_directory_entry_t *safe_directory_entry = NULL;
	static char *function                            = "libolecf_directory_list_get_element_by_identifier";
	int element_index                                = 0;

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( -1 );
	}
	*directory_entry = NULL;

	if( libcdata_list_get_first_element(
	     directory_entry_list,
	     &list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve first element of directory entry list.",
		 function );

		return( -1 );
	}
	while( list_element != NULL )
	{
		if( libcdata_list_element_get_value(
		     list_element,
		     (intptr_t **) &safe_directory_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value from element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		if( safe_directory_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing directory entry: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		if( safe_directory_entry->directory_identifier == directory_entry_identifier )
		{
			break;
		}
		if( libcdata_list_element_get_next_element(
		     list_element,
		     &list_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve next element of element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		element_index++;
	}
	if( list_element != NULL )
	{
		*directory_entry = safe_directory_entry;

		return( 1 );
	}
	return( 0 );
}

