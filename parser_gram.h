
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
     FSC_EXEC = 260,
     FSC_QUIT = 261,
     FSC_DEBUG = 262,
     FSC_CREATE = 263,
     FSC_SLEEP = 264,
     FSC_STATS = 265,
     FSC_FOREACH = 266,
     FSC_SET = 267,
     FSC_SHUTDOWN = 268,
     FSC_LOG = 269,
     FSC_SYSTEM = 270,
     FSC_FLOWOP = 271,
     FSC_EVENTGEN = 272,
     FSC_ECHO = 273,
     FSC_LOAD = 274,
     FSC_RUN = 275,
     FSC_PSRUN = 276,
     FSC_WARMUP = 277,
     FSC_NOUSESTATS = 278,
     FSC_FSCHECK = 279,
     FSC_FSFLUSH = 280,
     FSC_USAGE = 281,
     FSC_HELP = 282,
     FSC_VARS = 283,
     FSC_VERSION = 284,
     FSC_ENABLE = 285,
     FSC_DOMULTISYNC = 286,
     FSV_STRING = 287,
     FSV_VAL_INT = 288,
     FSV_VAL_NEGINT = 289,
     FSV_VAL_BOOLEAN = 290,
     FSV_VARIABLE = 291,
     FSV_WHITESTRING = 292,
     FSV_RANDUNI = 293,
     FSV_RANDTAB = 294,
     FSV_RANDVAR = 295,
     FSV_URAND = 296,
     FSV_RAND48 = 297,
     FST_INT = 298,
     FST_BOOLEAN = 299,
     FSE_FILE = 300,
     FSE_PROC = 301,
     FSE_THREAD = 302,
     FSE_CLEAR = 303,
     FSE_ALL = 304,
     FSE_SNAP = 305,
     FSE_DUMP = 306,
     FSE_DIRECTORY = 307,
     FSE_COMMAND = 308,
     FSE_FILESET = 309,
     FSE_POSSET = 310,
     FSE_XMLDUMP = 311,
     FSE_RAND = 312,
     FSE_MODE = 313,
     FSE_MULTI = 314,
     FSE_MULTIDUMP = 315,
     FSK_SEPLST = 316,
     FSK_OPENLST = 317,
     FSK_CLOSELST = 318,
     FSK_ASSIGN = 319,
     FSK_IN = 320,
     FSK_QUOTE = 321,
     FSK_DIRSEPLST = 322,
     FSK_PLUS = 323,
     FSK_MINUS = 324,
     FSK_MULTIPLY = 325,
     FSK_DIVIDE = 326,
     FSA_SIZE = 327,
     FSA_PREALLOC = 328,
     FSA_PARALLOC = 329,
     FSA_PATH = 330,
     FSA_REUSE = 331,
     FSA_PROCESS = 332,
     FSA_MEMSIZE = 333,
     FSA_RATE = 334,
     FSA_CACHED = 335,
     FSA_READONLY = 336,
     FSA_TRUSTTREE = 337,
     FSA_IOSIZE = 338,
     FSA_FILE = 339,
     FSA_POSSET = 340,
     FSA_WSS = 341,
     FSA_NAME = 342,
     FSA_RANDOM = 343,
     FSA_INSTANCES = 344,
     FSA_DSYNC = 345,
     FSA_TARGET = 346,
     FSA_ITERS = 347,
     FSA_NICE = 348,
     FSA_VALUE = 349,
     FSA_BLOCKING = 350,
     FSA_HIGHWATER = 351,
     FSA_DIRECTIO = 352,
     FSA_DIRWIDTH = 353,
     FSA_FD = 354,
     FSA_SRCFD = 355,
     FSA_ROTATEFD = 356,
     FSA_NAMELENGTH = 357,
     FSA_FILESIZE = 358,
     FSA_ENTRIES = 359,
     FSA_FILESIZEGAMMA = 360,
     FSA_DIRDEPTHRV = 361,
     FSA_DIRGAMMA = 362,
     FSA_USEISM = 363,
     FSA_TYPE = 364,
     FSA_RANDTABLE = 365,
     FSA_RANDSRC = 366,
     FSA_RANDROUND = 367,
     FSA_LEAFDIRS = 368,
     FSA_INDEXED = 369,
     FSA_FSTYPE = 370,
     FSA_RANDSEED = 371,
     FSA_RANDGAMMA = 372,
     FSA_RANDMEAN = 373,
     FSA_RANDMIN = 374,
     FSA_RANDMAX = 375,
     FSA_MASTER = 376,
     FSA_CLIENT = 377,
     FSS_TYPE = 378,
     FSS_SEED = 379,
     FSS_GAMMA = 380,
     FSS_MEAN = 381,
     FSS_MIN = 382,
     FSS_SRC = 383,
     FSS_ROUND = 384,
     FSV_SET_LOCAL_VAR = 385,
     FSA_LVAR_ASSIGN = 386,
     FSA_ALLDONE = 387,
     FSA_FIRSTDONE = 388,
     FSA_TIMEOUT = 389,
     FSC_OSPROF_ENABLE = 390,
     FSC_OSPROF_DISABLE = 391,
     FSA_NOREADAHEAD = 392,
     FSA_IOPRIO = 393,
     FSA_WRITEONLY = 394
   };
