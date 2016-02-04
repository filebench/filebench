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

#include <stdio.h>
#include <fcntl.h>
/* this definition prevents warning about
   using undefined round() function */
#include <math.h>
#include "filebench.h"
#include "ipc.h"
#include "gamma_dist.h"
#include "cvars/mtwist/mtwist.h"

/*
 * Generates a 64-bit random number using mtwist or from a provided random
 * variable "avd".
 *
 * Returned random number "randp" is clipped by the "max" value and rounded off
 * by the "round" value.  Returns 0 on success, shuts down Filebench on
 * failure.
 */
void
fb_random64(uint64_t *randp, uint64_t max, uint64_t round, avd_t avd)
{
	double random_normalized;
	uint64_t random = 0;

	if (avd) {
		/* get it from the random variable */
		if (!AVD_IS_RANDOM(avd)) {
			/* trying to get random value not from
				random variable. That's a clear error. */
			filebench_log(LOG_ERROR, "filebench_randomno64: trying"
			" to get a random value from not a random variable");
			filebench_shutdown(1);
			/* NOT REACHABLE */
		} else {
			random = avd_get_int(avd);
		}
	} else {
		random = mt_llrand();
	}

	/*
	 * If round is not zero, then caller will get a random number in the
	 * range [0; max - round].  This allows the caller to use this
	 * function, for example, to obtain a pointer in an allocated memory
	 * region of [0; max] and read/write round bytes safely starting
	 * at this pointer.
	 */
	max = max - round;

	random_normalized = (double)random / UINT64_MAX;
	random = random_normalized * max;

	if (round) {
		random = random / round;
		random = random * round;
	}

	*randp = random;
}

/*
 * Same as filebench_randomno64, but for 32 bit integers.
 */

void
fb_random32(uint32_t *randp,
		uint32_t max, uint32_t round, avd_t avd)
{
	uint64_t rand64;

	fb_random64(&rand64, max, round, avd);

	/* rand64 always fits uint32, since "max" above was 32 bit */
	*randp = (uint32_t)rand64;
}

/*
 * Same as filebench_randomno64, but for probability [0-1].
 */
static double
fb_random_probability()
{
	uint64_t randnum;

	fb_random64(&randnum, UINT64_MAX, 0, NULL);

	/* convert to 0-1 probability */
	return (double)randnum / (double)(UINT64_MAX);
}

/****************************************
 *					*
 * randist related functions		*
 *					*
 ****************************************/

static double
fb_rand_src_rand48(unsigned short *xi)
{
	return (erand48(xi));
}

static double
fb_rand_src_random(unsigned short *xi)
{
	return fb_random_probability();
}

/*
 * fetch a uniformly distributed random number from the supplied
 * random object.
 */
static double
rand_uniform_get(randdist_t *rndp)
{
	double		dprob, dmin, dres, dround;

	dmin = (double)rndp->rnd_vint_min;
	dround = (double)rndp->rnd_vint_round;

	dprob = (*rndp->rnd_src)(rndp->rnd_xi);

	dres = (dprob * (2.0 * (rndp->rnd_dbl_mean - dmin))) + dmin;

	if (dround == 0.0)
		return (dres);
	else
		return (round(dres / dround) * dround);
}

/*
 * fetch a gamma distributed random number from the supplied
 * random object.
 */
static double
rand_gamma_get(randdist_t *rndp)
{
	double		dmult, dres, dmin, dround;

	dmin = (double)rndp->rnd_vint_min;
	dround = (double)rndp->rnd_vint_round;

	dmult = (rndp->rnd_dbl_mean - dmin) / rndp->rnd_dbl_gamma;

	dres = gamma_dist_knuth_src(rndp->rnd_dbl_gamma,
	    dmult, rndp->rnd_src, rndp->rnd_xi) + dmin;

	if (dround == 0.0)
		return (dres);
	else
		return (round(dres / dround) * dround);
}

/*
 * fetch a table driven random number from the supplied
 * random object.
 */
static double
rand_table_get(randdist_t *rndp)
{
	double		dprob, dprcnt, dtabres, dsclres, dmin, dround;
	int		idx;

	dmin = (double)rndp->rnd_vint_min;
	dround = (double)rndp->rnd_vint_round;

	dprob = (*rndp->rnd_src)(rndp->rnd_xi);

	dprcnt = (dprob * (double)(PF_TAB_SIZE));
	idx = (int)dprcnt;

	dtabres = (rndp->rnd_rft[idx].rf_base +
	    (rndp->rnd_rft[idx].rf_range * (dprcnt - (double)idx)));

	dsclres = (dtabres * (rndp->rnd_dbl_mean - dmin)) + dmin;

	if (dround == 0.0)
		return (dsclres);
	else
		return (round(dsclres / dround) * dround);
}

/*
 * Set the random seed in the supplied random object.
 */
static void
rand_seed_set(randdist_t *rndp)
{
	union {
		uint64_t  ll;
		uint16_t  w[4];
	} temp1;
	int  idx;

	temp1.ll = (uint64_t)avd_get_int(rndp->rnd_seed);

	for (idx = 0; idx < 3; idx++) {

#ifdef _BIG_ENDIAN
		rndp->rnd_xi[idx] = temp1.w[3-idx];
#else
		rndp->rnd_xi[idx] = temp1.w[idx];
#endif
	}
}

