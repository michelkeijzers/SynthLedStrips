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
	_ledSpeed(0),
	_foregroundColor(LedColor::EColor::Black),
	_foregroundColorSpeed(0),
	_backgroundColor(LedColor::EColor::Black),
	_backgroundColorSpeed(0),
	_direction(false),
	_currentLed(0),
	_timeRemainder(0)
{
}


PatternKnightRider::~PatternKnightRider()
{
}


void PatternKnightRider::SetBackgroundColor(LedColor::EColor color)
{
	_backgroundColor = color;
}


void PatternKnightRider::SetBackgroundColorSpeed(uint32_t backgroundColorSpeed)
{
	_backgroundColorSpeed = backgroundColorSpeed;
}


void PatternKnightRider::SetForegroundColor(LedColor::EColor color)
{
	_foregroundColor = color;
}


void PatternKnightRider::SetForegroundColorSpeed(uint32_t foregroundColorSpeed)
{
	_foregroundColorSpeed = foregroundColorSpeed;
}


void PatternKnightRider::SetDirection(bool direction)
{
	_direction = direction;
}


void PatternKnightRider::SetLedSpeed(uint32_t ledSpeed)
{
	_ledSpeed = ledSpeed;
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

	for (uint16_t led = 0; led < _ledStrip->GetNrOfLeds(); led++)
	{
		struct FastLedCRGB *rgb = _ledStrip->GetLed(led);
		uint8_t ratio = MAX(0, _ledWidth - ABS(led - _currentLed));

		if (ratio == 0)
		{
			LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, _backgroundColor, timeStamp * 360 / _backgroundColorSpeed);
		}
		else
		{
			struct FastLedCRGB backgroundColor{};
			LedColor::SetRgb(&backgroundColor.red, &backgroundColor.green, &backgroundColor.blue, 
				_backgroundColor, timeStamp * 360 / _backgroundColorSpeed);

			LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, _foregroundColor, timeStamp * 360 / _foregroundColorSpeed);
			rgb->red = backgroundColor.red + ((rgb->red - backgroundColor.red) * ratio) / _ledWidth;
			rgb->green = backgroundColor.green + ((rgb->green - backgroundColor.green) * ratio) / _ledWidth;
			rgb->blue = backgroundColor.blue + ((rgb->blue - backgroundColor.blue) * ratio) / _ledWidth;
		}
	}
}


void PatternKnightRider::ProcessCurrentLed(uint32_t timeStamp)
{
	uint8_t currentLedShiftAmount = ((timeStamp - _timeLastProcessed) * _ledStrip->GetNrOfLeds()) / _ledSpeed;

	while(_timeRemainder >= _ledSpeed)
	{
		_timeRemainder -= _ledSpeed;
		currentLedShiftAmount++;
	}

	if (currentLedShiftAmount > 0)
	{
		_timeRemainder += ((timeStamp - _timeLastProcessed) * _ledStrip->GetNrOfLeds()) % _ledSpeed;
		GotoNextCurrentLed(currentLedShiftAmount);
		_timeLastProcessed = timeStamp;
	}
}


void PatternKnightRider::GotoNextCurrentLed(uint8_t currentLedShiftAmount)
{
	for (uint16_t index = 0; index < currentLedShiftAmount; index++)
	{
		_currentLed = (_direction) ? _currentLed + 1 : _currentLed - 1;
		_direction = ((_currentLed == 0) || (_currentLed == _ledStrip->GetNrOfLeds())) ? !_direction : _direction;
	}
}
