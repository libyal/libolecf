/*
 * The internal type definitions
 *
 * Copyright (C) 2008-2022, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBOLECF_INTERNAL_TYPES_H )
#define _LIBOLECF_INTERNAL_TYPES_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBOLECF for local use of libolecf
 * The definitions in <libolecf/types.h> are copied here
 * for local use of libolecf
 */
#if defined( HAVE_LOCAL_LIBOLECF )

/* The following type definitions hide internal data structures
 */
#if defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI )
typedef struct libolecf_file {}			libolecf_file_t;
typedef struct libolecf_item {}			libolecf_item_t;
typedef struct libolecf_property_section {}	libolecf_property_section_t;
typedef struct libolecf_property_set {}		libolecf_property_set_t;
typedef struct libolecf_property_value {}	libolecf_property_value_t;

#else
typedef intptr_t libolecf_file_t;
typedef intptr_t libolecf_item_t;
typedef intptr_t libolecf_property_section_t;
typedef intptr_t libolecf_property_set_t;
typedef intptr_t libolecf_property_value_t;

#endif /* defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI ) */

#endif /* defined( HAVE_LOCAL_LIBOLECF ) */

#endif /* !defined( _LIBOLECF_INTERNAL_TYPES_H ) */

