#pragma once

#include "LedStrips.h"

class Configuration;
class MidiKeyboard;
class MidiKeyboards;
class Patterns;
class LedStrips;
class MidiProcessor;

class SynthLedStrips
{
public:
	SynthLedStrips();
	~SynthLedStrips();

	static void Setup();
	static void Loop();

	static MidiKeyboard& GetMidiKeyboards(uint8_t index);

private:
	static void ProcessMidi();

	static void SetPatterns();

	static Configuration _configuration;

	static MidiProcessor _midiProcessor;

	static MidiKeyboards _midiKeyboards;

	static Patterns _patterns;

	static LedStrips _ledStrips;
};
