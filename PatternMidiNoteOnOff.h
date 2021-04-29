#pragma once

#include <cstdint>
#include "Pattern.h"
#include "LedStrip.h"
#include "Time.h"
#include "MidiNote.h"

class MidiKeyboard;

class PatternMidiNoteOnOff : public Pattern
{
public:
	PatternMidiNoteOnOff();

	void SetBackgroundColor(LedColor::EColor color);
	void SetBackgroundColorTime(uint32_t backgroundColorTime);

	void SetForegroundColor(LedColor::EColor color);
	void SetForegroundColorTime(uint32_t foregroundColorTime);

	void SetFadeTimeNoteOn(uint32_t fadeTimeNoteOn);
	void SetFadeTimeNoteOff(uint32_t fadeTimeNoteOff);

	void SetMoveRightTime(uint32_t moveRightTime);
	void SetMoveLeftTime(uint32_t moveLeftTime);

	void SetNoteOnVelocityIntensity(uint8_t noteOnVelocityIntensity);

	/* override */ void Start();

	/* override */ void Process();

private:
	void AdjustForegroundLevels(uint8_t key);
	bool ProcessSidewaysMovement(
		bool directionRight, MidiNote midiNote, uint8_t key, uint32_t timeAgoPressed, uint32_t moveTime, uint32_t now, uint8_t* newLed);

	void SetLedColors();

	LedColor::EColor _backgroundColor;
	uint32_t _backgroundColorTime;

	LedColor::EColor _foregroundColor;
	uint32_t _foregroundColorTime;

	uint32_t _fadeTimeNoteOn;
	uint32_t _fadeTimeNoteOff;

	uint32_t _moveRightTime;
	uint32_t _moveLeftTime;

	uint8_t _noteOnVelocityIntensity;

	// Due to patterns having fixed lengths, it is not allowed to use dynamic memory
	uint8_t _foregroundValues[LED_STRIP_MAX_NR_OF_LEDS]; 
};
