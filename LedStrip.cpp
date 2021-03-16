#include "MathUtils.h"
#include <stdlib.h>

#include "LedStrip.h"
#include "LedColor.h"
#include "Time.h"

#include "ClassNames.h"
#include HEADER_FILE(MIDI_CLASS)
#include HEADER_FILE(FAST_LED_CLASS)


LedStrip::LedStrip()
:
	_nrOfLeds(0),
	_leds(NULL)
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
		exit(0);
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
