#include <stdlib.h>

#include "SynthLedStripsTypes.h"

#include "Color.h"

/* static */ void Color::SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t index, uint8_t step)
{
	switch ((EColor) index)
	{
	case EColor::Black			: Set(red, green, blue, 0x000000); break;
	case EColor::White			: Set(red, green, blue, 0xFFFFFF); break;
	case EColor::Red			: Set(red, green, blue, 0xFF0000); break;
	case EColor::Lime			: Set(red, green, blue, 0x00FF00); break;
	case EColor::Blue			: Set(red, green, blue, 0x0000FF); break;
	case EColor::Yellow			: Set(red, green, blue, 0xFFFF00); break;
	case EColor::Cyan			: Set(red, green, blue, 0x00FFFF); break;
	case EColor::Magenta		: Set(red, green, blue, 0xFF00FF); break;
	case EColor::Silver			: Set(red, green, blue, 0xC0C0C0); break;
	case EColor::Gray			: Set(red, green, blue, 0x808080); break;
		// TODO

	default:
		exit(0);
	}
}


/* static */ void Color::SetRgb(FastLedCRGB* rgb, uint8_t index, uint8_t step)
{
	SetRgb(&(rgb->red), &(rgb->green), &(rgb->blue), index, step);
}


/* static */ void Color::Set(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t rgb)
{
	*red = rgb & 0xFF0000 >> 16;
	*green = rgb & 0xFF00 >> 8;
	*blue = rgb & 0xFF;
}


/* static */ void Color::SetBrightness(FastLedCRGB* rgb, uint8_t percentage_0, uint8_t percentage_1)
{
	rgb->red   *= percentage_0 * percentage_1 / 255 / 255;
	rgb->green *= percentage_0 * percentage_1 / 255 / 255;
	rgb->blue  *= percentage_0 * percentage_1 / 255 / 255;
}