#pragma once

// see configuration.txt

#include <cstdint>

class Patterns;
class LedStrips;

class Configuration
{
public:
	Configuration();

	void SetPatterns(Patterns* patterns, uint8_t configurationIndex);

	void SetSplits(LedStrips* ledStrips, uint8_t configurationIndex);
};

