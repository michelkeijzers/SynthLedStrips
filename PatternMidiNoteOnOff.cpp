#include "PatternMidiNoteOnOff.h"
#include "AssertUtils.h"
#include "SerialUtils.h"
#include "MathUtils.h"
#include "MidiKeyboard.h"
#include "Time.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "MidiNote.h"


PatternMidiNoteOnOff::PatternMidiNoteOnOff()
	:	Pattern(),
	_foregroundColor(LedColor::EColor::Black),
	_foregroundColorSpeed(0),
	_backgroundColor(LedColor::EColor::Black),
	_backgroundColorSpeed(0),
	_moveRightSpeed(0),
	_moveLeftSpeed(0),
	_fadeTimeNoteOff(0),
	_fadeTimeNoteOn(0),
	_noteOnVelocityIntensity(0),
	_foregroundValues {}
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


void PatternMidiNoteOnOff::SetMoveRightSpeed(uint32_t moveRightSpeed)
{
	_moveRightSpeed = moveRightSpeed;
}


void PatternMidiNoteOnOff::SetMoveLeftSpeed(uint32_t moveLeftSpeed)
{
	_moveLeftSpeed = moveLeftSpeed;
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
	for (uint8_t led = 0; led < _ledStrip->GetNrOfLeds(); led++)
	{
		_foregroundValues[led] = 0x0;
	}

	for (uint8_t key = 0; key < _midiKeyboard->GetNrOfKeys(); key++)
	{
		AdjustForegroundLevels(key);
	}

	for (uint8_t led = 0; led < _ledStrip->GetNrOfLeds(); led++)
	{
		SetLedColors();	
	}
}


void PatternMidiNoteOnOff::AdjustForegroundLevels(uint8_t key)
{
	uint32_t now = millis();

	uint8_t level = 0;

	MidiNote& midiNote = _midiKeyboard->GetMidiNote(key);
	if (midiNote.GetTimePressed() != 0)
	{
		Serial.println("--");
		uint32_t timeAgoPressed = now - midiNote.GetTimePressed();

		if (midiNote.IsPressed())
		{
			level = _fadeTimeNoteOn == 0 ? 255 : 255 - MathUtils::Max(0, ((timeAgoPressed * 255) / _fadeTimeNoteOn));
			SerialUtils::PrintInt("Key", key);
			SerialUtils::PrintInt("TimeAgoPressed", timeAgoPressed);
			SerialUtils::PrintInt("Level", level);
		}
		else
		{
			level = _fadeTimeNoteOff == 0 ? 255 : 255 - MathUtils::Max(0, (((now - midiNote.GetTimeReleased()) * 255) / _fadeTimeNoteOff));
		}

		bool leftKeyInRange = false;
		int16_t leftKey = 0;

		if ((key >= 0) && (key < _ledStrip->GetNrOfLeds()))
		{
			if (_moveLeftSpeed == 0)
			{
				leftKeyInRange = true;
				leftKey = key;
			}
			else
			{
				if (timeAgoPressed < _moveLeftSpeed)
				{
					leftKeyInRange = true;
					leftKey = key - ((now - midiNote.GetTimePressed()) * _midiKeyboard->GetNrOfKeys()) / _moveLeftSpeed; 
					//SerialUtils::PrintInt("Left Key", leftKey);
				}
			}
		}

		bool rightKeyInRange = false;
		int16_t rightKey = 0;

		if ((key >= 0) && (key < _ledStrip->GetNrOfLeds()))
		{
			if (_moveRightSpeed = 0)
			{
				rightKeyInRange = _moveLeftSpeed != 0;
				rightKey = key;
			}
			else
			{
				if (timeAgoPressed < _moveRightSpeed)
				{
					rightKeyInRange = true;
					rightKey = key - (now - midiNote.GetTimePressed() * _midiKeyboard->GetNrOfKeys()) / _moveRightSpeed; 
					SerialUtils::PrintInt("Right Key", rightKey);
				}
			}
		}

		if (level > 0)
		{
			level = (level * (midiNote.GetVelocity() * 2 - 1)) / 255;
			// _noteOnVelocityIntensity
			SerialUtils::PrintInt("Level end", level);
			Serial.println("");
		}

		if (leftKeyInRange)
		{
			AssertUtils::MyAssert(_midiKeyboard->GetNrOfKeys() == 61);
			AssertUtils::MyAssert(_foregroundValues != nullptr);
			AssertUtils::MyAssert(leftKey >= 0);
			AssertUtils::MyAssert(leftKey < _ledStrip->GetNrOfLeds());
			if (_foregroundValues != nullptr)
			{
				_foregroundValues[leftKey] = MathUtils::Min(127, _foregroundValues[leftKey] + level);
			}
			AssertUtils::MyAssert(_midiKeyboard->GetNrOfKeys() == 61);
		}


		if (rightKeyInRange)
		{
			AssertUtils::MyAssert(_midiKeyboard->GetNrOfKeys() == 61);
			AssertUtils::MyAssert(rightKey >= 0);
			AssertUtils::MyAssert(rightKey < _ledStrip->GetNrOfLeds());
			SerialUtils::PrintInt("Right Key", rightKey);
			SerialUtils::PrintInt("Level", MathUtils::Min(127, _foregroundValues[rightKey] + level));
			Serial.println((uint32_t) this);
			Serial.println("");
			if (_foregroundValues != nullptr)
			{
				_foregroundValues[rightKey] = MathUtils::Min(127, _foregroundValues[rightKey] + level);
			}
			AssertUtils::MyAssert(_midiKeyboard->GetNrOfKeys() == 61);
		}
	}	
}


void PatternMidiNoteOnOff::SetLedColors()
{
	for (uint8_t key = 0; key < _midiKeyboard->GetNrOfKeys(); key++)
	{
		struct FastLedCRGB* rgb = _ledStrip->GetLed(key);

		if (_foregroundValues[key] == 0)
		{
			LedColor::SetRgb(&(rgb->red), &(rgb->green), &(rgb->blue), _backgroundColor, millis() * 360 / _backgroundColorSpeed);
		}
		else
		{
			LedColor::SetRgb(&(rgb->red), &(rgb->green), &(rgb->blue), _foregroundColor, millis() * 360 / _backgroundColorSpeed);
			rgb->red   = (rgb->red   * 255) / _foregroundValues[key];
			rgb->green = (rgb->green * 255) / _foregroundValues[key];
			rgb->blue  = (rgb->blue  * 255) / _foregroundValues[key];
		}
	}
	AssertUtils::MyAssert(_midiKeyboard->GetNrOfKeys() == 61);

}
