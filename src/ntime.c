/**
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#include "ntime.h"

ntime_t ntime_start;

nerror_t ntime_init(void)
{
	ntime_start = ntime_get_unix();
	return N_OK;
}

ntime_t ntime_get_unix(void)
{
#ifdef MODULE

#include <linux/ktime.h>
#include <linux/timekeeping.h>

	struct timespec64 ts;
	ktime_get_real_ts64(&ts);
	return (ntime_t)ts.tv_sec;

#else /* ifndef MODULE */

#include <time.h>

	return (ntime_t)time(NULL);

#endif /* ifndef MODULE */
}

ntime_t ntime_get_elapsed(void)
{
	return ntime_get_unix() - ntime_start;
}

void ntime_get_elapsed_str(char *str)
{
	ntime_t sec = ntime_get_elapsed();
	ntime_t min = sec / 60;
	ntime_t hour = min / 60;

	sec %= 60;
	min %= 60;
	hour %= 24;

	str[0] = '0' + hour / 10;
	str[1] = '0' + hour % 10;
	str[2] = ':';
	str[3] = '0' + min / 10;
	str[4] = '0' + min % 10;
	str[5] = ':';
	str[6] = '0' + sec / 10;
	str[7] = '0' + sec % 10;
}
