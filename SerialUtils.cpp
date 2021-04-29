#include <cstdint>

#include "SerialUtils.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

/* static */ void SerialUtils::PrintUint(const char* item, uint32_t value)
{
	Serial.print(item);
	Serial.print(":");
	Serial.print((int) value);
	Serial.print(", ");
}


/* static */ void SerialUtils::PrintlnUint(const char* item, uint32_t value)
{
	Serial.print(item);
	Serial.print(":");
	Serial.println((int) value);
}


/* static */ void SerialUtils::PrintInt(const char* item, int32_t value)
{
	Serial.print(item);
	Serial.print(":");
	Serial.print(value);
	Serial.print("; ");
}


/* static */ void SerialUtils::PrintlnInt(const char* item, int32_t value)
{
	Serial.print(item);
	Serial.print(":");
	Serial.println(value);
}


/* static */ void SerialUtils::PrintRgb(uint8_t red, uint8_t green, uint8_t blue)
{
	Serial.print("RGB: (");
	Serial.print(red);
	Serial.print(",");
	Serial.print(green);
	Serial.print(",");
	Serial.print(blue);
	Serial.print("); ");
}
