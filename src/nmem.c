/**
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#include "nmem.h"

#ifdef MODULE

void *nmem_alloc(size_t size)
{
	return kmalloc(size, GFP_KERNEL);
}

void *nmem_realloc(void *ptr, size_t size)
{
	return krealloc(ptr, size, GFP_KERNEL);
}

#endif /* ifdef MODULE */
