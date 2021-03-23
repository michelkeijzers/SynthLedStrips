#include "AssertUtils.h"
#include "MidiKeyboard.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "MidiNote.h"
#include "SynthLedStrips.h"

MidiKeyboard::MidiKeyboard()
: 
	_nrOfKeys(0),
	_keyOffset(0),
	_midiNotes(NULL)
{
}


MidiKeyboard::~MidiKeyboard()
{
	if (_midiNotes != NULL)
	{
		// delete _midiNotes; // Results in exception
	}
}


void MidiKeyboard::SetNrOfKeys(uint8_t nrOfKeys)
{
	_nrOfKeys = nrOfKeys;
	_midiNotes = new MidiNote[nrOfKeys];
	_keyOffset = nrOfKeys == 61 ? 36 : 21; // 36 = C2, 21 = A0
}


MidiNote& MidiKeyboard::GetMidiNote(uint8_t key)
{
	AssertUtils::MyAssert(key < _nrOfKeys);
	return _midiNotes[key];
}


void MidiKeyboard::Process()
{
}


void MidiKeyboard::ProcessMidiNoteOn(midi::DataByte noteNumber, midi::DataByte velocity)
{ 
	Serial.print("MIDI Note on: ");
	Serial.println(noteNumber - _keyOffset);
	MidiNote& midiNote = GetMidiNote(noteNumber - _keyOffset);
	midiNote.ProcessNoteOn(velocity);
}


void MidiKeyboard::ProcessMidiNoteOff(midi::DataByte noteNumber, midi::DataByte releaseVelocity)
{
	Serial.print("MIDI Note off: ");
	Serial.println(noteNumber - _keyOffset);
	MidiNote& midiNote = GetMidiNote(noteNumber - _keyOffset);
	midiNote.ProcessNoteOff(releaseVelocity);
}


void MidiKeyboard::ClearNewFlags()
{
	for (int key = 0; key < _nrOfKeys; key++)
	{
		GetMidiNote(key).ClearStatusChanged();
	}
}


uint8_t MidiKeyboard::GetNrOfKeys()
{
	return _nrOfKeys;
}


uint8_t MidiKeyboard::GetKeyOffset()
{
	return _keyOffset;
}
