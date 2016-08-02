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
 * Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 * Portions Copyright 2008 Denis Cheng
 */

%{

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <locale.h>
#include <sys/utsname.h>
#include <sys/statvfs.h>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "parsertypes.h"
#include "filebench.h"
#include "utils.h"
#include "stats.h"
#include "vars.h"
#include "eventgen.h"
#include "aslr.h"
#include "multi_client_sync.h"

/* yacc and lex externals */
extern FILE *yyin;
extern int yydebug;
extern void yyerror(char *s);
extern int yylex(void);

/* executable name to execute worker processes later */
char *execname;

/* utilities */
static cmd_t *alloc_cmd(void);
static attr_t *alloc_attr(void);
static attr_t *alloc_lvar_attr(var_t *var);
static attr_t *get_attr(cmd_t *cmd, int64_t name);
static void get_attr_lvars(cmd_t *cmd, flowop_t *flowop);
static list_t *alloc_list();
static probtabent_t *alloc_probtabent(void);
static void add_lvar_to_list(var_t *newlvar, var_t **lvar_list);

/* Info Commands */
static void parser_fileset_list(cmd_t *);
static void parser_flowop_list(cmd_t *);

/* Define Commands */
static void parser_proc_define(cmd_t *);
static void parser_thread_define(cmd_t *, procflow_t *);
static void parser_flowop_define(cmd_t *, threadflow_t *, flowop_t **, int);
static void parser_composite_flowop_define(cmd_t *);
static void parser_file_define(cmd_t *);
static void parser_fileset_define(cmd_t *);
static void parser_var_assign_random(char *, cmd_t *);
static void parser_var_assign_custom(char *, cmd_t *);

/* Create Commands */
static void parser_fileset_create(cmd_t *);

/* Run Commands */
static void parser_run(cmd_t *cmd);
static void parser_run_variable(cmd_t *cmd);
static void parser_psrun(cmd_t *cmd);

/* Shutdown (Quit) Commands */
static void parser_filebench_shutdown(cmd_t *cmd);

/* Other Commands */
static void parser_echo(cmd_t *cmd);
static void parser_system(cmd_t *cmd);
static void parser_eventgen(cmd_t *cmd);
static void parser_enable_mc(cmd_t *cmd);
static void parser_domultisync(cmd_t *cmd);
static void parser_sleep(cmd_t *cmd);
static void parser_sleep_variable(cmd_t *cmd);
static void parser_version(cmd_t *cmd);
static void parser_enable_lathist(cmd_t *cmd);

%}

%union {
	int64_t		 ival;
	unsigned char	 bval;
	char *		 sval;
	avd_t		 avd;
	cmd_t		*cmd;
	attr_t		*attr;
	list_t		*list;
	probtabent_t	*rndtb;
}

%start commands

%token FSC_LIST FSC_DEFINE FSC_QUIT FSC_DEBUG FSC_CREATE FSC_SLEEP FSC_SET
%token FSC_SYSTEM FSC_EVENTGEN FSC_ECHO FSC_RUN FSC_PSRUN FSC_VERSION FSC_ENABLE
%token FSC_DOMULTISYNC

%token FSV_STRING FSV_VAL_POSINT FSV_VAL_NEGINT FSV_VAL_BOOLEAN FSV_VARIABLE 
%token FSV_WHITESTRING FSV_RANDUNI FSV_RANDTAB FSV_URAND FSV_RAND48

%token FSE_FILE FSE_FILES FSE_FILESET FSE_PROC FSE_THREAD FSE_FLOWOP FSE_CVAR
%token FSE_RAND FSE_MODE FSE_MULTI

%token FSK_SEPLST FSK_OPENLST FSK_CLOSELST FSK_OPENPAR FSK_CLOSEPAR FSK_ASSIGN
%token FSK_IN FSK_QUOTE

%token FSA_SIZE FSA_PREALLOC FSA_PARALLOC FSA_PATH FSA_REUSE
%token FSA_MEMSIZE FSA_RATE FSA_READONLY FSA_TRUSTTREE
%token FSA_IOSIZE FSA_FILENAME FSA_WSS FSA_NAME FSA_RANDOM FSA_INSTANCES
%token FSA_DSYNC FSA_TARGET FSA_ITERS FSA_NICE FSA_VALUE FSA_BLOCKING
%token FSA_HIGHWATER FSA_DIRECTIO FSA_DIRWIDTH FSA_FD FSA_SRCFD FSA_ROTATEFD
%token FSA_ENTRIES FSA_DIRDEPTHRV FSA_DIRGAMMA FSA_USEISM FSA_TYPE
%token FSA_LEAFDIRS FSA_INDEXED FSA_RANDTABLE FSA_RANDSRC FSA_ROUND
%token FSA_RANDSEED FSA_RANDGAMMA FSA_RANDMEAN FSA_MIN FSA_MAX FSA_MASTER
%token FSA_CLIENT FSS_TYPE FSS_SEED FSS_GAMMA FSS_MEAN FSS_MIN FSS_SRC FSS_ROUND
%token FSA_LVAR_ASSIGN FSA_ALLDONE FSA_FIRSTDONE FSA_TIMEOUT FSA_LATHIST
%token FSA_NOREADAHEAD FSA_IOPRIO FSA_WRITEONLY FSA_PARAMETERS FSA_NOUSESTATS

%type <ival> FSV_VAL_POSINT FSV_VAL_NEGINT
%type <bval> FSV_VAL_BOOLEAN
%type <sval> FSV_STRING FSV_WHITESTRING FSV_VARIABLE FSK_ASSIGN

%type <ival> FSC_DEFINE FSC_SET FSC_RUN FSC_ENABLE FSC_PSRUN
%type <ival> FSC_DOMULTISYNC
%type <ival> FSE_FILE FSE_FILES FSE_PROC FSE_THREAD FSC_VERSION

%type <sval> name

%type <cmd> command run_command list_command psrun_command
%type <cmd> proc_define_command files_define_command
%type <cmd> flowop_define_command debug_command create_command
%type <cmd> sleep_command set_command
%type <cmd> system_command flowop_command
%type <cmd> eventgen_command quit_command flowop_list thread_list
%type <cmd> thread echo_command
%type <cmd> version_command enable_command multisync_command
%type <cmd> set_variable set_random_variable set_custom_variable set_mode

%type <attr> fileset_attr_op fileset_attr_ops file_attr_ops file_attr_op p_attr_op t_attr_op p_attr_ops t_attr_ops
%type <attr> fo_attr_op fo_attr_ops ev_attr_op ev_attr_ops
%type <attr> randvar_attr_op randvar_attr_ops randvar_attr_typop
%type <attr> randvar_attr_srcop attr_value
%type <attr> comp_lvar_def comp_attr_op comp_attr_ops
%type <attr> enable_multi_ops enable_multi_op multisync_op
%type <attr> cvar_attr_ops cvar_attr_op
%type <list> whitevar_string whitevar_string_list
%type <ival> attrs_define_thread attrs_flowop
%type <ival> attrs_define_fileset attrs_define_file attrs_define_proc attrs_eventgen attrs_define_comp
%type <ival> randvar_attr_name FSA_TYPE randtype_name
%type <ival> randsrc_name FSA_RANDSRC em_attr_name
%type <ival> FSS_TYPE FSS_SEED FSS_GAMMA FSS_MEAN FSS_MIN FSS_SRC
%type <ival> cvar_attr_name

%type <rndtb>  probtabentry_list probtabentry
%type <avd> var_int_val
%%

commands: commands command
{
	if ($2->cmd)
		$2->cmd($2);

	free($2);
}
| commands error
{
	YYABORT;
}
|;

command:
  proc_define_command
| files_define_command
| flowop_define_command
| debug_command
| eventgen_command
| create_command
| echo_command
| list_command
| run_command
| psrun_command
| set_command
| quit_command
| sleep_command
| system_command
| version_command
| enable_command
| multisync_command

eventgen_command: FSC_EVENTGEN
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = &parser_eventgen;
}
| eventgen_command ev_attr_ops
{
	$1->cmd_attr_list = $2;
};

system_command: FSC_SYSTEM whitevar_string_list
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;

	$$->cmd_param_list = $2;
	$$->cmd = parser_system;
};

echo_command: FSC_ECHO whitevar_string_list
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;

	$$->cmd_param_list = $2;
	$$->cmd = parser_echo;
};

version_command: FSC_VERSION
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = parser_version;
};

enable_command: FSC_ENABLE FSE_MULTI enable_multi_ops
{

	if (($$ = alloc_cmd()) == NULL)
		YYERROR;

	$$->cmd = parser_enable_mc;
	$$->cmd_attr_list = $3;
}
| FSC_ENABLE FSA_LATHIST
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;

	$$->cmd = parser_enable_lathist;
};

multisync_command: FSC_DOMULTISYNC multisync_op
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;

	$$->cmd = parser_domultisync;
	$$->cmd_attr_list = $2;
}

whitevar_string: FSK_QUOTE FSV_VARIABLE
{
	if (($$ = alloc_list()) == NULL)
			YYERROR;

	$$->list_string = avd_str_alloc($2);
}
| FSK_QUOTE FSV_WHITESTRING
{
	if (($$ = alloc_list()) == NULL)
			YYERROR;

	$$->list_string = avd_str_alloc($2);
};

whitevar_string_list: whitevar_string FSV_WHITESTRING
{
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add string */
	if (($$ = alloc_list()) == NULL)
		YYERROR;

	$$->list_string = avd_str_alloc($2);

	/* Find end of list */
	for (list = $1; list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = $$;
	$$ = $1;

}| whitevar_string FSV_VARIABLE
{
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add variable */
	if (($$ = alloc_list()) == NULL)
		YYERROR;

	$$->list_string = avd_str_alloc($2);

	/* Find end of list */
	for (list = $1; list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = $$;
	$$ = $1;
}| whitevar_string_list FSV_WHITESTRING
{
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add string */
	if (($$ = alloc_list()) == NULL)
		YYERROR;

	$$->list_string = avd_str_alloc($2);

	/* Find end of list */
	for (list = $1; list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = $$;
	$$ = $1;

}| whitevar_string_list FSV_VARIABLE
{
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add variable */
	if (($$ = alloc_list()) == NULL)
		YYERROR;

	$$->list_string = avd_str_alloc($2);

	/* Find end of list */
	for (list = $1; list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = $$;
	$$ = $1;
}| whitevar_string_list FSK_QUOTE
{
	$$ = $1;
}| whitevar_string FSK_QUOTE
{
	$$ = $1;
};

list_command: FSC_LIST FSE_FILESET
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = &parser_fileset_list;
}
| FSC_LIST FSE_FLOWOP
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = &parser_flowop_list;
};

debug_command: FSC_DEBUG FSV_VAL_POSINT
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = NULL;
	filebench_shm->shm_debug_level = $2;
	if (filebench_shm->shm_debug_level > 10) {
		filebench_log(LOG_ERROR, "Debug level set out of range."
					"  Adjusting to 10.");
			filebench_shm->shm_debug_level = 10;
		}
	if (filebench_shm->shm_debug_level > 9)
		yydebug = 1;
};

set_command: set_variable | set_random_variable | set_custom_variable | set_mode;

set_variable: FSC_SET FSV_VARIABLE FSK_ASSIGN FSV_VAL_POSINT
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;

	var_assign_integer($2, $4);

	$$->cmd = NULL;
}
|
FSC_SET FSV_VARIABLE FSK_ASSIGN FSV_VAL_BOOLEAN
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;

	var_assign_boolean($2, $4);

	$$->cmd = NULL;
}
| FSC_SET FSV_VARIABLE FSK_ASSIGN FSK_QUOTE FSV_WHITESTRING FSK_QUOTE
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;

	var_assign_string($2, $5);

	$$->cmd = NULL;
}
| FSC_SET FSV_VARIABLE FSK_ASSIGN FSV_STRING
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;

	var_assign_string($2, $4);

	$$->cmd = NULL;
};

