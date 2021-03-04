#pragma once

#include "SynthLedStripsTypes.h"

#include "ClassNames.h"
#include HEADER_FILE(FAST_LED_CLASS)

class Color
{
public:
	enum class EColor { Black, White, Red, Lime, Blue, Yellow, Cyan, Magenta, Silver, Gray };

	static void SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t index, uint8_t step);

	static void SetRgb(FastLedCRGB* rgb, uint8_t index, uint8_t step);

	static void Set(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t rgb);

	static void SetBrightness(FastLedCRGB* rgb, uint8_t percentage_0, uint8_t percentage_1);
};
