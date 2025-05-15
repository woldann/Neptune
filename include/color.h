/*
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#ifndef __COLOR_H__
#define __COLOR_H__

typedef const char *color_t;

#define COLOR_RESET ((color_t) "\033[0m")
#define COLOR_BLACK ((color_t) "\033[0;30m")
#define COLOR_RED ((color_t) "\033[0;31m")
#define COLOR_GREEN ((color_t) "\033[0;32m")
#define COLOR_YELLOW ((color_t) "\033[0;33m")
#define COLOR_BLUE ((color_t) "\033[0;34m")
#define COLOR_MAGENTA ((color_t) "\033[0;35m")
#define COLOR_CYAN ((color_t) "\033[0;36m")
#define COLOR_WHITE ((color_t) "\033[0;37m")

#define COLOR_BOLD_BLACK ((color_t) "\033[1;30m")
#define COLOR_BOLD_RED ((color_t) "\033[1;31m")
#define COLOR_BOLD_GREEN ((color_t) "\033[1;32m")
#define COLOR_BOLD_YELLOW ((color_t) "\033[1;33m")
#define COLOR_BOLD_BLUE ((color_t) "\033[1;34m")
#define COLOR_BOLD_MAGENTA ((color_t) "\033[1;35m")
#define COLOR_BOLD_CYAN ((color_t) "\033[1;36m")
#define COLOR_BOLD_WHITE ((color_t) "\033[1;37m")

#endif // !__COLOR_H__
