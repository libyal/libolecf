/*
 * The internal extern definition
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

#if !defined( _LIBOLECF_INTERNAL_EXTERN_H )
#define _LIBOLECF_INTERNAL_EXTERN_H

#include <common.h>

/* Define HAVE_LOCAL_LIBOLECF for local use of libolecf
 */
#if !defined( HAVE_LOCAL_LIBOLECF )

#include <libolecf/extern.h>

#define LIBOLECF_EXTERN_VARIABLE	LIBOLECF_EXTERN

#else
#define LIBOLECF_EXTERN		/* extern */
#define LIBOLECF_EXTERN_VARIABLE	extern

#endif /* !defined( HAVE_LOCAL_LIBOLECF ) */

#endif /* !defined( _LIBOLECF_INTERNAL_EXTERN_H ) */

