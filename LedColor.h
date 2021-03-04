#pragma once

#include "SynthLedStripsTypes.h"

class LedColor
{
public:
	enum class EColor { Black, White, Red, Lime, Blue, Yellow, Cyan, Magenta, Silver, Gray };

	static void SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, LedColor::EColor color, uint8_t step);

	static void SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t rgb);

	static void SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t redValue, uint8_t greenValue, uint8_t blueValue);

	static void SetBrightness(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t percentage_0, uint8_t percentage_1);
};
