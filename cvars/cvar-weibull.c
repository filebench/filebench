/*
 * rand-weibull.c
 *
 * Custom variable implementation that returns random numbers following the
 * Weibull distribution.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#include <stdio.h>
#include "mtwist/mtwist.h"
#include "mtwist/randistrs.h"
#include "cvar.h"
#include "cvar_trace.h"
#include "cvar_tokens.h"
#include "cvar-weibull.h"

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

	/* Get the value of shape and scale. */
	t = find_token(list_head, RW_SHAPE);
	if (t && t->value) {
		t->used = 1;
		handle.shape = atof(t->value);
	} else
		handle.shape = RW_SHAPE_DEFAULT;

	t = find_token(list_head, RW_SCALE);
	if (t && t->value) {
		t->used = 1;
		handle.scale = atof(t->value);
	} else
		handle.scale = RW_SCALE_DEFAULT;

	cvar_trace("shape = %lf, scale = %lf", handle.shape, handle.scale);

	/* Validate parameters. */
	if (handle.shape < 0) {
		cvar_log_error("Invalid parameter value: shape = %lf. shape is a "
				"non-zero, positive integer", handle.shape);
		goto out;
	}

	if (handle.scale < 0) {
		cvar_log_error("Invalid parameter value: scale = %lf. scale is a "
				"non-zero, positive rational number", handle.scale);
		goto out;
	}

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
		cvar_trace("NULL cvar_handle");
		return -1;
	}

	if (!value) {
		cvar_trace("NULL value");
		return -1;
	}

	*value = rds_weibull(&h->state, h->shape, h->scale);

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
			"\t%s\t\t%.1f\n", RW_SHAPE, RW_SHAPE_DEFAULT);
	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"\t%s\t\t%.1f\n", RW_SCALE, RW_SCALE_DEFAULT);

	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"Use '%c' to delimit parameters and '%c' to delimit key-value "
			"pairs.\n", DEFAULT_PARAMETER_DELIMITER,
			DEFAULT_KEY_VALUE_DELIMITER);

	offset += snprintf(usage + offset, USAGE_LEN - offset,
			"Example: '%s%c%.1f%c%s%c%.1f'",
			RW_SHAPE, DEFAULT_KEY_VALUE_DELIMITER, RW_SHAPE_DEFAULT,
			DEFAULT_PARAMETER_DELIMITER,
			RW_SCALE, DEFAULT_KEY_VALUE_DELIMITER, RW_SCALE_DEFAULT);

	return usage;
}

const char *cvar_version()
{
	return VERSION;
}
