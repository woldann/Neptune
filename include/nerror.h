/**
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

/**
 * @file nerror.h
 * @brief Flexible error handling system for the Neptune library.
 *
 * This header defines a lightweight, configurable error type (`nerror_t`) used across the Neptune project.
 * The behavior of the error system can be customized at compile time using the `NERROR_LEVEL` macro.
 *
 * Two error levels are supported:
 *
 * - `NERROR_LEVEL 1`: Use full error codes (e.g., `int` or `error_t`) for richer diagnostics.
 * - `NERROR_LEVEL 0`: Use a simple `true`/`false` boolean model for lightweight scenarios.
 *
 * This design allows developers to choose between detailed error reporting and minimal overhead,
 * depending on the use case (e.g., user-space vs kernel-space, debug vs release).
 */

#ifndef __NERROR_H__
#define __NERROR_H__

// Internal macro to temporarily define nerror_t if not already defined
#ifndef nerror_t
#define nerror_t int
#define undef_nerror_t 1
#endif // !nerror_t

#include "log.h" // Logging integration (optional for debug or error reporting)

#ifdef undef_nerror_t
#if undef_nerror_t == 1
#undef nerror_t
#endif // undef_nerror_t == 1
#endif // undef_nerror_t

// Set default error level if not explicitly defined
#ifndef NERROR_LEVEL
#ifdef LOG_LEVEL_1
#define NERROR_LEVEL 1
#else // !LOG_LEVEL_1
#define NERROR_LEVEL 0
#endif // !LOG_LEVEL_1
#endif // !NERROR_LEVEL

#if NERROR_LEVEL == 1

// Full error mode using error codes

#if !defined(__WIN32) && !defined(MODULE)
#include <bits/types/error_t.h> // Use standard error type if available
#endif // !defined(__WIN32) && !defined(MODULE)

#ifdef error_t
typedef error_t nerror_t;
#error "defined" // NOTE: This line looks suspicious—should this be here?
#else // !error_t
typedef int nerror_t;
#endif // !error_t

#define N_OK  0x00 // No error
#define N_ERR 0x01 // Generic error code

/**
 * @brief Create an nerror_t from a given error value.
 */
nerror_t nerror_create(nerror_t error);

#define HAS_ERROR(error) (error != N_OK)
#define GET_ERROR(error) nerror_create(error)

#elif NERROR_LEVEL == 0

// Minimal error mode using boolean values

typedef bool nerror_t;

#define N_OK  true  // No error
#define N_ERR false // Error occurred

#define HAS_ERROR(error) (error == N_ERR)
#define GET_ERROR(error) (N_ERR)

#endif // NERROR_LEVEL == 0

/**
 * @brief Return early if an error is detected.
 */
#define RET_ERROR(error)                  \
	do {                              \
		nerror_t __error = (error); \
		if (HAS_ERROR(__error))   \
			return __error;   \
	} while (0)

// Convenience macros
#define HAS_ERR(error) HAS_ERROR(error)
#define RET_ERR(error) RET_ERROR(error)
#define GET_ERR(error) GET_ERROR(error)

#endif // !__NERROR_H__

