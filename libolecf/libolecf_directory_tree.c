/*
 * The directory tree functions
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

#include "libolecf_definitions.h"
#include "libolecf_directory_entry.h"
#include "libolecf_directory_list.h"
#include "libolecf_directory_tree.h"
#include "libolecf_libcdata.h"
#include "libolecf_libcerror.h"
#include "libolecf_libcnotify.h"
#include "libolecf_libuna.h"

#include "olecf_directory.h"

/* Create the directory tree from the directory entry list
 * Returns 1 if succesful, 0 if no directory entries or -1 on error
 */
int libolecf_directory_tree_create(
     libcdata_tree_node_t **directory_tree_root_node,
     uint32_t *short_sector_stream_start_sector_identifier,
     libolecf_directory_entry_t **document_summary_information_directory_entry,
     libolecf_directory_entry_t **summary_information_directory_entry,
     libcdata_list_t *directory_entry_list,
     uint8_t byte_order,
     libcerror_error_t **error )
{
	libcdata_list_element_t *list_element       = NULL;
	libolecf_directory_entry_t *directory_entry = NULL;
	static char *function                       = "libolecf_directory_tree_create";
	int element_index                           = 0;
	int number_of_elements                      = 0;

	if( directory_tree_root_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory tree root node.",
		 function );

		return( -1 );
	}
	if( *directory_tree_root_node != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: directory tree root node already set.",
		 function );

		return( -1 );
	}
	if( short_sector_stream_start_sector_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid short sector stream start sector identifier.",
		 function );

		return( -1 );
	}
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

		goto on_error;
	}
	if( libcdata_list_get_number_of_elements(
	     directory_entry_list,
	     &number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in directory entry list.",
		 function );

		goto on_error;
	}
	if( number_of_elements == 0 )
	{
		return( 0 );
	}
	for( element_index = 0;
	     element_index < number_of_elements;
	     element_index++ )
	{
		if( libcdata_list_element_get_value(
		     list_element,
		     (intptr_t **) &directory_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value from element: %d.",
			 function,
			 element_index );

			goto on_error;
		}
		if( directory_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing directory entry: %d.",
			 function,
			 element_index );

			goto on_error;
		}
		if( directory_entry->type == LIBOLECF_ITEM_TYPE_ROOT_STORAGE )
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

			goto on_error;
		}
	}
	if( list_element == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: unable to find root storage directory entry.",
		 function );

		goto on_error;
	}
#if defined( HAVE_VERBOSE_OUTPUT ) || defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( element_index != 0 )
		{
			libcnotify_printf(
			 "%s: root storage is not first directory entry.\n",
			 function );
		}
		if( directory_entry->previous_directory_identifier != LIBOLECF_SECTOR_IDENTIFIER_UNUSED )
		{
			libcnotify_printf(
			 "%s: previous directory identifier in root storage is not unused.\n",
			 function );
		}
		if( directory_entry->next_directory_identifier != LIBOLECF_SECTOR_IDENTIFIER_UNUSED )
		{
			libcnotify_printf(
			 "%s: next directory identifier in root storage is not unused.\n",
			 function );
		}
	}
#endif
	if( directory_entry->sub_directory_identifier == LIBOLECF_SECTOR_IDENTIFIER_UNUSED )
	{
		return( 0 );
	}
	if( libcdata_tree_node_initialize(
	     directory_tree_root_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create directory root node.",
		 function );

		goto on_error;
	}
	if( libcdata_tree_node_set_value(
	     *directory_tree_root_node,
	     (intptr_t *) directory_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set directory root node value.",
		 function );

		goto on_error;
	}
	*short_sector_stream_start_sector_identifier = directory_entry->sector_identifier;

	if( libolecf_directory_tree_create_process_entry(
	     *directory_tree_root_node,
	     directory_entry,
	     document_summary_information_directory_entry,
	     summary_information_directory_entry,
	     directory_entry_list,
	     directory_entry,
	     byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to process sub directory entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *directory_tree_root_node != NULL )
	{
		/* The directory entry is managed by the list
		 */
		libcdata_tree_node_free(
		 directory_tree_root_node,
		 NULL,
		 NULL );
	}
	return( -1 );
}

/* Process the directory entry and adds it to the directory tree node
 * Returns 1 if succesful or -1 on error
 */
