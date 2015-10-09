/*
 * rand-gamma.c
 *
 * Custom variable implementation that returns gamma distributed random
 * numbers.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cvar.h"
#include "cvar_trace.h"
#include "cvar_tokens.h"

#define VERSION	"0.1.1 (alpha)"

#define USAGE_LEN	2048
static char usage[USAGE_LEN + 1];

#define MEAN	"mean"
#define GAMMA	"gamma"

#define MEAN_DEFAULT	4096.0
#define GAMMA_DEFAULT 1.5

typedef struct handle {
	double mean;
	double scaledmean;
	double gamma;
} handle_t;

/******* Part from the original FB distribution ****************/

/*
 * This is valid for 0 < a <= 1
 *
 * From Knuth Volume 2, 3rd edition, pages 586 - 587.
 */
static double
gamma_dist_knuth_algG(double a, double (*src)(unsigned short *),
    unsigned short *xi)
{
	double p, U, V, X, q;

	p = M_E/(a + M_E);
G2:
	/* get a random number U */
	U = (*src)(xi);

	do {
		/* get a random number V */
		V = (*src)(xi);

	} while (V == 0);

	if (U < p) {
		X = pow(V, 1/a);
		/* q = e^(-X) */
		q = exp(-X);
	} else {
		X = 1 - log(V);
		q = pow(X, a-1);
	}

	/*
	 * X now has density g, and q = f(X)/cg(X)
	 */

	/* get a random number U */
	U = (*src)(xi);

	if (U >= q)
		goto G2;
	return (X);
}

/*
 * This is valid for a > 1
 *
 * From Knuth Volume 2, 3rd edition, page 134.
 */
static double
gamma_dist_knuth_algA(double a, double (*src)(unsigned short *),
    unsigned short *xi)
{
	double U, Y, X, V;

A1:
	/* get a random number U */
	U = (*src)(xi);

	Y = tan(M_PI*U);
	X = (sqrt((2*a) - 1) * Y) + a - 1;

	if (X <= 0)
		goto A1;

	/* get a random number V */
	V = (*src)(xi);

	if (V > ((1 + (Y*Y)) * exp((a-1) * log(X/(a-1)) - sqrt(2*a -1) * Y)))
		goto A1;

	return (X);
}

/*
 * fetch a uniformly distributed random number using the drand48 generator
 */
/* ARGSUSED */
static double
default_src(unsigned short *xi)
{
	return (drand48());
}

/*
 * Sample the gamma distributed random variable with gamma 'a' and
 * result mulitplier 'b', which is usually mean/gamma. Uses the default
 * drand48 random number generator as input
 */
static double
gamma_dist_knuth(double a, double b)
{
	if (a <= 1.0)
		return (b * gamma_dist_knuth_algG(a, default_src, NULL));
	else
		return (b * gamma_dist_knuth_algA(a, default_src, NULL));
}

/*
 * Sample the gamma distributed random variable with gamma 'a' and
 * multiplier 'b', which is mean / gamma adjusted for the specified
 * minimum value. The suppled random number source function is
 * used to optain the uniformly distributed random numbers.
 */
static double
gamma_dist_knuth_src(double a, double b,
    double (*src)(unsigned short *), unsigned short *xi)
{
	if (a <= 1.0)
		return (b * gamma_dist_knuth_algG(a, src, xi));
	else
		return (b * gamma_dist_knuth_algA(a, src, xi));
}
/*************************************************************/

void *cvar_alloc_handle(const char *cvar_parameters,
		void *(*cvar_malloc)(size_t size), void (*cvar_free)(void *cvar_ptr))
{
	cvar_token_t *list_head;;
	cvar_token_t *t;
	handle_t handle;
	handle_t *state = NULL;
	int ret = 0;

	cvar_trace("entry");

	/* Tokenize parameters supplied by filebench. */
	list_head = NULL;
	ret = tokenize(cvar_parameters, DEFAULT_PARAMETER_DELIMITER,
			DEFAULT_KEY_VALUE_DELIMITER, &list_head);
	if (ret)
		goto out;

	/* Get the values for mean and gamma. */
	t = find_token(list_head, MEAN);
	if (t && t->value) {
		t->used = 1;
		handle.mean = atof(t->value);
	} else
		handle.mean = MEAN_DEFAULT;

	t = find_token(list_head, GAMMA);
	if (t && t->value) {
		t->used = 1;
		handle.gamma = atof(t->value);
	} else
		handle.gamma= GAMMA_DEFAULT;

	if (!handle.gamma) {
		cvar_log_error("Invalid parameter values: mean = %lf "
				"and gamma = %lf. gamma must be greater "
				"than 0", handle.mean, handle.gamma);
		goto out;
	}

	handle.scaledmean = handle.mean / handle.gamma;

	cvar_trace("mean = %lf, gamma = %lf", handle.mean, handle.gamma);

	t = unused_tokens(list_head);
	if (t) {
		cvar_log_error("Unsupported parameter %s", t->key);
		goto out;
	}

	/* All set. Now allocate space for the handle in the shared segment and
	 * copy the state over. */
	state = (handle_t *)cvar_malloc(sizeof(handle_t));
	if (!state) {
		cvar_log_error("Out of memory");
		goto out;
	}

	*state = handle;

out:
	free_tokens(list_head);

	cvar_trace("exit");
	return state;
}

int cvar_revalidate_handle(void *cvar_handle)
{
	handle_t *h = (handle_t *) cvar_handle;

	return 0;
}

int cvar_next_value(void *cvar_handle, double *value)
{
	handle_t *h = (handle_t *) cvar_handle;

	if (!h) {
		cvar_log_error("NULL cvar_handle");
		return -1;
	}

	if (!value) {
		cvar_log_error("NULL value");
		return -1;
	}

	*value = gamma_dist_knuth(h->gamma, h->scaledmean);

	return 0;
}

void cvar_free_handle(void *handle, void (*cvar_free)(void *ptr))
{
	cvar_free(handle);
}

const char *cvar_usage()
{
	int offset;

	if (usage[0])
		return usage;

	offset = 0;

	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"\tparameter\tdefault\n");
	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"\t---------\t-------\n");

	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"\t%s\t\t%.1f\n", MEAN, MEAN_DEFAULT);
	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"\t%s\t\t%.1f\n", GAMMA, GAMMA_DEFAULT);

	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"Use '%c' to delimit parameters and '%c' to delimit key-value "
			"pairs.\n", DEFAULT_PARAMETER_DELIMITER,
			DEFAULT_KEY_VALUE_DELIMITER);
	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"Example: '%s%c%.1f%c%s%c%.1f'",
			MEAN, DEFAULT_KEY_VALUE_DELIMITER, MEAN_DEFAULT,
			DEFAULT_PARAMETER_DELIMITER,
			GAMMA, DEFAULT_KEY_VALUE_DELIMITER, GAMMA_DEFAULT);

	return usage;
}

const char *cvar_version()
{
	return VERSION;
}
