#include <stdlib.h>

#include "SerialUtils.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "LedColor.h"
#include "MathUtils.h"
#include "AssertUtils.h"


/* Table for galaxy, each value shows the next step. There is a slow speed, starting at 1 (next step is 5)
 * and a fast speed, starting at 3 (next step is 7). When at highest brightness, the values (steps) fade 
 * out with values +1 compared to fade in. All values which do not follow the slow/fast route have numbers
 * to continue via the fast fade down route. */

/* static */ const uint8_t LedColor::GALAXY_SLOW_SPEED_START_STEP = 1;
/* static */ const uint8_t LedColor::GALAXY_FAST_SPEED_START_STEP = 3;

/* static */ const PROGMEM uint8_t LedColor::GALAXY_STEPS[] = 
{
	// --0  --1  --2  --3  --4  --5  --6  --7  --8  --9
	     0,   5,   0,   7,   0,   9,   2,  17,   4,  14, // 000-009
		 6, 196,   4,   4,  20,  10,   8,  35,   8,   8, // 010-019
		30,  15,   8,   8,   8,   8,   8,   8,   8,   8, // 020-029
		40,  21,   8,   8,   8,  55,  18,  18,  18,  18, // 030-039
		50,  31,  18,  18,  18,  18,  18,  18,  18,  18, // 040-049
		60,  41,  18,  18,  18,  75,  36,  36,  36,  36, // 050-059
		70,  51,  36,  36,  36,  36,  36,  36,  36,  36, // 060-069
		80,  61,  36,  36,  36,  95,  56,  56,  56,  56, // 070-079
		90,  71,  56,  56,  56,  56,  56,  56,  56,  56, // 080-089
	   100,  81,  56,  56,  56, 115,  76,  76,  76,  76, // 090-099
	   110,  91,  76,  76,  76,  76,  76,  76,  76,  76, // 100-009
	   120, 101,  76,  76,  76, 135,  96,  96,  96,  96, // 110-019
	   130, 111,  96,  96,  96,  96,  96,  96,  96,  96, // 120-029
	   140, 121,  96,  96,  96, 155, 116, 116, 116, 116, // 130-039
	   150, 131, 116, 116, 116, 116, 116, 116, 116, 116, // 140-049
	   160, 141, 116, 116, 116, 175, 136, 136, 136, 136, // 150-059
	   170, 151, 136, 136, 136, 136, 136, 136, 136, 136, // 160-069
	   180, 161, 136, 136, 136, 195, 156, 156, 156, 156, // 170-079
	   190, 171, 156, 156, 156, 156, 156, 156, 156, 156, // 180-089
	   200, 181, 156, 156, 156, 215, 176, 176, 176, 176, // 190-099
	   210, 191, 176, 176, 176, 176, 176, 176, 176, 176, // 200-009
	   220, 201, 176, 176, 176, 235, 196, 196, 196, 196, // 210-019
	   230, 211, 196, 196, 196, 196, 196, 196, 196, 196, // 220-029
	   240, 221, 196, 196, 196, 252, 216, 216, 216, 216, // 230-039
	   250, 231, 216, 216, 216, 216, 216, 216, 216, 216, // 240-049
	   254, 241, 253, 236, 255, 251                      // 250-059
};

/* static */ bool LedColor::IsOff(uint8_t* red, uint8_t* green, uint8_t* blue)
{
	return ((*red == 0) && (*green == 0) && (*blue == 0));
}