int libolecf_directory_tree_create_process_entry(
     libcdata_tree_node_t *directory_tree_node,
     const libolecf_directory_entry_t *root_directory_entry,
     libolecf_directory_entry_t **document_summary_information_directory_entry,
     libolecf_directory_entry_t **summary_information_directory_entry,
     libcdata_list_t *directory_entry_list,
     libolecf_directory_entry_t *directory_entry,
     uint8_t byte_order,
     libcerror_error_t **error )
{
	libcdata_tree_node_t *parent_node                 = NULL;
	libolecf_directory_entry_t *directory_entry_value = NULL;
	libcdata_tree_node_t *tree_node                   = NULL;
	static char *function                             = "libolecf_directory_tree_create_process_entry";
	int result                                        = 0;

	if( directory_tree_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory tree node.",
		 function );

		return( -1 );
	}
	if( root_directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid root directory entry.",
		 function );

		return( -1 );
	}
	if( document_summary_information_directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid document summary information directory entry.",
		 function );

		return( -1 );
	}
	if( summary_information_directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid summary information directory entry.",
		 function );

		return( -1 );
	}
	if( directory_entry->name_size == 28 )
	{
		result = libuna_utf8_string_compare_with_utf16_stream(
		          (uint8_t *) "\005DocumentSummaryInformation",
		          28,
		          directory_entry->name,
		          directory_entry->name_size,
		          byte_order,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to compare directory entry name.",
			 function );

			goto on_error;
		}
		else if( result == 1 )
		{
			*document_summary_information_directory_entry = directory_entry;
		}
	}
	else if( directory_entry->name_size == 20 )
	{
		result = libuna_utf8_string_compare_with_utf16_stream(
		          (uint8_t *) "\005SummaryInformation",
		          20,
		          directory_entry->name,
		          directory_entry->name_size,
		          byte_order,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to compare directory entry name.",
			 function );

			goto on_error;
		}
		else if( result == 1 )
		{
			*summary_information_directory_entry = directory_entry;
		}
	}
	/* Process sub directory identifier
	 */
	if( ( directory_entry->sub_directory_identifier != LIBOLECF_SECTOR_IDENTIFIER_UNUSED )
	 && ( directory_entry->sub_directory_identifier != 0 )
	 && ( root_directory_entry->directory_identifier == 0 ) )
	{
		result = libolecf_directory_list_get_element_by_identifier(
		          directory_entry_list,
		          directory_entry->sub_directory_identifier,
		          &directory_entry_value,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve sub directory entry list element: %" PRIu32 ".",
			 function,
			 directory_entry->sub_directory_identifier );

			goto on_error;
		}
		else if( result != 0 )
		{
			if( directory_entry_value == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing sub directory entry: %" PRIu32 ".",
				 function,
				 directory_entry->sub_directory_identifier );

				goto on_error;
			}
			if( directory_entry_value->set_in_tree != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
				 "%s: directory entry tree node already set.",
				 function );

				goto on_error;
			}
			if( libcdata_tree_node_initialize(
			     &tree_node,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create directory tree node.",
				 function );

				goto on_error;
			}
			if( libcdata_tree_node_set_value(
			     tree_node,
			     (intptr_t *) directory_entry_value,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set directory tree node value.",
				 function );

				goto on_error;
			}
			if( libcdata_tree_node_insert_node(
			     directory_tree_node,
			     tree_node,
			     (int (*)(intptr_t *, intptr_t *, libcerror_error_t **)) &libolecf_directory_entry_compare,
			     LIBCDATA_INSERT_FLAG_UNIQUE_ENTRIES,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to insert sub directory tree node.",
				 function );

				goto on_error;
			}
			directory_entry_value->set_in_tree = 1;

			if( libolecf_directory_tree_create_process_entry(
			     tree_node,
			     root_directory_entry,
			     document_summary_information_directory_entry,
			     summary_information_directory_entry,
			     directory_entry_list,
			     directory_entry_value,
			     byte_order,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to process sub directory entry.",
				 function );

				tree_node = NULL;

				goto on_error;
			}
			tree_node = NULL;
		}
	}
	/* Process previous directory identifier
	 */
	if( directory_entry->previous_directory_identifier != LIBOLECF_SECTOR_IDENTIFIER_UNUSED )
	{
		result = libolecf_directory_list_get_element_by_identifier(
		          directory_entry_list,
		          (int) directory_entry->previous_directory_identifier,
		          &directory_entry_value,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve previous directory entry: 0x%08" PRIx32 ".",
			 function,
			 directory_entry->previous_directory_identifier );

			goto on_error;
		}
		else if( result != 0 )
		{
			if( directory_entry_value == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing previous directory entry: %" PRIu32 ".",
				 function,
				 directory_entry->previous_directory_identifier );

				goto on_error;
			}
			if( directory_entry_value->set_in_tree != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
				 "%s: directory entry tree node already set.",
				 function );

				goto on_error;
			}
			if( libcdata_tree_node_initialize(
			     &tree_node,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create directory tree node.",
				 function );

				goto on_error;
			}
			if( libcdata_tree_node_set_value(
			     tree_node,
			     (intptr_t *) directory_entry_value,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set directory tree node value.",
				 function );

				goto on_error;
			}
			if( libcdata_tree_node_get_parent_node(
			     directory_tree_node,
			     &parent_node,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve parent node.",
				 function );

				goto on_error;
			}
			if( libcdata_tree_node_insert_node(
			     parent_node,
			     tree_node,
			     (int (*)(intptr_t *, intptr_t *, libcerror_error_t **)) &libolecf_directory_entry_compare,
			     LIBCDATA_INSERT_FLAG_UNIQUE_ENTRIES,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to insert previous directory tree node.",
				 function );

				goto on_error;
			}
			directory_entry_value->set_in_tree = 1;

			if( libolecf_directory_tree_create_process_entry(
			     tree_node,
			     root_directory_entry,
			     document_summary_information_directory_entry,
			     summary_information_directory_entry,
			     directory_entry_list,
			     directory_entry_value,
			     byte_order,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to process previous directory entry.",
				 function );

				tree_node = NULL;

				goto on_error;
			}
			tree_node = NULL;
		}
	}
	/* Process next directory identifier
	 */
	if( directory_entry->next_directory_identifier != LIBOLECF_SECTOR_IDENTIFIER_UNUSED )
	{
		result = libolecf_directory_list_get_element_by_identifier(
		          directory_entry_list,
		          (int) directory_entry->next_directory_identifier,
		          &directory_entry_value,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve next directory entry: 0x%08" PRIx32 ".",
			 function,
			 directory_entry->next_directory_identifier );

			goto on_error;
		}
		else if( result != 0 )
		{
			if( directory_entry_value == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing next directory entry: %" PRIu32 ".",
				 function,
				 directory_entry->sub_directory_identifier );

				goto on_error;
			}
			if( directory_entry_value->set_in_tree != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
				 "%s: directory entry tree node already set.",
				 function );

				goto on_error;
			}
			if( libcdata_tree_node_initialize(
			     &tree_node,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create directory tree node.",
				 function );

				goto on_error;
			}
			if( libcdata_tree_node_set_value(
			     tree_node,
			     (intptr_t *) directory_entry_value,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set directory tree node value.",
				 function );

				goto on_error;
			}
			if( libcdata_tree_node_get_parent_node(
			     directory_tree_node,
			     &parent_node,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve parent node.",
				 function );

				goto on_error;
			}
			if( libcdata_tree_node_insert_node(
			     parent_node,
			     tree_node,
			     (int (*)(intptr_t *, intptr_t *, libcerror_error_t **)) &libolecf_directory_entry_compare,
			     LIBCDATA_INSERT_FLAG_UNIQUE_ENTRIES,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to insert next directory tree node.",
				 function );

				goto on_error;
			}
			directory_entry_value->set_in_tree = 1;

			if( libolecf_directory_tree_create_process_entry(
			     tree_node,
			     root_directory_entry,
			     document_summary_information_directory_entry,
			     summary_information_directory_entry,
			     directory_entry_list,
			     directory_entry_value,
			     byte_order,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to process next directory entry.",
				 function );

				tree_node = NULL;

				goto on_error;
			}
			tree_node = NULL;
		}
	}
	return( 1 );

