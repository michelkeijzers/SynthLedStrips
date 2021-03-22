#pragma once
#include "Pattern.h"
#include "LedStrip.h"
#include "Time.h"


class MidiKeyboard;

class PatternMidiNoteOnOff : public Pattern
{
public:
	PatternMidiNoteOnOff();
	~PatternMidiNoteOnOff();

	void SetBackgroundColor(LedColor::EColor color);
	void SetBackgroundColorSpeed(uint32_t backgroundColorSpeed);

	void SetForegroundColor(LedColor::EColor color);
	void SetForegroundColorSpeed(uint32_t foregroundColorSpeed);

	void SetFadeTimeNoteOn(uint32_t fadeTimeNoteOn);
	void SetFadeTimeNoteOff(uint32_t fadeTimeNoteOff);

	void SetNoteOnVelocityIntensity(uint8_t noteOnVelocityIntensity);

	/* override */ void Start();

	/* override */ void Process();

private:
	void ProcessFade(uint32_t fadeTime, uint8_t key);

	LedColor::EColor _backgroundColor;
	uint32_t _backgroundColorSpeed;

	LedColor::EColor _foregroundColor;
	uint32_t _foregroundColorSpeed;

	uint32_t _fadeTimeNoteOn;
	uint32_t _fadeTimeNoteOff;

	uint8_t _noteOnVelocityIntensity;
};
