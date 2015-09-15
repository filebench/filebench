/*
 * rand-triangular.h
 *
 * Custom variable implementation that returns random numbers following a
 * Triangular distribution.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#ifndef _RAND_TRIANGULAR_H
#define _RAND_TRIANGULAR_H

#include "mtwist/mtwist.h"

/* Parameters recognized by this variable. */
#define RT_LOWER	"lower"
#define RT_UPPER	"upper"
#define RT_MODE		"mode"

/* Parameter defaults. */
#define RT_LOWER_DEFAULT	0.0
#define RT_UPPER_DEFAULT	1.0
#define RT_MODE_DEFAULT		0.5

#define VERSION	"0.1.1 (alpha)"

/* The handle that will be returned to Filebench. */
typedef struct handle {
	mt_state state;
	double lower;
	double upper;
	double mode;
} handle_t;

/* Static buffer to hold the usage string */
#define USAGE_LEN	2048

char usage[USAGE_LEN + 1] = {0};

#endif /* _RAND_TRIANGULAR_H */
