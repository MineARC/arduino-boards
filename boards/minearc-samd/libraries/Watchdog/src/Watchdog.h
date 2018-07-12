#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <Arduino.h>

class Watchdog {

public:
  enum Clock_Speed : uint8_t {
    CLOCK_16x = 0,   // Hexadeca speed
    CLOCK_8x = 1,    // Octa speed
    CLOCK_4x = 2,    // Quad speed
    CLOCK_2x = 3,    // Double speed
    CLOCK_1x = 4,    // Regular speed 1s = 1s
    CLOCK_1_2x = 5,  // Half speed
    CLOCK_1_4x = 6,  // Quarter speed
    CLOCK_1_8x = 7,  // One eighth speed
    CLOCK_1_16x = 8, // One sixteenth speed
    CLOCK_1_32x = 9, // One thirty-second speed
    CLOCK_1_64x = 10 // One sixty-fourth speed
  };

  enum Window_Size : uint8_t {
    WINDOW_8 = 0x0,    // 8 clock cycles
    WINDOW_16 = 0x1,   // 16 clock cycles
    WINDOW_32 = 0x2,   // 32 clock cycles
    WINDOW_64 = 0x3,   // 64 clock cycles
    WINDOW_128 = 0x4,  // 128 clock cycles
    WINDOW_256 = 0x5,  // 256 clock cycles
    WINDOW_512 = 0x6,  // 512 clock cycles
    WINDOW_1024 = 0x7, // 1024 clock cycles
    WINDOW_2048 = 0x8, // 2048 clock cycles
    WINDOW_4096 = 0x9, // 4096 clock cycles
    WINDOW_8192 = 0xA, // 8192 clock cycles
    WINDOW_16384 = 0xB // 16384 clock cycles
  };

  void WDTsync();

  void resetWDT();

  void systemReset();

  void setupWDT(Clock_Speed div = CLOCK_1x, Window_Size period = WINDOW_16384);
};

#endif // WATCHDOG_H