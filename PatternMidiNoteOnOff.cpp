#include "PatternMidiNoteOnOff.h"
#include "MidiKeyboard.h"
#include "Time.h"
#include "MathUtils.h"


PatternMidiNoteOnOff::PatternMidiNoteOnOff(LedStrip& ledStrip, MidiKeyboard& midiKeyboard)
	: Pattern(ledStrip),
	_midiKeyboard(midiKeyboard),
	_foregroundColor(LedColor::EColor::Black),
	_backgroundColor(LedColor::EColor::Black),
	_fadeTimeNoteOff(Time::ETime::NA),
	_fadeTimeNoteOn(Time::ETime::NA),
	_noteOnVelocityIntensity(0)
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
		if (_midiKeyboard.IsNew(key))
		{
			if (_midiKeyboard.IsPressed(key))
			{
				Serial.print("Key pressed: ");
				Serial.println(key);
				struct FastLedCRGB* rgb = _ledStrip.GetLed(key); // TODO: Key should be in range 0..59 (led strips)
				LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, _foregroundColor, 0); // P2: Foreground color
				LedColor::SetBrightness(&rgb->red, &rgb->green, &rgb->blue, _noteOnVelocityIntensity, _midiKeyboard.GetVelocity(key) * 2 + 1);
			}
			else
			{
				Serial.print("TimeAgo: ");
				Serial.print(_midiKeyboard.TimeAgo(key));
				_midiKeyboard.SetTimeAgo(key, _midiKeyboard.TimeAgo(key) * Time::GetTimeInMilliSeconds(_fadeTimeNoteOff) / Time::GetTimeInMilliSeconds(_fadeTimeNoteOn));
				Serial.print(", new: ");
				Serial.println(_midiKeyboard.TimeAgo(key));
			}
		} 
		else if (_midiKeyboard.IsPressed(key)) // if ((counter % Time::GetTimeInMilliSeconds((Time::ETime) _fadeTimeNoteOn) == 0)
		{
			ProcessFade(_fadeTimeNoteOn, key, counter);
		}
		else if (!_midiKeyboard.IsPressed(key)) // ((counter % Time::GetTimeInMilliSeconds((Time::ETime) _fadeTimeNoteOff) == 0)
		{
			ProcessFade(_fadeTimeNoteOff, key, counter);
		}
	}
}

void PatternMidiNoteOnOff::ProcessFade(Time::ETime fadeTimeEnum, uint8_t key, uint32_t counter)
{
	uint32_t fadeTime = Time::GetTimeInMilliSeconds(fadeTimeEnum);
	struct FastLedCRGB foregroundColor{};
	LedColor::SetRgb(&foregroundColor.red, &foregroundColor.green, &foregroundColor.blue, _foregroundColor, 0);
	uint32_t timeAgo = _midiKeyboard.TimeAgo(key);
	uint8_t red = foregroundColor.red * MathUtils::Max(0, fadeTime - timeAgo) / fadeTime;
	uint8_t green = foregroundColor.green * MathUtils::Max(0, fadeTime - timeAgo) / fadeTime;
	uint8_t blue = foregroundColor.blue * MathUtils::Max(0, fadeTime - timeAgo) / fadeTime;
	struct FastLedCRGB* rgb = _ledStrip.GetLed(key); // TODO: Key should be in range 0..59 (led strips)
	rgb->red = red;
	rgb->green = green;
	rgb->blue = blue;

}