#pragma once

#include "Pattern.h"


class PatternOff : public Pattern
{
public:
	PatternOff(LedStrip& ledStrip);

	~PatternOff();

	/* override */ void Start();

	/* override */ void Process(uint32_t counter);
};

