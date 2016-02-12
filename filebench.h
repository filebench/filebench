/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 * Portions Copyright 2008 Denis Cheng
 */

#ifndef _FB_FILEBENCH_H
#define	_FB_FILEBENCH_H

#include "config.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <pthread.h>
#include <signal.h>
#ifndef HAVE_SYSV_SEM
#include <semaphore.h>
#endif
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/times.h>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
/* We use __STDC__ to determine
how to handle functions with variable
number of arguments in filbench_log
function */
#ifdef __STDC__
#include <stdarg.h>
#define	__V(x)  x
#ifndef __P
#define	__P(x)  x
#endif
#else
#include <varargs.h>
#define	__V(x)  (va_alist) va_dcl
#define	__P(x)  ()
#define	const
#endif
#ifdef HAVE_AIO
#include <aio.h>
#endif
#include <dirent.h>

/* Defining our internal types */
typedef uint64_t fbint_t;
#ifndef HAVE_BOOLEAN_T
typedef enum { B_FALSE, B_TRUE } boolean_t;
#endif
#define	TRUE 1
#define	FALSE 0
#ifndef HAVE_U_LONGLONG_T
typedef unsigned long long u_longlong_t;
#endif
#ifndef HAVE_UINT_T
typedef unsigned int uint_t;
#endif
#ifndef MIN
/* not defined on OpenSolaris */
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
/* change 64-postfixed defininition to the regular: on FreeBSD
   all these function are already 64bit  */
#ifndef HAVE_OFF64_T
	#define off64_t off_t
#endif
#ifndef HAVE_STAT64
	/* this will replace both: struct stat64 and function stat64 */
	#define stat64 stat
#endif
#ifndef HAVE_AIO_ERROR64
	#define aio_error64 aio_error
#endif
#ifndef HAVE_AIO_WRITE64
	#define aio_write64 aio_write
	#define aiocb64 aiocb
#endif
#ifndef HAVE_AIO_RETURN64
	#define aio_return64 aio_return
#endif
#ifndef HAVE_OPEN64
	#define open64 open
#endif
#ifndef HAVE_MMAP64
	#define mmap64 mmap
#endif
#ifndef HAVE_FSTAT64
	#define fstat64 fstat
#endif
#ifndef HAVE_LSEEK64
	#define lseek64 lseek
#endif
#ifndef HAVE_PWRITE64
	#define pwrite64 pwrite
#endif
#ifndef HAVE_PREAD64
	#define pread64 pread
#endif

#include "flag.h"
#include "vars.h"
#include "fb_cvar.h"
#include "fb_avl.h"
#include "stats.h"
#include "procflow.h"
#include "misc.h"
#include "fsplug.h"
#include "fileset.h"
#include "threadflow.h"
#include "flowop.h"
#include "fb_random.h"
#include "ipc.h"

extern pid_t my_pid;		/* this process' process id */
extern procflow_t *my_procflow;	/* if slave process, procflow pointer */
extern int errno;
extern char *execname;

void filebench_log __V((int level, const char *fmt, ...));
void filebench_shutdown(int error);
void filebench_plugin_funcvecinit(void);

#define	FILEBENCH_RANDMAX64 UINT64_MAX
#define	FILEBENCH_RANDMAX32 UINT32_MAX

#if defined(_LP64) || (__WORDSIZE == 64)
#define	fb_random fb_random64
#define	FILEBENCH_RANDMAX FILEBENCH_RANDMAX64
#else
#define	fb_random fb_random32
#define	FILEBENCH_RANDMAX FILEBENCH_RANDMAX32
#endif

#ifndef HAVE_SIGIGNORE
/* No sigignore on FreeBSD */
static inline int sigignore(int sig) {
        struct sigaction sa;
        bzero(&sa, sizeof(sa));
        sa.sa_handler = SIG_IGN;
        return (sigaction(sig, &sa, NULL));
}
#endif

#define	KB (1024LL)
#define	MB (KB * KB)
#define	GB (KB * MB)

#define	KB_FLOAT ((double)1024.0)
#define	MB_FLOAT (KB_FLOAT * KB_FLOAT)
#define	GB_FLOAT (KB_FLOAT * MB_FLOAT)

#define	MMAP_SIZE	(1024UL * 1024UL * 1024UL)

#define	FILEBENCH_VERSION	VERSION
#define	FILEBENCH_PROMPT	"filebench> "
#define	MAX_LINE_LEN	1024
#define	MAX_CMD_HIST	128
#define	SHUTDOWN_WAIT_SECONDS	3 /* time to wait for proc / thrd to quit */

#define	FILEBENCH_DONE	 1
#define	FILEBENCH_OK	 0
#define	FILEBENCH_ERROR -1
#define	FILEBENCH_NORSC -2

#endif	/* _FB_FILEBENCH_H */
