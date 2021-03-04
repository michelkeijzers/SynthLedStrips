#include "MidiKeyboard.h"


MidiKeyboard::MidiKeyboard(uint8_t nrOfKeys)
: 
	_nrOfKeys(nrOfKeys)
{
	_keys = new uint8_t[nrOfKeys];
	_keyOffset = nrOfKeys == 61 ? 36 : 21; // 36 = C2, 21 = A0

	for (uint8_t key = 0; key < nrOfKeys; key++)
	{
		_keys[key] = 0;
	}
}


MidiKeyboard::~MidiKeyboard()
{
	delete _keys;
}


void MidiKeyboard::ProcessMidiNoteOn(midi::DataByte noteNumber, midi::DataByte velocity)
{ 
	_keys[noteNumber - _keyOffset] = 0x80 | velocity;  // 0x80 means new
}


void MidiKeyboard::ProcessMidiNoteOff(midi::DataByte noteNumber)
{
	_keys[noteNumber - _keyOffset] = 0;
}


void MidiKeyboard::ClearNewFlags()
{
	for (int key = 0; key < _nrOfKeys - _keyOffset; key++)
	{
		_keys[key] = _keys[key] & 0x7F;
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


uint8_t MidiKeyboard::GetKey(uint8_t keyNumber)
{
	return _keys[keyNumber];
}
