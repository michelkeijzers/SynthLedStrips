// BitsUtils.h
// Utilities for bits and bytes.

#pragma once

#include <cstdint>

class BitsUtils
{
public:

  static uint16_t GetUint16(uint8_t* data, uint16_t offset);

  static uint8_t GetNrOfHighBits(uint32_t value);
  
  //static uint8_t indexOfBit(uint32_t value, uint8_t bit); // bit 0..31

  static uint32_t ChangeBit(uint32_t value, uint8_t bitNumber, bool set);

  static void SetBitsFromZero(uint8_t* address, uint8_t startBit, uint8_t nrOfBits, uint32_t value);

  static uint32_t GetBits(uint8_t* address, uint8_t startBit, uint32_t nrOfBits);

private:
  BitsUtils();
};
