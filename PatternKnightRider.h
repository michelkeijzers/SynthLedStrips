#pragma once

#include "Pattern.h"
#include "LedStrip.h"

class PatternKnightRider : public Pattern
{
public:
	PatternKnightRider();

	void SetBackgroundColor(LedColor::EColor color);
	void SetBackgroundColorTime(uint32_t backgroundColorTime);

	void SetForegroundColor(LedColor::EColor color);
    void SetForegroundColorTime(uint32_t foregroundColorTime);

	void SetDirection(bool direction);

	void SetLedTime(uint32_t ledTime);

	void SetLedWidth(uint8_t ledWidth);

	/* override */ void Start();

	/* override */ void Process();

private:
	void ProcessCurrentLed(uint32_t timeStamp);

	void GotoNextCurrentLed(uint8_t currentLedShiftAmount);

	LedColor::EColor _backgroundColor;
	uint32_t _backgroundColorTime;

	LedColor::EColor _foregroundColor;
	uint32_t _foregroundColorTime;

	bool _direction;

	/// <summary>
	/// Time in one direction
	/// </summary>
	uint32_t _ledTime;

	uint8_t _ledWidth;

	uint8_t _currentLed;

	uint16_t _timeRemainder;
};
