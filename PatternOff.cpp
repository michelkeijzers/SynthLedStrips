#include "PatternOff.h"

#include "LedColor.h"
#include "LedStrip.h"


PatternOff::PatternOff(LedStrip& ledStrip)
	: Pattern(ledStrip)
{
}


PatternOff::~PatternOff()
{
}


/* override */ void PatternOff::Start()
{
	_ledStrip.SetAllLeds(LedColor::EColor::Black, 0); // P0: Background color
}


/* override */ void PatternOff::Process(uint32_t counter)
{
}
