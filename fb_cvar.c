/*
 * fb_cvar.c
 *
 * Support for custom variables in Filebench.
 *
 * @Author Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <dlfcn.h>

#include "ipc.h"
#include "fb_cvar.h"

/* Some helpers. */
static int alloc_cvar_lib_info(const char *filename);
static char *gettype(const char *filename);
static cvar_library_t *init_cvar_library(cvar_library_info_t *cvar_lib_info);
static void *load_library(const char *filename);
static void free_cvar_library(cvar_library_t *c);
static int init_cvar_library_ops(cvar_library_t *c);

/* Points to the head of an array of pointers to cvar_library_t. */
cvar_library_t **cvar_libraries;

/*
 * Allocate space for a new custom variable in the shared memory location.
 */
cvar_t *
cvar_alloc(void)
{
	cvar_t *cvar;

	if ((cvar = (cvar_t *)ipc_malloc(FILEBENCH_CVAR)) == NULL) {
		filebench_log(LOG_ERROR, "Out of memory for custom variable");
		return (NULL);
	}

	/* place on the head of the global list */
	cvar->next = filebench_shm->shm_cvar_list;
	filebench_shm->shm_cvar_list = cvar;

	return (cvar);
}

/*
 * Initialize cvar_library_info structures in the shared memory.
 * Return 0 on success and a non zero error code on failure.
 */
int
init_cvar_library_info(const char *dirpath)
{
	DIR *libdir = NULL;
	struct dirent *dirent;
	char *filename = NULL;
	int ret = -1;
	int dirpath_len = strlen(dirpath);
	int direntlen;

	filename = (char *) malloc(dirpath_len + 1 + NAME_MAX + 1);
	if (!filename) {
		filebench_log(LOG_ERROR, "Out of memory");
		goto out;
	}

	strcpy(filename, dirpath);
	filename[dirpath_len] = '/';

	filename[dirpath_len + NAME_MAX] = '\0';

	libdir = opendir(dirpath);
	if (!libdir) {
		filebench_log(LOG_ERROR, "Failed to open cvar directory");
		ret = 0;
		goto out;
	}

	while ((dirent = readdir(libdir)) != NULL) {
		if (!strcmp(".", dirent->d_name) || !strcmp("..", dirent->d_name))
			continue;

		direntlen = strlen(dirent->d_name);
		if (strcmp(".so", dirent->d_name + direntlen - 3))
			continue;

		strncpy(filename + dirpath_len + 1, dirent->d_name, NAME_MAX);
		ret = alloc_cvar_lib_info(filename);
		if (ret)
			goto out;
	}

	ret = 0;

out:
	if (filename)
		free(filename);

	if (libdir)
		closedir(libdir);

	return ret;
}

/*
 * Return 0 on success and a non zero error code on failure.
 */
static int
alloc_cvar_lib_info(const char *filename)
{
	int ret = -1;
	cvar_library_info_t *cli = NULL;
	cvar_library_info_t *t;

	cli = (cvar_library_info_t *) ipc_malloc(FILEBENCH_CVAR_LIB_INFO);
	if (!cli)
		goto out;

	cli->filename = ipc_stralloc(filename);
	if (!cli->filename)
		goto out;

	cli->type = ipc_stralloc(gettype(filename));
	if (!cli->type)
		goto out;

	cli->next = NULL;

	if (filebench_shm->shm_cvar_lib_info_list) {
		for (t = filebench_shm->shm_cvar_lib_info_list; t->next != NULL;
				t = t->next); /* Seek to the last entry. */

		cli->index = t->index + 1;
		t->next = cli;
	} else {
		cli->index = 0;
		filebench_shm->shm_cvar_lib_info_list = cli;
	}

	ret = 0;

out:
	if (ret && cli) {
		/* NOTE: There is no mechanism to free cli->filename and cli->type. */
		ipc_free(FILEBENCH_CVAR_LIB_INFO, (char *) cli);
	}

	return ret;
}

/*
 * Returns the 'type' name from the library.
 */
