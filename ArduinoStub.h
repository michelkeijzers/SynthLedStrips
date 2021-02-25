// ArduinoStub.h
// Stub for Arduino function on Windows.
// Only for Windows

#pragma once

#include "SynthLedStripsTypes.h"

#define F
#define PROGMEM

#define LED_BUILTIN 10
//#define INPUT        0 // Existing type in Windows
#define OUTPUT       1

extern void delay(uint32_t milliSeconds);

extern uint32_t millis();

extern void pinMode(int pin, int state);