/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright 2009 Sun Microsystems, Inc. All rights reserved.
 * Use is subject to license terms.
 *
 * Portions Copyright 2008 Denis Cheng
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "filebench.h"
#include "vars.h"
#include "misc.h"
#include "utils.h"
#include "stats.h"
#include "eventgen.h"
#include "fb_random.h"

/*
 * The filebench variables system has attribute value descriptors (avd_t) where
 * an avd contains a boolean, integer, double, string, random distribution
 * object ptr, boolean ptr, integer ptr, double ptr, string ptr, or variable
 * ptr. The system also has the variables themselves, (var_t), which are named
 * and typed entities that can be allocated, selected and changed using the
 * "set" command and used in attribute assignments. The variables contain
 * either a boolean, an integer, a double, a string or pointer to an associated
 * random distribution object. Both avd_t and var_t entities are allocated from
 * interprocess shared memory space.
 * 
 * The attribute descriptors implement delayed binding to variable values,
 * which is necessary because the values of variables may be changed between
 * the time the workload model is loaded and the time it actually runs by
 * further "set" commands.
 *
 * For static attributes, the value is just loaded in the descriptor directly,
 * avoiding the need to allocate a variable to hold the static value.
 *
 * For random variables, they actually point to the random distribution object,
 * allowing Filebench to invoke the appropriate random distribution function on
 * each access to the attribute. 
 *
 * The routines in this module are used to allocate, locate, and manipulate the
 * attribute descriptors and vars. Routines are also included to convert
 * between the component strings, doubles and integers of vars, and said
 * components of avd_t.
 */

static char *
avd_get_type_textified(avd_t avd)
{
	switch (avd->avd_type) {
	case AVD_INVALID:
		return "uninitialized";
	case AVD_VAL_BOOL:
		return "boolean";
	case AVD_VARVAL_BOOL:
		return "pointer to a boolean in a variable";
	case AVD_VAL_INT:
		return "integer";
	case AVD_VARVAL_INT:
		return "pointer to an integer in a variable";
	case AVD_VAL_DBL:
		return "double";
	case AVD_VARVAL_DBL:
		return "pointer to a double in a variable";
	case AVD_VAL_STR:
		return "string";
	case AVD_VARVAL_STR:
		return "pointer to a string in a variable";
	case AVD_VARVAL_RANDOM:
		return "pointer to a random variable";
	case AVD_VARVAL_CUSTOM:
		return "pointer to a custom variable";
	case AVD_VARVAL_UNKNOWN:
		return "pointer to variable of unknown type";
	default:
		return "illegal avd type";
	}
}

static void
set_avd_type_by_var(avd_t avd, var_t *var, int error_on_unknown) {
	switch (var->var_type) {
	case VAR_BOOL:
		avd->avd_type = AVD_VARVAL_BOOL;
		avd->avd_val.boolptr = &var->var_val.boolean;
		break;
	case VAR_INT:
		avd->avd_type = AVD_VARVAL_INT;
		avd->avd_val.intptr = &var->var_val.integer;
		break;
	case VAR_DBL:
		avd->avd_type = AVD_VARVAL_DBL;
		avd->avd_val.dblptr = &var->var_val.dbl;
		break;
	case VAR_STR:
		avd->avd_type = AVD_VARVAL_STR;
		avd->avd_val.strptr = &var->var_val.string;
		break;
	case VAR_RANDOM:
		avd->avd_type = AVD_VARVAL_RANDOM;
		avd->avd_val.randptr = var->var_val.randptr;
		break;
	case VAR_CUSTOM:
		avd->avd_type = AVD_VARVAL_CUSTOM;
		avd->avd_val.cvarptr = var->var_val.cvarptr;
		break;
	case VAR_UNKNOWN:
		if (error_on_unknown) {
			filebench_log(LOG_ERROR,
				"Noninitialized variable %s", var->var_name);
			filebench_shutdown(1);
		}
		avd->avd_type = AVD_VARVAL_UNKNOWN;
		avd->avd_val.varptr = var;
		break;
	default:
		filebench_log(LOG_ERROR,
			"Invalid variable type (variable: %s)", var->var_name);
		filebench_shutdown(1);
	}
}

