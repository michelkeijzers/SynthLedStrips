#include "Time.h"

uint32_t Time::GetTimeInMilliSeconds(ETime time)
{
	switch (time)
	{
	case ETime::NA		: return     0;
	case ETime::_1ms	: return     1;
	case ETime::_2ms	: return     2;
	case ETime::_4ms	: return     4;
	case ETime::_7ms	: return     7;
	case ETime::_10ms	: return    10;
	case ETime::_20ms	: return    20;
	case ETime::_40ms	: return    40;
	case ETime::_70ms	: return    70;
	case ETime::_100ms	: return   100;
	case ETime::_200ms	: return   200;
	case ETime::_400ms	: return   400;
	case ETime::_700ms	: return   700;
	case ETime::_1s		: return  1000;
	case ETime::_2s		: return  2000;
	case ETime::_4s		: return  4000;
	case ETime::_7s		: return  7000;
	case ETime::_10s	: return 10000;
	}
};

