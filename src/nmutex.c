/*
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#include "nmutex.h"

#ifndef MODULE

#ifdef __WIN32

HANDLE nmutex_init()
{
  return CreateMutex(NULL, FALSE, NULL);
}

void nmutex_lock(HANDLE nmutex)
{
  WaitForSingleObject(nmutex, INFINITE);
}

#else /* ifndef __WIN32 */

void nmutex_init(pthread_mutex_t *mutex)
{
  pthread_mutex_init(mutex, NULL);
}

#endif /* ifndef __WIN32 */

#endif /* ifndef MODULE */
