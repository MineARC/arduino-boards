/*
  Copyright (c) 2017 Arduino LLC.  All right reserved.

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

#include <FlashStorage.h>
#include <SD.h>
#include <SPIMemory.h>
#include <crc32.h>

const uint32_t SDU_START = 0x0000;
const uint32_t SDU_SIZE = 0x4000;
const uint32_t SKETCH_START = SDU_START + SDU_SIZE;
const char *UPDATE_FILE = "UPDATE.BIN";

#ifndef SDCARD_SS_PIN
#define SDCARD_SS_PIN 16
#endif

FlashClass flash;
SPIFlash spi_flash(SPIFLASH_SS_PIN);

// Initialize C library
extern "C" void __libc_init_array(void);

int main() {
  init();

  __libc_init_array();

  delay(1);

  dsu_crc32_init();

  if (SD.begin(SDCARD_SS_PIN) && SD.exists(UPDATE_FILE)) {
    File updateFile = SD.open(UPDATE_FILE);

    uint32_t updateSize = updateFile.size();

    uint32_t flashAddress = SKETCH_START;

    // erase the pages
    flash.erase((void *)flashAddress, updateSize);

    uint8_t buffer[512];
    // write the pages
    for (uint32_t i = 0, bytes = 0; i < updateSize; i += bytes, flashAddress += bytes) {
      bytes = updateFile.read(buffer, sizeof(buffer));
      flash.write((void *)flashAddress, buffer, bytes);
    }

    updateFile.close();

    SD.remove(UPDATE_FILE);
  } /* else if (spi_flash.begin() && spiflash.exists(UPDATE_FILE)) {
     File updateFile = spiflash.open(UPDATE_FILE);

     uint32_t updateSize = updateFile.size();

     uint8_t buffer[0x1000];
     uint32_t crc = 0xFFFFFFFF;
     // write the pages
     for (uint32_t i = 0, bytes = 0; i < updateSize; i += bytes, flashAddress += bytes) {
       bytes = updateFile.read(buffer, sizeof(buffer));
       dsu_crc32_cal((uint32_t)buffer, sizeof(buffer), &crc);
     }

     uint32_t flashAddress = SKETCH_START;

     // erase the pages
     flash.erase((void *)flashAddress, updateSize);

     // write the pages
     for (uint32_t i = 0, bytes = 0; i < updateSize; i += bytes, flashAddress += bytes) {
       bytes = updateFile.read(buffer, sizeof(buffer));
       flash.write((void *)flashAddress, buffer, bytes);
     }*/

  updateFile.close();

  spiflash.remove(UPDATE_FILE);
}

// jump to the sketch
__set_MSP(SKETCH_START);

// Reset vector table address
SCB->VTOR = SKETCH_START & SCB_VTOR_TBLOFF_Msk;

// address of Reset_Handler is written by the linker at the beginning of the .text section (see linker script)
uint32_t resetHandlerAddress = SKETCH_START + 1;
// jump to reset handler
asm("bx %0" ::"r"(resetHandlerAddress));
}
