
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FSC_LIST = 258,
     FSC_DEFINE = 259,
     FSC_QUIT = 260,
     FSC_DEBUG = 261,
     FSC_CREATE = 262,
     FSC_SLEEP = 263,
     FSC_STATS = 264,
     FSC_FOREACH = 265,
     FSC_SET = 266,
     FSC_SHUTDOWN = 267,
     FSC_LOG = 268,
     FSC_SYSTEM = 269,
     FSC_FLOWOP = 270,
     FSC_EVENTGEN = 271,
     FSC_ECHO = 272,
     FSC_RUN = 273,
     FSC_PSRUN = 274,
     FSC_WARMUP = 275,
     FSC_NOUSESTATS = 276,
     FSC_FSCHECK = 277,
     FSC_FSFLUSH = 278,
     FSC_USAGE = 279,
     FSC_HELP = 280,
     FSC_VERSION = 281,
     FSC_ENABLE = 282,
     FSC_DOMULTISYNC = 283,
     FSV_STRING = 284,
     FSV_VAL_INT = 285,
     FSV_VAL_NEGINT = 286,
     FSV_VAL_BOOLEAN = 287,
     FSV_VARIABLE = 288,
     FSV_WHITESTRING = 289,
     FSV_RANDUNI = 290,
     FSV_RANDTAB = 291,
     FSV_URAND = 292,
     FSV_RAND48 = 293,
     FSE_FILE = 294,
     FSE_PROC = 295,
     FSE_THREAD = 296,
     FSE_CLEAR = 297,
     FSE_SNAP = 298,
     FSE_DUMP = 299,
     FSE_DIRECTORY = 300,
     FSE_COMMAND = 301,
     FSE_FILESET = 302,
     FSE_XMLDUMP = 303,
     FSE_RAND = 304,
     FSE_MODE = 305,
     FSE_MULTI = 306,
     FSE_MULTIDUMP = 307,
     FSK_SEPLST = 308,
     FSK_OPENLST = 309,
     FSK_CLOSELST = 310,
     FSK_OPENPAR = 311,
     FSK_CLOSEPAR = 312,
     FSK_ASSIGN = 313,
     FSK_IN = 314,
     FSK_QUOTE = 315,
     FSA_SIZE = 316,
     FSA_PREALLOC = 317,
     FSA_PARALLOC = 318,
     FSA_PATH = 319,
     FSA_REUSE = 320,
     FSA_PROCESS = 321,
     FSA_MEMSIZE = 322,
     FSA_RATE = 323,
     FSA_CACHED = 324,
     FSA_READONLY = 325,
     FSA_TRUSTTREE = 326,
     FSA_IOSIZE = 327,
     FSA_FILE = 328,
     FSA_WSS = 329,
     FSA_NAME = 330,
     FSA_RANDOM = 331,
     FSA_INSTANCES = 332,
     FSA_DSYNC = 333,
     FSA_TARGET = 334,
     FSA_ITERS = 335,
     FSA_NICE = 336,
     FSA_VALUE = 337,
     FSA_BLOCKING = 338,
     FSA_HIGHWATER = 339,
     FSA_DIRECTIO = 340,
     FSA_DIRWIDTH = 341,
     FSA_FD = 342,
     FSA_SRCFD = 343,
     FSA_ROTATEFD = 344,
     FSA_ENTRIES = 345,
     FSA_DIRDEPTHRV = 346,
     FSA_DIRGAMMA = 347,
     FSA_USEISM = 348,
     FSA_TYPE = 349,
     FSA_RANDTABLE = 350,
     FSA_RANDSRC = 351,
     FSA_ROUND = 352,
     FSA_LEAFDIRS = 353,
     FSA_INDEXED = 354,
     FSA_FSTYPE = 355,
     FSA_RANDSEED = 356,
     FSA_RANDGAMMA = 357,
     FSA_RANDMEAN = 358,
     FSA_MIN = 359,
     FSA_MAX = 360,
     FSA_MASTER = 361,
     FSA_CLIENT = 362,
     FSS_TYPE = 363,
     FSS_SEED = 364,
     FSS_GAMMA = 365,
     FSS_MEAN = 366,
     FSS_MIN = 367,
     FSS_SRC = 368,
     FSS_ROUND = 369,
     FSA_LVAR_ASSIGN = 370,
     FSA_ALLDONE = 371,
     FSA_FIRSTDONE = 372,
     FSA_TIMEOUT = 373,
     FSC_OSPROF_ENABLE = 374,
     FSC_OSPROF_DISABLE = 375,
     FSA_NOREADAHEAD = 376,
     FSA_IOPRIO = 377,
     FSA_WRITEONLY = 378,
     FSE_CVAR = 379,
     FSA_PARAMETERS = 380
   };
