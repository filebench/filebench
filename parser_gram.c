
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 29 "parser_gram.y"


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
#ifdef HAVE_LIBTECLA
#include <libtecla.h>
#endif
#include "parsertypes.h"
#include "filebench.h"
#include "utils.h"
#include "stats.h"
#include "vars.h"
#include "eventgen.h"
#ifdef HAVE_LIBTECLA
#include "auto_comp.h"
#endif
#include "multi_client_sync.h"

/* yacc and lex externals */
extern FILE *yyin;
extern int yydebug;
extern void yyerror(char *s);
extern int yylex(void);

/* GetLine resource object */
#ifdef HAVE_LIBTECLA
static GetLine *gl;
#endif

/* executable name to execute worker processes later */
char *execname;

static int dofile = DOFILE_FALSE;

static char *fbbasepath = FILEBENCHDIR;
static char cwd[MAXPATHLEN];
static pidlist_t *pidlist;
static int filecreate_done;

/* utilities */
static cmd_t *alloc_cmd(void);
static attr_t *alloc_attr(void);
static attr_t *alloc_lvar_attr(var_t *var);
static attr_t *get_attr(cmd_t *cmd, int64_t name);
static attr_t *get_attr_fileset(cmd_t *cmd, int64_t name);
static attr_t *get_attr_integer(cmd_t *cmd, int64_t name);
static attr_t *get_attr_bool(cmd_t *cmd, int64_t name);
static void get_attr_lvars(cmd_t *cmd, flowop_t *flowop);
static list_t *alloc_list();
static probtabent_t *alloc_probtabent(void);
static void add_lvar_to_list(var_t *newlvar, var_t **lvar_list);

/* Info Commands */
static void parser_list(cmd_t *);
static void parser_flowop_list(cmd_t *);
static void parser_list_cvar_types(void);
static void parser_list_cvar_type_parameters(cmd_t *);

/* Define Commands */
static void parser_proc_define(cmd_t *);
static void parser_thread_define(cmd_t *, procflow_t *, int instances);
static void parser_flowop_define(cmd_t *, threadflow_t *, flowop_t **, int);
static void parser_file_define(cmd_t *);
static void parser_fileset_define(cmd_t *);
static void parser_posset_define(cmd_t *);
static void parser_var_assign_randvar(char *, cmd_t *);
static void parser_composite_flowop_define(cmd_t *);
static void parser_var_assign_cvar(char *, cmd_t *);

/* Create Commands */
static void parser_proc_create(cmd_t *);
static void parser_fileset_create(cmd_t *);

/* Shutdown Commands */
static void parser_proc_shutdown(cmd_t *);
static void parser_filebench_shutdown(cmd_t *cmd);
static void parser_fileset_shutdown(cmd_t *cmd);

/* Other Commands */
static void parser_echo(cmd_t *cmd);
static void parser_foreach_integer(cmd_t *cmd);
static void parser_foreach_string(cmd_t *cmd);
static void parser_fscheck(cmd_t *cmd);
static void parser_fsflush(cmd_t *cmd);
static void parser_log(cmd_t *cmd);
static void parser_statscmd(cmd_t *cmd);
static void parser_statsdump(cmd_t *cmd);
static void parser_statsxmldump(cmd_t *cmd);
static void parser_statsmultidump(cmd_t *cmd);
static void parser_usage(cmd_t *cmd);
static void parser_system(cmd_t *cmd);
static void parser_statssnap(cmd_t *cmd);
static void parser_directory(cmd_t *cmd);
static void parser_eventgen(cmd_t *cmd);
static void parser_enable_mc(cmd_t *cmd);
static void parser_domultisync(cmd_t *cmd);
static void parser_run(cmd_t *cmd);
static void parser_run_variable(cmd_t *cmd);
static void parser_psrun(cmd_t *cmd);
static void parser_sleep(cmd_t *cmd);
static void parser_sleep_variable(cmd_t *cmd);
static void parser_warmup(cmd_t *cmd);
static void parser_warmup_variable(cmd_t *cmd);
static void parser_help(cmd_t *cmd);
static void arg_parse(const char *command);
static void parser_abort(int arg);
static void parser_version(cmd_t *cmd);
static void parser_osprof_enable(cmd_t *cmd);
static void parser_osprof_disable(cmd_t *cmd);



/* Line 189 of yacc.c  */
#line 201 "parser_gram.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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
     FSK_OPENPAR = 318,
     FSK_CLOSEPAR = 319,
     FSK_ASSIGN = 320,
     FSK_IN = 321,
     FSK_QUOTE = 322,
     FSK_DIRSEPLST = 323,
     FSK_PLUS = 324,
     FSK_MINUS = 325,
     FSK_MULTIPLY = 326,
     FSK_DIVIDE = 327,
     FSA_SIZE = 328,
     FSA_PREALLOC = 329,
     FSA_PARALLOC = 330,
     FSA_PATH = 331,
     FSA_REUSE = 332,
     FSA_PROCESS = 333,
     FSA_MEMSIZE = 334,
     FSA_RATE = 335,
     FSA_CACHED = 336,
     FSA_READONLY = 337,
     FSA_TRUSTTREE = 338,
     FSA_IOSIZE = 339,
     FSA_FILE = 340,
     FSA_POSSET = 341,
     FSA_WSS = 342,
     FSA_NAME = 343,
     FSA_RANDOM = 344,
     FSA_INSTANCES = 345,
     FSA_DSYNC = 346,
     FSA_TARGET = 347,
     FSA_ITERS = 348,
     FSA_NICE = 349,
     FSA_VALUE = 350,
     FSA_BLOCKING = 351,
     FSA_HIGHWATER = 352,
     FSA_DIRECTIO = 353,
     FSA_DIRWIDTH = 354,
     FSA_FD = 355,
     FSA_SRCFD = 356,
     FSA_ROTATEFD = 357,
     FSA_NAMELENGTH = 358,
     FSA_FILESIZE = 359,
     FSA_ENTRIES = 360,
     FSA_DIRDEPTHRV = 361,
     FSA_DIRGAMMA = 362,
     FSA_USEISM = 363,
     FSA_TYPE = 364,
     FSA_RANDTABLE = 365,
     FSA_RANDSRC = 366,
     FSA_ROUND = 367,
     FSA_LEAFDIRS = 368,
     FSA_INDEXED = 369,
     FSA_FSTYPE = 370,
     FSA_RANDSEED = 371,
     FSA_RANDGAMMA = 372,
     FSA_RANDMEAN = 373,
     FSA_MIN = 374,
     FSA_MAX = 375,
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
     FSA_WRITEONLY = 394,
     FSE_CVAR = 395,
     FSA_PARAMETERS = 396,
     FSA_TYPES = 397
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
#define FSK_OPENPAR 318
#define FSK_CLOSEPAR 319
#define FSK_ASSIGN 320
#define FSK_IN 321
#define FSK_QUOTE 322
#define FSK_DIRSEPLST 323
#define FSK_PLUS 324
#define FSK_MINUS 325
#define FSK_MULTIPLY 326
#define FSK_DIVIDE 327
#define FSA_SIZE 328
#define FSA_PREALLOC 329
#define FSA_PARALLOC 330
#define FSA_PATH 331
#define FSA_REUSE 332
#define FSA_PROCESS 333
#define FSA_MEMSIZE 334
#define FSA_RATE 335
#define FSA_CACHED 336
#define FSA_READONLY 337
#define FSA_TRUSTTREE 338
#define FSA_IOSIZE 339
#define FSA_FILE 340
#define FSA_POSSET 341
#define FSA_WSS 342
#define FSA_NAME 343
#define FSA_RANDOM 344
#define FSA_INSTANCES 345
#define FSA_DSYNC 346
#define FSA_TARGET 347
#define FSA_ITERS 348
#define FSA_NICE 349
#define FSA_VALUE 350
#define FSA_BLOCKING 351
#define FSA_HIGHWATER 352
#define FSA_DIRECTIO 353
#define FSA_DIRWIDTH 354
#define FSA_FD 355
#define FSA_SRCFD 356
#define FSA_ROTATEFD 357
#define FSA_NAMELENGTH 358
#define FSA_FILESIZE 359
#define FSA_ENTRIES 360
#define FSA_DIRDEPTHRV 361
#define FSA_DIRGAMMA 362
#define FSA_USEISM 363
#define FSA_TYPE 364
#define FSA_RANDTABLE 365
#define FSA_RANDSRC 366
#define FSA_ROUND 367
#define FSA_LEAFDIRS 368
#define FSA_INDEXED 369
#define FSA_FSTYPE 370
#define FSA_RANDSEED 371
#define FSA_RANDGAMMA 372
#define FSA_RANDMEAN 373
#define FSA_MIN 374
#define FSA_MAX 375
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
#define FSE_CVAR 395
#define FSA_PARAMETERS 396
#define FSA_TYPES 397




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 156 "parser_gram.y"

	int64_t		 ival;
	unsigned char	 bval;
	char *		 sval;
	fs_u		 val;
	avd_t		 avd;
	cmd_t		*cmd;
	attr_t		*attr;
	list_t		*list;
	probtabent_t	*rndtb;



