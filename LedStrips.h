#pragma once

#include "LedStrip.h"
#include "SynthLedStrips.h"


#define NR_OF_LED_STRIPS                   4

#define NR_OF_MAIN_SYNTH_FRONT_LEDS       98
#define NR_OF_MASTER_KEYBOARD_FRONT_LEDS 178 


class LedStrips
{
public:
	LedStrips();

	~LedStrips();

	void Initialize();

	void Process(uint32_t counter);

	LedStrip& GetLedStrip(uint8_t index);

private:
	LedStrip _ledStrips[NR_OF_LED_STRIPS];
};

