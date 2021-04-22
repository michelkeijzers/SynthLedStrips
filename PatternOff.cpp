#include "PatternOff.h"

#include "LedColor.h"
#include "LedStrip.h"


PatternOff::PatternOff()
{
}


/* override */ void PatternOff::Start()
{
	_ledStrip->SetAllLeds(LedColor::EColor::BLACK, 0); // P0: Background color
}


/* override */ void PatternOff::Process()
{
}
