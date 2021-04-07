#include "LedStrips.h"

#include <cstdint>
#include <limits.h>

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "MidiKeyboards.h"
#include "Time.h"
#include "LedColor.h"
#include "AssertUtils.h"

/* static */ const uint16_t LedStrips::MAX_CURRENT_IN_MILLI_AMP = 9000; // mA

LedStrips::LedStrips()
  : _on(false)
{
	if ((NR_OF_KEYBOARD_1_KEYS + NR_OF_KEYBOARD_1_FRONT_LEDS + 
		 NR_OF_KEYBOARD_2_KEYS + NR_OF_KEYBOARD_2_FRONT_LEDS) *
		LedStrip::MAX_CURRENT_IN_MILLI_AMP_PER_SUB_LED * LedStrip::SUB_LEDS_PER_LED > UINT16_MAX)
	{
		AssertUtils::MyAssert(false);
	}
}


void LedStrips::Initialize()
{
	_ledStrips[Keyboard1Front].Initialize(NR_OF_KEYBOARD_1_KEYS);
	_ledStrips[Keyboard1Back ].Initialize(NR_OF_KEYBOARD_1_FRONT_LEDS);
	_ledStrips[Keyboard2Front].Initialize(NR_OF_KEYBOARD_2_KEYS);
	_ledStrips[Keyboard2Back ].Initialize(NR_OF_KEYBOARD_2_FRONT_LEDS);

	FastLED.addLeds<WS2812, 2, RGB>(_ledStrips[0].GetLeds(), _ledStrips[0].GetNrOfLeds());
	FastLED.addLeds<WS2812, 3, RGB>(_ledStrips[1].GetLeds(), _ledStrips[1].GetNrOfLeds());
	FastLED.addLeds<WS2812, 4, RGB>(_ledStrips[2].GetLeds(), _ledStrips[2].GetNrOfLeds());
	FastLED.addLeds<WS2812, 5, RGB>(_ledStrips[3].GetLeds(), _ledStrips[3].GetNrOfLeds());
}


void LedStrips::Process()
{
	uint16_t currentFront = _ledStrips[Keyboard1Front].CalculateCurrentInMilliAmp() +
                            _ledStrips[Keyboard2Front].CalculateCurrentInMilliAmp();
	uint16_t currentBack  = _ledStrips[Keyboard1Back ].CalculateCurrentInMilliAmp() + 
		                    _ledStrips[Keyboard2Back ].CalculateCurrentInMilliAmp();

	if (currentFront + currentBack > MAX_CURRENT_IN_MILLI_AMP)
	{
		if (currentFront > 0)
		{
			uint8_t currentPercentage = MIN(100, (MAX_CURRENT_IN_MILLI_AMP - currentBack) * 100 / currentFront);
			_ledStrips[Keyboard1Front     ].ReduceCurrent(currentPercentage);
			_ledStrips[Keyboard2Front].ReduceCurrent(currentPercentage);
		}

		currentFront = _ledStrips[Keyboard1Front].CalculateCurrentInMilliAmp() +
				       _ledStrips[Keyboard2Front].CalculateCurrentInMilliAmp();
	}

	if (currentFront + currentBack > MAX_CURRENT_IN_MILLI_AMP)
	{
		uint8_t currentPercentage = MIN(100, (MAX_CURRENT_IN_MILLI_AMP - currentFront) * 100 / currentBack);
		_ledStrips[Keyboard1Back].ReduceCurrent(currentPercentage);
		_ledStrips[Keyboard2Back].ReduceCurrent(currentPercentage);
	}
}


void LedStrips::On()
{
	_on = true;
	for (uint8_t ledStrip = 0; ledStrip < NR_OF_LED_STRIPS; ledStrip++)
	{
		_ledStrips[ledStrip].SetAllLeds(0); 
	}
}


void LedStrips::Off()
{
	_on = false;
}


bool LedStrips::IsOn()
{
	return _on;
}


LedStrip& LedStrips::GetLedStrip(uint8_t index)
{
	return _ledStrips[index];
}
