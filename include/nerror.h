/*
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#ifndef __NERROR_H__
#define __NERROR_H__

#ifndef nerror_t
#define nerror_t int
#define undef_nerror_t 1
#endif // !nerror_t

#include "log.h"

#ifdef undef_nerror_t
#if undef_nerror_t == 1
#undef nerror_t
#endif // undef_nerror_t == 1
#endif // undef_nerror_t

#ifndef NERROR_LEVEL
#ifdef LOG_LEVEL_1
#define NERROR_LEVEL 1
#else // !LOG_LEVEL_1
#define NERROR_LEVEL 0
#endif // !LOG_LEVEL_1
#endif // !NERROR_LEVEL

#if NERROR_LEVEL == 1

#if !defined(__WIN32) && !defined(MODULE)
#include <bits/types/error_t.h>
#endif // !defined(__WIN32) && !defined(MODULE)

#ifdef error_t
typedef error_t nerror_t;
#error "defined"
#else // !error_t
typedef int nerror_t;
#endif // !error_t

#define N_OK 0x00
#define N_ERR 0x01

nerror_t nerror_create(nerror_t error);

#define HAS_ERROR(error) (error != N_OK)
#define GET_ERROR(error) nerror_create(error)

#elif NERROR_LEVEL == 0

typedef bool nerror_t;

#define N_OK true
#define N_ERR false

#define HAS_ERROR(error) (error == N_ERR)
#define GET_ERROR(error) (N_ERR)

#endif // NERROR_LEVEL == 0

#define RET_ERROR(error)                  \
	do {                              \
		nerror_t __error = (error); \
		if (HAS_ERROR(__error))   \
			return __error;   \
	} while (0)

#define HAS_ERR(error) HAS_ERROR(error)
#define RET_ERR(error) RET_ERROR(error)
#define GET_ERR(error) GET_ERROR(error)

#endif // !__NERROR_H__
