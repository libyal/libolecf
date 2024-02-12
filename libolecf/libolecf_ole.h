/*
 * Object Linking and Embedding (OLE) definitions
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

#if !defined( _LIBOLECF_INTERNAL_OLE_H )
#define _LIBOLECF_INTERNAL_OLE_H

#include <common.h>
#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBOLECF )

#include <libolecf/ole.h>

/* Define HAVE_LOCAL_LIBOLECF for local use of libolecf
 * The definitions in <libolecf/ole.h> are copied here
 * for local use of libolecf
 */
#else

/* The value types
 */
enum LIBOLECF_VALUE_TYPES
{
	LIBOLECF_VALUE_TYPE_EMPTY				= 0x00000000UL,
	LIBOLECF_VALUE_TYPE_NULL				= 0x00000001UL,
	LIBOLECF_VALUE_TYPE_INTEGER_16BIT_SIGNED		= 0x00000002UL,
	LIBOLECF_VALUE_TYPE_INTEGER_32BIT_SIGNED		= 0x00000003UL,
	LIBOLECF_VALUE_TYPE_FLOAT_32BIT				= 0x00000004UL,
	LIBOLECF_VALUE_TYPE_DOUBLE_64BIT			= 0x00000005UL,
	LIBOLECF_VALUE_TYPE_CURRENCY				= 0x00000006UL,
	LIBOLECF_VALUE_TYPE_APPLICATION_TIME			= 0x00000007UL,
	LIBOLECF_VALUE_TYPE_BINARY_STRING			= 0x00000008UL,
	LIBOLECF_VALUE_TYPE_IDISPATCH				= 0x00000009UL,
	LIBOLECF_VALUE_TYPE_ERROR				= 0x0000000aUL,
	LIBOLECF_VALUE_TYPE_BOOLEAN				= 0x0000000bUL,
	LIBOLECF_VALUE_TYPE_VARIANT				= 0x0000000cUL,
	LIBOLECF_VALUE_TYPE_IUNKNOWN				= 0x0000000dUL,
	LIBOLECF_VALUE_TYPE_FIXED_POINT_128BIT			= 0x0000000eUL,

	LIBOLECF_VALUE_TYPE_INTEGER_8BIT_SIGNED			= 0x00000010UL,
	LIBOLECF_VALUE_TYPE_INTEGER_8BIT_UNSIGNED		= 0x00000011UL,
	LIBOLECF_VALUE_TYPE_INTEGER_16BIT_UNSIGNED		= 0x00000012UL,
	LIBOLECF_VALUE_TYPE_INTEGER_32BIT_UNSIGNED		= 0x00000013UL,
	LIBOLECF_VALUE_TYPE_INTEGER_64BIT_SIGNED		= 0x00000014UL,
	LIBOLECF_VALUE_TYPE_INTEGER_64BIT_UNSIGNED		= 0x00000015UL,
	LIBOLECF_VALUE_TYPE_INTEGER_SIGNED			= 0x00000016UL,
	LIBOLECF_VALUE_TYPE_INTEGER_UNSIGNED			= 0x00000017UL,
	LIBOLECF_VALUE_TYPE_VOID				= 0x00000018UL,
	LIBOLECF_VALUE_TYPE_HRESULT				= 0x00000019UL,
	LIBOLECF_VALUE_TYPE_POINTER				= 0x0000001aUL,
	LIBOLECF_VALUE_TYPE_SAFE_ARRAY				= 0x0000001bUL,
	LIBOLECF_VALUE_TYPE_ARRAY				= 0x0000001cUL,
	LIBOLECF_VALUE_TYPE_USER_DEFINED			= 0x0000001dUL,
	LIBOLECF_VALUE_TYPE_STRING_ASCII			= 0x0000001eUL,
	LIBOLECF_VALUE_TYPE_STRING_UNICODE			= 0x0000001fUL,

	LIBOLECF_VALUE_TYPE_FILETIME				= 0x00000040UL,
	LIBOLECF_VALUE_TYPE_BINARY_DATA				= 0x00000041UL,
	LIBOLECF_VALUE_TYPE_STREAM				= 0x00000042UL,
	LIBOLECF_VALUE_TYPE_STORAGE				= 0x00000043UL,
	LIBOLECF_VALUE_TYPE_STREAMED_OBJECT			= 0x00000044UL,
	LIBOLECF_VALUE_TYPE_STORED_OBJECT			= 0x00000045UL,
	LIBOLECF_VALUE_TYPE_BINARY_DATA_OBJECT			= 0x00000046UL,
	LIBOLECF_VALUE_TYPE_CLIPBOARD_FORMAT			= 0x00000047UL,
	LIBOLECF_VALUE_TYPE_GUID				= 0x00000048UL,
	LIBOLECF_VALUE_TYPE_VERSIONED_STREAM			= 0x00000049UL,

	LIBOLECF_VALUE_TYPE_MULTI_VALUE_INTEGER_16BIT_SIGNED	= 0x00001002UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_INTEGER_32BIT_SIGNED	= 0x00001003UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_FLOAT_32BIT		= 0x00001004UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_DOUBLE_64BIT		= 0x00001005UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_CURRENCY		= 0x00001006UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_APPLICATION_TIME	= 0x00001007UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_BINARY_STRING		= 0x00001008UL,

	LIBOLECF_VALUE_TYPE_MULTI_VALUE_BOOLEAN			= 0x0000100bUL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_VARIANT			= 0x0000100cUL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_IUNKNOWN		= 0x0000100dUL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_FIXED_POINT_128BIT	= 0x0000100eUL,

	LIBOLECF_VALUE_TYPE_MULTI_VALUE_INTEGER_8BIT_SIGNED	= 0x00001010UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_INTEGER_8BIT_UNSIGNED	= 0x00001011UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_INTEGER_16BIT_UNSIGNED	= 0x00001012UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_INTEGER_32BIT_UNSIGNED	= 0x00001013UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_INTEGER_64BIT_SIGNED	= 0x00001014UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_INTEGER_64BIT_UNSIGNED	= 0x00001015UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_INTEGER_SIGNED		= 0x00001016UL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_INTEGER_UNSIGNED	= 0x00001017UL,

	LIBOLECF_VALUE_TYPE_MULTI_VALUE_STRING_ASCII		= 0x0000101eUL,
	LIBOLECF_VALUE_TYPE_MULTI_VALUE_STRING_UNICODE		= 0x0000101fUL,
};

#endif /* !defined( HAVE_LOCAL_LIBOLECF ) */

#ifdef __cplusplus
}
#endif

#endif /* !defined( _LIBOLECF_INTERNAL_OLE_H ) */

