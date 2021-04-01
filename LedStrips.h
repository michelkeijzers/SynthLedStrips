#pragma once

#include "LedStrip.h"
#include "SynthLedStrips.h"

constexpr auto NR_OF_LED_STRIPS = 4;
constexpr auto NR_OF_KEYBOARD_1_FRONT_LEDS = 98;
constexpr auto NR_OF_KEYBOARD_2_FRONT_LEDS = 178 ;

class LedStrips
{
public:
	enum ELocation 
	{
		Keyboard1Front = 0, 
		Keyboard1Back = 1, 
		Keyboard2Front = 2, 
		Keyboard2Back = 3 
	};

	LedStrips();

	void Initialize();

	void Process();

	void On();
	void Off();
	bool IsOn();

	LedStrip& GetLedStrip(uint8_t index);

private:
	static const uint16_t MAX_CURRENT_IN_MILLI_AMP;

	LedStrip _ledStrips[NR_OF_LED_STRIPS];

	bool _on;
};
