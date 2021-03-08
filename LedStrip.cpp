#include "MathUtils.h"
#include <stdlib.h>

#include "LedStrip.h"
#include "LedColor.h"
#include "Time.h"

#include "ClassNames.h"
#include HEADER_FILE(MIDI_CLASS)

LedStrip::LedStrip()
:
	_dataPin(0),
	_nrOfLeds(0),
	_data(NULL),
	_pattern(NULL)
{
}


LedStrip::~LedStrip()
{
}


void LedStrip::Initialize(uint8_t dataPin, uint8_t nrOfLeds, struct FastLedCRGB* data)
{
	_dataPin = dataPin;
	_nrOfLeds = nrOfLeds;
	_data = data;
}

uint8_t LedStrip::GetNrOfLeds()
{
	return _nrOfLeds;
}


void LedStrip::SetPattern(Pattern* pattern)
{
	_pattern = pattern;
	_pattern->Start();
}

struct FastLedCRGB* LedStrip::GetLed(uint8_t ledIndex)
{
	return &_data[ledIndex];
}

void LedStrip::Process(uint32_t counter)
{
	_pattern->Process(counter);
}


void LedStrip::SetAllLeds(LedColor::EColor color, uint8_t step)
{
	for (uint8_t ledIndex = 0; ledIndex < _nrOfLeds; ledIndex++)
	{
		FastLedCRGB& led = _data[ledIndex];
		LedColor::SetRgb(&led.red, &led.green, &led.blue, color, step);
	}
}


void LedStrip::SetAllLeds(uint32_t color)
{
	for (uint8_t ledIndex = 0; ledIndex < _nrOfLeds; ledIndex++)
	{
		FastLedCRGB& led = _data[ledIndex];
		LedColor::SetRgb(&led.red, &led.green, &led.blue, color);
	}
}


void LedStrip::SetAllLeds(uint8_t red, uint8_t green, uint8_t blue)
{
	for (uint8_t ledIndex = 0; ledIndex < _nrOfLeds; ledIndex++)
	{
		FastLedCRGB& led = _data[ledIndex];
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
