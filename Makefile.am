SUBDIRS = workloads

# we depend on this lex & yacc generated file
BUILT_SOURCES = parser_gram.h

bin_PROGRAMS = filebench
filebench_SOURCES = eventgen.c fb_avl.c fb_localfs.c \
		    fb_random.c fileset.c flowop.c flowop_library.c \
		    gamma_dist.c ipc.c misc.c multi_client_sync.c \
		    parser_gram.y parser_lex.l procflow.c stats.c \
		    threadflow.c utils.c vars.c posset.c ioprio.c \
		    eventgen.h  fb_random.h  fileset.h  fsplug.h \
		    ipc.h   multi_client_sync.h  parsertypes.h  stats.h \
		    utils.h config.h fb_avl.h filebench.h flowop.h gamma_dist.h \
		    misc.h procflow.h threadflow.h vars.h posset.h ioprio.h flag.h

EXTRA_DIST = LICENSE

if AUTOCOMP_LIBTECLA
filebench_SOURCES += auto_comp.c auto_comp.h
endif

AM_YFLAGS = -d
#AM_LDFLAGS = 
if GCC_USED
AM_CFLAGS = -Wall -Wno-unknown-pragmas
endif

DEFS = -D_REENTRANT -DYYDEBUG -DYY_NO_INPUT -DFILEBENCHDIR=\"$(datadir)/filebench\" -D_LARGEFILE64_SOURCE -D_GNU_SOURCE
