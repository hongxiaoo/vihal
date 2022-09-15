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
 *  file:     hwusbctrl.h
 *  brief:    USB Controller (device only) vendor-independent definitions
 *  version:  1.00
 *  date:     2018-05-18
 *  authors:  nvitya
*/

#ifndef HWUSBCTRL_H_PRE_
#define HWUSBCTRL_H_PRE_

#include "hwpins.h"

#define HWUSB_EP_TYPE_CONTROL      0x0001
#define HWUSB_EP_TYPE_INTERRUPT    0x0002
#define HWUSB_EP_TYPE_BULK         0x0003
#define HWUSB_EP_TYPE_ISO          0x0004
#define HWUSB_EP_TYPE_MASK         0x0007

// Error codes
#define USBERR_INVALID_EP            -1
#define USBERR_INVALID_BUFFER_SIZE   -2  // must be dividible by 2
#define USBERR_BUFFER_TOO_SMALL      -3
#define USBERR_TX_OVERWRITE          -4  // there were remaining data in the tx buffer

class THwUsbCtrl; // forward declaration
class THwUsbEndpoint;

class THwUsbEndpoint_pre
{
public:
	THwUsbCtrl *    usbctrl = nullptr;

	uint8_t         index = 0xFF;  // will be set later

	bool            dir_htod = false;
	bool            iscontrol = false;
	uint8_t         send_zero_state = 0; // if a data with maxlength is sent then automatically send a zero packet

	uint16_t        maxlen = 0;

	uint32_t        attr = 0;

	virtual         ~THwUsbEndpoint_pre() { }

	void            CheckZeroPacketSending(unsigned asendlen, bool alastsegment = true);
};

class THwUsbCtrl_pre
{
public:  // parameters
	int             devnum = 0;  // on stm32 0 = OTG_HS, 1 = OTG_FS
	bool            highspeed = false;

public:
	bool            initialized = false;

	virtual ~THwUsbCtrl_pre() { }
	virtual void HandleReset() { }
  virtual THwUsbEndpoint_pre *  GetEndPoint(uint8_t epid) { return nullptr; }
	virtual void SetPullUp(bool aenable) { }
	virtual bool HandleEpTransferEvent(uint8_t epid, bool htod) { return false; }

public:
	bool            double_ctrl_ack = false;  // some ATSAM devices require to send the ACK twice (for DATA1)
};

#endif // ndef HWUSBCTRL_H_PRE_

#ifndef HWUSBCTRL_PRE_ONLY

//-----------------------------------------------------------------------------

#ifndef HWUSBCTRL_H_
#define HWUSBCTRL_H_

#include "mcu_impl.h"

#if !defined(HWUSBCTRL_IMPL) || !defined(HWUSBENDPOINT_IMPL)

#define HWUSB_MAX_ENDPOINTS 8

class THwUsbEndpoint_noimpl : public THwUsbEndpoint_pre
{
public: // mandatory functions
	bool ConfigureHwEp()  { return false; }  // based on previously set fields

	int  ReadRecvData(void * buf, uint32_t buflen) { return 0; }
	int  StartSendData(void * buf, unsigned len, bool lastsegment = true)   { return 0; }
	void SendAck()  { }

  void FinishRecv(bool reenable) { }
  void EnableRecv()     { }
  void DisableRecv()    { }
  void StopSend()       { }
  void FinishSend()     { }
  void Stall()          { }
  void Nak()            { }

  void SetData0()       { }
  bool IsSetupRequest() { return false; }
};

class THwUsbCtrl_noimpl : public THwUsbCtrl_pre
{
public: // mandatory functions
	bool InitHw() { return false; }
	void HandleIrq() { }

	void SetDeviceAddress(uint8_t aaddr) { }

	void EnableIrq() { }
	void ResetEndpoints() { }
};

#define HWUSBENDPOINT_IMPL   THwUsbEndpoint_noimpl
#define HWUSBCTRL_IMPL   THwUsbCtrl_noimpl

#endif // ndef HWUSBCTRL_IMPL

//-----------------------------------------------------------------------------

class THwUsbEndpoint : public HWUSBENDPOINT_IMPL
{
public:
  void    Reset();
};

class THwUsbCtrl : public HWUSBCTRL_IMPL
{
public:
	virtual void HandleReset();

};

#endif // ndef HWUSBCTRL_H_ */

#else
  #undef HWUSBCTRL_PRE_ONLY
#endif
