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
 *  file:     hwqspi_lpc.h
 *  brief:    LPC V3 QSPI
 *  version:  1.00
 *  date:     2018-06-28
 *  authors:  nvitya
*/

#ifndef HWQSPI_LPC_V3_H_
#define HWQSPI_LPC_V3_H_

#include "platform.h"

#ifdef SPIFI0

#define HWQSPI_PRE_ONLY
#include "hwqspi.h"

#define HW_QSPI_REGS  SPIFI_Type

class THwQspi_lpc_v3 : public THwQspi_pre
{
public:
	unsigned char  dmachannel = 7;
	HW_QSPI_REGS * regs = nullptr;

	bool Init();

	virtual bool InitInterface(); // override

	int  StartReadData(unsigned acmd, unsigned address, void * dstptr, unsigned len);
	int  StartWriteData(unsigned acmd, unsigned address, void * srcptr, unsigned len);
	void Run();

	unsigned       ctrlbase = 0;
};

#define HWQSPI_IMPL THwQspi_lpc_v3

#endif

#endif // def HWQSPI_LPC_V3_H_
