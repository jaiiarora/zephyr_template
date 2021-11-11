/*
 * Copyright (c) 2021, SAMSUNG
 *
 * SPDX-License-Identifier: Apache-2.0
 */


 /**
  * @file
  * @brief System/hardware module for Atmel SAM4S family processor
  *
  * This module provides routines to initialize and support board-level hardware
  * for the Samsung System On Chip.
  */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <soc.h>
#include <uart.h>
#include <linker/sections.h>
#include <fsl_common.h>
#include <fsl_clock.h>
#include <arch/cpu.h>
#include <cortex_m/exc.h>

/* ARM PLL configuration for RUN mode */
const clock_arm_pll_config_t armPllConfig = {
	.loopDivider = 100U
};

/* SYS PLL configuration for RUN mode */
const clock_sys_pll_config_t sysPllConfig = {
	.loopDivider = 1U
};

/* USB1 PLL configuration for RUN mode */
const clock_usb_pll_config_t usb1PllConfig = {
	.loopDivider = 0U
};

static void BOARD_BootClockGate(void)
{
	/* Disable all unused peripheral clocks */
	CCM->CCGR0 = CCM_CCGR0_CG15(0) | CCM_CCGR0_CG14(0) |
		     CCM_CCGR0_CG13(0) | CCM_CCGR0_CG12(0) |
		     CCM_CCGR0_CG11(3) | CCM_CCGR0_CG10(0) |
		     CCM_CCGR0_CG9(0) | CCM_CCGR0_CG8(0) |
		     CCM_CCGR0_CG7(0) | CCM_CCGR0_CG6(0) |
		     CCM_CCGR0_CG5(0) | CCM_CCGR0_CG4(0) |
		     CCM_CCGR0_CG3(0) | CCM_CCGR0_CG2(0) |
		     CCM_CCGR0_CG1(3) | CCM_CCGR0_CG0(3);

	CCM->CCGR1 = CCM_CCGR1_CG15(0) | CCM_CCGR1_CG14(3) |
		     CCM_CCGR1_CG13(0) | CCM_CCGR1_CG12(0) |
		     CCM_CCGR1_CG11(0) | CCM_CCGR1_CG10(0) |
		     CCM_CCGR1_CG9(0) | CCM_CCGR1_CG8(0) |
		     CCM_CCGR1_CG7(0) | CCM_CCGR1_CG6(0) |
		     CCM_CCGR1_CG5(0) | CCM_CCGR1_CG4(0) |
		     CCM_CCGR1_CG3(0) | CCM_CCGR1_CG2(0) |
		     CCM_CCGR1_CG1(0) | CCM_CCGR1_CG0(0);

	CCM->CCGR2 = CCM_CCGR2_CG15(3) | CCM_CCGR2_CG14(3) |
		     CCM_CCGR2_CG13(3) | CCM_CCGR2_CG12(3) |
		     CCM_CCGR2_CG11(0) | CCM_CCGR2_CG10(3) |
		     CCM_CCGR2_CG9(3) | CCM_CCGR2_CG8(3) |
		     CCM_CCGR2_CG7(0) | CCM_CCGR2_CG6(3) |
		     CCM_CCGR2_CG5(0) | CCM_CCGR2_CG4(0) |
		     CCM_CCGR2_CG3(0) | CCM_CCGR2_CG2(3) |
		     CCM_CCGR2_CG1(3) | CCM_CCGR2_CG0(3);

	CCM->CCGR3 = CCM_CCGR3_CG15(3) | CCM_CCGR3_CG14(3) |
		     CCM_CCGR3_CG13(0) | CCM_CCGR3_CG12(0) |
		     CCM_CCGR3_CG11(0) | CCM_CCGR3_CG10(0) |
		     CCM_CCGR3_CG9(0) | CCM_CCGR3_CG8(0) |
		     CCM_CCGR3_CG7(0) | CCM_CCGR3_CG6(0) |
		     CCM_CCGR3_CG5(0) | CCM_CCGR3_CG4(3) |
		     CCM_CCGR3_CG3(0) | CCM_CCGR3_CG2(3) |
		     CCM_CCGR3_CG1(0) | CCM_CCGR3_CG0(0);


	CCM->CCGR4 = CCM_CCGR4_CG15(0) | CCM_CCGR4_CG14(0) |
		     CCM_CCGR4_CG13(0) | CCM_CCGR4_CG12(0) |
		     CCM_CCGR4_CG11(0) | CCM_CCGR4_CG10(0) |
		     CCM_CCGR4_CG9(0) | CCM_CCGR4_CG8(0) |
		     CCM_CCGR4_CG7(3) | CCM_CCGR4_CG6(3) |
		     CCM_CCGR4_CG5(3) | CCM_CCGR4_CG4(3) |
		     CCM_CCGR4_CG3(0) | CCM_CCGR4_CG2(3) |
		     CCM_CCGR4_CG1(3) | CCM_CCGR4_CG0(0);

	CCM->CCGR5 = CCM_CCGR5_CG15(3) | CCM_CCGR5_CG14(3) |
		     CCM_CCGR5_CG13(0) | CCM_CCGR5_CG12(0) |
		     CCM_CCGR5_CG11(0) | CCM_CCGR5_CG10(0) |
		     CCM_CCGR5_CG9(0) | CCM_CCGR5_CG8(3) |
		     CCM_CCGR5_CG7(0) | CCM_CCGR5_CG6(3) |
		     CCM_CCGR5_CG5(0) | CCM_CCGR5_CG4(3) |
		     CCM_CCGR5_CG3(0) | CCM_CCGR5_CG2(0) |
		     CCM_CCGR5_CG1(3) | CCM_CCGR5_CG0(3);

	CCM->CCGR6 = CCM_CCGR6_CG15(0) | CCM_CCGR6_CG14(0) |
		     CCM_CCGR6_CG13(0) | CCM_CCGR6_CG12(0) |
		     CCM_CCGR6_CG11(3) | CCM_CCGR6_CG10(3) |
		     CCM_CCGR6_CG9(3) | CCM_CCGR6_CG8(0) |
		     CCM_CCGR6_CG7(0) | CCM_CCGR6_CG6(0) |
		     CCM_CCGR6_CG5(3) | CCM_CCGR6_CG4(3) |
		     CCM_CCGR6_CG3(0) | CCM_CCGR6_CG2(0) |
		     CCM_CCGR6_CG1(0) | CCM_CCGR6_CG0(0);
}

