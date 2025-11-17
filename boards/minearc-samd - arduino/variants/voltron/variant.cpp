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
/*
 * +-----+------------+---------+--------------+----------------+-----------------+---------+--------+----------------+----------------+--------------+----------------+----------------+
 * + Pin | Legacy Pin | I/O Pin | Label/Name   | Interupt       | Ref             | ADC     | AC     | SERCOM         | SERCOM-ALT     | TC/TCC       | TCC            | COM            |
 * +-----+------------+---------+--------------+----------------+-----------------+---------+--------+----------------+----------------+--------------+----------------+----------------+
 * |     | Digital    |         |              |                |                 |         |        |                |                |              |                |                |
 * +-----+------------+---------+--------------+----------------+-----------------+---------+--------+----------------+----------------+--------------+----------------+----------------+
 * | 0   |            | PA00    | ~D0/XIN32    | EIC/EXTINT[0]  |                 |         |        | SERCOM1/PAD[0] |                | TCC2/WO[0]   |                |                |
 * | 1   |            | PA01    | ~D1/XOUT32   | EIC/EXTINT[1]  |                 |         |        | SERCOM1/PAD[1] |                | TCC2/WO[1]   |                |                |
 * | 2   | ~4         | PA08    | ~D2/SDA1     | EIC/NMI        |                 | AIN[16] |        | SERCOM0/PAD[0] | SERCOM2/PAD[0] | TCC0/WO[0]   | TCC1/WO[2]     | I2S/SD[1]      |
 * | 3   | ~3         | PA09    | ~D3/SCL1     | EIC/EXTINT[9]  |                 | AIN[17] |        | SERCOM0/PAD[1] | SERCOM2/PAD[1] | TCC0/WO[1]   | TCC1/WO[3]     | I2S/MCK[0]     |
 * | 4   | 1 <- TX    | PA10    | ~D4          | EIC/EXTINT[10] |                 | AIN[18] |        | SERCOM0/PAD[2] | SERCOM2/PAD[2] | TCC1/WO[0]   | TCC0/WO[2]     | I2S/SCK[0]     |
 * | 5   | 0 -> RX    | PA11    | ~D5          | EIC/EXTINT[11] |                 | AIN[19] |        | SERCOM0/PAD[3] | SERCOM2/PAD[3] | TCC1/WO[1]   | TCC0/WO[3]     | I2S/FS[0]      |
 * | 6   | 2          | PA14    | ~D6/XIN      | EIC/EXTINT[14] |                 |         |        | SERCOM2/PAD[2] |                | TC3/WO[0]    | TCC0/WO[4]     |                |
 * | 7   | ~5         | PA15    | ~D7/XOUT     | EIC/EXTINT[15] |                 |         |        | SERCOM2/PAD[3] |                | TC3/WO[1]    | TCC0/WO[5]     |                |
 * | 8   | ~11        | PA16    | ~D8          | EIC/EXTINT[0]  |                 |         |        | SERCOM1/PAD[0] | SERCOM3/PAD[0] | TCC2/WO[0]   | TCC0/WO[6]     |                |
 * | 9   | ~13        | PA17    | ~D9/SCK      | EIC/EXTINT[1]  |                 |         |        | SERCOM1/PAD[1] | SERCOM3/PAD[1] | TCC2/WO[1]   | TCC0/WO[7]     |                |
 * | 10  | ~10        | PA18    | ~D10/MISO    | EIC/EXTINT[2]  |                 |         |        | SERCOM1/PAD[2] | SERCOM3/PAD[2] | TC3/WO[0]    | TCC0/WO[2]     |                |
 * | 11  | ~12        | PA19    | ~D11/MOSI    | EIC/EXTINT[3]  |                 |         |        | SERCOM1/PAD[3] | SERCOM3/PAD[3] | TC3/WO[1]    | TCC0/WO[3]     | I2S/SD[0]      |
 * | 12  | SDA        | PA22    | ~D12/SDA     | EIC/EXTINT[6]  |                 |         |        | SERCOM3/PAD[0] |                | TC4/WO[0]    | TCC0/WO[4]     |                |
 * | 13  | SCL        | PA23    | ~D13/SCL     | EIC/EXTINT[7]  |                 |         |        | SERCOM3/PAD[1] |                | TC4/WO[1]    | TCC0/WO[5]     | USB/SOF 1kHz   |
 * | 14  |            | PA24    | ~D14/USB_NEG | EIC/EXTINT[12] |                 |         |        | SERCOM3/PAD[2] |                | TC5/WO[0]    | TCC1/WO[2]     | USB/DM         |
 * | 15  |            | PA25    | ~D15/USB_POS | EIC/EXTINT[13] |                 |         |        | SERCOM3/PAD[3] |                | TC5/WO[1]    | TCC1/WO[3]     | USB/DP         |
 * | 16  |            | PA27    | D16          | EIC/EXTINT[15] |                 |         |        |                |                |              |                |                |
 * | 17  |            | PA28    | D17          | EIC/EXTINT[8]  |                 |         |        |                |                |              |                |                |
 * +-----+------------+---------+--------------+----------------+-----------------+---------+--------+----------------+----------------+--------------+----------------+----------------+
 * |     | Analog     |         |              |                |                 |         |        |                |                |              |                |                |
 * +-----+------------+---------+--------------+----------------+-----------------+---------+--------+----------------+----------------+--------------+----------------+----------------+
 * | 18  | A0         | PA02    | A0/DAC       | EIC/EXTINT[2]  |                 | AIN[0]  |        |                |                |              |                |                |
 * | 19  | AREF       | PA03    | A1/AREF      | EIC/EXTINT[3]  | [ADC|DAC]/VREFA | AIN[1]  |        |                |                |              |                |                |
 * | 20  | A3         | PA04    | ~A2/TX/AREF  | EIC/EXTINT[4]  | ADC/VREFB       | AIN[4]  | AIN[0] |                | SERCOM0/PAD[0] | TCC0/WO[0]   |                |                |
 * | 21  | A4         | PA05    | ~A3/RX       | EIC/EXTINT[5]  |                 | AIN[5]  | AIN[1] |                | SERCOM0/PAD[1] | TCC0/WO[1]   |                |                |
 * | 22  | ~8         | PA06    | ~A4/RTS      | EIC/EXTINT[6]  |                 | AIN[6]  | AIN[2] |                | SERCOM0/PAD[2] | TCC1/WO[0]   |                |                |
 * | 23  | ~9         | PA07    | ~A5/CTS      | EIC/EXTINT[7]  |                 | AIN[7]  | AIN[3] |                | SERCOM0/PAD[3] | TCC1/WO[1]   |                | I2S/SD[0]      |
 * +-----+------------+---------+--------------+----------------+-----------------+---------+--------+----------------+----------------+--------------+----------------+----------------+
 * |     | Debug      |         |              |                |                 |         |        |                |                |              |                |                |
 * +-----+------------+---------+--------------+----------------+-----------------+---------+--------+----------------+----------------+--------------+----------------+----------------+
 * |     |            | PA30    | SWCLK        | EIC/EXTINT[10] |                 |         |        | SERCOM1/PAD[2] |                | TCC1/WO[0]   |                | SWCLK          |
 * |     |            | PA31    | SWDIO        | EIC/EXTINT[11] |                 |         |        | SERCOM1/PAD[3] |                | TCC1/WO[1]   |                | SWDIO          |
 * +-----+------------+---------+--------------+----------------+-----------------+---------+--------+----------------+----------------+--------------+----------------+----------------+
 */


