#include "Watchdog.h"

void Watchdog::resetWDT() {
  // reset the WDT watchdog timer.
  WDT->CLEAR.reg = 0xA5;
  while (WDT->SYNCBUSY.bit.CLEAR == 1)
    ;
}

void Watchdog::systemReset() {
  // use the WDT watchdog timer to force a system reset.
  WDT->CLEAR.reg = 0x00;
  while (WDT->SYNCBUSY.bit.CLEAR == 1)
    ;
}

void Watchdog::setupWDT(Period_Size period) {
  MCLK->APBAMASK.bit.WDT_ = 1; // enable watchdog clock

  WDT->CTRLA.bit.ENABLE = 0; // disable watchdog
  while (WDT->SYNCBUSY.bit.ENABLE == 1)
    ;

  WDT->CONFIG.bit.PER = min(period, PERIOD_16384);

  WDT->CTRLA.bit.ENABLE = 1; // enable watchdog
  while (WDT->SYNCBUSY.bit.ENABLE == 1)
    ;
}