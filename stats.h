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
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_FB_STATS_H
#define	_FB_STATS_H

#include "filebench.h"
#include "fbtime.h"

void stats_clear(void);
void stats_snap(void);

#define OSPROF_BUCKET_NUMBER	64

struct flowstats {
	/* Eight fields below are updated per each flowop and
	 * added up in globalstats and master flowop at stats_snap() */
	int		fs_count;	/* Number of ops */
	uint64_t	fs_rcount;	/* Number of read ops */
	uint64_t	fs_wcount;	/* Number of write ops */

	uint64_t	fs_bytes;	/* Number of bytes read/written */
	uint64_t	fs_rbytes;	/* Number of bytes read */
	uint64_t	fs_wbytes;	/* Number of bytes written */

	unsigned long	fs_distribution[OSPROF_BUCKET_NUMBER]; /* Used for OSprof */
	hrtime_t	fs_total_lat;
	unsigned long long fs_maxlat;	/* max flowop latency (nanoseconds) */
	unsigned long long fs_minlat; /* min flowop latency (nanoseconds) */

	/* These two fields are used only in globalstats variable
	 * to note the total time of statistics collection: from
	 * stats_clear() to stats_snap() */
	hrtime_t	fs_stime;
	hrtime_t	fs_etime;
};

#define	IS_FLOW_IOP(x) (x->fo_stats.fs_rcount + x->fo_stats.fs_wcount)
#define	STAT_IOPS(x)   ((x->fs_rcount) + (x->fs_wcount))
#define	IS_FLOW_ACTIVE(x) (x->fo_stats.fs_count)
#define	STAT_CPUTIME(x) (x->fs_cpu_op)
#define	STAT_OHEADTIME(x) (x->fs_cpu_ohead)

#endif	/* _FB_STATS_H */
