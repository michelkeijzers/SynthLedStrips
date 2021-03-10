// ArduinoStub.h
// Stub for Arduino function on Windows.
// Only for Windows

#pragma once

#include "MathUtils.h"

#include "SynthLedStripsTypes.h"

#include "SerialStub.h"


#define F
#define PROGMEM

#define LED_BUILTIN 10
//#define INPUT        0 // Existing type in Windows
#define OUTPUT       1

// Digital I/O

extern void pinMode(int pin, int state);


// Analog I/O

extern uint16_t analogRead(uint8_t pin);

// Zero, Due & MKR Family

// Advanced I/O

// Time

extern void delay(uint32_t milliSeconds);

extern uint32_t millis();

// Math

#define ABS(x) MathUtils::Abs(x)

extern int constrain(int x, int lower, int upper);

extern int map(int value, int fromLower, int fromUpper, int toLower, int toUpper);

#define MIN(x, y) MathUtils::Min(x, y)

#define MAX(x, y) MathUtils::Max(x, y)


// Trigonometry

// Characters

// Random Numbers

extern uint32_t random(uint32_t number);

extern void randomSeed(uint16_t seed);

// Bits and Bytes

// External Interrupts

// Interrupts

// Communication

// USB

