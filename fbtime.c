#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "fbtime.h"
#include "config.h"
#include "filebench.h"

/*
 * If we dont have gethrtime() function provided by the environment
 * (which is usually provided only by Solaris), then we either use
 * gettimeofdate() or RDTSC instruction (if user requested).
 */

#ifndef HAVE_GETHRTIME
#ifdef USE_RDTSC

/*
 * Multiplier to convert CPU cycles returned by rdtsc() to nanoseconds.  In
 * other words nanoseconds per CPU cycle. E.g.,  for a 1GHz CPU it is equal to
 * 1.0.  For currently available systems the factor varies between 10.0
 * (100MHz) to 0.2 (5GHz).
 *
 * Notice, we do not take into account CPU frequency scaling. Therefore,
 * results might be incorrect for sytems that use CPU frequency scaling.
 *
 */
static double rdtsc2nan_mul = 0;

/*
 * Uses the rdtsc instruction to get high resolution (cpu
 * clock ticks) time. Only used for explicitly requested
 * non-Solaris compiles.
 */
__inline__  uint64_t
rdtsc(void)
{
	unsigned long long int x;
	__asm__ volatile(".byte 0x0f, 0x31" : "=A" (x));
	return x;
}

/*
 * Get high resolution time in nanoseconds. This is the version used when
 * explicitly requested on non-Solaris systems. It uses rdtsc call to get
 * clock ticks and converts to nanoseconds.
 */
hrtime_t
gethrtime(void)
{
	hrtime_t hrt;

	/* convert to nanosecs and return */
	hrt = rdtsc() * rdtsc2nan_mul;

	return hrt;
}

/*
 * Gets CPU clock frequency in MHz from cpuinfo file.
 * Converts to cpu_hz and stores in cpu_hz global uint64_t.
 * Only used for non-Solaris compiles.
 */
static uint64_t
parse_cpu_hz(void)
{
	/*
	 * Parse the following from /proc/cpuinfo.
	 * cpu MHz		: 2191.563
	 */
	FILE *cpuinfo;
	double hertz = -1;
	uint64_t hz;

	cpuinfo = fopen("/proc/cpuinfo", "r");
	if (!cpuinfo) {
		filebench_log(LOG_ERROR, "open /proc/cpuinfo failed: %s",
		    strerror(errno));
		filebench_shutdown(1);
	}

	while (!feof(cpuinfo)) {
		char buffer[80];

		fgets(buffer, 80, cpuinfo);
		if (!strlen(buffer))
			continue;
		if (!strncasecmp(buffer, "cpu MHz", 7)) {
			char *token = strtok(buffer, ":");

			if (token) {
				token = strtok((char *)NULL, ":");
				hertz = strtod(token, NULL);
			}
			break;
		}
	}

	hz = hertz * 1000000;

	fclose(cpuinfo);

	return hz;
}
#else /* USE_RDTSC */

/*
 * Get high resolution time in nanoseconds. This is the version used if
 * compiled for non-Solaris systems. It calls gettimeofday to get current time
 * and converts it to nanoseconds.
 */
hrtime_t
gethrtime(void)
{
	struct timeval tv;
	hrtime_t hrt;

	gettimeofday(&tv, NULL);

	hrt = (hrtime_t)tv.tv_sec * 1000000000UL +
	    (hrtime_t)tv.tv_usec * 1000UL;

	return hrt;
}
#endif /* USE_RDTSC */
#endif /* HAVE_GETHRTIME */

/*
 * In case if rdtsc is used, sets the cpu clock frequency variable or shuts
 * down the run if one is not found.
 */
void
clock_init(void)
{
#if !defined(HAVE_GETHRTIME) && defined(USE_RDTSC)
	uint64_t cpu_hz;

	cpu_hz = parse_cpu_hz();
	if (cpu_hz <= 0) {
		filebench_log(LOG_ERROR, "Error getting CPU Mhz: %s",
		    strerror(errno));
		filebench_shutdown(1);
	}

	rdtsc2nan_mul = 1000000000.0 / cpu_hz;
#endif
}
