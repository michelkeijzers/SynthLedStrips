#pragma once

#include "ClassNames.h"
#include HEADER_FILE(MIDI_CLASS)

class MidiKeyboard;

class MidiProcessor
{
public:
	MidiProcessor();

	void Process(MidiKeyboard& midiKeyboard, midi::MidiType midiType, midi::DataByte dataByte1, midi::DataByte dataByte2);
};
