#pragma once

#include <cstdint>

#include "Pattern.h"


constexpr auto MAX_NR_OF_NOTES = 4;

class PatternSplits : public Pattern
{
public:
	PatternSplits();

	void SetColorAndNote(uint8_t index, LedColor::EColor color, uint8_t note);

	/* override */ void Start();
	/* override */ void Process();

private:
	uint8_t Fill(uint8_t currentLed, uint8_t noteIndex, uint8_t color);

	uint8_t _colors[MAX_NR_OF_NOTES + 1];
	uint8_t _notes[MAX_NR_OF_NOTES];

	uint8_t _nrOfNotesSet;

};

