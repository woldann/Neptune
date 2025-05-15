/*
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#ifndef __NTIME_H__
#define __NTIME_H__

#include "neptune.h"

typedef uint64_t ntime_t; 

extern ntime_t ntime_st;

nerror_t ntime_init(void);

ntime_t ntime_gu(void);

ntime_t ntime_ge(void);

void ntime_ge_str(char *str);

#endif // !__NTIME_H__
