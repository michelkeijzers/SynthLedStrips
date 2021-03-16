#pragma once

#include "Pattern.h"
#include "LedStrips.h"


#define NR_OF_PATTERNS 4


class Patterns
{
public:
	Patterns();
	~Patterns();

	void Initialize();

	uint8_t* GetPatternData(uint8_t index);

	void SetPattern(uint8_t index, Pattern* pattern, MidiKeyboard* midiKeyboard, LedStrip* ledStrip);

	void Process(uint32_t counter);

private:
	Pattern* _patterns[NR_OF_LED_STRIPS];
	uint8_t* _patternData;
	uint8_t _patternDataSize;
};
