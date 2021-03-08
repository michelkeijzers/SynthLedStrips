// ArduinoStub.cpp
// Stub for Arduino function on Windows.
// Only for Windows

#ifdef _WINDOWS

#include <sys/timeb.h>
#include <time.h>
#include <stdlib.h>

#include "SynthLedStripsTypes.h"
#include "ArduinoStub.h"

void delay(uint32_t delayInMilliSeconds)
{
	timeb startTime;
	ftime(&startTime);

	uint64_t endTime = startTime.time * 1000 + startTime.millitm + delayInMilliSeconds;
	timeb runningTime;

	do
	{
		ftime(&runningTime);
	} while (runningTime.time * 1000 + runningTime.millitm < endTime);
}


uint32_t millis()
{
	timeb now;

	ftime(&now);
	return uint32_t(now.time * 1000 + now.millitm);
}


// ReSharper disable once CppParameterNeverUsed
void pinMode(int pin, int state)
{
	(void) pin;
	(void) state;
}

uint16_t analogRead(uint8_t pin)
{
	return rand() % 4096;
}


uint32_t random(uint32_t number)
{
	return rand() % number;
}


void randomSeed(uint16_t seed)
{
	srand(time(NULL));
}


#endif // _WINDOWS