boolean_t
avd_get_bool(avd_t avd)
{
	var_t *var;

	assert(avd);

	switch (avd->avd_type) {
	case AVD_VAL_BOOL:
		return avd->avd_val.boolval;
	case AVD_VARVAL_BOOL:
		assert(avd->avd_val.boolptr);
		return *(avd->avd_val.boolptr);
	case AVD_VAL_INT:
		if (avd->avd_val.intval)
			return TRUE;
		return FALSE;
	case AVD_VARVAL_INT:
		assert(avd->avd_val.intptr);
		if (*(avd->avd_val.intptr))
			return TRUE;
		return FALSE;
	case AVD_VAL_DBL:
		if (avd->avd_val.dblval)
			return TRUE;
		return FALSE;
	case AVD_VARVAL_DBL:
		assert(avd->avd_val.dblptr);
		if (*(avd->avd_val.dblptr))
			return TRUE;
		return FALSE;
	case AVD_VARVAL_UNKNOWN:
		var = avd->avd_val.varptr;
		set_avd_type_by_var(avd, var, 1);
		return avd_get_bool(avd);
	default:
		filebench_log(LOG_ERROR,
			"Attempt to get boolean from %s avd",
			avd_get_type_textified(avd));
		return FALSE;
	}
}

uint64_t
avd_get_int(avd_t avd)
{
	randdist_t *rndp;
	cvar_t *cvar;
	var_t *var;

	assert(avd);

	switch (avd->avd_type) {
	case AVD_VAL_INT:
		return avd->avd_val.intval;
	case AVD_VARVAL_INT:
		assert(avd->avd_val.intptr);
		return *(avd->avd_val.intptr);
	case AVD_VAL_DBL:
		return (uint64_t)avd->avd_val.dblval;
	case AVD_VARVAL_DBL:
		assert(avd->avd_val.dblptr);
		return (uint64_t)*(avd->avd_val.dblptr);
	case AVD_VARVAL_RANDOM:
		rndp = avd->avd_val.randptr;
		assert(rndp);
		return (uint64_t)rndp->rnd_get(rndp);
	case AVD_VARVAL_CUSTOM:
		cvar = avd->avd_val.cvarptr;
		assert(cvar);
		return (uint64_t)get_cvar_value(cvar);
	case AVD_VARVAL_UNKNOWN:
		var = avd->avd_val.varptr;
		set_avd_type_by_var(avd, var, 1);
		return avd_get_int(avd);
	default:
		filebench_log(LOG_ERROR,
			"Attempt to get integer from %s avd",
			avd_get_type_textified(avd));
		return 0;
	}
}

double
avd_get_dbl(avd_t avd)
{
	randdist_t *rndp;
	cvar_t *cvar;
	var_t *var;

	assert(avd);

	switch (avd->avd_type) {
	case AVD_VAL_DBL:
		return avd->avd_val.dblval;
	case AVD_VARVAL_DBL:
		assert(avd->avd_val.dblptr);
		return *(avd->avd_val.dblptr);
	case AVD_VAL_INT:
		return (double)avd->avd_val.intval;
	case AVD_VARVAL_INT:
		assert(avd->avd_val.intptr);
		return (double)(*(avd->avd_val.intptr));
	case AVD_VARVAL_RANDOM:
		rndp = avd->avd_val.randptr;
		assert(rndp);
		return rndp->rnd_get(rndp);
	case AVD_VARVAL_CUSTOM:
		cvar = avd->avd_val.cvarptr;
		assert(cvar);
		return get_cvar_value(cvar);
	case AVD_VARVAL_UNKNOWN:
		var = avd->avd_val.varptr;
		set_avd_type_by_var(avd, var, 1);
		return avd_get_dbl(avd);
	default:
		filebench_log(LOG_ERROR,
			"Attempt to get floating point from %s avd",
			avd_get_type_textified(avd));
		return 0.0;
	}
}

char *
avd_get_str(avd_t avd)
{
	assert(avd);
	var_t *var;

	switch (avd->avd_type) {
	case AVD_VAL_STR:
		return avd->avd_val.strval;
	case AVD_VARVAL_STR:
		assert(avd->avd_val.strptr);
		return *avd->avd_val.strptr;
	case AVD_VARVAL_UNKNOWN:
		var = avd->avd_val.varptr;
		set_avd_type_by_var(avd, var, 1);
		return avd_get_str(avd);
	default:
		filebench_log(LOG_ERROR,
			"Attempt to get string from %s avd",
			avd_get_type_textified(avd));
		return NULL;
	}
}

static avd_t
avd_alloc_cmn(void)
{
	avd_t avd;

	avd = (avd_t)ipc_malloc(FILEBENCH_AVD);
	if (!avd)
		filebench_log(LOG_ERROR, "AVD allocation failed");

	return avd;
}

avd_t
avd_bool_alloc(boolean_t val)
{
	avd_t avd;

	avd = avd_alloc_cmn();
	if (!avd)
		return NULL;

	avd->avd_type = AVD_VAL_BOOL;
	avd->avd_val.boolval = val;

	return avd;
}

