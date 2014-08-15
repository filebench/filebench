#ifndef _ASLR_H
#define _ASLR_H

#include <filebench.h>

#ifdef HAVE_SYS_PERSONALITY_H
extern void
linux_disable_aslr();

static inline void
disable_aslr()
{
	return linux_disable_aslr();
}
#else /* HAVE_SYS_PERSONALITY_H */
extern void
other_disable_aslr();

static inline void
disable_aslr() {
	return other_disable_aslr();
}
#endif /* HAVE_SYS_PERSONALITY_H */

#endif /* _ASLR_H */
