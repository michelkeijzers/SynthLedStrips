#include "ArrayUtils.h"


ArrayUtils::ArrayUtils()
{
}


ArrayUtils::~ArrayUtils()
{
}


/* static */ uint8_t ArrayUtils::FindNearestIndexOfValue(const uint8_t array[], uint8_t arrayLength, uint8_t value)
{
	for (uint8_t index = 0; index < arrayLength; index++)
	{
		if (value == array[index])
		{
			return index;
		}
		
		if (value < array[index])
		{
			return ((index > 0) && (value - array[index - 1] < array[index] - value)) ? index - 1 : index;
		}

		index++;
	}

	return arrayLength - 1;
}
