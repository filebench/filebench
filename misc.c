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
 */

#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>
#include <libgen.h>
#include <unistd.h>
#include <strings.h>
#include <sys/time.h>
#include "filebench.h"
#include "ipc.h"
#include "eventgen.h"
#include "utils.h"
#include "fsplug.h"
#include "fbtime.h"

/* File System functions vector */
fsplug_func_t *fs_functions_vec;

extern int lex_lineno;

/*
 * Writes a message consisting of information formated by
 * "fmt" to the log file, dump file or stdout.  The supplied
 * "level" argument determines which file to write to and
 * what other actions to take.
 * The level LOG_DUMP writes to the "dump" file,
 * and will open it on the first invocation. Other levels
 * print to the stdout device, with the amount of information
 * dependent on the error level and the current error level
 * setting in filebench_shm->shm_debug_level.
 */
void filebench_log
__V((int level, const char *fmt, ...))
{
	va_list args;
	hrtime_t now = 0;
	char line[131072];
	char buf[131072];

	/* we want to be able to use filebench_log()
	   eveing before filebench_shm is initialized.
	   In this case, all logs have FATAL level. */
	if (!filebench_shm)
		level = LOG_FATAL;


	if (level == LOG_FATAL)
		goto fatal;

	/* open dumpfile if not already open and writing to it */
	if ((level == LOG_DUMP) &&
	    (*filebench_shm->shm_dump_filename == 0))
		return;

	if ((level == LOG_DUMP) &&
	    (filebench_shm->shm_dump_fd < 0)) {

		filebench_shm->shm_dump_fd =
		    open(filebench_shm->shm_dump_filename,
		    O_RDWR | O_CREAT | O_TRUNC, 0666);
	}

	if ((level == LOG_DUMP) &&
	    (filebench_shm->shm_dump_fd < 0)) {
		(void) snprintf(line, sizeof (line), "Open logfile failed: %s",
		    strerror(errno));
		level = LOG_ERROR;
	}

	/* Quit if this is a LOG_ERROR messages and they are disabled */
	if ((filebench_shm->shm_1st_err) && (level == LOG_ERROR))
		return;

	if (level == LOG_ERROR1) {
		if (filebench_shm->shm_1st_err)
			return;

		/* A LOG_ERROR1 temporarily disables LOG_ERROR messages */
		filebench_shm->shm_1st_err = 1;
		level = LOG_ERROR;
	}

	/* Only log greater or equal than debug setting */
	if ((level != LOG_DUMP) &&
	    (level > filebench_shm->shm_debug_level))
		return;

	now = gethrtime();

fatal:

#ifdef __STDC__
	va_start(args, fmt);
#else
	char *fmt;
	va_start(args);
	fmt = va_arg(args, char *);
#endif

	(void) vsprintf(line, fmt, args);

	va_end(args);

	if (level == LOG_FATAL) {
		(void) fprintf(stderr, "%s\n", line);
		return;
	}

	/* Serialize messages to log */
	(void) ipc_mutex_lock(&filebench_shm->shm_msg_lock);

	if (level == LOG_DUMP) {
		if (filebench_shm->shm_dump_fd != -1) {
			(void) snprintf(buf, sizeof (buf), "%s\n", line);
			/* We ignore the return value of write() */
			if (write(filebench_shm->shm_dump_fd, buf, strlen(buf)));
			(void) fsync(filebench_shm->shm_dump_fd);
			(void) ipc_mutex_unlock(&filebench_shm->shm_msg_lock);
			return;
		}

	} else if (filebench_shm->shm_debug_level > LOG_INFO) {
		if (level < LOG_INFO)
			(void) fprintf(stderr, "%5d: ", (int)my_pid);
		else
			(void) fprintf(stdout, "%5d: ", (int)my_pid);
	}

	if (level < LOG_INFO) {
		(void) fprintf(stderr, "%4.3f: %s",
		    (now - filebench_shm->shm_epoch) / SEC2NS_FLOAT,
		    line);

		if (my_procflow == NULL)
			(void) fprintf(stderr, " around line %d", lex_lineno);

		(void) fprintf(stderr, "\n");
		(void) fflush(stderr);
	} else {
		(void) fprintf(stdout, "%4.3f: %s",
		    (now - filebench_shm->shm_epoch) / SEC2NS_FLOAT,
		    line);
		(void) fprintf(stdout, "\n");
		(void) fflush(stdout);
	}

	(void) ipc_mutex_unlock(&filebench_shm->shm_msg_lock);
}

/*
 * Stops the run and exits filebench. If filebench is
 * currently running a workload, calls procflow_shutdown()
 * to stop the run. Also closes and deletes shared memory.
 */
void
filebench_shutdown(int error) {

	if (error) {
		filebench_log(LOG_DEBUG_IMPL, "Shutdown on error %d", error);
		(void) ipc_mutex_lock(&filebench_shm->shm_procflow_lock);
		if (filebench_shm->shm_f_abort == FILEBENCH_ABORT_FINI) {
			(void) ipc_mutex_unlock(
			    &filebench_shm->shm_procflow_lock);
			return;
		}
		filebench_shm->shm_f_abort = FILEBENCH_ABORT_ERROR;
		(void) ipc_mutex_unlock(&filebench_shm->shm_procflow_lock);
	} else {
		filebench_log(LOG_DEBUG_IMPL, "Shutdown");
	}

	procflow_shutdown();

	(void) unlink("/tmp/filebench_shm");
	ipc_ismdelete();
	exit(error);
}