/*
 * Define a random entity which will contain the parameters of a random
 * distribution.
 */
randdist_t *
randdist_alloc(void)
{
	randdist_t *rndp;

	if ((rndp = (randdist_t *)ipc_malloc(FILEBENCH_RANDDIST)) == NULL) {
		filebench_log(LOG_ERROR, "Out of memory for random dist");
		return (NULL);
	}

	/* place on global list */
	rndp->rnd_next = filebench_shm->shm_rand_list;
	filebench_shm->shm_rand_list = rndp;

	return (rndp);
}

/*
 * Initializes a random distribution entity, converting avd_t parameters to
 * doubles, and converting the list of probability density function table
 * entries, if supplied, into a probablilty function table.
 */
void
randdist_init(randdist_t *rndp)
{
	probtabent_t	*rdte_hdp, *ptep;
	double		tablemean, tablemin = 0;
	int		pteidx;

	/* convert parameters to doubles */
	rndp->rnd_dbl_gamma = (double)avd_get_int(rndp->rnd_gamma) / 1000.0;
	if (rndp->rnd_mean != NULL)
		rndp->rnd_dbl_mean  = (double)avd_get_int(rndp->rnd_mean);
	else
		rndp->rnd_dbl_mean = rndp->rnd_dbl_gamma;

	/* de-reference min and round amounts for later use */
	rndp->rnd_vint_min  = avd_get_int(rndp->rnd_min);
	rndp->rnd_vint_round  = avd_get_int(rndp->rnd_round);

	filebench_log(LOG_DEBUG_IMPL,
	    "init random var: Mean = %6.0llf, Gamma = %6.3llf, Min = %llu",
	    rndp->rnd_dbl_mean, rndp->rnd_dbl_gamma,
	    (u_longlong_t)rndp->rnd_vint_min);

	/* initialize distribution to apply */
	switch (rndp->rnd_type & RAND_TYPE_MASK) {
	case RAND_TYPE_UNIFORM:
		rndp->rnd_get = rand_uniform_get;
		break;

	case RAND_TYPE_GAMMA:
		rndp->rnd_get = rand_gamma_get;
		break;

	case RAND_TYPE_TABLE:
		rndp->rnd_get = rand_table_get;
		break;

	default:
		filebench_log(LOG_DEBUG_IMPL, "Random Type not Specified");
		filebench_shutdown(1);
		return;
	}

	/* initialize source of random numbers */
	if (rndp->rnd_type & RAND_SRC_GENERATOR) {
		rndp->rnd_src = fb_rand_src_rand48;
		rand_seed_set(rndp);
	} else {
		rndp->rnd_src = fb_rand_src_random;
	}

	/* any random distribution table to convert? */
	if ((rdte_hdp = rndp->rnd_probtabs) == NULL)
		return;

	/* determine random distribution max and mins and initialize table */
	pteidx = 0;
	tablemean = 0.0;
	for (ptep = rdte_hdp; ptep; ptep = ptep->pte_next) {
		double	dmin, dmax;
		int	entcnt;

		dmax = (double)avd_get_int(ptep->pte_segmax);
		dmin = (double)avd_get_int(ptep->pte_segmin);

		/* initialize table minimum on first pass */
		if (pteidx == 0)
			tablemin = dmin;

		/* update table minimum */
		if (tablemin > dmin)
			tablemin = dmin;

		entcnt = (int)avd_get_int(ptep->pte_percent);
		tablemean += (((dmin + dmax)/2.0) * (double)entcnt);

		/* populate the lookup table */

		for (; entcnt > 0; entcnt--) {
			rndp->rnd_rft[pteidx].rf_base = dmin;
			rndp->rnd_rft[pteidx].rf_range = dmax - dmin;
			pteidx++;
		}
	}

	/* check to see if probability equals 100% */
	if (pteidx != PF_TAB_SIZE)
		filebench_log(LOG_ERROR,
		    "Prob table only totals %d%%", pteidx);

	/* If table is not supplied with a mean value, set it to table mean */
	if (rndp->rnd_dbl_mean == 0.0)
		rndp->rnd_dbl_mean = (double)tablemean / (double)PF_TAB_SIZE;

	/* now normalize the entries for a min value of 0, mean of 1 */
	tablemean = (tablemean / 100.0) - tablemin;

	/* special case if really a constant value */
	if (tablemean == 0.0) {
		for (pteidx = 0; pteidx < PF_TAB_SIZE; pteidx++) {
			rndp->rnd_rft[pteidx].rf_base = 0.0;
			rndp->rnd_rft[pteidx].rf_range = 0.0;
		}
		return;
	}

	for (pteidx = 0; pteidx < PF_TAB_SIZE; pteidx++) {

		rndp->rnd_rft[pteidx].rf_base =
		    ((rndp->rnd_rft[pteidx].rf_base - tablemin) / tablemean);
		rndp->rnd_rft[pteidx].rf_range =
		    (rndp->rnd_rft[pteidx].rf_range / tablemean);
	}
}
