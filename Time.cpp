#include "Time.h"

int32_t Time::GetTimeInMilliSeconds(ETime time)
{
	switch (time)
	{
	case ETime::NA		: return   0;
	case ETime::_10ms	: return  10;
	case ETime::_100ms	: return 100;
	}
};

