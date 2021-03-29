#ifdef _WINDOWS

#include "FastLedStub.h"

CFastLED FastLED;

/* static */ struct FastLedCRGB* CFastLED::_data[MAX_NR_OF_LED_STRIPS];
/* static */ int CFastLED::_pinNumbers[MAX_NR_OF_LED_STRIPS];
/* static */ int CFastLED::_nrOfUsedLeds[MAX_NR_OF_LED_STRIPS];
///* static */ int CFastLED::_nLedsOrOffset[MAX_NR_OF_LED_STRIPS];
/* static */ int CFastLED::_nrOfLedStrips = 0;
/* static */ bool CFastLED::_showEnabled = false;

CFastLED::CFastLED()
{
}


/* static */ struct FastLedCRGB* CFastLED::GetData(int ledStrip) 
{
	_showEnabled = false;
	return _data[ledStrip]; 
}


/* static */ int CFastLED::GetPinNumber(int ledStrip) { return _pinNumbers[ledStrip]; }


/* static */ int CFastLED::GetNrOfUsedLeds(int ledStrip) { return _nrOfUsedLeds[ledStrip]; }


/* static */ int CFastLED::GetNrOfLedStrips() { return _nrOfLedStrips; }


/* static */ bool CFastLED::IsShowEnabled() { return _showEnabled; }


/* static */ CLEDController& CFastLED::addLeds(CLEDController* pLed, struct FastLedCRGB* data, int nLedsOrOffset, int nLedsIfOffset /* = 0 */)
{
	_data[_nrOfLedStrips] = data;
	_nrOfUsedLeds[_nrOfLedStrips] = nLedsOrOffset;
	_nrOfLedStrips++;

	return *new CLEDController();
}


/* static */ void CFastLED::show()
{
	_showEnabled = true;
}

#endif // _WINDOWS