// https://www.w3schools.com/colors/colors_hex.asp
/* static */ void LedColor::SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, LedColor::EColor color, uint32_t step)
{
	switch (color)
	{
		case LedColor::EColor::BLACK: SetRgb(red, green, blue, 0x000000); break;
		case LedColor::EColor::NAVY: SetRgb(red, green, blue, 0x000080); break;
		case LedColor::EColor::DARKBLUE: SetRgb(red, green, blue, 0x00008B); break;
		case LedColor::EColor::MEDIUMBLUE: SetRgb(red, green, blue, 0x0000CD); break;
		case LedColor::EColor::BLUE: SetRgb(red, green, blue, 0x0000FF); break;
		case LedColor::EColor::DARKGREEN: SetRgb(red, green, blue, 0x006400); break;
		case LedColor::EColor::GREEN: SetRgb(red, green, blue, 0x008000); break;
		case LedColor::EColor::TEAL: SetRgb(red, green, blue, 0x008080); break;
		case LedColor::EColor::DARKCYAN: SetRgb(red, green, blue, 0x008B8B); break;
		case LedColor::EColor::DEEPSKYBLUE: SetRgb(red, green, blue, 0x00BFFF); break;
		case LedColor::EColor::DARKTURQUOISE: SetRgb(red, green, blue, 0x00CED1); break;
		case LedColor::EColor::MEDIUMSPRINGGREEN: SetRgb(red, green, blue, 0x00FA9A); break;
		case LedColor::EColor::LIME: SetRgb(red, green, blue, 0x00FF00); break;
		case LedColor::EColor::SPRINGGREEN: SetRgb(red, green, blue, 0x00FF7F); break;
		case LedColor::EColor::AQUA: SetRgb(red, green, blue, 0x00FFFF); break;
		case LedColor::EColor::CYAN: SetRgb(red, green, blue, 0x00FFFF); break;
		case LedColor::EColor::MIDNIGHTBLUE: SetRgb(red, green, blue, 0x191970); break;
		case LedColor::EColor::DODGERBLUE: SetRgb(red, green, blue, 0x1E90FF); break;
		case LedColor::EColor::LIGHTSEAGREEN: SetRgb(red, green, blue, 0x20B2AA); break;
		case LedColor::EColor::FORESTGREEN: SetRgb(red, green, blue, 0x228B22); break;
		case LedColor::EColor::SEAGREEN: SetRgb(red, green, blue, 0x2E8B57); break;
		case LedColor::EColor::DARKSLATEGREY: SetRgb(red, green, blue, 0x2F4F4F); break;
		case LedColor::EColor::LIMEGREEN: SetRgb(red, green, blue, 0x32CD32); break;
		case LedColor::EColor::MEDIUMSEAGREEN: SetRgb(red, green, blue, 0x3CB371); break;
		case LedColor::EColor::TURQUOISE: SetRgb(red, green, blue, 0x40E0D0); break;
		case LedColor::EColor::ROYALBLUE: SetRgb(red, green, blue, 0x4169E1); break;
		case LedColor::EColor::STEELBLUE: SetRgb(red, green, blue, 0x4682B4); break;
		case LedColor::EColor::DARKSLATEBLUE: SetRgb(red, green, blue, 0x483D8B); break;
		case LedColor::EColor::MEDIUMTURQUOISE: SetRgb(red, green, blue, 0x48D1CC); break;
		case LedColor::EColor::INDIGO: SetRgb(red, green, blue, 0x4B0082); break;
		case LedColor::EColor::DARKOLIVEGREEN: SetRgb(red, green, blue, 0x556B2F); break;
		case LedColor::EColor::CADETBLUE: SetRgb(red, green, blue, 0x5F9EA0); break;
		case LedColor::EColor::CORNFLOWERBLUE: SetRgb(red, green, blue, 0x6495ED); break;
		case LedColor::EColor::REBECCAPURPLE: SetRgb(red, green, blue, 0x663399); break;
		case LedColor::EColor::MEDIUMAQUAMARINE: SetRgb(red, green, blue, 0x66CDAA); break;
		case LedColor::EColor::DIMGREY: SetRgb(red, green, blue, 0x696969); break;
		case LedColor::EColor::SLATEBLUE: SetRgb(red, green, blue, 0x6A5ACD); break;
		case LedColor::EColor::OLIVEDRAB: SetRgb(red, green, blue, 0x6B8E23); break;
		case LedColor::EColor::SLATEGREY: SetRgb(red, green, blue, 0x708090); break;
		case LedColor::EColor::LIGHTSLATEGREY: SetRgb(red, green, blue, 0x778899); break;
		case LedColor::EColor::MEDIUMSLATEBLUE: SetRgb(red, green, blue, 0x7B68EE); break;
		case LedColor::EColor::LAWNGREEN: SetRgb(red, green, blue, 0x7CFC00); break;
		case LedColor::EColor::CHARTREUSE: SetRgb(red, green, blue, 0x7FFF00); break;
		case LedColor::EColor::AQUAMARINE: SetRgb(red, green, blue, 0x7FFFD4); break;
		case LedColor::EColor::MAROON: SetRgb(red, green, blue, 0x800000); break;
		case LedColor::EColor::PURPLE: SetRgb(red, green, blue, 0x800080); break;
		case LedColor::EColor::OLIVE: SetRgb(red, green, blue, 0x808000); break;
		case LedColor::EColor::GREY: SetRgb(red, green, blue, 0x808080); break;
		case LedColor::EColor::SKYBLUE: SetRgb(red, green, blue, 0x87CEEB); break;
		case LedColor::EColor::LIGHTSKYBLUE: SetRgb(red, green, blue, 0x87CEFA); break;
		case LedColor::EColor::BLUEVIOLET: SetRgb(red, green, blue, 0x8A2BE2); break;
		case LedColor::EColor::DARKRED: SetRgb(red, green, blue, 0x8B0000); break;
		case LedColor::EColor::DARKMAGENTA: SetRgb(red, green, blue, 0x8B008B); break;
		case LedColor::EColor::SADDLEBROWN: SetRgb(red, green, blue, 0x8B4513); break;
		case LedColor::EColor::DARKSEAGREEN: SetRgb(red, green, blue, 0x8FBC8F); break;
		case LedColor::EColor::LIGHTGREEN: SetRgb(red, green, blue, 0x90EE90); break;
		case LedColor::EColor::MEDIUMPURPLE: SetRgb(red, green, blue, 0x9370DB); break;
		case LedColor::EColor::DARKVIOLET: SetRgb(red, green, blue, 0x9400D3); break;
		case LedColor::EColor::PALEGREEN: SetRgb(red, green, blue, 0x98FB98); break;
		case LedColor::EColor::DARKORCHID: SetRgb(red, green, blue, 0x9932CC); break;
		case LedColor::EColor::YELLOWGREEN: SetRgb(red, green, blue, 0x9ACD32); break;
		case LedColor::EColor::SIENNA: SetRgb(red, green, blue, 0xA0522D); break;
		case LedColor::EColor::BROWN: SetRgb(red, green, blue, 0xA52A2A); break;
		case LedColor::EColor::DARKGREY: SetRgb(red, green, blue, 0xA9A9A9); break;
		case LedColor::EColor::LIGHTBLUE: SetRgb(red, green, blue, 0xADD8E6); break;
		case LedColor::EColor::GREENYELLOW: SetRgb(red, green, blue, 0xADFF2F); break;
		case LedColor::EColor::PALETURQUOISE: SetRgb(red, green, blue, 0xAFEEEE); break;
		case LedColor::EColor::LIGHTSTEELBLUE: SetRgb(red, green, blue, 0xB0C4DE); break;
		case LedColor::EColor::POWDERBLUE: SetRgb(red, green, blue, 0xB0E0E6); break;
		case LedColor::EColor::FIREBRICK: SetRgb(red, green, blue, 0xB22222); break;
		case LedColor::EColor::DARKGOLDENROD: SetRgb(red, green, blue, 0xB8860B); break;
		case LedColor::EColor::MEDIUMORCHID: SetRgb(red, green, blue, 0xBA55D3); break;
		case LedColor::EColor::ROSYBROWN: SetRgb(red, green, blue, 0xBC8F8F); break;
		case LedColor::EColor::DARKKHAKI: SetRgb(red, green, blue, 0xBDB76B); break;
		case LedColor::EColor::SILVER: SetRgb(red, green, blue, 0xC0C0C0); break;
		case LedColor::EColor::MEDIUMVIOLETRED: SetRgb(red, green, blue, 0xC71585); break;
		case LedColor::EColor::INDIANRED: SetRgb(red, green, blue, 0xCD5C5C); break;
		case LedColor::EColor::PERU: SetRgb(red, green, blue, 0xCD853F); break;
		case LedColor::EColor::CHOCOLATE: SetRgb(red, green, blue, 0xD2691E); break;
		case LedColor::EColor::TAN: SetRgb(red, green, blue, 0xD2B48C); break;
		case LedColor::EColor::LIGHTGREY: SetRgb(red, green, blue, 0xD3D3D3); break;
		case LedColor::EColor::THISTLE: SetRgb(red, green, blue, 0xD8BFD8); break;
		case LedColor::EColor::ORCHID: SetRgb(red, green, blue, 0xDA70D6); break;
		case LedColor::EColor::GOLDENROD: SetRgb(red, green, blue, 0xDAA520); break;
		case LedColor::EColor::PALEVIOLETRED: SetRgb(red, green, blue, 0xDB7093); break;
		case LedColor::EColor::CRIMSON: SetRgb(red, green, blue, 0xDC143C); break;
		case LedColor::EColor::GAINSBORO: SetRgb(red, green, blue, 0xDCDCDC); break;
		case LedColor::EColor::PLUM: SetRgb(red, green, blue, 0xDDA0DD); break;
		case LedColor::EColor::BURLYWOOD: SetRgb(red, green, blue, 0xDEB887); break;
		case LedColor::EColor::LIGHTCYAN: SetRgb(red, green, blue, 0xE0FFFF); break;
		case LedColor::EColor::LAVENDER: SetRgb(red, green, blue, 0xE6E6FA); break;
		case LedColor::EColor::DARKSALMON: SetRgb(red, green, blue, 0xE9967A); break;
		case LedColor::EColor::VIOLET: SetRgb(red, green, blue, 0xEE82EE); break;
		case LedColor::EColor::PALEGOLDENROD: SetRgb(red, green, blue, 0xEEE8AA); break;
		case LedColor::EColor::LIGHTCORAL: SetRgb(red, green, blue, 0xF08080); break;
		case LedColor::EColor::KHAKI: SetRgb(red, green, blue, 0xF0E68C); break;
		case LedColor::EColor::ALICEBLUE: SetRgb(red, green, blue, 0xF0F8FF); break;
		case LedColor::EColor::HONEYDEW: SetRgb(red, green, blue, 0xF0FFF0); break;
		case LedColor::EColor::AZURE: SetRgb(red, green, blue, 0xF0FFFF); break;
		case LedColor::EColor::SANDYBROWN: SetRgb(red, green, blue, 0xF4A460); break;
		case LedColor::EColor::WHEAT: SetRgb(red, green, blue, 0xF5DEB3); break;
		case LedColor::EColor::BEIGE: SetRgb(red, green, blue, 0xF5F5DC); break;
		case LedColor::EColor::WHITESMOKE: SetRgb(red, green, blue, 0xF5F5F5); break;
		case LedColor::EColor::MINTCREAM: SetRgb(red, green, blue, 0xF5FFFA); break;
		case LedColor::EColor::GHOSTWHITE: SetRgb(red, green, blue, 0xF8F8FF); break;
		case LedColor::EColor::SALMON: SetRgb(red, green, blue, 0xFA8072); break;
		case LedColor::EColor::ANTIQUEWHITE: SetRgb(red, green, blue, 0xFAEBD7); break;
		case LedColor::EColor::LINEN: SetRgb(red, green, blue, 0xFAF0E6); break;
		case LedColor::EColor::LIGHTGOLDENRODYELLOW: SetRgb(red, green, blue, 0xFAFAD2); break;
		case LedColor::EColor::OLDLACE: SetRgb(red, green, blue, 0xFDF5E6); break;
		case LedColor::EColor::RED: SetRgb(red, green, blue, 0xFF0000); break;
		case LedColor::EColor::FUCHSIA: SetRgb(red, green, blue, 0xFF00FF); break;
		case LedColor::EColor::MAGENTA: SetRgb(red, green, blue, 0xFF00FF); break;
		case LedColor::EColor::DEEPPINK: SetRgb(red, green, blue, 0xFF1493); break;
		case LedColor::EColor::ORANGERED: SetRgb(red, green, blue, 0xFF4500); break;
		case LedColor::EColor::TOMATO: SetRgb(red, green, blue, 0xFF6347); break;
		case LedColor::EColor::HOTPINK: SetRgb(red, green, blue, 0xFF69B4); break;
		case LedColor::EColor::CORAL: SetRgb(red, green, blue, 0xFF7F50); break;
		case LedColor::EColor::DARKORANGE: SetRgb(red, green, blue, 0xFF8C00); break;
		case LedColor::EColor::LIGHTSALMON: SetRgb(red, green, blue, 0xFFA07A); break;
		case LedColor::EColor::ORANGE: SetRgb(red, green, blue, 0xFFA500); break;
		case LedColor::EColor::LIGHTPINK: SetRgb(red, green, blue, 0xFFB6C1); break;
		case LedColor::EColor::PINK: SetRgb(red, green, blue, 0xFFC0CB); break;
		case LedColor::EColor::GOLD: SetRgb(red, green, blue, 0xFFD700); break;
		case LedColor::EColor::PEACHPUFF: SetRgb(red, green, blue, 0xFFDAB9); break;
		case LedColor::EColor::NAVAJOWHITE: SetRgb(red, green, blue, 0xFFDEAD); break;
		case LedColor::EColor::MOCCASIN: SetRgb(red, green, blue, 0xFFE4B5); break;
		case LedColor::EColor::BISQUE: SetRgb(red, green, blue, 0xFFE4C4); break;
		case LedColor::EColor::MISTYROSE: SetRgb(red, green, blue, 0xFFE4E1); break;
		case LedColor::EColor::BLANCHEDALMOND: SetRgb(red, green, blue, 0xFFEBCD); break;
		case LedColor::EColor::PAPAYAWHIP: SetRgb(red, green, blue, 0xFFEFD5); break;
		case LedColor::EColor::LAVENDERBLUSH: SetRgb(red, green, blue, 0xFFF0F5); break;
		case LedColor::EColor::SEASHELL: SetRgb(red, green, blue, 0xFFF5EE); break;
		case LedColor::EColor::CORNSILK: SetRgb(red, green, blue, 0xFFF8DC); break;
		case LedColor::EColor::LEMONCHIFFON: SetRgb(red, green, blue, 0xFFFACD); break;
		case LedColor::EColor::FLORALWHITE: SetRgb(red, green, blue, 0xFFFAF0); break;
		case LedColor::EColor::SNOW: SetRgb(red, green, blue, 0xFFFAFA); break;
		case LedColor::EColor::YELLOW: SetRgb(red, green, blue, 0xFFFF00); break;
		case LedColor::EColor::LIGHTYELLOW: SetRgb(red, green, blue, 0xFFFFE0); break;
		case LedColor::EColor::IVORY: SetRgb(red, green, blue, 0xFFFFF0); break;
		case LedColor::EColor::WHITE: SetRgb(red, green, blue, 0xFFFFFF); break;

		// Special colors
		case LedColor::EColor::RANDOM: SetRandom	(red, green, blue); break;
		case LedColor::EColor::RAINBOW: SetRainbow(red, green, blue, step); break;
		case LedColor::EColor::FIRE: SetFire   (red, green, blue, step); break;
		case LedColor::EColor::GALAXY: SetGalaxy (red, green, blue, step); break;
		default:
			AssertUtils::MyAssert(false);
	}
};


