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

#include <sys/personality.h>

#include "filebench.h"
#include "aslr.h"

#ifdef HAVE_SYS_PERSONALITY_H
void
linux_disable_aslr()
{
	int old;
	int r;

	old = personality(0xffffffff);
	r = personality(0xffffffff | ADDR_NO_RANDOMIZE);
	if (r == -1)
		filebench_log(LOG_ERROR, "Could not disable ASLR");
}
#else /* HAVE_SYS_PERSONALITY_H */
void
other_disable_aslr()
{
	filebench_log(LOG_INFO, "Disabling ASLR is not "
				"supported on this platform");
}

#endif /* HAVE_SYS_PERSONALITY_H */
