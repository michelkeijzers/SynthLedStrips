#pragma once

#include "SynthLedStripsTypes.h"

class LedColor
{
public:
	enum class EColor { Black, White, Red, Lime, Blue, Yellow, Cyan, Magenta, Silver, Gray,
	                    Random, Rainbow};

	static void SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, LedColor::EColor color, uint32_t step);

	static void SetRandom(uint8_t* red, uint8_t* green, uint8_t* blue);
	static void SetRainbow(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t step);

	static void SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t rgb);

	static void SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t redValue, uint8_t greenValue, uint8_t blueValue);

	static uint8_t SetBrightness(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t percentage_0, uint8_t percentage_1);
};
