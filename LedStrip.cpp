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
	_pattern(EPattern::Off),
	_value_0(0),
	_value_1(0),
	_parameter_0(0),
	_parameter_1(0),
	_parameter_2(0),
	_parameter_3(0),
	_parameter_4(0),
	_parameter_5(0),
	_parameter_6(0),
	_parameter_7(0)
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

void LedStrip::SetPattern(EPattern pattern,
	uint8_t parameter_0 /* = 0 */, uint8_t parameter_1 /* = 0 */, uint8_t parameter_2 /* = 0 */, uint8_t parameter_3 /* = 0 */, uint8_t parameter_4 /* = 0 */, 
	uint8_t parameter_5 /* = 0 */, uint8_t parameter_6 /* = 0 */, uint8_t parameter_7 /* = 0 */, uint8_t parameter_8 /* = 0 */, uint8_t parameter_9 /* = 0 */)
{
	_pattern = pattern;
	_parameter_0 = parameter_0;
	_parameter_1 = parameter_1;
	_parameter_2 = parameter_2;
	_parameter_3 = parameter_3;
	_parameter_4 = parameter_4;
	_parameter_5 = parameter_5;
	_parameter_6 = parameter_6;
	_parameter_7 = parameter_7;
	_parameter_8 = parameter_8;
	_parameter_9 = parameter_9;

	_value_0 = 0; // Down/Up
	_value_1 = 1; // Current LED

	StartPattern();
}


void LedStrip::StartPattern()
{
	switch (_pattern)
	{
	case EPattern::Off:					// Fall Through
		break;

	case EPattern::KnightRider:			// Fall Through
		break;

	case EPattern::MidiNoteOnOff:
		SetAllLeds((LedColor::EColor) _parameter_0, 0); // P0: Background color
		break;

	default:
		exit(0);
	}
}


void LedStrip::Process(uint32_t counter)
{
	// LEDs
	switch (_pattern)
	{
	case EPattern::Off:
		break;

	case EPattern::KnightRider:
		ProcessKnightRider(counter);
		break;

	case EPattern::MidiNoteOnOff:
		ProcessMidiNoteOnOff(counter);
		break;

	default:
		exit(0);
	}
}


void LedStrip::ProcessKnightRider(uint32_t counter)
{
	// P0: RGB, P3: Speed, P4: Width
	// V0: Direction V1: Current led

	if (counter % _parameter_3 == 0)
	{
		_value_1 = (_value_0 == 0) ? _value_1 - 1 : _value_1 + 1;
		_value_0 = ((_value_1 == 0) || (_value_1 == _nrOfLeds - 1)) ? ~_value_0 : _value_0;
	}

	for (int led = 0; led < _nrOfLeds; led++)
	{
		struct FastLedCRGB *rgb = &(_data[led]);
		uint8_t ratio = MathUtils::Max(0, _parameter_4 - MathUtils::Abs(led - _value_1));

		rgb->red = (_parameter_0 * ratio) / _parameter_4;
		rgb->blue = (_parameter_1 * ratio) / _parameter_4;
		rgb->green = (_parameter_2 * ratio) / _parameter_4;
	}
}


void LedStrip::ProcessMidiNoteOnOff(uint32_t counter)
{
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
