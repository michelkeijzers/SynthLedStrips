#include "PatternMidiNoteOnOff.h"
#include "MidiKeyboard.h"
#include "Time.h"

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


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


void PatternMidiNoteOnOff::SetBackgroundColorSpeed(Speed::ESpeed backgroundColorSpeed)
{
	_backgroundColorSpeed = backgroundColorSpeed;
}


void PatternMidiNoteOnOff::SetForegroundColor(LedColor::EColor color)
{
	_foregroundColor = color;
}


void PatternMidiNoteOnOff::SetForegroundColorSpeed(Speed::ESpeed foregroundColorSpeed)
{
	_foregroundColorSpeed = foregroundColorSpeed;
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
				uint8_t led = ConvertKeyToLed(key);
				struct FastLedCRGB* rgb = _ledStrip.GetLed(led);
				LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, _foregroundColor, counter); // P2: Foreground color
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
	uint8_t led = ConvertKeyToLed(key);
	uint32_t fadeTime = Time::GetTimeInMilliSeconds(fadeTimeEnum);
	uint32_t timeAgo = _midiKeyboard.TimeAgo(key);

	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;

	if (timeAgo < fadeTime)
	{
		struct FastLedCRGB foregroundColor{};
		LedColor::SetRgb(&foregroundColor.red, &foregroundColor.green, &foregroundColor.blue, _foregroundColor,  counter * 360 / Speed::GetSpeedInMilliSeconds(_foregroundColorSpeed));
		red = foregroundColor.red * (fadeTime - timeAgo) / fadeTime;
		green = foregroundColor.green * (fadeTime - timeAgo) / fadeTime;
		blue = foregroundColor.blue * (fadeTime - timeAgo) / fadeTime;
	}
	else
	{
		struct FastLedCRGB backgroundColor{};
		LedColor::SetRgb(&backgroundColor.red, &backgroundColor.green, &backgroundColor.blue, _backgroundColor,  counter * 360 / Speed::GetSpeedInMilliSeconds(_backgroundColorSpeed));
		red = backgroundColor.red;
		green = backgroundColor.green;
		blue = backgroundColor.blue;
	}
		
	struct FastLedCRGB* rgb = _ledStrip.GetLed(led);
	rgb->red = red;
	rgb->green = green;
	rgb->blue = blue;
}


uint8_t PatternMidiNoteOnOff::ConvertKeyToLed(uint8_t key)
{
	return constrain(key, 0, _ledStrip.GetNrOfLeds() - 1);
}