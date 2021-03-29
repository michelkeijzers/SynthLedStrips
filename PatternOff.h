#pragma once

#include "Pattern.h"

class PatternOff : public Pattern
{
public:
	PatternOff();

	/* override */ void Start();

	/* override */ void Process();
};
