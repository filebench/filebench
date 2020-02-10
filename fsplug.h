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
 */


#ifndef _FB_FSPLUG_H
#define	_FB_FSPLUG_H

#include "filebench.h"

/* universal file descriptor for both local and nfs file systems */
typedef union fb_fdesc {
	int		fd_num;		/* OS file descriptor number */
	void		*fd_ptr;	/* Pointer to nfs information block */
} fb_fdesc_t;

typedef struct aiolist aiol_t;

struct fsplug_dir; /* Opaque! */

/* Approximate a dirent as far as we're concerned as a benchmark tool */
struct fsplug_dirent {
	int  bytecost;	/* Size of read operations */
};

/* Functions vector for file system plug-ins */
typedef struct fsplug_func_s {
	char fs_name[16];
	void (*fsp_init_master)(void);		/* Initialize once, in master process */
	void (*fsp_init)(void);				/* Initialize in all processes */

	int (*fsp_freemem)(fb_fdesc_t *, off64_t);
	int (*fsp_open)(fb_fdesc_t *, char *, int, int);
	int (*fsp_pread)(fb_fdesc_t *, caddr_t, fbint_t, off64_t);
	int (*fsp_read)(fb_fdesc_t *, caddr_t, fbint_t);
	int (*fsp_pwrite)(fb_fdesc_t *, caddr_t, fbint_t, off64_t);
	int (*fsp_write)(fb_fdesc_t *, caddr_t, fbint_t);
	int (*fsp_lseek)(fb_fdesc_t *, off64_t, int);
	int (*fsp_ftrunc)(fb_fdesc_t *, off64_t);
	int (*fsp_rename)(const char *, const char *);
	int (*fsp_close)(fb_fdesc_t *);
	int (*fsp_link)(const char *, const char *);
	int (*fsp_symlink)(const char *, const char *);
	int (*fsp_unlink)(char *);
	ssize_t (*fsp_readlink)(const char *, char *, size_t);
	int (*fsp_mkdir)(char *, int);
	int (*fsp_rmdir)(char *);
	struct fsplug_dir *(*fsp_opendir)(char *);
	int (*fsp_readdir)(struct fsplug_dir *, struct fsplug_dirent *);
	int (*fsp_closedir)(struct fsplug_dir *);
	int (*fsp_fsync)(fb_fdesc_t *);
	int (*fsp_stat)(char *, struct stat64 *);
	int (*fsp_fstat)(fb_fdesc_t *, struct stat64 *);
	int (*fsp_access)(const char *, int);
	void (*fsp_recur_rm)(char *);
} fsplug_func_t;

#define FB_FSPLUG_MODULE_FUNC_S	"fsplug_funcs"

/*
 * The current functions vector; statically initialized to that of
 * fb_localfs.c, but may be overwritten in flowop_init()
 */
extern fsplug_func_t *fs_functions_vec;

/* Macros for calling functions */
#define	FB_FREEMEM(fd, sz) \
	(*fs_functions_vec->fsp_freemem)(fd, sz)

#define	FB_OPEN(fd, path, flags, perms) \
	(*fs_functions_vec->fsp_open)(fd, path, flags, perms)

#define	FB_PREAD(fdesc, iobuf, iosize, offset) \
	(*fs_functions_vec->fsp_pread)(fdesc, iobuf, iosize, offset)

#define	FB_READ(fdesc, iobuf, iosize) \
	(*fs_functions_vec->fsp_read)(fdesc, iobuf, iosize)

#define	FB_PWRITE(fdesc, iobuf, iosize, offset) \
	(*fs_functions_vec->fsp_pwrite)(fdesc, iobuf, iosize, offset)

#define	FB_WRITE(fdesc, iobuf, iosize) \
	(*fs_functions_vec->fsp_write)(fdesc, iobuf, iosize)

#define	FB_LSEEK(fdesc, amnt, whence) \
	(*fs_functions_vec->fsp_lseek)(fdesc, amnt, whence)

#define	FB_CLOSE(fdesc) \
	(*fs_functions_vec->fsp_close)(fdesc)

#define	FB_UNLINK(path) \
	(*fs_functions_vec->fsp_unlink)(path)

#define	FB_MKDIR(path, perm) \
	(*fs_functions_vec->fsp_mkdir)(path, perm)

#define	FB_RMDIR(path) \
	(*fs_functions_vec->fsp_rmdir)(path)

#define	FB_OPENDIR(path) \
	(*fs_functions_vec->fsp_opendir)(path)

#define	FB_READDIR(dir,dent) \
	(*fs_functions_vec->fsp_readdir)(dir,dent)

#define	FB_CLOSEDIR(dir) \
	(*fs_functions_vec->fsp_closedir)(dir)

#define	FB_FSYNC(fdesc) \
	(*fs_functions_vec->fsp_fsync)(fdesc)

#define	FB_RECUR_RM(path) \
	(*fs_functions_vec->fsp_recur_rm)(path)

#define	FB_STAT(path, statp) \
	(*fs_functions_vec->fsp_stat)(path, statp)

#define	FB_FSTAT(fdesc, statp) \
	(*fs_functions_vec->fsp_fstat)(fdesc, statp)

#define	FB_FTRUNC(fdesc, size) \
	(*fs_functions_vec->fsp_ftrunc)(fdesc, size)

#define	FB_LINK(existing, new) \
	(*fs_functions_vec->fsp_link)(existing, new)

#define	FB_SYMLINK(name1, name2) \
	(*fs_functions_vec->fsp_symlink)(name1, name2)

#endif /* _FB_FSPLUG_H */
