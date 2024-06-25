/* This file is a part of the VIHAL project: https://github.com/nvitya/vihal
 * Copyright (c) 2023 Viktor Nagy, nvitya
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
 *  file:     hwclkctrl_am.cpp
 *  brief:    AM MCU Clock / speed setup
 *  created:  2024-06-15
 *  authors:  nvitya
*/

#include "platform.h"
#include "hwclk.h"
//#include "am_utils.h"

inline bool hwclk_ext_osc_ready()
{
  return true;
	//return (0 != (SYSCTL->SOCLOCK.CLKSTATUS & SYSCTL_CLKSTATUS_HFCLKGOOD_MASK));
}

void hwclk_start_ext_osc(unsigned aextspeed)
{
}

bool hwclk_start_inths_osc(unsigned aextspeed)
{
	return true;
}

void hwclk_prepare_hispeed(unsigned acpuspeed)
{
}

bool hwclk_init(unsigned external_clock_hz, unsigned target_speed_hz)
{
  SystemCoreClock = MCU_INTERNAL_RC_SPEED;
  return true;
}

