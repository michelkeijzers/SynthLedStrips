#pragma once

#include "SynthLedStripsTypes.h"

class Time
{
public:
	enum class ETime { NA, _1ms, _2ms, _4ms, _7ms, _10ms, _20ms, _40ms, _70ms, _100ms, _200ms, _400ms, _700ms, _1s, _2s, _4s, _7s, _10s };

	uint32_t GetTimeInMilliSeconds(ETime time);
};

