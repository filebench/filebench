/*
 * rand-lognormal.h
 *
 * Custom variable implementation that returns Log-Normally distributed random
 * numbers.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#ifndef _RAND_LOGNORMAL_H
#define _RAND_LOGNORMAL_H

#include "mtwist/mtwist.h"

/* Parameters recognized by this variable. */
#define RLN_SHAPE	"shape"
#define RLN_SCALE	"scale"

/* Parameter defaults. */
#define RLN_SHAPE_DEFAULT	1.0
#define RLN_SCALE_DEFAULT	1.0

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

#endif /* _RAND_NORMAL_H */
