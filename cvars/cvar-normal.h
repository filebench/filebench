/*
 * rand-normal.h
 *
 * Custom variable that returns Normally distributed random numbers.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#ifndef _RAND_NORMAL_H
#define _RAND_NORMAL_H

#include "mtwist/mtwist.h"

/* Parameters recognized by this variable. */
#define RN_MEAN		"mean"
#define RN_SIGMA	"sigma"

/* Parameter defaults. */
#define RN_MEAN_DEFAULT		0.0
#define RN_SIGMA_DEFAULT	1.0

#define VERSION	"0.1.1 (alpha)"

/* The handle that will be returned to Filebench. */
typedef struct handle {
	mt_state state;
	double mean;
	double sigma;
} handle_t;

/* Static buffer to hold the usage string */
#define USAGE_LEN	2048

char usage[USAGE_LEN + 1] = {0};

#endif /* _RAND_NORMAL_H */