static char
*gettype(const char *filename)
{
	char libprefix[] = "lib";
	const char *libname;
	char *type;
	int type_len;
	const char *t;

	libname = strrchr(filename, '/');
	if (!libname)
		libname = filename; /* filename is not a fully qualified path. */
	else {
		libname++;
		/* Check for a malformed filename string. */
		if (!libname) {
			filebench_log(LOG_ERROR, "Malformed cvar library filename");
			return NULL;
		}

	}

	/* Strip the leading "lib". */
	if (!strncmp(libprefix, libname, sizeof(libprefix) - 1))
		libname += sizeof(char) * (sizeof(libprefix) - 1);

	if (!libname) {
		filebench_log(LOG_ERROR, "Malformed cvar library filename");
		return NULL;
	}

	/* Look for the first '.'. */
	type_len = 0;
	for (t = libname; *t != '\0' && *t != '.'; t++)
		type_len++;

	type = (char *) malloc(type_len + 1);
	if (!type) {
		filebench_log(LOG_ERROR, "Out of memory");
		return NULL;
	}
	strncpy(type, libname, type_len);
	type[type_len] = '\0';

	return type;
}

/*
 * Load shared objects.
 * Returns 0 on success and non-zero on error.
 */
int
init_cvar_libraries()
{
	int count;
	int ret = -1;
	int i;

	cvar_library_info_t *t;

	if (!filebench_shm->shm_cvar_lib_info_list) {
		/* Nothing to do. */
		return 0;
	}

	count = 0;
	for (t = filebench_shm->shm_cvar_lib_info_list; t != NULL;
			t = t->next)
		count++;

	cvar_libraries = (cvar_library_t **)
			malloc(sizeof(cvar_library_t *) * count);

	if (!cvar_libraries) {
		filebench_log(LOG_ERROR, "Out of memory");
		goto out;
	}

	for (t = filebench_shm->shm_cvar_lib_info_list, i = 0; t != NULL;
			t = t->next, i++) {
		if ((cvar_libraries[i] = init_cvar_library(t)) == NULL) {
			goto out;
		}
	}

	ret = 0;

out:
	return ret;
}

static cvar_library_t
*init_cvar_library(cvar_library_info_t *cvar_lib_info)
{
	cvar_library_t *c = NULL;
	int ret;

	c = (cvar_library_t *) malloc(sizeof(cvar_library_t));
	if (!c) {
		filebench_log(LOG_ERROR, "Out of memory");
		goto out;
	}

	c->cvar_lib_info = cvar_lib_info;
	c->lib_handle = load_library(cvar_lib_info->filename);
	if (!c->lib_handle)
		goto cleanup;

	ret = init_cvar_library_ops(c);
	if (ret)
		goto cleanup;

	if (c->cvar_op.cvar_module_init) {
		ret = c->cvar_op.cvar_module_init();
		if (ret) {
			filebench_log(LOG_ERROR, "Failed to initialize custom variable of type"
					" %s. cvar_module_init failed with error %d",
					cvar_lib_info->type, ret);
			goto cleanup;
		}
	}

out:
	return c;

cleanup:
	if (c) {
		free_cvar_library(c);
		free(c);
		c = NULL;
	}
	goto out;
}

static void
*load_library(const char *filename)
{
	void *lib_handle = dlopen(filename, RTLD_LOCAL | RTLD_NOW);
	if (!lib_handle)
		filebench_log(LOG_ERROR, "Unable to load library %s: %s",
				filename, dlerror());

	return lib_handle;
}

static void
free_cvar_library(cvar_library_t *c)
{
	if (c) {
		if (c->lib_handle) {
			dlclose(c->lib_handle);
		}
	}
}

