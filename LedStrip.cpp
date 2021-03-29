#include "MathUtils.h"
#include <stdlib.h>
#include "LedStrip.h"
#include "LedColor.h"
#include "Time.h"
#include "ClassNames.h"
#include "AssertUtils.h"
#include HEADER_FILE(MIDI_CLASS)
#include HEADER_FILE(FAST_LED_CLASS)

/* static */ const uint8_t LedStrip::MAX_CURRENT_IN_MILLI_AMP_PER_SUB_LED =   20; // mA
/* static */ const uint8_t LedStrip::SUB_LEDS_PER_LED                     =    3; // R, G, B


LedStrip::LedStrip()
:
	_nrOfLeds(0),
	_leds(nullptr)
{
}


LedStrip::~LedStrip()
{
}


void LedStrip::Initialize( uint8_t nrOfLeds)
{
	_nrOfLeds = nrOfLeds;
	_leds = new FastLedCRGB[nrOfLeds];
}


uint8_t LedStrip::GetNrOfLeds()
{
	return _nrOfLeds;
}


struct FastLedCRGB* LedStrip::GetLeds()
{
	return _leds;
}


struct FastLedCRGB* LedStrip::GetLed(uint8_t ledIndex)
{
#ifdef _DEBUG
	if (ledIndex >= _nrOfLeds)
	{
		AssertUtils::MyAssert(false);
	}
#endif
	return &_leds[ledIndex];
}


void LedStrip::SetAllLeds(LedColor::EColor color, uint8_t step)
{
	for (uint8_t ledIndex = 0; ledIndex < _nrOfLeds; ledIndex++)
	{
		FastLedCRGB& led = _leds[ledIndex];
		LedColor::SetRgb(&led.red, &led.green, &led.blue, color, step);
	}
}


void LedStrip::SetAllLeds(uint32_t color)
{
	for (uint8_t ledIndex = 0; ledIndex < _nrOfLeds; ledIndex++)
	{
		FastLedCRGB& led = _leds[ledIndex];
		LedColor::SetRgb(&led.red, &led.green, &led.blue, color);
	}
}


void LedStrip::SetAllLeds(uint8_t red, uint8_t green, uint8_t blue)
{
	for (uint8_t ledIndex = 0; ledIndex < _nrOfLeds; ledIndex++)
	{
		FastLedCRGB& led = _leds[ledIndex];
		LedColor::SetRgb(&led.red, &led.green, &led.blue, red, green, blue);
	}
}


void LedStrip::SetLed(struct FastLedCRGB* led, LedColor::EColor color, uint8_t step)
{
	LedColor::SetRgb(&led->red, &led->green, &led->blue, color, step);
}


void LedStrip::SetLed(struct FastLedCRGB* led, uint32_t color)
{
	LedColor::SetRgb(&led->red, &led->green, &led->blue, color);
}


void LedStrip::SetLed(struct FastLedCRGB* led, uint8_t red, uint8_t green, uint8_t blue)
{
	LedColor::SetRgb(&led->red, &led->green, &led->blue, red, green, blue);
}


uint16_t LedStrip::CalculateCurrentInMilliAmp()
{
	uint32_t brightness = 0;
	for (uint8_t ledIndex = 0; ledIndex < _nrOfLeds; ledIndex++)
	{
		FastLedCRGB& led = _leds[ledIndex];
		brightness += led.red + led.green + led.blue;
	}

	return brightness * MAX_CURRENT_IN_MILLI_AMP_PER_SUB_LED / 255;
}



void LedStrip::ReduceCurrent(uint8_t percentage)
{
	if (percentage >= 100)
	{
		return;
	}

	for (uint8_t ledIndex = 0; ledIndex < _nrOfLeds; ledIndex++)
	{
		FastLedCRGB& led = _leds[ledIndex];
		led.red   = led.red   * percentage / 100;
		led.green = led.green * percentage / 100;
		led.blue  = led.blue  * percentage / 100;
	}
}
