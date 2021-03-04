#pragma once

#include "SynthLedStripsTypes.h"

class Time
{
public:
	enum class ETime { NA, _10ms, _100ms, _1s };

	int32_t GetTimeInMilliSeconds(ETime time);
};

