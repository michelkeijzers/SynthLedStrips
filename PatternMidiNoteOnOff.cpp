#include "PatternMidiNoteOnOff.h"
#include "MidiKeyboard.h"
#include "Time.h"
#include "MathUtils.h"


PatternMidiNoteOnOff::PatternMidiNoteOnOff(LedStrip& ledStrip, MidiKeyboard& midiKeyboard)
	: Pattern(ledStrip),
	_midiKeyboard(midiKeyboard),
	_foregroundColor(LedColor::EColor::Black),
	_backgroundColor(LedColor::EColor::Black)
{
}


PatternMidiNoteOnOff::~PatternMidiNoteOnOff()
{
}


void PatternMidiNoteOnOff::SetBackgroundColor(LedColor::EColor color)
{
	_backgroundColor = color;
}


void PatternMidiNoteOnOff::SetForegroundColor(LedColor::EColor color)
{
	_foregroundColor = color;
}


void PatternMidiNoteOnOff::SetFadeTimeNoteOn(Time::ETime fadeTimeNoteOn)
{
	_fadeTimeNoteOn = fadeTimeNoteOn;
}


void PatternMidiNoteOnOff::SetFadeTimeNoteOff(Time::ETime fadeTimeNoteOff)
{
	_fadeTimeNoteOff = fadeTimeNoteOff;
}


void PatternMidiNoteOnOff::SetNoteOnVelocityIntensity(uint8_t noteOnVelocityIntensity)
{
	_noteOnVelocityIntensity = noteOnVelocityIntensity;
}


/* override */ void PatternMidiNoteOnOff::Start()
{
	_ledStrip.SetAllLeds(_backgroundColor, 0);
}


/* override */ void PatternMidiNoteOnOff::Process(uint32_t counter)
{
	for (uint8_t key = 0; key < _midiKeyboard.GetNrOfKeys(); key++)
	{
		struct FastLedCRGB* rgb = _ledStrip.GetLed(key); // TODO: Key should be in range 0..59 (led strips)

		if (_midiKeyboard.IsNew(key))
		{
			if (_midiKeyboard.IsPressed(key))
			{
				Serial.print("Key pressed: ");
				Serial.println(key);
				LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, _foregroundColor, 0); // P2: Foreground color
				LedColor::SetBrightness(&rgb->red, &rgb->green, &rgb->blue, _noteOnVelocityIntensity, _midiKeyboard.GetVelocity(key) * 2 + 1);
			}
			else
			{
				// Do nothing
			}
		} 
		else if (_midiKeyboard.IsPressed(key)) // if ((counter % Time::GetTimeInMilliSeconds((Time::ETime) _fadeTimeNoteOn) == 0)
		{
			struct FastLedCRGB foregroundColor{};
			uint16_t timeAgo = _midiKeyboard.TimeAgo(key);
			Serial.println("Time ago: ");
			Serial.println(timeAgo);
			uint32_t fadeTimeNoteOn = Time::GetTimeInMilliSeconds(_fadeTimeNoteOn);
			LedColor::SetRgb(&foregroundColor.red, &foregroundColor.green, &foregroundColor.blue, _foregroundColor, 0);
			uint8_t red = MathUtils::Max(0, foregroundColor.red * (fadeTimeNoteOn - timeAgo)) / fadeTimeNoteOn;
			uint8_t green = MathUtils::Max(0, foregroundColor.green * (fadeTimeNoteOn - timeAgo)) / fadeTimeNoteOn;
			uint8_t blue = MathUtils::Max(0, foregroundColor.blue * (fadeTimeNoteOn - timeAgo)) / fadeTimeNoteOn;
			rgb->red = red;
			rgb->green = green;
			rgb->blue = blue;
		}
		else if (!_midiKeyboard.IsPressed(key)) // ((counter % Time::GetTimeInMilliSeconds((Time::ETime) _fadeTimeNoteOff) == 0)
		{
			uint16_t timeAgo = _midiKeyboard.TimeAgo(key);
			//_value_3 = LedColor::SetBrightness(&rgb->red, &rgb->green, &rgb->blue, _value_3, MathUtils::Max(256, 256 * timeAgo / Time::GetTimeInMilliSeconds((Time::ETime) _parameter_4)));
			// (((foregroundColor.green - rgb->green) * _midiKeyboard.TimeAgo(key) *Time::GetTimeInMilliSeconds(_fadeTimeNoteOn)) / foregroundColor.green);
		}
	}
}