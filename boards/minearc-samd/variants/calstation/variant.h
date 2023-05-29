/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_CALSTATION_
#define _VARIANT_CALSTATION_

// The definitions here needs a SAMD core >=1.6.10
#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10610

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC (32768ul)

/** Master clock frequency */
#define VARIANT_MCK (F_CPU)

#define VARIANT_GCLK0_FREQ (F_CPU)
#define VARIANT_GCLK1_FREQ (48000000UL)
#define VARIANT_GCLK2_FREQ (100000000UL)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "WVariant.h"

#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Number of pins defined in PinDescription array
#define PINS_COUNT (35ul)
#define NUM_DIGITAL_PINS (35ul)
#define NUM_ANALOG_INPUTS (0ul)
#define NUM_ANALOG_OUTPUTS (0ul)
#define analogInputToDigitalPin(p) ((p < NUM_ANALOG_INPUTS) ? (p) + PIN_A0 : -1)

#define digitalPinToPort(P) (&(PORT->Group[g_APinDescription[P].ulPort]))
#define digitalPinToBitMask(P) (1 << g_APinDescription[P].ulPin)
// #define analogInPinToBit(P) ()
#define portOutputRegister(port) (&(port->OUT.reg))
#define portInputRegister(port) (&(port->IN.reg))
#define portModeRegister(port) (&(port->DIR.reg))
#define digitalPinHasPWM(P) (g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER)

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)

/*
 * Analog pins
 */
#define PIN_A0 (255ul)
#define PIN_A1 (255ul)
#define PIN_DAC0 (255ul)
#define PIN_DAC1 (255ul)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t DAC0 = PIN_DAC0;
static const uint8_t DAC1 = PIN_DAC1;

#define ADC_RESOLUTION 12

/*
 * Serial interfaces
 */

// Serial
#define PIN_SERIAL_TX (35ul)
#define PIN_SERIAL_RX (36ul)
#define PAD_SERIAL_TX (UART_TX_PAD_0)
#define PAD_SERIAL_RX (SERCOM_RX_PAD_1)

static const uint8_t TX = PIN_SERIAL_TX;
static const uint8_t RX = PIN_SERIAL_RX;

// Serial1
#define PIN_SERIAL1_TX (37ul)
#define PIN_SERIAL1_RX (38ul)
#define PAD_SERIAL1_TX (UART_TX_PAD_0)
#define PAD_SERIAL1_RX (SERCOM_RX_PAD_1)

static const uint8_t TX1 = PIN_SERIAL1_TX;
static const uint8_t RX1 = PIN_SERIAL1_RX;

// Serial2
#define PIN_SERIAL2_TX (40ul)
#define PIN_SERIAL2_RX (39ul)
#define PAD_SERIAL2_TX (UART_TX_PAD_0)
#define PAD_SERIAL2_RX (SERCOM_RX_PAD_1)

static const uint8_t TX2 = PIN_SERIAL2_TX;
static const uint8_t RX2 = PIN_SERIAL2_RX;

// Serial3
#define PIN_SERIAL3_TX (41ul)
#define PIN_SERIAL3_RX (42ul)
#define PAD_SERIAL3_TX (UART_TX_PAD_0)
#define PAD_SERIAL3_RX (SERCOM_RX_PAD_1)

static const uint8_t TX3 = PIN_SERIAL3_TX;
static const uint8_t RX3 = PIN_SERIAL3_RX;

// Serial4
#define PIN_SERIAL4_TX (43ul)
#define PIN_SERIAL4_RX (44ul)
#define PAD_SERIAL4_TX (UART_TX_PAD_0)
#define PAD_SERIAL4_RX (SERCOM_RX_PAD_1)

static const uint8_t TX4 = PIN_SERIAL4_TX;
static const uint8_t RX4 = PIN_SERIAL4_RX;

// Serial5
#define PIN_SERIAL5_TX (45ul)
#define PIN_SERIAL5_RX (46ul)
#define PAD_SERIAL5_TX (UART_TX_PAD_0)
#define PAD_SERIAL5_RX (SERCOM_RX_PAD_1)

static const uint8_t TX5 = PIN_SERIAL5_TX;
static const uint8_t RX5 = PIN_SERIAL5_RX;

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 0

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 0

/*
 * USB
 */
// #define PIN_USB_HOST_ENABLE (-1ul)
#define PIN_USB_DM (255ul)
#define PIN_USB_DP (255ul)

/*
 * I2S Interfaces
 */
// #define I2S_INTERFACES_COUNT 1

// #define I2S_DEVICE 0
// #define I2S_CLOCK_GENERATOR 3

// #define PIN_I2S_SDO (-1u)
// #define PIN_I2S_SDI (-1u)
// #define PIN_I2S_SCK (-1u)
// #define PIN_I2S_FS (-1u)
// #define PIN_I2S_MCK (-1u)

// QSPI Pins
// #define PIN_QSPI_SCK (-1u)
// #define PIN_QSPI_CS (-1u)
// #define PIN_QSPI_IO0 (-1u)
// #define PIN_QSPI_IO1 (-1u)
// #define PIN_QSPI_IO2 (-1u)
// #define PIN_QSPI_IO3 (-1u)

// PCC Pins
// #define PIN_PCC_DEN1 (PIN_SPI_MOSI)
// #define PIN_PCC_DEN2 (PIN_SPI_SCK)
// #define PIN_PCC_CLK (PIN_SPI_MISO)
// #define PIN_PCC_D0 (-1u)
// #define PIN_PCC_D1 (-1u)
// #define PIN_PCC_D2 (-1u)
// #define PIN_PCC_D3 (-1u)
// #define PIN_PCC_D4 (-1u)
// #define PIN_PCC_D5 (-1u)
// #define PIN_PCC_D6 (-1u)
// #define PIN_PCC_D7 (-1u)
// #define PIN_PCC_D8 (-1u)
// #define PIN_PCC_D9 (-1u)

// TODO: meaningful value for this
// #define VARIANT_QSPI_BAUD_DEFAULT 5000000

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

/*	=========================
 *	===== SERCOM DEFINITION
 *	=========================
 */
extern SERCOM sercom0;
extern SERCOM sercom1;
extern SERCOM sercom2;
extern SERCOM sercom3;
extern SERCOM sercom4;
extern SERCOM sercom5;

extern Uart Serial;
extern Uart Serial1;
extern Uart Serial2;
extern Uart Serial3;
extern Uart Serial4;
extern Uart Serial5;

#endif

// These serial port names are intended to allow libraries and
// architecture-neutral sketches to automatically default to the correct port
// name for a particular type of use.  For example, a GPS module would normally
// connect to SERIAL_PORT_HARDWARE_OPEN, the first hardware serial port whose
// RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial
// Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge
// library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.
// Their RX & TX
//                            pins are NOT connected to anything by default.

#define SERIAL_PORT_USBVIRTUAL Serial3
#define SERIAL_PORT_MONITOR Serial3
#define SERIAL_PORT_HARDWARE Serial
#define SERIAL_PORT_USBVIRTUAL SerialUSB
#define SERIAL_PORT_MONITOR SerialUSB
#define SERIAL_PORT_HARDWARE Serial
#endif // _VARIANT_CALSTATION_