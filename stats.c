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
#include <sys/types.h>
#include <stdarg.h>
#include <limits.h>

#include "filebench.h"
#include "flowop.h"
#include "vars.h"
#include "stats.h"
#include "fbtime.h"

/*
 * A set of routines for collecting and dumping various filebench
 * run statistics.
 */

/* Global statistics */
static struct flowstats *globalstats = NULL;

/*
 * Add a flowstat b to a, leave sum in a.
 */
static void
stats_add(struct flowstats *a, struct flowstats *b)
{
	int i;

	a->fs_count += b->fs_count;
	a->fs_rcount += b->fs_rcount;
	a->fs_wcount += b->fs_wcount;
	a->fs_bytes += b->fs_bytes;
	a->fs_rbytes += b->fs_rbytes;
	a->fs_wbytes += b->fs_wbytes;
	a->fs_total_lat += b->fs_total_lat;

	if (b->fs_maxlat > a->fs_maxlat)
		a->fs_maxlat = b->fs_maxlat;

	if (b->fs_minlat < a->fs_minlat)
		a->fs_minlat = b->fs_minlat;

	for (i = 0; i < OSPROF_BUCKET_NUMBER; i++)
		a->fs_distribution[i] += b->fs_distribution[i];
}

/*
 * Takes a "snapshot" of the global statistics. Actually, it calculates
 * them from the local statistics maintained by each flowop.
 * First the routine pauses filebench, then rolls the statistics for
 * each flowop into its associated FLOW_MASTER flowop.
 * Next all the FLOW_MASTER flowops' statistics are written
 * to the log file followed by the global totals. Then filebench
 * operation is allowed to resume.
 */