#endif
/* Tokens.  */
#define FSC_LIST 258
#define FSC_DEFINE 259
#define FSC_EXEC 260
#define FSC_QUIT 261
#define FSC_DEBUG 262
#define FSC_CREATE 263
#define FSC_SLEEP 264
#define FSC_STATS 265
#define FSC_FOREACH 266
#define FSC_SET 267
#define FSC_SHUTDOWN 268
#define FSC_LOG 269
#define FSC_SYSTEM 270
#define FSC_FLOWOP 271
#define FSC_EVENTGEN 272
#define FSC_ECHO 273
#define FSC_LOAD 274
#define FSC_RUN 275
#define FSC_PSRUN 276
#define FSC_WARMUP 277
#define FSC_NOUSESTATS 278
#define FSC_FSCHECK 279
#define FSC_FSFLUSH 280
#define FSC_USAGE 281
#define FSC_HELP 282
#define FSC_VARS 283
#define FSC_VERSION 284
#define FSC_ENABLE 285
#define FSC_DOMULTISYNC 286
#define FSV_STRING 287
#define FSV_VAL_INT 288
#define FSV_VAL_NEGINT 289
#define FSV_VAL_BOOLEAN 290
#define FSV_VARIABLE 291
#define FSV_WHITESTRING 292
#define FSV_RANDUNI 293
#define FSV_RANDTAB 294
#define FSV_RANDVAR 295
#define FSV_URAND 296
#define FSV_RAND48 297
#define FST_INT 298
#define FST_BOOLEAN 299
#define FSE_FILE 300
#define FSE_PROC 301
#define FSE_THREAD 302
#define FSE_CLEAR 303
#define FSE_ALL 304
#define FSE_SNAP 305
#define FSE_DUMP 306
#define FSE_DIRECTORY 307
#define FSE_COMMAND 308
#define FSE_FILESET 309
#define FSE_POSSET 310
#define FSE_XMLDUMP 311
#define FSE_RAND 312
#define FSE_MODE 313
#define FSE_MULTI 314
#define FSE_MULTIDUMP 315
#define FSK_SEPLST 316
#define FSK_OPENLST 317
#define FSK_CLOSELST 318
#define FSK_ASSIGN 319
#define FSK_IN 320
#define FSK_QUOTE 321
#define FSK_DIRSEPLST 322
#define FSK_PLUS 323
#define FSK_MINUS 324
#define FSK_MULTIPLY 325
#define FSK_DIVIDE 326
#define FSA_SIZE 327
#define FSA_PREALLOC 328
#define FSA_PARALLOC 329
#define FSA_PATH 330
#define FSA_REUSE 331
#define FSA_PROCESS 332
#define FSA_MEMSIZE 333
#define FSA_RATE 334
#define FSA_CACHED 335
#define FSA_READONLY 336
#define FSA_TRUSTTREE 337
#define FSA_IOSIZE 338
#define FSA_FILE 339
#define FSA_POSSET 340
#define FSA_WSS 341
#define FSA_NAME 342
#define FSA_RANDOM 343
#define FSA_INSTANCES 344
#define FSA_DSYNC 345
#define FSA_TARGET 346
#define FSA_ITERS 347
#define FSA_NICE 348
#define FSA_VALUE 349
#define FSA_BLOCKING 350
#define FSA_HIGHWATER 351
#define FSA_DIRECTIO 352
#define FSA_DIRWIDTH 353
#define FSA_FD 354
#define FSA_SRCFD 355
#define FSA_ROTATEFD 356
#define FSA_NAMELENGTH 357
#define FSA_FILESIZE 358
#define FSA_ENTRIES 359
#define FSA_FILESIZEGAMMA 360
#define FSA_DIRDEPTHRV 361
#define FSA_DIRGAMMA 362
#define FSA_USEISM 363
#define FSA_TYPE 364
#define FSA_RANDTABLE 365
#define FSA_RANDSRC 366
#define FSA_RANDROUND 367
#define FSA_LEAFDIRS 368
#define FSA_INDEXED 369
#define FSA_FSTYPE 370
#define FSA_RANDSEED 371
#define FSA_RANDGAMMA 372
#define FSA_RANDMEAN 373
#define FSA_RANDMIN 374
#define FSA_RANDMAX 375
#define FSA_MASTER 376
#define FSA_CLIENT 377
#define FSS_TYPE 378
#define FSS_SEED 379
#define FSS_GAMMA 380
#define FSS_MEAN 381
#define FSS_MIN 382
#define FSS_SRC 383
#define FSS_ROUND 384
#define FSV_SET_LOCAL_VAR 385
#define FSA_LVAR_ASSIGN 386
#define FSA_ALLDONE 387
#define FSA_FIRSTDONE 388
#define FSA_TIMEOUT 389
#define FSC_OSPROF_ENABLE 390
#define FSC_OSPROF_DISABLE 391
#define FSA_NOREADAHEAD 392
#define FSA_IOPRIO 393
#define FSA_WRITEONLY 394




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 162 "parser_gram.y"

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
#line 344 "parser_gram.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


