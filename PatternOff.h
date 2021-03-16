#pragma once

#include "Pattern.h"


class PatternOff : public Pattern
{
public:
	PatternOff();

	~PatternOff();

	/* override */ void Start();

	/* override */ void Process(uint32_t counter);
};
