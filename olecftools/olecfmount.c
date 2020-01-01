/*
 * Mounts an Object Linking and Embedding (OLE) Compound File (CF)
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
#include <file_stream.h>
#include <memory.h>
#include <system_string.h>
#include <types.h>

#include <stdio.h>

#if defined( HAVE_IO_H ) || defined( WINAPI )
#include <io.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "mount_dokan.h"
#include "mount_fuse.h"
#include "mount_handle.h"
#include "olecftools_getopt.h"
#include "olecftools_i18n.h"
#include "olecftools_libcerror.h"
#include "olecftools_libclocale.h"
#include "olecftools_libcnotify.h"
#include "olecftools_libolecf.h"
#include "olecftools_output.h"
#include "olecftools_signal.h"
#include "olecftools_unused.h"

mount_handle_t *olecfmount_mount_handle = NULL;
int olecfmount_abort                    = 0;

/* Prints usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use olecfmount to mount an Object Linking and Embedding (OLE) Compound File (CF)\n\n" );

	fprintf( stream, "Usage: olecfmount [ -c codepage ] [ -X extended_options ] [ -hvV ] file\n"
	                 "                  mount_point\n\n" );

	fprintf( stream, "\tfile:        an Object Linking and Embedding (OLE) Compound File (CF)\n\n" );
	fprintf( stream, "\tmount_point: the directory to serve as mount point\n\n" );

	fprintf( stream, "\t-c:          codepage of ASCII strings, options: ascii, windows-874, windows-932,\n"
	                 "\t             windows-936, windows-949, windows-950, windows-1250, windows-1251,\n"
	                 "\t             windows-1252 (default), windows-1253, windows-1254, windows-1255,\n"
	                 "\t             windows-1256, windows-1257 or windows-1258\n" );
	fprintf( stream, "\t-h:          shows this help\n" );
	fprintf( stream, "\t-v:          verbose output to stderr, while olecfmount will remain running in the\n"
	                 "\t             foreground\n" );
	fprintf( stream, "\t-V:          print version\n" );
	fprintf( stream, "\t-X:          extended options to pass to sub system\n" );
}

/* Signal handler for olecfmount
 */
