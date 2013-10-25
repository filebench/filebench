/*
 * fb_cvar.h
 *
 * Include file for code using custom variables.
 *
 * @Author Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#ifndef _FB_CVAR_H
#define _FB_CVAR_H

#include <stdint.h>
#include <sys/types.h>

/* Function (symbol) names within custom variable libraries. */
#define FB_CVAR_MODULE_INIT			"cvar_module_init"
#define FB_CVAR_ALLOC_HANDLE		"cvar_alloc_handle"
#define FB_CVAR_REVALIDATE_HANDLE	"cvar_revalidate_handle"
#define FB_CVAR_NEXT_VALUE			"cvar_next_value"
#define FB_CVAR_FREE_HANDLE			"cvar_free_handle"
#define FB_CVAR_MODULE_EXIT			"cvar_module_exit"
#define FB_CVAR_USAGE				"cvar_usage"
#define FB_CVAR_VERSION				"cvar_version"

/* Information about each library supporting a custom variable. This structure
 * is rooted in the shared memory segment. */
typedef struct cvar_library_info {
	char *filename; /* The fully qualified path to the library. */
	/* The type name of the library is the soname without the "lib" prefix and
	 * the ".so.XXX.XXX" suffix. */
	char *type;
	/* The index is a sequentially increasing count. It helps seek within global
	 * variable cvar_library_array. */
	int index;
	struct cvar_library_info *next;
} cvar_library_info_t;

/* Structure that encapsulates access to a custom variable. A var_t points to a
 * cvar_t (and not vice versa). */
typedef struct cvar {
	/* Used to provide exclusive access to this custom variable across threads
	 * and processes. */
	pthread_mutex_t cvar_lock;
	/* The custom variable handle returned by cvar_alloc() */
	void *cvar_handle;
	double min;
	double max;
	uint64_t round;
	cvar_library_info_t *cvar_lib_info;
	struct cvar *next;
} cvar_t;

/* The operations vector for a library. Each member is populated by a call to
 * dlsym(). */
typedef struct cvar_operations {
	int (*cvar_module_init)(void);
	void *(*cvar_alloc_handle)(const char *cvar_parameters,
			void *(*cvar_malloc)(size_t size), void (*cvar_free)(void *ptr));
	int (*cvar_revalidate_handle)(void *cvar_handle);
	int (*cvar_next_value)(void *cvar_handle, double *value);
	void (*cvar_free_handle)(void *cvar_handle, void (*cvar_free)(void *ptr));
	void (*cvar_module_exit)();
	const char *(*cvar_usage)(void);
	const char *(*cvar_version)(void);
} cvar_operations_t;

/* Structure that represents a library.  This structure is "per-process" and
 * "per-library" (and not in the shared memory). There is a one to one mapping
 * between cvar_library_t and cvar_library_info_t. */
typedef struct cvar_library {
	cvar_library_info_t *cvar_lib_info;
	void *lib_handle; /* The handle returned by dlopen(). */
	cvar_operations_t cvar_op; /* The operations vector of the library. */
} cvar_library_t;

/* Points to the head of an array of pointers to cvar_library_t. */
extern cvar_library_t **cvar_libraries;

cvar_t * cvar_alloc(void);
int init_cvar_library_info(const char *dirpath);
int init_cvar_libraries();
int init_cvar_handle(cvar_t *cvar, const char *type, const char *parameters);
double get_cvar_value(cvar_t *cvar);
int revalidate_cvar_handles();

#endif /* _FB_CVAR_H */
