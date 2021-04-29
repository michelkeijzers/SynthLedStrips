#include "ClassNames.h"
#include HEADER_FILE(SERIAL_CLASS)
#include "AssertUtils.h"
#include <stdio.h>

#ifdef _WINDOWS
#include <cstdlib>
#endif


void AssertUtils::MyAssert(bool expression)
{
	if (!expression)
	{
		abort;
	}
}


void AssertUtils::MyAssert(bool expression, const char* fileName, int line)
{
	if (!expression)
	{
		//Serial.println(funcName);
		Serial.println(fileName);
		Serial.println(line, DEC);
		Serial.flush();
		
		// Abort program execution.
		abort();
	}
}
