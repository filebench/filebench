/*
 * sanity.c
 *
 * Sanity checker for custom libraries.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdint.h>
#include <fb_cvar.h>

char *pgmname;

void print_usage()
{
	printf("Usage:   %s <library name> <parameter string> "
			"<count>\n", pgmname);
	printf("Example: %s librand-triangular.so.1 "
			"'lower:1024;upper:4096;mode:4096'"
			" 10\n", pgmname);
	return;
}

int main(int argc, char *argv[])
{
	void *cvar_lib;
	void *cvar_handle;
	char *libname;
	char *parameters;
	int count;
	int ret;
	cvar_operations_t cvar_op;
	double d;

	/* Set the global program name. */
	pgmname = argv[0];

	if (argc < 4) {
		printf("Insufficient parameters.\n");
		print_usage();
		ret = -1;
		goto exit;
	}

	/* Load the library. */
	libname = argv[1];
	cvar_lib = dlopen(libname, RTLD_NOW | RTLD_GLOBAL);
	if (!cvar_lib) {
		printf("Unable to load library: %s.\n", dlerror());
		ret = -2;
		goto exit;
	}

	/* Initialize the function pointers. */
	cvar_op.cvar_module_init = dlsym(cvar_lib, FB_CVAR_MODULE_INIT);

	cvar_op.cvar_alloc_handle = dlsym(cvar_lib, FB_CVAR_ALLOC_HANDLE);
	if (!cvar_op.cvar_alloc_handle) {
		printf("Unable to find " FB_CVAR_ALLOC_HANDLE ": %s.\n", dlerror());
		ret = -3;
		goto dlclose;
	}

	cvar_op.cvar_revalidate_handle = dlsym(cvar_lib, FB_CVAR_REVALIDATE_HANDLE);
	if (!cvar_op.cvar_revalidate_handle) {
		printf("Unable to find " FB_CVAR_ALLOC_HANDLE ": %s.\n", dlerror());
		ret = -4;
		goto dlclose;
	}

	cvar_op.cvar_next_value = dlsym(cvar_lib, FB_CVAR_NEXT_VALUE);
	if (!cvar_op.cvar_next_value) {
		printf("Unable to find " FB_CVAR_NEXT_VALUE ": %s.\n", dlerror());
		ret = -5;
		goto dlclose;
	}

	cvar_op.cvar_free_handle = dlsym(cvar_lib, FB_CVAR_FREE_HANDLE);
	if (!cvar_op.cvar_free_handle) {
		printf("Unable to find " FB_CVAR_FREE_HANDLE ": %s.\n", dlerror());
		ret = -6;
		goto dlclose;
	}

	cvar_op.cvar_module_exit = dlsym(cvar_lib, FB_CVAR_MODULE_EXIT);

	cvar_op.cvar_usage = dlsym(cvar_lib, FB_CVAR_USAGE);

	cvar_op.cvar_version = dlsym(cvar_lib, FB_CVAR_VERSION);

	if (cvar_op.cvar_module_init) {
		ret = cvar_op.cvar_module_init();
		if (ret) {
			printf("Custom variable module initialization failed.\n");
			goto dlclose;
		}
	}

	if (cvar_op.cvar_version)
		printf("Variable: %s (%s)\n", libname, cvar_op.cvar_version());
	else
		printf("Variable: %s\n", libname);

	if (cvar_op.cvar_usage)
		printf("%s\n", cvar_op.cvar_usage());

	/* Allocate a new custom variable handle */
	parameters = argv[2];
	cvar_handle = cvar_op.cvar_alloc_handle(parameters, malloc, free);
	if (!cvar_handle) {
		printf("Custom variable handle allocation failed.\n");
		ret = -7;
		goto cvar_free;
	}

	/* Try revalidating the handle. */
	ret = cvar_op.cvar_revalidate_handle(cvar_handle);
	if (ret) {
		printf("Custom variable handle revalidation failed.\n");
		ret = -10;
		goto cvar_free;
	}

	count = atoi(argv[3]);
	if (count > 0) {
		while (count > 1) {
			ret = cvar_op.cvar_next_value(cvar_handle, &d);
			if (ret) {
				printf("Unable to get the next value. Error %d.\n" ,ret);
				ret = -11;
				goto cvar_free;
			}
			printf("%lf,", d);
			count--;
		}
		ret = cvar_op.cvar_next_value(cvar_handle, &d);
		if (ret) {
			printf("Unable to get the next value. Error %d.\n" ,ret);
			ret = -11;
			goto cvar_free;
		}
		printf("%lf.\n", d);
	}

	ret = 0;
	printf("\nAll done.\n");

cvar_free:
	cvar_op.cvar_free_handle(cvar_handle, free);

	if (cvar_op.cvar_module_exit)
		cvar_op.cvar_module_exit();

dlclose:
	dlclose(cvar_lib);

exit:
	return ret;
}
