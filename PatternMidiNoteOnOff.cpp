#include "PatternMidiNoteOnOff.h"
#include "MidiKeyboard.h"
#include "Time.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "MidiNote.h"


PatternMidiNoteOnOff::PatternMidiNoteOnOff()
:	_foregroundColor(LedColor::EColor::Black),
	_foregroundColorSpeed(0),
	_backgroundColor(LedColor::EColor::Black),
	_backgroundColorSpeed(0),
	_fadeTimeNoteOff(0),
	_fadeTimeNoteOn(0),
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


void PatternMidiNoteOnOff::SetBackgroundColorSpeed(uint32_t backgroundColorSpeed)
{
	_backgroundColorSpeed = backgroundColorSpeed;
}


void PatternMidiNoteOnOff::SetForegroundColor(LedColor::EColor color)
{
	_foregroundColor = color;
}


void PatternMidiNoteOnOff::SetForegroundColorSpeed(uint32_t foregroundColorSpeed)
{
	_foregroundColorSpeed = foregroundColorSpeed;
}


void PatternMidiNoteOnOff::SetFadeTimeNoteOn(uint32_t fadeTimeNoteOn)
{
	_fadeTimeNoteOn = fadeTimeNoteOn;
}


void PatternMidiNoteOnOff::SetFadeTimeNoteOff(uint32_t fadeTimeNoteOff)
{
	_fadeTimeNoteOff = fadeTimeNoteOff;
}


void PatternMidiNoteOnOff::SetNoteOnVelocityIntensity(uint8_t noteOnVelocityIntensity)
{
	_noteOnVelocityIntensity = noteOnVelocityIntensity;
}


/* override */ void PatternMidiNoteOnOff::Start()
{
	_ledStrip->SetAllLeds(_backgroundColor, 0);
}


/* override */ void PatternMidiNoteOnOff::Process()
{
	for (uint8_t key = 0; key < _midiKeyboard->GetNrOfKeys(); key++)
	{
		MidiNote& midiNote = _midiKeyboard->GetMidiNote(key);

		if (midiNote.HasStatusChanged())
		{
			if (midiNote.IsPressed())
			{
				Serial.print("Key pressed: ");
				Serial.println(key);
				struct FastLedCRGB* rgb = _ledStrip->GetLed(key);
				LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, _foregroundColor, millis());
				LedColor::SetBrightness(&rgb->red, &rgb->green, &rgb->blue, 
					_noteOnVelocityIntensity, midiNote.GetVelocity() * 2 + 1);
			}
		} 
		else if (midiNote.IsPressed())
		{
			ProcessFade(_fadeTimeNoteOn, key);
		}
		else if (!midiNote.IsPressed())
		{
			ProcessFade(_fadeTimeNoteOff, key);
		}
	}
}


void PatternMidiNoteOnOff::ProcessFade(uint32_t fadeTime, uint8_t key)
{
	uint32_t timeAgo = millis() - _midiKeyboard->GetMidiNote(key).GetTimePressed();
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;

	if (timeAgo < fadeTime)
	{
		struct FastLedCRGB foregroundColor{};
		LedColor::SetRgb(&foregroundColor.red, &foregroundColor.green, &foregroundColor.blue, 
			_foregroundColor,  millis() * 360 / _foregroundColorSpeed);
		red = foregroundColor.red * (fadeTime - timeAgo) / fadeTime;
		green = foregroundColor.green * (fadeTime - timeAgo) / fadeTime;
		blue = foregroundColor.blue * (fadeTime - timeAgo) / fadeTime;
	}
	else
	{
		struct FastLedCRGB* backgroundColor = _ledStrip->GetLed(key);
		LedColor::SetRgb(&(backgroundColor->red), &(backgroundColor->green), &(backgroundColor->blue), 
			_backgroundColor, millis() * 360 / _backgroundColorSpeed);
		red = backgroundColor->red;
		green = backgroundColor->green;
		blue = backgroundColor->blue;
	}
		
	struct FastLedCRGB* rgb = _ledStrip->GetLed(key);
	rgb->red = red;
	rgb->green = green;
	rgb->blue = blue;
}
