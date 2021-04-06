#pragma once

#include <cstdint>

class ArrayUtils
{
public:
	// Assuming ascending order
	static uint8_t FindNearestIndexOfValue(const uint8_t array[], uint8_t arrayLength, uint8_t value);

private:
	ArrayUtils();
};
