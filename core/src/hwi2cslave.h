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
 *  file:     hwi2cslave.h
 *  brief:    Internal I2C / TWI Slave vendor-independent definitions
 *  version:  1.00
 *  date:     2019-10-13
 *  authors:  nvitya
 *  notes:
 *    no DMA support so far
*/

#ifndef _HWI2CSLAVE_H_PRE_
#define _HWI2CSLAVE_H_PRE_

#include "platform.h"
#include "hwpins.h"
#include "hwdma.h"
#include "hwerrors.h"

class THwI2cSlave_pre
{
public:	// settings
	bool 					   initialized = false;
	int8_t   			   devnum = -1;
	uint8_t          address     = 0x7F;
	uint8_t          addressmask = 0x00;   // 1 bits = ignore

public: // run state
	bool             istx = false;

public:
	virtual          ~THwI2cSlave_pre() { };  // to avoid compiler warning

public:
	virtual void     OnAddressRw(uint8_t aaddress)    { }; // must be overridden, warning: IRQ context !
	virtual uint8_t  OnTransmitRequest()              { return 0; }; // must be overridden, warning: IRQ context !
	virtual void     OnByteReceived(uint8_t adata)    { }; // must be overridden, warning: IRQ context !
};

#endif // ndef HWI2CSLAVE_H_PRE_

#ifndef HWI2CSLAVE_PRE_ONLY

//-----------------------------------------------------------------------------

#ifndef HWI2CSLAVE_H_
#define HWI2CSLAVE_H_

#include "mcu_impl.h"

#ifndef HWI2CSLAVE_IMPL

//#warning "HWI2CSLAVE is not implemented!"

class THwI2cSlave_noimpl : public THwI2cSlave_pre
{
public: // mandatory
	bool InitHw(int adevnum)      { return false; }

	void HandleIrq()              { }
	void Run()                    { }
};

#define HWI2CSLAVE_IMPL   THwI2cSlave_noimpl

#endif // ndef HWI2CSLAVE_IMPL

//-----------------------------------------------------------------------------

class THwI2cSlave : public HWI2CSLAVE_IMPL
{
public:
	bool Finished();
	int WaitFinish();
};

#endif // HWI2CSLAVE_H_

#else
  #undef HWI2CSLAVE_PRE_ONLY
#endif