avd_t
avd_int_alloc(uint64_t val)
{
	avd_t avd;

	avd = avd_alloc_cmn();
	if (!avd)
		return NULL;

	avd->avd_type = AVD_VAL_INT;
	avd->avd_val.intval = val;

	return avd;
}

avd_t
avd_dbl_alloc(double val)
{
	avd_t avd;

	avd = avd_alloc_cmn();
	if (!avd)
		return NULL;

	avd->avd_type = AVD_VAL_DBL;
	avd->avd_val.dblval = val;

	return avd;
}

avd_t
avd_str_alloc(char *string)
{
	avd_t avd;

	assert(string);

	avd = avd_alloc_cmn();
	if (!avd)
		return NULL;

	avd->avd_type = AVD_VAL_STR;
	avd->avd_val.strval = ipc_stralloc(string);

	return avd;
}

static var_t *
var_alloc(char *name)
{
	var_t *var;

	var = (var_t *)ipc_malloc(FILEBENCH_VARIABLE);
	if (!var) {
		filebench_log(LOG_ERROR, "Out of memory for variables");
		return NULL;
	}

	memset(var, 0, sizeof(*var));
	VAR_SET_UNKNOWN(var);

	var->var_name = ipc_stralloc(name);
	if (!var->var_name) {
		filebench_log(LOG_ERROR, "Out of memory for strings");
		return NULL;
	}

	var->var_next = filebench_shm->shm_var_list;
	filebench_shm->shm_var_list = var;

	return var;
}

static var_t *
var_find(char *name)
{
	var_t *var;

	for (var = filebench_shm->shm_var_list; var; var = var->var_next)
		if (!strcmp(var->var_name, name))
			return var;

	return NULL;
}

static var_t *
var_find_alloc(char *name)
{
	var_t *var;

	var = var_find(name);
	if (!var)
		var = var_alloc(name);

	return var;
}

int
var_assign_boolean(char *name, boolean_t bool)
{
	var_t *var;

	var = var_find_alloc(name);
	if (!var) {
		filebench_log(LOG_ERROR, "Could not assign variable %s", name);
		return -1;
	}

	VAR_SET_BOOL(var, bool);

	return 0;
}

int
var_assign_integer(char *name, uint64_t integer)
{
	var_t *var;

	var = var_find_alloc(name);
	if (!var) {
		filebench_log(LOG_ERROR, "Could not assign variable %s", name);
		return -1;
	}

	VAR_SET_INT(var, integer);

	return 0;
}

int
var_assign_double(char *name, double dbl)
{
	var_t *var;

	var = var_find_alloc(name);
	if (!var) {
		filebench_log(LOG_ERROR, "Could not assign variable %s", name);
		return -1;
	}

	VAR_SET_DBL(var, dbl);

	return 0;
}

int
var_assign_string(char *name, char *string)
{
	var_t *var;
	char *strptr;

	var = var_find_alloc(name);
	if (!var) {
		filebench_log(LOG_ERROR, "Could not assign variable %s", name);
		return -1;
	}

	strptr = ipc_stralloc(string);
	if (!strptr) {
		filebench_log(LOG_ERROR, "Could not assign variable %s", name);
		return -1;
	}

	VAR_SET_STR(var, strptr);

	return 0;
}

int
var_assign_random(char *name, randdist_t *rndp)
{
	var_t *var;

	var = var_find_alloc(name);
	if (!var) {
		filebench_log(LOG_ERROR, "Could not assign variable %s", name);
		return -1;
	}

	VAR_SET_RANDOM(var, rndp);

	return 0;
}

int
var_assign_custom(char *name, struct cvar *cvar)
{
	var_t *var;

	var = var_find_alloc(name);
	if (!var) {
		filebench_log(LOG_ERROR, "Could not assign variable %s", name);
		return -1;
	}

	VAR_SET_CUSTOM(var, cvar);

	return 0;
}

/*
 * This function is called during the workload description parsing prior to the
 * execution phase. It is called when parser encounters a variable used as a
 * value (for attributes or command arguments, e.g., instances=$myinstances).
 *
 * At this point, the user might or might NOT have set the value (and consequently
 * its type is not known as well).
 */
avd_t
avd_var_alloc(char *varname)
{
	var_t *var;
	avd_t avd;

	var = var_find_alloc(varname);
	if (!var) {
		filebench_log(LOG_ERROR, "Could not access variable %s", varname);
		filebench_shutdown(1);
	}

	avd = avd_alloc_cmn();
	if (!avd)
		return NULL;

	set_avd_type_by_var(avd, var, 0);

	return avd;
}