set_random_variable: FSC_SET FSV_VARIABLE FSK_ASSIGN FSE_RAND FSK_OPENPAR randvar_attr_ops FSK_CLOSEPAR
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;

	$$->cmd_attr_list = $6;
	$$->cmd = NULL;

	parser_var_assign_random($2, $$);
}

set_custom_variable: FSC_SET FSV_VARIABLE FSK_ASSIGN FSE_CVAR FSK_OPENPAR cvar_attr_ops FSK_CLOSEPAR
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;

	$$->cmd_attr_list = $6;
	$$->cmd = NULL;

	parser_var_assign_custom($2, $$);
};

set_mode: FSC_SET FSE_MODE FSC_QUIT FSA_TIMEOUT
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;

	filebench_shm->shm_rmode = FILEBENCH_MODE_TIMEOUT;

	$$->cmd = NULL;
}
| FSC_SET FSE_MODE FSC_QUIT FSA_ALLDONE
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;

	filebench_shm->shm_rmode = FILEBENCH_MODE_QALLDONE;

	$$->cmd = NULL;
}
| FSC_SET FSE_MODE FSC_QUIT FSA_FIRSTDONE
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;

	filebench_shm->shm_rmode = FILEBENCH_MODE_Q1STDONE;

	$$->cmd = NULL;
}
| FSC_SET FSE_MODE FSA_NOUSESTATS
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;

	filebench_log(LOG_INFO, "Disabling CPU usage statistics");
	filebench_shm->shm_mmode |= FILEBENCH_MODE_NOUSAGE;

	$$->cmd = NULL;
};

quit_command: FSC_QUIT
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = parser_filebench_shutdown;
};

flowop_list: flowop_command
{
	$$ = $1;
}| flowop_list flowop_command
{
	cmd_t *list = NULL;
	cmd_t *list_end = NULL;

	/* Find end of list */
	for (list = $1; list != NULL;
	    list = list->cmd_next)
		list_end = list;

	list_end->cmd_next = $2;

	filebench_log(LOG_DEBUG_IMPL,
	    "flowop_list adding cmd %zx to list %zx", $2, $1);

	$$ = $1;
};

thread: FSE_THREAD t_attr_ops FSK_OPENLST flowop_list FSK_CLOSELST
{
	/*
	 * Allocate a cmd node per thread, with a
	 * list of flowops attached to the cmd_list
	 */
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd_list = $4;
	$$->cmd_attr_list = $2;
};

thread_list: thread
{
	$$ = $1;
}| thread_list thread
{
	cmd_t *list = NULL;
	cmd_t *list_end = NULL;

	/* Find end of list */
	for (list = $1; list != NULL;
	    list = list->cmd_next)
		list_end = list;

	list_end->cmd_next = $2;

	filebench_log(LOG_DEBUG_IMPL,
	    "thread_list adding cmd %zx to list %zx", $2, $1);

	$$ = $1;
};

proc_define_command: FSC_DEFINE FSE_PROC p_attr_ops FSK_OPENLST thread_list FSK_CLOSELST
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;
	$$->cmd = &parser_proc_define;
	$$->cmd_list = $5;
	$$->cmd_attr_list = $3;
}

files_define_command: FSC_DEFINE FSE_FILE file_attr_ops
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;

	$$->cmd = &parser_file_define;
	$$->cmd_attr_list = $3;
}| FSC_DEFINE FSE_FILESET fileset_attr_ops
{
	$$ = alloc_cmd();
	if (!$$)
		YYERROR;

	$$->cmd = &parser_fileset_define;
	$$->cmd_attr_list = $3;
}

create_command: FSC_CREATE FSE_FILES
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;

	$$->cmd = &parser_fileset_create;
};

sleep_command: FSC_SLEEP FSV_VAL_POSINT
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = parser_sleep;
	$$->cmd_qty = $2;
}
| FSC_SLEEP FSV_VARIABLE
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = parser_sleep_variable;
	$$->cmd_tgt1 = fb_stralloc($2);
}

run_command: FSC_RUN FSV_VAL_POSINT
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = parser_run;
	$$->cmd_qty = $2;
}
| FSC_RUN FSV_VARIABLE
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = parser_run_variable;
	$$->cmd_tgt1 = fb_stralloc($2);
}
| FSC_RUN
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = parser_run;
	$$->cmd_qty = 0;
};

psrun_command: FSC_PSRUN
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = parser_psrun;
	$$->cmd_qty1 = 0;
	$$->cmd_qty = 0;
}
| FSC_PSRUN FSV_VAL_NEGINT
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = parser_psrun;
	$$->cmd_qty1 = $2;
	$$->cmd_qty = 0;

}
| FSC_PSRUN FSV_VAL_POSINT
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = parser_psrun;
	$$->cmd_qty1 = $2;
	$$->cmd_qty = 0;

}
| FSC_PSRUN FSV_VAL_NEGINT FSV_VAL_POSINT
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = parser_psrun;
	$$->cmd_qty1 = $2;
	$$->cmd_qty = $3;
}
| FSC_PSRUN FSV_VAL_POSINT FSV_VAL_POSINT
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = parser_psrun;
	$$->cmd_qty1 = $2;
	$$->cmd_qty = $3;
};

flowop_command: FSE_FLOWOP name
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd_name = fb_stralloc($2);
}
| flowop_command fo_attr_ops
{
	$1->cmd_attr_list = $2;
};

name: FSV_STRING;

file_attr_ops: file_attr_op
{
	$$ = $1;
}
| file_attr_ops FSK_SEPLST file_attr_op
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr; attr = attr->attr_next)
		list_end = attr;

	list_end->attr_next = $3;

	$$ = $1;
};

fileset_attr_ops: fileset_attr_op
{
	$$ = $1;
}
| fileset_attr_ops FSK_SEPLST fileset_attr_op
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr; attr = attr->attr_next)
		list_end = attr;

	list_end->attr_next = $3;

	$$ = $1;
};

file_attr_op: attrs_define_file FSK_ASSIGN attr_value
{
	$$ = $3;
	$$->attr_name = $1;
}
| attrs_define_file
{
	$$ = alloc_attr();
	if (!$$)
		YYERROR;

	$$->attr_name = $1;
	$$->attr_avd = avd_bool_alloc(TRUE);
};

fileset_attr_op: attrs_define_fileset FSK_ASSIGN attr_value
{
	$$ = $3;
	$$->attr_name = $1;
}
| attrs_define_fileset 
{
	$$ = alloc_attr();
	if (!$$)
		YYERROR;

	$$->attr_name = $1;
	$$->attr_avd = avd_bool_alloc(TRUE);
};

/* attribute parsing for random variables */
randvar_attr_ops: randvar_attr_op
{
	$$ = $1;
}
| randvar_attr_ops FSK_SEPLST randvar_attr_op
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = $3;

	$$ = $1;
}
| randvar_attr_ops FSK_SEPLST FSA_RANDTABLE FSK_ASSIGN FSK_OPENLST probtabentry_list FSK_CLOSELST
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */


	if ((attr = alloc_attr()) == NULL)
		YYERROR;

	attr->attr_name = FSA_RANDTABLE;
	attr->attr_obj = (void *)$6;
	list_end->attr_next = attr;
	$$ = $1;
};

randvar_attr_op: randvar_attr_name FSK_ASSIGN attr_value
{
	$$ = $3;
	$$->attr_name = $1;
}
| randvar_attr_name
{
	if (($$ = alloc_attr()) == NULL)
		YYERROR;
	$$->attr_name = $1;
	$$->attr_avd = avd_bool_alloc(TRUE);
}
| FSA_TYPE FSK_ASSIGN randvar_attr_typop
{
	$$ = $3;
	$$->attr_name = FSA_TYPE;
}
| FSA_RANDSRC FSK_ASSIGN randvar_attr_srcop
{
	$$ = $3;
	$$->attr_name = FSA_RANDSRC;
};

probtabentry: FSK_OPENLST var_int_val FSK_SEPLST var_int_val FSK_SEPLST var_int_val FSK_CLOSELST
{
	if (($$ = alloc_probtabent()) == NULL)
		YYERROR;
	$$->pte_percent = $2;
	$$->pte_segmin  = $4;
	$$->pte_segmax  = $6;
};

/* attribute parsing for prob density function table */
probtabentry_list: probtabentry
{
	$$ = $1;
}
| probtabentry_list FSK_SEPLST probtabentry
{
	probtabent_t *pte = NULL;
	probtabent_t *ptelist_end = NULL;

	for (pte = $1; pte != NULL;
	    pte = pte->pte_next)
		ptelist_end = pte; /* Find end of prob table entry list */

	ptelist_end->pte_next = $3;

	$$ = $1;
};

p_attr_ops: p_attr_op
{
	$$ = $1;
}
| p_attr_ops FSK_SEPLST p_attr_op
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = $3;

	$$ = $1;
};

p_attr_op: attrs_define_proc FSK_ASSIGN attr_value
{
	$$ = $3;
	$$->attr_name = $1;
}
| attrs_define_proc
{
	$$ = alloc_attr();
	if (!$$)
		YYERROR;
	$$->attr_name = $1;
	$$->attr_avd = avd_bool_alloc(TRUE);
};

/* attribute parsing thread options */
t_attr_ops: t_attr_op
{
	$$ = $1;
}
| t_attr_ops FSK_SEPLST t_attr_op
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = $3;

	$$ = $1;
};

