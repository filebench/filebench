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

#ifndef _FB_VARS_H
#define	_FB_VARS_H

#include "filebench.h"

typedef uint64_t fbint_t;

/* Attribute Value Descriptor types */
typedef enum avd_type {
	AVD_INVALID = 0,	/* avd is empty */
	AVD_VAL_BOOL,		/* avd contains a boolean_t */
	AVD_VARVAL_BOOL,	/* avd points to the boolean_t in a var_t */
	AVD_VAL_INT,		/* avd contains an uint64_t */
	AVD_VARVAL_INT,		/* avd points to the uint64_t in a var_t */
	AVD_VAL_STR,		/* avd contains a sting (*char) */
	AVD_VARVAL_STR,		/* avd points to a string in a var_t */
	AVD_VAL_DBL,		/* avd contains a double float */
	AVD_VARVAL_DBL,		/* avd points to the double in a var_t */
	AVD_RANDVAR		/* avd points to the randdist_t associated */
				/* with a random type var_t */
} avd_type_t;

/* Attribute Value Descriptor */
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
		struct randdist *randptr;
		struct var	*varptr;
	} avd_val;
} *avd_t;

#define	AVD_IS_RANDOM(vp)	((vp) && ((vp)->avd_type == AVD_RANDVAR))
#define	AVD_IS_STRING(vp)	((vp) && (((vp)->avd_type == AVD_VAL_STR) || \
				((vp)->avd_type == AVD_VARVAL_STR)))
#define	AVD_IS_VAR(vp)		((vp) && \
				(((vp)->avd_type == AVD_RANDVAR) || \
				((vp)->avd_type == AVD_VARVAL_BOOL) || \
				((vp)->avd_type == AVD_VARVAL_INT) || \
				((vp)->avd_type == AVD_VARVAL_STR) || \
				((vp)->avd_type == AVD_VARVAL_DBL)))

typedef struct var {
	char		*var_name;
	int		var_type;	/* for types and subtypes below */
	struct var	*var_next;
	union {
		boolean_t	boolean;
		uint64_t		integer;
		double		dbl_flt;
		char		*string;
		struct randdist *randptr;
		struct var	*varptr2;
	} var_val;
	struct var	*var_varptr1;
} var_t;

/* basic var types */
#define	VAR_TYPE_GLOBAL		0x0000	/* global variable */
#define	VAR_TYPE_DYNAMIC	0x1000	/* dynamic variable */
#define	VAR_TYPE_RANDOM		0x2000	/* random variable */
#define	VAR_TYPE_LOCAL		0x3000	/* local variable */
#define	VAR_TYPE_MASK		0xf000

/* various var subtypes that a var can be set to */
#define	VAR_TYPE_BOOL_SET	0x0100	/* var contains a boolean */
#define	VAR_TYPE_INT_SET	0x0200	/* var contains an integer */
#define	VAR_TYPE_STR_SET	0x0300	/* var contains a string */
#define	VAR_TYPE_DBL_SET	0x0400	/* var contains a double */
#define	VAR_TYPE_RAND_SET	0x0500	/* var contains a randdist pointer */
#define	VAR_TYPE_SET_MASK	0x0f00

/* useful macroses */

#define	VAR_HAS_BOOLEAN(vp) \
	(((vp)->var_type & VAR_TYPE_SET_MASK) == VAR_TYPE_BOOL_SET)

#define	VAR_HAS_INTEGER(vp) \
	(((vp)->var_type & VAR_TYPE_SET_MASK) == VAR_TYPE_INT_SET)

#define	VAR_HAS_DOUBLE(vp) \
	(((vp)->var_type & VAR_TYPE_SET_MASK) == VAR_TYPE_DBL_SET)

#define	VAR_HAS_STRING(vp) \
	(((vp)->var_type & VAR_TYPE_SET_MASK) == VAR_TYPE_STR_SET)

#define	VAR_HAS_RANDDIST(vp) \
	(((vp)->var_type & VAR_TYPE_SET_MASK) == VAR_TYPE_RAND_SET)

#define	VAR_SET_BOOL(vp, val)	\
	{			\
		(vp)->var_val.boolean = (val); \
		(vp)->var_type = \
		(((vp)->var_type & (~VAR_TYPE_SET_MASK)) | VAR_TYPE_BOOL_SET);\
	}

#define	VAR_SET_INT(vp, val)	\
	{			\
		(vp)->var_val.integer = (val); \
		(vp)->var_type = \
		(((vp)->var_type & (~VAR_TYPE_SET_MASK)) | VAR_TYPE_INT_SET); \
	}

#define	VAR_SET_DBL(vp, val)	\
	{			\
		(vp)->var_val.dbl_flt = (val); \
		(vp)->var_type = \
		    (((vp)->var_type & (~VAR_TYPE_SET_MASK)) | \
		    VAR_TYPE_DBL_SET); \
	}

#define	VAR_SET_STR(vp, val)	\
	{			\
		(vp)->var_val.string = (val); \
		(vp)->var_type = \
		    (((vp)->var_type & (~VAR_TYPE_SET_MASK)) | \
		    VAR_TYPE_STR_SET); \
	}

#define	VAR_SET_RAND(vp, val)	\
	{			\
		(vp)->var_val.randptr = (val); \
		(vp)->var_type = \
		    (((vp)->var_type & (~VAR_TYPE_SET_MASK)) | \
		    VAR_TYPE_RAND_SET); \
	}

avd_t avd_bool_alloc(boolean_t bool);
avd_t avd_int_alloc(uint64_t integer);
avd_t avd_str_alloc(char *string);

boolean_t avd_get_bool(avd_t);
uint64_t avd_get_int(avd_t);
double avd_get_dbl(avd_t);
char *avd_get_str(avd_t);

void avd_update(avd_t *avdp, var_t *lvar_list);

avd_t var_ref_attr(char *name);

int var_assign_boolean(char *name, boolean_t bool);
int var_assign_integer(char *name, uint64_t integer);
int var_assign_double(char *name, double dbl);
int var_assign_string(char *name, char *string);

void var_update_comp_lvars(var_t *newlvar, var_t *proto_comp_vars,
				var_t *mstr_lvars);
var_t *var_define_randvar(char *name);

var_t *var_find_randvar(char *name);

var_t *var_lvar_alloc_local(char *name);
var_t *var_lvar_assign_boolean(char *name, boolean_t);
var_t *var_lvar_assign_integer(char *name, uint64_t);
var_t *var_lvar_assign_double(char *name, double);
var_t *var_lvar_assign_string(char *name, char *string);
var_t *var_lvar_assign_var(char *name, char *src_name);

char *var_to_string(char *name);
char *var_randvar_to_string(char *name, int param);

#endif	/* _FB_VARS_H */
