#pragma once

#include <stdlib.h>

constexpr auto COLOR_GALAXY_SLOW_STAR_LENGTH = 11;
constexpr auto COLOR_GALAXY_FAST_STAR_LENGTH = 6;

class LedColor
{
public:
	enum class EColor: uint8_t
	{
		Black, White, Red, Lime, Blue, Yellow, Cyan, Magenta, Silver, Gray,
		Random = 240, Rainbow, Fire, Galaxy
	};

	static bool IsOff					(uint8_t* red, uint8_t* green, uint8_t* blue);
	static void SetRgb					(uint8_t* red, uint8_t* green, uint8_t* blue, LedColor::EColor color, uint32_t step);

	static void SetRandom				(uint8_t* red, uint8_t* green, uint8_t* blue);
	static void SetRainbow				(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t step);
	
	static void SetFire					(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t step);
	
	static void SetGalaxy				(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t step);
	static void CreateNewGalaxyStar		(uint8_t* red, uint8_t* green, uint8_t* blue);

	static void SetRgb					(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t rgb);

	static void SetRgb					(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t redValue, uint8_t greenValue, uint8_t blueValue);

	static uint8_t SetBrightness		(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t percentage_0, uint8_t percentage_1);

private:
	static const uint8_t GALAXY_SLOW_SPEED_START_STEP;
	static const uint8_t GALAXY_FAST_SPEED_START_STEP;
	static const uint8_t GALAXY_STEPS[256];
};
