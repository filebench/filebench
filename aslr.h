#ifndef _ASLR_H
#define _ASLR_H

#include <filebench.h>

#if defined(HAVE_SYS_PERSONALITY_H) && defined(HAVE_ADDR_NO_RANDOMIZE)
extern void
linux_disable_aslr();

static inline void
disable_aslr()
{
	return linux_disable_aslr();
}
#else /* HAVE_SYS_PERSONALITY_H && HAVE_ADDR_NO_RANDOMIZE */
extern void
other_disable_aslr();

static inline void
disable_aslr() {
	return other_disable_aslr();
}
#endif /* HAVE_SYS_PERSONALITY_H && HAVE_ADDR_NO_RANDOMIZE */

#endif /* _ASLR_H */
