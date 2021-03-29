#include "LedStrips.h"
#include <limits.h>
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "MidiKeyboards.h"
#include "Time.h"
#include "LedColor.h"
#include "AssertUtils.h"

/* static */ const uint16_t LedStrips::MAX_CURRENT_IN_MILLI_AMP = 9000; // mA

LedStrips::LedStrips()
{
	if ((NR_OF_MAIN_SYNTH_KEYS + NR_OF_MAIN_SYNTH_FRONT_LEDS + NR_OF_MASTER_KEYBOARD_KEYS + NR_OF_MASTER_KEYBOARD_FRONT_LEDS) *
		LedStrip::MAX_CURRENT_IN_MILLI_AMP_PER_SUB_LED * LedStrip::SUB_LEDS_PER_LED > UINT16_MAX)
	{
		AssertUtils::MyAssert(false);
	}
}


void LedStrips::Initialize()
{
	_ledStrips[MainSynthFront     ].Initialize(NR_OF_MAIN_SYNTH_KEYS);
	_ledStrips[MainSynthBack      ].Initialize(NR_OF_MAIN_SYNTH_FRONT_LEDS);
	_ledStrips[MasterKeyboardFront].Initialize(NR_OF_MASTER_KEYBOARD_KEYS);
	_ledStrips[MasterKeyboardBack ].Initialize(NR_OF_MASTER_KEYBOARD_FRONT_LEDS);

	FastLED.addLeds<WS2812, 2, RGB>(_ledStrips[0].GetLeds(), _ledStrips[0].GetNrOfLeds());
	FastLED.addLeds<WS2812, 3, RGB>(_ledStrips[1].GetLeds(), _ledStrips[1].GetNrOfLeds());
	FastLED.addLeds<WS2812, 4, RGB>(_ledStrips[2].GetLeds(), _ledStrips[2].GetNrOfLeds());
	FastLED.addLeds<WS2812, 5, RGB>(_ledStrips[3].GetLeds(), _ledStrips[3].GetNrOfLeds());
}


void LedStrips::Process()
{
	uint16_t currentFront = _ledStrips[MainSynthFront     ].CalculateCurrentInMilliAmp() +
                            _ledStrips[MasterKeyboardFront].CalculateCurrentInMilliAmp();
	uint16_t currentBack  = _ledStrips[MainSynthBack      ].CalculateCurrentInMilliAmp() + 
		                    _ledStrips[MasterKeyboardBack ].CalculateCurrentInMilliAmp();

	if (currentFront + currentBack > MAX_CURRENT_IN_MILLI_AMP)
	{
		if (currentFront > 0)
		{
			uint8_t currentPercentage = MIN(100, (MAX_CURRENT_IN_MILLI_AMP - currentBack) * 100 / currentFront);
			_ledStrips[MainSynthFront     ].ReduceCurrent(currentPercentage);
			_ledStrips[MasterKeyboardFront].ReduceCurrent(currentPercentage);
		}

		currentFront = _ledStrips[MainSynthFront     ].CalculateCurrentInMilliAmp() +
				       _ledStrips[MasterKeyboardFront].CalculateCurrentInMilliAmp();
	}

	if (currentFront + currentBack > MAX_CURRENT_IN_MILLI_AMP)
	{
		uint8_t currentPercentage = MIN(100, (MAX_CURRENT_IN_MILLI_AMP - currentFront) * 100 / currentBack);
		_ledStrips[MainSynthBack     ].ReduceCurrent(currentPercentage);
		_ledStrips[MasterKeyboardBack].ReduceCurrent(currentPercentage);
	}
}


LedStrip& LedStrips::GetLedStrip(uint8_t index)
{
	return _ledStrips[index];
}
