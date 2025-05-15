/*
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#include "neptune.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	if (HAS_ERR(neptune_init())) {
		printf("neptune_init failed\n");
		return 1;
	}

#ifdef LOG_LEVEL_1
	LOG_INFO("Test Log");

	char testlog_file[] = "testneptune.log";

#ifdef __WIN32
	wchar_t testlog_file_u[] = L"testneptune.log";
  void *reg_log_file_addr = testlog_file_u;
#else /* ifndef __WIN32 */
  void *reg_log_file_addr = testlog_file;
#endif /* ifndef __WIN32 */


	char testlog_msg[] = "neptune_reigster_log_file check!";

	if (HAS_ERR(log_reg_file(reg_log_file_addr))) {
		printf("reg_log_file failed\n");
    neptune_destroy();
		return 2;
	}

	LOG_INFO(testlog_msg);
#endif /* ifdef LOG_LEVEL_1 */

#ifdef LOG_LEVEL_1
	neptune_destroy();

	FILE *file = fopen(testlog_file, "rb");
	if (file == NULL) {
		printf("file not found\n");
    return 3;
	}

  fseek(file, 0, SEEK_END);
  long file_length = ftell(file);

  if (file_length < sizeof(testlog_msg) + 5) {
    printf("file write error\n");
    return 4;
  }

  fseek(file, (long) -sizeof(testlog_msg), SEEK_END);

  char buffer[sizeof (testlog_msg)];
  fread (buffer, 1, sizeof (testlog_msg), file);
  fclose (file);

  if (buffer[sizeof(buffer) - 1] != '\n') {
    printf("Invalid EOL\n");
    return 5;
  }

  buffer[sizeof(buffer) - 1] = 0;

  if (memcmp(testlog_msg, buffer, sizeof (buffer)) != 0) {
    printf("logs not equal\n");
    return 6;
  }

#endif /* ifdef LOG_LEVEL_1 */

  printf("Everything is OK!!!\n");
	return EXIT_SUCCESS;
}
