/*
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#ifndef __NMEM_H__
#define __NMEM_H__

#include "neptune.h"

#ifdef MODULE

void *nmem_alloc(size_t size);

void *nmem_realloc(void *ptr, size_t size);

#define N_ALLOC(size) nmem_alloc(size)
#define N_REALLOC(addr, new_size) nmem_realloc(addr, new_size)
#define N_FREE(addr) kfree(addr)

#else // MODULE

#define N_ALLOC(size) malloc(size)
#define N_REALLOC(addr, new_size) realloc(addr, new_size)
#define N_FREE(addr) free(addr)

#endif // MODULE
#endif // !__NMEM_H__
