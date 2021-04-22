#pragma once

// see configuration.txt

#include <cstdint>
#include "ClassNames.h"
#include HEADER_FILE(SPIFFS_CLASS)

class MidiKeyboard;
class MidiKeyboards;
class LedStrip;
class LedStrips;
class Patterns;
class PatternKnightRider;
class PatternMidiNoteOnOff;
class PatternSplits;

class Configuration
{
public:
	Configuration();

	void OpenFile();

	void SetPatterns(MidiKeyboards* midiKeyboards, LedStrips* ledStrips, Patterns& patterns, uint8_t configurationIndex);

private:
	enum class EPatternType: uint8_t
	{
		Off,
		KnightRider,
		MidiNoteOnOff,
		Splits
	};

	void SetPattern(MidiKeyboard* midiKeyboard, LedStrip* ledStrip, 
		Patterns& patterns, uint8_t patternIndex, uint16_t* fileOffset, EPatternType pattern);

	void ReadKnightRiderProperties(PatternKnightRider* pattern, uint16_t* fileOffset);
	void ReadMidiNoteOnOffProperties(PatternMidiNoteOnOff* pattern, uint16_t* fileOffset);
	void ReadSplitsProperties(PatternSplits* pattern, uint16_t* fileOffset);

	uint8_t ReadNextByte(uint16_t* fileOffset);
	uint16_t ReadNext2Bytes(uint16_t* fileOffset);

	FILE* _file;
};

