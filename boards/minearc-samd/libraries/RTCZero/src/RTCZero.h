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

#ifndef RTC_ZERO_H
#define RTC_ZERO_H

#include "Arduino.h"

typedef void (*voidFuncPtr)(void);

class RTCZero {
public:
  enum Alarm_Match : uint8_t // Should we have this enum or just use the identifiers from /component/rtc.h ?
  { MATCH_OFF = RTC_MODE2_MASK_SEL_OFF_Val,                  // Never
    MATCH_SS = RTC_MODE2_MASK_SEL_SS_Val,                    // Every Minute
    MATCH_MMSS = RTC_MODE2_MASK_SEL_MMSS_Val,                // Every Hour
    MATCH_HHMMSS = RTC_MODE2_MASK_SEL_HHMMSS_Val,            // Every Day
    MATCH_DHHMMSS = RTC_MODE2_MASK_SEL_DDHHMMSS_Val,         // Every Month
    MATCH_MMDDHHMMSS = RTC_MODE2_MASK_SEL_MMDDHHMMSS_Val,    // Every Year
    MATCH_YYMMDDHHMMSS = RTC_MODE2_MASK_SEL_YYMMDDHHMMSS_Val // Once, on a specific date and a specific time
  };

  enum Clock_Speed : uint8_t {
    CLOCK_16x = 0,  // Hexadeca speed
    CLOCK_8x = 1,   // Octa speed
    CLOCK_4x = 2,   // Quad speed
    CLOCK_2x = 3,   // Double speed
    CLOCK_1x = 4,   // Regular speed 1s = 1s
    CLOCK_1_2x = 5, // Half speed
    CLOCK_1_4x = 6, // Quarter speed
    CLOCK_1_8x = 7, // Eighth speed
    CLOCK_1_16x = 8 // Sixteenth speeds
  };

  RTCZero();
  void begin(Clock_Speed div = CLOCK_1x, bool resetTime = false);

  void enableAlarm(Alarm_Match match);
  void disableAlarm();

  void attachInterrupt(voidFuncPtr callback);
  void detachInterrupt();

  void standbyMode();

  /* Get Functions */

  uint8_t getSeconds();
  uint8_t getMinutes();
  uint8_t getHours();

  uint8_t getDay();
  uint8_t getMonth();
  uint8_t getYear();

  uint8_t getAlarmSeconds();
  uint8_t getAlarmMinutes();
  uint8_t getAlarmHours();

  uint8_t getAlarmDay();
  uint8_t getAlarmMonth();
  uint8_t getAlarmYear();

  /* Set Functions */

  void setSeconds(uint8_t seconds);
  void setMinutes(uint8_t minutes);
  void setHours(uint8_t hours);
  void setTime(uint8_t hours, uint8_t minutes, uint8_t seconds);

  void setDay(uint8_t day);
  void setMonth(uint8_t month);
  void setYear(uint8_t year);
  void setDate(uint8_t day, uint8_t month, uint8_t year);

  void setAlarmSeconds(uint8_t seconds);
  void setAlarmMinutes(uint8_t minutes);
  void setAlarmHours(uint8_t hours);
  void setAlarmTime(uint8_t hours, uint8_t minutes, uint8_t seconds);

  void setAlarmDay(uint8_t day);
  void setAlarmMonth(uint8_t month);
  void setAlarmYear(uint8_t year);
  void setAlarmDate(uint8_t day, uint8_t month, uint8_t year);

  /* Epoch Functions */

  uint32_t getEpoch();
  uint32_t getY2kEpoch();
  void setEpoch(uint32_t ts);
  void setY2kEpoch(uint32_t ts);
  void setAlarmEpoch(uint32_t ts);

  bool isConfigured() { return _configured; }

private:
  bool _configured;

  void config32kOSC(void);
  void configureClock(Clock_Speed div);
  void RTCreadRequest();
  bool RTCisSyncing(void);
  void RTCdisable();
  void RTCenable();
  void RTCreset();
  void RTCresetRemove();
};

#endif // RTC_ZERO_H