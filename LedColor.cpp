#include <stdlib.h>
#include "SerialUtils.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "SynthLedStripsTypes.h"
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


// https://www.rapidtables.com/web/color/RGB_Color.html
/* static */ void LedColor::SetRgb(uint8_t* red, uint8_t* green, uint8_t* blue, LedColor::EColor color, uint32_t step)
{
	switch (color)
	{
	case LedColor::EColor::Black		: SetRgb	(red, green, blue, 0x000000); break;
	case LedColor::EColor::White		: SetRgb	(red, green, blue, 0xFFFFFF); break;
	case LedColor::EColor::Red			: SetRgb	(red, green, blue, 0xFF0000); break;
	case LedColor::EColor::Lime			: SetRgb	(red, green, blue, 0x00FF00); break;
	case LedColor::EColor::Blue			: SetRgb	(red, green, blue, 0x0000FF); break;
	case LedColor::EColor::Yellow		: SetRgb	(red, green, blue, 0xFFFF00); break;
	case LedColor::EColor::Cyan			: SetRgb	(red, green, blue, 0x00FFFF); break;
	case LedColor::EColor::Magenta		: SetRgb	(red, green, blue, 0xFF00FF); break;
	case LedColor::EColor::Silver		: SetRgb	(red, green, blue, 0xC0C0C0); break;
	case LedColor::EColor::Gray			: SetRgb	(red, green, blue, 0x808080); break;
	case LedColor::EColor::Random		: SetRandom	(red, green, blue);			  break;
	case LedColor::EColor::Rainbow      : SetRainbow(red, green, blue, step);     break;
	case LedColor::EColor::Fire         : SetFire   (red, green, blue, step);	  break;
	case LedColor::EColor::Galaxy       : SetGalaxy (red, green, blue, step);	  break;
	default:
		AssertUtils::MyAssert(false);
	}
}


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
