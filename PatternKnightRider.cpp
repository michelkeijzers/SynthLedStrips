#include "PatternKnightRider.h"
#include "SerialUtils.h"
#include "MathUtils.h"
#include "Time.h"
#include "LedColor.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "SynthLedStrips.h"


PatternKnightRider::PatternKnightRider()
:	_ledWidth(0),
	_ledTime(0),
	_foregroundColor(LedColor::EColor::Black),
	_foregroundColorTime(0),
	_backgroundColor(LedColor::EColor::Black),
	_backgroundColorTime(0),
	_direction(false),
	_currentLed(0),
	_timeRemainder(0)
{
}


void PatternKnightRider::SetBackgroundColor(LedColor::EColor color)
{
	_backgroundColor = color;
}


void PatternKnightRider::SetBackgroundColorTime(uint32_t backgroundColorTime)
{
	_backgroundColorTime = backgroundColorTime;
}


void PatternKnightRider::SetForegroundColor(LedColor::EColor color)
{
	_foregroundColor = color;
}


void PatternKnightRider::SetForegroundColorTime(uint32_t foregroundColorTime)
{
	_foregroundColorTime = foregroundColorTime;
}


void PatternKnightRider::SetDirection(bool direction)
{
	_direction = direction;
}


void PatternKnightRider::SetLedTime(uint32_t ledTime)
{
	_ledTime = ledTime;
}

void PatternKnightRider::SetLedWidth(uint8_t ledWidth)
{
	_ledWidth = ledWidth;
}


/* override */ void PatternKnightRider::Start()
{
	_ledStrip->SetAllLeds(_foregroundColor, 0); // P0: Background color
	_currentLed = _direction? 0 : _ledStrip->GetNrOfLeds() - 1;
}


/* override */ void PatternKnightRider::Process()
{
	uint32_t timeStamp = millis();
	ProcessCurrentLed(timeStamp);

	for (uint8_t led = 0; led < _ledStrip->GetNrOfLeds(); led++)
	{
		struct FastLedCRGB *rgb = _ledStrip->GetLed(led);
		uint8_t ratio = MAX(0, _ledWidth - ABS(led - _currentLed));

		if (ratio == 0)
		{
			LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, _backgroundColor, timeStamp * 360 / _backgroundColorTime);
		}
		else
		{
			struct FastLedCRGB backgroundColor{};
			LedColor::SetRgb(&backgroundColor.red, &backgroundColor.green, &backgroundColor.blue, 
				_backgroundColor, timeStamp * 360 / _backgroundColorTime);

			LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, _foregroundColor, timeStamp * 360 / _foregroundColorTime);
			rgb->red = backgroundColor.red + ((rgb->red - backgroundColor.red) * ratio) / _ledWidth;
			rgb->green = backgroundColor.green + ((rgb->green - backgroundColor.green) * ratio) / _ledWidth;
			rgb->blue = backgroundColor.blue + ((rgb->blue - backgroundColor.blue) * ratio) / _ledWidth;
		}
	}
}


void PatternKnightRider::ProcessCurrentLed(uint32_t timeStamp)
{
	uint8_t currentLedShiftAmount = ((timeStamp - _timeLastProcessed) * _ledStrip->GetNrOfLeds()) / _ledTime;

	while(_timeRemainder >= _ledTime)
	{
		_timeRemainder -= _ledTime;
		currentLedShiftAmount++;
	}

	if (currentLedShiftAmount > 0)
	{
		_timeRemainder += ((timeStamp - _timeLastProcessed) * _ledStrip->GetNrOfLeds()) % _ledTime;
		GotoNextCurrentLed(currentLedShiftAmount);
		_timeLastProcessed = timeStamp;
	}
}


void PatternKnightRider::GotoNextCurrentLed(uint8_t currentLedShiftAmount)
{
	for (uint8_t index = 0; index < currentLedShiftAmount; index++)
	{
		_currentLed = (_direction) ? _currentLed + 1 : _currentLed - 1;
		_direction = ((_currentLed == 0) || (_currentLed == _ledStrip->GetNrOfLeds())) ? !_direction : _direction;
	}
}