#endif
/* Tokens.  */
#define FSC_LIST 258
#define FSC_DEFINE 259
#define FSC_QUIT 260
#define FSC_DEBUG 261
#define FSC_CREATE 262
#define FSC_SLEEP 263
#define FSC_STATS 264
#define FSC_FOREACH 265
#define FSC_SET 266
#define FSC_SHUTDOWN 267
#define FSC_LOG 268
#define FSC_SYSTEM 269
#define FSC_FLOWOP 270
#define FSC_EVENTGEN 271
#define FSC_ECHO 272
#define FSC_RUN 273
#define FSC_PSRUN 274
#define FSC_WARMUP 275
#define FSC_NOUSESTATS 276
#define FSC_FSCHECK 277
#define FSC_FSFLUSH 278
#define FSC_USAGE 279
#define FSC_HELP 280
#define FSC_VERSION 281
#define FSC_ENABLE 282
#define FSC_DOMULTISYNC 283
#define FSV_STRING 284
#define FSV_VAL_INT 285
#define FSV_VAL_NEGINT 286
#define FSV_VAL_BOOLEAN 287
#define FSV_VARIABLE 288
#define FSV_WHITESTRING 289
#define FSV_RANDUNI 290
#define FSV_RANDTAB 291
#define FSV_URAND 292
#define FSV_RAND48 293
#define FSE_FILE 294
#define FSE_PROC 295
#define FSE_THREAD 296
#define FSE_CLEAR 297
#define FSE_SNAP 298
#define FSE_DUMP 299
#define FSE_DIRECTORY 300
#define FSE_COMMAND 301
#define FSE_FILESET 302
#define FSE_XMLDUMP 303
#define FSE_RAND 304
#define FSE_MODE 305
#define FSE_MULTI 306
#define FSE_MULTIDUMP 307
#define FSK_SEPLST 308
#define FSK_OPENLST 309
#define FSK_CLOSELST 310
#define FSK_OPENPAR 311
#define FSK_CLOSEPAR 312
#define FSK_ASSIGN 313
#define FSK_IN 314
#define FSK_QUOTE 315
#define FSA_SIZE 316
#define FSA_PREALLOC 317
#define FSA_PARALLOC 318
#define FSA_PATH 319
#define FSA_REUSE 320
#define FSA_PROCESS 321
#define FSA_MEMSIZE 322
#define FSA_RATE 323
#define FSA_CACHED 324
#define FSA_READONLY 325
#define FSA_TRUSTTREE 326
#define FSA_IOSIZE 327
#define FSA_FILE 328
#define FSA_WSS 329
#define FSA_NAME 330
#define FSA_RANDOM 331
#define FSA_INSTANCES 332
#define FSA_DSYNC 333
#define FSA_TARGET 334
#define FSA_ITERS 335
#define FSA_NICE 336
#define FSA_VALUE 337
#define FSA_BLOCKING 338
#define FSA_HIGHWATER 339
#define FSA_DIRECTIO 340
#define FSA_DIRWIDTH 341
#define FSA_FD 342
#define FSA_SRCFD 343
#define FSA_ROTATEFD 344
#define FSA_ENTRIES 345
#define FSA_DIRDEPTHRV 346
#define FSA_DIRGAMMA 347
#define FSA_USEISM 348
#define FSA_TYPE 349
#define FSA_RANDTABLE 350
#define FSA_RANDSRC 351
#define FSA_ROUND 352
#define FSA_LEAFDIRS 353
#define FSA_INDEXED 354
#define FSA_FSTYPE 355
#define FSA_RANDSEED 356
#define FSA_RANDGAMMA 357
#define FSA_RANDMEAN 358
#define FSA_MIN 359
#define FSA_MAX 360
#define FSA_MASTER 361
#define FSA_CLIENT 362
#define FSS_TYPE 363
#define FSS_SEED 364
#define FSS_GAMMA 365
#define FSS_MEAN 366
#define FSS_MIN 367
#define FSS_SRC 368
#define FSS_ROUND 369
#define FSA_LVAR_ASSIGN 370
#define FSA_ALLDONE 371
#define FSA_FIRSTDONE 372
#define FSA_TIMEOUT 373
#define FSC_OSPROF_ENABLE 374
#define FSC_OSPROF_DISABLE 375
#define FSA_NOREADAHEAD 376
#define FSA_IOPRIO 377
#define FSA_WRITEONLY 378
#define FSE_CVAR 379
#define FSA_PARAMETERS 380




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 154 "parser_gram.y"

	int64_t		 ival;
	unsigned char	 bval;
	char *		 sval;
	fs_u		 val;
	avd_t		 avd;
	cmd_t		*cmd;
	attr_t		*attr;
	list_t		*list;
	probtabent_t	*rndtb;



/* Line 1676 of yacc.c  */
#line 316 "parser_gram.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


