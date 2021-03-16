#include "LedStrips.h"

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "MidiKeyboards.h"
#include "Speed.h"
#include "Time.h"
#include "LedColor.h"



LedStrips::LedStrips()
{
}


LedStrips::~LedStrips()
{
}


void LedStrips::Initialize()
{
	_ledStrips[0].Initialize(NR_OF_MAIN_SYNTH_KEYS);
	_ledStrips[1].Initialize(NR_OF_MAIN_SYNTH_FRONT_LEDS);
	_ledStrips[2].Initialize(NR_OF_MASTER_KEYBOARD_KEYS);
	_ledStrips[3].Initialize(NR_OF_MASTER_KEYBOARD_FRONT_LEDS);

	FastLED.addLeds<WS2811, 2, RGB>(_ledStrips[0].GetLeds(), _ledStrips[0].GetNrOfLeds());
	FastLED.addLeds<WS2811, 3, RGB>(_ledStrips[1].GetLeds(), _ledStrips[1].GetNrOfLeds());
	FastLED.addLeds<WS2811, 4, RGB>(_ledStrips[2].GetLeds(), _ledStrips[2].GetNrOfLeds());
	FastLED.addLeds<WS2811, 5, RGB>(_ledStrips[3].GetLeds(), _ledStrips[3].GetNrOfLeds());
}


void LedStrips::Process(uint32_t counter)
{
	// TODO SafeguardPower();
}


LedStrip& LedStrips::GetLedStrip(uint8_t index)
{
	return _ledStrips[index];
}
