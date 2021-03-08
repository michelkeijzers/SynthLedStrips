#pragma once

#include "SynthLedStripsTypes.h"

#include "ClassNames.h"
#include HEADER_FILE(MIDI_CLASS)

#define NR_OF_CCS 8

class MidiKeyboard
{
public:
	MidiKeyboard();
	~MidiKeyboard();
	
	void SetNrOfKeys(uint8_t nrOfKeys);

	void Process(uint32_t counter);
	void ProcessMidiNoteOn(midi::DataByte noteNumber, midi::DataByte velocity);
	void ProcessMidiNoteOff(midi::DataByte noteNumber, midi::DataByte releaseVelocity);

	void ClearNewFlags();

	uint8_t GetNrOfKeys();
	uint8_t GetKeyOffset();
	bool IsPressed(uint8_t keyNumber);
	uint8_t GetVelocity(uint8_t keyNumber); // Returns velocity or release velocity
	bool IsNew(uint8_t keyNumber);
	uint16_t TimeAgo(uint8_t keyNumber); // 0..32767 ms (32.767 s, 15 bits)

private:
	const uint8_t PRESSED_FLAG = 0x80;
	const uint8_t VELOCITY_BITS = 0x7F;
	const uint16_t NEW_FLAG = 0x8000;
	const uint16_t TIME_AGO_BITS = 0x7FFF;

	const uint8_t NOTE_ON_OFF_PERIOD = 10; // 10 ms per note on/off increase time

	uint8_t* _keys; // MSB: Pressed/Released, LSB 7 bits: Velocity / Release Velocity
	uint16_t* _times; // MSB: New, LSB 7 bits: Time ago pressed/released

	uint8_t _nrOfKeys;
	uint8_t _keyOffset;

	uint8_t _ccGroup[NR_OF_CCS];
};

