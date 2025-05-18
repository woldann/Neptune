/*
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

/**
 * @file nfile.h
 * @brief Platform-independent file handling abstraction for the Neptune library.
 *
 * This header provides a unified interface for basic file operations such as open, read,
 * write, print, and delete — compatible with multiple platforms and execution contexts.
 *
 * The file operations are selectively enabled or disabled at compile time using
 * macros such as `NFILE_DISABLE_READ`, `NFILE_DISABLE_WRITE`, or `NFILE_DISABLE`.
 * This allows fine-grained control over the feature set to optimize footprint and
 * platform-specific requirements.
 *
 */

#ifndef __NFILE_H__
#define __NFILE_H__

#ifdef MODULE

#include <linux/types.h>
#include <linux/fs.h>

#define NFILE_MAX_PRINTF_LENGTH 256
#define NFILE_MAX_PATH_LENGTH 256

typedef struct file *nfile_t;

#define NFILE_FLUSH(nfile) \
	do {               \
	} while (0)

void nfile_close(nfile_t nfile);

#define NFILE_CLOSE(nfile) nfile_close(nfile)

#else // !MODULE

#include <stdio.h>
#include <wchar.h>

typedef FILE *nfile_t;

#define NFILE_FLUSH(nfile) fflush(nfile)
#define NFILE_CLOSE(nfile) fclose(nfile)

#endif // !MODULE

#ifdef __WIN32

typedef wchar_t nfile_char_t;
#define NFILE_MAX_PATH_LENGTH MAX_PATH

#else // !__WIN32

typedef char nfile_char_t;

#endif // __WIN32

typedef nfile_char_t *nfile_path_t;

#include "neptune.h"

#ifdef __WIN32
#define NFILE_PATH_GET_LENGTH(nfile_path) ((size_t)wcslen(nfile_path))
#else // !__WIN32
#define NFILE_PATH_GET_LENGTH(nfile_path) ((size_t)strlen(nfile_path))
#endif // !__WIN32

#define NFILE_PATH_CALC_SIZE(length) ((length + 1) * sizeof(nfile_char_t))
#define NFILE_PATH_GET_SIZE(nfile_path) \
	(NFILE_PATH_CALC_SIZE(NFILE_PATH_GET_LENGTH(nfile_path)))
#define NFILE_MAX_PATH_SIZE (NFILE_PATH_CALC_SIZE(NFILE_MAX_PATH_LENGTH))

#if defined(NFILE_DISABLE_READ) && defined(NFILE_DISABLE_WRITE)
#if NFILE_DISABLE_READ == 1 && NFILE_DISABLE_WRITE == 1

#ifdef NFILE_DISABLE
#undef NFILE_DISABLE
#endif // NFILE_DISABLE

#define NFILE_DISABLE 1

#endif // NFILE_DISABLE_READ == 1 && NFILE_DISABLE_WRITE == 1
#endif // defined(NFILE_DISABLE_READ) && defined(NFILE_DISABLE_WRITE)

#if defined(NFILE_DISABLE) && NFILE_DISABLE == 1

#ifdef NFILE_DISABLE_READ
#undef NFILE_DISABLE_READ
#endif // NFILE_DISABLE_READ

#ifdef NFILE_DISABLE_WRITE
#undef NFILE_DISABLE_WRITE
#endif // NFILE_DISABLE_WRITE

#ifdef NFILE_DISABLE_RDWR
#undef NFILE_DISABLE_RDWR
#endif // NFILE_DISABLE_RDWR

#define NFILE_DISABLE_READ 1
#define NFILE_DISABLE_WRITE 1
#define NFILE_DISABLE_RDWR 1

#else // !defined(NFILE_DISABLE) || NFILE_DISABLE != 1

#if !defined(NFILE_DISABLE_READ) || NFILE_DISABLE_READ != 1

nfile_t nfile_open_r(const nfile_path_t pathname);

