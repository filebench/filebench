#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "fbtime.h"
#include "config.h"
#include "filebench.h"

/*
 * If we don't have gethrtime() function provided by the environment (which is
 * usually provided only by Solaris) then we use gettimeofdate().
 */

#ifndef HAVE_GETHRTIME
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
#endif /* HAVE_GETHRTIME */
