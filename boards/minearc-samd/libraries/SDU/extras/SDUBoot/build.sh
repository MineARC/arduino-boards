#!/bin/sh -x

ARDUINO=arduino
SKETCH_NAME="SDUBoot.ino"
SKETCH="$PWD/$SKETCH_NAME"
BUILD_PATH="$PWD/build"
OUTPUT_PATH="../../src/boot"

if [[ "$OSTYPE" == "darwin"* ]]; then
	ARDUINO="/Applications/Arduino.app/Contents/MacOS/Arduino"
fi

buildSDUBootSketch() {
	VENDOR=$1
	BOARD=$2

	$ARDUINO --verify --board $VENDOR:$BOARD --preserve-temp-files --pref build.path="$BUILD_PATH" $SKETCH
	cat "$BUILD_PATH/$SKETCH_NAME.bin" | xxd -i > "$OUTPUT_PATH/$BOARD.h"
	cp "$BUILD_PATH/$SKETCH_NAME.bin" "$OUTPUT_PATH/$BOARD.bin"
	rm -rf "$BUILD_PATH"
}

mkdir -p "$OUTPUT_PATH"

buildSDUBootSketch "MineARC:samd" "bloodhound"

read