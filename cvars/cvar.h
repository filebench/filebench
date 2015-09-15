/*
 * cvar.h
 *
 * Include file for code implementing custom variables.
 *
 * @Author Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#ifndef _CVAR_H
#define _CVAR_H

/*
 * Initialize the state of the library supporting the custom variable.
 * cvar_module_init is the first function to be invoked when a custom variable
 * module is loaded.
 *
 * Implementation: Optional.
 *
 * Return 0 on success and a non-zero error code on failure.
 */

int cvar_module_init();

/*
 * Allocate a new custom variable handle. A handle is subsequently used to
 * generate values. Memory required for initializing the handle must be
 * allocated using argument cvar_malloc only. Libraries can use cvar_free to
 * clean up memory allocated by cvar_malloc in case construction of the handle
 * fails. Libraries must not store references to cvar_malloc and cvar_free for
 * later use.
 *
 * Implementation: Mandatory.
 *
 * Return a non NULL handle on success and a NULL handle on error.
 */

void *cvar_alloc_handle(const char *cvar_parameters,
		void *(*cvar_malloc)(size_t size), void (*cvar_free)(void *ptr));

/*
 * Re-validate a previously allocated handle. Filebench will always
 * re-validate handles that were not allocated in the current process before
 * use in the current process.
 *
 * Implementation: Optional.
 *
 * Return 0 on success and a non-zero error code on failure to re-validate
 * existing handle.
 */

int cvar_revalidate_handle(void *cvar_handle);

/*
 * Called every time a new value of the custom variable is required.
 *
 * Implementation: Mandatory.
 *
 * Return 0 on success and non zero on error. On success, argument value is
 * initialized to the next value of the variable whose state is in handle.
 */

int cvar_next_value(void *cvar_handle, double *value);

/*
 * Called when an existing custom variable has to be destroyed. Use function
 * cvar_free to free up memory allocated for cvar_handle.
 *
 * Implementation: Mandatory.
 *
 * Note: cvar_free_handle may not be called at all, i.e., Filebench may choose
 * to quit without invoking free_handle.
 */

void cvar_free_handle(void *cvar_handle, void (*cvar_free)(void *ptr));

/*
 * Invoked before unloading the module.
 *
 * Implementation: Optional.
 *
 * Note:
 * 1. cvar_module_exit will never be invoked if cvar_module_init failed.
 * 2. cvar_module_exit may not be called at all, i.e., Filebench may choose
 * to quit without invoking cvar_module_exit.
 */

void cvar_module_exit();

/*
 * Show usage, including information on the list of parameters supported and the
 * format of the parameter string.
 *
 * Implementation: Optional.
 *
 * Return a non-null, formatted string to be displayed on screen.
 */

const char *cvar_usage();

/*
 * Show version.
 *
 * Implementation: Optional.
 *
 * Return a non-null version string.
 */

const char *cvar_version();

#endif /* _CVAR_H */
