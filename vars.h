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
 */

#ifndef _VARS_H
#define	_VARS_H

#include "filebench.h"

/* Attribute Value Descriptor (AVD) types */
typedef enum avd_type {
	AVD_INVALID = 0,	/* avd is empty */

	AVD_VAL_BOOL,		/* avd contains a boolean_t */
	AVD_VARVAL_BOOL,	/* avd points to the boolean_t in a var_t */
	AVD_VAL_INT,		/* avd contains an uint64_t */
	AVD_VARVAL_INT,		/* avd points to the uint64_t in a var_t */
	AVD_VAL_DBL,		/* avd contains a double float */
	AVD_VARVAL_DBL,		/* avd points to the double in a var_t */
	AVD_VAL_STR,		/* avd contains a sting (*char) */
	AVD_VARVAL_STR,		/* avd points to a string in a var_t */

	AVD_VARVAL_UNKNOWN,	/* avd points to a variable whose type is not
				 * known yet */

	AVD_VARVAL_RANDOM,	/* avd points to the randdist_t associated */
				/* with a random variable type var_t */

	AVD_VARVAL_CUSTOM	/* avd points to the cvar_t associated */
				/* with a custom variable type var_t */

} avd_type_t;

/* Attribute Value Descriptor (AVD) */
typedef struct avd {
	avd_type_t avd_type;
	union {
		boolean_t	boolval;
		boolean_t	*boolptr;
		uint64_t	intval;
		uint64_t	*intptr;
		double		dblval;
		double		*dblptr;
		char		*strval;
		char		**strptr;
		struct var	*varptr;	/*
						 * Used by AVDs that point to
						 * uninitialized variables of
						 * yet unknown type.
						 */
		struct randdist *randptr;
		struct cvar	*cvarptr;
	} avd_val;
} *avd_t;

#define	AVD_IS_RANDOM(vp)	((vp) && ((vp)->avd_type == AVD_VARVAL_RANDOM))
#define	AVD_IS_STRING(vp)	((vp) && (((vp)->avd_type == AVD_VAL_STR) || \
				((vp)->avd_type == AVD_VARVAL_STR)))
#define	AVD_IS_BOOL(vp)		((vp) && (((vp)->avd_type == AVD_VAL_BOOL) || \
				((vp)->avd_type == AVD_VARVAL_BOOL)))
#define	AVD_IS_INT(vp)		((vp) && (((vp)->avd_type == AVD_VAL_INT) || \
				((vp)->avd_type == AVD_VARVAL_INT)))

/* Variable Types */
typedef enum var_type {
	VAR_INVALID = 0,
	VAR_BOOL,
	VAR_INT,
	VAR_DBL,
	VAR_STR,
	VAR_RANDOM,
	VAR_CUSTOM,
	VAR_UNKNOWN,
} var_type_t;

typedef struct var {
	char		*var_name;
	var_type_t	var_type;
	struct var	*var_next;
	union {
		boolean_t	boolean;
		uint64_t	integer;
		double		dbl;
		char		*string;
		struct randdist *randptr;
		struct cvar 	*cvarptr;
	} var_val;
} var_t;


#define	VAR_HAS_BOOLEAN(vp) \
	((vp)->var_type == VAR_BOOL)
#define	VAR_HAS_INTEGER(vp) \
	((vp)->var_type == VAR_INT)
#define	VAR_HAS_DOUBLE(vp) \
	((vp)->var_type == VAR_DBL)
#define	VAR_HAS_STRING(vp) \
	((vp)->var_type == VAR_STR)
#define	VAR_HAS_RANDOM(vp) \
	((vp)->var_type == VAR_RANDOM)
#define	VAR_HAS_CUSTOM(vp) \
	((vp)->var_type == VAR_CUSTOM)
#define	VAR_HAS_UNKNOWN(vp) \
	((vp)->var_type == VAR_UNKNOWN)

#define	VAR_SET_BOOL(vp, val)	\
	{			\
		(vp)->var_val.boolean = (val); \
		(vp)->var_type = VAR_BOOL;\
	}
#define	VAR_SET_INT(vp, val)	\
	{			\
		(vp)->var_val.integer = (val); \
		(vp)->var_type = VAR_INT; \
	}
#define	VAR_SET_DBL(vp, val)	\
	{			\
		(vp)->var_val.dbl = (val); \
		(vp)->var_type = VAR_DBL; \
	}
#define	VAR_SET_STR(vp, val)	\
	{			\
		(vp)->var_val.string = (val); \
		(vp)->var_type = VAR_STR; \
	}
#define	VAR_SET_RANDOM(vp, val)	\
	{			\
		(vp)->var_val.randptr = (val); \
		(vp)->var_type = VAR_RANDOM; \
	}
#define	VAR_SET_CUSTOM(vp, val)	\
	{			\
		(vp)->var_val.cvarptr = (val); \
		(vp)->var_type = VAR_CUSTOM; \
	}
#define	VAR_SET_UNKNOWN(vp)	\
	{			\
		(vp)->var_type = VAR_UNKNOWN; \
	}

avd_t avd_bool_alloc(boolean_t bool);
avd_t avd_int_alloc(uint64_t integer);
avd_t avd_dbl_alloc(double integer);
avd_t avd_str_alloc(char *string);
avd_t avd_var_alloc(char *varname);

int var_assign_boolean(char *name, boolean_t bool);
int var_assign_integer(char *name, uint64_t integer);
int var_assign_double(char *name, double dbl);
int var_assign_string(char *name, char *string);
int var_assign_random(char *name, struct randdist *rndp);
int var_assign_custom(char *name, struct cvar *cvar);

boolean_t avd_get_bool(avd_t);
uint64_t avd_get_int(avd_t);
double avd_get_dbl(avd_t);
char *avd_get_str(avd_t);

/* Local variables related */
void avd_update(avd_t *avdp, var_t *lvar_list);
void var_update_comp_lvars(var_t *newlvar, var_t *proto_comp_vars,
				var_t *mstr_lvars);
var_t *var_lvar_alloc_local(char *name);
var_t *var_lvar_assign_boolean(char *name, boolean_t);
var_t *var_lvar_assign_integer(char *name, uint64_t);
var_t *var_lvar_assign_double(char *name, double);
var_t *var_lvar_assign_string(char *name, char *string);
var_t *var_lvar_assign_var(char *name, char *src_name);

/* miscelaneous */
char *var_to_string(char *name);
char *var_randvar_to_string(char *name, int param);

#endif	/* _VARS_H */
