#pragma once

#include "SynthLedStripsTypes.h"

#include "ClassNames.h"
#include HEADER_FILE(MIDI_CLASS)

#define NR_OF_CCS 8

class MidiKeyboard
{
public:
	MidiKeyboard(uint8_t midiChannel, uint8_t nrOfKeys);
	~MidiKeyboard();
	
	void ProcessMidiNoteOn(uint8_t midiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2);
	void ProcessMidiNoteOff(uint8_t midiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2);

private:
	uint8_t* _notes;

	uint8_t _midiChannel;

	uint8_t _nrOfKeys;

	uint8_t _ccGroup[NR_OF_CCS];
};