#include "variant.h"

/*
 * Pins descriptions
 */
const PinDescription g_APinDescription[]=
{
  // 0..17 - Digital
  // ----------------------
  { PORTA,  0, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH0, TCC2_CH0, EXTERNAL_INT_0 },
  { PORTA,  1, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH1, TCC2_CH1, EXTERNAL_INT_1 },
  { PORTA,  8, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM1_CH2, TCC1_CH2, EXTERNAL_INT_NMI },
  { PORTA,  9, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM1_CH3, TCC1_CH3, EXTERNAL_INT_9 },
  { PORTA, 10, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM1_CH0, TCC1_CH0, EXTERNAL_INT_10 },
  { PORTA, 11, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM1_CH1, TCC1_CH1, EXTERNAL_INT_11 },
  { PORTA, 14, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM3_CH0, TC3_CH0, EXTERNAL_INT_14 },
  { PORTA, 15, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM3_CH1, TC3_CH1, EXTERNAL_INT_15 },
  { PORTA, 16, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM0_CH6, TCC0_CH6, EXTERNAL_INT_0 },
  { PORTA, 17, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM0_CH7, TCC0_CH7, EXTERNAL_INT_1 },
  { PORTA, 18, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM0_CH2, TCC0_CH2, EXTERNAL_INT_2 },
  { PORTA, 19, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM0_CH3, TCC0_CH3, EXTERNAL_INT_3 },
  { PORTA, 22, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM4_CH0, TC4_CH0, EXTERNAL_INT_6 },
  { PORTA, 23, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM4_CH0, TC4_CH1, EXTERNAL_INT_7 },
  { PORTA, 24, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM5_CH0, TC5_CH0, EXTERNAL_INT_12 },
  { PORTA, 25, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM5_CH1, TC5_CH1, EXTERNAL_INT_13 },
  { PORTA, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 },
  { PORTA, 28, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8 },
  
  // 18..23 - Analog
  // --------------------
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_NONE, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 },
  { PORTA,  3, PIO_ANALOG, PIN_ATTR_NONE, ADC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 },     
  { PORTA,  4, PIO_ANALOG, (PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel4, PWM0_CH0, TCC0_CH0, EXTERNAL_INT_4 },
  { PORTA,  5, PIO_ANALOG, (PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel5, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_5 },
  { PORTA,  6, PIO_ANALOG, (PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel6, PWM1_CH0, TCC1_CH0, EXTERNAL_INT_6 },
  { PORTA,  7, PIO_ANALOG, (PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel7, PWM1_CH1, TCC1_CH1, EXTERNAL_INT_7 },

  // 24..25 - USB
  // --------------------
  { PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_12 },
  { PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_13 },

  // 26 - DAC
  // ----------------------
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 },

  // 27..28 - Wire
  // ----------------------
  { PORTA,  22, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA,  23, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

  // 29 - Serial
  // ----------------------
  { PORTA,  4, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

  // 30 - Serial
  // ----------------------
  { PORTA, 14, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
} ;

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5 } ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;

Uart Serial(&sercom0, PIN_SERIAL_RX, PIN_SERIAL_TX, PAD_SERIAL_RX, PAD_SERIAL_TX);

void SERCOM0_Handler()
{
  Serial.IrqHandler();
}

void SERCOM2_Handler()
{
  Serial1.IrqHandler();
}