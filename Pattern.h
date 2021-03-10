#pragma once

#include "LedColor.h"
#include "SynthLedStripsTypes.h"


class LedStrip;


class Pattern
{
public:
	Pattern(LedStrip& ledStrip);

	~Pattern();

	virtual void Start() = 0;

	virtual void Process(uint32_t counter) = 0;

protected:
	LedStrip& _ledStrip;
};
