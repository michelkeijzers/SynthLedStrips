#pragma once

#include "SynthLedStripsTypes.h"

class Speed
{
public:
	enum class ESpeed { NA, 
		_minus10ms, _minus20ms, _minus40ms, _minus70ms, _minus100ms, _minus200ms, _minus400ms, _minus700ms, 
		_minus1s, _minus2s, _minus4s, _minus7s, _minus10s, _minus20s, _minus30s, _minus1m,
		_10ms, _20ms, _40ms, _70ms, _100ms, _200ms, _400ms, _700ms, 
		_1s, _2s, _4s, _7s, _10s, _20s, _30s, _1m};

	static int32_t GetSpeed(ESpeed speed);
};
