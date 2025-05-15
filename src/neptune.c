/*
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#include "neptune.h"
#include "nerror.h"
#include "ninit.h"

typedef nerror_t (*neptune_init_fn)(void);

typedef nerror_t (*neptune_init_fn)(void);
typedef void (*neptune_destroy_fn)(void);

#define NEPTUNE_MODULE_INIT(init_fn)
#define NEPTUNE_MODULE_DESTROY(destroy_fn)
#define NEPTUNE_MODULE(init_fn, destroy_fn)

#include NEPTUNE_MODULERULES_HEADER

#undef NEPTUNE_MODULE
#undef NEPTUNE_MODULE_INIT
#undef NEPTUNE_MODULE_DESTROY

#define NEPTUNE_MODULE_INIT(init_fn) ((neptune_init_fn) (init_fn)),
#define NEPTUNE_MODULE_DESTROY(destroy_fn)
#define NEPTUNE_MODULE(init_fn, destroy_fn) NEPTUNE_MODULE_INIT(init_fn)

neptune_init_fn neptune_init_funcs[] = {
    #include NEPTUNE_MODULERULES_HEADER
};

#undef NEPTUNE_MODULE
#undef NEPTUNE_MODULE_INIT
#undef NEPTUNE_MODULE_DESTROY

#define NEPTUNE_MODULE_INIT(init_fn)
#define NEPTUNE_MODULE_DESTROY(destroy_fn) ((neptune_destroy_fn) (destroy_fn)),
#define NEPTUNE_MODULE(init_fn, destroy_fn) NEPTUNE_MODULE_DESTROY(destroy_fn)

neptune_destroy_fn neptune_destroy_funcs[] = {
    #include NEPTUNE_MODULERULES_HEADER
};

#undef NEPTUNE_MODULE
#undef NEPTUNE_MODULE_INIT
#undef NEPTUNE_MODULE_DESTROY

nerror_t neptune_init()
{
	size_t init_func_count =
		sizeof(neptune_init_funcs) / sizeof(*neptune_init_funcs);

	for (size_t i = 0; i < init_func_count; i++) {
		if (HAS_ERR(neptune_init_funcs[i]())) {
			nerror_t error = GET_ERR(NEPTUNE_INIT_ERROR + i);
			neptune_destroy();
			return error;
		}
	}

#ifdef MODULE

#else /* ifndef MODULE */
	srand(ntime_st);
#endif /* ifndef MODULE */

	return N_OK;
}

void neptune_destroy()
{
	size_t destroy_func_count =
		sizeof(neptune_destroy_funcs) / sizeof(*neptune_destroy_funcs);

	for (size_t i = 0; i < destroy_func_count; i++)
		neptune_destroy_funcs[i]();
}

#ifndef memmem

void *memmem(register const void *haystack, size_t haystacklen,
	     const void *needle, size_t needlelen)
{
	if (haystacklen < needlelen)
		return NULL;

	const void *end = haystack + haystacklen - needlelen;
	while (haystack <= end) {
		if (memcmp(haystack, needle, needlelen) == 0)
			return (void *)haystack;

		haystack++;
	}

	return NULL;
}

#endif /* ifndef memmem */

#ifndef memstr

void *memstr(register const void *haystack, const char *needle,
	     size_t haystacklen)
{
	return memmem(haystack, haystacklen, needle, strlen(needle));
}

#endif /* ifndef memstr */
