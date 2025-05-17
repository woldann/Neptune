/**
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#include "nerror.h"

#if NERROR_LEVEL == 1

nerror_t nerror_create(nerror_t error)
{
	if (error == N_OK)
		return N_OK;

#ifdef LOG_LEVEL_1
	log_error("An error created, code: %d 0x%X", error, error);
#endif /* ifdef LOG_LEVEL_1 */

	return true;
}

#endif /* if NERROR_LEVEL == 1 */
