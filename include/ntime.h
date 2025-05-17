/**
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

/**
 * @file ntime.h
 * @brief Neptune library - Time management subsystem.
 *
 * Provides basic time-related functionality including initialization,
 * obtaining the current Unix timestamp, measuring elapsed time since
 * subsystem start, and formatting elapsed time as a string.
 *
 * Designed for minimal overhead and cross-platform compatibility.
 */

#ifndef __NTIME_H__
#define __NTIME_H__

#include "neptune.h"


typedef uint64_t ntime_t;  /**< Type representing time values */

/** 
 * @brief External global variable storing the system start time.
 *
 * Typically set during initialization to mark the reference point
 * for elapsed time calculations.
 */
extern ntime_t ntime_st;

/**
 * @brief Initialize the time subsystem.
 *
 * This function sets up the necessary state for time measurements,
 * including initializing the system start time reference.
 *
 * @return Error code indicating success or failure.
 */
nerror_t ntime_init(void);

/**
 * @brief Retrieve the current Unix timestamp.
 *
 * Returns the number of seconds elapsed since the Unix epoch (January 1, 1970).
 *
 * @return Current Unix timestamp.
 */
ntime_t ntime_get_unix(void);

/**
 * @brief Get the elapsed time since the time subsystem was initialized.
 *
 * Calculates the time difference between the current time and the
 * stored start time.
 *
 * @return Elapsed time in seconds.
 */
ntime_t ntime_get_elapsed(void);

/**
 * @brief Write the elapsed time as a human-readable string in "HH:MM:SS" format.
 *
 * Formats the elapsed time (since initialization) into a fixed-length string
 * representing hours, minutes, and seconds, and writes it into the provided buffer.
 *
 * @param str Pointer to a character buffer of at least 8 bytes.
 *            The formatted string will have the format "HH:MM:SS" and is NOT null-terminated.
 *
 * @note The buffer must be exactly 8 bytes to hold the output.
 */
void ntime_get_elapsed_str(char *str);


#endif // !__NTIME_H__
