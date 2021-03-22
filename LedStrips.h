#pragma once

#include "LedStrip.h"
#include "SynthLedStrips.h"


#define NR_OF_LED_STRIPS                   4

#define NR_OF_MAIN_SYNTH_FRONT_LEDS       98
#define NR_OF_MASTER_KEYBOARD_FRONT_LEDS 178 


class LedStrips
{
public:
	enum ELocation 
	{
		MainSynthFront = 0, 
		MainSynthBack = 1, 
		MasterKeyboardFront = 2, 
		MasterKeyboardBack = 3 
	};

	LedStrips();
	~LedStrips();

	void Initialize();

	void Process();

	LedStrip& GetLedStrip(uint8_t index);

private:
	static const uint16_t MAX_CURRENT_IN_MILLI_AMP;

	LedStrip _ledStrips[NR_OF_LED_STRIPS];
};
