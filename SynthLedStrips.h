#pragma once

#include "LedStrips.h"

class MidiKeyboards;
class Patterns;
class LedStrips;


class SynthLedStrips
{
public:
	SynthLedStrips();
	~SynthLedStrips();

	static void Setup();
	static void Loop();

private:
	static void ProcessMidi();
	static void ProcessMidiEvents(midi::MidiType midiType, midi::DataByte dataByte1, midi::DataByte dataBatye2);
	static void ProcessMidiKeyboards();
	static void ClearNewFlags();

	static void SetPatterns();

	static MidiKeyboards _midiKeyboards;

	static Patterns _patterns;

	static LedStrips _ledStrips;

	static uint32_t _counter;
};
