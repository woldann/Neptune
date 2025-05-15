/*
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#ifdef DISABLE_LOGS

#ifdef LOG_LEVEL
#undef LOG_LEVEL
#define LOG_LEVEL 0
#endif // LOG_LEVEL

#ifdef LOG_LEVEL_3
#undef LOG_LEVEL_3
#endif // LOG_LEVEL_3

#ifdef LOG_LEVEL_2
#undef LOG_LEVEL_2
#endif // LOG_LEVEL_2

#ifdef LOG_LEVEL_1
#undef LOG_LEVEL_1
#endif // LOG_LEVEL_1

#else // !DISABLE_LOGS

#ifndef LOG_LEVEL
#define LOG_LEVEL 0
#endif // !LOG_LEVEL

#if LOG_LEVEL < 0
#undef LOG_LEVEL
#define LOG_LEVEL 0
#endif // LOG_LEVEL < 0

#if LOG_LEVEL == 3
#ifndef LOG_LEVEL_3
#define LOG_LEVEL_3
#endif // !LOG_LEVEL_3
#endif // LOG_LEVEL == 3

#if LOG_LEVEL == 2
#ifndef LOG_LEVEL_2
#define LOG_LEVEL_2
#endif // !LOG_LEVEL_2
#endif // LOG_LEVEL == 2

#if LOG_LEVEL == 1
#ifndef LOG_LEVEL_1
#define LOG_LEVEL_1
#endif // !LOG_LEVEL_1
#endif // LOG_LEVEL == 1

#ifdef LOG_LEVEL_3

#ifndef LOG_LEVEL_2
#define LOG_LEVEL_2
#endif // !LOG_LEVEL_2

#if LOG_LEVEL < 3
#undef LOG_LEVEL
#define LOG_LEVEL 3
#endif // LOG_LEVEL < 3

#endif // LOG_LEVEL_3

#ifdef LOG_LEVEL_2
#ifndef LOG_LEVEL_1
#define LOG_LEVEL_1
#endif // !LOG_LEVEL_1

#if LOG_LEVEL < 2
#undef LOG_LEVEL
#define LOG_LEVEL 2
#endif // LOG_LEVEL < 2

#endif // LOG_LEVEL_2

#ifdef LOG_LEVEL_1
#if LOG_LEVEL < 1
#undef LOG_LEVEL
#define LOG_LEVEL 1
#endif // LOG_LEVEL < 1
#endif // LOG_LEVEL_1

#endif // !DISABLE_LOGS
