#pragma once

#include "LedStrips.h"

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

private:
	static void ProcessMidi();

	static void SetPatterns();

	static MidiProcessor _midiProcessor;

	static MidiKeyboards _midiKeyboards;

	static Patterns _patterns;

	static LedStrips _ledStrips;
};
