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

#include "variant.h"

/*
// PA00 - N/A, 1/0
// PA01 - N/A, 1/1

PA02 - N/A, N/A
PA03 - N/A, N/A

PA04 - N/A, 0/0
PA05 - N/A, 0/1
PA06 - N/A, 0/2
PA07 - N/A, 0/3

~PA08 - 0/0, 2/1
~PA09 - 0/1, 2/0
~PA10 - 0/2, 2/2
~PA11 - 0/3, 2/3

~PA12 - 2/0, 4/1
~PA13 - 2/1, 4/0 // spi
PA14 - 2/2, 4/2  // spi
PA15 - 2/3, 4/3  // spi

~PA16 - 1/0, 3/1 // i2c
~PA17 - 1/1, 3/0 // i2c
~PA18 - 1/2, 3/2
~PA19 - 1/3, 3/3

~PA20 - 5/2, 3/2
~PA21 - 5/3, 3/3

~PA22 - 3/0, 5/1 // i2c
~PA23 - 3/1, 5/0 // i2c

PA24 - 3/2, 5/2
PA25 - 3/3, 5/3

PA27 - N/A, N/A

// PA30 - 7/2, 1/2
// PA31 - 7/3, 1/3

PB02 - N/A, 5/0 // uart
PB03 - N/A, 5/1 // uart

PB08 - N/A, 4/0 // uart
PB09 - N/A, 4/1 // uart
~PB10 - N/A, 4/2
~PB11 - N/A, 4/3

PB22 - 1/2, 5/2
PB23 - 1/3, 5/3
*/

/*
 * Pins descriptions
 */
const PinDescription g_APinDescription[]=
{
  // 0..24 - Digital
  // ----------------------
  { PORTA,  8, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM0_CH0, TCC0_CH0, EXTERNAL_INT_NMI },
  { PORTA,  9, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_9 },
  { PORTA, 10, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM0_CH2, TCC0_CH2, EXTERNAL_INT_10 },
  { PORTA, 11, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM0_CH3, TCC0_CH3, EXTERNAL_INT_11 },

  { PORTB, 10, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM0_CH4, TCC0_CH4, EXTERNAL_INT_10 },
  { PORTB, 11, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM0_CH5, TCC0_CH5, EXTERNAL_INT_11 },

  { PORTA, 12, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM0_CH6, TCC0_CH6, EXTERNAL_INT_12 },
  { PORTA, 13, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM0_CH7, TCC0_CH7, EXTERNAL_INT_13 },
  { PORTA, 14, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_14 },
  { PORTA, 15, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 },

  { PORTA, 16, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM1_CH0, TCC1_CH0, EXTERNAL_INT_0 },
  { PORTA, 17, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM1_CH1, TCC1_CH1, EXTERNAL_INT_1 },
  { PORTA, 18, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM1_CH2, TCC1_CH2, EXTERNAL_INT_2 },
  { PORTA, 19, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM1_CH3, TCC1_CH3, EXTERNAL_INT_3 },

  { PORTA, 20, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM1_CH4, TCC1_CH4, EXTERNAL_INT_4 },
  { PORTA, 21, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM1_CH5, TCC1_CH5, EXTERNAL_INT_5 },

  { PORTA, 22, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM1_CH6, TCC1_CH6, EXTERNAL_INT_6 },
  { PORTA, 23, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM1_CH7, TCC1_CH7, EXTERNAL_INT_7 },

  { PORTA, 24, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8 },
  { PORTA, 25, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9 },

  { PORTA, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 },

  { PORTB,  2, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 },
  { PORTB,  3, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 },

  { PORTB, 22, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 },
  { PORTB, 23, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 },
  
  // 25..32 - Analog
  // --------------------
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 },
  { PORTA,  3, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 },

  { PORTA,  4, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel4, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4 },
  { PORTA,  5, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel5, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5 },
  { PORTA,  6, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel6, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 },
  { PORTA,  7, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel7, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 },

  { PORTB,  8, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel2, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8 },
  { PORTB,  9, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel3, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9 },

  // 33..34 - USB
  // --------------------
  { PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

  // 35..36 - DAC
  // ----------------------
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA,  5, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

  // 37..38 - Wire
  // ----------------------
  { PORTA, 16, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 17, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

  // 39..40 - Wire1
  // ----------------------
  { PORTA,  22, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA,  23, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

  // 41..44 - SPI
  // ----------------------
  { PORTA, 12, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 13, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 14, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 15, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

  // 45..46 - Serial
  // ----------------------
  { PORTB,  2, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTB,  3, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

  // 47..48 - Serial1
  // ----------------------
  { PORTB,  8, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTB,  9, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
} ;

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TCC3, TCC4, TC0, TC1, TC2, TC3, TC4, TC5 } ;
const uint32_t GCLK_CLKCTRL_IDs[TCC_INST_NUM+TC_INST_NUM] = { TCC0_GCLK_ID, TCC1_GCLK_ID, TCC2_GCLK_ID, TCC3_GCLK_ID, TCC4_GCLK_ID, TC0_GCLK_ID, TC1_GCLK_ID, TC2_GCLK_ID, TC3_GCLK_ID, TC4_GCLK_ID, TC5_GCLK_ID } ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;
SERCOM sercom4( SERCOM4 ) ;
SERCOM sercom5( SERCOM5 ) ;

Uart Serial(&sercom5, PIN_SERIAL_RX, PIN_SERIAL_TX, PAD_SERIAL_RX, PAD_SERIAL_TX);
Uart Serial1(&sercom4, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX);

void SERCOM5_Handler()
{
  Serial.IrqHandler();
}

void SERCOM4_Handler()
{
  Serial1.IrqHandler();
}