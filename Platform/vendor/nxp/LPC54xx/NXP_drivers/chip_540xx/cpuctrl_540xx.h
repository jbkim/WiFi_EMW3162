/*
 * @brief LPC540XX CPU multi-core support driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __CPUCTRL_540XX_H_
#define __CPUCTRL_540XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup CPUCTRL_540XX CHIP: LPC540XX CPU multi-core support driver
 * @ingroup CHIP_540XX_Drivers
 * This driver helps with determine which MCU core the software is running,
 * whether the MCU core is in master or slave mode, and provides functions
 * for master and slave core control.
 * @{
 */

/* CPU control and status definitions for M0 and M4 cores */
#define MC_M4_BOOT              (1 << 0)	/*!< Determines which CPU is considered the master, 0 = CM0+, 1 = CM4 */
#define MC_CM4_CLK_ENABLE       (1 << 2)	/*!< Cortex-M4 clock enable */
#define MC_CM0_CLK_ENABLE       (1 << 3)	/*!< Cortex-M0+ clock enable */
#define MC_CM4_RESET_ENABLE     (1 << 4)	/*!< Cortex-M4 reset */
#define MC_CM0_RESET_ENABLE     (1 << 5)	/*!< Cortex-M0+ reset */
#define MC_CM4_SLEEPCON_OWNER   (1 << 6)	/*!< Identifies the owner of reduced power mode control, 0 = CM0+, 1 = CM4 */

/* CPU STAT regsiter */	// FIXME - these definitions are not in the UM!
#define MC_M4_SLEEPING          (1 << 0)
#define MC_M0_SLEEPING          (1 << 1)
#define MC_M4_LOCKUP            (1 << 2)
#define MC_M0_LOCKUP            (1 << 3)

/**
 * @brief	Determinc which MCU this code is running on
 * @return  true if executing on the CM4, or false if executing on the CM0+
 */
STATIC INLINE bool Chip_CPU_IsM4Core(void) {
	/* M4 core is designated by values 0xC24 on bits 15..4 */
	if (((SCB->CPUID >> 4) & 0xFFF) == 0xC24) {
		return true;
	}

	return false;
}

/**
 * @brief	Determine if this core is a slave or master
 * @return  true if this MCU is operating as the master, or false if operating as a slave
 */
STATIC INLINE bool Chip_CPU_IsMasterCore(void) {
	/* M4 core is designated by values 0xC24 on bits 15..4 */
	if ((LPC_SYSCTL->CPUCTRL & MC_M4_BOOT) != 0) {
		return true;
	}

	return false;
}

/**
 * @brief	Setup M0+ boot and reset M0+ core
 * @param	coentry		: Pointer to boot entry point for M0+ core
 * @param	costackptr	: Pointer to where stack should be located for M0+ core
 * @return  Nothing
 * @note	Will setup boot stack and entry point, enable M0+ clock and then
 * reset M0+ core.
 */
void Chip_CPU_CM0Boot(uint32_t *coentry, uint32_t *costackptr);

/**
 * @brief	Setup M4 boot and reset M4 core
 * @param	coentry		: Pointer to boot entry point for M4 core
 * @param	costackptr	: Pointer to where stack should be located for M4 core
 * @return  Nothing
 * @note	Will setup boot stack and entry point, enable M4 clock and then
 * reset M0+ core.
 */
void Chip_CPU_CM4Boot(uint32_t *coentry, uint32_t *costackptr);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __CPUCTRL_540XX_H_ */