on_error:
	if( tree_node != NULL )
	{
		libcdata_tree_node_free(
		 &tree_node,
		 NULL,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the sub node for the specific UTF-8 formatted name
 * Returns 1 if successful, 0 if no such sub node or -1 on error
 */
int libolecf_directory_tree_get_sub_node_by_utf8_name(
     libcdata_tree_node_t *directory_tree_node,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     uint8_t byte_order,
     libcdata_tree_node_t **sub_directory_tree_node,
     libcerror_error_t **error )
{
	libolecf_directory_entry_t *sub_directory_entry = NULL;
	static char *function                           = "libolecf_directory_tree_get_sub_node_by_utf8_name";
	int number_of_sub_nodex                         = 0;
	int result                                      = 0;
	int sub_node_index                              = 0;

	if( directory_tree_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory tree node.",
		 function );

		return( -1 );
	}
	if( sub_directory_tree_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub directory tree node.",
		 function );

		return( -1 );
	}
	if( libcdata_tree_node_get_number_of_sub_nodes(
	     directory_tree_node,
	     &number_of_sub_nodex,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sub nodex.",
		 function );

		return( -1 );
	}
	for( sub_node_index = 0;
	     sub_node_index < number_of_sub_nodex;
	     sub_node_index++ )
        {
		if( libcdata_tree_node_get_sub_node_by_index(
		     directory_tree_node,
		     sub_node_index,
		     sub_directory_tree_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of sub nodex: %d.",
			 function,
			 sub_node_index );

			return( -1 );
		}
		if( libcdata_tree_node_get_value(
		     *sub_directory_tree_node,
		     (intptr_t **) &sub_directory_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value from sub directory tree node: %d.",
			 function,
			 sub_node_index );

			return( -1 );
		}
		if( sub_directory_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing sub directory entry: %d.",
			 function,
			 sub_node_index );

			return( -1 );
		}
		result = libuna_utf8_string_compare_with_utf16_stream(
		          utf8_string,
		          utf8_string_length,
		          sub_directory_entry->name,
		          sub_directory_entry->name_size,
		          byte_order,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to compare sub directory entry: %d name.",
			 function,
			 sub_node_index );

			return( -1 );
		}
		else if( result == 1 )
		{
			break;
		}
		*sub_directory_tree_node = NULL;
	}
	return( result );
}

