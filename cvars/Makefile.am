libdir = $(datadir)/filebench/cvars

lib_LTLIBRARIES = libcvar-erlang.la \
		  libcvar-exponential.la \
		  libcvar-lognormal.la \
		  libcvar-normal.la \
		  libcvar-triangular.la \
		  libcvar-uniform.la \
		  libcvar-weibull.la \
		  libcvar-gamma.la

common_cvar_files = mtwist/mtwist.c mtwist/randistrs.c cvar_tokens.c

libcvar_erlang_la_SOURCES = cvar-erlang.c $(common_cvar_files)
libcvar_exponential_la_SOURCES = cvar-exponential.c $(common_cvar_files)
libcvar_lognormal_la_SOURCES = cvar-lognormal.c $(common_cvar_files)
libcvar_normal_la_SOURCES = cvar-normal.c $(common_cvar_files)
libcvar_triangular_la_SOURCES = cvar-triangular.c $(common_cvar_files)
libcvar_uniform_la_SOURCES = cvar-uniform.c $(common_cvar_files)
libcvar_weibull_la_SOURCES = cvar-weibull.c $(common_cvar_files)
libcvar_gamma_la_SOURCES = cvar-gamma.c $(common_cvar_files)
