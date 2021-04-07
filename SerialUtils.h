#pragma once

#include <cstdint>

class SerialUtils
{
public:
	static void PrintUint(const char* item, uint32_t value);
	static void PrintlnUint(const char* item, uint32_t value);
	static void PrintInt(const char* item, int32_t value);
	static void PrintlnInt(const char* item, int32_t value);

	static void PrintRgb(uint8_t red, uint8_t green, uint8_t blue);
};