/* Line 214 of yacc.c  */
#line 535 "parser_gram.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 547 "parser_gram.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   400

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  143
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  98
/* YYNRULES -- Number of rules.  */
#define YYNRULES  288
/* YYNRULES -- Number of states.  */
#define YYNSTATES  383

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   397

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    10,    12,    15,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    43,    45,    47,    49,    51,    53,    55,    57,    59,
      61,    63,    65,    67,    69,    71,    73,    75,    77,    79,
      87,    95,    97,   101,   105,   111,   113,   116,   119,   122,
     124,   126,   128,   131,   134,   137,   140,   142,   144,   146,
     149,   152,   155,   158,   161,   164,   167,   170,   173,   176,
     179,   182,   184,   187,   190,   193,   196,   199,   202,   204,
     206,   208,   210,   215,   220,   227,   232,   240,   248,   253,
     258,   263,   267,   270,   273,   277,   281,   285,   289,   293,
     295,   297,   300,   306,   308,   311,   318,   321,   324,   327,
     330,   333,   336,   343,   346,   349,   352,   355,   358,   361,
     364,   366,   369,   372,   374,   376,   379,   382,   386,   390,
     392,   395,   398,   400,   402,   404,   406,   408,   410,   414,
     416,   420,   424,   426,   430,   432,   434,   438,   446,   450,
     452,   456,   460,   468,   470,   474,   476,   480,   484,   486,
     488,   492,   496,   500,   502,   504,   508,   512,   514,   516,
     520,   524,   528,   532,   534,   536,   538,   540,   542,   544,
     546,   548,   550,   552,   554,   556,   558,   560,   562,   564,
     566,   568,   570,   572,   574,   576,   578,   580,   582,   584,
     586,   588,   590,   592,   594,   596,   598,   600,   602,   604,
     606,   608,   610,   612,   614,   616,   618,   620,   622,   624,
     626,   628,   630,   632,   634,   636,   638,   640,   642,   644,
     646,   648,   650,   652,   654,   656,   658,   660,   662,   664,
     666,   668,   670,   672,   674,   676,   678,   680,   682,   684,
     686,   688,   690,   692,   694,   696,   698,   700,   702,   704,
     706,   710,   714,   718,   722,   726,   732,   736,   740,   742,
     746,   752,   759,   762,   764,   768,   772,   774,   776,   778,
     780,   782,   784,   786,   788,   790,   792,   794,   796
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     144,     0,    -1,   144,   146,    -1,   144,     1,    -1,    -1,
     146,    -1,   145,   146,    -1,   178,    -1,   179,    -1,   180,
      -1,   181,    -1,   167,    -1,   150,    -1,   182,    -1,   152,
      -1,   156,    -1,   147,    -1,   164,    -1,   165,    -1,   188,
      -1,   163,    -1,   166,    -1,   186,    -1,   187,    -1,   168,
      -1,   183,    -1,   185,    -1,   184,    -1,   173,    -1,   151,
      -1,   153,    -1,   154,    -1,   155,    -1,   157,    -1,   158,
      -1,   174,    -1,   233,    -1,   234,    -1,    11,    -1,   147,
      36,    66,   148,    61,   145,    62,    -1,   147,    36,    66,
     149,    61,   145,    62,    -1,    33,    -1,   148,    60,    33,
      -1,    67,    37,    67,    -1,   149,    60,    67,    37,    67,
      -1,    17,    -1,   150,   204,    -1,    15,   162,    -1,    18,
     162,    -1,    29,    -1,   135,    -1,   136,    -1,    26,   162,
      -1,    30,    58,    -1,   157,   206,    -1,    31,   208,    -1,
      36,    -1,    32,    -1,   159,    -1,   159,    32,    -1,   159,
      36,    -1,   160,    32,    -1,   160,    36,    -1,    67,    36,
      -1,    67,    37,    -1,   161,    37,    -1,   161,    36,    -1,
     162,    37,    -1,   162,    36,    -1,   162,    67,    -1,   161,
      67,    -1,     3,    -1,   163,    16,    -1,    24,   209,    -1,
     164,   209,    -1,    25,   209,    -1,    14,   162,    -1,     7,
      33,    -1,   169,    -1,   170,    -1,   171,    -1,   172,    -1,
      12,    36,    65,    33,    -1,    12,    36,    65,    35,    -1,
      12,    36,    65,    67,    37,    67,    -1,    12,    36,    65,
      32,    -1,    12,    36,    65,    56,    63,   196,    64,    -1,
      12,    36,    65,   140,    63,   235,    64,    -1,    12,    57,
       6,   134,    -1,    12,    57,     6,   132,    -1,    12,    57,
       6,   133,    -1,    12,    57,    23,    -1,    10,    49,    -1,
      10,    47,    -1,    10,    51,   160,    -1,    10,    52,   162,
      -1,    10,    50,   162,    -1,    10,    55,   162,    -1,    10,
      59,   162,    -1,     6,    -1,   189,    -1,   175,   189,    -1,
      46,   200,    61,   175,    62,    -1,   176,    -1,   177,   176,
      -1,     4,    45,   200,    61,   177,    62,    -1,   178,   200,
      -1,     4,    44,    -1,     4,    53,    -1,   179,   192,    -1,
       4,    54,    -1,   180,   193,    -1,     4,    16,   230,    61,
     175,    62,    -1,   181,   230,    -1,     8,   190,    -1,    13,
     190,    -1,    22,    33,    -1,    22,    36,    -1,     9,    33,
      -1,     9,    36,    -1,     9,    -1,    20,    33,    -1,    20,
      36,    -1,    20,    -1,    21,    -1,    21,    34,    -1,    21,
      33,    -1,    21,    34,    33,    -1,    21,    33,    33,    -1,
      27,    -1,    16,   191,    -1,   189,   202,    -1,    45,    -1,
      46,    -1,    53,    -1,    44,    -1,    32,    -1,   195,    -1,
     192,    60,   195,    -1,   194,    -1,   193,    60,   194,    -1,
     211,    65,   239,    -1,   211,    -1,   210,    65,   239,    -1,
     210,    -1,   197,    -1,   196,    60,   197,    -1,   196,    60,
     110,    65,    61,   199,    62,    -1,   219,    65,   239,    -1,
     219,    -1,   109,    65,   220,    -1,   111,    65,   222,    -1,
      61,   240,    60,   240,    60,   240,    62,    -1,   198,    -1,
     199,    60,   198,    -1,   201,    -1,   200,    60,   201,    -1,
     212,    65,   238,    -1,   212,    -1,   203,    -1,   202,    60,
     203,    -1,   202,    60,   232,    -1,   213,    65,   238,    -1,
     213,    -1,   205,    -1,   204,    60,   205,    -1,   214,    65,
     238,    -1,   214,    -1,   207,    -1,   206,    60,   207,    -1,
     228,    65,   238,    -1,    95,    65,   238,    -1,   229,    65,
      32,    -1,   216,    -1,   217,    -1,   218,    -1,   225,    -1,
     215,    -1,   226,    -1,   227,    -1,    94,    -1,    88,    -1,
      90,    -1,    73,    -1,    88,    -1,    76,    -1,    82,    -1,
      83,    -1,    77,    -1,    74,    -1,    75,    -1,   139,    -1,
      88,    -1,    76,    -1,   105,    -1,    73,    -1,    99,    -1,
     106,    -1,    74,    -1,    75,    -1,    77,    -1,    82,    -1,
      83,    -1,   107,    -1,    81,    -1,   113,    -1,   139,    -1,
      88,    -1,   109,    -1,   116,    -1,   105,    -1,   120,    -1,
      88,    -1,   116,    -1,   117,    -1,   118,    -1,   119,    -1,
     112,    -1,   221,    -1,    38,    -1,    39,    -1,   117,    -1,
     223,    -1,    40,    -1,    41,    -1,   109,    -1,   141,    -1,
     119,    -1,   120,    -1,   112,    -1,    78,    -1,    88,    -1,
      79,    -1,   108,    -1,    90,    -1,   138,    -1,    87,    -1,
      85,    -1,    86,    -1,    88,    -1,    89,    -1,   100,    -1,
     101,    -1,   102,    -1,    91,    -1,    98,    -1,   114,    -1,
      92,    -1,    93,    -1,    95,    -1,    96,    -1,    97,    -1,
      84,    -1,   137,    -1,    80,    -1,   121,    -1,   122,    -1,
      76,    -1,   115,    -1,   231,    -1,   230,    60,   231,    -1,
     230,    60,   232,    -1,   237,    65,   238,    -1,    36,    65,
      35,    -1,    36,    65,    33,    -1,    36,    65,    67,    37,
      67,    -1,    36,    65,    32,    -1,    36,    65,    36,    -1,
      36,    -1,     3,   140,   142,    -1,     3,   140,   109,   141,
      32,    -1,     4,    16,   230,    61,   175,    62,    -1,   181,
     230,    -1,   236,    -1,   235,    60,   236,    -1,   224,    65,
     239,    -1,    88,    -1,    93,    -1,    32,    -1,    33,    -1,
      35,    -1,    36,    -1,   160,    -1,    32,    -1,    33,    -1,
      35,    -1,    36,    -1,    33,    -1,    36,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   254,   254,   261,   266,   268,   273,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   324,   330,
     353,   378,   385,   403,   410,   428,   434,   439,   448,   457,
     464,   471,   478,   487,   494,   499,   532,   539,   547,   550,
     568,   585,   603,   622,   629,   637,   655,   672,   690,   707,
     710,   715,   721,   726,   734,   739,   748,   756,   766,   766,
     766,   766,   768,   779,   789,   798,   809,   821,   833,   843,
     853,   863,   875,   883,   890,   898,   906,   913,   920,   929,
     936,   939,   957,   969,   972,   990,   999,  1004,  1011,  1019,
    1024,  1029,  1034,  1042,  1047,  1066,  1085,  1092,  1100,  1107,
    1114,  1122,  1129,  1136,  1144,  1152,  1161,  1170,  1178,  1187,
    1194,  1200,  1205,  1206,  1207,  1208,  1214,  1217,  1221,  1234,
    1238,  1252,  1257,  1264,  1269,  1279,  1283,  1296,  1315,  1320,
    1326,  1331,  1337,  1347,  1351,  1366,  1370,  1384,  1389,  1397,
    1401,  1414,  1428,  1433,  1441,  1445,  1459,  1464,  1472,  1476,
    1490,  1496,  1502,  1516,  1516,  1518,  1520,  1521,  1523,  1525,
    1528,  1529,  1530,  1533,  1534,  1535,  1536,  1537,  1538,  1539,
    1540,  1541,  1544,  1545,  1546,  1547,  1548,  1549,  1550,  1551,
    1552,  1553,  1554,  1555,  1556,  1557,  1558,  1561,  1562,  1563,
    1564,  1565,  1568,  1569,  1570,  1571,  1572,  1573,  1591,  1599,
    1600,  1601,  1603,  1611,  1612,  1615,  1616,  1617,  1618,  1619,
    1622,  1623,  1624,  1625,  1626,  1627,  1630,  1631,  1632,  1633,
    1634,  1635,  1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,
    1644,  1645,  1646,  1647,  1650,  1653,  1654,  1657,  1658,  1660,
    1664,  1677,  1691,  1697,  1702,  1707,  1712,  1717,  1722,  1728,
    1740,  1754,  1762,  1768,  1772,  1786,  1793,  1794,  1796,  1801,
    1805,  1809,  1815,  1819,  1823,  1827,  1831,  1837,  1840
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FSC_LIST", "FSC_DEFINE", "FSC_EXEC",
  "FSC_QUIT", "FSC_DEBUG", "FSC_CREATE", "FSC_SLEEP", "FSC_STATS",
  "FSC_FOREACH", "FSC_SET", "FSC_SHUTDOWN", "FSC_LOG", "FSC_SYSTEM",
  "FSC_FLOWOP", "FSC_EVENTGEN", "FSC_ECHO", "FSC_LOAD", "FSC_RUN",
  "FSC_PSRUN", "FSC_WARMUP", "FSC_NOUSESTATS", "FSC_FSCHECK",
  "FSC_FSFLUSH", "FSC_USAGE", "FSC_HELP", "FSC_VARS", "FSC_VERSION",
  "FSC_ENABLE", "FSC_DOMULTISYNC", "FSV_STRING", "FSV_VAL_INT",
  "FSV_VAL_NEGINT", "FSV_VAL_BOOLEAN", "FSV_VARIABLE", "FSV_WHITESTRING",
  "FSV_RANDUNI", "FSV_RANDTAB", "FSV_URAND", "FSV_RAND48", "FST_INT",
  "FST_BOOLEAN", "FSE_FILE", "FSE_PROC", "FSE_THREAD", "FSE_CLEAR",
  "FSE_ALL", "FSE_SNAP", "FSE_DUMP", "FSE_DIRECTORY", "FSE_COMMAND",
  "FSE_FILESET", "FSE_POSSET", "FSE_XMLDUMP", "FSE_RAND", "FSE_MODE",
  "FSE_MULTI", "FSE_MULTIDUMP", "FSK_SEPLST", "FSK_OPENLST",
  "FSK_CLOSELST", "FSK_OPENPAR", "FSK_CLOSEPAR", "FSK_ASSIGN", "FSK_IN",
  "FSK_QUOTE", "FSK_DIRSEPLST", "FSK_PLUS", "FSK_MINUS", "FSK_MULTIPLY",
  "FSK_DIVIDE", "FSA_SIZE", "FSA_PREALLOC", "FSA_PARALLOC", "FSA_PATH",
  "FSA_REUSE", "FSA_PROCESS", "FSA_MEMSIZE", "FSA_RATE", "FSA_CACHED",
  "FSA_READONLY", "FSA_TRUSTTREE", "FSA_IOSIZE", "FSA_FILE", "FSA_POSSET",
  "FSA_WSS", "FSA_NAME", "FSA_RANDOM", "FSA_INSTANCES", "FSA_DSYNC",
  "FSA_TARGET", "FSA_ITERS", "FSA_NICE", "FSA_VALUE", "FSA_BLOCKING",
  "FSA_HIGHWATER", "FSA_DIRECTIO", "FSA_DIRWIDTH", "FSA_FD", "FSA_SRCFD",
  "FSA_ROTATEFD", "FSA_NAMELENGTH", "FSA_FILESIZE", "FSA_ENTRIES",
  "FSA_DIRDEPTHRV", "FSA_DIRGAMMA", "FSA_USEISM", "FSA_TYPE",
  "FSA_RANDTABLE", "FSA_RANDSRC", "FSA_ROUND", "FSA_LEAFDIRS",
  "FSA_INDEXED", "FSA_FSTYPE", "FSA_RANDSEED", "FSA_RANDGAMMA",
  "FSA_RANDMEAN", "FSA_MIN", "FSA_MAX", "FSA_MASTER", "FSA_CLIENT",
  "FSS_TYPE", "FSS_SEED", "FSS_GAMMA", "FSS_MEAN", "FSS_MIN", "FSS_SRC",
  "FSS_ROUND", "FSV_SET_LOCAL_VAR", "FSA_LVAR_ASSIGN", "FSA_ALLDONE",
  "FSA_FIRSTDONE", "FSA_TIMEOUT", "FSC_OSPROF_ENABLE",
  "FSC_OSPROF_DISABLE", "FSA_NOREADAHEAD", "FSA_IOPRIO", "FSA_WRITEONLY",
  "FSE_CVAR", "FSA_PARAMETERS", "FSA_TYPES", "$accept", "commands",
  "inner_commands", "command", "foreach_command", "integer_seplist",
  "string_seplist", "eventgen_command", "system_command", "echo_command",
  "version_command", "osprof_enable_command", "osprof_disable_command",
  "usage_command", "enable_command", "multisync_command", "var_string",
  "var_string_list", "whitevar_string", "whitevar_string_list",
  "list_command", "fscheck_command", "fsflush_command", "log_command",
  "debug_command", "set_command", "set_variable", "set_random_variable",
  "set_custom_variable", "set_mode", "stats_command", "quit_command",
  "flowop_list", "thread", "thread_list", "proc_define_command",
  "files_define_command", "posset_define_command", "fo_define_command",
  "create_command", "shutdown_command", "warmup_command", "sleep_command",
  "run_command", "psrun_command", "help_command", "flowop_command",
  "entity", "name", "files_attr_ops", "posset_attr_ops", "posset_attr_op",
  "files_attr_op", "randvar_attr_ops", "randvar_attr_op", "probtabentry",
  "probtabentry_list", "pt_attr_ops", "pt_attr_op", "fo_attr_ops",
  "fo_attr_op", "ev_attr_ops", "ev_attr_op", "enable_multi_ops",
  "enable_multi_op", "multisync_op", "fscheck_attr_op", "files_attr_name",
  "posset_attr_name", "pt_attr_name", "fo_attr_name", "ev_attr_name",
  "attrs_define_proc", "attrs_define_file", "attrs_define_fileset",
  "attrs_define_posset", "randvar_attr_name", "randvar_attr_typop",
  "randtype_name", "randvar_attr_srcop", "randsrc_name", "cvar_attr_name",
  "attrs_define_thread", "attrs_flowop", "attrs_eventgen", "em_attr_name",
  "fscheck_attr_name", "comp_attr_ops", "comp_attr_op", "comp_lvar_def",
  "list_cvar_types_command", "list_cvar_type_parameters_command",
  "cvar_attr_ops", "cvar_attr_op", "attrs_define_comp", "attr_value",
  "attr_list_value", "var_int_val", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   143,   144,   144,   144,   145,   145,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   147,   147,
     147,   148,   148,   149,   149,   150,   150,   151,   152,   153,
     154,   155,   156,   157,   157,   158,   159,   159,   160,   160,
     160,   160,   160,   161,   161,   162,   162,   162,   162,   162,
     162,   163,   163,   164,   164,   165,   166,   167,   168,   168,
     168,   168,   169,   169,   169,   169,   170,   171,   172,   172,
     172,   172,   173,   173,   173,   173,   173,   173,   173,   174,
     175,   175,   176,   177,   177,   178,   178,   179,   179,   179,
     180,   180,   181,   181,   182,   183,   184,   184,   185,   185,
     185,   186,   186,   186,   187,   187,   187,   187,   187,   188,
     189,   189,   190,   190,   190,   190,   191,   192,   192,   193,
     193,   194,   194,   195,   195,   196,   196,   196,   197,   197,
     197,   197,   198,   199,   199,   200,   200,   201,   201,   202,
     202,   202,   203,   203,   204,   204,   205,   205,   206,   206,
     207,   208,   209,   210,   210,   211,   212,   212,   213,   214,
     215,   215,   215,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   218,   218,   218,
     218,   218,   219,   219,   219,   219,   219,   219,   220,   221,
     221,   221,   222,   223,   223,   224,   224,   224,   224,   224,
     225,   225,   225,   225,   225,   225,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   227,   228,   228,   229,   229,   230,
     230,   230,   231,   232,   232,   232,   232,   232,   232,   233,
     234,   181,   181,   235,   235,   236,   237,   237,   238,   238,
     238,   238,   239,   239,   239,   239,   239,   240,   240
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     7,
       7,     1,     3,     3,     5,     1,     2,     2,     2,     1,
       1,     1,     2,     2,     2,     2,     1,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     1,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     4,     4,     6,     4,     7,     7,     4,     4,
       4,     3,     2,     2,     3,     3,     3,     3,     3,     1,
       1,     2,     5,     1,     2,     6,     2,     2,     2,     2,
       2,     2,     6,     2,     2,     2,     2,     2,     2,     2,
       1,     2,     2,     1,     1,     2,     2,     3,     3,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     3,     1,     3,     1,     1,     3,     7,     3,     1,
       3,     3,     7,     1,     3,     1,     3,     3,     1,     1,
       3,     3,     3,     1,     1,     3,     3,     1,     1,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     5,     3,     3,     1,     3,
       5,     6,     2,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     1,     3,    71,     0,    99,     0,     0,   120,
       0,    38,     0,     0,     0,     0,    45,     0,   123,   124,
       0,     0,     0,     0,   129,    49,     0,     0,    50,    51,
       2,    16,    12,    29,    14,    30,    31,    32,    15,    33,
      34,    20,    17,    18,    21,    11,    24,    78,    79,    80,
      81,    28,    35,     7,     8,     9,    10,    13,    25,    27,
      26,    22,    23,    19,    36,    37,     0,     0,   107,     0,
     108,   110,    77,   135,   132,   133,   134,   114,   118,   119,
      93,    92,     0,     0,     0,     0,     0,     0,     0,   115,
       0,     0,    76,    47,    48,   121,   122,   126,   125,   116,
     117,   257,   258,    73,     0,    75,    52,    53,     0,    55,
       0,   254,    46,   164,   167,   179,   255,   256,    54,   168,
       0,    72,    74,   230,   232,   181,   182,   180,   233,   235,
     106,   155,   158,   177,   176,   183,   189,   190,   185,   188,
     204,   186,   187,   184,   196,   194,   197,   203,   205,   191,
     109,   137,   144,   173,   174,   207,   210,   208,   209,   211,
     111,   139,   142,   175,   276,   277,   113,   259,     0,     0,
     269,     0,     0,    96,    57,    56,    58,    94,    95,    97,
      98,     0,     0,    91,    63,    64,    66,    65,    70,    68,
      67,    69,   128,   127,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    59,    60,    61,    62,    85,    82,    83,     0,
       0,     0,    89,    90,    88,   172,   278,   279,   280,   281,
     171,    41,     0,     0,     0,   165,   166,   169,   170,   156,
     157,   138,    57,   284,   285,    56,   282,   143,   140,   141,
     268,   260,   261,   262,   270,     0,     0,   100,     0,   103,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     136,   130,   112,   101,   252,   237,   238,   236,   239,   240,
     244,   247,   248,   249,   250,   251,   245,   241,   242,   243,
     246,   253,   131,   159,   163,   178,     0,   105,   104,   212,
       0,     0,   217,   213,   214,   215,   216,     0,   145,   149,
      84,   225,   229,   227,   228,   226,     0,     0,   273,    43,
      42,     0,     5,     0,     0,   266,   264,   263,   267,     0,
       0,     0,     0,     0,     0,     0,    86,     0,     0,     0,
      87,    39,     6,     0,    40,     0,   160,   161,   162,     0,
     219,   220,   221,   150,   218,   223,   224,   151,   222,     0,
     146,   148,   275,   274,    44,   265,   102,     0,     0,     0,
     153,     0,   287,   288,     0,     0,   147,     0,   154,     0,
       0,     0,   152
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   321,   322,    31,   233,   234,    32,    33,    34,
      35,    36,    37,    38,    39,    40,   176,   246,    91,    92,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,   256,   259,   260,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,   257,    77,   271,   150,
     160,   161,   151,   307,   308,   370,   371,   130,   131,   292,
     293,   112,   113,   118,   119,   109,   103,   152,   162,   132,
     294,   114,   133,   153,   154,   163,   309,   353,   354,   357,
     358,   316,   134,   295,   115,   120,   104,   166,   167,   252,
      64,    65,   317,   318,   168,   230,   247,   374
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -221
static const yytype_int16 yypact[] =
{
    -221,     2,  -221,  -221,  -133,   101,  -221,    32,   167,   129,
     288,  -221,    77,   167,   -20,   -20,  -221,   -20,   191,   210,
     198,    16,    16,   -20,  -221,  -221,    52,    58,  -221,  -221,
    -221,   111,    84,  -221,  -221,  -221,  -221,  -221,  -221,   160,
    -221,   156,    16,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,   147,   133,   181,    -5,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,   -88,    -5,  -221,   147,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,   -20,   112,   -20,   -20,   -20,   152,    73,  -221,
     279,   132,   134,   134,   134,  -221,  -221,   164,   231,  -221,
    -221,  -221,  -221,  -221,   183,  -221,   134,  -221,   203,  -221,
     209,  -221,   224,  -221,   228,  -221,  -221,  -221,   229,  -221,
     243,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
     236,  -221,   245,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
     270,  -221,   254,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
     276,  -221,   285,  -221,  -221,  -221,   286,  -221,   287,   212,
    -221,   257,   261,   134,  -221,  -221,   149,   162,   134,   134,
     134,   107,   166,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,   319,   125,    -8,    84,   125,   160,
     125,   147,   125,   133,   259,   181,   259,    63,   125,   322,
     339,   310,  -221,  -221,  -221,  -221,  -221,  -221,  -221,   294,
     321,   296,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,   323,   268,   281,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,   162,  -221,  -221,  -221,
     297,  -221,  -221,  -221,  -221,   329,   -12,   165,   147,  -221,
      97,   195,   298,   168,   299,   330,    94,   300,    94,   238,
    -221,  -221,  -221,   165,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,   304,  -221,   303,  -221,   284,  -221,  -221,  -221,
     305,   306,  -221,  -221,  -221,  -221,  -221,   158,  -221,   307,
    -221,  -221,  -221,  -221,  -221,  -221,   309,   159,  -221,  -221,
    -221,    31,  -221,   332,    60,  -221,  -221,  -221,  -221,   336,
      91,   125,   339,    56,   308,   215,  -221,   259,   259,   168,
    -221,  -221,  -221,   311,  -221,   312,  -221,  -221,  -221,    14,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,   315,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,   314,   316,   200,
    -221,   216,  -221,  -221,   324,   316,  -221,   200,  -221,   325,
     200,   320,  -221
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -221,  -221,   108,    -1,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,   313,  -221,   118,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,    49,   123,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -220,   373,  -221,  -221,
    -221,   182,   185,  -221,    54,    15,  -221,   -68,   190,  -221,
      62,  -221,   196,  -221,   199,  -221,   110,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,   327,   188,    67,
    -221,  -221,  -221,    61,  -221,   -72,  -188,  -135
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      30,   172,     2,     3,   255,     4,     5,    66,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   249,    16,
      17,   169,    18,    19,    20,   231,    21,    22,    23,    24,
     255,    25,    26,    27,     4,     5,   273,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    90,    16,    17,
     272,    18,    19,    20,   170,    21,    22,    23,    24,   232,
      25,    26,    27,     4,     5,    72,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,   366,    16,    17,   182,
      18,    19,    20,   164,    21,    22,    23,    24,   165,    25,
      26,    27,   101,   341,   350,   351,   183,     4,     5,   250,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
     107,    16,    17,    87,    18,    19,    20,    67,    21,    22,
      23,    24,   344,    25,    26,    27,   236,   250,   238,   273,
     240,   102,   105,    93,    88,    94,   253,    28,    29,   216,
     217,   106,   218,   258,   174,    68,    69,   110,   175,   361,
     362,   164,   122,   108,    70,    71,   165,   226,   227,   297,
     228,   229,    78,   219,   111,    79,    28,    29,   186,   187,
     189,   190,   121,   352,   220,   274,   275,   276,   277,   278,
     279,   212,   280,   281,   282,   213,   283,   284,   285,   286,
     296,   287,   288,   289,   214,    28,    29,   192,   215,   188,
     173,   191,   178,   179,   180,   290,   135,   136,   137,   138,
     139,    73,    74,    75,   140,   141,   142,   181,   335,   339,
      76,   143,   336,   340,    95,   123,   124,    96,   291,    28,
      29,    99,   144,   372,   100,   125,   373,   126,   145,   146,
     147,   127,   379,    97,    98,   381,   148,   221,   194,   274,
     275,   276,   277,   278,   279,   128,   280,   281,   282,   348,
     283,   284,   285,   286,   193,   287,   288,   289,   195,   155,
     325,   326,   149,   327,   328,   196,   375,   311,   376,   290,
     312,   116,   117,   299,   197,   129,   156,   313,   314,   199,
     157,   242,   243,   198,   244,   245,   201,   158,   222,   223,
     224,   159,   291,   299,   300,   329,   301,   302,   200,   315,
     202,   303,   304,   305,   306,   184,   185,   207,   210,   204,
     342,   201,   211,   342,   300,   359,   301,   302,   265,   266,
     203,   303,   304,   305,   306,    80,   205,    81,    82,    83,
      84,   267,   268,    85,   201,   332,   207,    86,   355,   356,
     206,   225,   208,   209,   254,   255,   258,   261,   262,   263,
     264,   270,   269,   320,   330,   310,   319,   323,   331,   343,
     333,   334,   337,   345,   338,   368,   324,   369,   364,   365,
     367,   349,   382,   298,   377,   380,    89,   248,   241,   360,
     378,   239,   346,   235,   171,   251,   177,   347,   237,     0,
     363
};

