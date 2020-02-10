/*
 * mmap() call with MAP_FIXED flag does not guarantee that the allocated memory
 * region is not overlapped with the previously existant mappings. According to
 * POSIX, old mappings are silently discarded. There is no generic way to
 * detect overlap. If a silent overlap occurs, strange runtime errors might
 * happen, because we might overlap stack, libraries, anything else.
 *
 * Since we always fork+exec same binary (filebench), theoretically all the
 * mappings should be the same, so no overlap should happen. However, if
 * virtual Address Space Layout Randomization (ASLR) is enabled on the target
 * machine - overlap is very likely (especially if workload defines a lot of
 * processes). We observed numerous segmentation faults on CentOS because of
 * that.
 *
 * The function below disables ASLR in Linux. In future, more platform-specific
 * functions should be added.
 */

#include "filebench.h"
#include "aslr.h"

#if defined(HAVE_SYS_PERSONALITY_H)
#include <sys/personality.h>
#elif defined(HAVE_LINUX_PERSONALITY_H)
#include <linux/personality.h>
#endif

/*
 * Returns 0 if no action needs to be taken, 1 if the program must be
 * re-exec()'d.
 */
int
disable_aslr(void)
{
#if HAVE_DECL_ADDR_NO_RANDOMIZE
	int r;

	r = personality(0xffffffff);
	/* Already disabled, no need to re-exec self */
	if ((r != -1) && (r & ADDR_NO_RANDOMIZE))
		return 0;

	/* Toggle it on, then indicate need to re-exec() ourselves */
	r = personality(r | ADDR_NO_RANDOMIZE);
	if (r == -1) {
		filebench_log(LOG_ERROR, "Could not disable ASLR");
		return 0;
	}

	return 1;

#else /* HAVE_DECL_ADDR_NO_RANDOMIZE */

	filebench_log(LOG_INFO, "Per-process disabling of ASLR is not "
				"supported on this system. "
				"For Filebench to work properly, "
				"disable ASLR manually for the whole system. "
				"On Linux it can be achieved by "
				"\"sysctl  kernel.randomize_va_space=0\" command. "
				"(the change does not persist across reboots)");

	return 0;

#endif /* HAVE_DECL_ADDR_NO_RANDOMIZE */
}
