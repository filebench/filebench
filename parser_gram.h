
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
     FSV_URAND = 295,
     FSV_RAND48 = 296,
     FST_INT = 297,
     FST_BOOLEAN = 298,
     FSE_FILE = 299,
     FSE_PROC = 300,
     FSE_THREAD = 301,
     FSE_CLEAR = 302,
     FSE_ALL = 303,
     FSE_SNAP = 304,
     FSE_DUMP = 305,
     FSE_DIRECTORY = 306,
     FSE_COMMAND = 307,
     FSE_FILESET = 308,
     FSE_POSSET = 309,
     FSE_XMLDUMP = 310,
     FSE_RAND = 311,
     FSE_MODE = 312,
     FSE_MULTI = 313,
     FSE_MULTIDUMP = 314,
     FSK_SEPLST = 315,
     FSK_OPENLST = 316,
     FSK_CLOSELST = 317,
     FSK_ASSIGN = 318,
     FSK_IN = 319,
     FSK_QUOTE = 320,
     FSK_DIRSEPLST = 321,
     FSK_PLUS = 322,
     FSK_MINUS = 323,
     FSK_MULTIPLY = 324,
     FSK_DIVIDE = 325,
     FSA_SIZE = 326,
     FSA_PREALLOC = 327,
     FSA_PARALLOC = 328,
     FSA_PATH = 329,
     FSA_REUSE = 330,
     FSA_PROCESS = 331,
     FSA_MEMSIZE = 332,
     FSA_RATE = 333,
     FSA_CACHED = 334,
     FSA_READONLY = 335,
     FSA_TRUSTTREE = 336,
     FSA_IOSIZE = 337,
     FSA_FILE = 338,
     FSA_POSSET = 339,
     FSA_WSS = 340,
     FSA_NAME = 341,
     FSA_RANDOM = 342,
     FSA_INSTANCES = 343,
     FSA_DSYNC = 344,
     FSA_TARGET = 345,
     FSA_ITERS = 346,
     FSA_NICE = 347,
     FSA_VALUE = 348,
     FSA_BLOCKING = 349,
     FSA_HIGHWATER = 350,
     FSA_DIRECTIO = 351,
     FSA_DIRWIDTH = 352,
     FSA_FD = 353,
     FSA_SRCFD = 354,
     FSA_ROTATEFD = 355,
     FSA_NAMELENGTH = 356,
     FSA_FILESIZE = 357,
     FSA_ENTRIES = 358,
     FSA_FILESIZEGAMMA = 359,
     FSA_DIRDEPTHRV = 360,
     FSA_DIRGAMMA = 361,
     FSA_USEISM = 362,
     FSA_TYPE = 363,
     FSA_RANDTABLE = 364,
     FSA_RANDSRC = 365,
     FSA_RANDROUND = 366,
     FSA_LEAFDIRS = 367,
     FSA_INDEXED = 368,
     FSA_FSTYPE = 369,
     FSA_RANDSEED = 370,
     FSA_RANDGAMMA = 371,
     FSA_RANDMEAN = 372,
     FSA_RANDMIN = 373,
     FSA_RANDMAX = 374,
     FSA_MASTER = 375,
     FSA_CLIENT = 376,
     FSS_TYPE = 377,
     FSS_SEED = 378,
     FSS_GAMMA = 379,
     FSS_MEAN = 380,
     FSS_MIN = 381,
     FSS_SRC = 382,
     FSS_ROUND = 383,
     FSV_SET_LOCAL_VAR = 384,
     FSA_LVAR_ASSIGN = 385,
     FSA_ALLDONE = 386,
     FSA_FIRSTDONE = 387,
     FSA_TIMEOUT = 388,
     FSC_OSPROF_ENABLE = 389,
     FSC_OSPROF_DISABLE = 390,
     FSA_NOREADAHEAD = 391,
     FSA_IOPRIO = 392,
     FSA_WRITEONLY = 393
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
#define FSV_URAND 295
#define FSV_RAND48 296
#define FST_INT 297
#define FST_BOOLEAN 298
#define FSE_FILE 299
#define FSE_PROC 300
#define FSE_THREAD 301
#define FSE_CLEAR 302
#define FSE_ALL 303
#define FSE_SNAP 304
#define FSE_DUMP 305
#define FSE_DIRECTORY 306
#define FSE_COMMAND 307
#define FSE_FILESET 308
#define FSE_POSSET 309
#define FSE_XMLDUMP 310
#define FSE_RAND 311
#define FSE_MODE 312
#define FSE_MULTI 313
#define FSE_MULTIDUMP 314
#define FSK_SEPLST 315
#define FSK_OPENLST 316
#define FSK_CLOSELST 317
#define FSK_ASSIGN 318
#define FSK_IN 319
#define FSK_QUOTE 320
#define FSK_DIRSEPLST 321
#define FSK_PLUS 322
#define FSK_MINUS 323
#define FSK_MULTIPLY 324
#define FSK_DIVIDE 325
#define FSA_SIZE 326
#define FSA_PREALLOC 327
#define FSA_PARALLOC 328
#define FSA_PATH 329
#define FSA_REUSE 330
#define FSA_PROCESS 331
#define FSA_MEMSIZE 332
#define FSA_RATE 333
#define FSA_CACHED 334
#define FSA_READONLY 335
#define FSA_TRUSTTREE 336
#define FSA_IOSIZE 337
#define FSA_FILE 338
#define FSA_POSSET 339
#define FSA_WSS 340
#define FSA_NAME 341
#define FSA_RANDOM 342
#define FSA_INSTANCES 343
#define FSA_DSYNC 344
#define FSA_TARGET 345
#define FSA_ITERS 346
#define FSA_NICE 347
#define FSA_VALUE 348
#define FSA_BLOCKING 349
#define FSA_HIGHWATER 350
#define FSA_DIRECTIO 351
#define FSA_DIRWIDTH 352
#define FSA_FD 353
#define FSA_SRCFD 354
#define FSA_ROTATEFD 355
#define FSA_NAMELENGTH 356
#define FSA_FILESIZE 357
#define FSA_ENTRIES 358
#define FSA_FILESIZEGAMMA 359
#define FSA_DIRDEPTHRV 360
#define FSA_DIRGAMMA 361
#define FSA_USEISM 362
#define FSA_TYPE 363
#define FSA_RANDTABLE 364
#define FSA_RANDSRC 365
#define FSA_RANDROUND 366
#define FSA_LEAFDIRS 367
#define FSA_INDEXED 368
#define FSA_FSTYPE 369
#define FSA_RANDSEED 370
#define FSA_RANDGAMMA 371
#define FSA_RANDMEAN 372
#define FSA_RANDMIN 373
#define FSA_RANDMAX 374
#define FSA_MASTER 375
#define FSA_CLIENT 376
#define FSS_TYPE 377
#define FSS_SEED 378
#define FSS_GAMMA 379
#define FSS_MEAN 380
#define FSS_MIN 381
#define FSS_SRC 382
#define FSS_ROUND 383
#define FSV_SET_LOCAL_VAR 384
#define FSA_LVAR_ASSIGN 385
#define FSA_ALLDONE 386
#define FSA_FIRSTDONE 387
#define FSA_TIMEOUT 388
#define FSC_OSPROF_ENABLE 389
#define FSC_OSPROF_DISABLE 390
#define FSA_NOREADAHEAD 391
#define FSA_IOPRIO 392
#define FSA_WRITEONLY 393




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 151 "parser_gram.y"

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
#line 342 "parser_gram.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


