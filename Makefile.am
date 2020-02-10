libdir = @libdir@/filebench

SUBDIRS = workloads cvars

# we depend on this lex & yacc generated file
BUILT_SOURCES = parser_gram.h

bin_PROGRAMS = filebench
filebench_SOURCES = eventgen.c fb_avl.c fb_localfs.c \
		    fb_random.c fileset.c flowop.c flowop_library.c \
		    gamma_dist.c ipc.c misc.c multi_client_sync.c \
		    parser_gram.y parser_lex.l procflow.c stats.c \
		    threadflow.c utils.c vars.c ioprio.c \
		    eventgen.h  fb_random.h  fileset.h  fsplug.h \
		    ipc.h   multi_client_sync.h  parsertypes.h  stats.h \
		    utils.h config.h fb_avl.h filebench.h flowop.h gamma_dist.h \
		    misc.h procflow.h threadflow.h vars.h ioprio.h flag.h \
		    fbtime.c fbtime.h \
		    fb_cvar.c fb_cvar.h aslr.c aslr.h \
		    cvars/mtwist/mtwist.c cvars/mtwist/mtwist.h
filebench_LDFLAGS = -export-dynamic

# We're going to build fb_localfs.c into a library as well; this means
# building it both with and without libtool, triggering
# an autoconf issue as documented at
# https://www.gnu.org/software/automake/manual/html_node/Objects-created-both-with-libtool-and-without.html
#
# The recommended fix there is per-target flags.
lib_LTLIBRARIES = libfb_localfs.la
libfb_localfs_la_SOURCES = fb_localfs.c
libfb_localfs_la_CFLAGS = $(AM_CFLAGS)

EXTRA_DIST = LICENSE

ACLOCAL_AMFLAGS = -I m4
AM_YFLAGS = -d
#AM_LDFLAGS = 
if GCC_USED
AM_CFLAGS = -Wall -Wno-unknown-pragmas
endif

DEFS = -D_REENTRANT -DYYDEBUG -DYY_NO_INPUT -DFBLIBDIR=\"$(libdir)\" -D_LARGEFILE64_SOURCE -D_GNU_SOURCE
