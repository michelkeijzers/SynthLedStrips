#pragma once
#include "Pattern.h"
#include "LedStrip.h"
#include "Time.h"
#include "Speed.h"

class MidiKeyboard;

class PatternMidiNoteOnOff : public Pattern
{
public:
	PatternMidiNoteOnOff();
	~PatternMidiNoteOnOff();

	void SetBackgroundColor(LedColor::EColor color);
	void SetBackgroundColorSpeed(Speed::ESpeed backgroundColorSpeed);

	void SetForegroundColor(LedColor::EColor color);
	void SetForegroundColorSpeed(Speed::ESpeed foregroundColorSpeed);

	void SetFadeTimeNoteOn(Time::ETime fadeTimeNoteOn);
	void SetFadeTimeNoteOff(Time::ETime fadeTimeNoteOff);

	void SetNoteOnVelocityIntensity(uint8_t noteOnVelocityIntensity);

	/* override */ void Start();

	/* override */ void Process(uint32_t counter);

private:
	void ProcessFade(Time::ETime fadeTimeEnum, uint8_t key, uint32_t counter);

	LedColor::EColor _backgroundColor;
	Speed::ESpeed _backgroundColorSpeed;

	LedColor::EColor _foregroundColor;
	Speed::ESpeed _foregroundColorSpeed;

	Time::ETime _fadeTimeNoteOn;
	Time::ETime _fadeTimeNoteOff;

	uint8_t _noteOnVelocityIntensity;
};
