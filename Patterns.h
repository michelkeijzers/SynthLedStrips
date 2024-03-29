#pragma once

#include <cstdint>

#include "Pattern.h"
#include "LedStrips.h"

constexpr auto NR_OF_PATTERNS = 4;
constexpr auto MAX_PROPERTY_BYTES = 256;


class Patterns
{
public:
	Patterns();
	~Patterns();

	void Initialize();

	uint8_t* GetPatternData(uint8_t index);

	void SetPattern(uint8_t index, Pattern* pattern, MidiKeyboard* midiKeyboard, LedStrip* ledStrip);

	void Process();

private:
	Pattern* _patterns[NR_OF_LED_STRIPS];
	uint8_t* _patternData;
	uint16_t _patternDataSize;
};
