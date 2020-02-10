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

#ifndef _FB_FILESET_H
#define	_FB_FILESET_H

#include "filebench.h"

#define	FILE_ALLOC_BLOCK (off64_t)(1024 * 1024)

#define	FSE_MAXTID 16384

#define	FSE_MAXPATHLEN 16
#define	FSE_TYPE_FILE		0x00
#define	FSE_TYPE_DIR		0x01
#define	FSE_TYPE_LEAFDIR	0x02
#define	FSE_TYPE_MASK		0x03
#define	FSE_FREE		0x04
#define	FSE_EXISTS		0x08
#define	FSE_BUSY		0x10
#define	FSE_REUSING		0x20
#define	FSE_THRD_WAITNG		0x40

typedef struct filesetentry {
	struct filesetentry	*fse_next;	/* master list of entries */
	struct filesetentry	*fse_parent;	/* link to directory */
	avl_node_t		fse_link;	/* links in avl btree, prot. */
						/*    by fs_pick_lock */
	uint_t			fse_index;	/* file order number */
	struct filesetentry	*fse_nextoftype; /* List of specific fse */
	struct fileset		*fse_fileset;	/* Parent fileset */
	char			*fse_path;
	int			fse_depth;
	off64_t			fse_size;
	int			fse_open_cnt;	/* protected by fs_pick_lock */
	int			fse_flags;	/* protected by fs_pick_lock */
} filesetentry_t;

#define	FSE_OFFSETOF(f)	((size_t)(&(((filesetentry_t *)0)->f)))

/* type of fileset entry to obtain */
#define	FILESET_PICKFILE    0x00 /* Pick a file from the set */
#define	FILESET_PICKDIR	    0x01 /* Pick a directory */
#define	FILESET_PICKLEAFDIR 0x02 /* Pick a leaf directory */
#define	FILESET_PICKMASK    0x03 /* Pick type mask */
/* other pick flags */
#define	FILESET_PICKUNIQUE  0x04 /* Pick a unique file or leafdir from the */
				    /* fileset until empty */
#define	FILESET_PICKEXISTS  0x10 /* Pick an existing file */
#define	FILESET_PICKNOEXIST 0x20 /* Pick a file that doesn't exist */
#define	FILESET_PICKBYINDEX 0x40 /* use supplied index number to select file */
#define	FILESET_PICKFREE    FILESET_PICKUNIQUE

/* fileset attributes */
#define	FILESET_IS_RAW_DEV  0x01 /* fileset is a raw device */
#define	FILESET_IS_FILE	    0x02 /* Fileset is emulating a single file */

typedef struct fileset {
	struct fileset	*fs_next;	/* Next in list */
	avd_t		fs_name;	/* Name */
	avd_t		fs_path;	/* Pathname prefix in fileset */
	avd_t		fs_entries;	/* Number of entries attr */
					/* (possibly random) */
	fbint_t		fs_constentries; /* Constant version of enties attr */
	avd_t		fs_leafdirs;	/* Number of leaf directories attr */
					/* (possibly random) */
	fbint_t		fs_constleafdirs; /* Constant version of leafdirs */
					    /* attr */
	avd_t		fs_preallocpercent; /* Prealloc size */
	int		fs_attrs;	/* Attributes */
	avd_t		fs_dirwidth;	/* Explicit or mean for distribution */
	avd_t		fs_dirdepthrv;	/* random variable for dir depth */
	avd_t		fs_size;	/* Explicit or mean for distribution */
	avd_t		fs_dirgamma;	/* Dirdepth Gamma distribution */
					/* (* 1000) defaults to 1500, set */
					/* to 0 for explicit depth */
	avd_t		fs_create;	/* Attr */
	avd_t		fs_paralloc;	/* Attr */
	avd_t		fs_reuse;	/* Attr */
	avd_t		fs_readonly;	/* Attr */
	avd_t		fs_writeonly;	/* Attr */
	avd_t		fs_trust_tree;	/* Attr */
	double		fs_meandepth;	/* Computed mean depth */
	double		fs_meanwidth;	/* Specified mean dir width */
	int		fs_realfiles;	/* Actual files */
	int		fs_realleafdirs; /* Actual explicit leaf directories */
	off64_t		fs_bytes;	/* Total space consumed by files */

	int64_t		fs_idle_files;	/* number of files NOT busy */
	pthread_cond_t	fs_idle_files_cv; /* idle files condition variable */

	int64_t		fs_idle_dirs;	/* number of dirs NOT busy */
	pthread_cond_t	fs_idle_dirs_cv; /* idle dirs condition variable */

	int64_t		fs_idle_leafdirs; /* number of dirs NOT busy */
	pthread_cond_t	fs_idle_leafdirs_cv; /* idle dirs condition variable */

	pthread_mutex_t	fs_pick_lock;	/* per fileset "pick" function lock */
	pthread_cond_t	fs_thrd_wait_cv; /* per fileset file busy wait cv */
	avl_tree_t	fs_free_files;	/* btree of free files */
	avl_tree_t	fs_exist_files;	/* btree of files on device */
	avl_tree_t	fs_noex_files;	/* btree of files NOT on device */
	avl_tree_t	fs_dirs;	/* btree of internal dirs */
	avl_tree_t	fs_free_leaf_dirs; /* btree of free leaf dirs */
	avl_tree_t	fs_exist_leaf_dirs; /* btree of leaf dirs on device */
	avl_tree_t	fs_noex_leaf_dirs;  /* btree of leaf dirs NOT */
					    /* currently on device */
	filesetentry_t	*fs_filelist;	/* List of files */
	uint_t		fs_file_exrotor[FSE_MAXTID];	/* next file to */
							/* select */
	uint_t		fs_file_nerotor;	/* next non existent file */
						/* to select for createfile */
	filesetentry_t	*fs_dirlist;	/* List of directories */
	uint_t		fs_dirrotor;	/* index of next directory to select */
	filesetentry_t	*fs_leafdirlist; /* List of leaf directories */
	uint_t		fs_leafdir_exrotor;	/* Ptr to next existing leaf */
						/* directory to select */
	uint_t		fs_leafdir_nerotor;	/* Ptr to next non-existing */
	int		*fs_filehistop;		/* Ptr to access histogram */
	pthread_mutex_t	fs_histo_lock;	/* lock for incr of histo */
} fileset_t;

int fileset_createsets(void);

void fileset_delete_all_filesets(void);
int fileset_openfile(fb_fdesc_t *fd, fileset_t *fileset,
    filesetentry_t *entry, int flag, int mode, int attrs);
fileset_t *fileset_define(avd_t name, avd_t path);
fileset_t *fileset_find(char *name);
filesetentry_t *fileset_pick(fileset_t *fileset, int flags, int tid,
    int index);
char *fileset_resolvepath(filesetentry_t *entry);
int fileset_iter(int (*cmd)(fileset_t *fileset, int first));
int fileset_print(fileset_t *fileset, int first);
void fileset_unbusy(filesetentry_t *entry, int update_exist,
    int new_exist_val, int open_cnt_incr);
int fileset_dump_histo(fileset_t *fileset, int first);
void fileset_attach_all_histos(void);

#endif	/* _FB_FILESET_H */
