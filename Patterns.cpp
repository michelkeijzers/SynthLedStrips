#include <stdlib.h>
#include "SerialUtils.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "Patterns.h"
#include "PatternOff.h"
#include "PatternKnightRider.h"
#include "PatternMidiNoteOnOff.h"


Patterns::Patterns()
	: _patternData(NULL),
	  _patterns(),
	  _patternDataSize(0)
{
}


Patterns::~Patterns()
{
	if (_patternData != NULL)
	{
		delete _patternData;
	}
}


void Patterns::Initialize()
{
	_patternDataSize = MAX(sizeof(PatternOff), sizeof(PatternKnightRider));
	_patternData = new uint8_t[_patternDataSize * 4];
}


uint8_t* Patterns::GetPatternData(uint8_t index)
{
	return &(_patternData[index * _patternDataSize]);
}


void Patterns::SetPattern(uint8_t index, Pattern* pattern, MidiKeyboard* midiKeyboard, LedStrip* ledStrip)
{
	_patterns[index] = pattern;
	_patterns[index]->Initialize(midiKeyboard, ledStrip);
}


void Patterns::Process()
{
	for (uint8_t index = 0; index < NR_OF_PATTERNS; index++)
	{
		if (_patterns[index] != nullptr)
		{
			_patterns[index]->Process();
		}
	}
}
