#pragma once

#include "Pattern.h"
#include "LedStrip.h"
#include "Speed.h"

class PatternKnightRider : public Pattern
{
public:
	PatternKnightRider(LedStrip& ledStrip);

	~PatternKnightRider();

	void SetBackgroundColor(LedColor::EColor color);

	void SetBackgroundColorSpeed(Speed::ESpeed backgroundColorSpeed);

	void SetForegroundColor(LedColor::EColor color);

	void SetForegroundColorSpeed(Speed::ESpeed foregroundColorSpeed);

	void SetDirection(bool direction);

	void SetLedSpeed(Speed::ESpeed ledSpeed);

	void SetLedWidth(uint8_t ledWidth);

	/* override */ void Start();

	/* override */ void Process(uint32_t counter);

private:
	LedColor::EColor _backgroundColor;

	Speed::ESpeed _backgroundColorSpeed;

	LedColor::EColor _foregroundColor;

	Speed::ESpeed _foregroundColorSpeed;

	bool _direction;

	Speed::ESpeed _ledSpeed;

	uint8_t _ledWidth;

	uint8_t _currentLed;
};

