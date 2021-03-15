#include "Speed.h"
#include "Time.h"

#include <stdlib.h>


/* static */ int32_t Speed::GetSpeed(ESpeed speed)
{
	switch (speed)
	{
	case ESpeed::NA			: return      0 / Time::MULTIPLIER;
	case ESpeed::_minus10ms	: return    -10 / Time::MULTIPLIER;
	case ESpeed::_minus20ms	: return    -20 / Time::MULTIPLIER;
	case ESpeed::_minus40ms	: return    -40 / Time::MULTIPLIER;
	case ESpeed::_minus70ms	: return    -70 / Time::MULTIPLIER;
	case ESpeed::_minus100ms: return   -100 / Time::MULTIPLIER;
	case ESpeed::_minus200ms: return   -200 / Time::MULTIPLIER;
	case ESpeed::_minus400ms: return   -400 / Time::MULTIPLIER;
	case ESpeed::_minus700ms: return   -700 / Time::MULTIPLIER;
	case ESpeed::_minus1s	: return  -1000 / Time::MULTIPLIER;
	case ESpeed::_minus2s	: return  -2000 / Time::MULTIPLIER;
	case ESpeed::_minus4s	: return  -4000 / Time::MULTIPLIER;
	case ESpeed::_minus7s	: return  -7000 / Time::MULTIPLIER;
	case ESpeed::_minus10s	: return -10000 / Time::MULTIPLIER;
	case ESpeed::_minus20s	: return -10000 / Time::MULTIPLIER;
	case ESpeed::_minus30s	: return -30000 / Time::MULTIPLIER;
	case ESpeed::_minus1m 	: return -60000 / Time::MULTIPLIER;

	case ESpeed::_10ms		: return     10 / Time::MULTIPLIER;
	case ESpeed::_20ms		: return     20 / Time::MULTIPLIER;
	case ESpeed::_40ms		: return     40 / Time::MULTIPLIER;
	case ESpeed::_70ms		: return     70 / Time::MULTIPLIER;
	case ESpeed::_100ms		: return    100 / Time::MULTIPLIER;
	case ESpeed::_200ms		: return    200 / Time::MULTIPLIER;
	case ESpeed::_400ms		: return    400 / Time::MULTIPLIER;
	case ESpeed::_700ms		: return    700 / Time::MULTIPLIER;
	case ESpeed::_1s		: return   1000 / Time::MULTIPLIER;
	case ESpeed::_2s		: return   2000 / Time::MULTIPLIER;
	case ESpeed::_4s		: return   4000 / Time::MULTIPLIER;
	case ESpeed::_7s		: return   7000 / Time::MULTIPLIER;
	case ESpeed::_10s		: return  10000 / Time::MULTIPLIER;
	case ESpeed::_20s		: return  20000 / Time::MULTIPLIER;
	case ESpeed::_30s		: return  30000 / Time::MULTIPLIER;
	case ESpeed::_1m 		: return  60000 / Time::MULTIPLIER;
	default                 : exit(0);
	}
};
