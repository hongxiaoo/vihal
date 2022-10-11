/* -----------------------------------------------------------------------------
 * This file is a part of the NVCM project: https://github.com/nvitya/nvcm
 * Copyright (c) 2018 Viktor Nagy, nvitya
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software. Permission is granted to anyone to use this
 * software for any purpose, including commercial applications, and to alter
 * it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 * --------------------------------------------------------------------------- */
/*
 *  file:     mcu_defs.h (LPC_V3)
 *  brief:    LPC_V3 MCU Family definitions
 *  version:  1.00
 *  date:     2018-02-10
 *  authors:  nvitya
*/

#ifndef __MCU_DEFS_H
#define __MCU_DEFS_H

#if defined(MCUSF_546XX) || defined(MCUSF_540XX)

  #define MAX_CLOCK_SPEED  180000000

#endif


#if defined(MCUSF_540XX)

  #define IRQVECTAB_OFFS_24_VALUE  0xEDDC94BD
  #define IRQVECTAB_OFFS_28_VALUE  0x180  // fix boot block offset

#endif

#define MCU_INTERNAL_RC_SPEED  12000000

#define HW_GPIO_REGS  GPIO_Type
#define HW_UART_REGS  USART_Type
#define HW_SPI_REGS   SPI_Type

#define HW_DMA_MAX_COUNT  1024  // quite low on this CPU

inline void __attribute__((always_inline)) mcu_preinit_code()
{
  // enable the SRAM0-2 blocks (they are disabled after reset...)
  // addr 0x20000000 - 0x20028000 = 160k
  SYSCON->AHBCLKCTRLSET[0] = (7 << 3);
  // enable the USB1 RAM at	0x40100000 - 0x40102000 = 8k
  SYSCON->AHBCLKCTRLSET[2] = (1 << 6);
}

#endif // __MCU_DEFS_H
