#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define __SAMD21E18A__ 1
#define CRYSTALLESS    1

#define VENDOR_NAME "MineARC"
#define PRODUCT_NAME "Pathfinder"
#define VOLUME_LABEL "Pathfinder"
#define INDEX_URL "https://github.com/MineARC/arduino-boards"
#define BOARD_ID "SAMD21E18A-Pathfinder-v0"

#define USB_VID 0xFFFF
#define USB_PID 0x0000

#define LED_PIN PIN_PA07

#define BOARD_RGBLED_CLOCK_PIN            PIN_PA17
#define BOARD_RGBLED_DATA_PIN             PIN_PA19

#endif
