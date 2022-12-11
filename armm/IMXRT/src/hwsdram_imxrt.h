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
 *  file:     hwsdram_imxrt.h
 *  brief:    IMXRT SDRAM controller
 *  created:  2018-11-24
 *  authors:  nvitya
*/

#ifndef HWSDRAM_IMXRT_H_
#define HWSDRAM_IMXRT_H_

#define HWSDRAM_PRE_ONLY
#include "hwsdram.h"

#define HWSDRAM_ADDRESS  0x80000000 // by IMXRT it is actually selectable

#define HW_SDRAM_REGS    SEMC_Type

class THwSdram_imxrt : public THwSdram_pre
{
public:
	HW_SDRAM_REGS *  regs = nullptr;

	bool InitHw();

	void Cmd_ClockEnable();
	void Cmd_AllBankPrecharge();
	void Cmd_AutoRefresh(int acount);
	void Cmd_LoadModeRegister(uint16_t aregvalue);
	void Cmd_LoadExtModeRegister(uint16_t aregvalue);
	void SetNormalMode();
	void SetRefreshTime(uint32_t atime_ns);

public:
	void SendIpCommand(uint32_t address, uint16_t command, uint32_t data);
};

#define HWSDRAM_IMPL THwSdram_imxrt

#endif /* HWSDRAM_IMXRT_H_ */
