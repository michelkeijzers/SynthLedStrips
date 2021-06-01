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
	_foregroundColor(LedColor::EColor::BLACK),
	_foregroundColorTime(0),
	_backgroundColor(LedColor::EColor::BLACK),
	_backgroundColorTime(0),
	_moveRightTime(0),
	_moveLeftTime(0),
	_fadeTimeNoteOff(0),
	_fadeTimeNoteOn(0),
	_noteOnVelocityIntensity(0),
	_foregroundValues {}
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

	//for (uint8_t led = 0; led < _ledStrip->GetNrOfLeds(); led++)
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
	
		// 2 bugs:
	    // - LEDs stop before end of right side of led strip


		uint32_t timeDiff = 0;
		if (midiNote.IsPressed())
		{
			Serial.print("+");
			timeDiff = now - midiNote.GetTimePressed();
			if (timeDiff < _fadeTimeNoteOn)
			{
				level = timeDiff * 255 / _fadeTimeNoteOn * 255;
			}
		}
		else 
		{
			Serial.print("-");
			uint8_t remainingLevel = 0;
			timeDiff = now - midiNote.GetTimePressed();
			if (timeDiff < _fadeTimeNoteOn)
			{
				remainingLevel = timeDiff * 255 / _fadeTimeNoteOn * 255;
			}

			timeDiff = now - midiNote.GetTimeReleased();
			if (timeDiff < _fadeTimeNoteOff)
			{
				level = remainingLevel - timeDiff * remainingLevel / _fadeTimeNoteOff;
			}
		}
		//uint32_t timeDiff = now - MathUtils::Max(0, now - !midiNote.IsPressed() * midiNote.GetTimeReleased());
		//level = MathUtils::Min(_fadeTimeNoteOff == 0 ? 255 : (255 - (_fadeTimeNoteOff * 255 / timeDiff));
		SerialUtils::PrintUint("TimeDiff", timeDiff);
		SerialUtils::PrintUint("Key", key);
		SerialUtils::PrintlnUint("Level", level);
			
		uint8_t leftLed = 0;
		uint8_t leftLedInRange = ProcessSidewaysMovement(false, midiNote, key, timeAgoPressed, _moveLeftTime, now, &leftLed);

		uint8_t rightLed = 0;
		uint8_t rightLedInRange = ProcessSidewaysMovement(true, midiNote, key, timeAgoPressed, _moveRightTime, now, &rightLed);

		if (level > 0)
		{
			level = (level * (midiNote.GetVelocity() * 2 + 1)) / 255;
		}
		
		if (leftLedInRange)
		{
			_foregroundValues[leftLed] = MathUtils::Min(255, _foregroundValues[leftLed] + level);
		}

		if (rightLedInRange)
		{
			_foregroundValues[rightLed] = MathUtils::Min(255, _foregroundValues[rightLed] + level);
		}
		else
		{
			Serial.print("-");
		}
	}	
}


bool PatternMidiNoteOnOff::ProcessSidewaysMovement(
	bool directionRight, MidiNote midiNote, uint8_t led, uint32_t timeAgoPressed, uint32_t moveTime, uint32_t now, uint8_t* newLed)
{
	bool inRange = false;

	if ((led >= 0) && (led < _ledStrip->GetNrOfLeds()))
	{
		if ((moveTime == 0) || (timeAgoPressed == 0))
		{
			*newLed = led;
			inRange = true;
		}
		else
		{
			if (timeAgoPressed < moveTime)
			{
				uint32_t newLedUnconstrained =
					led + (directionRight ? 1 : -1) * (((now - midiNote.GetTimePressed()) * _ledStrip->GetNrOfLeds()) / moveTime);
				inRange = ((newLedUnconstrained >= 0) && (newLedUnconstrained < _ledStrip->GetNrOfLeds())); // _midiKeyboard->GetNrOfKeys()));
				if (inRange)
				{
					*newLed = newLedUnconstrained;
				}
			}
		}
	}

	if (!inRange)
	{
		Serial.print("-");
	}
	return inRange;
}


void PatternMidiNoteOnOff::SetLedColors()
{
	for (uint8_t led = 0; led < _ledStrip->GetNrOfLeds(); led++)
	{
		struct FastLedCRGB* rgb = _ledStrip->GetLed(led);
		//SerialUtils::PrintUint(" Key", key);

		if (_foregroundValues[led] == 0)
		{
			LedColor::SetRgb(&(rgb->red), &(rgb->green), &(rgb->blue), _backgroundColor, millis() * 360 / _backgroundColorTime);
			//Serial.print("/");
		}
		else
		{
			LedColor::SetRgb(&(rgb->red), &(rgb->green), &(rgb->blue), _foregroundColor, millis() * 360 / _backgroundColorTime);
			rgb->red   = (rgb->red   * _foregroundValues[led]) / 255;
			rgb->green = (rgb->green * _foregroundValues[led]) / 255;
			rgb->blue  = (rgb->blue  * _foregroundValues[led]) / 255;
			//SerialUtils::PrintRgb(rgb->red, rgb->green, rgb->blue);
		}
	}
	AssertUtils::MyAssert(_midiKeyboard->GetNrOfKeys() == 61);
}
