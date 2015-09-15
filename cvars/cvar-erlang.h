/*
 * rand-erlang.h
 *
 * Custom variable that returns random numbers following the Erlang
 * distribution.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#ifndef _RAND_ERLANG_H
#define _RAND_ERLANG_H

#include "mtwist/mtwist.h"

/* Parameters recognized by this variable. */
#define RER_SHAPE	"shape"
#define RER_RATE	"rate"

/* Parameter defaults. */
#define RER_SHAPE_DEFAULT	1
#define RER_RATE_DEFAULT	1.0

#define VERSION	"0.1.1 (alpha)"

/* The handle that will be returned to Filebench. */
typedef struct handle {
	mt_state state;
	int shape;
	double rate;
} handle_t;

/* Static buffer to hold the usage string */
#define USAGE_LEN	2048

char usage[USAGE_LEN + 1] = {0};

#endif /* _RAND_ERLANG_H */
