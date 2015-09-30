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

%option nounput
%option noyywrap

%{

#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

#include "filebench.h"
#include "parsertypes.h"
#include "utils.h"
#include "parser_gram.h"

int lex_lineno = 1;		/* line-number for error reporting */
extern void yyerror(char *s);
%}

%s WHITESTRINGSTATE

%a 50000
%p 50000
%o 50000
%n 5000

%%

\n			{ lex_lineno++; }

<INITIAL>[ \t]+			;

<INITIAL>#.*			;

create                  { return FSC_CREATE; }
define			{ return FSC_DEFINE; }
debug                   { return FSC_DEBUG; }
domultisync		{ return FSC_DOMULTISYNC; }
echo                    { return FSC_ECHO; }
enable			{ return FSC_ENABLE; }
eventgen                { return FSC_EVENTGEN; }
quit		        { return FSC_QUIT; }
list		        { return FSC_LIST; }
run                     { return FSC_RUN; }
psrun                   { return FSC_PSRUN; }
set                     { return FSC_SET; }
sleep                   { return FSC_SLEEP; }
system                  { return FSC_SYSTEM; }
version                 { return FSC_VERSION; }

file       	        { return FSE_FILE; }
files       	        { return FSE_FILES; }
fileset[s]*             { return FSE_FILESET; }
process[es]*	        { return FSE_PROC; }
thread		        { return FSE_THREAD; }
flowop		        { return FSE_FLOWOP; }
randvar		        { return FSE_RAND; }
mode                    { return FSE_MODE; }
multi			{ return FSE_MULTI; }
cvar                    { return FSE_CVAR; }

alldone                 { return FSA_ALLDONE; }
blocking                { return FSA_BLOCKING; }
client			{ return FSA_CLIENT; }
dirwidth                { return FSA_DIRWIDTH; }
dirdepthrv              { return FSA_DIRDEPTHRV; }
directio                { return FSA_DIRECTIO; }
dirgamma                { return FSA_DIRGAMMA; }
dsync                   { return FSA_DSYNC;  }
entries                 { return FSA_ENTRIES;}
fd                      { return FSA_FD; }
filename                { return FSA_FILENAME; }
filesetname             { return FSA_FILENAME; }
filesize                { return FSA_SIZE; }
firstdone               { return FSA_FIRSTDONE; }
gamma                   { return FSA_RANDGAMMA; }
highwater               { return FSA_HIGHWATER; }
indexed                 { return FSA_INDEXED; }
instances               { return FSA_INSTANCES;}                  
iosize                  { return FSA_IOSIZE; }
iters                   { return FSA_ITERS;}
leafdirs                { return FSA_LEAFDIRS;}
master			{ return FSA_MASTER; }
mean                    { return FSA_RANDMEAN; }
memsize                 { return FSA_MEMSIZE; }
ioprio                  { return FSA_IOPRIO; }
min                     { return FSA_MIN; }
max                     { return FSA_MAX; }
name                    { return FSA_NAME;}
nice                    { return FSA_NICE;}
opennext                { return FSA_ROTATEFD; }
paralloc                { return FSA_PARALLOC; }
parameters              { return FSA_PARAMETERS; }
path                    { return FSA_PATH; }
prealloc                { return FSA_PREALLOC; }
random                  { return FSA_RANDOM;}
randsrc			{ return FSA_RANDSRC; }
randtable		{ return FSA_RANDTABLE; }
rate                    { return FSA_RATE;}
readonly		{ return FSA_READONLY; }
writeonly		{ return FSA_WRITEONLY; }
reuse                   { return FSA_REUSE; }
round			{ return FSA_ROUND; }
seed			{ return FSA_RANDSEED; }
size                    { return FSA_SIZE; }
srcfd                   { return FSA_SRCFD; }
target                  { return FSA_TARGET;}
timeout                 { return FSA_TIMEOUT; }
trusttree		{ return FSA_TRUSTTREE; }
type			{ return FSA_TYPE; }
useism                  { return FSA_USEISM;}
value                   { return FSA_VALUE;}
workingset              { return FSA_WSS; }
nousestats		{ return FSA_NOUSESTATS; }
lathist			{ return FSA_LATHIST; }

uniform                 { return FSV_RANDUNI; }
tabular			{ return FSV_RANDTAB; }
urandom			{ return FSV_URAND; }
rand48			{ return FSV_RAND48; }
noreadahead             { return FSA_NOREADAHEAD; }


<INITIAL>\"			{ 
                                BEGIN WHITESTRINGSTATE;
                                return FSK_QUOTE;
                        }

<WHITESTRINGSTATE>\"    {
                                BEGIN INITIAL;
                                return FSK_QUOTE;
                        }

