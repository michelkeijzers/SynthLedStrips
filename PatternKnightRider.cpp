#include "PatternKnightRider.h"
#include "MathUtils.h"

#include "LedColor.h"

PatternKnightRider::PatternKnightRider(LedStrip& ledStrip)
	: Pattern(ledStrip),
	_ledWidth(0),
	_ledSpeed(Speed::ESpeed::NA),
	_foregroundColor(LedColor::EColor::Black),
	_backgroundColor(LedColor::EColor::Black),
	_direction(false),
	_currentLed(0)
{
}


PatternKnightRider::~PatternKnightRider()
{
}


void PatternKnightRider::SetBackgroundColor(LedColor::EColor color)
{
	_backgroundColor = color;
}


void PatternKnightRider::SetForegroundColor(LedColor::EColor color)
{
	_foregroundColor = color;
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
	// P0: RGB, P3: Speed, P4: Width
	// V0: Direction V1: Current led

	if (counter % (Speed::GetSpeedInMilliSeconds(_ledSpeed) / _ledStrip.GetNrOfLeds()) == 0)
	{
		_currentLed = (_direction) ? _currentLed + 1 : _currentLed - 1;
		_direction = ((_currentLed == 0) || (_currentLed == _ledStrip.GetNrOfLeds() - 1)) ? !_direction : _direction;
	}

	for (int led = 0; led < _ledStrip.GetNrOfLeds(); led++)
	{
		struct FastLedCRGB *rgb = _ledStrip.GetLed(led);
		uint8_t ratio = MathUtils::Max(0, _ledWidth - MathUtils::Abs(led - _currentLed));

		LedColor::SetRgb(&rgb->red, &rgb->green, &rgb->blue, _foregroundColor, 0); // TODO: Step 0
		rgb->red = (rgb->red * ratio) / _ledWidth;
		rgb->green = (rgb->green * ratio) / _ledWidth;
		rgb->blue = (rgb->blue * ratio) / _ledWidth;
	}
}