ssize_t nfile_read_o(nfile_t nfile, ssize_t offset, void *buffer,
		     ssize_t length);

ssize_t nfile_read(nfile_t nfile, void *buffer, ssize_t length);

#define NFILE_OPEN_R(pathname) nfile_open_r(pathname)

#define NFILE_READ_O(nfile, buffer, length, offset) \
	nfile_read_o(nfile, buffer, length, offset)

#define NFILE_READ(nfile, buffer, length) nfile_read(nfile, buffer, length)

#endif // !defined(NFILE_DISABLE_READ) || NFILE_DISABLE_READ != 1

#if !defined(NFILE_DISABLE_WRITE) || NFILE_DISABLE_WRITE != 1

nfile_t nfile_open_w(const nfile_path_t pathname);

ssize_t nfile_write_o(nfile_t nfile, ssize_t offset, const void *buffer,
		      ssize_t length);

ssize_t nfile_write(nfile_t nfile, const void *buffer, ssize_t length);

ssize_t nfile_printf_ov(nfile_t nfile, ssize_t offset, const char *format,
			va_list args);

ssize_t nfile_printf_o(nfile_t nfile, ssize_t offset, const char *format, ...);

ssize_t nfile_printf_v(nfile_t nfile, const char *format, va_list args);

ssize_t nfile_printf(nfile_t nfile, const char *format, ...);

#define NFILE_OPEN_W(pathname) nfile_open_w(pathname)

#define NFILE_WRITE_O(nfile, buffer, length, offset) \
	nfile_write_o(nfile, buffer, length, offset)

#define NFILE_WRITE(nfile, buffer, length) nfile_write(nfile, buffer, length)

#define NFILE_PRINTF_OV(nfile, offset, format, args) \
	nfile_printf_ov(nfile, offset, format, args)

#define NFILE_PRINTF_O(nfile, offset, format, ...) \
	nfile_printf_v(nfile, offset, format, ##__VA_ARGS__)

#define NFILE_PRINTF_V(nfile, format, args) nfile_printf_v(nfile, format, args)

#define NFILE_PRINTF(nfile, format, ...) \
	nfile_printf_v(nfile, format, ##__VA_ARGS__)

#endif // !defined(NFILE_DISABLE_WRITE) || NFILE_DISABLE_WRITE != 1

#if !defined(NFILE_DISABLE_RDWR) || NFILE_DISABLE_RDWR != 1
#if (defined(NFILE_DISABLE_READ) && NFILE_DISABLE_READ == 1) || \
	(defined(NFILE_DISABLE_WRITE) && NFILE_DISABLE_WRITE == 1)

#ifdef NFILE_DISABLE_RDWR
#undef NFILE_DISABLE_RDWR
#endif // NFILE_DISABLE_RDWR

#define NFILE_DISABLE_RDWR 1

#endif // (defined(NFILE_DISABLE_READ) && NFILE_DISABLE_READ == 1) || (defined(NFILE_DISABLE_WRITE) && NFILE_DISABLE_WRITE == 1)
#endif // !defined(NFILE_DISABLE_RDWR) || NFILE_DISABLE_RDWR != 1

#if !defined(NFILE_DISABLE_RDWR) || NFILE_DISABLE_RDWR != 1

nfile_t nfile_open_rw(const nfile_path_t pathname);

nfile_t nfile_open_wr(const nfile_path_t pathname);

#endif // !defined(NFILE_DISABLE_RDWR) || NFILE_DISABLE_RDWR != 1

void nfile_delete(const nfile_path_t path);

#define NFILE_DELETE(nfile) nfile_delete(nfile)

ssize_t nfile_get_length(nfile_t nfile);

#define NFILE_GET_LENGTH(nfile) nfile_get_length(nfile)

#endif // !defined(NFILE_DISABLE) || NFILE_DISABLE != 1
#endif // !__FILE_H__
