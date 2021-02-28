#include "MathUtils.h"
#include "LedStrip.h"
#include <stdlib.h>


LedStrip::LedStrip()
:
	_dataPin(0),
	_nrOfLeds(0),
	_data(NULL),
	_pattern(EPattern::Off),
	_value_0(0),
	_value_1(0),
	_parameter_0(0),
	_parameter_1(0),
	_parameter_2(0),
	_parameter_3(0),
	_parameter_4(0),
	_parameter_5(0),
	_parameter_6(0),
	_parameter_7(0)
{

}



LedStrip::~LedStrip()
{

}


void LedStrip::Set(uint8_t dataPin, uint8_t nrOfLeds, struct FastLedCRGB* data, EPattern pattern,
	uint8_t parameter_0 /* = 0 */, uint8_t parameter_1 /* = 0 */, uint8_t parameter_2 /* = 0 */, uint8_t parameter_3 /* = 0 */,
	uint8_t parameter_4 /* = 0 */, uint8_t parameter_5 /* = 0 */, uint8_t parameter_6 /* = 0 */, uint8_t parameter_7 /* = 0 */)
{
	_dataPin = dataPin;
	_nrOfLeds = nrOfLeds;
	_data = data;
	_pattern = pattern;
	_parameter_0 = parameter_0;
	_parameter_1 = parameter_1;
	_parameter_2 = parameter_2;
	_parameter_3 = parameter_3;
	_parameter_4 = parameter_4;
	_parameter_5 = parameter_5;
	_parameter_6 = parameter_6;
	_parameter_7 = parameter_7;

	_value_0 = 0; // Down/Up
	_value_1 = 1; // Current LED
}


void LedStrip::Process(uint32_t counter)
{
	ProcessStart(counter);
	ProcessLeds(counter);
}


void LedStrip::ProcessStart(uint32_t counter)
{
	// LEDs
	switch (_pattern)
	{
	case EPattern::Off:
		break;

	case EPattern::KnightRider:
	case EPattern::KnightRiderSpread:
	    if (counter % _parameter_3 == 0)
		{
			_value_1 = (_value_0 == 0) ? _value_1 - 1 : _value_1 + 1;
			_value_0 = ((_value_1 == 0) || (_value_1 == _nrOfLeds - 1)) ? ~_value_0 : _value_0;
		}
		break;

	default:
		exit(0);
	}
}


void LedStrip::ProcessLeds(uint32_t counter)
{
	for (int led = 0; led < _nrOfLeds; led++)
	{
		struct FastLedCRGB *rgb = &(_data[led]);
		switch (_pattern)
		{
		case EPattern::Off:
			rgb->red = 0;
			rgb->green = 0;
			rgb->blue = 0;
			break;

		case EPattern::KnightRider:
			// P0: RGB, P3: Speed
			// V0: Direction V1: Current led
			rgb->red = _value_1 == led ? _parameter_0 : 0;
			rgb->blue = _value_1 == led ? _parameter_1 : 0;
			rgb->green = _value_1 == led ? _parameter_2 : 0;
			break;

		case EPattern::KnightRiderSpread:
			// P0: RGB, P3: Speed, P4: Width
			// V0: Direction V1: Current led
			{
				uint8_t ratio = MathUtils::Max(0, _parameter_4 - MathUtils::Abs(led - _value_1));
		
				rgb->red = (_parameter_0 * ratio) / _parameter_4;
				rgb->blue = (_parameter_1 * ratio) / _parameter_4;
				rgb->green = (_parameter_2 * ratio) / _parameter_4;
			}
			break;

		default:
			exit(0);
		}

		//int width = 15;
		//rgb->red = max(0, width - abs(led - _currentLed)) * (255/width);
		//rgb->green = _currentLed * 3 + led % 20 * 2; // 0; ((NR_OF_LEDS - led - 1) == _currentLed) ? 255 : 0;
		//rgb->blue = 0; //(led + _currentLed) % (_currentLed / 10 + 1) == 0 ? 255 : 0;
	}
}