<WHITESTRINGSTATE>[^$^\\^"][^$^"]*[^\\^$^"] {
				if ((yylval.sval = strdup(yytext)) == NULL) {
					yyerror("Out of memory");
					filebench_shutdown(1);
				}
 				return FSV_WHITESTRING;
	       	}

<WHITESTRINGSTATE>\\n	{
				yylval.sval = "\n";
 				return FSV_WHITESTRING;
	       	}


<WHITESTRINGSTATE>\\$[^"^$^\\]+	{
				if ((yylval.sval = strdup(yytext + 1)) == NULL) {
					yyerror("Out of memory");
					filebench_shutdown(1);
				}
 				return FSV_WHITESTRING;
	       	}

<WHITESTRINGSTATE>[^$^\\^"] {
				if ((yylval.sval = strdup(yytext)) == NULL) {
					yyerror("Out of memory");
					filebench_shutdown(1);
				}
 				return FSV_WHITESTRING;
	       	}


<INITIAL>\{			{ return FSK_OPENLST; }
<INITIAL>\}			{ return FSK_CLOSELST; }
<INITIAL>\(			{ return FSK_OPENPAR; }
<INITIAL>\)			{ return FSK_CLOSEPAR; }
<INITIAL>=			{ return FSK_ASSIGN; }
<INITIAL>\,			{ return FSK_SEPLST; }
<INITIAL>in                     { return FSK_IN; }

<INITIAL>[0-9]+	{
                                errno = 0;
				yylval.ival = strtoll(yytext, NULL, 10);
				if (errno == EINVAL || errno == ERANGE) {
                                        (void) filebench_log(LOG_ERROR, 
						"Invalid I value '%s':%s", yytext,
						strerror(errno));
				}
                                return FSV_VAL_POSINT;
}

<INITIAL>-[0-9]+	{
                                errno = 0;
				yylval.ival = strtoll(yytext, NULL, 10);
				if (errno == EINVAL || errno == ERANGE) {
                                        (void) filebench_log(LOG_ERROR, 
						"Invalid I value '%s':%s", yytext,
						strerror(errno));
				}
                                return FSV_VAL_NEGINT;
}

<INITIAL>[0-9]+k	{
                                errno = 0;
				yylval.ival = KB * strtoll(yytext, NULL, 10);
				if (errno == EINVAL || errno == ERANGE) {
                                        (void) filebench_log(LOG_ERROR, 
						"Invalid I value '%s':%s", yytext,
						strerror(errno));
				}
                                return FSV_VAL_POSINT;
}

<INITIAL>[0-9]+m	{
                                errno = 0;
				yylval.ival = MB * strtoll(yytext, NULL, 10);
				if (errno == EINVAL || errno == ERANGE) {
                                        (void) filebench_log(LOG_ERROR, 
						"Invalid I value '%s':%s", yytext,
						strerror(errno));
				}
                                return FSV_VAL_POSINT;
}

<INITIAL>[0-9]+g	{
                                errno = 0;
				yylval.ival = GB * strtoll(yytext, NULL, 10);
				if (errno == EINVAL || errno == ERANGE) {
                                        (void) filebench_log(LOG_ERROR, 
						"Invalid I value '%s':%s", yytext,
						strerror(errno));
				}
                                return FSV_VAL_POSINT;
}

<INITIAL>true	{
				yylval.bval = TRUE;
				return FSV_VAL_BOOLEAN;
		}

<INITIAL>false	{
				yylval.bval = FALSE;
				return FSV_VAL_BOOLEAN;
		}

$[({A-Za-z][A-Za-z0-9_]*[A-Za-z0-9][)}]*	{
				if ((yylval.sval = strdup(yytext)) == NULL) {
					yyerror("Out of memory");
					filebench_shutdown(1);
				}

 				return FSV_VARIABLE;
			}

<INITIAL>[/A-Za-z-][/A-Za-z0-9._:;-]*	{
				if ((yylval.sval = strdup(yytext)) == NULL) {
					yyerror("Out of memory");
					filebench_shutdown(1);
				}
 				return FSV_STRING;
			}


.			{
				yyerror("Illegal character");
			}

%%

void
yyerror(char *s)
{
	if (yytext[0] == '\0') {
		(void)filebench_log(LOG_ERROR, "%s, token expected", s);
		return;
	}

	(void)filebench_log(LOG_ERROR, "%s at '%s'", s, yytext);
}

struct yy_buffer_state *parent;
struct yy_buffer_state *script;

int
yy_switchfileparent(FILE *file)
{
	script = YY_CURRENT_BUFFER;
	parent = (struct yy_buffer_state *)yy_create_buffer(yyin, 128);
	yy_switch_to_buffer(parent);
	return (0);
}

int
yy_switchfilescript(FILE *file)
{
	yy_switch_to_buffer(script);
	return (0);
}

