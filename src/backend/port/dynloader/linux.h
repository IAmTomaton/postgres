/*-------------------------------------------------------------------------
 *
 * Dynamic loader interface for Linux
 *
 *
 * Portions Copyright (c) 1996-2001, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $Id: linux.h,v 1.13 2001/10/25 01:29:37 momjian Exp $
 *
 *-------------------------------------------------------------------------
 */
#ifndef PORT_PROTOS_H
#define PORT_PROTOS_H

#include "utils/dynamic_loader.h"
#ifdef HAVE_DLOPEN
#include <dlfcn.h>
#endif


#ifndef HAVE_DLOPEN

#ifndef HAVE_DLD_H
#define pg_dlsym(handle, funcname)		(NULL)
#define pg_dlclose(handle)			   {}
#else
#define pg_dlsym(handle, funcname)		((PGFunction) dld_get_func((funcname)))
#define pg_dlclose(handle) \
do { \
	dld_unlink_by_file(handle, 1); \
	free(handle); \
} while (0)

#endif

#else /* HAVE_DLOPEN */

#define pg_dlopen(f)	dlopen((f), RTLD_LAZY | RTLD_GLOBAL)
#define pg_dlsym		dlsym
#define pg_dlclose		dlclose
#define pg_dlerror		dlerror

#endif /* HAVE_DLOPEN */

#endif	 /* PORT_PROTOS_H */
