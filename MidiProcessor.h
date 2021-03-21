#pragma once

#include "ClassNames.h"
#include HEADER_FILE(MIDI_CLASS)


class MidiProcessor
{
public:
	MidiProcessor();
	~MidiProcessor();

	void SetMidiB(MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>* midi);

	void Process();

private:
	MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>* _midiB;
};

