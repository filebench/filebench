#include "filebench.h"
#include "posset.h"

static int
posset_collection_fill(struct posset *ps)
{
	filebench_log(LOG_ERROR, "posset_alloc: possets of type "
			 "\"collection\" are not supported at the moment");
	return -1;
}

static int
posset_rnd_fill(struct posset *ps)
{
	uint64_t pos;
	int i;

	if (!avd_get_int(ps->ps_rnd_max)) {
		filebench_log(LOG_ERROR, "posset_rnd_fill: maximum value "
					"for random posset is not specified");
		return -1;
	}

	for (i = 0; i < avd_get_int(ps->ps_entries); i++) {
		if (!avd_get_int(ps->ps_rnd_seed)) {
			filebench_log(LOG_INFO, "seed was not specified,"
				"using /dev/urandom when filling posset");
			fb_urandom64(&pos, avd_get_int(ps->ps_rnd_max),
					POSSET_POS_ALIGNMENT, NULL);
		} else {
			/* XXX: this code below MUST eventually
					 be moved to fb_random.c */
			if (i == 0)
				srand(avd_get_int(ps->ps_rnd_seed));

			pos = ((double)rand() / RAND_MAX) *  UINT64_MAX;
			pos = pos / (UINT64_MAX / (avd_get_int(ps->ps_rnd_max)
						 + POSSET_POS_ALIGNMENT));
			if (pos > avd_get_int(ps->ps_rnd_max))
				pos = avd_get_int(ps->ps_rnd_max);

			pos = pos / POSSET_POS_ALIGNMENT;
			pos = pos * POSSET_POS_ALIGNMENT;
		}

		ps->ps_positions[i] = pos;
	}

	return 0;
}

struct posset *
posset_find(char *name)
{
	struct posset *ps;

	(void)ipc_mutex_lock(&filebench_shm->shm_posset_lock);
	ps = filebench_shm->shm_possetlist;
	while (ps) {
		if (!strcmp(avd_get_str(ps->ps_name), name))
			break;
		ps = ps->ps_next;
	}
	(void)ipc_mutex_unlock(&filebench_shm->shm_posset_lock);

	return ps;
}

struct posset *
posset_alloc(avd_t name, avd_t type, avd_t seed, avd_t max, avd_t entries)
{
	struct posset *ps;
	int ret;

	ps = (struct posset *)ipc_malloc(FILEBENCH_POSSET);
	if (!ps) {
		filebench_log(LOG_ERROR, "posset_alloc: " 
				"can't malloc posset in IPC region");
		return NULL;
	}

	/* we do not support any possets except "rnd" at the moment */
	if (!strcmp(avd_get_str(type), "rnd")) {
		ps->ps_type = avd_int_alloc(POSSET_TYPE_RND);
	} else if (!strcmp(avd_get_str(type), "collection")) {
		ps->ps_type = avd_int_alloc(POSSET_TYPE_COLLECTION);
	} else {
		filebench_log(LOG_ERROR, "posset_alloc: wrong posset type");
		ipc_free(FILEBENCH_POSSET, (char *)ps);
		return NULL;
	}

	ps->ps_name = name;
	ps->ps_rnd_seed = seed;
	ps->ps_rnd_max = max;
	ps->ps_entries = entries;

	if (avd_get_int(ps->ps_entries) > POSSET_MAX_ENTRIES) {
		filebench_log(LOG_ERROR, "posset_alloc: the number of posset "
							"entries is too high");
		ipc_free(FILEBENCH_POSSET, (char *)ps);
		return NULL;
	}

	/* depending on the posset type generate (or load) positions */
	switch (avd_get_int(ps->ps_type)) {
	case(POSSET_TYPE_RND):
		ret = posset_rnd_fill(ps);
		break;
	case(POSSET_TYPE_COLLECTION):
		ret = posset_collection_fill(ps);
		break;
	default:
		filebench_log(LOG_ERROR, "posset_alloc: wrong posset type");
		ipc_free(FILEBENCH_POSSET, (char *)ps);
		return NULL;
	}

	if (ret < 0) {
		filebench_log(LOG_ERROR, "posset_alloc: could not fill posset");
		ipc_free(FILEBENCH_POSSET, (char *)ps);
		return NULL;
	}

	/* add posset to the global list */
	(void)ipc_mutex_lock(&filebench_shm->shm_posset_lock);
	if (filebench_shm->shm_possetlist == NULL) {
		filebench_shm->shm_possetlist = ps;
		ps->ps_next = NULL;
	} else {
		ps->ps_next = filebench_shm->shm_possetlist;
		filebench_shm->shm_possetlist = ps;
	}
	(void)ipc_mutex_unlock(&filebench_shm->shm_posset_lock);


	return ps;
}