t_attr_op: attrs_define_thread FSK_ASSIGN attr_value
{
	$$ = $3;
	$$->attr_name = $1;
}
| attrs_define_thread
{
	if (($$ = alloc_attr()) == NULL)
		YYERROR;
	$$->attr_name = $1;
	$$->attr_avd = avd_bool_alloc(TRUE);
};

/* attribute parsing for flowops */
fo_attr_ops: fo_attr_op
{
	$$ = $1;
}
| fo_attr_ops FSK_SEPLST fo_attr_op
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = $3;

	$$ = $1;
}
| fo_attr_ops FSK_SEPLST comp_lvar_def
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = $3;

	$$ = $1;
};

fo_attr_op: attrs_flowop FSK_ASSIGN attr_value
{
	$$ = $3;
	$$->attr_name = $1;
}
| attrs_flowop 
{
	if (($$ = alloc_attr()) == NULL)
		YYERROR;
	$$->attr_name = $1;
	$$->attr_avd = avd_bool_alloc(TRUE);
};

/* attribute parsing for Event Generator */
ev_attr_ops: ev_attr_op
{
	$$ = $1;
}
| ev_attr_ops FSK_SEPLST ev_attr_op
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = $3;

	$$ = $1;
};

ev_attr_op: attrs_eventgen FSK_ASSIGN attr_value
{
	$$ = $3;
	$$->attr_name = $1;
}
| attrs_eventgen 
{
	if (($$ = alloc_attr()) == NULL)
		YYERROR;
	$$->attr_name = $1;
	$$->attr_avd = avd_bool_alloc(TRUE);
};

/* attribute parsing for enable multiple client command */
enable_multi_ops: enable_multi_op
{
	$$ = $1;
}
| enable_multi_ops FSK_SEPLST enable_multi_op
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = $3;

	$$ = $1;
};

enable_multi_op: em_attr_name FSK_ASSIGN attr_value
{
	$$ = $3;
	$$->attr_name = $1;
};

multisync_op: FSA_VALUE FSK_ASSIGN attr_value
{
	$$ = $3;
	$$->attr_name = FSA_VALUE;
};

/*
 * Attribute names
 */
attrs_define_proc:
  FSA_NAME { $$ = FSA_NAME;}
| FSA_INSTANCES { $$ = FSA_INSTANCES;}
| FSA_NICE { $$ = FSA_NICE;}

attrs_define_file:
  FSA_NAME { $$ = FSA_NAME;}
| FSA_PATH { $$ = FSA_PATH;}
| FSA_SIZE { $$ = FSA_SIZE;}
| FSA_PREALLOC { $$ = FSA_PREALLOC;}
| FSA_PARALLOC { $$ = FSA_PARALLOC;}
| FSA_REUSE { $$ = FSA_REUSE;}
| FSA_TRUSTTREE { $$ = FSA_TRUSTTREE;}
| FSA_READONLY { $$ = FSA_READONLY;}
| FSA_WRITEONLY { $$ = FSA_WRITEONLY;}

attrs_define_fileset:
  FSA_NAME { $$ = FSA_NAME;}
| FSA_PATH { $$ = FSA_PATH;}
| FSA_ENTRIES { $$ = FSA_ENTRIES;}
| FSA_SIZE { $$ = FSA_SIZE;}
| FSA_PREALLOC { $$ = FSA_PREALLOC;}
| FSA_PARALLOC { $$ = FSA_PARALLOC;}
| FSA_REUSE { $$ = FSA_REUSE;}
| FSA_TRUSTTREE { $$ = FSA_TRUSTTREE;}
| FSA_READONLY { $$ = FSA_READONLY;}
| FSA_WRITEONLY { $$ = FSA_WRITEONLY;}
| FSA_DIRWIDTH { $$ = FSA_DIRWIDTH;}
| FSA_DIRDEPTHRV { $$ = FSA_DIRDEPTHRV;}
| FSA_DIRGAMMA { $$ = FSA_DIRGAMMA;}
| FSA_LEAFDIRS { $$ = FSA_LEAFDIRS;};

randvar_attr_name:
  FSA_NAME { $$ = FSA_NAME;}
| FSA_RANDSEED { $$ = FSA_RANDSEED;}
| FSA_RANDGAMMA { $$ = FSA_RANDGAMMA;}
| FSA_RANDMEAN { $$ = FSA_RANDMEAN;}
| FSA_MIN { $$ = FSA_MIN;}
| FSA_ROUND { $$ = FSA_ROUND;};

randvar_attr_typop: randtype_name
{
	if (($$ = alloc_attr()) == NULL)
		YYERROR;
	$$->attr_avd = avd_int_alloc($1);
};

randtype_name:
  FSV_RANDUNI { $$ = FSV_RANDUNI;}
| FSV_RANDTAB { $$ = FSV_RANDTAB;}
| FSA_RANDGAMMA { $$ = FSA_RANDGAMMA;};

randvar_attr_srcop: randsrc_name
{
	if (($$ = alloc_attr()) == NULL)
		YYERROR;
	$$->attr_avd = avd_int_alloc($1);
};

randsrc_name:
  FSV_URAND { $$ = FSV_URAND;}
| FSV_RAND48 { $$ = FSV_RAND48;};

cvar_attr_name:
  FSA_TYPE { $$ = FSA_TYPE;}
| FSA_PARAMETERS { $$ = FSA_PARAMETERS;}
| FSA_MIN { $$ = FSA_MIN;}
| FSA_MAX { $$ = FSA_MAX;}
| FSA_ROUND { $$ = FSA_ROUND;};

attrs_define_thread:
  FSA_NAME { $$ = FSA_NAME;}
| FSA_MEMSIZE { $$ = FSA_MEMSIZE;}
| FSA_USEISM { $$ = FSA_USEISM;}
| FSA_INSTANCES { $$ = FSA_INSTANCES;}
| FSA_IOPRIO { $$ = FSA_IOPRIO;};

attrs_flowop:
  FSA_WSS { $$ = FSA_WSS;}
| FSA_FILENAME { $$ = FSA_FILENAME;}
| FSA_NAME { $$ = FSA_NAME;}
| FSA_RANDOM { $$ = FSA_RANDOM;}
| FSA_FD { $$ = FSA_FD;}
| FSA_SRCFD { $$ = FSA_SRCFD;}
| FSA_ROTATEFD { $$ = FSA_ROTATEFD;}
| FSA_DSYNC { $$ = FSA_DSYNC;}
| FSA_DIRECTIO { $$ = FSA_DIRECTIO;}
| FSA_INDEXED { $$ = FSA_INDEXED;}
| FSA_TARGET { $$ = FSA_TARGET;}
| FSA_ITERS { $$ = FSA_ITERS;}
| FSA_VALUE { $$ = FSA_VALUE;}
| FSA_BLOCKING { $$ = FSA_BLOCKING;}
| FSA_HIGHWATER { $$ = FSA_HIGHWATER;}
| FSA_IOSIZE { $$ = FSA_IOSIZE;}
| FSA_NOREADAHEAD { $$ = FSA_NOREADAHEAD;};

attrs_eventgen:
  FSA_RATE { $$ = FSA_RATE;};

em_attr_name:
  FSA_MASTER { $$ = FSA_MASTER;}
| FSA_CLIENT { $$ = FSA_CLIENT;};

comp_attr_ops: comp_attr_op
{
	$$ = $1;
}
| comp_attr_ops FSK_SEPLST comp_attr_op
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = $3;

	$$ = $1;
}
| comp_attr_ops FSK_SEPLST comp_lvar_def
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = $3;

	$$ = $1;
};

comp_attr_op: attrs_define_comp FSK_ASSIGN attr_value
{
	$$ = $3;
	$$->attr_name = $1;
};

comp_lvar_def: FSV_VARIABLE FSK_ASSIGN FSV_VAL_BOOLEAN
{
	if (($$ = alloc_lvar_attr(var_lvar_assign_boolean($1, $3))) == NULL)
		YYERROR;
}
| FSV_VARIABLE FSK_ASSIGN FSV_VAL_POSINT
{
	if (($$ = alloc_lvar_attr(var_lvar_assign_integer($1, $3))) == NULL)
		YYERROR;
}
| FSV_VARIABLE FSK_ASSIGN FSK_QUOTE FSV_WHITESTRING FSK_QUOTE
{
	if (($$ = alloc_lvar_attr(var_lvar_assign_string($1, $4))) == NULL)
		YYERROR;
}
| FSV_VARIABLE FSK_ASSIGN FSV_STRING
{
	if (($$ = alloc_lvar_attr(var_lvar_assign_string($1, $3))) == NULL)
		YYERROR;
}
| FSV_VARIABLE FSK_ASSIGN FSV_VARIABLE
{
	if (($$ = alloc_lvar_attr(var_lvar_assign_var($1, $3))) == NULL)
		YYERROR;
}
| FSV_VARIABLE
{
	if (($$ = alloc_lvar_attr(var_lvar_alloc_local($1))) == NULL)
		YYERROR;
};

flowop_define_command: FSC_DEFINE FSE_FLOWOP comp_attr_ops FSK_OPENLST flowop_list FSK_CLOSELST
{
	if (($$ = alloc_cmd()) == NULL)
		YYERROR;
	$$->cmd = &parser_composite_flowop_define;
	$$->cmd_list = $5;
	$$->cmd_attr_list = $3;
}
| flowop_define_command comp_attr_ops
{
	$1->cmd_attr_list = $2;
};

/* attribute parsing for custom variables */
cvar_attr_ops: cvar_attr_op
{
	$$ = $1;
}
| cvar_attr_ops FSK_SEPLST cvar_attr_op
{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = $1; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = $3;

	$$ = $1;
}

cvar_attr_op: cvar_attr_name FSK_ASSIGN attr_value
{
	$$ = $3;
	$$->attr_name = $1;
};

attrs_define_comp:
  FSA_NAME { $$ = FSA_NAME;}
| FSA_ITERS { $$ = FSA_ITERS;};

attr_value: FSV_STRING
{
	$$ = alloc_attr();
	if (!$$)
		YYERROR;
	$$->attr_avd = avd_str_alloc($1);
} | FSK_QUOTE FSV_WHITESTRING FSK_QUOTE {
	$$ = alloc_attr();
	if (!$$)
		YYERROR;
	$$->attr_avd = avd_str_alloc($2);
} | FSV_VAL_POSINT {
	$$ = alloc_attr();
	if (!$$)
		YYERROR;
	$$->attr_avd = avd_int_alloc($1);
} | FSV_VAL_BOOLEAN {
	$$ = alloc_attr();
	if (!$$)
		YYERROR;
	$$->attr_avd = avd_bool_alloc($1);
} | FSV_VARIABLE {
	$$ = alloc_attr();
	if (!$$)
		YYERROR;
	$$->attr_avd = avd_var_alloc($1);
};

