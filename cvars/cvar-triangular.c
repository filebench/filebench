/*
 * rand-triangular.c
 *
 * Custom variable implementation that returns random numbers following a
 * Triangular distribution.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#include <stdio.h>
#include "mtwist/mtwist.h"
#include "mtwist/randistrs.h"
#include "cvar.h"
#include "cvar_trace.h"
#include "cvar_tokens.h"
#include "cvar-triangular.h"

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

	/* Get the value of lower, upper and mode. */
	t = find_token(list_head, RT_LOWER);
	if (t && t->value) {
		t->used = 1;
		handle.lower = atof(t->value);
	} else
		handle.lower = RT_LOWER_DEFAULT;

	t = find_token(list_head, RT_UPPER);
	if (t && t->value) {
		t->used = 1;
		handle.upper = atof(t->value);
	} else
		handle.upper = RT_UPPER_DEFAULT;

	t = find_token(list_head, RT_MODE);
	if (t && t->value) {
		t->used = 1;
		handle.mode = atof(t->value);
	} else
		handle.mode = RT_MODE_DEFAULT;

	cvar_trace("lower = %lf, upper = %lf, mode = %lf", handle.lower,
			handle.upper, handle.mode);

	/* Validate parameters. */
	if (handle.upper < handle.lower) {
		cvar_log_error("Invalid parameter values: lower = %lf and upper = %lf. "
				"upper must be greater than lower", handle.lower, handle.upper);
		goto out;
	}

	if ((handle.mode > handle.upper) || (handle.mode < handle.lower)) {
		cvar_log_error("Invalid parameter values: lower = %lf, mode = %lf and "
				"upper = %lf. mode must be between lower and upper",
				handle.lower, handle.mode, handle.upper);
		goto out;
	}

	/* Check if there are unused tokens. */
	t = unused_tokens(list_head);
	if (t) {
		cvar_log_error("Unsupported parameter %s", t->key);
		goto out;
	}

	/* Seed the state. */
	mts_goodseed(&handle.state);

	/* All set. Now allocate space for the handle in the shared segment and
	 * copy the state over. */
	state = (handle_t *) cvar_malloc(sizeof(handle_t));
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

	mts_mark_initialized(&h->state);

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

	*value = rds_triangular(&h->state, h->lower, h->upper, h->mode);

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
			"\t%s\t\t%.1f\n", RT_LOWER, RT_LOWER_DEFAULT);
	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"\t%s\t\t%.1f\n", RT_UPPER, RT_UPPER_DEFAULT);
	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"\t%s\t\t%.1f\n", RT_MODE, RT_MODE_DEFAULT);

	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"Use '%c' to delimit parameters and '%c' to delimit key-value "
			"pairs.\n", DEFAULT_PARAMETER_DELIMITER,
			DEFAULT_KEY_VALUE_DELIMITER);

	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"Example: '%s%c%.1f%c%s%c%.1f%c%s%c%.1f'",
			RT_LOWER, DEFAULT_KEY_VALUE_DELIMITER, RT_LOWER_DEFAULT,
			DEFAULT_PARAMETER_DELIMITER,
			RT_UPPER, DEFAULT_KEY_VALUE_DELIMITER, RT_UPPER_DEFAULT,
			DEFAULT_PARAMETER_DELIMITER,
			RT_MODE, DEFAULT_KEY_VALUE_DELIMITER, RT_MODE_DEFAULT);

	return usage;
}

const char *cvar_version()
{
	return VERSION;
}