static int
init_cvar_library_ops(cvar_library_t *c)
{
	int ret = -1;

	c->cvar_op.cvar_module_init = dlsym(c->lib_handle, FB_CVAR_MODULE_INIT);

	c->cvar_op.cvar_alloc_handle = dlsym(c->lib_handle, FB_CVAR_ALLOC_HANDLE);
	if (!c->cvar_op.cvar_alloc_handle) {
		filebench_log(LOG_ERROR, "Unable to find " FB_CVAR_ALLOC_HANDLE
				": %s.", dlerror());
		goto out;
	}

	c->cvar_op.cvar_revalidate_handle = dlsym(c->lib_handle,
			FB_CVAR_REVALIDATE_HANDLE);
	if (!c->cvar_op.cvar_revalidate_handle) {
		filebench_log(LOG_ERROR, "Unable to find " FB_CVAR_REVALIDATE_HANDLE
				": %s", dlerror());
	}

	c->cvar_op.cvar_next_value = dlsym(c->lib_handle, FB_CVAR_NEXT_VALUE);
	if (!c->cvar_op.cvar_next_value) {
		filebench_log(LOG_ERROR, "Unable to find " FB_CVAR_NEXT_VALUE
				": %s.", dlerror());
		goto out;
	}

	c->cvar_op.cvar_free_handle = dlsym(c->lib_handle, FB_CVAR_FREE_HANDLE);
	if (!c->cvar_op.cvar_free_handle) {
		filebench_log(LOG_ERROR, "Unable to find " FB_CVAR_FREE_HANDLE
				": %s.", dlerror());
		goto out;
	}

	c->cvar_op.cvar_module_exit = dlsym(c->lib_handle, FB_CVAR_MODULE_EXIT);

	c->cvar_op.cvar_usage = dlsym(c->lib_handle, FB_CVAR_USAGE);

	c->cvar_op.cvar_version = dlsym(c->lib_handle, FB_CVAR_VERSION);

	ret = 0;

out:
	return ret;
}

int
init_cvar_handle(cvar_t *cvar, const char *type, const char *parameters)
{
	int ret = -1;
	cvar_library_t *cvar_lib;
	cvar_library_info_t *t;

	for (t = filebench_shm->shm_cvar_lib_info_list; t != NULL; t = t->next) {
		if (!strcmp(type, t->type))
			break;
	}

	if (!t) {
		filebench_log(LOG_ERROR, "Undefined custom variable %s", type);
		goto out;
	}

	cvar->cvar_lib_info = t;

	cvar_lib = cvar_libraries[cvar->cvar_lib_info->index];
	cvar->cvar_handle = cvar_lib->cvar_op.cvar_alloc_handle(parameters,
			ipc_cvar_heapalloc, ipc_cvar_heapfree);
	if (!cvar->cvar_handle)
		goto out;

	ret = 0;

out:
	return ret;
}

double
get_cvar_value(cvar_t *cvar)
{
	int ret;
	double value = 0.0;
	fbint_t round = cvar->round;

	ipc_mutex_lock(&cvar->cvar_lock);
	cvar_library_t *cvar_lib = cvar_libraries[cvar->cvar_lib_info->index];
	ret = cvar_lib->cvar_op.cvar_next_value(cvar->cvar_handle, &value);
	ipc_mutex_unlock(&cvar->cvar_lock);

	if (ret) {
		filebench_log(LOG_ERROR, "Unable to get next_value from custom variable"
				" of type %s", cvar->cvar_lib_info->type);
		filebench_shutdown(1);
	}

	if (round) {
		fbint_t num, lower, upper;

		num = (fbint_t) value;
		lower = num - (num % round);
		upper = lower + round;

		value = (num - lower) > (upper - num) ? upper : lower;
	}

	if (value < cvar->min)
		value = cvar->min;
	else if (value > cvar->max)
		value = cvar->max;

	return value;
}

/*
 * Return 0 on success and a non-zero error code on failure.
 */
int
revalidate_cvar_handles()
{
	cvar_t *t;
	cvar_library_t *cvar_lib;
	int ret;

	if (!filebench_shm->shm_cvar_list)
		return 0; /* Nothing to do. */

	for (t = filebench_shm->shm_cvar_list; t != NULL; t = t->next) {
		cvar_lib = cvar_libraries[t->cvar_lib_info->index];
		if (cvar_lib->cvar_op.cvar_revalidate_handle) {
			ipc_mutex_lock(&t->cvar_lock);
			ret = cvar_lib->cvar_op.cvar_revalidate_handle(t->cvar_handle);
			ipc_mutex_unlock(&t->cvar_lock);

			if (ret) {
				filebench_log(LOG_ERROR, "Revalidation failed for cvar_handle "
						"of type %s with error code %d", t->cvar_lib_info->type,
						ret);
				return ret;
			}
		}
	}

	return 0;
}
