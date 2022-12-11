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
 *  file:     mcu_builtin.h (IMXRT)
 *  brief:    Built-in IMXRT MCU definitions
 *  version:  1.00
 *  date:     2018-11-23
 *  authors:  nvitya
*/

#ifndef __MCU_BUILTIN_H
#define __MCU_BUILTIN_H

//----------------------------------------------------------------------
// IMXRT
//----------------------------------------------------------------------

#if defined(MCU_IMXRT1020) || defined(MCU_IMXRT1021)

  #define MCUF_IMXRT
  #define MCUSF_1020

  #include "MIMXRT1021.h"

#else

  #error "Unknown MCU"

#endif

#endif