var_int_val: FSV_VAL_POSINT
{
	$$ = avd_int_alloc($1);
} | FSV_VARIABLE
{
	$$ = avd_var_alloc($1);
};

%%

/*
 * The following C routines implement the various commands defined in the above
 * yacc parser code. The yacc portion checks the syntax of the commands found
 * in a workload file and parses the commands' parameters into lists. The lists
 * are then passed in a cmd_t struct for each command to its related routine in
 * the following section for actual execution.  This section also includes a
 * few utility routines and the main entry point for the program.
 */

#define	USAGE \
"Usage: " \
"filebench {-f <wmlscript> | -h | -c [cvartype]}\n\n" \
"  Filebench version " FILEBENCH_VERSION "\n\n" \
"  Filebench is a file system and storage benchmark that interprets a script\n" \
"  written in its Workload Model Language (WML), and procees to generate the\n" \
"  specified workload. Refer to the README for more details.\n\n" \
"  Visit github.com/filebench/filebench for WML definition and tutorials.\n\n" \
"Options:\n" \
"   -f <wmlscript> generate workload from the specified file\n" \
"   -h             display this help message\n" \
"   -c             display supported cvar types\n" \
"   -c [cvartype]  display options of the specific cvar type\n\n"

static void
usage_exit(int ret, const char *msg)
{
	if (ret) {
		(void)fprintf(stderr, "Usage error: %s\n\n", msg);
		(void)fprintf(stderr, USAGE);
	} else
		printf(USAGE);
	exit(ret);
}

struct fbparams {
	char *execname;
	char *fscriptname;
	char *procname;
	char *shmaddr;
	char *shmpath;
	int instance;
	char *cvartype;
};

static void
init_fbparams(struct fbparams *fbparams)
{
	memset(fbparams, 0, sizeof(*fbparams));
	fbparams->instance = -1;
}

#define FB_MODE_NONE		0
#define FB_MODE_HELP		1
#define FB_MODE_MASTER		2
#define FB_MODE_WORKER		3
#define FB_MODE_CVARS		4

static int
parse_options(int argc, char *argv[], struct fbparams *fbparams)
{
	const char cmd_options[] = "m:s:a:i:hf:c:";
	int mode = FB_MODE_NONE;
	int opt;

	init_fbparams(fbparams);
	fbparams->execname = argv[0];

 	/*
	 * We don't want getopt() to print error messages because
	 * sometimes what it percieves as an error is actually not
	 * an error.  For example, "-c" option might have or might
	 * not have an argument.  If opterr is non-zero, getopt()
	 * prints an error message when "-c"'s argument is missing.
	 */
	opterr = 0;

	/* Either
		(-f <wmlscript>) or
		(-a and -s and -m and -i) or
		(-c [cvartype]) or
		(-h)
	   must be specified */
	while ((opt = getopt(argc, argv, cmd_options)) > 0) {
		switch (opt) {
		/* public parameters */
		case 'h':
			if (mode != FB_MODE_NONE)
				usage_exit(1, "Too many options specified");
			mode = FB_MODE_HELP;
			break;
		case 'c':
			if (mode != FB_MODE_NONE)
				usage_exit(1, "Too many options specified");
			mode = FB_MODE_CVARS;
			fbparams->cvartype = optarg;
			break;
		case 'f':
			if (mode != FB_MODE_NONE)
				usage_exit(1, "Too many options specified");
			mode = FB_MODE_MASTER;
			fbparams->fscriptname = optarg;
			break;
		/* private parameters: when filebench calls itself */
		case 'a':
			if (mode != FB_MODE_NONE &&
				(mode != FB_MODE_WORKER || fbparams->procname))
					usage_exit(1, "Too many options");
			mode = FB_MODE_WORKER;
			fbparams->procname = optarg;
			break;
		case 's':
			if (mode != FB_MODE_NONE &&
				(mode != FB_MODE_WORKER || fbparams->shmaddr))
					usage_exit(1, "Too many options");
			mode = FB_MODE_WORKER;
			sscanf(optarg, "%p", &fbparams->shmaddr);
			break;
		case 'm':
			if (mode != FB_MODE_NONE &&
				(mode != FB_MODE_WORKER || fbparams->shmpath))
					usage_exit(1, "Too many options");
			mode = FB_MODE_WORKER;
			fbparams->shmpath = optarg;
			break;
		case 'i':
			if (mode != FB_MODE_NONE &&
				(mode != FB_MODE_WORKER || fbparams->instance != -1))
					usage_exit(1, "Too many options");
			mode = FB_MODE_WORKER;
			sscanf(optarg, "%d", &fbparams->instance);
			break;
		case '?':
			if (optopt == 'c') {
				if (mode != FB_MODE_NONE)
					usage_exit(1, "Too many options");
				mode = FB_MODE_CVARS;
				break;
			}
		default:
			usage_exit(1, "Unrecognized option");
			break;
		}
	}

	if (mode == FB_MODE_NONE)
		usage_exit(1, "No runtime options specified");

	if (mode == FB_MODE_WORKER) {
		if (!fbparams->procname ||
			!fbparams->shmaddr ||
			!fbparams->shmpath ||
			fbparams->instance == -1)
			usage_exit(1, "Invalid worker settings");
	}

	return mode;
}

static void
worker_mode(struct fbparams *fbparams)
{
	int ret;

	ret = ipc_attach(fbparams->shmaddr, fbparams->shmpath);
	if (ret < 0) {
		filebench_log(LOG_FATAL, "Cannot attach shm for %s",
		    fbparams->procname);
		exit(1);
	}

	/* get correct function pointer for each working process */
	flowop_init(0);

	/* load custom variable libraries and revalidate handles */
	ret = init_cvar_libraries();
	if (ret)
		exit(1);

	ret = revalidate_cvar_handles();
	if (ret)
		exit(1);

	/* execute corresponding procflow */
	ret = procflow_exec(fbparams->procname, fbparams->instance);
	if (ret < 0) {
		filebench_log(LOG_FATAL, "Cannot startup process %s",
		    fbparams->procname);
		exit(1);
	}

	exit(0);
}

void parser_list_cvar_types(void)
{
	cvar_library_info_t *t;

	if (!filebench_shm->shm_cvar_lib_info_list) {
		printf("No custom variables supported.\n");
		return;
	}

	printf("Custom variable types supported:\n");
	for (t = filebench_shm->shm_cvar_lib_info_list; t; t = t->next)
		printf("  %s\n", t->type);

	return;
}

void parser_list_cvar_type_parameters(char *type)
{
	const char *version = NULL;
	const char *usage = NULL;

	cvar_library_info_t *t;

	for (t = filebench_shm->shm_cvar_lib_info_list; t != NULL; t = t->next) {
		if (!strcmp(type, t->type))
			break;
	}

	if (!t) {
		printf("Unknown custom variable type %s.\n", type);
		return;
	}

	printf("Custom variable type: %s\n", t->type);
	printf("Supporting library: %s\n", t->filename);

	if (cvar_libraries[t->index]->cvar_op.cvar_version)
		version = cvar_libraries[t->index]->cvar_op.cvar_version();

	if (cvar_libraries[t->index]->cvar_op.cvar_usage)
		usage = cvar_libraries[t->index]->cvar_op.cvar_usage();


	if (version)
		printf("Version: %s\n", version);
	else
		printf("Oops. No version information provided.\n");

	if (usage)
		printf("Usage:\n%s\n", usage);
	else
		printf("Oops. No usage information provided.\n");

	return;
}

static void
cvars_mode(struct fbparams *fbparams)
{
	int ret;

	ipc_init();

	ret = init_cvar_library_info(FBDATADIR "/cvars");
	if (ret)
		filebench_shutdown(1);

	ret = init_cvar_libraries();
	if (ret)
		filebench_shutdown(1);

	if (fbparams->cvartype)
		parser_list_cvar_type_parameters(fbparams->cvartype);
	else
		parser_list_cvar_types();

	ipc_fini();

	exit(0);
}

/*
 * Shutdown filebench.
 */
static void
parser_abort(int arg)
{
	(void) sigignore(SIGINT);
	filebench_log(LOG_INFO, "Aborting...");
	filebench_shutdown(1);
}

static void
master_mode(struct fbparams *fbparams) {
	int ret;

	printf("Filebench Version %s\n", FILEBENCH_VERSION);

	yyin = fopen(fbparams->fscriptname, "r");
	if (!yyin) {
		filebench_log(LOG_FATAL,
			"Cannot open file %s!", fbparams->fscriptname);
		exit(1);
	}

	execname = fbparams->execname;
	fb_set_shmmax();

	ipc_init();

	/* Below we initialize things that depend on IPC */
	(void)strcpy(filebench_shm->shm_fscriptname,
				fbparams->fscriptname);

	flowop_init(1);
	eventgen_init();

	/* Initialize custom variables. */
	ret = init_cvar_library_info(FBDATADIR "/cvars");
	if (ret)
		filebench_shutdown(1);

	ret = init_cvar_libraries();
	if (ret)
		filebench_shutdown(1);

	signal(SIGINT, parser_abort);

	/* yyparse() after it parsed complete grammar */
	yyparse();

	/* We only get here if there was no
	   run (or similar) command in the
	   end of the WML script. */
	printf("Warning: no run command in the WML script!\n");
	parser_filebench_shutdown((cmd_t *)0);
}

static void
init_common()
{
	disable_aslr();
	my_pid = getpid();
	fb_set_rlimit();
}

/*
 * Entry point for Filebench. Processes command line arguments. The -f option
 * will read in a workload file (the full name and extension must must be
 * given). The -a, -s, -m and -i options are used by the worker process to
 * receive the name, the base address of shared memory, its path, and the
 * process' instance number, respectively. This information is supplied by the
 * master process when it execs worker processes. If the worker process
 * arguments are passed then main will call the procflow_exec() routine which
 * creates worker threadflows and flowops and executes the procflow's portion of
 * the workload model until completion. If worker process arguments are not
 * passed to the process, then it becomes the master process for a filebench
 * run. It initializes the various filebench components and either executes the
 * supplied workload file, or enters interactive mode.
 */
int
main(int argc, char *argv[])
{
	struct fbparams fbparams;
	int mode;

	/* parse_options() exits if detects wrong usage */
	mode = parse_options(argc, argv, &fbparams);

	if (mode == FB_MODE_HELP)
		usage_exit(0, NULL);

	if (mode == FB_MODE_CVARS)
		cvars_mode(&fbparams);

	init_common();

	if (mode == FB_MODE_MASTER)
		master_mode(&fbparams);

	if (mode == FB_MODE_WORKER)
		worker_mode(&fbparams);

	/* We should never reach this point */
	return 0;
}

