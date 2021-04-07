#pragma once

#include "ClassNames.h"
#include HEADER_FILE(MIDI_CLASS)

class Configuration;
class LedStrips;
class MidiKeyboard;
class MidiKeyboards;
class Patterns;

class MidiProcessor
{
public:
	MidiProcessor();

	void Process(Configuration* configuration, MidiKeyboards* midiKeyboards, LedStrips* ledStrips, Patterns* patterns, 
		midi::MidiType midiType, uint8_t midiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2);
	
	void ProcessControlChange(Configuration* configuration, MidiKeyboards* midiKeyboards, LedStrips* ledStrips, Patterns* patterns, 
		uint8_t midiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2);
};
