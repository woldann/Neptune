/*
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#include "nfile.h"

#if defined(NFILE_DISABLE_WRITE) && NFILE_DISABLE_WRITE == 1

#ifdef LOG_LEVEL_1
#undef LOG_LEVEL_1
#endif // LOG_LEVEL_1

#ifdef LOG_LEVEL_2
#undef LOG_LEVEL_2
#endif // LOG_LEVEL_2

#ifdef LOG_LEVEL_3
#undef LOG_LEVEL_3
#endif // LOG_LEVEL_3

#ifdef LOG_LEVEL
#undef LOG_LEVEL
#endif // LOG_LEVEL

#endif // defined(NFILE_DISABLE_WRITE) && NFILE_DISABLE_WRITE == 1

#include "loghelper.h"

#ifdef LOG_LEVEL_1
#ifndef __LOG_H__
#define __LOG_H__

#include "color.h"
#include "nerror.h"

#ifndef LOG_ON_STDOUT
#ifdef MODULE
#define LOG_ON_STDOUT 0
#else // !MODULE
#define LOG_ON_STDOUT 1
#endif // !MODULE
#endif // !LOG_ON_STDOUT

#define LOG_INFO_COLOR COLOR_CYAN
#define LOG_WARN_COLOR COLOR_YELLOW
#define LOG_ERROR_COLOR COLOR_RED

#define LOG_FILE_DONT_CLOSE 0x01
#define LOG_FILE_DONT_FLUSH 0x02

#define LOG_FILE_PRINT_TIME 0x04
#define LOG_FILE_PRINT_TYPE 0x08
#define LOG_FILE_PRINT_MSG 0x10
#define LOG_FILE_PRINT_ENDL 0x20

#define LOG_FILE_COLORABLE 0x80

#ifndef LOG_SFILE_MASK
#ifdef __WIN32

#define LOG_TEMP_SFILE_MASK                                                    \
	(LOG_FILE_PRINT_TIME | LOG_FILE_PRINT_TYPE | LOG_FILE_PRINT_MSG | \
	 LOG_FILE_PRINT_ENDL | LOG_FILE_DONT_CLOSE)

#ifdef LOG_FORCE_COLOR
#define LOG_SFILE_MASK LOG_TEMP_SFILE_MASK | LOG_FILE_COLORABLE
#else // !LOG_FORCE_COLOR
#define LOG_SFILE_MASK LOG_TEMP_SFILE_MASK
#endif // !LOG_FORCE_COLOR

#else // !__WIN32

#define LOG_SFILE_MASK                                                    \
	(LOG_FILE_PRINT_TIME | LOG_FILE_PRINT_TYPE | LOG_FILE_PRINT_MSG | \
	 LOG_FILE_PRINT_ENDL | LOG_FILE_DONT_CLOSE | LOG_FILE_COLORABLE)

#endif // !__WIN32

#endif // !LOG_SFILE_MASK

#ifndef LOG_DFILE_MASK

#define LOG_DFILE_MASK                                                    \
	(LOG_FILE_PRINT_TIME | LOG_FILE_PRINT_TYPE | LOG_FILE_PRINT_MSG | \
	 LOG_FILE_PRINT_ENDL)

#endif // !LOG_DFILE_MASK

#define LOG_ERROR_S 0x6100
#define LOG_ALLOC_ERROR 0x6101
#define LOG_REALLOC_ERROR 0x6102
#define LOG_NFILE_OPEN_W_ERR 0x6103
#define LOG_ERROR_E LOG_NFILE_OPEN_W_ERR

#define LOG_INFO_TEXT "INFO"
#define LOG_WARN_TEXT "WARN"
#define LOG_ERROR_TEXT "ERROR"

#define LOG_CLASS_TIME LOG_FILE_PRINT_TIME
#define LOG_CLASS_TYPE LOG_FILE_PRINT_TYPE
#define LOG_CLASS_MSG LOG_FILE_PRINT_MSG
#define LOG_CLASS_ENDL LOG_FILE_PRINT_ENDL

typedef int8_t log_file_flags_t;

struct log_file {
	nfile_t file;
	log_file_flags_t file_flags;
};

typedef struct log_file log_file_t;

void log_set_color(color_t color);

nerror_t log_reg_file_ex(nfile_t file, log_file_flags_t file_flags);

nerror_t log_reg_file(nfile_path_t path);

bool log_can_out(void);

nerror_t log_info(const char *format, ...);

nerror_t log_warn(const char *format, ...);

nerror_t log_error(const char *format, ...);

nerror_t log_init(void);

void log_destroy(void);

nerror_t log_log_v(color_t color, const char *type, const char *format,
		   va_list list);

nerror_t log_log(color_t color, const char *type, const char *format, ...);

#define LOG_V(color, type, format, list) log_log_v(color, type, format, list)
#define LOG(color, type, format, ...) \
	log_log(color, type, format, ##__VA_ARGS__)

#define LOG_INFO(format, ...) log_info(format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) log_warn(format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) log_error(format, ##__VA_ARGS__)

#endif // !__LOG_H__
#else // !LOG_LEVEL_1
#define log_can_out() (false)
#endif // !LOG_LEVEL_1
