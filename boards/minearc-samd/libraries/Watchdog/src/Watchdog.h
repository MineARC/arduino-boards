#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <Arduino.h>

class Watchdog {

public:
  enum Period_Size : uint8_t {
    PERIOD_8 = 0x0,    // 8 clock cycles
    PERIOD_16 = 0x1,   // 16 clock cycles
    PERIOD_32 = 0x2,   // 32 clock cycles
    PERIOD_64 = 0x3,   // 64 clock cycles
    PERIOD_128 = 0x4,  // 128 clock cycles
    PERIOD_256 = 0x5,  // 256 clock cycles
    PERIOD_512 = 0x6,  // 512 clock cycles
    PERIOD_1024 = 0x7, // 1024 clock cycles
    PERIOD_2048 = 0x8, // 2048 clock cycles
    PERIOD_4096 = 0x9, // 4096 clock cycles
    PERIOD_8192 = 0xA, // 8192 clock cycles
    PERIOD_16384 = 0xB // 16384 clock cycles
  };

  void resetWDT();

  void systemReset();

  void setupWDT(Period_Size period = PERIOD_16384);
};

#endif // WATCHDOG_H