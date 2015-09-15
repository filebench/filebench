/*
 * rand-weibull.h
 *
 * Custom variable implementation that returns random numbers following the
 * Weibull distribution.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#ifndef _RAND_WEIBULL_H
#define _RAND_WEIBULL_H

#include "mtwist/mtwist.h"

/* Parameters recognized by this variable. */
#define RW_SHAPE	"shape"
#define RW_SCALE	"scale"

/* Parameter defaults. */
#define RW_SHAPE_DEFAULT	1.0
#define RW_SCALE_DEFAULT	1.0

#define VERSION	"0.1.1 (alpha)"

/* The handle that will be returned to Filebench. */
typedef struct handle {
	mt_state state;
	double shape;
	double scale;
} handle_t;

/* Static buffer to hold the usage string */
#define USAGE_LEN	2048

char usage[USAGE_LEN + 1] = {0};

#endif /* _RAND_WEIBULL_H */
