#pragma once

#include "SynthLedStripsTypes.h"

class Speed
{
public:
	enum class ESpeed { NA, _10ms, _100ms, _1s };

	int32_t GetSpeedInMilliSeconds(ESpeed speed);
};

