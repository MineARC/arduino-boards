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

#include <Arduino.h>
#include <SPIMemory.h>
#include <FlashStorage.h>
#include <SD.h>
#include <CRC32.h>

struct flash_header_t {
  char magic[4];
  uint32_t isValid;
  uint32_t sectors;
  uint32_t crcs[120];
  uint32_t crc;
};

#define SDU_START 0x0
#define SDU_SIZE 0x10000
#define SECTOR_SIZE 0x2000

#define SKETCH_START (uint32_t *)(SDU_START + SDU_SIZE)

#ifndef SDCARD_SS_PIN
#define SDCARD_SS_PIN 6
#endif

#ifndef FLASH_SS_PIN
#define FLASH_SS_PIN A5
#endif

#define UPDATE_FILE "UPDATE.BIN"

FlashClass flash;
SPIFlash spiflash = SPIFlash(FLASH_SS_PIN);
flash_header_t flashHeader;
uint8_t buffer[SECTOR_SIZE];

// Initialize C library
extern "C" void __libc_init_array(void);

int main() {
  init();

  __libc_init_array();

  delay(1);

  if (SD.begin(SDCARD_SS_PIN) && SD.exists(UPDATE_FILE)) {
    File updateFile = SD.open(UPDATE_FILE);
    uint32_t updateSize = updateFile.size();
    uint32_t flashAddress = (uint32_t)SKETCH_START;

    // Erase old software
    flash.erase((void *)flashAddress, updateSize);

    // Write new software
    for (uint32_t i = 0; i < updateSize; i += sizeof(buffer)) {
      updateFile.read(buffer, sizeof(buffer));
      flash.write((void *)flashAddress, buffer, sizeof(buffer));
      flashAddress += sizeof(buffer);
    }

    updateFile.close();
    // Delete update file
    SD.remove(UPDATE_FILE);
  } else if(spiflash.begin()) {
    uint32_t flashAddress = (uint32_t)SKETCH_START;
    uint32_t spiAddress = 0;
    bool flashValid = true;
    uint32_t crc;

    spiflash.readByteArray(spiAddress, (uint8_t *)(&flashHeader), sizeof(buffer));
    spiAddress += sizeof(buffer);
    crc = CRC32::calculate(&flashHeader, sizeof(flashHeader) - sizeof(flashHeader.crc));

    if (crc == flashHeader.crc && flashHeader.isValid == 1) {

      // Verify contents of SPI flash
      for (uint32_t i = 0; i < flashHeader.sectors && flashValid; i++) {
        spiflash.readByteArray(spiAddress, buffer, sizeof(buffer));
        spiAddress += sizeof(buffer);
        crc = CRC32::calculate(&buffer, sizeof(buffer));
        flashValid = crc == flashHeader.crcs[flashHeader.sectors];
      }

      if (flashValid) {
        // Erase old software
        flash.erase((void *)flashAddress, flashHeader.sectors * SECTOR_SIZE);
        spiAddress = sizeof(buffer);

        // Write new software
        for (uint32_t i = 0; i < flashHeader.sectors; i++) {
          spiflash.readByteArray(spiAddress, buffer, sizeof(buffer));
          flash.write((void *)flashAddress, buffer, sizeof(buffer));
          spiAddress += sizeof(buffer);
          flashAddress += sizeof(buffer);
        }

        // Erase contents of SPI flash
        spiflash.eraseSector(0);
      }
    }
  }

  // jump to the sketch
  __set_MSP(*SKETCH_START);

  // Reset vector table address
  SCB->VTOR = ((uint32_t)(SKETCH_START)&SCB_VTOR_TBLOFF_Msk);

  // address of Reset_Handler is written by the linker at the beginning of the .text section (see linker script)
  uint32_t resetHandlerAddress = (uint32_t) * (SKETCH_START + 1);
  // jump to reset handler
  asm("bx %0" ::"r"(resetHandlerAddress));
}
