/*
  RTC library for Arduino Zero.
  Copyright (c) 2015 Arduino LLC. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <time.h>

#include "RTCZero.h"

voidFuncPtr _callback = NULL;

void RTCZero::begin(uint32_t compare) {
  MCLK->APBAMASK.bit.RTC_ = 1; // enable RTC clock

  RTC->MODE0.CTRLA.bit.ENABLE = 0; // disable RTC
  while (RTC->MODE0.SYNCBUSY.bit.ENABLE)
    ;
  RTC->MODE0.CTRLA.bit.SWRST = 1;
  while (RTC->MODE0.SYNCBUSY.bit.SWRST)
    ;
  RTC->MODE0.CTRLA.bit.SWRST = 0;
  while (RTC->MODE0.SYNCBUSY.bit.SWRST)
    ;

  RTC->MODE0.CTRLA.bit.MODE = RTC_MODE0_CTRLA_MODE_COUNT32_Val;
  RTC->MODE0.CTRLA.bit.MATCHCLR = 1;
  RTC->MODE0.INTENSET.reg |= RTC_MODE0_INTENSET_CMP0;
  RTC->MODE0.COMP[0].bit.COMP = compare;

  RTC->MODE0.CTRLA.bit.ENABLE = 1;
  while (RTC->MODE0.SYNCBUSY.bit.ENABLE)
    ;

  NVIC_EnableIRQ(RTC_IRQn); // enable RTC interrupt
  NVIC_SetPriority(RTC_IRQn, 0x00);
}

void RTCZero::attachInterrupt(voidFuncPtr callback) { _callback = callback; }

void RTCZero::setCompare(uint32_t compare) {
  RTC->MODE0.COMP[0].bit.COMP = compare;
  RTC->MODE0.COUNT.bit.COUNT = 0;
  while (RTC->MODE0.SYNCBUSY.bit.COUNT)
    ;
}

void RTC_Handler(void) {
  if (_callback != NULL) {
    _callback();
  }

  RTC->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_CMP0; // must clear flag at end
}

void RTCZero::standbyMode() {
  PM->SLEEPCFG.bit.SLEEPMODE = PM_SLEEPCFG_SLEEPMODE_STANDBY_Val;
  __DSB();
  __WFI();
}