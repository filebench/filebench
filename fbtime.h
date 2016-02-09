#ifndef _FBTIME_H
#define	_FBTIME_H

#include "config.h"

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

#define	FSECS (double)1000000000.0

#ifndef HAVE_GETHRTIME
typedef uint64_t hrtime_t;
#endif

hrtime_t gethrtime(void);
void clock_init();

#endif	/* _FBTIME_H*/
