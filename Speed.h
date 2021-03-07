#pragma once

#include "SynthLedStripsTypes.h"

class Speed
{
public:
	enum class ESpeed { NA, 
		_minus1ms, _minus2ms, _minus4ms, _minus7ms, _minus10ms, _minus20ms, _minus40ms, _minus70ms, _minus100ms,
		_minus200ms, _minus400ms, _minus700ms, _minus1s, _minus2s, _minus4s, _minus7s, _minus10s,
		_1ms, _2ms, _4ms, _7ms, _10ms, _20ms, _40ms, _70ms, _100ms, _200ms, _400ms, _700ms, _1s, _2s, _4s, _7s, _10s };

	int32_t GetSpeedInMilliSeconds(ESpeed speed);
};

