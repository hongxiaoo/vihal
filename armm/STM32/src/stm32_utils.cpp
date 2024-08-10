/* This file is a part of the VIHAL project: https://github.com/nvitya/vihal
 * Copyright (c) 2021 Viktor Nagy, nvitya
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
 *  file:     stm32_utils.cpp
 *  brief:    STM32 Utilities
 *  version:  1.00
 *  date:     2019-11-24
 *  authors:  nvitya
*/

#include "stm32_utils.h"

#if defined(MCUSF_H7)

// high speed devices

uint32_t stm32_bus_speed(uint8_t abusid)
{
	uint32_t tmp;
	uint32_t clockshr;  // clock shift right = division

	// check AHB division
	tmp = (RCC->D1CFGR & RCC_D1CFGR_HPRE);
	if (tmp & 8)
	{
		clockshr = 1; // if AHB divided, then surely only with 2
	}
	else
	{
		clockshr = 0;
	}

  #if defined(MCUSF_H7_V2)
	if (abusid > STM32_BUSID_AHB)
	{
	  ++clockshr;
	}
  #endif

	return (SystemCoreClock >> clockshr);
}

#elif defined(MCUSF_H7RS)

uint32_t stm32_bus_speed(uint8_t abusid)
{
  uint32_t tmp;
  uint32_t clockshr;  // clock shift right = division

  // TODO: change for a more proper version

  // check AHB division
  if (SystemCoreClock > 300000000)
  {
    clockshr = 1; // if AHB divided, then surely only with 2
  }
  else
  {
    clockshr = 0; // if AHB divided, then surely only with 2
  }

  if (abusid > STM32_BUSID_AHB)
  {
    if (SystemCoreClock > 300000000)
    {
      clockshr = 2;
    }
    else if (SystemCoreClock > 150000000)
    {
      clockshr = 1;
    }
    else
    {
      clockshr = 0;
    }
  }

  return (SystemCoreClock >> clockshr);
}

#elif defined(MCUSF_G0)

// missing RCC_CFGR_HPRE_DIV2 etc. defines here ....

uint32_t stm32_bus_speed(uint8_t abusid)
{
  return SystemCoreClock; // no division is set up
}

#elif defined(MCUSF_WB)

// missing RCC_CFGR_HPRE_DIV2 etc. defines here ....

uint32_t stm32_bus_speed(uint8_t abusid)
{
  return SystemCoreClock; // no division is set up
}

#else

// classic

uint32_t stm32_bus_speed(uint8_t abusid)
{
	uint32_t tmp;
	uint32_t clockshr;  // clock shift right = division

	if (STM32_BUSID_AHB == abusid)
	{
		tmp = (RCC->CFGR & RCC_CFGR_HPRE);
		if      (RCC_CFGR_HPRE_DIV2 == tmp)  clockshr = 1;
		else if (RCC_CFGR_HPRE_DIV4 == tmp)  clockshr = 2;
		else                                 clockshr = 0;
	}
#ifdef RCC_CFGR_PPRE // smaller devices have only one peripheral bus
	else if ((STM32_BUSID_APB1 == abusid) || (STM32_BUSID_APB2 == abusid))
	{
		tmp = (RCC->CFGR & RCC_CFGR_PPRE);
		if      (RCC_CFGR_PPRE_DIV2 == tmp)  clockshr = 1;
		else if (RCC_CFGR_PPRE_DIV4 == tmp)  clockshr = 2;
		else                                 clockshr = 0;
	}
#else
	else if (STM32_BUSID_APB1 == abusid)
	{
		tmp = (RCC->CFGR & RCC_CFGR_PPRE1);
		if      (RCC_CFGR_PPRE1_DIV2 == tmp)  clockshr = 1;
		else if (RCC_CFGR_PPRE1_DIV4 == tmp)  clockshr = 2;
		else                                  clockshr = 0;
	}
	else if (STM32_BUSID_APB2 == abusid)
	{
		tmp = (RCC->CFGR & RCC_CFGR_PPRE2);
		if      (RCC_CFGR_PPRE2_DIV2 == tmp)  clockshr = 1;
		else if (RCC_CFGR_PPRE2_DIV4 == tmp)  clockshr = 2;
		else                                  clockshr = 0;
	}
#endif
	else
	{
		clockshr = 0; // unhandled, no division by default
	}

	return (SystemCoreClock >> clockshr);
}

#endif

void stm32_start_internal_hs_rc_osc()
{
#ifdef RCC_CR_HSIKERON
  RCC->CR |= (RCC_CR_HSION | RCC_CR_HSIKERON);
#else
  RCC->CR |= RCC_CR_HSION;
#endif
  while ((RCC->CR & RCC_CR_HSIRDY) == 0)
  {
    // wait until it is ready
  }
}