void olecfmount_signal_handler(
      olecftools_signal_t signal OLECFTOOLS_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "olecfmount_signal_handler";

	OLECFTOOLS_UNREFERENCED_PARAMETER( signal )

	olecfmount_abort = 1;

	if( olecfmount_mount_handle != NULL )
	{
		if( mount_handle_signal_abort(
		     olecfmount_mount_handle,
		     &error ) != 1 )
		{
			libcnotify_printf(
			 "%s: unable to signal mount handle to abort.\n",
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
	libolecf_error_t *error                     = NULL;
	system_character_t *mount_point             = NULL;
	system_character_t *option_codepage         = NULL;
	system_character_t *option_extended_options = NULL;
	system_character_t *source                  = NULL;
	char *program                               = "olecfmount";
	system_integer_t option                     = 0;
	int result                                  = 0;
	int verbose                                 = 0;

#if defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE )
	struct fuse_operations olecfmount_fuse_operations;

	struct fuse_args olecfmount_fuse_arguments = FUSE_ARGS_INIT(0, NULL);
	struct fuse_chan *olecfmount_fuse_channel  = NULL;
	struct fuse *olecfmount_fuse_handle        = NULL;

#elif defined( HAVE_LIBDOKAN )
	DOKAN_OPERATIONS olecfmount_dokan_operations;
	DOKAN_OPTIONS olecfmount_dokan_options;
#endif

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
	                   _SYSTEM_STRING( "c:hvVX:" ) ) ) != (system_integer_t) -1 )
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

			case (system_integer_t) 'c':
				option_codepage = optarg;

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

			case (system_integer_t) 'X':
				option_extended_options = optarg;

				break;
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
	source = argv[ optind++ ];

	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing mount point.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	mount_point = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libolecf_notify_set_stream(
	 stderr,
	 NULL );
	libolecf_notify_set_verbose(
	 verbose );

	if( mount_handle_initialize(
	     &olecfmount_mount_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize mount handle.\n" );

		goto on_error;
	}
	if( option_codepage != NULL )
	{
		result = mount_handle_set_ascii_codepage(
		          olecfmount_mount_handle,
		          option_codepage,
		          &error );

		if( result == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to set ASCII codepage in mount handle.\n" );

			goto on_error;
		}
		else if( result == 0 )
		{
			fprintf(
			 stderr,
			 "Unsupported ASCII codepage defaulting to: windows-1252.\n" );
		}
	}
	if( mount_handle_open(
	     olecfmount_mount_handle,
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open source file\n" );

		goto on_error;
	}
#if defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE )
	if( option_extended_options != NULL )
	{
		/* This argument is required but ignored
		 */
		if( fuse_opt_add_arg(
		     &olecfmount_fuse_arguments,
		     "" ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable add fuse arguments.\n" );

			goto on_error;
		}
		if( fuse_opt_add_arg(
		     &olecfmount_fuse_arguments,
		     "-o" ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable add fuse arguments.\n" );

			goto on_error;
		}
		if( fuse_opt_add_arg(
		     &olecfmount_fuse_arguments,
		     option_extended_options ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable add fuse arguments.\n" );

			goto on_error;
		}
	}
	if( memory_set(
	     &olecfmount_fuse_operations,
	     0,
	     sizeof( struct fuse_operations ) ) == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to clear fuse operations.\n" );

		goto on_error;
	}
	olecfmount_fuse_operations.open       = &mount_fuse_open;
	olecfmount_fuse_operations.read       = &mount_fuse_read;
	olecfmount_fuse_operations.release    = &mount_fuse_release;
	olecfmount_fuse_operations.opendir    = &mount_fuse_opendir;
	olecfmount_fuse_operations.readdir    = &mount_fuse_readdir;
	olecfmount_fuse_operations.releasedir = &mount_fuse_releasedir;
	olecfmount_fuse_operations.getattr    = &mount_fuse_getattr;
	olecfmount_fuse_operations.destroy    = &mount_fuse_destroy;

	olecfmount_fuse_channel = fuse_mount(
	                           mount_point,
	                           &olecfmount_fuse_arguments );

	if( olecfmount_fuse_channel == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to create fuse channel.\n" );

		goto on_error;
	}
	olecfmount_fuse_handle = fuse_new(
	                          olecfmount_fuse_channel,
	                          &olecfmount_fuse_arguments,
	                          &olecfmount_fuse_operations,
	                          sizeof( struct fuse_operations ),
	                          olecfmount_mount_handle );

	if( olecfmount_fuse_handle == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to create fuse handle.\n" );

		goto on_error;
	}
	if( verbose == 0 )
	{
		if( fuse_daemonize(
		     0 ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable to daemonize fuse.\n" );

			goto on_error;
		}
	}
	result = fuse_loop(
	          olecfmount_fuse_handle );

	if( result != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to run fuse loop.\n" );

		goto on_error;
	}
	fuse_destroy(
	 olecfmount_fuse_handle );

	fuse_opt_free_args(
	 &olecfmount_fuse_arguments );

	return( EXIT_SUCCESS );

#elif defined( HAVE_LIBDOKAN )
	if( memory_set(
	     &olecfmount_dokan_operations,
	     0,
	     sizeof( DOKAN_OPERATIONS ) ) == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to clear dokan operations.\n" );

		goto on_error;
	}
	if( memory_set(
	     &olecfmount_dokan_options,
	     0,
	     sizeof( DOKAN_OPTIONS ) ) == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to clear dokan options.\n" );

		goto on_error;
	}
	olecfmount_dokan_options.Version     = DOKAN_VERSION;
	olecfmount_dokan_options.ThreadCount = 0;
	olecfmount_dokan_options.MountPoint  = mount_point;

	if( verbose != 0 )
	{
		olecfmount_dokan_options.Options |= DOKAN_OPTION_STDERR;
#if defined( HAVE_DEBUG_OUTPUT )
		olecfmount_dokan_options.Options |= DOKAN_OPTION_DEBUG;
#endif
	}
/* This will only affect the drive properties
	olecfmount_dokan_options.Options |= DOKAN_OPTION_REMOVABLE;
*/

#if ( DOKAN_VERSION >= 600 ) && ( DOKAN_VERSION < 800 )
	olecfmount_dokan_options.Options |= DOKAN_OPTION_KEEP_ALIVE;

	olecfmount_dokan_operations.CreateFile           = &mount_dokan_CreateFile;
	olecfmount_dokan_operations.OpenDirectory        = &mount_dokan_OpenDirectory;
	olecfmount_dokan_operations.CreateDirectory      = NULL;
	olecfmount_dokan_operations.Cleanup              = NULL;
	olecfmount_dokan_operations.CloseFile            = &mount_dokan_CloseFile;
	olecfmount_dokan_operations.ReadFile             = &mount_dokan_ReadFile;
	olecfmount_dokan_operations.WriteFile            = NULL;
	olecfmount_dokan_operations.FlushFileBuffers     = NULL;
	olecfmount_dokan_operations.GetFileInformation   = &mount_dokan_GetFileInformation;
	olecfmount_dokan_operations.FindFiles            = &mount_dokan_FindFiles;
	olecfmount_dokan_operations.FindFilesWithPattern = NULL;
	olecfmount_dokan_operations.SetFileAttributes    = NULL;
	olecfmount_dokan_operations.SetFileTime          = NULL;
	olecfmount_dokan_operations.DeleteFile           = NULL;
	olecfmount_dokan_operations.DeleteDirectory      = NULL;
	olecfmount_dokan_operations.MoveFile             = NULL;
	olecfmount_dokan_operations.SetEndOfFile         = NULL;
	olecfmount_dokan_operations.SetAllocationSize    = NULL;
	olecfmount_dokan_operations.LockFile             = NULL;
	olecfmount_dokan_operations.UnlockFile           = NULL;
	olecfmount_dokan_operations.GetFileSecurity      = NULL;
	olecfmount_dokan_operations.SetFileSecurity      = NULL;
	olecfmount_dokan_operations.GetDiskFreeSpace     = NULL;
	olecfmount_dokan_operations.GetVolumeInformation = &mount_dokan_GetVolumeInformation;
	olecfmount_dokan_operations.Unmount              = &mount_dokan_Unmount;

#else
	olecfmount_dokan_operations.ZwCreateFile         = &mount_dokan_ZwCreateFile;
	olecfmount_dokan_operations.Cleanup              = NULL;
	olecfmount_dokan_operations.CloseFile            = &mount_dokan_CloseFile;
	olecfmount_dokan_operations.ReadFile             = &mount_dokan_ReadFile;
	olecfmount_dokan_operations.WriteFile            = NULL;
	olecfmount_dokan_operations.FlushFileBuffers     = NULL;
	olecfmount_dokan_operations.GetFileInformation   = &mount_dokan_GetFileInformation;
	olecfmount_dokan_operations.FindFiles            = &mount_dokan_FindFiles;
	olecfmount_dokan_operations.FindFilesWithPattern = NULL;
	olecfmount_dokan_operations.SetFileAttributes    = NULL;
	olecfmount_dokan_operations.SetFileTime          = NULL;
	olecfmount_dokan_operations.DeleteFile           = NULL;
	olecfmount_dokan_operations.DeleteDirectory      = NULL;
	olecfmount_dokan_operations.MoveFile             = NULL;
	olecfmount_dokan_operations.SetEndOfFile         = NULL;
	olecfmount_dokan_operations.SetAllocationSize    = NULL;
	olecfmount_dokan_operations.LockFile             = NULL;
	olecfmount_dokan_operations.UnlockFile           = NULL;
	olecfmount_dokan_operations.GetFileSecurity      = NULL;
	olecfmount_dokan_operations.SetFileSecurity      = NULL;
	olecfmount_dokan_operations.GetDiskFreeSpace     = NULL;
	olecfmount_dokan_operations.GetVolumeInformation = &mount_dokan_GetVolumeInformation;
	olecfmount_dokan_operations.Unmounted            = NULL;
	olecfmount_dokan_operations.FindStreams          = NULL;
	olecfmount_dokan_operations.Mounted              = NULL;

#endif /* ( DOKAN_VERSION >= 600 ) && ( DOKAN_VERSION < 800 ) */

	result = DokanMain(
	          &olecfmount_dokan_options,
	          &olecfmount_dokan_operations );

	switch( result )
	{
		case DOKAN_SUCCESS:
			break;

		case DOKAN_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: generic error\n" );
			break;

		case DOKAN_DRIVE_LETTER_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: bad drive letter\n" );
			break;

		case DOKAN_DRIVER_INSTALL_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: unable to load driver\n" );
			break;

		case DOKAN_START_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: driver error\n" );
			break;

		case DOKAN_MOUNT_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: unable to assign drive letter\n" );
			break;

		case DOKAN_MOUNT_POINT_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: mount point error\n" );
			break;

		default:
			fprintf(
			 stderr,
			 "Unable to run dokan main: unknown error: %d\n",
			 result );
			break;
	}
	return( EXIT_SUCCESS );

#else
	fprintf(
	 stderr,
	 "No sub system to mount OLECF format.\n" );

	return( EXIT_FAILURE );

#endif /* defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE ) */

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE )
	if( olecfmount_fuse_handle != NULL )
	{
		fuse_destroy(
		 olecfmount_fuse_handle );
	}
	fuse_opt_free_args(
	 &olecfmount_fuse_arguments );
#endif
	if( olecfmount_mount_handle != NULL )
	{
		mount_handle_free(
		 &olecfmount_mount_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

