/*
 * rand-uniform.h
 *
 * Custom variable implementation that generates uniformly distributed random
 * numbers.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#ifndef _RAND_UNIFORM_H
#define _RAND_UNIFORM_H

#include "mtwist/mtwist.h"

/* Parameters recognized by this variable. */
#define RU_LOWER	"lower"
#define RU_UPPER	"upper"

/* Parameter defaults. */
#define RU_LOWER_DEFAULT	0.0
#define RU_UPPER_DEFAULT	1.0

#define VERSION	"0.1.1 (alpha)"

/* The handle that will be returned to Filebench. */
typedef struct handle {
	mt_state state;
	double lower;
	double upper;
} handle_t;

/* Static buffer to hold the usage string */
#define USAGE_LEN	2048

char usage[USAGE_LEN + 1] = {0};

#endif /* _RAND_UNIFORM_H */
