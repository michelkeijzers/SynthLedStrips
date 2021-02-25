// ArduinoStub.cpp
// Stub for Arduino function on Windows.
// Only for Windows

#ifdef _WINDOWS

#include "SynthLedStripsTypes.h"
#include "ArduinoStub.h"
#include <sys/timeb.h>


void delay(uint32_t delayInMilliSeconds)
{
	timeb startTime;
	ftime(&startTime);

	uint32_t endTime = startTime.time * 1000 + startTime.millitm + delayInMilliSeconds;
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

#endif // _WINDOWS