static char *
__var_to_string(var_t *var)
{
	char tmp[128];

	if (VAR_HAS_RANDOM(var)) {
		switch (var->var_val.randptr->rnd_type & RAND_TYPE_MASK) {
		case RAND_TYPE_UNIFORM:
			return fb_stralloc("uniform random var");
		case RAND_TYPE_GAMMA:
			return fb_stralloc("gamma random var");
		case RAND_TYPE_TABLE:
			return fb_stralloc("tabular random var");
		default:
			return fb_stralloc("unitialized random var");
		}
	}

	if (VAR_HAS_CUSTOM(var))
			return fb_stralloc("custom variable");

	if (VAR_HAS_STRING(var) && var->var_val.string)
		return fb_stralloc(var->var_val.string);

	if (VAR_HAS_BOOLEAN(var)) {
		if (var->var_val.boolean)
			return fb_stralloc("true");
		else
			return fb_stralloc("false");
	}

	if (VAR_HAS_INTEGER(var)) {
		(void) snprintf(tmp, sizeof (tmp), "%llu",
			(u_longlong_t)var->var_val.integer);
		return fb_stralloc(tmp);
	}

	if (VAR_HAS_DOUBLE(var)) {
		(void) snprintf(tmp, sizeof (tmp), "%lf",
			var->var_val.dbl);
		return fb_stralloc(tmp);
	}

	return fb_stralloc("No default");
}

char *
var_to_string(char *name)
{
	var_t *var;

	var = var_find(name);
	if (!var)
		return NULL;

	return __var_to_string(var);
}

char *
var_randvar_to_string(char *name, int param_name)
{
	var_t *var;
	uint64_t value;
	char tmp[128];

	var = var_find(name);
	if (!var)
		return var_to_string(name);

	if (!VAR_HAS_RANDOM(var))
		return var_to_string(name);

	switch (param_name) {
	case RAND_PARAM_TYPE:
		switch (var->var_val.randptr->rnd_type & RAND_TYPE_MASK) {
		case RAND_TYPE_UNIFORM:
			return fb_stralloc("uniform");
		case RAND_TYPE_GAMMA:
			return fb_stralloc("gamma");
		case RAND_TYPE_TABLE:
			return fb_stralloc("tabular");
		default:
			return fb_stralloc("uninitialized");
		}

	case RAND_PARAM_SRC:
		if (var->var_val.randptr->rnd_type & RAND_SRC_GENERATOR)
			return fb_stralloc("rand48");
		else
			return fb_stralloc("urandom");

	case RAND_PARAM_SEED:
		value = avd_get_int(var->var_val.randptr->rnd_seed);
		break;

	case RAND_PARAM_MIN:
		value = avd_get_int(var->var_val.randptr->rnd_min);
		break;

	case RAND_PARAM_MEAN:
		value = avd_get_int(var->var_val.randptr->rnd_mean);
		break;

	case RAND_PARAM_GAMMA:
		value = avd_get_int(var->var_val.randptr->rnd_gamma);
		break;

	case RAND_PARAM_ROUND:
		value = avd_get_int(var->var_val.randptr->rnd_round);
		break;

	default:
		return NULL;

	}

	/* just an integer value if we got here */
	(void) snprintf(tmp, sizeof (tmp), "%llu", (u_longlong_t)value);
	return (fb_stralloc(tmp));
}

/* XXX: Local variables related */

static var_t *
var_find_list_only(char *name, var_t *var_list)
{
	var_t *var;

	for (var = var_list; var; var = var->var_next) {
		if (!strcmp(var->var_name, name))
			return var;
	}

	return NULL;
}

static var_t *
var_find_local_normal(char *name)
{
	var_t *var;

	var = var_find_list_only(name, filebench_shm->shm_var_loc_list);
	if (!var)
		var = var_find_list_only(name, filebench_shm->shm_var_list);

	return var;
}

/*
 * Copies the value stored in the source variable into the destination
 * variable.  Returns -1 if any problems encountered, 0 otherwise.
 */
static int
var_copy(var_t *dst_var, var_t *src_var) {
	char *strptr;

	if (VAR_HAS_BOOLEAN(src_var))
		VAR_SET_BOOL(dst_var, src_var->var_val.boolean);

	if (VAR_HAS_INTEGER(src_var))
		VAR_SET_INT(dst_var, src_var->var_val.integer);

	if (VAR_HAS_DOUBLE(src_var))
		VAR_SET_DBL(dst_var, src_var->var_val.dbl);

	if (VAR_HAS_STRING(src_var)) {
		strptr = ipc_stralloc(src_var->var_val.string);
		if (!strptr) {
			filebench_log(LOG_ERROR,
				"Cannot assign string for variable %s",
				dst_var->var_name);
			return -1;
		}
		VAR_SET_STR(dst_var, strptr);
	}

	return 0;
}

