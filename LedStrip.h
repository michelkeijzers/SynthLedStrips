#pragma once

#include "SynthLedStripsTypes.h"

#include "ClassNames.h"
#include HEADER_FILE(FAST_LED_CLASS)

class LedStrip
{
public:

	enum class EPattern { Off, KnightRider, KnightRiderSpread, Strobo };
	
	LedStrip();

    ~LedStrip();

    void Set(uint8_t dataPin, uint8_t nrOfLeds, struct FastLedCRGB* data, EPattern pattern,
		uint8_t parameter0 = 0, uint8_t parameter1 = 0, uint8_t parameter2 = 0, uint8_t parameter3 = 0,
		uint8_t parameter4 = 0, uint8_t parameter5 = 0, uint8_t parameter6 = 0, uint8_t parameter7 = 0);

	void Process(uint32_t counter);

private:

	void ProcessStart(uint32_t counter);
	void ProcessLeds(uint32_t counter);

	uint8_t _dataPin;

	uint8_t _nrOfLeds;

	struct FastLedCRGB* _data;

	EPattern _pattern;


	// LED Strips

	uint8_t _value_0 = 0;
	uint8_t _value_1 = 1;

	uint8_t _parameter_0 = 0;
	uint8_t _parameter_1 = 0;
	uint8_t _parameter_2 = 0;
	uint8_t _parameter_3 = 0;
	uint8_t _parameter_4 = 0;
	uint8_t _parameter_5 = 0;
	uint8_t _parameter_6 = 0;
	uint8_t _parameter_7 = 0;
};