void
stats_snap(void)
{
	struct flowstats *iostat = &globalstats[FLOW_TYPE_IO];
	struct flowstats *aiostat = &globalstats[FLOW_TYPE_AIO];
	hrtime_t orig_starttime;
	flowop_t *flowop;
	char *str;
	double total_time_sec;

	if (!globalstats) {
		filebench_log(LOG_ERROR,
		    "'stats snap' called before 'stats clear'");
		return;
	}

	/* don't print out if run ended in error */
	if (filebench_shm->shm_f_abort == FILEBENCH_ABORT_ERROR) {
		filebench_log(LOG_ERROR,
		    "NO VALID RESULTS! Filebench run terminated prematurely");
		return;
	}

	/* Freeze statistics during update */
	filebench_shm->shm_bequiet = 1;

	/* We want to have blank global statistics each
	 * time we start the summation process, but the
	 * statistics collection start time must remain
	 * unchanged (it's a snapshot compared to the original
	 * start time). */
	orig_starttime = globalstats->fs_stime;
	(void) memset(globalstats, 0, FLOW_TYPES * sizeof(struct flowstats));
	globalstats->fs_stime = orig_starttime;
	globalstats->fs_etime = gethrtime();

	total_time_sec = (globalstats->fs_etime -
			globalstats->fs_stime) / SEC2NS_FLOAT;
	filebench_log(LOG_DEBUG_SCRIPT, "Stats period = %.0f sec",
			total_time_sec);

	/* Similarly we blank the master flowop statistics */
	flowop = filebench_shm->shm_flowoplist;
	while (flowop) {
		if (flowop->fo_instance == FLOW_MASTER) {
			(void) memset(&flowop->fo_stats, 0, sizeof(struct flowstats));
			flowop->fo_stats.fs_minlat = ULLONG_MAX;
		}
		flowop = flowop->fo_next;
	}

	/* Roll up per-flowop statistics in globalstats and master flowops */
	flowop = filebench_shm->shm_flowoplist;
	while (flowop) {
		flowop_t *flowop_master;

		if (flowop->fo_instance <= FLOW_DEFINITION) {
			flowop = flowop->fo_next;
			continue;
		}

		/* Roll up per-flowop into global stats */
		stats_add(&globalstats[flowop->fo_type], &flowop->fo_stats);
		stats_add(&globalstats[FLOW_TYPE_GLOBAL], &flowop->fo_stats);

		flowop_master = flowop_find_one(flowop->fo_name, FLOW_MASTER);
		if (flowop_master) {
			/* Roll up per-flowop stats into master */
			stats_add(&flowop_master->fo_stats, &flowop->fo_stats);
		} else {
			filebench_log(LOG_DEBUG_NEVER,
			    "flowop_stats could not find %s",
			    flowop->fo_name);
		}

		filebench_log(LOG_DEBUG_SCRIPT,
		    "flowop %-20s-%4d  - %5d ops %5.1lf ops/sec %5.1lfmb/s "
		    "%8.3fms/op",
		    flowop->fo_name,
		    flowop->fo_instance,
		    flowop->fo_stats.fs_count,
		    flowop->fo_stats.fs_count / total_time_sec,
		    (flowop->fo_stats.fs_bytes / MB_FLOAT) / total_time_sec,
		    flowop->fo_stats.fs_count ?
		    flowop->fo_stats.fs_total_lat /
		    (flowop->fo_stats.fs_count * SEC2MS_FLOAT) : 0);

		flowop = flowop->fo_next;

	}

	flowop = filebench_shm->shm_flowoplist;
	str = malloc(1048576);
	*str = '\0';
	(void) strcpy(str, "Per-Operation Breakdown\n");
	while (flowop) {
		char line[1024];
		char histogram[1024];
		char hist_reading[20];
		int i = 0;

		if (flowop->fo_instance != FLOW_MASTER) {
			flowop = flowop->fo_next;
			continue;
		}

		(void) snprintf(line, sizeof(line), "%-20s %dops %8.0lfops/s "
		    "%5.1lfmb/s %8.1fms/op",
		    flowop->fo_name,
		    flowop->fo_stats.fs_count,
		    flowop->fo_stats.fs_count / total_time_sec,
		    (flowop->fo_stats.fs_bytes / MB_FLOAT) / total_time_sec,
		    flowop->fo_stats.fs_count ?
		    flowop->fo_stats.fs_total_lat /
		    (flowop->fo_stats.fs_count * SEC2MS_FLOAT) : 0);
		(void) strcat(str, line);

		(void) snprintf(line, sizeof(line)," [%.2fms - %5.2fms]",
			flowop->fo_stats.fs_minlat / SEC2MS_FLOAT,
			flowop->fo_stats.fs_maxlat / SEC2MS_FLOAT);
		(void) strcat(str, line);

		if (filebench_shm->lathist_enabled) {
			(void) sprintf(histogram, "\t[ ");
			for (i = 0; i < OSPROF_BUCKET_NUMBER; i++) {
				(void) sprintf(hist_reading, "%lu ",
				flowop->fo_stats.fs_distribution[i]);
				(void) strcat(histogram, hist_reading);
			}
			(void) strcat(histogram, "]\n");
			(void) strcat(str, histogram);
		} else
			(void) strcat(str, "\n");

		flowop = flowop->fo_next;
	}

	/* removing last \n  */
	str[strlen(str) - 1] = '\0';

	filebench_log(LOG_INFO, "%s", str);
	free(str);

	filebench_log(LOG_INFO,
	    "IO Summary: %5d ops %5.3lf ops/s %0.0lf/%0.0lf rd/wr "
	    "%5.1lfmb/s %5.1fms/op",
	    iostat->fs_count + aiostat->fs_count,
	    (iostat->fs_count + aiostat->fs_count) / total_time_sec,
	    (iostat->fs_rcount + aiostat->fs_rcount) / total_time_sec,
	    (iostat->fs_wcount + aiostat->fs_wcount) / total_time_sec,
	    ((iostat->fs_bytes + aiostat->fs_bytes) / MB_FLOAT)
						/ total_time_sec,
	    (iostat->fs_rcount + iostat->fs_wcount) ?
	    iostat->fs_total_lat /
	    ((iostat->fs_rcount + iostat->fs_wcount) * SEC2MS_FLOAT) : 0);

	filebench_shm->shm_bequiet = 0;
}

/*
 * Clears all the statistics variables (fo_stats) for every defined flowop.
 * It also creates a global flowstat table if one doesn't already exist and
 * clears it.
 */
void
stats_clear(void)
{
	flowop_t *flowop;

	if (globalstats == NULL)
		globalstats = malloc(FLOW_TYPES * sizeof (struct flowstats));

	(void) memset(globalstats, 0, FLOW_TYPES * sizeof (struct flowstats));

	flowop = filebench_shm->shm_flowoplist;

	while (flowop) {
		filebench_log(LOG_DEBUG_IMPL, "Clearing stats for %s-%d",
		    flowop->fo_name,
		    flowop->fo_instance);
		(void) memset(&flowop->fo_stats, 0, sizeof (struct flowstats));
		flowop = flowop->fo_next;
	}

	(void) memset(globalstats, 0, sizeof(struct flowstats));
	globalstats->fs_stime = gethrtime();
}
