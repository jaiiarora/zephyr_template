/*
 * Copyright (c) 2021, SAMSUNG
 *
 * SPDX-License-Identifier: Apache-2.0
 */


 /**
  * @file
  * @brief System/hardware module for
  *
  * This module provides routines to initialize and support board-level hardware
  * for the Samsung System On Chip.
  */


	#include <arch/cpu.h>
	#include <init.h>
	#include <soc.h>
	#include <kernel.h>

	/**
	 * @brief Perform basic hardware initialization at boot.
	 *
	 * @return 0
	 */
	static int sm_soc_init(const struct device *arg)
	{
		ARG_UNUSED(arg);

		/*
		 * Install default handler that simply resets the CPU
		 * if configured in the kernel, NOP otherwise.
		 */
		NMI_INIT();

		return 0;
	}

	SYS_INIT(sm_soc_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
