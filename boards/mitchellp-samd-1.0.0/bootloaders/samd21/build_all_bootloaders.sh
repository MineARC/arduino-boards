#!/bin/bash -ex

BOARD_ID=mitchellp_samd21g NAME=mitchellp_samd21g make clean all

BOARD_ID=mitchellp_samd21e NAME=mitchellp_samd21e make clean all

echo Done building bootloaders!

