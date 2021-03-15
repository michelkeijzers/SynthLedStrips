#include "PatternKnightRider.h"
#include "MathUtils.h"

#include "LedColor.h"

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


PatternKnightRider::PatternKnightRider(LedStrip& ledStrip)
	: Pattern(ledStrip),
	_ledWidth(0),
	_ledSpeed(Speed::ESpeed::NA),
	_foregroundColor(LedColor::EColor::Black),
	_foregroundColorSpeed(Speed::ESpeed::NA),
	_backgroundColor(LedColor::EColor::Black),
	_backgroundColorSpeed(Speed::ESpeed::NA),
	_direction(false),
	_currentLed(0),
	_counterRemainder(0)
{
}


PatternKnightRider::~PatternKnightRider()
{
}


void PatternKnightRider::SetBackgroundColor(LedColor::EColor color)
{
	_backgroundColor = color;
}


void PatternKnightRider::SetBackgroundColorSpeed(Speed::ESpeed backgroundColorSpeed)
{
	_backgroundColorSpeed = backgroundColorSpeed;
}


void PatternKnightRider::SetForegroundColor(LedColor::EColor color)
{
	_foregroundColor = color;
}


void PatternKnightRider::SetForegroundColorSpeed(Speed::ESpeed foregroundColorSpeed)
{
	_foregroundColorSpeed = foregroundColorSpeed;
}


void PatternKnightRider::SetDirection(bool direction)
{
	_direction = direction;
}


void PatternKnightRider::SetLedSpeed(Speed::ESpeed ledSpeed)
{
	_ledSpeed = ledSpeed;
}

void PatternKnightRider::SetLedWidth(uint8_t ledWidth)
{
	_ledWidth = ledWidth;
}


/* override */ void PatternKnightRider::Start()
{
	_ledStrip.SetAllLeds(_foregroundColor, 0); // P0: Background color
	_currentLed = _direction? 0 : _ledStrip.GetNrOfLeds() - 1;
}


/* override */ void PatternKnightRider::Process(uint32_t counter)
{
	ProcessCurrentLed(counter);

	for (int led = 0; led < _ledStrip.GetNrOfLeds(); led++)
	{
		struct FastLedCRGB *rgb = _ledStrip.GetLed(led);
		uint8_t ratio = MAX(0, _ledWidth - ABS(led - _currentLed));

		if (ratio == 0)
		{
			LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, _backgroundColor, counter * 360 / Speed::GetSpeed(_backgroundColorSpeed));
		}
		else
		{
			LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, _foregroundColor, counter * 360 / Speed::GetSpeed(_foregroundColorSpeed));
			rgb->red = (rgb->red * ratio) / _ledWidth;
			rgb->green = (rgb->green * ratio) / _ledWidth;
			rgb->blue = (rgb->blue * ratio) / _ledWidth;
		}
	}
}


void PatternKnightRider::ProcessCurrentLed(uint32_t counter)
{
	Serial.print("counter: "); Serial.print(counter); 
	uint32_t ledSpeed =  Speed::GetSpeed(_ledSpeed);
	uint8_t currentLedShiftAmount = _ledStrip.GetNrOfLeds() / ledSpeed;
	_counterRemainder += _ledStrip.GetNrOfLeds() % ledSpeed;
	if (_counterRemainder >= ledSpeed)
	{
		_counterRemainder -= ledSpeed;
		currentLedShiftAmount++;
	}

	GotoNextCurrentLed(currentLedShiftAmount);
}


void PatternKnightRider::GotoNextCurrentLed(uint8_t currentLedShiftAmount)
{
	for (uint8_t index = 0; index < currentLedShiftAmount; index++)
	{
		_currentLed = (_direction) ? _currentLed + 1 : _currentLed - 1;
		_direction = ((_currentLed == 0) || (_currentLed == _ledStrip.GetNrOfLeds())) ? !_direction : _direction;
	}
}
