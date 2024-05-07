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
 *  file:     hwspi_atsam.h
 *  brief:    ATSAM SPI (master only)
 *  version:  1.00
 *  date:     2018-02-10
 *  authors:  nvitya
*/

#ifndef HWSPI_ATSAM_H_
#define HWSPI_ATSAM_H_

#define HWSPI_PRE_ONLY
#include "hwspi.h"

#define HW_SPI_REGS       Spi

class THwSpi_atsam : public THwSpi_pre
{
public:
	bool Init(int adevnum);
  void SetSpeed(unsigned aspeed);

	bool TrySendData(uint8_t adata);
	bool TryRecvData(uint8_t * dstptr);
	bool SendFinished();

	void DmaAssign(bool istx, THwDmaChannel * admach);

	bool DmaStartSend(THwDmaTransfer * axfer);
	bool DmaStartRecv(THwDmaTransfer * axfer);
	bool DmaSendCompleted();
	bool DmaRecvCompleted();

#ifdef HW_HAS_PDMA
	void PdmaInit(bool istx, THwDmaChannel * admach);
#endif

public:
	unsigned  					basespeed;
	HW_SPI_REGS * 			regs;
#ifdef HW_UART_ALT_REGS
	HW_UART_ALT_REGS *	usartregs;  // on Atmel the USART units can be used too
#endif

  void SetCs(unsigned value);
};


#define HWSPI_IMPL THwSpi_atsam

#endif // def HWSPI_ATSAM_H_
