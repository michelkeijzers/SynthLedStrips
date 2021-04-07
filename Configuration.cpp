#include <cstdint>

#include "ClassNames.h"
#include HEADER_FILE(SPIFFS_CLASS)

#include "Configuration.h"
#include "LedStrips.h"
#include "Patterns.h"


Configuration::Configuration()
{
}

void Configuration::SetPatterns(Patterns* patterns, uint8_t configurationIndex)
{
	/*TODO*/
}


void Configuration::SetSplits(LedStrips* ledStrips, uint8_t configurationIndex)
{
	/*TODO*/
}
