/* -----------------------------------------------------------------------------
 * This file is a part of the VIHAL project: https://github.com/nvitya/vihal
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
 *  file:     hwi2c.h
 *  brief:    Internal I2C / TWI vendor-independent definitions
 *  version:  1.00
 *  date:     2018-02-10
 *  authors:  nvitya
*/

#ifndef _HWI2C_H_PRE_
#define _HWI2C_H_PRE_

#include "platform.h"
#include "hwpins.h"
#include "hwdma.h"
#include "hwerrors.h"

#define ERR_I2C_BASE      0x10000
#define ERR_I2C_ACK       (ERR_I2C_BASE + 1)
#define ERR_I2C_ARBLOST   (ERR_I2C_BASE + 2)
#define ERR_I2C_BUS       (ERR_I2C_BASE + 3)
#define ERR_I2C_OVERRUN   (ERR_I2C_BASE + 4)
#define ERR_I2C_UNDERRUN  ERR_I2C_OVERRUN
#define ERR_I2C_OVRUDR    ERR_I2C_OVERRUN

#define I2CEX_0           0x00000000  // do not send extra data
#define I2CEX_1           0x01000000  // send 1 extra byte
#define I2CEX_2           0x02000000  // send 2 extra bytes
#define I2CEX_3           0x03000000  // send 3 extra bytes
#define I2CEX_MASK        0x03000000

struct TI2cTransaction
{
  bool               completed;
  uint8_t            iswrite;  // 0 = read, 1 = write
  uint8_t            address;
  int                error;

  uint32_t           extra;
  uint8_t *          dataptr;
  unsigned           datalen;

  PCbClassCallback   callback = nullptr;
  void *             callbackobj = nullptr;
  void *             callbackarg = nullptr;

  TI2cTransaction *  next;
};

class THwI2c_pre
{
public:	// settings
	bool 					   initialized = false;

	int      			   devnum = -1;
	unsigned         speed = 100000;  // default speed = 100 kHz

public: // DMA
  THwDmaChannel *  txdma = nullptr;
  THwDmaChannel *  rxdma = nullptr;

	THwDmaTransfer   xfer;

public: // run state
	bool             istx = false;
	bool             dmaused = false;
	uint8_t *        dataptr = nullptr;
	unsigned         datalen = 0;
	unsigned         remainingbytes = 0;

  int              trastate = 0; // transaction state

  TI2cTransaction *  curtra = nullptr;

  void             StartWrite(TI2cTransaction * atra, uint8_t aaddr, uint32_t aextra, void * dataptr, unsigned len);
  void             StartRead(TI2cTransaction * atra, uint8_t aaddr, uint32_t aextra, void * dataptr, unsigned len);

  bool             AddTransaction(TI2cTransaction * atra);  // returns false if already added

};

#endif // ndef HWI2C_H_PRE_

#ifndef HWI2C_PRE_ONLY

//-----------------------------------------------------------------------------

#ifndef HWI2C_H_
#define HWI2C_H_

#include "mcu_impl.h"

#ifndef HWI2C_IMPL

#warning "HWI2C is not implemented!"

class THwI2c_noimpl : public THwI2c_pre
{
public: // mandatory
	bool Init(int adevnum)      { return false; }

  void DmaAssign(bool istx, THwDmaChannel * admach)  { }

	void RunTransaction()  { }
};

#define HWI2C_IMPL   THwI2c_noimpl

#endif // ndef HWI2C_IMPL

//-----------------------------------------------------------------------------

class THwI2c : public HWI2C_IMPL
{
public:
  void WaitFinish(TI2cTransaction * atra);
  void Run();
};

#endif // HWI2C_H_

#else
  #undef HWI2C_PRE_ONLY
#endif
