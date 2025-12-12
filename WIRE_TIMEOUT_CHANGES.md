# Wire Library Timeout Support

## Overview
Added timeout support to the Wire (I2C) library. The Wire class already extends Stream, which has a `_timeout` member and `setTimeout()` method, but the underlying SERCOM functions had blocking while loops that could hang indefinitely.

## Changes Made

### 1. SERCOM.h
Added timeout-aware overloaded versions of three critical functions:
- `bool startTransmissionWIRE(uint8_t address, SercomWireReadWriteFlag flag, unsigned long timeout_ms)`
- `bool sendDataMasterWIRE(uint8_t data, unsigned long timeout_ms)`
- `uint8_t readDataWIRE(unsigned long timeout_ms, bool *timeout_occurred)`

The original versions (without timeout parameters) remain for backward compatibility and now delegate to the timeout versions with `timeout_ms = 0` (blocking behavior).

### 2. SERCOM.cpp
Implemented the timeout-aware functions with the following behavior:
- When `timeout_ms > 0`, the functions check `millis()` against the start time in their blocking loops
- When `timeout_ms == 0`, functions behave as before (blocking indefinitely)
- `startTransmissionWIRE()` and `sendDataMasterWIRE()` return `false` on timeout
- `readDataWIRE()` sets a `timeout_occurred` flag and returns 0 on timeout

### 3. Wire.cpp
Updated the two main I2C operations to use timeouts:

#### requestFrom()
- Now calls `sercom->startTransmissionWIRE(address, WIRE_READ_FLAG, _timeout)`
- Calls `sercom->readDataWIRE(_timeout, &timeout_occurred)` with timeout checking
- Returns the number of bytes successfully read before timeout
- Sends STOP condition if timeout occurs and `stopBit` is true

#### endTransmission()
- Now calls `sercom->startTransmissionWIRE(txAddress, WIRE_WRITE_FLAG, _timeout)`
- Calls `sercom->sendDataMasterWIRE(data, _timeout)` for each byte
- Returns error code 2 or 3 on timeout (same as NACK errors for backward compatibility)
- Added error code 5 to the documentation comments for future timeout-specific error handling

## Usage

```cpp
#include <Wire.h>

void setup() {
  Wire.begin();
  
  // Set timeout to 100ms (default is 1000ms from Stream)
  Wire.setTimeout(100);
}

void loop() {
  Wire.beginTransmission(0x50);
  Wire.write(0x00);
  uint8_t error = Wire.endTransmission();
  
  // error == 2 or 3 could now indicate timeout as well as NACK
  
  uint8_t bytesRead = Wire.requestFrom(0x50, 16);
  // If timeout occurs, bytesRead will be less than 16
  
  delay(1000);
}
```

## Backward Compatibility
All changes are backward compatible:
- Existing code continues to work without modification
- The default timeout behavior is preserved (1000ms from Stream class)
- SERCOM functions without timeout parameters still exist and work as before
- Error codes remain the same (timeout failures return existing error codes 2 or 3)

## Benefits
1. **Prevents indefinite hangs**: I2C bus issues no longer freeze the microcontroller
2. **User-configurable**: Developers can adjust timeout via `setTimeout()`
3. **Graceful degradation**: Failed operations return error codes rather than hanging
4. **Stream API integration**: Uses the standard Stream timeout mechanism
