#ifndef _FB_POSSET_H
#define	_FB_POSSET_H

#include "filebench.h"

/* Types of position sets */
#define POSSET_TYPE_RND 	1
#define POSSET_TYPE_COLLECTION	2

/* Maxiumum number of positions in a single position set */
#define POSSET_MAX_ENTRIES	512

/* Allign random position by this value */
#define POSSET_POS_ALIGNMENT	512

struct posset {
	avd_t ps_name;
	/* type: currently only random type is supported */
	avd_t ps_type;
	avd_t ps_rnd_max;
	avd_t ps_rnd_seed;
	avd_t ps_entries;
	struct posset *ps_next;
	uint64_t ps_positions[POSSET_MAX_ENTRIES];
};

extern struct posset *
posset_alloc(avd_t name, avd_t type, avd_t seed, avd_t max, avd_t entries);
extern struct posset *
posset_find(char *name);

#endif /* _FB_POSSET_H */

