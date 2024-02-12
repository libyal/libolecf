/*
 * Library to access the Object Linking and Embedding (OLE) Compound File (CF)
 *
 * Copyright (C) 2008-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBOLECF_H )
#define _LIBOLECF_H

#include <libolecf/codepage.h>
#include <libolecf/definitions.h>
#include <libolecf/error.h>
#include <libolecf/extern.h>
#include <libolecf/features.h>
#include <libolecf/ole.h>
#include <libolecf/types.h>

#include <stdio.h>

#if defined( LIBOLECF_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBOLECF_EXTERN \
const char *libolecf_get_version(
             void );

/* Returns the access flags for reading
 *  */
LIBOLECF_EXTERN \
uint8_t libolecf_get_access_flags_read(
         void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_get_codepage(
     int *codepage,
     libolecf_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_set_codepage(
     int codepage,
     libolecf_error_t **error );

/* Determines if a file contains an OLECF file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_check_file_signature(
     const char *filename,
     libolecf_error_t **error );

#if defined( LIBOLECF_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains an OLECF file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_check_file_signature_wide(
     const wchar_t *filename,
     libolecf_error_t **error );

#endif /* defined( LIBOLECF_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBOLECF_HAVE_BFIO )

/* Determines if a file contains an OLECF file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libolecf_error_t **error );

#endif /* defined( LIBOLECF_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Set the verbose notification
 */
LIBOLECF_EXTERN \
void libolecf_notify_set_verbose(
      int verbose );

/* Set the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_notify_set_stream(
     FILE *stream,
     libolecf_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_notify_stream_open(
     const char *filename,
     libolecf_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_notify_stream_close(
     libolecf_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBOLECF_EXTERN \
void libolecf_error_free(
      libolecf_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_error_fprint(
     libolecf_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_error_sprint(
     libolecf_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_error_backtrace_fprint(
     libolecf_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_error_backtrace_sprint(
     libolecf_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * File functions
 * ------------------------------------------------------------------------- */

/* Creates a file
 * Make sure the value file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_initialize(
     libolecf_file_t **file,
     libolecf_error_t **error );

/* Frees a file
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_free(
     libolecf_file_t **file,
     libolecf_error_t **error );

/* Signals the file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_signal_abort(
     libolecf_file_t *file,
     libolecf_error_t **error );

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_open(
     libolecf_file_t *file,
     const char *filename,
     int access_flags,
     libolecf_error_t **error );

#if defined( LIBOLECF_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_open_wide(
     libolecf_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libolecf_error_t **error );

#endif /* defined( LIBOLECF_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBOLECF_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_open_file_io_handle(
     libolecf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libolecf_error_t **error );

#endif /* defined( LIBOLECF_HAVE_BFIO ) */

/* Closes a file
 * Returns 0 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_close(
     libolecf_file_t *file,
     libolecf_error_t **error );

/* Retrieves the sector size
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_get_sector_size(
     libolecf_file_t *file,
     size32_t *sector_size,
     libolecf_error_t **error );

/* Retrieves the short sector size
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_get_short_sector_size(
     libolecf_file_t *file,
     size32_t *short_sector_size,
     libolecf_error_t **error );

/* Retrieves the ASCII codepage
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_get_ascii_codepage(
     libolecf_file_t *file,
     int *ascii_codepage,
     libolecf_error_t **error );

/* Sets the ASCII codepage
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_set_ascii_codepage(
     libolecf_file_t *file,
     int ascii_codepage,
     libolecf_error_t **error );

/* Retrieves the format version
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_get_format_version(
     libolecf_file_t *file,
     uint16_t *major_version,
     uint16_t *minor_version,
     libolecf_error_t **error );

/* Retrieves the number of unallocated blocks
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_get_number_of_unallocated_blocks(
     libolecf_file_t *file,
     int *number_of_unallocated_blocks,
     libolecf_error_t **error );

/* Retrieves a specific unallocated block
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_get_unallocated_block(
     libolecf_file_t *file,
     int unallocated_block_index,
     off64_t *offset,
     size64_t *size,
     libolecf_error_t **error );

/* Retrieves the root item from the file
 * Returns 1 if successful, 0 if no such item or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_get_root_item(
     libolecf_file_t *file,
     libolecf_item_t **root_item,
     libolecf_error_t **error );

/* Retrieves the item for the specific UTF-8 encoded path
 * The path separator is the \ character
 * Returns 1 if successful, 0 if no such item or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_get_item_by_utf8_path(
     libolecf_file_t *file,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libolecf_item_t **item,
     libolecf_error_t **error );

/* Retrieves the item for the specific UTF-16 encoded path
 * The path separator is the \ character
 * Returns 1 if successful, 0 if no such item or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_file_get_item_by_utf16_path(
     libolecf_file_t *file,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libolecf_item_t **item,
     libolecf_error_t **error );

/* -------------------------------------------------------------------------
 * Item functions
 * ------------------------------------------------------------------------- */

/* Frees an item
 * Return 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_free(
     libolecf_item_t **item,
     libolecf_error_t **error );

/* Retrieves the type
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_type(
     libolecf_item_t *item,
     uint8_t *type,
     libolecf_error_t **error );

/* Retrieves the size of the UTF-8 encoded name of the referenced item
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_utf8_name_size(
     libolecf_item_t *item,
     size_t *utf8_string_size,
     libolecf_error_t **error );

/* Retrieves the UTF-8 encoded name of the referenced item
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_utf8_name(
     libolecf_item_t *item,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libolecf_error_t **error );

/* Retrieves the size of the UTF-16 encoded name of the referenced item
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_utf16_name_size(
     libolecf_item_t *item,
     size_t *utf16_string_size,
     libolecf_error_t **error );

/* Retrieves the UTF-16 encoded name of the referenced item
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_utf16_name(
     libolecf_item_t *item,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libolecf_error_t **error );

/* Retrieves the size of the referenced item
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_size(
     libolecf_item_t *item,
     uint32_t *size,
     libolecf_error_t **error );

/* Retrieves the creation date and time
 * The returned time is a 64-bit version of a FILETIME value
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_creation_time(
     libolecf_item_t *item,
     uint64_t *filetime,
     libolecf_error_t **error );

/* Retrieves the modification date and time
 * The returned time is a 64-bit version of a FILETIME value
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_modification_time(
     libolecf_item_t *item,
     uint64_t *filetime,
     libolecf_error_t **error );

/* Retrieves the number of sub items from a item
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_number_of_sub_items(
     libolecf_item_t *item,
     int *number_of_sub_items,
     libolecf_error_t **error );

/* Retrieves the sub item for the specific index from a item
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_sub_item(
     libolecf_item_t *item,
     int sub_item_index,
     libolecf_item_t **sub_item,
     libolecf_error_t **error );

/* Retrieves the sub item for the specific UTF-8 encoded name
 * Returns 1 if successful, 0 if the sub item could not be found or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_sub_item_by_utf8_name(
     libolecf_item_t *item,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libolecf_item_t **sub_item,
     libolecf_error_t **error );

/* Retrieves the sub item for the specific UTF-16 encoded name
 * Returns 1 if successful, 0 if the sub item could not be found or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_sub_item_by_utf16_name(
     libolecf_item_t *item,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libolecf_item_t **sub_item,
     libolecf_error_t **error );

/* Retrieves the sub item for the specific UTF-8 encoded path
 * The path separator is the \ character
 * Returns 1 if successful, 0 if no such item or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_sub_item_by_utf8_path(
     libolecf_item_t *item,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libolecf_item_t **sub_item,
     libolecf_error_t **error );

/* Retrieves the sub item for the specific UTF-16 encoded path
 * The path separator is the \ character
 * Returns 1 if successful, 0 if no such item or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_item_get_sub_item_by_utf16_path(
     libolecf_item_t *item,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libolecf_item_t **sub_item,
     libolecf_error_t **error );

/* -------------------------------------------------------------------------
 * Stream functions
 * ------------------------------------------------------------------------- */

/* Reads stream data from the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
LIBOLECF_EXTERN \
ssize_t libolecf_stream_read_buffer(
         libolecf_item_t *stream,
         uint8_t *buffer,
         size_t size,
         libolecf_error_t **error );

/* Reads stream data a specific offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libolecf_stream_read_buffer_at_offset(
         libolecf_item_t *stream,
         uint8_t *buffer,
         size_t buffer_size,
         off64_t offset,
         libolecf_error_t **error );

/* Seeks a certain offset of the stream data
 * Returns the offset if seek is successful or -1 on error
 */
LIBOLECF_EXTERN \
off64_t libolecf_stream_seek_offset(
         libolecf_item_t *stream,
         off64_t offset,
         int whence,
         libolecf_error_t **error );

/* Retrieves the current offset in the stream data
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_stream_get_offset(
     libolecf_item_t *stream,
     off64_t *offset,
     libolecf_error_t **error );

/* -------------------------------------------------------------------------
 * Property set stream functions
 * ------------------------------------------------------------------------- */

/* Retrieves the property set from a property set stream
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_set_stream_get_set(
     libolecf_item_t *property_set_stream,
     libolecf_property_set_t **property_set,
     libolecf_error_t **error );

/* -------------------------------------------------------------------------
 * Property set functions
 * ------------------------------------------------------------------------- */

/* Frees a property set
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_set_free(
     libolecf_property_set_t **property_set,
     libolecf_error_t **error );

/* Retrieves the class identifier
 * The identifier is a GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_set_get_class_identifier(
     libolecf_property_set_t *property_set,
     uint8_t *guid_data,
     size_t guid_data_size,
     libolecf_error_t **error );

/* Retrieves the number of sections
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_set_get_number_of_sections(
     libolecf_property_set_t *property_set,
     int *number_of_sections,
     libolecf_error_t **error );

/* Retrieves a specific section
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_set_get_section_by_index(
     libolecf_property_set_t *property_set,
     int section_index,
     libolecf_property_section_t **property_section,
     libolecf_error_t **error );

/* -------------------------------------------------------------------------
 * Property section functions
 * ------------------------------------------------------------------------- */

/* Frees a property section
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_section_free(
     libolecf_property_section_t **property_section,
     libolecf_error_t **error );

/* Retrieves the class identifier
 * The identifier is a GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_section_get_class_identifier(
     libolecf_property_section_t *property_section,
     uint8_t *guid_data,
     size_t guid_data_size,
     libolecf_error_t **error );

/* Retrieves the number of properties
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_section_get_number_of_properties(
     libolecf_property_section_t *property_section,
     int *number_of_properties,
     libolecf_error_t **error );

/* Retrieves a specific property
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_section_get_property_by_index(
     libolecf_property_section_t *property_section,
     int property_index,
     libolecf_property_value_t **property_value,
     libolecf_error_t **error );

/* -------------------------------------------------------------------------
 * Property value functions
 * ------------------------------------------------------------------------- */

/* Frees a property value
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_free(
     libolecf_property_value_t **property_value,
     libolecf_error_t **error );

/* Retrieves the identifier (property type)
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_identifier(
     libolecf_property_value_t *property_value,
     uint32_t *identifier,
     libolecf_error_t **error );

/* Retrieves the value type
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_value_type(
     libolecf_property_value_t *property_value,
     uint32_t *value_type,
     libolecf_error_t **error );

/* Retrieves the data size
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_data_size(
     libolecf_property_value_t *property_value,
     size_t *data_size,
     libolecf_error_t **error );

/* Retrieves the data
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_data(
     libolecf_property_value_t *property_value,
     uint8_t *data,
     size_t data_size,
     libolecf_error_t **error );

/* Retrieves the data as a boolean value
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_boolean(
     libolecf_property_value_t *property_value,
     uint8_t *value_boolean,
     libolecf_error_t **error );

/* Retrieves the data as a 16-bit integer value
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_16bit_integer(
     libolecf_property_value_t *property_value,
     uint16_t *value_16bit,
     libolecf_error_t **error );

/* Retrieves the data as a 32-bit integer value
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_32bit_integer(
     libolecf_property_value_t *property_value,
     uint32_t *value_32bit,
     libolecf_error_t **error );

/* Retrieves the data as a 64-bit integer value
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_64bit_integer(
     libolecf_property_value_t *property_value,
     uint64_t *value_64bit,
     libolecf_error_t **error );

/* Retrieves the data as a 64-bit filetime value
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_filetime(
     libolecf_property_value_t *property_value,
     uint64_t *filetime,
     libolecf_error_t **error );

/* Retrieves the size of the data as an UTF-8 string value
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_utf8_string_size(
     libolecf_property_value_t *property_value,
     size_t *utf8_string_size,
     libolecf_error_t **error );

/* Retrieves the data as an UTF-8 string value
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_utf8_string(
     libolecf_property_value_t *property_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libolecf_error_t **error );

/* Retrieves the size of the data as an UTF-16 string value
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_utf16_string_size(
     libolecf_property_value_t *property_value,
     size_t *utf16_string_size,
     libolecf_error_t **error );

/* Retrieves the data as an UTF-16 string value
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_EXTERN \
int libolecf_property_value_get_data_as_utf16_string(
     libolecf_property_value_t *property_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libolecf_error_t **error );

/* -------------------------------------------------------------------------
 * Property value functions - deprecated
 * ------------------------------------------------------------------------- */

/* Retrieves the value data size
 *
 * This function deprecated use libolecf_property_value_get_data_size instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_DEPRECATED \
LIBOLECF_EXTERN \
int libolecf_property_value_get_value_data_size(
     libolecf_property_value_t *property_value,
     size_t *value_data_size,
     libolecf_error_t **error );

/* Retrieves the value data
 *
 * This function deprecated use libolecf_property_value_get_data instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_DEPRECATED \
LIBOLECF_EXTERN \
int libolecf_property_value_get_value_data(
     libolecf_property_value_t *property_value,
     uint8_t *value_data,
     size_t value_data_size,
     libolecf_error_t **error );

/* Retrieves the boolean value
 *
 * This function deprecated use libolecf_property_value_get_data_as_boolean instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_DEPRECATED \
LIBOLECF_EXTERN \
int libolecf_property_value_get_value_boolean(
     libolecf_property_value_t *property_value,
     uint8_t *value_boolean,
     libolecf_error_t **error );

/* Retrieves the 16-bit value
 *
 * This function deprecated use libolecf_property_value_get_data_as_16bit_integer instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_DEPRECATED \
LIBOLECF_EXTERN \
int libolecf_property_value_get_value_16bit(
     libolecf_property_value_t *property_value,
     uint16_t *value_16bit,
     libolecf_error_t **error );

/* Retrieves the 32-bit value
 *
 * This function deprecated use libolecf_property_value_get_data_as_32bit_integer instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_DEPRECATED \
LIBOLECF_EXTERN \
int libolecf_property_value_get_value_32bit(
     libolecf_property_value_t *property_value,
     uint32_t *value_32bit,
     libolecf_error_t **error );

/* Retrieves the 64-bit value
 *
 * This function deprecated use libolecf_property_value_get_data_as_64bit_integer instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_DEPRECATED \
LIBOLECF_EXTERN \
int libolecf_property_value_get_value_64bit(
     libolecf_property_value_t *property_value,
     uint64_t *value_64bit,
     libolecf_error_t **error );

/* Retrieves the 64-bit filetime value
 *
 * This function deprecated use libolecf_property_value_get_data_as_filetime instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_DEPRECATED \
LIBOLECF_EXTERN \
int libolecf_property_value_get_value_filetime(
     libolecf_property_value_t *property_value,
     uint64_t *value_filetime,
     libolecf_error_t **error );

/* Retrieves the UTF-8 string size
 * The returned size includes the end of string character
 *
 * This function deprecated use libolecf_property_value_get_data_as_utf8_string_size instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_DEPRECATED \
LIBOLECF_EXTERN \
int libolecf_property_value_get_value_utf8_string_size(
     libolecf_property_value_t *property_value,
     size_t *utf8_string_size,
     libolecf_error_t **error );

/* Retrieves the UTF-8 string value
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 *
 * This function deprecated use libolecf_property_value_get_data_as_utf8_string instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_DEPRECATED \
LIBOLECF_EXTERN \
int libolecf_property_value_get_value_utf8_string(
     libolecf_property_value_t *property_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libolecf_error_t **error );

/* Retrieves the UTF-16 string size
 * The returned size includes the end of string character
 *
 * This function deprecated use libolecf_property_value_get_data_as_utf16_string_size instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_DEPRECATED \
LIBOLECF_EXTERN \
int libolecf_property_value_get_value_utf16_string_size(
     libolecf_property_value_t *property_value,
     size_t *utf16_string_size,
     libolecf_error_t **error );

/* Retrieves the UTF-16 string value
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 *
 * This function deprecated use libolecf_property_value_get_data_as_utf16_string instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBOLECF_DEPRECATED \
LIBOLECF_EXTERN \
int libolecf_property_value_get_value_utf16_string(
     libolecf_property_value_t *property_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libolecf_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBOLECF_H ) */

