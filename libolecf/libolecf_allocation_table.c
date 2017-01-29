/*
 * Allocation table functions
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
#include <memory.h>
#include <types.h>

#include "libolecf_allocation_table.h"
#include "libolecf_libcerror.h"

/* Creates an allocation table
 * Make sure the value allocation_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libolecf_allocation_table_initialize(
     libolecf_allocation_table_t **allocation_table,
     int number_of_sector_identifiers,
     libcerror_error_t **error )
{
	static char *function          = "libolecf_allocation_table_initialize";
	size_t sector_identifiers_size = 0;

	if( allocation_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid allocation table.",
		 function );

		return( -1 );
	}
	if( *allocation_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid allocation table value already set.",
		 function );

		return( -1 );
	}
	if( number_of_sector_identifiers < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid number of sector identifiers value less than zero.",
		 function );

		return( -1 );
	}
	if( (size_t) number_of_sector_identifiers > (size_t) ( SSIZE_MAX / sizeof( uint32_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid number of sector identifers value exceeds maximum.",
		 function );

		goto on_error;
	}
	*allocation_table = memory_allocate_structure(
	                     libolecf_allocation_table_t );

	if( *allocation_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create allocation table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *allocation_table,
	     0,
	     sizeof( libolecf_allocation_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear allocation table.",
		 function );

		memory_free(
		 *allocation_table );

		*allocation_table = NULL;

		return( -1 );
	}
	if( number_of_sector_identifiers > 0 )
	{
		sector_identifiers_size = number_of_sector_identifiers * sizeof( uint32_t );

		if( sector_identifiers_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid sector identifiers size value exceeds maximum.",
			 function );

			goto on_error;
		}
		( *allocation_table )->sector_identifier = (uint32_t *) memory_allocate(
									 sector_identifiers_size );

		if( ( *allocation_table )->sector_identifier == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create sector identifiers.",
			 function );

			goto on_error;
		}
		if( memory_set(
		     ( *allocation_table )->sector_identifier,
		     0,
		     sector_identifiers_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear sector identifiers.",
			 function );

			goto on_error;
		}
		( *allocation_table )->number_of_sector_identifiers = number_of_sector_identifiers;
	}
	return( 1 );

on_error:
	if( *allocation_table != NULL )
	{
		if( ( *allocation_table )->sector_identifier != NULL )
		{
			memory_free(
			 ( *allocation_table )->sector_identifier );
		}
		memory_free(
		 *allocation_table );

		*allocation_table = NULL;
	}
	return( -1 );
}

/* Frees an allocation table
 * Returns 1 if successful or -1 on error
 */
int libolecf_allocation_table_free(
     libolecf_allocation_table_t **allocation_table,
     libcerror_error_t **error )
{
	static char *function = "libolecf_allocation_table_free";

	if( allocation_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid allocation_table.",
		 function );

		return( -1 );
	}
	if( *allocation_table != NULL )
	{
		if( ( *allocation_table )->sector_identifier != NULL )
		{
			memory_free(
			 ( *allocation_table )->sector_identifier );
		}
		memory_free(
		 *allocation_table );

		*allocation_table = NULL;
	}
	return( 1 );
}

/* Resizes an allocation_table
 * Returns 1 if successful or -1 on error
 */
int libolecf_allocation_table_resize(
     libolecf_allocation_table_t *allocation_table,
     int number_of_sector_identifiers,
     libcerror_error_t **error )
{
	void *reallocation             = NULL;
	static char *function          = "libolecf_allocation_table_resize";
	size_t sector_identifiers_size = 0;

	if( allocation_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid allocation_table.",
		 function );

		return( -1 );
	}
	if( number_of_sector_identifiers < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid number of sector identifiers value less than zero.",
		 function );

		return( -1 );
	}
	if( allocation_table->number_of_sector_identifiers < number_of_sector_identifiers )
	{
		sector_identifiers_size = sizeof( uint32_t ) * number_of_sector_identifiers;

		if( sector_identifiers_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid sector identifiers size value exceeds maximum.",
			 function );

			return( -1 );
		}
		reallocation = memory_reallocate(
		                allocation_table->sector_identifier,
		                sector_identifiers_size );

		if( reallocation == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to resize sector identifiers.",
			 function );

			return( -1 );
		}
		allocation_table->sector_identifier = (uint32_t *) reallocation;

		allocation_table->number_of_sector_identifiers = number_of_sector_identifiers;

		if( memory_set(
		     allocation_table->sector_identifier,
		     0,
		     sizeof( uint32_t ) * ( number_of_sector_identifiers - allocation_table->number_of_sector_identifiers ) ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear sector identifiers.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

