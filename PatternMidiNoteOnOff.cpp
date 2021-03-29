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
	_foregroundColorTime(0),
	_backgroundColor(LedColor::EColor::Black),
	_backgroundColorTime(0),
	_moveRightTime(0),
	_moveLeftTime(0),
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


void PatternMidiNoteOnOff::SetBackgroundColorTime(uint32_t backgroundColorTime)
{
	_backgroundColorTime = backgroundColorTime;
}


void PatternMidiNoteOnOff::SetForegroundColor(LedColor::EColor color)
{
	_foregroundColor = color;
}


void PatternMidiNoteOnOff::SetForegroundColorTime(uint32_t foregroundColorTime)
{
	_foregroundColorTime = foregroundColorTime;
}


void PatternMidiNoteOnOff::SetFadeTimeNoteOn(uint32_t fadeTimeNoteOn)
{
	_fadeTimeNoteOn = fadeTimeNoteOn;
}


void PatternMidiNoteOnOff::SetFadeTimeNoteOff(uint32_t fadeTimeNoteOff)
{
	_fadeTimeNoteOff = fadeTimeNoteOff;
}


void PatternMidiNoteOnOff::SetMoveRightTime(uint32_t moveRightTime)
{
	_moveRightTime = moveRightTime;
}


void PatternMidiNoteOnOff::SetMoveLeftTime(uint32_t moveLeftTime)
{
	_moveLeftTime = moveLeftTime;
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
		//Serial.println("--");
		uint32_t timeAgoPressed = now - midiNote.GetTimePressed();
		
		level = _fadeTimeNoteOff == 0 ? 255 : 255 - MathUtils::Max(
			0, (((now - (!midiNote.IsPressed() * midiNote.GetTimeReleased())) * 255) / _fadeTimeNoteOff));
	
		uint8_t leftKey = 0;
		uint8_t leftKeyInRange = ProcessSidewaysMovement(false, midiNote, key, timeAgoPressed, _moveLeftTime, now, &leftKey);

		uint8_t rightKey = 0;
		uint8_t rightKeyInRange = ProcessSidewaysMovement(true, midiNote, key, timeAgoPressed, _moveRightTime, now, &rightKey);

		if (level > 0)
		{
			level = (level * (midiNote.GetVelocity() * 2 + 1)) / 255;
		}
		
		if (leftKeyInRange)
		{
			_foregroundValues[leftKey] = MathUtils::Min(255, _foregroundValues[leftKey] + level);
		}

		if (rightKeyInRange)
		{
			_foregroundValues[rightKey] = MathUtils::Min(255, _foregroundValues[rightKey] + level);
		}
	}	
}


bool PatternMidiNoteOnOff::ProcessSidewaysMovement(
	bool directionRight, MidiNote midiNote, uint8_t key, uint32_t timeAgoPressed, uint32_t moveTime, uint32_t now, uint8_t* newKey)
{
	uint32_t newKeyUnconstrained;
	bool inRange = false;

	if ((key >= 0) && (key < _ledStrip->GetNrOfLeds()))
	{
		if ((moveTime == 0) || (timeAgoPressed == 0))
		{
			*newKey = key;
			inRange = true;
		}
		else
		{
			if (timeAgoPressed < moveTime)
			{
				newKeyUnconstrained =
					key + (directionRight ? 1 : -1) * (((now - midiNote.GetTimePressed())  * _midiKeyboard->GetNrOfKeys()) / moveTime);
				inRange = ((newKeyUnconstrained >= 0) && (newKeyUnconstrained < _midiKeyboard->GetNrOfKeys()));
				if (inRange)
				{
					*newKey = newKeyUnconstrained;
				}
			}
		}
	}

	return inRange;
}


void PatternMidiNoteOnOff::SetLedColors()
{
	for (uint8_t key = 0; key < _midiKeyboard->GetNrOfKeys(); key++)
	{
		struct FastLedCRGB* rgb = _ledStrip->GetLed(key);

		if (_foregroundValues[key] == 0)
		{
			LedColor::SetRgb(&(rgb->red), &(rgb->green), &(rgb->blue), _backgroundColor, millis() * 360 / _backgroundColorTime);
		}
		else
		{
			LedColor::SetRgb(&(rgb->red), &(rgb->green), &(rgb->blue), _foregroundColor, millis() * 360 / _backgroundColorTime);
			rgb->red   = (rgb->red   * _foregroundValues[key]) / 255;
			rgb->green = (rgb->green * _foregroundValues[key]) / 255;
			rgb->blue  = (rgb->blue  * _foregroundValues[key]) / 255;
		}
	}
	AssertUtils::MyAssert(_midiKeyboard->GetNrOfKeys() == 61);

}
