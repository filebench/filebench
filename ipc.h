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

#ifndef _FB_IPC_H
#define	_FB_IPC_H

#include "filebench.h"

/* Mutex Priority Inheritance and Robustness flags */
#define	IPC_MUTEX_NORMAL	0x0
#define	IPC_MUTEX_PRIORITY	0x1
#define	IPC_MUTEX_ROBUST	0x2
#define	IPC_MUTEX_PRI_ROB	0x3
#define	IPC_NUM_MUTEX_ATTRS	4

#define	FILEBENCH_NSEMS 128

#define	FILEBENCH_ABORT_ERROR  	1
#define	FILEBENCH_ABORT_DONE   	2
#define	FILEBENCH_ABORT_RSRC	3
#define	FILEBENCH_ABORT_FINI	4

	/* run modes */
#define	FILEBENCH_MODE_TIMEOUT	0x0
#define	FILEBENCH_MODE_Q1STDONE	0x1
#define	FILEBENCH_MODE_QALLDONE	0x2

	/* misc. modes */
#define	FILEBENCH_MODE_NOUSAGE	0x01

/*
 * Types of IPC shared memory pools we have.
 * ipc_malloc() gets the type as an argument and
 * allocates a slot from the appropriate pool.
 * */
#define	FILEBENCH_FILESET		0
#define	FILEBENCH_FILESETENTRY		1
#define	FILEBENCH_PROCFLOW		2
#define	FILEBENCH_THREADFLOW		3
#define	FILEBENCH_FLOWOP		4
#define	FILEBENCH_VARIABLE		5
#define	FILEBENCH_AVD			6
#define	FILEBENCH_RANDDIST		7
#define FILEBENCH_CVAR			8
#define FILEBENCH_CVAR_LIB_INFO		9
#define	FILEBENCH_MAXTYPE		FILEBENCH_CVAR_LIB_INFO

/*
 * The values below are selected by intuition: these limits
 * seem to be reasonable for medium-scale workloads. If
 * one needs more processes, threads, flowops, etc., one
 * has to increase these values
 */
#define	FILEBENCH_NFILESETS		(16)
#define	FILEBENCH_NFILESETENTRIES	(1024 * 1024)
#define	FILEBENCH_NPROCFLOWS		(1024)
#define	FILEBENCH_NTHREADFLOWS 		(1024)
/* 16 flowops per threadflow seems reasonable */
#define	FILEBENCH_NFLOWOPS 		(16 * 1024)
/* variables are not the only one that are specified
   explicitly in the .f file. Some special 
   variables are used within FB itself. So, let's
   put this value to some save large value */
#define	FILEBENCH_NVARIABLES		(1024)
#define	FILEBENCH_NAVDS			(4096)
#define	FILEBENCH_NRANDDISTS		(16)
#define FILEBENCH_NCVARS		(16)
#define FILEBENCH_NCVAR_LIB_INFO	(32)
#define	FILEBENCH_MAXBITMAP		FILEBENCH_NFILESETENTRIES

/* these below are not regular pools and are allocated separately from ipc_malloc() */
#define	FILEBENCH_FILESETPATHMEMORY	(FILEBENCH_NFILESETENTRIES * FSE_MAXPATHLEN)
#define	FILEBENCH_STRINGMEMORY		(FILEBENCH_NVARIABLES * 128)
#define FILEBENCH_CVAR_HEAPSIZE		(FILEBENCH_NCVARS * 4096)

