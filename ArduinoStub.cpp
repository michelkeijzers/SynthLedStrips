// ArduinoStub.cpp
// Stub for Arduino function on Windows.
// Only for Windows

#ifdef _WINDOWS

#include <sys/timeb.h>
#include <time.h>
#include <stdlib.h>
#include "ArduinoStub.h"

timeb* _startupTime = nullptr;

// Digital I/O

extern void pinMode(int pin, int state)
{
	(void) pin;
	(void) state;
}


// Analog I/O

extern uint16_t analogRead(uint8_t pin)
{
	return rand() % 4096;
}


// Zero, Due & MKR Family

// Advanced I/O

// Time

extern void delay(uint32_t delay)
{
	timeb startTime;
	ftime(&startTime);

	uint64_t endTime = startTime.time * 1000 + startTime.millitm + delay;
	timeb runningTime;

	do
	{
		ftime(&runningTime);
 	} while ((uint64_t) (runningTime.time * 1000 + runningTime.millitm) < endTime);
}


extern uint32_t millis()
{
	if (_startupTime == nullptr)
	{
		_startupTime = new timeb;
		ftime(_startupTime);
	}

	timeb now;

	ftime(&now);
	return uint32_t(now          .time * 1000 + now          .millitm - 
		            _startupTime->time * 1000 - _startupTime->millitm);
}


// Math

extern _Check_return_ int __cdecl abs(_In_ int a)
{
	return a < 0 ? -a : a;
}


extern int constrain(int x, int lower, int upper)
{
	return (x < lower ? lower : (x > upper ? upper : x));
}


// Manual test: map(5, 1, 10, 100, 200) = 10
extern int map(int value, int fromLower, int fromUpper, int toLower, int toUpper)
{
	return toLower + ((toUpper - toLower) / (fromUpper - fromLower)) * (value - fromLower);
}


extern int Min(int a, int b)
{
	return a < b ? a : b;
}


extern int Max(int a, int b)
{
	return a > b ? a : b;
}


// Trigonometry

// Characters

// Random Numbers

extern uint32_t random(uint32_t number)
{
	return rand() % number;
}


extern void randomSeed(uint16_t seed)
{
	srand((unsigned int) time(nullptr));
}


// Bits and Bytes

// External Interrupts

// Interrupts

// Communication

// USB

#endif // _WINDOWS
