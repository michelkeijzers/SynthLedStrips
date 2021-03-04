#pragma once

#include "SynthLedStripsTypes.h"

#include "ClassNames.h"
#include HEADER_FILE(MIDI_CLASS)

#define NR_OF_CCS 8

class MidiKeyboard
{
public:
	MidiKeyboard(uint8_t nrOfKeys);
	~MidiKeyboard();
	
	void ProcessMidiNoteOn(midi::DataByte noteNumber, midi::DataByte velocity);
	void ProcessMidiNoteOff(midi::DataByte noteNumber);

	void ClearNewFlags();

	uint8_t GetNrOfKeys();
	uint8_t GetKeyOffset();
	uint8_t GetKey(uint8_t keyNumber);

private:
	uint8_t* _keys;

	uint8_t _nrOfKeys;
	uint8_t _keyOffset;

	uint8_t _ccGroup[NR_OF_CCS];
};