/*
 * Converts a list of var_strings or ordinary strings to a single ordinary
 * string. It returns a pointer to the string (in malloc'd memory) if found,
 * or NULL otherwise.
 */
char *
parser_list2string(list_t *list)
{
	list_t *l;
	char *string;
	char *tmp;

	string = malloc(MAXPATHLEN);
	if (!string) {
		filebench_log(LOG_ERROR, "Failed to allocate memory");
		return NULL;
	}

	*string = 0;

	/* Format args */
	for (l = list; l != NULL; l = l->list_next) {

		char *lstr = avd_get_str(l->list_string);

		filebench_log(LOG_DEBUG_SCRIPT, "converting string '%s'", lstr);

		/* see if it is a random variable */
		if (l->list_integer) {
			fbint_t param_name;

			tmp = NULL;
			param_name = avd_get_int(l->list_integer);

			switch (param_name) {
			case FSS_TYPE:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_TYPE);
				break;

			case FSS_SRC:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_SRC);
				break;

			case FSS_SEED:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_SEED);
				break;

			case FSS_MIN:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_MIN);
				break;

			case FSS_MEAN:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_MEAN);
				break;

			case FSS_GAMMA:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_GAMMA);
				break;

			case FSS_ROUND:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_ROUND);
				break;
			}

			if (tmp) {
				(void) strcat(string, tmp);
				free(tmp);
			} else {
				(void) strcat(string, lstr);
			}
		} else {
			/* perhaps a normal variable? */
			if ((tmp = var_to_string(lstr)) != NULL) {
				(void) strcat(string, tmp);
				free(tmp);
			} else {
				(void) strcat(string, lstr);
			}
		}
	}

	return string;
}

/*
 * If the list just contains a single string starting with '$', then find
 * or create the named var and return the var's var_string component.
 * Otherwise, convert the list to a string, and allocate a var_string
 * containing a copy of that string. On failure either returns NULL
 * or shuts down the run.
 */
avd_t
parser_list2varstring(list_t *list)
{
	char *lstr = avd_get_str(list->list_string);

	/* Special case - variable name */
	if ((list->list_next == NULL) && (*lstr == '$'))
		return avd_var_alloc(lstr);

	return (avd_str_alloc(parser_list2string(list)));
}

/*
 * Looks for the var named in list_string of the first element of the
 * supplied list. If found, returns the var_val portion of the var in
 * an attribute value descriptor. If the var is not found, cannot be
 * allocated, the supplied list is NULL, or the list_string filed is
 * empty, returns NULL.
 */
avd_t
parser_list2avd(list_t *list)
{
	avd_t avd;
	char *lstr;

	if (list && ((lstr = avd_get_str(list->list_string)) != NULL)) {
		avd = avd_var_alloc(lstr);
		return (avd);
	}

	return (NULL);
}

/*
 * Sets the event generator rate from the attribute supplied with the
 * command. If the attribute doesn't exist the routine does nothing.
 */
static void
parser_eventgen(cmd_t *cmd)
{
	attr_t *attr;

	/* Get the rate from attribute */
	if ((attr = get_attr(cmd, FSA_RATE))) {
		if (attr->attr_avd) {
			eventgen_setrate(attr->attr_avd);
		}
	}
}

/*
 * Lists the fileset name, path name and average size for all defined
 * filesets.
 */
static void
parser_fileset_list(cmd_t *cmd)
{
	(void) fileset_iter(fileset_print);
}

/*
 * Lists the flowop name and instance number for all flowops.
 */
static void
parser_flowop_list(cmd_t *cmd)
{
	flowop_printall();
}

/*
 * Calls procflow_define() to allocate "instances" number of  procflow(s)
 * (processes) with the supplied name. The default number of instances is
 * one. An optional priority level attribute can be supplied and is stored in
 * pf_nice. Finally the routine loops through the list of inner commands, if
 * any, which are defines for threadflows, and passes them one at a time to
 * parser_thread_define() to allocate threadflow entities for the process(es).
 */
static void
parser_proc_define(cmd_t *cmd)
{
	procflow_t *procflow;
	char *name = NULL;
	attr_t *attr;
	avd_t var_instances;
	fbint_t instances;
	cmd_t *inner_cmd;

	attr = get_attr(cmd, FSA_NAME);
	if (attr)
		name = avd_get_str(attr->attr_avd);
	else {
		filebench_log(LOG_ERROR, "process specifies no name");
		filebench_shutdown(1);
	}

	attr = get_attr(cmd, FSA_INSTANCES);
	if (attr) {
		var_instances = attr->attr_avd;
		instances = avd_get_int(var_instances);
		filebench_log(LOG_DEBUG_IMPL,
		    "Setting instances = %llu", (u_longlong_t)instances);
	} else {
		filebench_log(LOG_DEBUG_IMPL,
		    "Defaulting to instances = 1");
		var_instances = avd_int_alloc(1);
		instances = 1;
	}

	procflow = procflow_define(name, var_instances);
	if (!procflow) {
		filebench_log(LOG_ERROR,
		    "Failed to instantiate %d %s process(es)\n",
		    instances, name);
		filebench_shutdown(1);
	}

	attr = get_attr(cmd, FSA_NICE);
	if (attr) {
		filebench_log(LOG_DEBUG_IMPL, "Setting pri = %llu",
			    (u_longlong_t)avd_get_int(attr->attr_avd));
		procflow->pf_nice = attr->attr_avd;
	} else
		procflow->pf_nice = avd_int_alloc(0);

	/* Create the list of threads for this process  */
	for (inner_cmd = cmd->cmd_list; inner_cmd;
	    	inner_cmd = inner_cmd->cmd_next)
		parser_thread_define(inner_cmd, procflow);
}

/*
 * Calls threadflow_define() to allocate "instances" number of  threadflow(s)
 * (threads) with the supplied name. The default number of instances is
 * one. Two other optional attributes may be supplied, one to set the memory
 * size, stored in tf_memsize, and to select the use of Interprocess Shared
 * Memory, which sets the THREADFLOW_USEISM flag in tf_attrs. Finally
 * the routine loops through the list of inner commands, if any, which are
 * defines for flowops, and passes them one at a time to
 * parser_flowop_define() to allocate flowop entities for the threadflows.
 */
static void
parser_thread_define(cmd_t *cmd, procflow_t *procflow)
{
	threadflow_t *threadflow, template;
	attr_t *attr;
	avd_t instances;
	cmd_t *inner_cmd;
	char *name = NULL;

	memset(&template, 0, sizeof (threadflow_t));

	attr = get_attr(cmd, FSA_NAME);
	if (attr)
		name = avd_get_str(attr->attr_avd);
	else {
		filebench_log(LOG_ERROR,
		    "thread in process %s specifies no name",
		    procflow->pf_name);
		filebench_shutdown(1);
	}

	attr = get_attr(cmd, FSA_INSTANCES);
	if (attr)
		instances = attr->attr_avd;
	else
		instances = avd_int_alloc(1);

	attr = get_attr(cmd, FSA_MEMSIZE);
	if (attr)
		template.tf_memsize = attr->attr_avd;
	else /* XXX: really, memsize zero is default?.. */
		template.tf_memsize = avd_int_alloc(0);
	
	attr = get_attr(cmd, FSA_IOPRIO);
	if (attr)
		template.tf_ioprio = attr->attr_avd;
	else /* XXX: really, ioprio is 8 by default?.. */
		template.tf_ioprio = avd_int_alloc(8);


	threadflow = threadflow_define(procflow, name, &template, instances);
	if (!threadflow) {
		filebench_log(LOG_ERROR,
		    "failed to instantiate thread\n");
		filebench_shutdown(1);
	}

	attr = get_attr(cmd, FSA_USEISM);
	if (attr)
		threadflow->tf_attrs |= THREADFLOW_USEISM;

	/* create the list of flowops */
	for (inner_cmd = cmd->cmd_list; inner_cmd;
	    inner_cmd = inner_cmd->cmd_next)
		parser_flowop_define(inner_cmd, threadflow,
		    &threadflow->tf_thrd_fops, FLOW_MASTER);
}

/*
 * Fills in the attributes for a newly allocated flowop
 */
static void
parser_flowop_get_attrs(cmd_t *cmd, flowop_t *flowop)
{
	attr_t *attr;

	/* Get the filename from attribute */
	if ((attr = get_attr(cmd, FSA_FILENAME))) {
		flowop->fo_filename = attr->attr_avd;
		if (flowop->fo_filename == NULL) {
			filebench_log(LOG_ERROR,
			    "define flowop: no filename specfied");
			filebench_shutdown(1);
		}
	} else {
		/* no filename attribute specified */
		flowop->fo_filename = NULL;
	}

	/* Get the iosize of the op */
	if ((attr = get_attr(cmd, FSA_IOSIZE)))
		flowop->fo_iosize = attr->attr_avd;
	else
		flowop->fo_iosize = avd_int_alloc(0);

	/* Get the working set size of the op */
	if ((attr = get_attr(cmd, FSA_WSS)))
		flowop->fo_wss = attr->attr_avd;
	else
		flowop->fo_wss = avd_int_alloc(0);

	/* Random I/O? */
	if ((attr = get_attr(cmd, FSA_RANDOM)))
		flowop->fo_random = attr->attr_avd;
	else
		flowop->fo_random = avd_bool_alloc(FALSE);

	/* Sync I/O? */
	if ((attr = get_attr(cmd, FSA_DSYNC)))
		flowop->fo_dsync = attr->attr_avd;
	else
		flowop->fo_dsync = avd_bool_alloc(FALSE);

	/* Target, for wakeup etc */
	if ((attr = get_attr(cmd, FSA_TARGET)))
		(void) strcpy(flowop->fo_targetname,
		    avd_get_str(attr->attr_avd));

	/* Value */
	if ((attr = get_attr(cmd, FSA_VALUE)))
		flowop->fo_value = attr->attr_avd;
	else
		flowop->fo_value = avd_int_alloc(0);

	/* FD */
	if ((attr = get_attr(cmd, FSA_FD))) {
		flowop->fo_fdnumber = avd_get_int(attr->attr_avd);
		if (flowop->fo_filename != NULL)
			filebench_log(LOG_DEBUG_SCRIPT, "It is not "
			    "advisable to supply both an fd number "
			    "and a fileset name in most cases");
	}

	/* Rotatefd? */
	if ((attr = get_attr(cmd, FSA_ROTATEFD)))
		flowop->fo_rotatefd = attr->attr_avd;
	else
		flowop->fo_rotatefd = avd_bool_alloc(FALSE);

	/* SRC FD, for copies etc... */
	if ((attr = get_attr(cmd, FSA_SRCFD)))
		flowop->fo_srcfdnumber = avd_get_int(attr->attr_avd);

	/* Blocking operation? */
	if ((attr = get_attr(cmd, FSA_BLOCKING)))
		flowop->fo_blocking = attr->attr_avd;
	else
		flowop->fo_blocking = avd_bool_alloc(FALSE);

	/* Direct I/O Operation */
	if ((attr = get_attr(cmd, FSA_DIRECTIO)))
		flowop->fo_directio = attr->attr_avd;
	else
		flowop->fo_directio = avd_bool_alloc(FALSE);

	/* Highwater mark */
	if ((attr = get_attr(cmd, FSA_HIGHWATER))) {
		flowop->fo_highwater = attr->attr_avd;
		if (AVD_IS_RANDOM(attr->attr_avd)) {
			filebench_log(LOG_ERROR,
			    "define flowop: Highwater attr cannot be random");
			filebench_shutdown(1);
		}
	} else {
		flowop->fo_highwater = avd_int_alloc(1);
	}

	/* find file or leaf directory by index number */
	if ((attr = get_attr(cmd, FSA_INDEXED)))
		flowop->fo_fileindex = attr->attr_avd;
	else
		flowop->fo_fileindex = NULL;

	/* Read Ahead Diable */
	if ((attr = get_attr(cmd, FSA_NOREADAHEAD)))
		flowop->fo_noreadahead = attr->attr_avd;
	else
		flowop->fo_noreadahead = avd_bool_alloc(FALSE);


}

