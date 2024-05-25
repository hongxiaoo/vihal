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
 *  file:     hwdma_sg.h
 *  brief:    SG200x/CV1800 (Sophgo) DMA
 *  created:  2024-05-25
 *  authors:  nvitya
*/

#ifndef HWDMA_SG_H_
#define HWDMA_SG_H_

#include "platform.h"

#define HWDMA_PRE_ONLY
#include "hwdma.h"


class THwDmaChannel_sg : public THwDmaChannel_pre
{
public:
	unsigned          perid = 0;
	dma_chregs_t *    regs = nullptr;
	dma_regs_t *      dmaregs = nullptr;
	uint32_t          chbit = 0;


	bool Init(int achnum, int aperid);

	void Prepare(bool aistx, void * aperiphaddr, unsigned aflags);
	void Disable();
	void Enable();

	inline bool Enabled()        { return false; } //return ((regs->CTL & 1) != 0); }

  inline bool Active()         { return false; } //((regs->CTL & 1) && (regs->CNT)); }  // combined termination check

	inline uint16_t Remaining()  { return 0; } //regs->CNT; }

	bool StartTransfer(THwDmaTransfer * axfer);
	bool StartMemToMem(THwDmaTransfer * axfer);

	void PrepareTransfer(THwDmaTransfer * axfer);
	inline void StartPreparedTransfer() { Enable(); }

	inline void ClearIrqFlag()
	{
			//dmaregs->INTC = (0x0F << irqstshift);
	}

public:

  volatile uint32_t *  reg_int_cpu_mux = nullptr;
  volatile uint32_t *  reg_dma_ch_mux = nullptr;

};

#define HWDMACHANNEL_IMPL  THwDmaChannel_sg

#endif // def HWDMA_SG_H_
