/**
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

/**
 * @file nmem.h
 * @brief Neptune library - Memory management subsystem.
 *
 * This header defines simple macros that wrap the standard C library
 * memory management functions for allocation, reallocation, and freeing:
 * - `N_ALLOC(size)` for `malloc`
 * - `N_REALLOC(addr, new_size)` for `realloc`
 * - `N_FREE(addr)` for `free`
 *
 * These macros provide a consistent interface for dynamic memory operations
 * throughout the Neptune project.
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
