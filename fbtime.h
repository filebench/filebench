#ifndef _FBTIME_H
#define	_FBTIME_H

#include "config.h"

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

#ifndef HAVE_GETHRTIME
typedef uint64_t hrtime_t;
hrtime_t gethrtime(void);
#endif

#define	SEC2NS_FLOAT (double)1000000000.0
#define	SEC2MS_FLOAT (double)1000000.0

#endif	/* _FBTIME_H*/
