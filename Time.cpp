#include "Time.h"

#include <stdlib.h>


/* static */ uint32_t Time::GetTime(ETime time)
{
	switch (time)
	{
	case ETime::NA		: return 0xFFFFFFFF;
	case ETime::_10ms	: return    10 / Time::MULTIPLIER;
	case ETime::_20ms	: return    20 / Time::MULTIPLIER;
	case ETime::_40ms	: return    40 / Time::MULTIPLIER;
	case ETime::_70ms	: return    70 / Time::MULTIPLIER;
	case ETime::_100ms	: return   100 / Time::MULTIPLIER;
	case ETime::_200ms	: return   200 / Time::MULTIPLIER;
	case ETime::_400ms	: return   400 / Time::MULTIPLIER;
	case ETime::_700ms	: return   700 / Time::MULTIPLIER;
	case ETime::_1s		: return  1000 / Time::MULTIPLIER;
	case ETime::_2s		: return  2000 / Time::MULTIPLIER;
	case ETime::_4s		: return  4000 / Time::MULTIPLIER;
	case ETime::_7s		: return  7000 / Time::MULTIPLIER;
	case ETime::_10s	: return 10000 / Time::MULTIPLIER;
	case ETime::_20s    : return 20000 / Time::MULTIPLIER;
	case ETime::_30s    : return 30000 / Time::MULTIPLIER;
	case ETime::_1m     : return 60000 / Time::MULTIPLIER;
	default:              exit(0);
	}
};
