#include "PatternMidiNoteOnOff.h"
#include "MidiKeyboard.h"
#include "Time.h"


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
	_ledStrip.SetAllLeds(_foregroundColor, 0);
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
	Serial.println("Key pressed");
	Serial.println(key);
	LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, _foregroundColor, 0); // P2: Foreground color
	//_value_3 = LedColor::SetBrightness(&rgb->red, &rgb->green, &rgb->blue, _parameter_6, ((_midiKeyboard.GetVelocity(key) & 0x7F) * 2 + 1)); // P6 = Note On Velocity)
	}
	else
	{
	// Do nothing
	}
		} 
		else if ((counter % Time::GetTimeInMilliSeconds((Time::ETime) _fadeTimeNoteOn) == 0) && _midiKeyboard.IsPressed(key))
		{
			//LedColor::Decrease(&rgb->red, &rgb->green, &rgb->blue);
			uint16_t timeAgo = _midiKeyboard.TimeAgo(key);
			//_value_3 = LedColor::SetBrightness(&rgb->red, &rgb->green, &rgb->blue, _value_3, MathUtils::Max(256, 256 * timeAgo / Time::GetTimeInMilliSeconds((Time::ETime) _parameter_4)));
		}
		else if ((counter % Time::GetTimeInMilliSeconds((Time::ETime) _fadeTimeNoteOff) == 0) && !_midiKeyboard.IsPressed(key))
		{
			uint16_t timeAgo = _midiKeyboard.TimeAgo(key);
			//_value_3 = LedColor::SetBrightness(&rgb->red, &rgb->green, &rgb->blue, _value_3, MathUtils::Max(256, 256 * timeAgo / Time::GetTimeInMilliSeconds((Time::ETime) _parameter_4)));
		}
	}
}