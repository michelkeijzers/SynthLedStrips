// BitsUtils.cpp
// Utilities for bits and bytes.

#include "BitsUtils.h"


BitsUtils::BitsUtils()
{
}


BitsUtils::~BitsUtils()
{
}

/* static */ uint16_t BitsUtils::GetUint16(uint8_t* data, uint16_t offset)
{
	return (data[offset] << 8) + data[offset + 1];
}


/* static */ uint8_t BitsUtils::GetNrOfHighBits(uint32_t value)
{
	uint8_t nrOfHighBits = 0;
	while (value > 0)
	{
		nrOfHighBits += value & 1; // If right bit set, add 1
		value >>= 1; // Shift right
	}

	return nrOfHighBits;
}



/* static */ uint32_t BitsUtils::ChangeBit(uint32_t value, uint8_t bitNumber, bool set)
{
	return (value & ~(1 << bitNumber)) | (set ? 1 : 0) << bitNumber;
}


/*
 * Assuming bits to set are all 0, otherwise use ChangeBit.
 */
/* static */ void BitsUtils::SetBitsFromZero(uint8_t* address, uint8_t startBit, uint8_t nrOfBits, uint32_t value)
{
	while (nrOfBits > 0)
	{
		nrOfBits--;
		(*address) |= (value >> nrOfBits) << startBit;
		value %= (1 << nrOfBits); // Remove left bit
		
		if (startBit == 0)
		{
			startBit = 7;
			address++;
		}
		else
		{
			startBit--;
		}
	};
}


/* static */ uint32_t BitsUtils::GetBits(uint8_t* address, uint8_t startBit, uint32_t nrOfBits)
{
	uint32_t value = 0;
	
	while (nrOfBits > 0)
	{
		nrOfBits--;
		value |= ((((*address) & (1 << startBit)) > 0) ? 1 : 0) << nrOfBits;

		if (startBit == 0)
		{
			startBit = 7;
			address++;
		}
		else
		{
			startBit--;
		}
	}

	return value;
}