/*
 * defines the FLOW_MASTER flowops within a FLOW_MASTER instance of
 * a composit flowop. Default attributes from the FLOW_INNER_DEF instances
 * of the composit flowop's inner flowops are used if set. Otherwise
 * default attributes from the FLOW_MASTER instance of the composit flowop
 * are used, which may include defaults from the original FLOW_DEFINITION
 * of the composit flowop.
 */
static void
parser_inner_flowop_define(threadflow_t *thread, flowop_t *comp0_flow,
			   flowop_t *comp_mstr_flow)
{
	flowop_t *inner_flowtype, *inner_flowop;

	/* follow flowop list, creating composit names */
	inner_flowtype = comp0_flow->fo_comp_fops;
	comp_mstr_flow->fo_comp_fops = NULL;

	while (inner_flowtype) {
		char fullname[MAXPATHLEN];

		/* create composite_name.name for new flowop */
		snprintf(fullname, MAXPATHLEN, "%s.%s",
		    comp_mstr_flow->fo_name, inner_flowtype->fo_name);

		if ((inner_flowop = flowop_define(thread, fullname,
		    inner_flowtype, &comp_mstr_flow->fo_comp_fops,
		    FLOW_MASTER, 0)) == NULL) {
			filebench_log(LOG_ERROR,
			    "define flowop: Failed to instantiate flowop %s\n",
			    fullname);
			filebench_shutdown(1);
		}

		/* if applicable, update filename attribute */
		if (inner_flowop->fo_filename) {
			char *name;

			/* fix up avd_t */
			avd_update(&inner_flowop->fo_filename,
			    comp_mstr_flow->fo_lvar_list);

			/* see if ready to get the file or fileset */
			name = avd_get_str(inner_flowop->fo_filename);
			if (name) {

				inner_flowop->fo_fileset = fileset_find(name);

				if (inner_flowop->fo_fileset == NULL) {
					filebench_log(LOG_ERROR,
					    "inr flowop %s: file %s not found",
					    inner_flowop->fo_name, name);
					filebench_shutdown(1);
				}
			}
		}

		/* update attributes from local variables */
		avd_update(&inner_flowop->fo_iters,
		    comp_mstr_flow->fo_lvar_list);

		/* if the inner flowop is a composit flowop, recurse */
		if (inner_flowtype->fo_type == FLOW_TYPE_COMPOSITE) {
			var_t *newlvar, *proto_lvars, *lvar_ptr;

			proto_lvars = inner_flowop->fo_lvar_list;
			inner_flowop->fo_lvar_list = 0;

			for (lvar_ptr = inner_flowtype->fo_lvar_list; lvar_ptr;
			    lvar_ptr = lvar_ptr->var_next) {

				if ((newlvar = var_lvar_alloc_local(
				    lvar_ptr->var_name)) != NULL) {

					add_lvar_to_list(newlvar,
					    &inner_flowop->fo_lvar_list);

					var_update_comp_lvars(newlvar,
					    proto_lvars,
					    comp_mstr_flow->fo_lvar_list);
				}
			}

			parser_inner_flowop_define(thread,
			    inner_flowtype,
			    inner_flowop);

			inner_flowtype = inner_flowtype->fo_exec_next;
			continue;
		}

		avd_update(&inner_flowop->fo_iosize,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_wss,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_iters,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_value,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_random,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_dsync,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_rotatefd,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_blocking,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_directio,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_highwater,
		    comp_mstr_flow->fo_lvar_list);

		inner_flowtype = inner_flowtype->fo_exec_next;
	}
}

/*
 * Calls flowop_define() to allocate a flowop with the supplied name.
 * The allocated flowop inherits attributes from a base flowop of the
 * same type.  If the new flowop has a file or fileset attribute specified,
 * it must specify a defined fileobj or fileset or an error will be logged.
 * The new flowop may  also have the following attributes set by
 * the program:
 *  - file size (fo_iosize)
 *  - working set size (fo_wss)
 *  - do random io (fo_random)
 *  - do synchronous io (fo_dsync)
 *  - perform each operation multiple times before advancing (fo_iter)
 *  - target name (fo_targetname)
 *  - An integer value (fo_value)
 *  - a file descriptor (fo_fd)
 *  - specify to rotate file descriptors (fo_rotatefd)
 *  - a source fd (fo_srcfdnumber)
 *  - specify a blocking operation (fo_blocking)
 *  - specify a highwater mark (fo_highwater)
 *
 * After all the supplied attributes are stored in their respective locations
 * in the flowop object, the flowop's init function is called. No errors are
 * returned, but the filebench run will be terminated if the flowtype is not
 * specified, a name for the new flowop is not supplied, the flowop_define
 * call fails, or a file or fileset name is supplied but the corresponding
 * fileobj or fileset cannot be located.
 */
static void
parser_flowop_define(cmd_t *cmd, threadflow_t *thread,
    flowop_t **flowoplist_hdp, int category)
{
	flowop_t *flowop, *flowop_type;
	char *type = (char *)cmd->cmd_name;
	char *name = NULL;
	attr_t *attr;

	/* Get the inherited flowop */
	flowop_type = flowop_find(type);
	if (flowop_type == NULL) {
		filebench_log(LOG_ERROR,
		    "define flowop: flowop type %s not found",
		    type);
		filebench_shutdown(1);
	}

	/* Get the name of the flowop */
	if ((attr = get_attr(cmd, FSA_NAME))) {
		name = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "define flowop: flowop %s specifies no name",
		    flowop_type->fo_name);
		filebench_shutdown(1);
	}

	if ((flowop = flowop_define(thread, name,
	    flowop_type, flowoplist_hdp, category, 0)) == NULL) {
		filebench_log(LOG_ERROR,
		    "define flowop: Failed to instantiate flowop %s\n",
		    cmd->cmd_name);
		filebench_shutdown(1);
	}

	/* Iterations */
	if ((attr = get_attr(cmd, FSA_ITERS)))
		flowop->fo_iters = attr->attr_avd;
	else
		flowop->fo_iters = avd_int_alloc(1);


	/* if this is a use of a composit flowop, create inner FLOW MASTERS */
	if (flowop_type->fo_type == FLOW_TYPE_COMPOSITE) {
		get_attr_lvars(cmd, flowop);
		if (category == FLOW_MASTER)
			parser_inner_flowop_define(thread,
			    flowop_type, flowop);
	}
	else {
		parser_flowop_get_attrs(cmd, flowop);
	}
}

static void
parser_composite_flowop_define(cmd_t *cmd)
{
	flowop_t *flowop;
	cmd_t *inner_cmd;
	char *name = NULL;
	attr_t *attr;

	/* Get the name of the flowop */
	if ((attr = get_attr(cmd, FSA_NAME))) {
		name = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "define flowop: Composit flowop specifies no name");

		filebench_shutdown(1);
	}

	if ((flowop = flowop_new_composite_define(name)) == NULL) {
		filebench_log(LOG_ERROR,
		    "define flowop: Failed to instantiate flowop %s\n",
		    cmd->cmd_name);
		filebench_shutdown(1);
	}

	/* place any local var_t variables on the flowop's local list */
	get_attr_lvars(cmd, flowop);

	/* Iterations */
	if ((attr = get_attr(cmd, FSA_ITERS)))
		flowop->fo_iters = attr->attr_avd;
	else
		flowop->fo_iters = avd_int_alloc(1);

	/* define inner flowops */
	for (inner_cmd = cmd->cmd_list; inner_cmd != NULL;
	    inner_cmd = inner_cmd->cmd_next) {
		parser_flowop_define(inner_cmd, NULL,
		    &flowop->fo_comp_fops, FLOW_INNER_DEF);
	}
}


