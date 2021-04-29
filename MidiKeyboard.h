#pragma once

#include "ClassNames.h"
#include HEADER_FILE(MIDI_CLASS)

#define NR_OF_CCS 8

class MidiNote;

class MidiKeyboard
{
public:
	MidiKeyboard();
	~MidiKeyboard();
	
	void SetNrOfKeys(uint8_t nrOfKeys);

	void Process();
	void ProcessMidiNoteOn(midi::DataByte noteNumber, midi::DataByte velocity);
	void ProcessMidiNoteOff(midi::DataByte noteNumber, midi::DataByte releaseVelocity);

	void ClearNewFlags();

	uint8_t GetNrOfKeys();
	uint8_t GetKeyOffset();

	MidiNote& GetMidiNote(uint8_t key);

	void DebugPrint();

private:
	MidiNote* _midiNotes;

	uint8_t _nrOfKeys;
	uint8_t _keyOffset;

	uint8_t _ccGroup[NR_OF_CCS];
};