/*
 * Allocates a local var (var_t) from interprocess shared memory after
 * first adjusting the name to elminate the leading $.
 */
var_t *
var_lvar_alloc_local(char *name)
{
	return var_alloc(name);
}

/*
 * Allocates a local var and then extracts the var_string from
 * the var named "string" and copies it into the var_string
 * of the var "name", after first allocating a piece of
 * interprocess shared string memory. Returns a pointer to the
 * newly allocated local var or NULL on error.
 */
var_t *
var_lvar_assign_var(char *name, char *src_name)
{
	var_t *dst_var, *src_var;
	char *strptr;

	src_name += 1;

	src_var = var_find_local_normal(src_name);
	if (!src_var) {
		filebench_log(LOG_ERROR,
			"Cannot find source variable %s", src_name);
		return NULL;
	}

	dst_var = var_lvar_alloc_local(name);
	if (!dst_var) {
		filebench_log(LOG_ERROR, "Cannot assign variable %s", name);
		return NULL;
	}

	if (VAR_HAS_BOOLEAN(src_var)) {
		VAR_SET_BOOL(dst_var, src_var->var_val.boolean);
	} else if (VAR_HAS_INTEGER(src_var)) {
		VAR_SET_INT(dst_var, src_var->var_val.integer);
	} else if (VAR_HAS_STRING(src_var)) {
		strptr = ipc_stralloc(src_var->var_val.string);
		if (!strptr) {
			filebench_log(LOG_ERROR,
				"Cannot assign variable %s", name);
			return NULL;
		}
		VAR_SET_STR(dst_var, strptr);
	} else if (VAR_HAS_DOUBLE(src_var)) {
		VAR_SET_INT(dst_var, src_var->var_val.dbl);
	} else if (VAR_HAS_RANDOM(src_var))
		VAR_SET_RANDOM(dst_var, src_var->var_val.randptr);

	return dst_var;
}

var_t *
var_lvar_assign_boolean(char *name, boolean_t bool)
{
	var_t *var;

	var = var_lvar_alloc_local(name);
	if (!var) {
		filebench_log(LOG_ERROR, "Cannot assign variable %s",
			name);
		return NULL;
	}

	VAR_SET_BOOL(var, bool);

	return var;
}

var_t *
var_lvar_assign_integer(char *name, uint64_t integer)
{
	var_t *var;

	var = var_lvar_alloc_local(name);
	if (!var) {
		filebench_log(LOG_ERROR, "Cannot assign variable %s",
			name);
		return NULL;
	}

	VAR_SET_INT(var, integer);

	return var;
}

var_t *
var_lvar_assign_double(char *name, double dbl)
{
	var_t *var;

	var = var_lvar_alloc_local(name);

	if (!var) {
		filebench_log(LOG_ERROR, "Cannot assign variable %s",
						name);
		return NULL;
	}

	VAR_SET_DBL(var, dbl);

	return var;
}

var_t *
var_lvar_assign_string(char *name, char *string)
{
	var_t *var;
	char *strptr;

	var = var_lvar_alloc_local(name);
	if (!var) {
		filebench_log(LOG_ERROR, "Cannot assign variable %s",
					name);
		return NULL;
	}

	strptr = ipc_stralloc(string);
	if (!strptr) {
		filebench_log(LOG_ERROR, "Cannot assign variable %s",
				name);
		return NULL;
	}

	VAR_SET_STR(var, strptr);

	return var;
}

/*
 * replace the avd_t attribute value descriptor in the new FLOW_MASTER flowop
 * that points to a local variable with a new avd_t containing
 * the actual value from the local variable.
 */
void
avd_update(avd_t *avdp, var_t *lvar_list)
{
	/* Empty or not indirect, so no update needed */
	return;
}

void
var_update_comp_lvars(var_t *newlvar, var_t *proto_comp_vars,
			var_t *mstr_lvars)
{
	var_t *proto_lvar;

	/* find the prototype lvar from the inherited list */
	proto_lvar = var_find_list_only(newlvar->var_name, proto_comp_vars);

	if (!proto_lvar)
		return;

	/*
	 * if the new local variable has not already been assigned
	 * a value, try to copy a value from the prototype local variable
	 */
	if (VAR_HAS_UNKNOWN(newlvar)) {
		/* copy value from prototype lvar to new lvar */
		(void) var_copy(newlvar, proto_lvar);
	}
}
