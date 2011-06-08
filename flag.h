#ifndef _FB_FLAG_H
#define	_FB_FLAG_H

typedef volatile int flag_t;

static inline void clear_flag(flag_t *flag)
{
	*flag = 0;
}

static inline void set_flag(flag_t *flag)
{
	*flag = 1;
}

static inline int query_flag(flag_t *flag)
{
	return (*flag) != 0;
}

static inline void wait_flag(flag_t *flag)
{
	while (!query_flag(flag))
		; /* Do nothing */
}

#endif /* _FB_FLAG_H */