/*
 * First, we verify that mandatory attributes - name and path - are specified.
 * Then allocate a fileset structure and setup its fields. Notice, at this
 * point we should not verify if AVD type makes sense, because AVD type can
 * change as variables are set to other values after fileset definition.
*/
static fileset_t *
parser_fileset_define_common(cmd_t *cmd)
{
	fileset_t *fileset;
	attr_t *attr;
	avd_t name;
	avd_t path;

	attr = get_attr(cmd, FSA_NAME);
	if (attr)
		name = attr->attr_avd;
	else {
		filebench_log(LOG_ERROR, "file[set] specifies no name");
		return NULL;
	}

	attr = get_attr(cmd, FSA_PATH);
	if (attr)
		path = attr->attr_avd;
	else {
		filebench_log(LOG_ERROR, "file[set] specifies no path");
		return NULL;
	}

	fileset = fileset_define(name, path);
	if (!fileset) {
		filebench_log(LOG_ERROR, "failed to instantiate file[set] %s\n",
		    		avd_get_str(name));
		return NULL;
	}

	attr = get_attr(cmd, FSA_PREALLOC);
	if (attr)
		fileset->fs_preallocpercent = attr->attr_avd;
	else
		fileset->fs_preallocpercent = avd_int_alloc(0);

	attr = get_attr(cmd, FSA_PARALLOC);
	if (attr)
		fileset->fs_paralloc = attr->attr_avd;
	else
		fileset->fs_paralloc = avd_bool_alloc(FALSE);

	attr = get_attr(cmd, FSA_READONLY);
	if (attr)
		fileset->fs_readonly = attr->attr_avd;
	else
		fileset->fs_readonly = avd_bool_alloc(FALSE);

	attr = get_attr(cmd, FSA_WRITEONLY);
	if (attr)
		fileset->fs_writeonly = attr->attr_avd;
	else
		fileset->fs_writeonly = avd_bool_alloc(FALSE);

	attr = get_attr(cmd, FSA_REUSE);
	if (attr)
		fileset->fs_reuse = attr->attr_avd;
	else
		fileset->fs_reuse = avd_bool_alloc(FALSE);

	/* Should we check for files actual existance? */
	attr = get_attr(cmd, FSA_TRUSTTREE);
	if (attr )
		fileset->fs_trust_tree = attr->attr_avd;
	else
		fileset->fs_trust_tree = avd_bool_alloc(FALSE);

	attr = get_attr(cmd, FSA_SIZE);
	if (attr)
		fileset->fs_size = attr->attr_avd;
	else
		fileset->fs_size = avd_int_alloc(1024);

	return fileset;
}

static void
parser_file_define(cmd_t *cmd)
{
	fileset_t *fileset;

	fileset = parser_fileset_define_common(cmd);
	if (!fileset) {
		filebench_log(LOG_ERROR, "failed to instantiate file");
		filebench_shutdown(1);
		return;
	}

	/* fileset is emulating a single file */
	fileset->fs_attrs = FILESET_IS_FILE;
	fileset->fs_entries = avd_int_alloc(1);
	/* Set the mean dir width to more than 1 */
	fileset->fs_dirwidth = avd_int_alloc(10);
	fileset->fs_dirgamma = avd_int_alloc(0);
	fileset->fs_leafdirs = avd_int_alloc(0);
}

static void
parser_fileset_define(cmd_t *cmd)
{
	fileset_t *fileset;
	attr_t *attr;

	fileset = parser_fileset_define_common(cmd);
	if (!fileset) {
		filebench_log(LOG_ERROR, "failed to instantiate fileset");
		filebench_shutdown(1);
		return;
	}

	attr = get_attr(cmd, FSA_ENTRIES);
	if (attr)
		fileset->fs_entries = attr->attr_avd;
	else
		fileset->fs_entries = avd_int_alloc(0);

	attr = get_attr(cmd, FSA_LEAFDIRS);
	if (attr)
		fileset->fs_leafdirs = attr->attr_avd;
	else
		fileset->fs_leafdirs = avd_int_alloc(0);

	attr = get_attr(cmd, FSA_DIRWIDTH);
	if (attr)
		fileset->fs_dirwidth = attr->attr_avd;
	else {
		filebench_log(LOG_ERROR, "Fileset has no directory width");
		fileset->fs_dirwidth = avd_int_alloc(0);
	}

	attr = get_attr(cmd, FSA_DIRDEPTHRV);
	if (attr)
		fileset->fs_dirdepthrv = attr->attr_avd;
	else
		fileset->fs_dirdepthrv = NULL;

	attr = get_attr(cmd, FSA_DIRGAMMA);
	if (attr)
		fileset->fs_dirgamma = attr->attr_avd;
	else
		fileset->fs_dirgamma = avd_int_alloc(1500);
}

/*
 * Calls fileset_createsets() to populate all filesets and create all
 * associated, initially existant,  files and subdirectories.
 * If errors are encountered, calls filebench_shutdown() to exit Filebench.
 */
static void
parser_fileset_create(cmd_t *cmd)
{
	int ret;

	ret = fileset_createsets(); 
	if (ret) {
		filebench_log(LOG_ERROR, "Failed to create filesets");
		filebench_shutdown(1);
	}
}

/*
 * Ends filebench run after first destoring any interprocess
 * shared memory. The call to filebench_shutdown()
 * also causes filebench to exit.
 */
static void
parser_filebench_shutdown(cmd_t *cmd)
{
	int f_abort = filebench_shm->shm_f_abort;

	ipc_fini();

	if (f_abort == FILEBENCH_ABORT_ERROR)
		filebench_shutdown(1);
	else
		filebench_shutdown(0);
}

/*
 * This is used for timing runs. Pauses the master thread in one second
 * intervals until the supplied ptime runs out or the f_abort flag
 * is raised. If given a time of zero, it will pause until f_abort is raised.
 */
static int
parser_pause(int ptime)
{
	int timeslept = 0;

	if (ptime) {
		while (timeslept < ptime) {
			(void) sleep(1);
			timeslept++;
			if (filebench_shm->shm_f_abort)
				break;
		}
	} else {
		/* initial runtime of 0 means run till abort */
		/* CONSTCOND */
		while (1) {
			(void) sleep(1);
			timeslept++;
			if (filebench_shm->shm_f_abort)
				break;
		}
	}

	return (timeslept);
}

#define TIMED_RUNTIME_DEFAULT 60 /* In seconds */
#define PERIOD_DEFAULT 10 /* In seconds */

/*
 * Do a file bench run. Calls routines to create file sets, files, and
 * processes. It resets the statistics counters, then sleeps for the runtime
 * passed as an argument to it on the command line in 1 second increments.
 * When it is finished sleeping, it collects a snapshot of the statistics
 * and ends the run.
 */
static void
parser_run(cmd_t *cmd)
{
	int runtime;
	int timeslept;

	runtime = cmd->cmd_qty;

	parser_fileset_create(cmd);
	proc_create();

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Running...");
	stats_clear();

	/* If it is a timed mode and timeout is not specified use default */
	if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT && !runtime)
		runtime = TIMED_RUNTIME_DEFAULT;

	timeslept = parser_pause(runtime);

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
	stats_snap();
	proc_shutdown();
	parser_filebench_shutdown((cmd_t *)0);
}

static void
parser_psrun(cmd_t *cmd)
{
	int runtime;
	int period;
	int timeslept = 0;
	int reset_stats = 0;

	runtime = cmd->cmd_qty;

	/*
	 * If period is negative then
	 * we want to reset statistics
	 * at the end of the every period
	 */
	if (cmd->cmd_qty1 < 0) {
		period = -cmd->cmd_qty1;
		reset_stats = 1;
	} else if (cmd->cmd_qty1 > 0) {
		period = cmd->cmd_qty1;
		reset_stats = 0;
	} else { /* (cmd->cmd_qty1) == 0 */
		period = PERIOD_DEFAULT;
		reset_stats = 0;
	}

	parser_fileset_create(cmd);
	proc_create();

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Running...");
	stats_clear();

	/* If it is a timed mode and timeout is not specified use default */
	if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT && !runtime)
		runtime = TIMED_RUNTIME_DEFAULT;

	while (1) {
		/* sleep the remaining time if a period is smaller */
		if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT)
			period = period > (runtime - timeslept) ?
						(runtime - timeslept) : period;

		timeslept += parser_pause(period);

		if (filebench_shm->shm_f_abort)
			break;

		if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT &&
							timeslept >= runtime)
			break;

		stats_snap();

		if (reset_stats)
			stats_clear();
	}

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
	stats_snap();
	proc_shutdown();
	parser_filebench_shutdown((cmd_t *)0);
}

/*
 * Similar to parser_run, but gets the sleep time from a variable
 * whose name is supplied as an argument to the command.
 */
static void
parser_run_variable(cmd_t *cmd)
{
	avd_t integer = avd_var_alloc(cmd->cmd_tgt1);
	int runtime;
	int timeslept;

	if (integer == NULL) {
		filebench_log(LOG_ERROR, "Unknown variable %s",
		cmd->cmd_tgt1);
		return;
	}

	runtime = avd_get_int(integer);

	parser_fileset_create(cmd);
	proc_create();

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Running...");
	stats_clear();

	/* If it is a timed mode and timeout is not specified use default */
	if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT && !runtime)
		runtime = TIMED_RUNTIME_DEFAULT;

	timeslept = parser_pause(runtime);

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
	stats_snap();
	proc_shutdown();
	parser_filebench_shutdown((cmd_t *)0);
}

/*
 * Establishes multi-client synchronization socket with synch server.
 */
static void
parser_enable_mc(cmd_t *cmd)
{
	attr_t *attr;
	char *master;
	char *client;

	if ((attr = get_attr(cmd, FSA_MASTER))) {
		master = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "enable multi: no master specified");
		return;
	}

	if ((attr = get_attr(cmd, FSA_CLIENT))) {
		client = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "enable multi: no client specified");
		return;
	}

	mc_sync_open_sock(master, 8001, client);
}

/*
 * Exchanges multi-client synchronization message with synch server.
 */
static void
parser_domultisync(cmd_t *cmd)
{
	attr_t *attr;
	fbint_t value;

	if ((attr = get_attr(cmd, FSA_VALUE)))
		value = avd_get_int(attr->attr_avd);
	else
		value = 1;

	mc_sync_synchronize((int)value);
}

/*
 * Sleeps for cmd->cmd_qty seconds, one second at a time.
 */
static void
parser_sleep(cmd_t *cmd)
{
	int sleeptime;
	int timeslept;

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	sleeptime = cmd->cmd_qty;
	filebench_log(LOG_INFO, "Sleeping...");

	timeslept = parser_pause(sleeptime);

	filebench_log(LOG_INFO, "Slept for %d seconds...", timeslept);
}

/*
 * Same as parser_sleep, except the sleep time is obtained from a variable
 * whose name is passed to it as an argument on the command line.
 */
static void
parser_sleep_variable(cmd_t *cmd)
{
	avd_t integer = avd_var_alloc(cmd->cmd_tgt1);
	int sleeptime;
	int timeslept;

	if (integer == NULL) {
		filebench_log(LOG_ERROR, "Unknown variable %s",
		cmd->cmd_tgt1);
		return;
	}

	sleeptime = avd_get_int(integer);

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Running...");

	timeslept = parser_pause(sleeptime);

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
}

/*
 * Launches a shell to run the unix command supplied in the argument.
 * The command should be enclosed in quotes, as in:
 * 	system "rm xyz"
 * which would run the "rm" utility to delete the file "xyz".
 */
static void
parser_system(cmd_t *cmd)
{
	char *string;

	if (!cmd->cmd_param_list)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (!string)
		return;

	filebench_log(LOG_VERBOSE, "Running '%s'", string);

	if (system(string) < 0) {
		filebench_log(LOG_ERROR,
		    "system exec failed: %s",
		    strerror(errno));
		free(string);
		filebench_shutdown(1);
	}

	free(string);
}

