#include "Speed.h"

/* static */ int32_t Speed::GetSpeedInMilliSeconds(ESpeed speed)
{
	switch (speed)
	{
	case ESpeed::NA			: return      0;

	case ESpeed::_minus1ms	: return     -1;
	case ESpeed::_minus2ms	: return     -2;
	case ESpeed::_minus4ms	: return     -4;
	case ESpeed::_minus7ms	: return     -7;
	case ESpeed::_minus10ms	: return    -10;
	case ESpeed::_minus20ms	: return    -20;
	case ESpeed::_minus40ms	: return    -40;
	case ESpeed::_minus70ms	: return    -70;
	case ESpeed::_minus100ms: return   -100;
	case ESpeed::_minus200ms: return   -200;
	case ESpeed::_minus400ms: return   -400;
	case ESpeed::_minus700ms: return   -700;
	case ESpeed::_minus1s	: return  -1000;
	case ESpeed::_minus2s	: return  -2000;
	case ESpeed::_minus4s	: return  -4000;
	case ESpeed::_minus7s	: return  -7000;
	case ESpeed::_minus10s	: return -10000;

	case ESpeed::_1ms		: return      1;
	case ESpeed::_2ms		: return      2;
	case ESpeed::_4ms		: return      4;
	case ESpeed::_7ms		: return      7;
	case ESpeed::_10ms		: return     10;
	case ESpeed::_20ms		: return     20;
	case ESpeed::_40ms		: return     40;
	case ESpeed::_70ms		: return     70;
	case ESpeed::_100ms		: return    100;
	case ESpeed::_200ms		: return    200;
	case ESpeed::_400ms		: return    400;
	case ESpeed::_700ms		: return    700;
	case ESpeed::_1s		: return   1000;
	case ESpeed::_2s		: return   2000;
	case ESpeed::_4s		: return   4000;
	case ESpeed::_7s		: return   7000;
	case ESpeed::_10s		: return  10000;
	}
};
