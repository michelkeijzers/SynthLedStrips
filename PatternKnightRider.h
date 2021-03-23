#pragma once

#include "Pattern.h"
#include "LedStrip.h"


class PatternKnightRider : public Pattern
{
public:
	PatternKnightRider();
	~PatternKnightRider();

	void SetBackgroundColor(LedColor::EColor color);
	void SetBackgroundColorSpeed(uint32_t backgroundColorSpeed);

	void SetForegroundColor(LedColor::EColor color);
    void SetForegroundColorSpeed(uint32_t foregroundColorSpeed);

	void SetDirection(bool direction);

	void SetLedSpeed(uint32_t ledSpeed);

	void SetLedWidth(uint8_t ledWidth);

	/* override */ void Start();

	/* override */ void Process();

private:
	void ProcessCurrentLed(uint32_t timeStamp);

	void GotoNextCurrentLed(uint8_t currentLedShiftAmount);

	LedColor::EColor _backgroundColor;
	uint32_t _backgroundColorSpeed;

	LedColor::EColor _foregroundColor;
	uint32_t _foregroundColorSpeed;

	bool _direction;

	/// <summary>
	/// Speed in one direction
	/// </summary>
	uint32_t _ledSpeed;

	uint8_t _ledWidth;

	uint8_t _currentLed;

	uint16_t _timeRemainder;
};
