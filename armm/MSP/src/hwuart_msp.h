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
 *  file:     hwuart_atsam_v2.h
 *  brief:    ATSAM_V2 UART
 *  version:  1.00
 *  date:     2018-02-10
 *  authors:  nvitya
*/

#ifndef HWUART_ATSAM_V2_H_
#define HWUART_ATSAM_V2_H_

#define HWUART_PRE_ONLY
#include "hwuart.h"

class THwUart_atsam_v2 : public THwUart_pre
{
public:
	bool Init(int adevnum);

	bool TrySendChar(char ach);
	bool TryRecvChar(char * ach);

	inline bool SendFinished()   { return regs->INTFLAG.bit.TXC; }

	void DmaAssign(bool istx, THwDmaChannel * admach);

	bool DmaStartSend(THwDmaTransfer * axfer);
	bool DmaStartRecv(THwDmaTransfer * axfer);

public:
	HW_UART_REGS *      regs = nullptr;
};

#define HWUART_IMPL THwUart_atsam_v2

#endif // def HWUART_ATSAM_V2_H_
