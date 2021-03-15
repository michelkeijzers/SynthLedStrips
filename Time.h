#pragma once

#include "SynthLedStripsTypes.h"

class Time
{
public:
	static const uint8_t MULTIPLIER = 10;

	enum class ETime { NA, _10ms, _20ms, _40ms, _70ms, _100ms, _200ms, _400ms, _700ms, _1s, _2s, _4s, _7s, _10s, _20s, _30s, _1m };

	static uint32_t GetTime(ETime time);
};
