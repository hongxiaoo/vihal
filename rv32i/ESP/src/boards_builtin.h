/*
 *  file:     boards_builtin.h (ESP)
 *  brief:    Built-in Risc-V Espressiv board definitions
 *  version:  1.00
 *  date:     2022-02-03
 *  authors:  nvitya
*/

#ifndef _BOARDS_BUILTIN_H_
#define _BOARDS_BUILTIN_H_

#if 0 // to use elif everywhere

//-------------------------------------------------------------------------------------------------
// ESP32
//-------------------------------------------------------------------------------------------------

#elif defined(BOARD_ESP32C3_DEVKIT) || defined(BOARD_NANO_ESP32C3)

  #define BOARD_NAME "ESP32C3 Development Kit"
  #define MCU_ESP32C3
  #define EXTERNAL_XTAL_HZ   40000000

#elif defined(BOARD_NODEMCU_ESP32C3)

  #define BOARD_NAME "NodeMCU ESP32C3 Development Kit"
  #define MCU_ESP32C3
  #define EXTERNAL_XTAL_HZ   40000000

#else

  #error "Unknown board."

#endif

#endif