/*
 * Echos string supplied with command to the log.
 */
static void
parser_echo(cmd_t *cmd)
{
	char *string;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_INFO, "%s", string);
}

/*
 * Prints out the version of Filebench.
 */
static void
parser_version(cmd_t *cmd)
{
	filebench_log(LOG_INFO, "Filebench Version: %s", FILEBENCH_VERSION);
}

static void
parser_enable_lathist(cmd_t *cmd)
{
	filebench_shm->lathist_enabled = 1;
	filebench_log(LOG_INFO, "Latency histogram enabled");
}

/*
 * define a random variable and initialize the distribution parameters
 */
static void
parser_var_assign_random(char *name, cmd_t *cmd)
{
	randdist_t	*rndp;
	attr_t		*attr;

	rndp = randdist_alloc();
	if (!rndp) {
		filebench_log(LOG_ERROR,
			"failed to alloc random distribution object\n");
		return;
	}

	rndp->rnd_type = 0;

	/* Get the source of the random numbers */
	if ((attr = get_attr(cmd, FSA_RANDSRC))) {
		int randsrc = (int)avd_get_int(attr->attr_avd);

		switch (randsrc) {
		case FSV_URAND:
			rndp->rnd_type |= RAND_SRC_URANDOM;
			break;
		case FSV_RAND48:
			rndp->rnd_type |= RAND_SRC_GENERATOR;
			break;
		}
	} else {
		/* default to rand48 random number generator */
		rndp->rnd_type |= RAND_SRC_GENERATOR;
	}

	/* Get the min value of the random distribution */
	if ((attr = get_attr(cmd, FSA_MIN)))
		rndp->rnd_min = attr->attr_avd;
	else
		rndp->rnd_min = avd_int_alloc(0);

	/* Get the roundoff value for the random distribution */
	if ((attr = get_attr(cmd, FSA_ROUND)))
		rndp->rnd_round = attr->attr_avd;
	else
		rndp->rnd_round = avd_int_alloc(0);

	/* Get a tablular probablility distribution if there is one */
	if ((attr = get_attr(cmd, FSA_RANDTABLE))) {
		rndp->rnd_probtabs = (probtabent_t *)(attr->attr_obj);
		rndp->rnd_type |= RAND_TYPE_TABLE;

		/* no need for the rest of the attributes */
		goto randdist_init;
	} else {
		rndp->rnd_probtabs = NULL;
	}

	/* Get the type for the random variable */
	if ((attr = get_attr(cmd, FSA_TYPE))) {
		int disttype = (int)avd_get_int(attr->attr_avd);

		switch (disttype) {
		case FSV_RANDUNI:
			rndp->rnd_type |= RAND_TYPE_UNIFORM;
			break;
		case FSA_RANDGAMMA:
			rndp->rnd_type |= RAND_TYPE_GAMMA;
			break;
		case FSV_RANDTAB:
			filebench_log(LOG_ERROR,
			    "Table distribution type without prob table");
			break;
		}
	} else {
		/* default to gamma distribution type */
		rndp->rnd_type |= RAND_TYPE_GAMMA;
	}

	/* Get the seed for the random variable */
	if ((attr = get_attr(cmd, FSA_RANDSEED)))
		rndp->rnd_seed = attr->attr_avd;
	else
		rndp->rnd_seed = avd_int_alloc(0);

	/* Get the gamma value of the random distribution */
	if ((attr = get_attr(cmd, FSA_RANDGAMMA)))
		rndp->rnd_gamma = attr->attr_avd;
	else
		rndp->rnd_gamma = avd_int_alloc(1500);

	/* Get the mean value of the random distribution */
	if ((attr = get_attr(cmd, FSA_RANDMEAN))) {
		rndp->rnd_mean = attr->attr_avd;
	} else if ((rndp->rnd_type & RAND_TYPE_MASK) == RAND_TYPE_GAMMA) {
		rndp->rnd_mean = NULL;
	} else {
		rndp->rnd_mean = avd_int_alloc(0);
	}

	var_assign_random(name, rndp);

randdist_init:
	randdist_init(rndp);
}

/*
 * alloc_cmd() allocates the required resources for a cmd_t. On failure, a
 * filebench_log is issued and NULL is returned.
 */
static cmd_t *
alloc_cmd(void)
{
	cmd_t *cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd) {
		filebench_log(LOG_ERROR, "Alloc cmd failed");
		return NULL;
	}

	memset(cmd, 0, sizeof (cmd_t));

	return cmd;
}

/*
 * Allocates an attr_t structure and zeros it. Returns NULL on failure, or
 * a pointer to the attr_t.
 */
static attr_t *
alloc_attr(void)
{
	attr_t *attr;

	attr = malloc(sizeof(*attr));
	if (!attr)
		return (NULL);

	(void) memset(attr, 0, sizeof(*attr));

	return (attr);
}

/*
 * Allocates a probtabent_t structure and zeros it. Returns NULL on failure, or
 * a pointer to the probtabent_t.
 */
static probtabent_t *
alloc_probtabent(void)
{
	probtabent_t *rte;

	if ((rte = malloc(sizeof (probtabent_t))) == NULL) {
		return (NULL);
	}

	(void) memset(rte, 0, sizeof (probtabent_t));
	return (rte);
}

/*
 * Allocates an attr_t structure and puts the supplied var_t into
 * its attr_avd location, and sets its name to FSA_LVAR_ASSIGN
 */
static attr_t *
alloc_lvar_attr(var_t *var)
{
	attr_t *attr;

	if ((attr = alloc_attr()) == NULL)
		return (NULL);

	attr->attr_name = FSA_LVAR_ASSIGN;
	attr->attr_avd = (avd_t)var;

	return (attr);
}

/*
 * Searches the attribute list for the command for the named attribute type.
 * The attribute list is created by the parser from the list of attributes
 * supplied with certain commands, such as the define and flowop commands.
 * Returns a pointer to the attribute structure if the named attribute is
 * found, otherwise returns NULL. If the attribute includes a parameter list,
 * the list is converted to a string and stored in the attr_avd field of
 * the returned attr_t struct.
 */
static attr_t *
get_attr(cmd_t *cmd, int64_t name)
{
	attr_t *attr;
	attr_t *rtn = NULL;

	for (attr = cmd->cmd_attr_list; attr != NULL;
	    attr = attr->attr_next) {

		filebench_log(LOG_DEBUG_IMPL,
		    "attr %d = %d %llx?",
		    attr->attr_name,
		    name,
		    attr->attr_avd);

		if (attr->attr_name == name)
			rtn = attr;
	}

	return rtn;
}

/*
 * removes the newly allocated local var from the shared local var
 * list, then puts it at the head of the private local var list
 * supplied as the second argument.
 */
static void
add_lvar_to_list(var_t *newlvar, var_t **lvar_list)
{
	var_t *prev;

	/* remove from shared local list, if there */
	if (newlvar == filebench_shm->shm_var_loc_list) {
		/* on top of list, just grap */
		filebench_shm->shm_var_loc_list = newlvar->var_next;
	} else {
		/* find newvar on list and remove */
		for (prev = filebench_shm->shm_var_loc_list; prev;
		    prev = prev->var_next) {
			if (prev->var_next == newlvar)
				prev->var_next = newlvar->var_next;
		}
	}
	newlvar->var_next = NULL;

	/* add to flowop private local list at head */
	newlvar->var_next = *lvar_list;
	*lvar_list = newlvar;
}

/*
 * Searches the attribute list for the command for any allocated local
 * variables. The attribute list is created by the parser from the list of
 * attributes supplied with certain commands, such as the define and flowop
 * commands. Places all found local vars onto the flowop's local variable
 * list.
 */
static void
get_attr_lvars(cmd_t *cmd, flowop_t *flowop)
{
	attr_t *attr;
	var_t *orig_lvar_list;

	/* save the local var list */
	orig_lvar_list = flowop->fo_lvar_list;

	for (attr = cmd->cmd_attr_list; attr != NULL;
	    attr = attr->attr_next) {

		if (attr->attr_name == FSA_LVAR_ASSIGN) {
			var_t *newvar;

			if ((newvar = (var_t *)attr->attr_avd) == NULL)
				continue;

			add_lvar_to_list(newvar, &flowop->fo_lvar_list);
			var_update_comp_lvars(newvar, orig_lvar_list, NULL);
		}
	}
}

/*
 * Allocates memory for a list_t structure, initializes it to zero, and
 * returns a pointer to it. On failure, returns NULL.
 */
static list_t *
alloc_list()
{
	list_t *list;

	if ((list = malloc(sizeof (list_t))) == NULL) {
		return (NULL);
	}

	(void) memset(list, 0, sizeof (list_t));
	return (list);
}

/*
 * Define a custom variable and validate its parameters.
 * TODO: Clean up state when things go wrong.
 */
static void
parser_var_assign_custom(char *name, cmd_t *cmd)
{
	cvar_t	*cvar;
	attr_t	*attr;
	char	*type;
	char	*parameters;
	int 	ret;

	attr = get_attr(cmd, FSA_TYPE);
	if (attr)
		type = avd_get_str(attr->attr_avd);
	else {
		filebench_log(LOG_ERROR, "define cvar: no type specified");
		filebench_shutdown(1);
		return;
	}

	cvar = cvar_alloc();
	if (!cvar) {
		filebench_log(LOG_ERROR, "Failed to allocate custom variable");
		filebench_shutdown(1);
		return;
	}

	/* Initialize the custom variable mutex. */
	(void) pthread_mutex_init(&cvar->cvar_lock,
			ipc_mutexattr(IPC_MUTEX_NORMAL));

	/* Get the min, max and round values for the custom variable. */
	if ((attr = get_attr(cmd, FSA_MIN)))
		cvar->min = avd_get_dbl(attr->attr_avd);
	else
		cvar->min = DBL_MIN;

	if ((attr = get_attr(cmd, FSA_MAX)))
		cvar->max = avd_get_dbl(attr->attr_avd);
	else
		cvar->max = DBL_MAX;

	if ((attr = get_attr(cmd, FSA_ROUND)))
		cvar->round = avd_get_dbl(attr->attr_avd);
	else
		cvar->round = 0;

	attr = get_attr(cmd, FSA_PARAMETERS);
	if (attr)
		parameters = avd_get_str(attr->attr_avd);
	else
		parameters = NULL;

	ret = init_cvar_handle(cvar, type, parameters);
	if (ret) {
		filebench_log(LOG_FATAL, "define cvar: failed for custom variable %s",
		    name);
		filebench_shutdown(1);
		return;
	}

	var_assign_custom(name, cvar);
}
