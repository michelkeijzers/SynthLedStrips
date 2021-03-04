#include "Speed.h"

int32_t Speed::GetSpeedInMilliSeconds(ESpeed speed)
{
	switch (speed)
	{
	case ESpeed::NA		: return   0;
	case ESpeed::_10ms	: return  10;
	case ESpeed::_100ms	: return 100;
	}
};