/**
 * @brief Setup various clock on SoC.
 *
 * Setup the SoC clocks according to the datasheet.
 *
 * Assumption:
 * SLCK = 32.768kHz
 */

static ALWAYS_INLINE void clkInit(void)
{
  u32_t tmp;

#ifdef CONFIG_SOC_ATMEL_SAM4S_EXT_SLCK
	/* This part is to switch the slow clock to using
	 * the external 32 kHz crystal oscillator.
	 * SUPC is in section 18.5.3 page 340 for the Control Register.
	 */

	/* Select external crystal */
	__SUPC->cr = SUPC_CR_KEY | SUPC_CR_XTALSEL;

	/* Wait for oscillator to be stablized */
	while (!(__SUPC->sr & SUPC_SR_OSCSEL))
		;
#endif /* CONFIG_SOC_ATMEL_SAM4S_EXT_SLCK */

#ifdef CONFIG_SOC_ATMEL_SAM4S_EXT_MAINCK
	/* Start the external main oscillator */
	__PMC->ckgr_mor = PMC_CKGR_MOR_KEY | PMC_CKGR_MOR_MOSCRCF_4MHZ
			  | PMC_CKGR_MOR_MOSCRCEN | PMC_CKGR_MOR_MOSCXTEN
			  | PMC_CKGR_MOR_MOSCXTST;

	/* Wait for main oscillator to be stablized */
	while (!(__PMC->sr & PMC_INT_MOSCXTS))
		;

	/* Select main oscillator as source since it is more accurate
	 * according to datasheet.
	 */
	__PMC->ckgr_mor = PMC_CKGR_MOR_KEY | PMC_CKGR_MOR_MOSCRCF_4MHZ
			  | PMC_CKGR_MOR_MOSCRCEN | PMC_CKGR_MOR_MOSCXTEN
			  | PMC_CKGR_MOR_MOSCXTST | PMC_CKGR_MOR_MOSCSEL;

	/* Wait for main oscillator to be selected */
	while (!(__PMC->sr & PMC_INT_MOSCSELS))
		;
#ifdef CONFIG_SOC_ATMEL_SAM4S_WAIT_MODE
	/*
	 * Instruct CPU enter Wait mode instead of Sleep mode to
	 * keep Processor Clock (HCLK) and thus be able to debug
	 * CPU using JTAG
	 */
	__PMC->fsmr |= PMC_FSMR_LPM;
#endif
#else
	/* Set main fast RC oscillator to 12 MHz */
	__PMC->ckgr_mor = PMC_CKGR_MOR_KEY | PMC_CKGR_MOR_MOSCRCF_12MHZ
			  | PMC_CKGR_MOR_MOSCRCEN;

	/* Wait for main fast RC oscillator to be stablized */
	while (!(__PMC->sr & PMC_INT_MOSCRCS))
		;
#endif /* CONFIG_SOC_ATMEL_SAM4S_EXT_MAINCK */

	/* Use PLLA as master clock.
	 * According to datasheet, PMC_MCKR must not be programmed in
	 * a single write operation. So it seems the safe way is to
	 * get the system to use main clock (by setting CSS). Then set
	 * the prescaler (PRES). Finally setting it back to using PLL.
	 */

	/* Switch to main clock first so we can setup PLL */
	tmp = __PMC->mckr & ~PMC_MCKR_CSS_MASK;
	__PMC->mckr = tmp | PMC_MCKR_CSS_MAIN;

	/* Wait for clock selection complete */
	while (!(__PMC->sr & PMC_INT_MCKRDY))
		;

	/* Setup PLLA */
	__PMC->ckgr_pllar = PMC_CKGR_PLLAR_DIVA | PMC_CKGR_PLLAR_ONE
			    | PMC_CKGR_PLLAR_MULA
			    | PMC_CKGR_PLLAR_PLLACOUNT;

	/* Wait for PLL lock */
	while (!(__PMC->sr & PMC_INT_LOCKA))
		;

	/* Setup PLLB */
	__PMC->ckgr_pllbr = PMC_CKGR_PLLBR_DIVB
			    | PMC_CKGR_PLLBR_MULB
			    | PMC_CKGR_PLLBR_PLLBCOUNT;

	/* Wait for PLL lock */
	while (!(__PMC->sr & PMC_INT_LOCKB))
		;

	/* Setup prescaler */
	tmp = __PMC->mckr & ~PMC_MCKR_PRES_MASK;
	__PMC->mckr = tmp | PMC_MCKR_PRES_CLK;

	/* Wait for main clock setup complete */
	while (!(__PMC->sr & PMC_INT_MCKRDY))
		;

	/* Finally select PLL as clock source */
	tmp = __PMC->mckr & ~PMC_MCKR_CSS_MASK;
	__PMC->mckr = tmp | PMC_MCKR_CSS_PLLA;

	/* Wait for main clock setup complete */
	while (!(__PMC->sr & PMC_INT_MCKRDY))
		;

}
/**
 *
 * @brief Perform basic hardware initialization
 * This needs to be run from the very beginning.
 * So the init priority has to be 0 (zero).
 *
 * Initialize the interrupt controller device drivers.
 * Also initialize the timer device driver, if required.
 *
 * @return 0
 */

static int sm_init(struct device *arg)
{
  u32_t key;

	ARG_UNUSED(arg);

	/* Note:
	 * Magic numbers below are obtained by reading the registers
	 * when the SoC was running the SAM4S-BA bootloader
	 * (with reserved bits set to 0).
	 */

	key = irq_lock();

	/* Setup the flash controller.
	 * The bootloader is running @ 48 MHz with
	 * FWS == 2.
	 * When running at 84 MHz, FWS == 4 seems
	 * to be more stable, and allows the board
	 * to boot.
	 */
	__EEFC0->fmr = (4 << EEFC_FMR_FWS_POS);
	__EEFC1->fmr = (4 << EEFC_FMR_FWS_POS);

	_ClearFaults();

	/* Setup master clock */
	clock_init();

	/* Disable watchdog timer, not used by system */
	__WDT->mr |= WDT_DISABLE;

	/* Install default handler that simply resets the CPU
	 * if configured in the kernel, NOP otherwise
	 */
	NMI_INIT();

	irq_unlock(key);

	return 0;
}

SYS_INIT(sm_init, PRE_KERNEL_1, 0);