/* Retrieves the sub node for the specific UTF-16 formatted name
 * Returns 1 if successful, 0 if no such sub node or -1 on error
 */
int libolecf_directory_tree_get_sub_node_by_utf16_name(
     libcdata_tree_node_t *directory_tree_node,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     uint8_t byte_order,
     libcdata_tree_node_t **sub_directory_tree_node,
     libcerror_error_t **error )
{
	libolecf_directory_entry_t *sub_directory_entry = NULL;
	static char *function                           = "libolecf_directory_tree_get_sub_node_by_utf16_name";
	int number_of_sub_nodex                         = 0;
	int result                                      = 0;
	int sub_node_index                              = 0;

	if( directory_tree_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory tree node.",
		 function );

		return( -1 );
	}
	if( sub_directory_tree_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub directory tree node.",
		 function );

		return( -1 );
	}
	if( libcdata_tree_node_get_number_of_sub_nodes(
	     directory_tree_node,
	     &number_of_sub_nodex,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sub nodex.",
		 function );

		return( -1 );
	}
	for( sub_node_index = 0;
	     sub_node_index < number_of_sub_nodex;
	     sub_node_index++ )
        {
		if( libcdata_tree_node_get_sub_node_by_index(
		     directory_tree_node,
		     sub_node_index,
		     sub_directory_tree_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of sub nodex: %d.",
			 function,
			 sub_node_index );

			return( -1 );
		}
		if( libcdata_tree_node_get_value(
		     *sub_directory_tree_node,
		     (intptr_t **) &sub_directory_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value from sub directory tree node: %d.",
			 function,
			 sub_node_index );

			return( -1 );
		}
		if( sub_directory_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing sub directory entry: %d.",
			 function,
			 sub_node_index );

			return( -1 );
		}
		result = libuna_utf16_string_compare_with_utf16_stream(
		          utf16_string,
		          utf16_string_length,
		          sub_directory_entry->name,
		          sub_directory_entry->name_size,
		          byte_order,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to compare sub directory entry: %d name.",
			 function,
			 sub_node_index );

			return( -1 );
		}
		else if( result == 1 )
		{
			break;
		}
		*sub_directory_tree_node = NULL;
	}
	return( result );
}

