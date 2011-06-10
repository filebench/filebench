#include "filebench.h"
#include "ioprio.h"

#ifdef HAVE_IOPRIO

static inline int ioprio_set(int which, int who, int ioprio)
{
	return syscall(__NR_ioprio_set, which, who, ioprio);
}

static inline int ioprio_get(int which, int who)
{
	return syscall(__NR_ioprio_get, which, who);
}

enum {
	IOPRIO_CLASS_NONE,
	IOPRIO_CLASS_RT,
	IOPRIO_CLASS_BE,
	IOPRIO_CLASS_IDLE,
};

enum {
	IOPRIO_WHO_PROCESS = 1,
	IOPRIO_WHO_PGRP,
	IOPRIO_WHO_USER,
};

#define IOPRIO_CLASS_SHIFT	13

void set_thread_ioprio(threadflow_t *tf)
{
	int ret;
	int ioprio = avd_get_int(tf->tf_ioprio);

	if (ioprio > 7)
		return;

	ret = ioprio_set(IOPRIO_WHO_PROCESS, 0,
			ioprio | IOPRIO_CLASS_BE << IOPRIO_CLASS_SHIFT);
	if (ret) {
		filebench_log(LOG_ERROR, "set_thread_ioprio: error while setting ioprio!");
		return;
	}

	ioprio = ioprio_get(IOPRIO_WHO_PROCESS, 0);
	ioprio = ioprio & 0xff;
	filebench_log(LOG_INFO, "ioprio set to %d for thread %s",
						ioprio, tf->tf_name);
}

#endif /* HAVE_IOPRIO */