static const yytype_int16 yycheck[] =
{
       1,    69,     0,     1,    16,     3,     4,   140,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   206,    17,
      18,   109,    20,    21,    22,    33,    24,    25,    26,    27,
      16,    29,    30,    31,     3,     4,   256,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    67,    17,    18,
      62,    20,    21,    22,   142,    24,    25,    26,    27,    67,
      29,    30,    31,     3,     4,    33,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    62,    17,    18,     6,
      20,    21,    22,    88,    24,    25,    26,    27,    93,    29,
      30,    31,    76,    62,    38,    39,    23,     3,     4,    36,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      58,    17,    18,    36,    20,    21,    22,    16,    24,    25,
      26,    27,    62,    29,    30,    31,   198,    36,   200,   349,
     202,   115,    22,    15,    57,    17,   208,   135,   136,    32,
      33,    23,    35,    46,    32,    44,    45,    36,    36,   337,
     338,    88,    42,    95,    53,    54,    93,    32,    33,    62,
      35,    36,    33,    56,    80,    36,   135,   136,    36,    37,
      36,    37,    16,   117,    67,    84,    85,    86,    87,    88,
      89,    32,    91,    92,    93,    36,    95,    96,    97,    98,
     258,   100,   101,   102,    32,   135,   136,    33,    36,    67,
      82,    67,    84,    85,    86,   114,    73,    74,    75,    76,
      77,    44,    45,    46,    81,    82,    83,    65,    60,    60,
      53,    88,    64,    64,    33,    78,    79,    36,   137,   135,
     136,    33,    99,    33,    36,    88,    36,    90,   105,   106,
     107,    94,   377,    33,    34,   380,   113,   140,    65,    84,
      85,    86,    87,    88,    89,   108,    91,    92,    93,   331,
      95,    96,    97,    98,    33,   100,   101,   102,    65,    88,
      32,    33,   139,    35,    36,    66,    60,   109,    62,   114,
     112,   121,   122,    88,    60,   138,   105,   119,   120,    60,
     109,    32,    33,    65,    35,    36,    60,   116,   132,   133,
     134,   120,   137,    88,   109,    67,   111,   112,    65,   141,
      65,   116,   117,   118,   119,    36,    37,    60,    61,    65,
     321,    60,    61,   324,   109,   110,   111,   112,    60,    61,
      60,   116,   117,   118,   119,    47,    60,    49,    50,    51,
      52,    60,    61,    55,    60,    61,    60,    59,    40,    41,
      65,    32,    65,   141,    32,    16,    46,    63,    37,    63,
      37,    32,    65,    33,    60,    67,    67,    67,    65,    37,
      65,    65,    65,    37,    65,    61,   268,    61,    67,    67,
      65,   332,    62,   260,    60,    60,    13,   205,   203,   335,
     375,   201,   330,   197,    67,   207,    83,   330,   199,    -1,
     339
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   144,     0,     1,     3,     4,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    17,    18,    20,    21,
      22,    24,    25,    26,    27,    29,    30,    31,   135,   136,
     146,   147,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   233,   234,   140,    16,    44,    45,
      53,    54,    33,    44,    45,    46,    53,   190,    33,    36,
      47,    49,    50,    51,    52,    55,    59,    36,    57,   190,
      67,   161,   162,   162,   162,    33,    36,    33,    34,    33,
      36,    76,   115,   209,   229,   209,   162,    58,    95,   208,
      36,    80,   204,   205,   214,   227,   121,   122,   206,   207,
     228,    16,   209,    78,    79,    88,    90,    94,   108,   138,
     200,   201,   212,   215,   225,    73,    74,    75,    76,    77,
      81,    82,    83,    88,    99,   105,   106,   107,   113,   139,
     192,   195,   210,   216,   217,    88,   105,   109,   116,   120,
     193,   194,   211,   218,    88,    93,   230,   231,   237,   109,
     142,   230,   200,   162,    32,    36,   159,   160,   162,   162,
     162,    65,     6,    23,    36,    37,    36,    37,    67,    36,
      37,    67,    33,    33,    65,    65,    66,    60,    65,    60,
      65,    60,    65,    60,    65,    60,    65,    60,    65,   141,
      61,    61,    32,    36,    32,    36,    32,    33,    35,    56,
      67,   140,   132,   133,   134,    32,    32,    33,    35,    36,
     238,    33,    67,   148,   149,   205,   238,   207,   238,   201,
     238,   195,    32,    33,    35,    36,   160,   239,   194,   239,
      36,   231,   232,   238,    32,    16,   175,   189,    46,   176,
     177,    63,    37,    63,    37,    60,    61,    60,    61,    65,
      32,   191,    62,   189,    84,    85,    86,    87,    88,    89,
      91,    92,    93,    95,    96,    97,    98,   100,   101,   102,
     114,   137,   202,   203,   213,   226,   200,    62,   176,    88,
     109,   111,   112,   116,   117,   118,   119,   196,   197,   219,
      67,   109,   112,   119,   120,   141,   224,   235,   236,    67,
      33,   145,   146,    67,   145,    32,    33,    35,    36,    67,
      60,    65,    61,    65,    65,    60,    64,    65,    65,    60,
      64,    62,   146,    37,    62,    37,   203,   232,   238,   175,
      38,    39,   117,   220,   221,    40,    41,   222,   223,   110,
     197,   239,   239,   236,    67,    67,    62,    65,    61,    61,
     198,   199,    33,    36,   240,    60,    62,    60,   198,   240,
      60,   240,    62
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 255 "parser_gram.y"
    {
	if ((yyvsp[(2) - (2)].cmd)->cmd)
		(yyvsp[(2) - (2)].cmd)->cmd((yyvsp[(2) - (2)].cmd));

	free((yyvsp[(2) - (2)].cmd));
}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 262 "parser_gram.y"
    {
	if (dofile == DOFILE_TRUE)
		YYABORT;
}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 269 "parser_gram.y"
    {
	filebench_log(LOG_DEBUG_IMPL, "inner_command %zx", (yyvsp[(1) - (1)].cmd));
	(yyval.cmd) = (yyvsp[(1) - (1)].cmd);
}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 274 "parser_gram.y"
    {
	cmd_t *list = NULL;
	cmd_t *list_end = NULL;

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].cmd); list != NULL;
	    list = list->cmd_next)
		list_end = list;

	list_end->cmd_next = (yyvsp[(2) - (2)].cmd);

	filebench_log(LOG_DEBUG_IMPL,
	    "inner_commands adding cmd %zx to list %zx", (yyvsp[(2) - (2)].cmd), (yyvsp[(1) - (2)].cmd));

	(yyval.cmd) = (yyvsp[(1) - (2)].cmd);
}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 325 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	filebench_log(LOG_DEBUG_IMPL, "foreach_command %zx", (yyval.cmd));
}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 331 "parser_gram.y"
    {
	cmd_t *inner_cmd;
	list_t *list;

	(yyval.cmd) = (yyvsp[(1) - (7)].cmd);
	(yyval.cmd)->cmd_list = (yyvsp[(6) - (7)].cmd);
	(yyval.cmd)->cmd_tgt1 = (yyvsp[(2) - (7)].sval);
	(yyval.cmd)->cmd_param_list = (yyvsp[(4) - (7)].list);
	(yyval.cmd)->cmd = parser_foreach_integer;

	for (list = (yyval.cmd)->cmd_param_list; list != NULL;
	    list = list->list_next) {
		for (inner_cmd = (yyval.cmd)->cmd_list;
		    inner_cmd != NULL;
		    inner_cmd = inner_cmd->cmd_next) {
			filebench_log(LOG_DEBUG_IMPL,
			    "packing foreach: %zx %s=%llu, cmd %zx",
			    (yyval.cmd), (yyval.cmd)->cmd_tgt1,
			    (u_longlong_t)avd_get_int(list->list_integer),
			    inner_cmd);
		}
	}
}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 354 "parser_gram.y"
    {
	cmd_t *inner_cmd;
	list_t *list;

	(yyval.cmd) = (yyvsp[(1) - (7)].cmd);
	(yyval.cmd)->cmd_list = (yyvsp[(6) - (7)].cmd);
	(yyval.cmd)->cmd_tgt1 = (yyvsp[(2) - (7)].sval);
	(yyval.cmd)->cmd_param_list = (yyvsp[(4) - (7)].list);
	(yyval.cmd)->cmd = parser_foreach_string;

	for (list = (yyval.cmd)->cmd_param_list; list != NULL;
	    list = list->list_next) {
		for (inner_cmd = (yyval.cmd)->cmd_list;
		    inner_cmd != NULL;
		    inner_cmd = inner_cmd->cmd_next) {
			filebench_log(LOG_DEBUG_IMPL,
			    "packing foreach: %zx %s=%s, cmd %zx",
			    (yyval.cmd),
			    (yyval.cmd)->cmd_tgt1,
			    *list->list_string, inner_cmd);
		}
	}
}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 379 "parser_gram.y"
    {
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_integer = avd_int_alloc((yyvsp[(1) - (1)].ival));
}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 386 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_integer = avd_int_alloc((yyvsp[(3) - (3)].ival));

	/* Find end of list */
	for (list = (yyvsp[(1) - (3)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (3)].list);
}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 404 "parser_gram.y"
    {
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (3)].sval));
}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 411 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	if (((yyval.list) = alloc_list()) == NULL)
			YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(4) - (5)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (5)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (5)].list);
}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 429 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_eventgen;
}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 435 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 440 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(2) - (2)].list);
	(yyval.cmd)->cmd = parser_system;
}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 449 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(2) - (2)].list);
	(yyval.cmd)->cmd = parser_echo;
}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 458 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_version;
}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 465 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_osprof_enable;
}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 472 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_osprof_disable;
}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 479 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(2) - (2)].list);
	(yyval.cmd)->cmd = parser_usage;
}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 488 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd = parser_enable_mc;
}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 495 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 500 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd = parser_domultisync;
	(yyval.cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 533 "parser_gram.y"
    {
	if (((yyval.list) = alloc_list()) == NULL)
			YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(1) - (1)].sval));
}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 540 "parser_gram.y"
    {
	if (((yyval.list) = alloc_list()) == NULL)
			YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(1) - (1)].sval));
}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 548 "parser_gram.y"
    {
	(yyval.list) = (yyvsp[(1) - (1)].list);
}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 551 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add string */
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (2)].list);

}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 569 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add variable */
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (2)].list);
}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 586 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add string */
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (2)].list);

}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 604 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add variable */
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (2)].list);
}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 623 "parser_gram.y"
    {
	if (((yyval.list) = alloc_list()) == NULL)
			YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));
}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 630 "parser_gram.y"
    {
	if (((yyval.list) = alloc_list()) == NULL)
			YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));
}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 638 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add string */
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (2)].list);

}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 656 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add variable */
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (2)].list);
}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 673 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add string */
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (2)].list);

}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 691 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add variable */
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (2)].list);
}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 708 "parser_gram.y"
    {
	(yyval.list) = (yyvsp[(1) - (2)].list);
}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 711 "parser_gram.y"
    {
	(yyval.list) = (yyvsp[(1) - (2)].list);
}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 716 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_list;
}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 722 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd = &parser_flowop_list;
}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 727 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_fscheck;

	(yyval.cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 735 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list->attr_next = (yyvsp[(2) - (2)].attr);
}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 740 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_fsflush;

	(yyval.cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 749 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_log;
	(yyval.cmd)->cmd_param_list = (yyvsp[(2) - (2)].list);
}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 757 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = NULL;
	filebench_shm->shm_debug_level = (yyvsp[(2) - (2)].ival);
	if (filebench_shm->shm_debug_level > 9)
		yydebug = 1;
}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 769 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	var_assign_integer((yyvsp[(2) - (4)].sval), (yyvsp[(4) - (4)].ival));

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 780 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	var_assign_boolean((yyvsp[(2) - (4)].sval), (yyvsp[(4) - (4)].bval));

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 790 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	var_assign_string((yyvsp[(2) - (6)].sval), (yyvsp[(5) - (6)].sval));

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 799 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	var_assign_string((yyvsp[(2) - (4)].sval), (yyvsp[(4) - (4)].sval));

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 810 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	(yyval.cmd)->cmd_attr_list = (yyvsp[(6) - (7)].attr);
	(yyval.cmd)->cmd = NULL;

	parser_var_assign_randvar((yyvsp[(2) - (7)].sval), (yyval.cmd));
}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 822 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	(yyval.cmd)->cmd_attr_list = (yyvsp[(6) - (7)].attr);
	(yyval.cmd)->cmd = NULL;

	parser_var_assign_cvar((yyvsp[(2) - (7)].sval), (yyval.cmd));
}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 834 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	filebench_shm->shm_rmode = FILEBENCH_MODE_TIMEOUT;

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 844 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	filebench_shm->shm_rmode = FILEBENCH_MODE_QALLDONE;

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 854 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	filebench_shm->shm_rmode = FILEBENCH_MODE_Q1STDONE;

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 864 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	filebench_log(LOG_INFO, "Disabling CPU usage statistics");
	filebench_shm->shm_mmode |= FILEBENCH_MODE_NOUSAGE;

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 876 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = (void (*)(struct cmd *))&parser_statssnap;
	break;

}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 884 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = (void (*)(struct cmd *))&stats_clear;

}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 891 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd_param_list = (yyvsp[(3) - (3)].list);
	(yyval.cmd)->cmd = (void (*)(struct cmd *))&parser_directory;

}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 899 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(3) - (3)].list);
	(yyval.cmd)->cmd = parser_statscmd;

}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 907 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(3) - (3)].list);
	(yyval.cmd)->cmd = parser_statsdump;
}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 914 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(3) - (3)].list);
	(yyval.cmd)->cmd = parser_statsxmldump;
}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 921 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(3) - (3)].list);
	(yyval.cmd)->cmd = parser_statsmultidump;
}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 930 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_filebench_shutdown;
}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 937 "parser_gram.y"
    {
	(yyval.cmd) = (yyvsp[(1) - (1)].cmd);
}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 940 "parser_gram.y"
    {
	cmd_t *list = NULL;
	cmd_t *list_end = NULL;

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].cmd); list != NULL;
	    list = list->cmd_next)
		list_end = list;

	list_end->cmd_next = (yyvsp[(2) - (2)].cmd);

	filebench_log(LOG_DEBUG_IMPL,
	    "flowop_list adding cmd %zx to list %zx", (yyvsp[(2) - (2)].cmd), (yyvsp[(1) - (2)].cmd));

	(yyval.cmd) = (yyvsp[(1) - (2)].cmd);
}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 958 "parser_gram.y"
    {
	/*
	 * Allocate a cmd node per thread, with a
	 * list of flowops attached to the cmd_list
	 */
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd_list = (yyvsp[(4) - (5)].cmd);
	(yyval.cmd)->cmd_attr_list = (yyvsp[(2) - (5)].attr);
}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 970 "parser_gram.y"
    {
	(yyval.cmd) = (yyvsp[(1) - (1)].cmd);
}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 973 "parser_gram.y"
    {
	cmd_t *list = NULL;
	cmd_t *list_end = NULL;

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].cmd); list != NULL;
	    list = list->cmd_next)
		list_end = list;

	list_end->cmd_next = (yyvsp[(2) - (2)].cmd);

	filebench_log(LOG_DEBUG_IMPL,
	    "thread_list adding cmd %zx to list %zx", (yyvsp[(2) - (2)].cmd), (yyvsp[(1) - (2)].cmd));

	(yyval.cmd) = (yyvsp[(1) - (2)].cmd);
}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 991 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_proc_define;
	(yyval.cmd)->cmd_list = (yyvsp[(5) - (6)].cmd);
	(yyval.cmd)->cmd_attr_list = (yyvsp[(3) - (6)].attr);

}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1000 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1005 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	(yyval.cmd)->cmd = &parser_file_define;
}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1012 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	(yyval.cmd)->cmd = &parser_fileset_define;
}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1020 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1025 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_posset_define;
}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1030 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1035 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_composite_flowop_define;
	(yyval.cmd)->cmd_list = (yyvsp[(5) - (6)].cmd);
	(yyval.cmd)->cmd_attr_list = (yyvsp[(3) - (6)].attr);
}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1043 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1048 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	switch ((yyvsp[(2) - (2)].ival)) {
	case FSE_PROC:
		(yyval.cmd)->cmd = &parser_proc_create;
		break;
	case FSE_FILESET:
	case FSE_FILE:
		(yyval.cmd)->cmd = &parser_fileset_create;
		break;
	default:
		filebench_log(LOG_ERROR, "unknown entity", (yyvsp[(2) - (2)].ival));
		YYERROR;
	}

}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1067 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	switch ((yyvsp[(2) - (2)].ival)) {
	case FSE_PROC:
		(yyval.cmd)->cmd = &parser_proc_shutdown;
		break;
	case FSE_FILE:
	case FSE_FILESET:
		(yyval.cmd)->cmd = &parser_fileset_shutdown;
		break;
	default:
		filebench_log(LOG_ERROR, "unknown entity", (yyvsp[(2) - (2)].ival));
		YYERROR;
	}

}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1086 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_warmup;
	(yyval.cmd)->cmd_qty = (yyvsp[(2) - (2)].ival);
}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1093 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_warmup_variable;
	(yyval.cmd)->cmd_tgt1 = fb_stralloc((yyvsp[(2) - (2)].sval));
}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1101 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_sleep;
	(yyval.cmd)->cmd_qty = (yyvsp[(2) - (2)].ival);
}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1108 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_sleep_variable;
	(yyval.cmd)->cmd_tgt1 = fb_stralloc((yyvsp[(2) - (2)].sval));
}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1115 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_sleep;
	(yyval.cmd)->cmd_qty = 0;
}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1123 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_run;
	(yyval.cmd)->cmd_qty = (yyvsp[(2) - (2)].ival);
}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1130 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_run_variable;
	(yyval.cmd)->cmd_tgt1 = fb_stralloc((yyvsp[(2) - (2)].sval));
}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1137 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_run;
	(yyval.cmd)->cmd_qty = 0;
}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1145 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_psrun;
	(yyval.cmd)->cmd_qty1 = 0;
	(yyval.cmd)->cmd_qty = 0;
}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1153 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_psrun;
	(yyval.cmd)->cmd_qty1 = (yyvsp[(2) - (2)].ival);
	(yyval.cmd)->cmd_qty = 0;

}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1162 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_psrun;
	(yyval.cmd)->cmd_qty1 = (yyvsp[(2) - (2)].ival);
	(yyval.cmd)->cmd_qty = 0;

}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1171 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_psrun;
	(yyval.cmd)->cmd_qty1 = (yyvsp[(2) - (3)].ival);
	(yyval.cmd)->cmd_qty = (yyvsp[(3) - (3)].ival);
}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1179 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_psrun;
	(yyval.cmd)->cmd_qty1 = (yyvsp[(2) - (3)].ival);
	(yyval.cmd)->cmd_qty = (yyvsp[(3) - (3)].ival);
}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1188 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_help;
}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1195 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd_name = fb_stralloc((yyvsp[(2) - (2)].sval));
}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1201 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1205 "parser_gram.y"
    {(yyval.ival) = FSE_PROC;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1206 "parser_gram.y"
    {(yyval.ival) = FSE_THREAD;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1207 "parser_gram.y"
    {(yyval.ival) = FSE_FILESET;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1208 "parser_gram.y"
    {(yyval.ival) = FSE_FILE;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1218 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1222 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr; attr = attr->attr_next)
		list_end = attr;

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1235 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1239 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1253 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1258 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1265 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1270 "parser_gram.y"
    {
	(yyval.attr) = alloc_attr();
	if (!(yyval.attr))
		YYERROR;

	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1280 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1284 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1297 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (7)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	
	if ((attr = alloc_attr()) == NULL)
		YYERROR;

	attr->attr_name = FSA_RANDTABLE;
	attr->attr_obj = (void *)(yyvsp[(6) - (7)].rndtb);
	list_end->attr_next = attr;
	(yyval.attr) = (yyvsp[(1) - (7)].attr);
}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1316 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1321 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1327 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = FSA_TYPE;
}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1332 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = FSA_RANDSRC;
}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1338 "parser_gram.y"
    {
	if (((yyval.rndtb) = alloc_probtabent()) == NULL)
		YYERROR;
	(yyval.rndtb)->pte_percent = (yyvsp[(2) - (7)].avd);
	(yyval.rndtb)->pte_segmin  = (yyvsp[(4) - (7)].avd);
	(yyval.rndtb)->pte_segmax  = (yyvsp[(6) - (7)].avd);
}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1348 "parser_gram.y"
    {
	(yyval.rndtb) = (yyvsp[(1) - (1)].rndtb);
}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1352 "parser_gram.y"
    {
	probtabent_t *pte = NULL;
	probtabent_t *ptelist_end = NULL;

	for (pte = (yyvsp[(1) - (3)].rndtb); pte != NULL;
	    pte = pte->pte_next)
		ptelist_end = pte; /* Find end of prob table entry list */

	ptelist_end->pte_next = (yyvsp[(3) - (3)].rndtb);

	(yyval.rndtb) = (yyvsp[(1) - (3)].rndtb);
}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1367 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1371 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1385 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1390 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1398 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1402 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1415 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1429 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1434 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1442 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1446 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1460 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1465 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1473 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1477 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1491 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1497 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = FSA_VALUE;
}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1503 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_str_alloc((yyvsp[(3) - (3)].sval));
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1528 "parser_gram.y"
    { (yyval.ival) = FSA_NICE;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1529 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1530 "parser_gram.y"
    { (yyval.ival) = FSA_INSTANCES;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1533 "parser_gram.y"
    { (yyval.ival) = FSA_SIZE;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1534 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1535 "parser_gram.y"
    { (yyval.ival) = FSA_PATH;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1536 "parser_gram.y"
    { (yyval.ival) = FSA_READONLY;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1537 "parser_gram.y"
    { (yyval.ival) = FSA_TRUSTTREE;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1538 "parser_gram.y"
    { (yyval.ival) = FSA_REUSE;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1539 "parser_gram.y"
    { (yyval.ival) = FSA_PREALLOC;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1540 "parser_gram.y"
    { (yyval.ival) = FSA_PARALLOC;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1541 "parser_gram.y"
    { (yyval.ival) = FSA_WRITEONLY;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1544 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1545 "parser_gram.y"
    { (yyval.ival) = FSA_PATH;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1546 "parser_gram.y"
    { (yyval.ival) = FSA_ENTRIES;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1547 "parser_gram.y"
    { (yyval.ival) = FSA_SIZE;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1548 "parser_gram.y"
    { (yyval.ival) = FSA_DIRWIDTH;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1549 "parser_gram.y"
    { (yyval.ival) = FSA_DIRDEPTHRV;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1550 "parser_gram.y"
    { (yyval.ival) = FSA_PREALLOC;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1551 "parser_gram.y"
    { (yyval.ival) = FSA_PARALLOC;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1552 "parser_gram.y"
    { (yyval.ival) = FSA_REUSE;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1553 "parser_gram.y"
    { (yyval.ival) = FSA_READONLY;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1554 "parser_gram.y"
    { (yyval.ival) = FSA_TRUSTTREE;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1555 "parser_gram.y"
    { (yyval.ival) = FSA_DIRGAMMA;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1556 "parser_gram.y"
    { (yyval.ival) = FSA_CACHED;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1557 "parser_gram.y"
    { (yyval.ival) = FSA_LEAFDIRS;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1558 "parser_gram.y"
    { (yyval.ival) = FSA_WRITEONLY;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1561 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1562 "parser_gram.y"
    { (yyval.ival) = FSA_TYPE;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1563 "parser_gram.y"
    { (yyval.ival) = FSA_RANDSEED;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1564 "parser_gram.y"
    { (yyval.ival) = FSA_ENTRIES;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1565 "parser_gram.y"
    { (yyval.ival) = FSA_MAX;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1568 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1569 "parser_gram.y"
    { (yyval.ival) = FSA_RANDSEED;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1570 "parser_gram.y"
    { (yyval.ival) = FSA_RANDGAMMA;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1571 "parser_gram.y"
    { (yyval.ival) = FSA_RANDMEAN;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1572 "parser_gram.y"
    { (yyval.ival) = FSA_MIN;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1573 "parser_gram.y"
    { (yyval.ival) = FSA_ROUND;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1592 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_int_alloc((yyvsp[(1) - (1)].ival));
}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1599 "parser_gram.y"
    { (yyval.ival) = FSV_RANDUNI;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1600 "parser_gram.y"
    { (yyval.ival) = FSV_RANDTAB;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1601 "parser_gram.y"
    { (yyval.ival) = FSA_RANDGAMMA;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1604 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_int_alloc((yyvsp[(1) - (1)].ival));
}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1611 "parser_gram.y"
    { (yyval.ival) = FSV_URAND;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1612 "parser_gram.y"
    { (yyval.ival) = FSV_RAND48;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1615 "parser_gram.y"
    { (yyval.ival) = FSA_TYPE;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1616 "parser_gram.y"
    { (yyval.ival) = FSA_PARAMETERS;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1617 "parser_gram.y"
    { (yyval.ival) = FSA_MIN;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1618 "parser_gram.y"
    { (yyval.ival) = FSA_MAX;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1619 "parser_gram.y"
    { (yyval.ival) = FSA_ROUND;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1622 "parser_gram.y"
    { (yyval.ival) = FSA_PROCESS;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1623 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1624 "parser_gram.y"
    { (yyval.ival) = FSA_MEMSIZE;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1625 "parser_gram.y"
    { (yyval.ival) = FSA_USEISM;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1626 "parser_gram.y"
    { (yyval.ival) = FSA_INSTANCES;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1627 "parser_gram.y"
    { (yyval.ival) = FSA_IOPRIO;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1630 "parser_gram.y"
    { (yyval.ival) = FSA_WSS;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1631 "parser_gram.y"
    { (yyval.ival) = FSA_FILE;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 1632 "parser_gram.y"
    { (yyval.ival) = FSA_POSSET;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 1633 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 1634 "parser_gram.y"
    { (yyval.ival) = FSA_RANDOM;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 1635 "parser_gram.y"
    { (yyval.ival) = FSA_FD;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 1636 "parser_gram.y"
    { (yyval.ival) = FSA_SRCFD;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 1637 "parser_gram.y"
    { (yyval.ival) = FSA_ROTATEFD;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 1638 "parser_gram.y"
    { (yyval.ival) = FSA_DSYNC;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 1639 "parser_gram.y"
    { (yyval.ival) = FSA_DIRECTIO;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 1640 "parser_gram.y"
    { (yyval.ival) = FSA_INDEXED;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 1641 "parser_gram.y"
    { (yyval.ival) = FSA_TARGET;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 1642 "parser_gram.y"
    { (yyval.ival) = FSA_ITERS;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 1643 "parser_gram.y"
    { (yyval.ival) = FSA_VALUE;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 1644 "parser_gram.y"
    { (yyval.ival) = FSA_BLOCKING;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 1645 "parser_gram.y"
    { (yyval.ival) = FSA_HIGHWATER;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 1646 "parser_gram.y"
    { (yyval.ival) = FSA_IOSIZE;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 1647 "parser_gram.y"
    { (yyval.ival) = FSA_NOREADAHEAD;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 1650 "parser_gram.y"
    { (yyval.ival) = FSA_RATE;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 1653 "parser_gram.y"
    { (yyval.ival) = FSA_MASTER;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 1654 "parser_gram.y"
    { (yyval.ival) = FSA_CLIENT;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 1657 "parser_gram.y"
    { (yyval.ival) = FSA_PATH;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 1658 "parser_gram.y"
    { (yyval.ival) = FSA_FSTYPE;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 1661 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 1665 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 1678 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 1692 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 1698 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_lvar_attr(var_lvar_assign_boolean((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].bval)))) == NULL)
		YYERROR;
}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 1703 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_lvar_attr(var_lvar_assign_integer((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].ival)))) == NULL)
		YYERROR;
}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 1708 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_lvar_attr(var_lvar_assign_string((yyvsp[(1) - (5)].sval), (yyvsp[(4) - (5)].sval)))) == NULL)
		YYERROR;
}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 1713 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_lvar_attr(var_lvar_assign_string((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval)))) == NULL)
		YYERROR;
}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 1718 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_lvar_attr(var_lvar_assign_var((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval)))) == NULL)
		YYERROR;
}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 1723 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_lvar_attr(var_lvar_alloc_local((yyvsp[(1) - (1)].sval)))) == NULL)
		YYERROR;
}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 1729 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();

	if (!(yyval.cmd))
		YYERROR;

	(yyval.cmd)->cmd = NULL;

	(void) parser_list_cvar_types();
}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 1741 "parser_gram.y"
    {
	attr_t *attr;

	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	if ((attr = alloc_attr()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd = &parser_list_cvar_type_parameters;
	attr->attr_avd = avd_str_alloc((yyvsp[(5) - (5)].sval));
	(yyval.cmd)->cmd_attr_list = attr;	
}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 1755 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_composite_flowop_define;
	(yyval.cmd)->cmd_list = (yyvsp[(5) - (6)].cmd);
	(yyval.cmd)->cmd_attr_list = (yyvsp[(3) - (6)].attr);
}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 1763 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 1769 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 1773 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 1787 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 1793 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 1794 "parser_gram.y"
    { (yyval.ival) = FSA_ITERS;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 1797 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_str_alloc((yyvsp[(1) - (1)].sval));
}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 1801 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_int_alloc((yyvsp[(1) - (1)].ival));
}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 1805 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_bool_alloc((yyvsp[(1) - (1)].bval));
}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 1809 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_var_alloc((yyvsp[(1) - (1)].sval));
}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 1815 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_param_list = (yyvsp[(1) - (1)].list);
}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 1819 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_str_alloc((yyvsp[(1) - (1)].sval));
}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 1823 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_int_alloc((yyvsp[(1) - (1)].ival));
}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 1827 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_bool_alloc((yyvsp[(1) - (1)].bval));
}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 1831 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_var_alloc((yyvsp[(1) - (1)].sval));
}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 1838 "parser_gram.y"
    {
	(yyval.avd) = avd_int_alloc((yyvsp[(1) - (1)].ival));
}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 1841 "parser_gram.y"
    {
	(yyval.avd) = avd_var_alloc((yyvsp[(1) - (1)].sval));
}
    break;



/* Line 1455 of yacc.c  */
#line 4920 "parser_gram.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1845 "parser_gram.y"


/*
 * The following C routines implement the various commands defined in the above
 * yacc parser code. The yacc portion checks the syntax of the commands found in
 * a workload file (or typed interactively) and parses the commands' parameters
 * into lists. The lists are then passed in a cmd_t struct for each command to
 * its related routine in the following section for actual execution.  This
 * section also includes a few utility routines and the main entry point for the
 * program.
 */

#define	USAGE1	\
"Usage:\n" \
"filebench: interprets WML script and generates apporpriate workload\n" \
"Options:\n" \
"   [-h] Display verbose help\n" \
"   [-f <filename>] use specified file as an input instead of stdin\n"

#define	PARSER_CMDS \
"create [files|filesets|processes]\n" \
"stats [clear|snap]\n" \
"stats command \"shell command $var1,$var2...\"\n" \
"stats directory <directory>\n" \
"sleep <sleep-value>\n" \
"quit\n\n" \
"Variables:\n" \
"set $var = value\n" \
"    $var   - regular variables\n" \
"    ${var} - internal special variables\n" \
"    $(var) - environment variables\n\n"

#define	PARSER_EXAMPLE \
"Example:\n\n" \
"#!" FILEBENCHDIR "/bin/filebench -f\n" \
"\n" \
"define file name=bigfile,path=bigfile,size=1g,prealloc,reuse\n" \
"define process name=randomizer\n" \
"{\n" \
"  thread random-thread procname=randomizer\n"	\
"  {\n" \
"    flowop read name=random-read,filename=bigfile,iosize=16k,random\n" \
"  }\n" \
"}\n" \
"create files\n" \
"create processes\n" \
"stats clear\n" \
"sleep 30\n" \
"stats snap\n"

/*
 * Displays brief or verbose help for Filebench.
 */
static void
usage(int help)
{
	if (help >= 1)
		(void) fprintf(stderr, USAGE1);

	if (help >= 2) {
		(void) fprintf(stderr,
		    "\n'f' language definition:\n\n");
		fileset_usage();
		procflow_usage();
		threadflow_usage();
		flowoplib_usage();
		eventgen_usage();
		(void) fprintf(stderr, PARSER_CMDS);
		(void) fprintf(stderr, PARSER_EXAMPLE);
	}

	exit(1);
}

/*
 * mmap() call with MAP_FIXED argument does not guarantee
 * that the allocated memory region is not overlapped with
 * the previously existant mappings. According to POSIX, old mappings
 * are just disregarded. There is no generic way to detect
 * overlap. If overlap occurs strange runtime errors might happen,
 * because we might overlap stack, libraries, anything else.
 *
 * Since we always fork+exec same binary (filebench), theoretically
 * all the mappings should be the same, so no overlap should happen.
 * However, if virtual address space randomization is enabled on the target
 * machine - overlap is very likely (especially if workload defines a lot of
 * processes).  We observed numerous segmentation faults on CentOS because of
 * that.
 *
 * The function below checks if virtual address space randomization is
 * enabled on Linux. In case it is enabled, we print a warning and continue
 * execution.
 */
static void
check_va_randomization()
{
	char buf[4];
	int val;
	int ret;
	int fd;

	fd = open("/proc/sys/kernel/randomize_va_space", O_RDONLY);
	if (fd == -1) {
		/*
		 * probably this file just doesn't exist, so we conclude that the
		 * system does not support virtual address space randomization
		 * and silently return.
		 */
		return;
	}

	ret = read(fd, buf, sizeof(buf));
	if (ret == -1) {
		filebench_log(LOG_FATAL, "Coud not read from "
			"/proc/sys/kernel/randomize_va_space file!");
		return;
	}

	sscanf(buf, "%d", &val);
	if (val != 0) {
		filebench_log(LOG_FATAL, "IMPORTANT: Virtual address space "
			"randomization is enabled on this machine!\n"
			"It is highly recommended to disable randomization "
			"to provide stable Filebench runs.\n"
			"Echo 0 to /proc/sys/kernel/randomize_va_space file "
			"to disable the randomization.");

	}
}

#ifdef HAVE_PROC_SYS_KERNEL_SHMMAX
/*
 * Increase the maximum shared memory segment size till some large value.  We do
 * not restore it to the old value when the Filebench run is over. If we could
 * not change the value - we continue execution.
 */
void
fb_set_shmmax(void)
{
	FILE *f;
	int ret;

	f = fopen("/proc/sys/kernel/shmmax", "r+");
	if (!f) {
		filebench_log(LOG_FATAL, "WARNING: Could not open "
				"/proc/sys/kernel/shmmax file!\n"
				"It means that you probably ran Filebench not "
				"as a root. Filebench will not increase shared\n"
				"region limits in this case, which can lead "
				"to the failures on certain workloads.");
		return; 
	}

	/* writing new value */
#define SOME_LARGE_SHMAX "268435456" /* 256 MB */
	ret = fwrite(SOME_LARGE_SHMAX, sizeof(SOME_LARGE_SHMAX), 1, f);
	if (ret != 1) 
		filebench_log(LOG_ERROR, "Coud not write to "
				"/proc/sys/kernel/shmmax file!");
#undef SOME_LARGE_SHMAX

	return;
}
#else /* HAVE_PROC_SYS_KERNEL_SHMMAX */
void
fb_set_shmmax(void)
{
	return;
}
#endif /* HAVE_PROC_SYS_KERNEL_SHMMAX */

#ifdef HAVE_SETRLIMIT
/*
 * Increase the limit of opened files.
 *
 * We first set the limit to the hardlimit reported by the kernel; this call
 * will always succeed.  Then we try to set the limit to some large number of
 * files (unfortunately we can't set this ulimit to infinity), this will only
 * succeed if the process is ran by root.  Therefore, we always set the maximum
 * possible value for the limit for this given process (well, only if hardlimit
 * is greater then the large number of files defined by us, it is not true).
 *
 * Increasing this limit is especially important when we use thread model,
 * because opened files are accounted per-process, not per-thread.
 */
void
fb_set_rlimit(void)
{
	struct rlimit rlp;

	(void)getrlimit(RLIMIT_NOFILE, &rlp);
	rlp.rlim_cur = rlp.rlim_max;
	(void)setrlimit(RLIMIT_NOFILE, &rlp);
#define SOME_LARGE_NUMBER_OF_FILES 50000
	rlp.rlim_cur = rlp.rlim_max = SOME_LARGE_NUMBER_OF_FILES;
#undef SOME_LARGE_NUMBER_OF_FILES
	(void)setrlimit(RLIMIT_NOFILE, &rlp);
	return;
}
#else /* HAVE_SETRLIMIT */
void
fb_set_rlimit(void)
{
	return;
}
#endif /* HAVE_SETRLIMIT */

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
	const char cmd_options[] = "m:s:a:i:hf:";
	int opt;
	char *procname = NULL;
	int instance;
	void *shmaddr;
	char *cwdret;
	char *fscriptname = NULL;
#ifdef HAVE_LIBTECLA
	char *line;
#else /* HAVE_LIBTECLA */
	char line[1024];
#endif
	int ret;

	 /* parsing the parameters */
	while ((opt = getopt(argc, argv, cmd_options)) > 0) {
		switch (opt) {
		/* public parameters */
		case 'h':
			usage(2);
			break;
		case 'f':
			if (!optarg)
				usage(1);

			yyin = fopen(optarg, "r");
			if (!yyin) {
				filebench_log(LOG_FATAL,
				    "Cannot open file %s!", optarg);
				exit(1);
			}

			dofile = DOFILE_TRUE;
			fscriptname = optarg;
			break;
		/* private parameters: when filebench calls itself */
		case 'a':
			if (!optarg)
				usage(1);

			procname = optarg;
			break;
		case 's':
			if (!optarg)
				usage(1);
			sscanf(optarg, "%p", &shmaddr);
			break;
		case 'm':
			if (!optarg)
				usage(1);
			sscanf(optarg, "%s", shmpath);
			break;
		case 'i':
			if (!optarg)
				usage(1);
			sscanf(optarg, "%d", &instance);
			break;
		case '?':
		default:
			usage(1);
			break;
		}
	}

	/*
	 * Init things common to all processes: master and workers
	 */
	my_pid = getpid();
	fb_set_rlimit();
	fb_urandom_init();
	clock_init();

	if (procname) {
		/* A child Filebench instance */
		if (ipc_attach(shmaddr) < 0) {
			filebench_log(LOG_FATAL, "Cannot attach shm for %s",
			    procname);
			exit(1);
		}
		
		/* get correct function pointer for each working process */
		filebench_plugin_funcvecinit();
		
		/* Load custom variable libraries and re-validate handles. */
		ret = init_cvar_libraries();
		if (ret)
			exit(1);

		ret = revalidate_cvar_handles();
		if (ret)
			exit(1);

		/* execute corresponding procflow */
		if (procflow_exec(procname, instance) < 0) {
			filebench_log(LOG_FATAL, "Cannot startup process %s",
			    procname);
			exit(1);
		}

		exit(0);
	}

	/*
	 * Master process
	 */
	printf("Filebench Version %s\n", FILEBENCH_VERSION);
	check_va_randomization();

	/* saving executable name to exec it later as worker processes */
	execname = argv[0];

	/* saving current working directory */
	cwdret = getcwd(cwd, MAXPATHLEN);
	if (cwdret != cwd) {
		filebench_log(LOG_FATAL, "Cannot save current "
					 "working directory!");
		exit(1);
	}

	fb_set_shmmax();

	ipc_init();

	if (fscriptname)
		(void)strcpy(filebench_shm->shm_fscriptname, fscriptname);

	flowop_init();
	stats_init();
	eventgen_init();
	
	/* Initialize custom variables. */
	ret = init_cvar_library_info(FILEBENCHDIR "/cvars");
	if (ret)
		filebench_shutdown(1);

	ret = init_cvar_libraries();
	if (ret)
		filebench_shutdown(1);

	signal(SIGINT, parser_abort);

	if (dofile == DOFILE_TRUE)
		yyparse();
	else {
#ifdef HAVE_LIBTECLA
		if ((gl = new_GetLine(MAX_LINE_LEN, MAX_CMD_HIST)) == NULL) {
			filebench_log(LOG_ERROR,
			    "Failed to create GetLine object");
			filebench_shutdown(1);
		}

		if (gl_customize_completion(gl, NULL, command_complete)) {
			filebench_log(LOG_ERROR,
			    "Failed to register auto-completion function");
			filebench_shutdown(1);
		}

		while ((line = gl_get_line(gl, FILEBENCH_PROMPT, NULL, -1))) {
			arg_parse(line);
			yyparse();
		}

		del_GetLine(gl);
#else
		while (!feof(stdin)) {
			printf(FILEBENCH_PROMPT);
			fflush(stdout);
			if (fgets(line, sizeof (line), stdin) == NULL) {
				if (errno == EINTR)
					continue;
				else
					break;
			}
			arg_parse(line);
			yyparse();
		}
		printf("\n");
#endif	/* HAVE_LIBTECLA */
	}

	parser_filebench_shutdown((cmd_t *)0);

	return 0;
}

/*
 * arg_parse() puts the parser into command parsing mode. Create a tmpfile
 * and instruct the parser to read instructions from this location by setting
 * yyin to the value returned by tmpfile. Write the command into the file.
 * Then seek back to to the start of the file so that the parser can read
 * the instructions.
 */
static void
arg_parse(const char *command)
{
	if ((yyin = tmpfile()) == NULL) {
		filebench_log(LOG_FATAL,
		    "Exiting: Cannot create tmpfile: %s", strerror(errno));
		exit(1);
	}

	if (fwrite(command, strlen(command), 1, yyin) != 1)
		filebench_log(LOG_FATAL,
		    "Cannot write tmpfile: %s", strerror(errno));

	if (fseek(yyin, 0, SEEK_SET) != 0)
		filebench_log(LOG_FATAL,
		    "Cannot seek tmpfile: %s", strerror(errno));
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
	if ((string = malloc(MAXPATHLEN)) == NULL) {
		filebench_log(LOG_ERROR, "Failed to allocate memory");
		return (NULL);
	}

	*string = 0;

	/*	printf("parser_list2string: called\n"); */
	/* Format args */
	for (l = list; l != NULL; l = l->list_next) {
		char *lstr = avd_get_str(l->list_string);

		filebench_log(LOG_DEBUG_SCRIPT,
		    "converting string '%s'", lstr);

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
	return (string);
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
	if ((attr = get_attr_integer(cmd, FSA_RATE))) {
		if (attr->attr_avd) {
			eventgen_setrate(attr->attr_avd);
		}
	}
}

/*
 * Assigns the designated integer variable successive values from the
 * supplied comma seperated integer list. After each successive integer
 * assignment, it executes the bracket enclosed list of commands. For
 * example, repeated runs of a workload with increasing io sizes can
 * be done using the following command line:
 * 	foreach $iosize in 2k, 4k, 8k {run 60}
 */
static void
parser_foreach_integer(cmd_t *cmd)
{
	list_t *list = cmd->cmd_param_list;
	cmd_t *inner_cmd;

	for (; list != NULL; list = list->list_next) {
		fbint_t list_int = avd_get_int(list->list_integer);

		var_assign_integer(cmd->cmd_tgt1, list_int);
		filebench_log(LOG_VERBOSE, "Iterating %s=%llu",
		    cmd->cmd_tgt1, (u_longlong_t)list_int);
		for (inner_cmd = cmd->cmd_list; inner_cmd != NULL;
		    inner_cmd = inner_cmd->cmd_next) {
			inner_cmd->cmd(inner_cmd);
		}
	}
}

/*
 * Similar to parser_foreach_integer(), except takes a list of strings after
 * the "in" token. For example, to run twice using a different directory,
 * perhaps using a different filesystem, the following command line
 * could be used:
 * 	foreach $dir in "/ufs_top/fbt", "/zfs_top/fbt" {run 60)
 */
static void
parser_foreach_string(cmd_t *cmd)
{
	list_t *list = cmd->cmd_param_list;

	for (; list != NULL; list = list->list_next) {
		cmd_t *inner_cmd;
		char *lstr = avd_get_str(list->list_string);
		var_assign_string(cmd->cmd_tgt1, lstr);
		filebench_log(LOG_VERBOSE, "Iterating %s=%s",
		    cmd->cmd_tgt1, lstr);
		for (inner_cmd = cmd->cmd_list; inner_cmd != NULL;
		    inner_cmd = inner_cmd->cmd_next) {
			inner_cmd->cmd(inner_cmd);
		}
	}
}

/*
 * Lists the fileset name, path name and average size for all defined
 * filesets.
 */
static void
parser_list(cmd_t *cmd)
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

	/* Get the name of the process */
	if ((attr = get_attr(cmd, FSA_NAME))) {
		name = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "define proc: proc specifies no name");
		filebench_shutdown(1);
	}

	/* Get the memory size from attribute */
	if ((attr = get_attr_integer(cmd, FSA_INSTANCES))) {
		if (AVD_IS_RANDOM(attr->attr_avd)) {
			filebench_log(LOG_ERROR,
			    "proc_define: Instances attr cannot be random");
			filebench_shutdown(1);
		}
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

	if ((procflow = procflow_define(name, NULL, var_instances)) == NULL) {
		filebench_log(LOG_ERROR,
		    "Failed to instantiate %d %s process(es)\n",
		    instances, name);
		filebench_shutdown(1);
	}

	/* Get the pri from attribute */
	if ((attr = get_attr_integer(cmd, FSA_NICE))) {
		if (AVD_IS_RANDOM(attr->attr_avd)) {
			filebench_log(LOG_ERROR,
			    "proc_define: priority cannot be random");
			filebench_shutdown(1);
		}
		filebench_log(LOG_DEBUG_IMPL, "Setting pri = %llu",
		    (u_longlong_t)avd_get_int(attr->attr_avd));
		procflow->pf_nice = attr->attr_avd;
	} else
		procflow->pf_nice = avd_int_alloc(0);


	/* Create the list of threads for this process  */
	for (inner_cmd = cmd->cmd_list; inner_cmd != NULL;
	    inner_cmd = inner_cmd->cmd_next) {
		parser_thread_define(inner_cmd, procflow, instances);
	}
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
parser_thread_define(cmd_t *cmd, procflow_t *procflow, int procinstances)
{
	threadflow_t *threadflow, template;
	attr_t *attr;
	avd_t instances;
	cmd_t *inner_cmd;
	char *name = NULL;

	memset(&template, 0, sizeof (threadflow_t));

	/* Get the name of the thread */
	if ((attr = get_attr(cmd, FSA_NAME))) {
		name = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "define thread: thread in process %s specifies no name",
		    procflow->pf_name);
		filebench_shutdown(1);
	}

	/* Get the number of instances from attribute */
	if ((attr = get_attr_integer(cmd, FSA_INSTANCES))) {
		instances = attr->attr_avd;
	} else
		instances = avd_int_alloc(1);

	/* Get the memory size from attribute */
	if ((attr = get_attr_integer(cmd, FSA_MEMSIZE))) {
		template.tf_memsize = attr->attr_avd;
	} else
		template.tf_memsize = avd_int_alloc(0);

	/* Get ioprio parameters from attribute */
	if ((attr = get_attr_integer(cmd, FSA_IOPRIO))) {
		template.tf_ioprio = attr->attr_avd;
	} else
		template.tf_ioprio = avd_int_alloc(8);

	if ((threadflow = threadflow_define(procflow, name,
	    &template, instances)) == NULL) {
		filebench_log(LOG_ERROR,
		    "define thread: Failed to instantiate thread\n");
		filebench_shutdown(1);
	}

	/* Use ISM Memory? */
	if ((attr = get_attr(cmd, FSA_USEISM))) {
		threadflow->tf_attrs |= THREADFLOW_USEISM;
	}

	/* Create the list of flowops */
	for (inner_cmd = cmd->cmd_list; inner_cmd != NULL;
	    inner_cmd = inner_cmd->cmd_next) {
		parser_flowop_define(inner_cmd, threadflow,
		    &threadflow->tf_thrd_fops, FLOW_MASTER);
	}
}

/*
 * Fills in the attributes for a newly allocated flowop
 */
static void
parser_flowop_get_attrs(cmd_t *cmd, flowop_t *flowop)
{
	attr_t *attr;

	/* Get the filename from attribute */
	if ((attr = get_attr(cmd, FSA_FILE))) {
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

	/* Get the possetname from attribute */
	if ((attr = get_attr(cmd, FSA_POSSET))) {
		flowop->fo_possetname = attr->attr_avd;
		if (flowop->fo_possetname == NULL) {
			filebench_log(LOG_ERROR,
			    "parser_flowop_get_attrs: no "
				"posset name specfied");
			filebench_shutdown(1);
		}
	} else {
		/* no possetname attribute specified */
		flowop->fo_possetname = NULL;
	}

	/* Get the iosize of the op */
	if ((attr = get_attr_integer(cmd, FSA_IOSIZE)))
		flowop->fo_iosize = attr->attr_avd;
	else
		flowop->fo_iosize = avd_int_alloc(0);

	/* Get the working set size of the op */
	if ((attr = get_attr_integer(cmd, FSA_WSS)))
		flowop->fo_wss = attr->attr_avd;
	else
		flowop->fo_wss = avd_int_alloc(0);

	/* Random I/O? */
	if ((attr = get_attr_bool(cmd, FSA_RANDOM)))
		flowop->fo_random = attr->attr_avd;
	else
		flowop->fo_random = avd_bool_alloc(FALSE);

	/* Sync I/O? */
	if ((attr = get_attr_bool(cmd, FSA_DSYNC)))
		flowop->fo_dsync = attr->attr_avd;
	else
		flowop->fo_dsync = avd_bool_alloc(FALSE);

	/* Target, for wakeup etc */
	if ((attr = get_attr(cmd, FSA_TARGET)))
		(void) strcpy(flowop->fo_targetname,
		    avd_get_str(attr->attr_avd));

	/* Value */
	if ((attr = get_attr_integer(cmd, FSA_VALUE)))
		flowop->fo_value = attr->attr_avd;
	else
		flowop->fo_value = avd_int_alloc(0);

	/* FD */
	if ((attr = get_attr_integer(cmd, FSA_FD))) {
		flowop->fo_fdnumber = avd_get_int(attr->attr_avd);
		if (flowop->fo_filename != NULL)
			filebench_log(LOG_DEBUG_SCRIPT, "It is not "
			    "advisable to supply both an fd number "
			    "and a fileset name in most cases");
	}

	/* Rotatefd? */
	if ((attr = get_attr_bool(cmd, FSA_ROTATEFD)))
		flowop->fo_rotatefd = attr->attr_avd;
	else
		flowop->fo_rotatefd = avd_bool_alloc(FALSE);

	/* SRC FD, for copies etc... */
	if ((attr = get_attr_integer(cmd, FSA_SRCFD)))
		flowop->fo_srcfdnumber = avd_get_int(attr->attr_avd);

	/* Blocking operation? */
	if ((attr = get_attr_bool(cmd, FSA_BLOCKING)))
		flowop->fo_blocking = attr->attr_avd;
	else
		flowop->fo_blocking = avd_bool_alloc(FALSE);

	/* Direct I/O Operation */
	if ((attr = get_attr_bool(cmd, FSA_DIRECTIO)))
		flowop->fo_directio = attr->attr_avd;
	else
		flowop->fo_directio = avd_bool_alloc(FALSE);

	/* Highwater mark */
	if ((attr = get_attr_integer(cmd, FSA_HIGHWATER))) {
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
	if ((attr = get_attr_integer(cmd, FSA_INDEXED)))
		flowop->fo_fileindex = attr->attr_avd;
	else
		flowop->fo_fileindex = NULL;

	/* Read Ahead Diable */
	if ((attr = get_attr_bool(cmd, FSA_NOREADAHEAD)))
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
	if ((attr = get_attr_integer(cmd, FSA_ITERS)))
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
	if ((attr = get_attr_integer(cmd, FSA_ITERS)))
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
 * Calls fileset_define() to allocate a fileset with the supplied name and
 * initializes the fileset's pathname attribute, and optionally the
 * fileset_cached, fileset_reuse, fileset_prealloc and fileset_size attributes.
 *
 */
static fileset_t *
parser_fileset_define_common(cmd_t *cmd)
{
	fileset_t *fileset;
	avd_t name;
	attr_t *attr;
	avd_t pathname;

	/*
	 * Make sure all plugin flowops are initialized.
	 * Defaults to local fs for now
	 */
	flowop_plugin_flowinit();

	/* Get the name of the file */
	if ((attr = get_attr_fileset(cmd, FSA_NAME))) {
		name = attr->attr_avd;
	} else {
		filebench_log(LOG_ERROR,
		    "define fileset: file or fileset specifies no name");
		return (NULL);
	}

	if ((fileset = fileset_define(name)) == NULL) {
		filebench_log(LOG_ERROR,
		    "define file: failed to instantiate file %s\n",
		    avd_get_str(name));
		return (NULL);
	}

	/* Get the pathname from attribute */
	if ((attr = get_attr(cmd, FSA_PATH)) == NULL) {
		filebench_log(LOG_ERROR, "define file: no pathname specified");
		return (NULL);
	}

	/* Expand variables in pathname */
	if ((pathname = parser_list2varstring(attr->attr_param_list))
	    == NULL) {
		filebench_log(LOG_ERROR, "Cannot interpret path");
		return (NULL);
	}

	fileset->fs_path = pathname;

	/* How much should we preallocate? */
	if ((attr = get_attr_integer(cmd, FSA_PREALLOC)) &&
	    attr->attr_avd) {
		if (AVD_IS_RANDOM(attr->attr_avd)) {
			filebench_log(LOG_ERROR,
			    "define fileset: Prealloc attr cannot be random");
			filebench_shutdown(1);
		}
		fileset->fs_preallocpercent = attr->attr_avd;
	} else if (attr && !attr->attr_avd) {
		fileset->fs_preallocpercent = avd_int_alloc(100);
	} else {
		fileset->fs_preallocpercent = avd_int_alloc(0);
	}

	/* Should we preallocate? */
	if ((attr = get_attr_bool(cmd, FSA_PREALLOC)))
		fileset->fs_prealloc = attr->attr_avd;
	else
		fileset->fs_prealloc = avd_bool_alloc(FALSE);

	/* Should we prealloc in parallel? */
	if ((attr = get_attr_bool(cmd, FSA_PARALLOC)))
		fileset->fs_paralloc = attr->attr_avd;
	else
		fileset->fs_paralloc = avd_bool_alloc(FALSE);

	/* Should we allow writes to the file? */
	if ((attr = get_attr_bool(cmd, FSA_READONLY)))
		fileset->fs_readonly = attr->attr_avd;
	else
		fileset->fs_readonly = avd_bool_alloc(FALSE);

	if ((attr = get_attr_bool(cmd, FSA_WRITEONLY)))
		fileset->fs_writeonly = attr->attr_avd;
	else
		fileset->fs_writeonly = avd_bool_alloc(FALSE);

	if ((avd_get_bool(fileset->fs_readonly) == TRUE) &&
		(avd_get_bool(fileset->fs_writeonly) == TRUE)) {
		filebench_log(LOG_ERROR, "fileset can't be read-only and "
					"write-only at the same time!");
		return NULL;
	}

	/* Should we reuse the existing file? */
	if ((attr = get_attr_bool(cmd, FSA_REUSE)))
		fileset->fs_reuse = attr->attr_avd;
	else
		fileset->fs_reuse = avd_bool_alloc(FALSE);

	/* Should we check for files actual existance? */
	if ((attr = get_attr_bool(cmd, FSA_TRUSTTREE)))
		fileset->fs_trust_tree = attr->attr_avd;
	else
		fileset->fs_trust_tree = avd_bool_alloc(FALSE);

	/* Should we leave in cache? */
	if ((attr = get_attr_bool(cmd, FSA_CACHED)))
		fileset->fs_cached = attr->attr_avd;
	else
		fileset->fs_cached = avd_bool_alloc(FALSE);

	/* Get the mean or absolute size of the file */
	if ((attr = get_attr_integer(cmd, FSA_SIZE)))
		fileset->fs_size = attr->attr_avd;
	else
		fileset->fs_size = avd_int_alloc(0);

	return (fileset);
}

/*
 * Calls parser_fileset_define_common() to allocate a fileset with
 * one entry and optionally the fileset_prealloc. sets the fileset_entries,
 * fileset_dirwidth, fileset_dirgamma, and fileset_sizegamma attributes
 * to appropriate values for emulating the old "fileobj" entity
 */
static void
parser_file_define(cmd_t *cmd)
{
	fileset_t *fileset;

	if ((fileset = parser_fileset_define_common(cmd)) == NULL) {
		filebench_log(LOG_ERROR,
		    "define file: failed to instantiate file");
		filebench_shutdown(1);
		return;
	}

	/* fileset is emulating a single file */
	fileset->fs_attrs = FILESET_IS_FILE;

	/* Set the size of the fileset to 1 */
	fileset->fs_entries = avd_int_alloc(1);

	/* Set the mean dir width to more than 1 */
	fileset->fs_dirwidth = avd_int_alloc(10);

	/* Set the dir and size gammas to 0 */
	fileset->fs_dirgamma = avd_int_alloc(0);
}

/*
 * Calls parser_fileset_define_common() to allocate a fileset with the
 * supplied name and initializes the fileset's fileset_preallocpercent,
 * fileset_prealloc, fileset_entries, fileset_dirwidth, fileset_dirgamma,
 * and fileset_sizegamma attributes.
 */
static void
parser_fileset_define(cmd_t *cmd)
{
	fileset_t *fileset;
	attr_t *attr;

	if ((fileset = parser_fileset_define_common(cmd)) == NULL) {
		filebench_log(LOG_ERROR,
		    "define fileset: failed to instantiate fileset");
		filebench_shutdown(1);
		return;
	}

	/* Get the number of files in the fileset */
	if ((attr = get_attr_integer(cmd, FSA_ENTRIES))) {
		fileset->fs_entries = attr->attr_avd;
	} else {
		fileset->fs_entries = avd_int_alloc(0);
	}

	/* Get the number of leafdirs in the fileset */
	if ((attr = get_attr_integer(cmd, FSA_LEAFDIRS))) {
		fileset->fs_leafdirs = attr->attr_avd;
	} else {
		fileset->fs_leafdirs = avd_int_alloc(0);
	}

	/* Get the mean dir width of the fileset */
	if ((attr = get_attr_integer(cmd, FSA_DIRWIDTH))) {
		fileset->fs_dirwidth = attr->attr_avd;
	} else {
		filebench_log(LOG_ERROR, "Fileset has zero directory width");
		fileset->fs_dirwidth = avd_int_alloc(0);
	}

	/* Get the dir depth */
	if ((attr = get_attr_integer(cmd, FSA_DIRDEPTHRV))) {
		fileset->fs_dirdepthrv = attr->attr_avd;
	} else {
		fileset->fs_dirdepthrv = NULL;
	}

	/* Get the gamma value for dir depth distributions */
	if ((attr = get_attr_integer(cmd, FSA_DIRGAMMA))) {
		fileset->fs_dirgamma = attr->attr_avd;
	} else
		fileset->fs_dirgamma = avd_int_alloc(1500);
}

static void
parser_posset_define(cmd_t *cmd)
{
	attr_t *attr;
	avd_t name;
	avd_t type;
	avd_t seed;
	avd_t max;
	avd_t entries;
	int i;

	struct posset *ps;
	
	if ((attr = get_attr(cmd, FSA_NAME))) {
		name = attr->attr_avd;
	} else {
		filebench_log(LOG_ERROR,
		   "parser_posset_define: no name specified for the posset");
		filebench_shutdown(1);
		return;
	}

	if ((attr = get_attr(cmd, FSA_TYPE))) {
		type = attr->attr_avd;
	} else {
		filebench_log(LOG_ERROR,
		   "parser_posset_define: no type specified for the posset");
		filebench_shutdown(1);
		return;
	}

	if ((attr = get_attr_integer(cmd, FSA_ENTRIES))) {
		entries = attr->attr_avd;
	} else {
		filebench_log(LOG_ERROR,
		   "parser_posset_define: no entries number "
					"specified for the posset");
		filebench_shutdown(1);
		return;
	}

	/*
	 * two attributes below are mandatory only for specific types
	 * of possets, so postpone their validation for posset type
	 * specific functions.
	 */
	if ((attr = get_attr_integer(cmd, FSA_RANDSEED)))
		seed = attr->attr_avd;
	else
		seed = avd_int_alloc(0);

	if ((attr = get_attr_integer(cmd, FSA_MAX)))
		max = attr->attr_avd;
	else
		max = avd_int_alloc(0);

	filebench_log(LOG_INFO,"Defining position set: %s type: %s",
				 avd_get_str(name), avd_get_str(type));

	ps = posset_alloc(name, type, seed, max, entries);
	if (!ps) {
		filebench_log(LOG_ERROR, "Cannot define fileset");
		filebench_shutdown(1);
		/* NOT REACHABLE */
		return;
	}

	/* printing all positions */
	for (i = 0; i < avd_get_int(ps->ps_entries); i++)
		filebench_log(LOG_INFO,"pos %d: %llu", i, ps->ps_positions[i]);

}

/*
 * Creates and starts all defined procflow processes. The call to
 * procflow_init() results in creation of the requested number of
 * process instances for each previously defined procflow. The
 * child processes exec() a new instance of filebench, passing it
 * the instance number and address of the shared memory region.
 * The child processes will then create their threads and flowops.
 * The routine then unlocks the run_lock to allow all the processes'
 * threads to start and  waits for all of them to begin execution.
 * Finally, it records the start time and resets the event generation
 * system.
 */
static void
parser_proc_create(cmd_t *cmd)
{
	filebench_shm->shm_1st_err = 0;
	filebench_shm->shm_f_abort = FILEBENCH_OK;

	(void) pthread_rwlock_rdlock(&filebench_shm->shm_run_lock);

	if (procflow_init() != 0) {
		filebench_log(LOG_ERROR, "Failed to create processes\n");
		filebench_shutdown(1);
	}

	/* Wait for all threads to start */
	if (procflow_allstarted() != 0) {
		filebench_log(LOG_ERROR, "Could not start run");
		return;
	}

	/* Release the read lock, allowing threads to start */
	(void) pthread_rwlock_unlock(&filebench_shm->shm_run_lock);

	if (filebench_shm->shm_required &&
	    (ipc_ismcreate(filebench_shm->shm_required) < 0)) {
		filebench_log(LOG_ERROR, "Could not allocate shared memory");
		return;
	}

	filebench_shm->shm_starttime = gethrtime();
	eventgen_reset();
}

/*
 * Calls fileset_createsets() to populate all filesets and create all
 * associated, initially existant,  files and subdirectories.
 * If errors are encountered, calls filebench_shutdown() to exit Filebench.
 */
static void
parser_fileset_create(cmd_t *cmd)
{
	if (!filecreate_done) {
		filecreate_done = 1;

		if (fileset_createsets()) {
			filebench_log(LOG_ERROR, "Failed to create filesets");
			filebench_shutdown(1);
		}
	} else {
		filebench_log(LOG_INFO,
		    "Attempting to create fileset more than once, ignoring");
	}

}

/*
 * Deletes the files and directories that represent files and filesets on the
 * storage medium.
 */
static void
parser_fileset_shutdown(cmd_t *cmd)
{
	filebench_log(LOG_INFO, "Shutting down filesets");
	fileset_delete_all_filesets();
}

/*
 * Shuts down all processes and their associated threads. When finished
 * it deletes interprocess shared memory and resets the event generator.
 * It does not exit the filebench program though.
 */
static void
parser_proc_shutdown(cmd_t *cmd)
{
	filebench_log(LOG_INFO, "Shutting down processes");
	filecreate_done = 0;
	procflow_shutdown();
	if (filebench_shm->shm_required)
		ipc_ismdelete();
	eventgen_reset();
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
	parser_proc_create(cmd);

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
	parser_statssnap(cmd);
	parser_proc_shutdown(cmd);
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
	parser_proc_create(cmd);

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

		parser_statssnap(cmd);

		if (reset_stats)
			stats_clear();
	}

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
	parser_statssnap(cmd);
	parser_proc_shutdown(cmd);
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
	parser_proc_create(cmd);

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
	parser_statssnap(cmd);
	parser_proc_shutdown(cmd);
	parser_filebench_shutdown((cmd_t *)0);
}

char *usagestr = NULL;

/*
 * Prints usage string if defined, else just a message requesting load of a
 * personality.
 */
static void
parser_help(cmd_t *cmd)
{
	if (usagestr) {
		filebench_log(LOG_INFO, "%s", usagestr);
	} else {
		filebench_log(LOG_INFO,
		    "load <personality> (ls "
		    "%s/workloads for list)", fbbasepath);
	}
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

	if ((attr= get_attr(cmd, FSA_MASTER))) {
		master = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "enable multi: no master specified");
		return;
	}

	if ((attr= get_attr(cmd, FSA_CLIENT))) {
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
parser_warmup(cmd_t *cmd)
{
	int sleeptime;

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	sleeptime = cmd->cmd_qty;
	filebench_log(LOG_INFO, "Warming up...");

	(void) parser_pause(sleeptime);
}

/*
 * Same as parser_sleep, except the sleep time is obtained from a variable
 * whose name is passed to it as an argument on the command line.
 */
static void
parser_warmup_variable(cmd_t *cmd)
{
	avd_t integer = avd_var_alloc(cmd->cmd_tgt1);
	int sleeptime;

	if (integer == NULL) {
		filebench_log(LOG_ERROR, "Unknown variable %s",
		cmd->cmd_tgt1);
		return;
	}

	sleeptime = avd_get_int(integer);

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Warming up...");

	(void) parser_pause(sleeptime);
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
	filebench_log(LOG_INFO, "Running...");

	timeslept = parser_pause(sleeptime);

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
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
 * Parser log prints the values of a list of variables to the log file.
 * The list of variables is placed on the command line, separated
 * by comas and the entire list is enclosed in quotes.
 * For example, if $dir contains "/export/home/tmp" and $filesize = 1048576,
 * then typing: log "$dir, $filesize" prints: log /export/home/tmp, 1048576
 */
static void
parser_log(cmd_t *cmd)
{
	char *string;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_VERBOSE, "log %s", string);
	filebench_log(LOG_LOG, "%s", string);
}

/*
 * Implements the stats directory command. changes the directory for
 * dumping statistics to supplied directory path. For example:
 * 	stats directory /tmp
 * changes the stats directory to "/tmp".
 */
static void
parser_directory(cmd_t *cmd)
{
	char newdir[MAXPATHLEN];
	char *dir;
	int ret;

	if ((dir = parser_list2string(cmd->cmd_param_list)) == NULL) {
		filebench_log(LOG_ERROR, "Cannot interpret directory");
		return;
	}

	*newdir = 0;
	/* Change dir relative to cwd if path not fully qualified */
	if (*dir != '/') {
		(void) strcat(newdir, cwd);
		(void) strcat(newdir, "/");
	}
	(void) strcat(newdir, dir);
	(void) mkdir(newdir, 0755);
	filebench_log(LOG_VERBOSE, "Change dir to %s", newdir);
	ret = chdir(newdir);
	free(dir);
}

#define	PIPE_PARENT 1
#define	PIPE_CHILD  0

/*
 * Runs the quoted unix command as a background process. Intended for
 * running statistics gathering utilities such as mpstat while the filebench
 * workload is running. Also records the pid's of the background processes
 * so that parser_statssnap() can terminate them when the run completes.
 */
static void
parser_statscmd(cmd_t *cmd)
{
	char *string;
	pid_t pid;
	pidlist_t *pidlistent;
	int pipe_fd[2];
	int newstdout;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	if ((pipe(pipe_fd)) < 0) {
		filebench_log(LOG_ERROR, "statscmd pipe failed");
		return;
	}

#ifdef HAVE_FORK1
	if ((pid = fork1()) < 0) {
		filebench_log(LOG_ERROR, "statscmd fork failed");
		return;
	}
#elif HAVE_FORK
	if ((pid = fork()) < 0) {
		filebench_log(LOG_ERROR, "statscmd fork failed");
		return;
	}
#else
	Crash! - Need code to deal with no fork1!
#endif /* HAVE_FORK1 */

	if (pid == 0) {

		setsid();

		filebench_log(LOG_VERBOSE,
		    "Backgrounding %s", string);
		/*
		 * Child
		 * - close stdout
		 * - dup to create new stdout
		 * - close pipe fds
		 */
		(void) close(1);

		if ((newstdout = dup(pipe_fd[PIPE_CHILD])) < 0) {
			filebench_log(LOG_ERROR,
			    "statscmd dup failed: %s",
			    strerror(errno));
		}

		(void) close(pipe_fd[PIPE_PARENT]);
		(void) close(pipe_fd[PIPE_CHILD]);

		if (system(string) < 0) {
			filebench_log(LOG_ERROR,
			    "statscmd exec failed: %s",
			    strerror(errno));
		}
		/* Failed! */
		exit(1);

	} else {

		/* Record pid in pidlist for subsequent reaping by stats snap */
		if ((pidlistent = (pidlist_t *)malloc(sizeof (pidlist_t)))
		    == NULL) {
			filebench_log(LOG_ERROR, "pidlistent malloc failed");
			return;
		}

		pidlistent->pl_pid = pid;
		pidlistent->pl_fd = pipe_fd[PIPE_PARENT];
		(void) close(pipe_fd[PIPE_CHILD]);

		/* Add fileobj to global list */
		if (pidlist == NULL) {
			pidlist = pidlistent;
			pidlistent->pl_next = NULL;
		} else {
			pidlistent->pl_next = pidlist;
			pidlist = pidlistent;
		}
	}
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

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_VERBOSE,
	    "Running '%s'", string);

	if (system(string) < 0) {
		filebench_log(LOG_ERROR,
		    "system exec failed: %s",
		    strerror(errno));
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

static void parser_fscheck(cmd_t *cmd) {
	return;
}

#if 0
/* XXX: do not support this command for now */
/*
 * Checks to see if the specified data directory exists and it's mounted file
 * system is the correct type.
 */
static void
parser_fscheck(cmd_t *cmd)
{
	int fstype_idx;
	char *pathname = NULL;
	char *filesys = "tmpfs";
	char string[MAXPATHLEN];
	struct statvfs64 statbuf;
	attr_t *attr;

	if (cmd->cmd_attr_list == NULL)
		return;

	for (attr = cmd->cmd_attr_list; attr; attr = attr->attr_next) {

		switch(attr->attr_name) {
		case FSA_PATH:
			pathname = avd_get_str(attr->attr_avd);
			break;
		case FSA_FSTYPE:
			filesys = avd_get_str(attr->attr_avd);
			break;
		}
	}

	if (pathname == NULL)
		return;

	if (statvfs64(pathname, &statbuf) < 0) {
		filebench_log(LOG_ERROR,
		    "%s error with supplied data path name: %s; exiting",
		    strerror(errno), pathname);
		filebench_shutdown(1);
		return;
	}

	if (strncmp(filesys, statbuf.f_basetype, FSTYPSZ) != 0) {
		filebench_log(LOG_ERROR,
		    "File System is of type %s, NOT %s as indicated",
		    statbuf.f_basetype, filesys);
		filebench_shutdown(1);
		return;
	}
}
#endif

/*
 * Checks to see if any filesets need to have their caches flushed, and
 * if so invokes the fs_flush script.
 */
static void
parser_fsflush(cmd_t *cmd)
{
	fileset_t *fileset;
	char **fspathlist;
	char *pathname = NULL;
	char *filesys = NULL;
	char string[MAXPATHLEN];
	attr_t *attr;
	int fsidx;

	if ((attr = cmd->cmd_attr_list) == NULL)
		return;

	/* Get supplied file system type */
	if (attr->attr_name == FSA_FSTYPE)
		filesys = avd_get_str(attr->attr_avd);

	if (filesys == NULL) {
		filebench_log(LOG_ERROR,
		    "FSFLUSH command lacks file system type");
		return;
	}

	/* Check all filesets for any that remain cached and count them*/
	fsidx = 0;
	for (fileset = filebench_shm->shm_filesetlist; fileset != NULL;
	     fileset = fileset->fs_next) {

		if (avd_get_bool(fileset->fs_cached))
			return;

		fsidx++;
	}

	/* allocated space for fileset path pointers */
	fspathlist = (char **)malloc(fsidx * sizeof(char *));

	/* If flushing still required, flush all filesets */
	fsidx = 0;
	for (fileset = filebench_shm->shm_filesetlist; fileset != NULL;
	     fileset = fileset->fs_next) {
		int idx;

		if ((pathname = avd_get_str(fileset->fs_path)) == NULL)
			return;

		for (idx = 0; idx < fsidx; idx++) {
			if (strcmp(pathname, fspathlist[idx]) == 0)
				break;
		}

		if (fsidx == idx) {

			/* found a new path */
			fspathlist[fsidx++] = pathname;

			/* now flush it */
			snprintf(string, MAXPATHLEN,
			    "%s/scripts/fs_flush %s %s", fbbasepath,
			    filesys, pathname);

			if (system(string) < 0) {
				filebench_log(LOG_ERROR,
				    "exec of fs_flush script failed: %s",
				    strerror(errno));
				filebench_shutdown(1);
			}
		}
	}
}

/*
 * Prints out the version of Filebench.
 */
static void
parser_version(cmd_t *cmd)
{
	filebench_log(LOG_INFO, "Filebench Version: %s", FILEBENCH_VERSION);
}

/*
 * Sets osprof_enabled option
 */
static void
parser_osprof_enable(cmd_t *cmd)
{
	filebench_shm->osprof_enabled = 1;
	filebench_log(LOG_INFO, "OSprof enabled");
}

/*
 * Resets osprof_enabled option
 */
static void
parser_osprof_disable(cmd_t *cmd)
{
	filebench_shm->osprof_enabled = 0;
	filebench_log(LOG_INFO, "OSprof disabled");
}

/*
 * Adds the string supplied as the argument to the usage command
 * to the end of the string printed by the help command.
 */
static void
parser_usage(cmd_t *cmd)
{
	char *string;
	char *newusage;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	if (dofile == DOFILE_TRUE)
		return;

	if (usagestr == NULL) {
		newusage = malloc(strlen(string) + 2);
		*newusage = 0;
	} else {
		newusage = malloc(strlen(usagestr) + strlen(string) + 2);
		(void) strcpy(newusage, usagestr);
	}
	(void) strcat(newusage, "\n");
	(void) strcat(newusage, string);

	if (usagestr)
		free(usagestr);

	usagestr = newusage;

	filebench_log(LOG_INFO, "%s", string);
}

/*
 * Updates the global dump filename with the filename supplied
 * as the command's argument. Then dumps the statistics of each
 * worker flowop into the dump file, followed by a summary of
 * overall totals.
 */
static void
parser_statsdump(cmd_t *cmd)
{
	char *string;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_VERBOSE,
	    "Stats dump to file '%s'", string);

	stats_dump(string);

	free(string);
}

/*
 * Same as statsdump, but outputs in a computer friendly format.
 */
static void
parser_statsmultidump(cmd_t *cmd)
{
	char *string;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_VERBOSE,
	    "Stats dump to file '%s'", string);

	stats_multidump(string);

	free(string);
}

/*
 * Same as parser_statsdump, but in xml format.
 */
static void
parser_statsxmldump(cmd_t *cmd)
{
	char *string;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_VERBOSE,
	    "Stats dump to file '%s'", string);

	stats_xmldump(string);

	free(string);
}

/*
 * Kills off background statistics collection processes, then takes a snapshot
 * of the filebench run's collected statistics using stats_snap() from
 * stats.c.
 */
static void
parser_statssnap(cmd_t *cmd)
{
	pidlist_t *pidlistent;
	int stat;
	pid_t pid;

	for (pidlistent = pidlist; pidlistent != NULL;
	    pidlistent = pidlistent->pl_next) {
		filebench_log(LOG_VERBOSE, "Killing session %d for pid %d",
		    getsid(pidlistent->pl_pid),
		    pidlistent->pl_pid);
		if (pidlistent->pl_fd)
			(void) close(pidlistent->pl_fd);
#ifdef HAVE_SIGSEND
		sigsend(P_SID, getsid(pidlistent->pl_pid), SIGTERM);
#else
		(void) kill(-1, SIGTERM);
#endif

		/* Close pipe */
		if (pidlistent->pl_fd)
			(void) close(pidlistent->pl_fd);

		/* Wait for cmd and all its children */
		while ((pid = waitpid(pidlistent->pl_pid * -1, &stat, 0)) > 0)
			filebench_log(LOG_DEBUG_IMPL,
			"Waited for pid %d", (int)pid);
	}

	for (pidlistent = pidlist; pidlistent != NULL;
	    pidlistent = pidlistent->pl_next) {
		free(pidlistent);
	}

	pidlist = NULL;
	stats_snap();
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

/*
 * define a random variable and initialize the distribution parameters
 */
static void
parser_var_assign_randvar(char *name, cmd_t *cmd)
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
	if ((attr = get_attr_integer(cmd, FSA_RANDSRC))) {
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
	if ((attr = get_attr_integer(cmd, FSA_MIN)))
		rndp->rnd_min = attr->attr_avd;
	else
		rndp->rnd_min = avd_int_alloc(0);

	/* Get the roundoff value for the random distribution */
	if ((attr = get_attr_integer(cmd, FSA_ROUND)))
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
	if ((attr = get_attr_integer(cmd, FSA_RANDSEED)))
		rndp->rnd_seed = attr->attr_avd;
	else
		rndp->rnd_seed = avd_int_alloc(0);

	/* Get the gamma value of the random distribution */
	if ((attr = get_attr_integer(cmd, FSA_RANDGAMMA)))
		rndp->rnd_gamma = attr->attr_avd;
	else
		rndp->rnd_gamma = avd_int_alloc(1500);

	/* Get the mean value of the random distribution */
	if ((attr = get_attr_integer(cmd, FSA_RANDMEAN))) {
		rndp->rnd_mean = attr->attr_avd;
	} else if ((rndp->rnd_type & RAND_TYPE_MASK) == RAND_TYPE_GAMMA) {
		rndp->rnd_mean = NULL;
	} else {
		rndp->rnd_mean = avd_int_alloc(0);
	}

	var_assign_randvar(name, rndp);

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
get_attr_fileset(cmd_t *cmd, int64_t name)
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

	if (rtn == NULL)
		return (NULL);

	if (rtn->attr_param_list) {
		filebench_log(LOG_DEBUG_SCRIPT, "attr is param list");
		rtn->attr_avd = parser_list2varstring(rtn->attr_param_list);
	}

	return (rtn);
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
	char *string;

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

	if (rtn == NULL)
		return (NULL);

	if (rtn->attr_param_list) {
		filebench_log(LOG_DEBUG_SCRIPT, "attr is param list");
		string = parser_list2string(rtn->attr_param_list);
		if (string != NULL) {
			rtn->attr_avd = avd_str_alloc(string);
			filebench_log(LOG_DEBUG_SCRIPT,
			    "attr string %s", string);
		}
	}

	return (rtn);
}

/*
 * Similar to get_attr, but converts the parameter string supplied with the
 * named attribute to an integer and stores the integer in the attr_avd
 * portion of the returned attr_t struct.
 */
static attr_t *
get_attr_integer(cmd_t *cmd, int64_t name)
{
	attr_t *attr;
	attr_t *rtn = NULL;

	for (attr = cmd->cmd_attr_list; attr != NULL;
	    attr = attr->attr_next) {
		if (attr->attr_name == name)
			rtn = attr;
	}

	if (rtn == NULL)
		return (NULL);

	if (rtn->attr_param_list)
		rtn->attr_avd = parser_list2avd(rtn->attr_param_list);

	return (rtn);
}

/*
 * Similar to get_attr, but converts the parameter string supplied with the
 * named attribute to an integer and stores the integer in the attr_avd
 * portion of the returned attr_t struct. If no parameter string is supplied
 * then it defaults to TRUE (1).
 */
static attr_t *
get_attr_bool(cmd_t *cmd, int64_t name)
{
	attr_t *attr;
	attr_t *rtn = NULL;

	for (attr = cmd->cmd_attr_list; attr != NULL;
	    attr = attr->attr_next) {
		if (attr->attr_name == name)
			rtn = attr;
	}

	if (rtn == NULL)
		return (NULL);

	if (rtn->attr_param_list) {
		rtn->attr_avd = parser_list2avd(rtn->attr_param_list);

	} else if (rtn->attr_avd == NULL) {
		rtn->attr_avd = avd_bool_alloc(TRUE);
	}

	/* boolean attributes cannot point to random variables */
	if (AVD_IS_RANDOM(rtn->attr_avd)) {
		filebench_log(LOG_ERROR,
		    "define flowop: Boolean attr %s cannot be random", name);
		filebench_shutdown(1);
		return (NULL);
	}

	return (rtn);
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
 * Define a custom variable and validate it's parameters.
 * TODO: Clean up state when things go wrong.
 */
static void
parser_var_assign_cvar(char *name, cmd_t *cmd)
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

	var_assign_cvar(name, cvar);
}

void parser_list_cvar_types(void)
{
	cvar_library_info_t *t;

	if (!filebench_shm->shm_cvar_lib_info_list) {
		printf("No custom variables loaded.\n");
		return;
	}

	for (t = filebench_shm->shm_cvar_lib_info_list; t != NULL; t = t->next)
		printf("%s\n", t->type);

	return;
}

void parser_list_cvar_type_parameters(cmd_t *cmd)
{
	char *type;
	const char *version = NULL;
	const char *usage = NULL;

	cvar_library_info_t *t;

	type = avd_get_str(cmd->cmd_attr_list->attr_avd);
	if (type == NULL) { /* We will never ever be here. */
		filebench_log(LOG_ERROR, "list cvar type parameters: internal error");
		return;
	}

	for (t = filebench_shm->shm_cvar_lib_info_list; t != NULL; t = t->next) {
		if (!strcmp(type, t->type))
			break;
	}

	if (!t) {
		printf("Unknown custom variable %s. Run 'list cvar types' to list "
				"currently loaded custom variables.\n", type);
		return;
	}

	if (cvar_libraries[t->index]->cvar_op.cvar_version)
		version = cvar_libraries[t->index]->cvar_op.cvar_version();
	
	if (cvar_libraries[t->index]->cvar_op.cvar_usage)
		usage = cvar_libraries[t->index]->cvar_op.cvar_usage();

	printf("Supporting library: %s\n", t->filename);
	
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