/* static */ void LedColor::SetRandom(uint8_t* red, uint8_t* green, uint8_t* blue)
{
	*red   = random(256);
	*green = random(256);
	*blue  = random(256);
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


/* static */ void LedColor::SetFire(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t step)
{
	*red   = random(127) + 127;
	*green = MIN(*red * 3/4, random(255));
	*blue  = 0;
}


/* static */ void LedColor::SetGalaxy(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t step)
{
	if (step % 10 == 0)
	{
		if (IsOff(red, green, blue))
		{
			CreateNewGalaxyStar(red, green, blue);
		}
		else
		{
			*blue = LedColor::GALAXY_STEPS[*blue];

			if (*red != 0)
			{
				*red = *green = *blue;
			}
		}
	}
}


/* static */ void LedColor::CreateNewGalaxyStar(uint8_t* red, uint8_t* green, uint8_t* blue)
{
	switch (random(1000))
	{
	case 0: // Slow white star
		*red = *green = *blue = GALAXY_SLOW_SPEED_START_STEP; 
		break;

	case 1: // Fast white star
		*red = *green = *blue = GALAXY_FAST_SPEED_START_STEP;
		break;

	case 2: // Slow blue star
		*red = *green = 0;
		*blue = GALAXY_SLOW_SPEED_START_STEP;
		break;

	case 3: // Fast blue star
		*red = *green = 0;
		*blue = GALAXY_FAST_SPEED_START_STEP;
		break;

	default:
		// No new star
		break;
	}
}


/* static */ void LedColor::SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t rgb)
{
	*red   = (rgb & 0xFF0000) >> 16;
	*green = (rgb & 0xFF00) >> 8;
	*blue  =  rgb & 0xFF;
}


/* static */ void LedColor::SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t redValue, uint8_t greenValue, uint8_t blueValue)
{
	*red   = redValue;
	*green = greenValue;
	*blue  = blueValue;
}


/* static */ uint8_t LedColor::SetBrightness(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t percentage_0, uint8_t percentage_1)
{
	*red       *= percentage_0 * percentage_1 / 255 / 255;
	*green     *= percentage_0 * percentage_1 / 255 / 255;
	*blue      *= percentage_0 * percentage_1 / 255 / 255;
	return 255 * percentage_0 * percentage_1 / 255 / 255;
}
