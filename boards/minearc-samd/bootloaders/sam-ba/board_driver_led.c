/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  Copyright (c) 2015 Atmel Corporation/Thibaut VIARD.  All right reserved.

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

#include "board_driver_led.h"

volatile uint8_t ledKeepValue = 0;
volatile uint8_t ledTargetValue = 20;
volatile int8_t ledDirection = 1;

inline void LED_pulse() {
  if (ledKeepValue == 0) {
    ledTargetValue += ledDirection;
    LED_toggle();
  }
  ledKeepValue++;

  if (ledTargetValue > 240 || ledTargetValue < 10) {
    ledDirection = -ledDirection;
    ledTargetValue += ledDirection;
  }

  if (ledKeepValue == ledTargetValue) {
    LED_toggle();
  }
}

void rgb_init() {
#if defined(BOARD_RGBLED_CLOCK_PIN)
  // using APA102, set pins to outputs
  PINOP(BOARD_RGBLED_CLOCK_PIN, DIRSET);
  PINOP(BOARD_RGBLED_DATA_PIN, DIRSET);
#endif

  rgb_set_color(COLOR_LEAVE);
}

#if defined(BOARD_RGBLED_CLOCK_PIN)
void write_apa_byte(uint8_t x) {
  for (uint8_t i = 0x80; i != 0; i >>= 1) {
    if (x & i)
      PINOP(BOARD_RGBLED_DATA_PIN, OUTSET);
    else
      PINOP(BOARD_RGBLED_DATA_PIN, OUTCLR);

    PINOP(BOARD_RGBLED_CLOCK_PIN, OUTSET);

    PINOP(BOARD_RGBLED_CLOCK_PIN, OUTCLR);
  }
}
#endif

void rgb_set_color(uint32_t color) {
#if defined(BOARD_RGBLED_CLOCK_PIN)
  write_apa_byte(0x0);
  write_apa_byte(0x0);
  write_apa_byte(0x0);
  write_apa_byte(0x0);

  write_apa_byte(0xFF);
  write_apa_byte(color >> 16);
  write_apa_byte(color >> 8);
  write_apa_byte(color);

  write_apa_byte(0xFF);
  write_apa_byte(0xFF);
  write_apa_byte(0xFF);
  write_apa_byte(0xFF);

  // set clock port low for ~10ms
  delay(50);
#endif // BOARD_RGBLED_CLOCK_PIN
}

void delay(uint32_t ms) {
  ms <<= 8;
  for (int i = 1; i < ms; ++i) {
      asm("nop");
  }
}
