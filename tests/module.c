/*
 * Copyright (C) 2024, 2025 Serkan Aksoy
 * All rights reserved.
 *
 * This file is part of the Neptune project.
 * It may not be copied or distributed without permission.
 */

#include "neptune.h"
#include "log.h"

static int __init neptune_module_init(void)
{
	printk(KERN_INFO "neptune module initializing");
	if (HAS_ERR(neptune_init())) {
    printk(KERN_ERR "neptune_init error");
		return 1;
	}

  LOG_INFO("log system check");
	return 0;
}

static void __exit neptune_module_exit(void)
{
	printk(KERN_INFO "neptune module is unloading\n");
  LOG_INFO("neptune_destroy check");
  neptune_destroy();
}

module_init(neptune_module_init);
module_exit(neptune_module_exit);
