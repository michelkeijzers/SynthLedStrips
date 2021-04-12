#pragma once

// see configuration.txt

#include <cstdint>
#include "ClassNames.h"
#include HEADER_FILE(SPIFFS_CLASS)

class Patterns;
class LedStrips;

class Configuration
{
public:
	Configuration();

	void OpenFile();

	void SetPatterns(Patterns* patterns, uint8_t configurationIndex);

	void SetSplits(LedStrips* ledStrips, uint8_t configurationIndex);

private:
	FILE* _file;
};

