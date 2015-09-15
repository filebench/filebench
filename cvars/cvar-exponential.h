/*
 * rand-exponential.h
 *
 * Custom variable implementation that returns exponentially distributed random
 * numbers.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#ifndef _RAND_EXPONENTIAL_H
#define _RAND_EXPONENTIAL_H

#include "mtwist/mtwist.h"

/* Parameters recognized by this variable. */
#define RE_MEAN	"mean"

/* Parameter defaults. */
#define RE_MEAN_DEFAULT	1.0

#define VERSION	"0.1.1 (alpha)"

/* The handle that will be returned to Filebench. */
typedef struct handle {
	mt_state state;
	double mean;
} handle_t;

/* Static buffer to hold the usage string */
#define USAGE_LEN	2048

char usage[USAGE_LEN + 1] = {0};

#endif /* _RAND_EXPONENTIAL_H */
