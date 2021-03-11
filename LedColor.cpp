#include <stdlib.h>

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

#include "SynthLedStripsTypes.h"
#include "LedColor.h"
#include "MathUtils.h"


// https://www.rapidtables.com/web/color/RGB_Color.html
/* static */ void LedColor::SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, LedColor::EColor color, uint32_t step)
{
	switch (color)
	{
	case LedColor::EColor::Black		: SetRgb(red, green, blue, 0x000000); break;
	case LedColor::EColor::White		: SetRgb(red, green, blue, 0xFFFFFF); break;
	case LedColor::EColor::Red			: SetRgb(red, green, blue, 0xFF0000); break;
	case LedColor::EColor::Lime			: SetRgb(red, green, blue, 0x00FF00); break;
	case LedColor::EColor::Blue			: SetRgb(red, green, blue, 0x0000FF); break;
	case LedColor::EColor::Yellow		: SetRgb(red, green, blue, 0xFFFF00); break;
	case LedColor::EColor::Cyan			: SetRgb(red, green, blue, 0x00FFFF); break;
	case LedColor::EColor::Magenta		: SetRgb(red, green, blue, 0xFF00FF); break;
	case LedColor::EColor::Silver		: SetRgb(red, green, blue, 0xC0C0C0); break;
	case LedColor::EColor::Gray			: SetRgb(red, green, blue, 0x808080); break;
	case LedColor::EColor::Random		: SetRandom(red, green, blue); break;
	case LedColor::EColor::Rainbow      : SetRainbow(red, green, blue, step); break;

	default:
		exit(0);
	}
}


/* static */ void LedColor::SetRandom(uint8_t* red, uint8_t* green, uint8_t* blue)
{
	*red = random(256);
	*green = random(256);
	*blue = random(256);
}

// https://www.instructables.com/How-to-Make-Proper-Rainbow-and-Random-Colors-With-/
// Regular HSV
/* static */ void LedColor::SetRainbow(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t step)
{
	uint16_t angle = step % 360;
	if (angle < 60) 
	{
		*red = 255; 
		*green = map(angle, 0, 60, 0, 255); 
		*blue = 0;
	}
	else if (angle < 120)
	{
		*red = map(angle, 60, 120, 255, 0);
		*green = 255;
		*blue = 0;
	}
	else if (angle < 180)
	{
		*red = 0;
		*green = 255;
		*blue = map(angle, 120, 180, 0, 255);
	}
	else if (angle < 240)
	{
		*red = 0;
		*green = map(angle, 180, 240, 255, 0);
		*blue = 255;
	}
	else if (angle < 300)
	{
		*red = map(angle, 240, 300, 0, 255);
		*green = 0;
		*blue = 255;
	}
	else
	{
		*red = 255;
		*green = 0;
		*blue = map(angle, 300, 360, 255, 0);
	}
}


/* static */ void LedColor::SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t rgb)
{
	*red = (rgb & 0xFF0000) >> 16;
	*green = (rgb & 0xFF00) >> 8;
	*blue = rgb & 0xFF;
}


/* static */ void LedColor::SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t redValue, uint8_t greenValue, uint8_t blueValue)
{
	*red = redValue;
	*green = greenValue;
	*blue = blueValue;
}


/* static */ uint8_t LedColor::SetBrightness(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t percentage_0, uint8_t percentage_1)
{
	*red   *= percentage_0 * percentage_1 / 255 / 255;
	*green *= percentage_0 * percentage_1 / 255 / 255;
	*blue  *= percentage_0 * percentage_1 / 255 / 255;
	return 255 * percentage_0 * percentage_1 / 255 / 255;
}
