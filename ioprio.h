#ifndef _FB_IOPRIO_H
#define	_FB_IOPRIO_H

#ifdef HAVE_IOPRIO
extern void set_thread_ioprio(threadflow_t *);
#else
static inline void set_thread_ioprio(threadflow_t *tf)
{
	return;
}
#endif

#endif /* _FB_IOPRIO_H */
