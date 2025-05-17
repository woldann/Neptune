/**
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

/**
 * @file nmutex.h
 * @brief Neptune library - Mutex managment subsystem.
 *
 * This header defines macros wrapping platform-specific mutex operations,
 * providing a uniform interface to initialize, lock, and unlock mutexes.
 *
 * Macros:
 * - `NMUTEX_INIT(mutex)`: Initialize the mutex.
 * - `NMUTEX_LOCK(mutex)`: Acquire the mutex lock.
 * - `NMUTEX_UNLOCK(mutex)`: Release the mutex lock.
 */

#ifndef __NMUTEX_H__
#define __NMUTEX_H__

#include "neptune.h"

#ifdef MODULE

#define NMUTEX struct mutex

#define NMUTEX_INIT(nmutex) mutex_init(&nmutex)
#define NMUTEX_LOCK(nmutex) mutex_lock(&nmutex)
#define NMUTEX_UNLOCK(nmutex) mutex_unlock(&nmutex)

#else // !MODULE

#ifdef __WIN32 

#define NMUTEX HANDLE

HANDLE nmutex_init();

void nmutex_lock(HANDLE nmutex);

#define NMUTEX_INIT(nmutex) (nmutex = nmutex_init())
#define NMUTEX_LOCK(nmutex) nmutex_lock(nmutex)
#define NMUTEX_UNLOCK(nmutex) ReleaseMutex(nmutex)
#define NMUTEX_DESTROY(nmutex) CloseHandle(nmutex)

#else // !__WIN32

#define NMUTEX pthread_mutex_t

void nmutex_init(pthread_mutex_t *mutex);

#define NMUTEX_INIT(nmutex) nmutex_init(&nmutex)
#define NMUTEX_LOCK(nmutex) pthread_mutex_lock(&nmutex)
#define NMUTEX_UNLOCK(nmutex) pthread_mutex_unlock(&nmutex)
#define NMUTEX_DESTROY(nmutex) pthread_mutex_destroy(&nmutex)

#endif // !__WIN32
#endif // !MODULE
#endif // !__MUTEX_H__
