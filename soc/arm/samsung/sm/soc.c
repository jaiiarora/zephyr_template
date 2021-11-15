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


	/*
	* Setup the various clocks on soc
	* According to the datasheet.
	*/

	static ALWAYS_INLINE void clock_init(void)
	{
		
	}


	/**
	 * @brief Perform basic hardware initialization at boot.
	 * Needs to run at the very beginning.
	 * So, init property has to be 0 (zero).
	 *@return 0
	 */
	static int sm_soc_init(const struct device *arg)
	{
		u32_t key;
		ARG_UNUSED(arg);

		key=irq_lock();

		/* Setup the master clocks */
		clock_init();

		/* Disable watchdog timers if not used by the System */


		/*
		 * Install default handler that simply resets the CPU
		 * if configured in the kernel, NOP otherwise.
		 */

		NMI_INIT();

		irq_unlock(key);
		return 0;
	}

	SYS_INIT(sm_soc_init, PRE_KERNEL_1, 0);
