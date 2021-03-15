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

	bool IsAssignedToLed(uint8_t keyNumber);
	void AssignToLed(uint8_t keyNumber);
	void UnassignToLed(uint8_t keyNumber);
	uint8_t GetNrOfKeysAssignedToLeds();
	bool AreNewPressedKeysAssigned();

	uint16_t TimeAgo(uint8_t keyNumber); // 0..4096 in 10 ms (40.96 s)
	void SetTimeAgo(uint8_t keyNumber, uint16_t timeAgo);

private:
	const uint8_t PRESSED_FLAG = 0x80;
	const uint8_t VELOCITY_BITS = 0x7F;
	const uint16_t NEW_FLAG = 0x8000;
	const uint16_t ASSIGNED_TO_LED_FLAG = 0x4000;
	const uint16_t TIME_AGO_BITS = 0x0FFF;

	const uint8_t NOTE_ON_OFF_PERIOD = 10; // 10 ms per note on/off increase time

	uint8_t* _keys;    // Bits: 7     : 1=Pressed (Note On), 0=Released (Note Off)
                       //       6..0  : Velocity (Note On), Release Velocity (Note Off)

	uint16_t* _status; // Bits  15    : 1=New Note On or Note Off
	                   //       14    : Assigned to LED
					   //       13..12: Reserved
					   //       11..0 : Time ago pressed/released (Note On/Off) in 10 ms, max 40.96s

	uint8_t _nrOfKeys;
	uint8_t _keyOffset;

	uint8_t _ccGroup[NR_OF_CCS];
};
