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
	_pattern(NULL),
	_midiKeyboard(NULL)
{
}


LedStrip::~LedStrip()
{
}


void LedStrip::Initialize(MidiKeyboard* midiKeyboard, uint8_t dataPin, uint8_t nrOfLeds, struct FastLedCRGB* data)
{
	_midiKeyboard = midiKeyboard;
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


void LedStrip::ProcessMidiNoteOnOff(uint32_t counter)
{
	/*
	for (uint8_t key = 0; key < _midiKeyboard->GetNrOfKeys(); key++)
	{
		struct FastLedCRGB* rgb = &_data[key]; // TODO: Key should be in range 0..59 (led strips)

		if (_midiKeyboard->IsNew(key))
		{
			if (_midiKeyboard->IsPressed(key))
			{
				Serial.println("Key pressed");
				Serial.println(key);
				LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, (LedColor::EColor) _parameter_2, 0); // P2: Foreground color
				_value_0 = rgb->red;
				_value_1 = rgb->green;
				_value_2 = rgb->blue;
				_value_3 = LedColor::SetBrightness(&rgb->red, &rgb->green, &rgb->blue, _parameter_6, ((_midiKeyboard->GetVelocity(key) & 0x7F) * 2 + 1)); // P6 = Note On Velocity)
			}
			else
			{
				// Do nothing
			}
		} 
		else if ((counter % Time::GetTimeInMilliSeconds((Time::ETime) _parameter_4) == 0) && _midiKeyboard->IsPressed(key))
		{
			//LedColor::Decrease(&rgb->red, &rgb->green, &rgb->blue);
			uint16_t timeAgo = _midiKeyboard->TimeAgo(key);
			//_value_3 = LedColor::SetBrightness(&rgb->red, &rgb->green, &rgb->blue, _value_3, MathUtils::Max(256, 256 * timeAgo / Time::GetTimeInMilliSeconds((Time::ETime) _parameter_4)));
		}
		else if ((counter % Time::GetTimeInMilliSeconds((Time::ETime) _parameter_5) == 0) && !_midiKeyboard->IsPressed(key))
		{
			uint16_t timeAgo = _midiKeyboard->TimeAgo(key);
			//_value_3 = LedColor::SetBrightness(&rgb->red, &rgb->green, &rgb->blue, _value_3, MathUtils::Max(256, 256 * timeAgo / Time::GetTimeInMilliSeconds((Time::ETime) _parameter_4)));
		}
	}
	*/
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
