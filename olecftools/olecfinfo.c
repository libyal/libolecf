/*
 * Shows information obtained from an OLE Compound File
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
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "info_handle.h"
#include "olecftools_getopt.h"
#include "olecftools_libcerror.h"
#include "olecftools_libclocale.h"
#include "olecftools_libcnotify.h"
#include "olecftools_libolecf.h"
#include "olecftools_output.h"
#include "olecftools_signal.h"
#include "olecftools_unused.h"

info_handle_t *olecfinfo_info_handle = NULL;
int olecfinfo_abort                  = 0;

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use olecfinfo to determine information about an OLE Compound File.\n\n" );

	fprintf( stream, "Usage: olecfinfo [ -c codepage ] [ -ahvV ] source\n\n" );

	fprintf( stream, "\tsource: the source file\n\n" );

	fprintf( stream, "\t-a:     shows allocation information\n" );
	fprintf( stream, "\t-c:     codepage of ASCII strings, options: ascii, windows-874,\n"
	                 "\t        windows-932, windows-936, windows-949, windows-950,\n"
	                 "\t        windows-1250, windows-1251, windows-1252 (default),\n"
	                 "\t        windows-1253, windows-1254, windows-1255, windows-1256,\n"
	                 "\t        windows-1257 or windows-1258\n" );
	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* Signal handler for olecfinfo
 */
void olecfinfo_signal_handler(
      olecftools_signal_t signal OLECFTOOLS_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function   = "olecfinfo_signal_handler";

	OLECFTOOLS_UNREFERENCED_PARAMETER( signal )

	olecfinfo_abort = 1;

	if( olecfinfo_info_handle != NULL )
	{
		if( info_handle_signal_abort(
		     olecfinfo_info_handle,
		     &error ) != 1 )
		{
			libcnotify_printf(
			 "%s: unable to signal info handle to abort.\n",
			 function );

			libcnotify_print_error_backtrace(
			 error );
			libcerror_error_free(
			 &error );
		}
	}
	/* Force stdin to close otherwise any function reading it will remain blocked
	 */
#if defined( WINAPI ) && !defined( __CYGWIN__ )
	if( _close(
	     0 ) != 0 )
#else
	if( close(
	     0 ) != 0 )
#endif
	{
		libcnotify_printf(
		 "%s: unable to close stdin.\n",
		 function );
	}
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error                  = NULL;
	system_character_t *option_ascii_codepage = NULL;
	system_character_t *source                = NULL;
	char *program                             = "olecfinfo";
	system_integer_t option                   = 0;
	uint8_t show_allocation_information       = 0;
	int result                                = 0;
	int verbose                               = 0;

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
	     "olecftools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
	if( olecftools_output_initialize(
	     _IONBF,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
	olecftools_output_version_fprint(
	 stdout,
	 program );

	while( ( option = olecftools_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "ac:hvV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind - 1 ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'a':
				show_allocation_information = 1;

				break;

			case (system_integer_t) 'c':
				option_ascii_codepage = optarg;

				break;

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				olecftools_output_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libolecf_notify_set_stream(
	 stderr,
	 NULL );
	libolecf_notify_set_verbose(
	 verbose );

	if( info_handle_initialize(
	     &olecfinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize info handle.\n" );

		goto on_error;
	}
	if( option_ascii_codepage != NULL )
	{
		result = info_handle_set_ascii_codepage(
		          olecfinfo_info_handle,
		          option_ascii_codepage,
		          &error );

		if( result == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to set ASCII codepage in info handle.\n" );

			goto on_error;
		}
		else if( result == 0 )
		{
			fprintf(
			 stderr,
			 "Unsupported ASCII codepage defaulting to: windows-1252.\n" );
		}
	}
	if( info_handle_open_input(
	     olecfinfo_info_handle,
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open: %" PRIs_SYSTEM ".\n",
		 source );

		goto on_error;
	}
	if( info_handle_file_fprint(
	     olecfinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to print file information.\n" );

		goto on_error;
	}
	if( info_handle_items_fprint(
	     olecfinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to print file stream and storage items.\n" );

		goto on_error;
	}
	if( show_allocation_information != 0 )
	{
		if( info_handle_unallocated_blocks_fprint(
		     olecfinfo_info_handle,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to print file unallocated blocks.\n" );

			goto on_error;
		}
	}
	if( info_handle_summary_information_fprint(
	     olecfinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to print summary information.\n" );

		goto on_error;
	}
	if( info_handle_document_summary_information_fprint(
	     olecfinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to print document summary information.\n" );

		goto on_error;
	}
	if( info_handle_close(
	     olecfinfo_info_handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close info handle.\n" );

		goto on_error;
	}
	if( info_handle_free(
	     &olecfinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free info handle.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( olecfinfo_info_handle != NULL )
	{
		info_handle_close(
		 olecfinfo_info_handle,
		 NULL );
		info_handle_free(
		 &olecfinfo_info_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

