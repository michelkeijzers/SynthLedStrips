/*

#include "AssertUtils.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

*/

/* static */
#include "ClassNames.h"
#include HEADER_FILE(SERIAL_CLASS)
#include "AssertUtils.h"
#include <stdio.h>
#ifdef _WINDOWS
#include <cstdlib>
#endif


void AssertUtils::MyAssert(bool expression)
{
	//TODO call MyAssert with fileName/line
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
