#pragma once
#include "Pattern.h"
#include "LedStrip.h"
#include "Time.h"


class MidiKeyboard;

class PatternMidiNoteOnOff : public Pattern
{
public:
	PatternMidiNoteOnOff(LedStrip& ledStrip, MidiKeyboard& midiKeyboard);

	~PatternMidiNoteOnOff();

	void SetBackgroundColor(LedColor::EColor color);

	void SetForegroundColor(LedColor::EColor color);

	void SetFadeTimeNoteOn(Time::ETime fadeTimeNoteOn);

	void SetFadeTimeNoteOff(Time::ETime fadeTimeNoteOff);

	void SetNoteOnVelocityIntensity(uint8_t noteOnVelocityIntensity);

	/* override */ void Start();

	/* override */ void Process(uint32_t counter);

private:
	MidiKeyboard& _midiKeyboard;

	LedColor::EColor _backgroundColor;

	LedColor::EColor _foregroundColor;

	Time::ETime _fadeTimeNoteOn;

	Time::ETime _fadeTimeNoteOff;

	uint8_t _noteOnVelocityIntensity;
};