typedef struct filebench_shm {
	/*
	 * All fields down to shm_marker are set to zero during
	 * filebench initialization in ipc_init() function.
	 */
	
	/*
	 * Global lists and locks for main Filebench objects:
	 * filesets, procflows, threaflows, and flowops.
	 */
	fileset_t	*shm_filesetlist;
	pthread_mutex_t shm_fileset_lock;
	procflow_t	*shm_procflowlist;
	pthread_mutex_t shm_procflow_lock;
	/* threadflow_t	*shm_threadflowlist; (this one is per procflow) */ 
	pthread_mutex_t shm_threadflow_lock;
	flowop_t	*shm_flowoplist;
	pthread_mutex_t shm_flowop_lock;

	/*
	 * parallel file allocation  control. Restricts number of spawned
	 * allocation threads and allows waiting for allocation to finish.
	 */
	pthread_cond_t	shm_fsparalloc_cv;    /* cv to wait for alloc threads */
	int		shm_fsparalloc_count; /* active alloc thread count */
	pthread_mutex_t	shm_fsparalloc_lock;  /* lock to protect count */

	/*
	 * Procflow and process state
	 */
	int		shm_procs_running; /* count of running processes */
	pthread_mutex_t shm_procs_running_lock;	/* protects shm_procs_running */
	int		shm_f_abort;	/* stop the run NOW! */
	pthread_rwlock_t shm_run_lock;	/* used as barrier to sync run */
	flag_t          shm_procflows_defined_flag;  /* indicates that process
						creator thread has defined all
						the procflows */
	/*
	 * flowop state
	 */
	pthread_rwlock_t shm_flowop_find_lock;	/* prevents flowop_find() */
					    /* during initial flowop creation */


	/*
	 * Variable lits.
	 */
	var_t		*shm_var_list;		/* normal variables */
	var_t		*shm_var_loc_list;	/* variables local to composite flowops */

	/* List of randdist instances (randdist for every random variable) */
	randdist_t	*shm_rand_list;
	cvar_t		*shm_cvar_list;    /* custom variables */
	cvar_library_info_t *shm_cvar_lib_info_list;

	/*
	 * log and statistics dumping controls and state
	 */
	int		shm_debug_level;
	int		shm_bequiet;	/* pause run while collecting stats */
	int		shm_dump_fd;	/* dump file descriptor */
	char		shm_dump_filename[MAXPATHLEN];

	/*
	 * Event generator state
	 */
	int		shm_eventgen_enabled; /* event gen in operation */
	avd_t		shm_eventgen_hz;   /* number of events per sec. */
	uint64_t	shm_eventgen_q;    /* count of unclaimed events */
	pthread_mutex_t	shm_eventgen_lock; /* lock protecting count */
	pthread_cond_t	shm_eventgen_cv;   /* cv to wait on for more events */

	/*
	 * System 5 semaphore state
	 */
	key_t		shm_semkey;
	int		shm_sys_semid;
	char		shm_semids[FILEBENCH_NSEMS];

	/*
	 * Misc. pointers and state
	 */
	char		shm_fscriptname[1024];
	int		shm_id;
	int		shm_rmode;	/* run mode settings */
	int		shm_mmode;	/* misc. mode settings */
	int		shm_1st_err;
	pthread_mutex_t shm_msg_lock;
	pthread_mutexattr_t shm_mutexattr[IPC_NUM_MUTEX_ATTRS];
	char		*shm_string_ptr;
	char		*shm_path_ptr;
	hrtime_t	shm_epoch;
	hrtime_t	shm_starttime;
	int		shm_utid;
	int		lathist_enabled;
	int		shm_cvar_heapsize;

	/*
	 * Shared memory allocation control
	 */
	pthread_mutex_t shm_ism_lock;
	size_t		shm_required;
	size_t		shm_allocated;
	caddr_t		shm_addr;
	char		*shm_ptr;

	/*
	 * Type of plug-in file system client to use. Defaults to
	 * local file system, which is type "0".
	 */
	fb_plugin_type_t shm_filesys_type;

	/*
	 * IPC shared memory pools allocation/deallocation control:
	 *	- bitmap (if fact, bit is an integer here)
	 * 	- last allocated index
	 *	- lock for the operations on the pool
	 */
	int		shm_bitmap[FILEBENCH_MAXTYPE][FILEBENCH_MAXBITMAP];
	int		shm_lastbitmapindex[FILEBENCH_MAXTYPE];
	pthread_mutex_t shm_malloc_lock;

	/*
	 * end of pre-zeroed data. We do not bzero pools, because
	 * otherwise we will touch every page in the pools and
	 * consequently use a lot of physical memory, while
	 * in fact, we might not need so much memory later.
	 */
	int		shm_marker[0];

	/*
	 * IPC shared memory pools. Allocated to users
	 * when ipc_malloc() is called. Not zeroed, but
	 * ipc_malloc() will bzero each allocated slot.
	 */
	fileset_t	shm_fileset[FILEBENCH_NFILESETS];
	filesetentry_t	shm_filesetentry[FILEBENCH_NFILESETENTRIES];
	procflow_t	shm_procflow[FILEBENCH_NPROCFLOWS];
	threadflow_t	shm_threadflow[FILEBENCH_NTHREADFLOWS];
	flowop_t	shm_flowop[FILEBENCH_NFLOWOPS];
	var_t		shm_var[FILEBENCH_NVARIABLES];
	struct avd	shm_avd_ptrs[FILEBENCH_NAVDS];
	randdist_t	shm_randdist[FILEBENCH_NRANDDISTS];
	cvar_t		shm_cvar[FILEBENCH_NCVARS];
	cvar_library_info_t shm_cvar_lib_info[FILEBENCH_NCVAR_LIB_INFO];

	/* these below are not regular pools and are allocated separately from ipc_malloc() */
	char		shm_strings[FILEBENCH_STRINGMEMORY];
	char		shm_filesetpaths[FILEBENCH_FILESETPATHMEMORY];
	char		shm_cvar_heap[FILEBENCH_CVAR_HEAPSIZE];

} filebench_shm_t;

extern char shmpath[128];

extern void ipc_init(void);
extern int ipc_attach(void *shmaddr, char *shmpath);

void *ipc_malloc(int type);
void ipc_free(int type, char *addr);

pthread_mutexattr_t *ipc_mutexattr(int);
pthread_condattr_t *ipc_condattr(void);
int ipc_semidalloc(void);
void ipc_semidfree(int semid);
char *ipc_stralloc(const char *string);
char *ipc_pathalloc(char *string);
void *ipc_cvar_heapalloc(size_t size);
void ipc_cvar_heapfree(void *ptr);
int ipc_mutex_lock(pthread_mutex_t *mutex);
int ipc_mutex_unlock(pthread_mutex_t *mutex);
void ipc_seminit(void);
char *ipc_ismmalloc(size_t size);
int ipc_ismcreate(size_t size);
void ipc_ismdelete(void);
void ipc_fini(void);

extern filebench_shm_t *filebench_shm;

#endif	/* _FB_IPC_H */
