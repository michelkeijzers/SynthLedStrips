#include "MidiKeyboard.h"
#include "MathUtils.h"

MidiKeyboard::MidiKeyboard()
: 
	_nrOfKeys(0),
	_keyOffset(0),
	_keys(NULL),
	_times(NULL)
{
}


MidiKeyboard::~MidiKeyboard()
{
	delete _keys;
	delete _times;
}


void MidiKeyboard::SetNrOfKeys(uint8_t nrOfKeys)
{
	_nrOfKeys = nrOfKeys;
	_keys = new uint8_t[nrOfKeys];
	_times = new uint16_t[nrOfKeys];
	_keyOffset = nrOfKeys == 61 ? 36 : 21; // 36 = C2, 21 = A0

	for (uint8_t key = 0; key < nrOfKeys; key++)
	{
		_keys[key] = 0;
	}
}


void MidiKeyboard::Process(uint32_t counter)
{
	for (uint8_t key = 0; key < _nrOfKeys; key++)
	{
		if (counter % NOTE_ON_OFF_PERIOD == 0)
		{
			_times[key] = (_times[key] & NEW_FLAG) + MathUtils::Min(TIME_AGO_BITS, (_times[key] & TIME_AGO_BITS) + 1);
		}
	}
}


void MidiKeyboard::ProcessMidiNoteOn(midi::DataByte noteNumber, midi::DataByte velocity)
{ 
	Serial.println("MIDI Note on");
	Serial.println(noteNumber - _keyOffset);
	_keys[noteNumber - _keyOffset] = PRESSED_FLAG | velocity;
	_times[noteNumber - _keyOffset] = NEW_FLAG;
}


void MidiKeyboard::ProcessMidiNoteOff(midi::DataByte noteNumber, midi::DataByte releaseVelocity)
{
	_keys[noteNumber - _keyOffset] = releaseVelocity;
	_times[noteNumber - _keyOffset] = NEW_FLAG;
}


void MidiKeyboard::ClearNewFlags()
{
	//Serial.println("Clear New Flags");
	for (int key = 0; key < _nrOfKeys; key++)
	{
		_times[key] = _times[key] & TIME_AGO_BITS;
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


bool MidiKeyboard::IsPressed(uint8_t keyNumber)
{
	return (bool)(_keys[keyNumber] & PRESSED_FLAG);
}


uint8_t MidiKeyboard::GetVelocity(uint8_t keyNumber)
{
	return _keys[keyNumber] & VELOCITY_BITS;
}



bool MidiKeyboard::IsNew(uint8_t keyNumber)
{
	return (bool)(_times[keyNumber] & NEW_FLAG);
}


uint16_t MidiKeyboard::TimeAgo(uint8_t keyNumber)
{
	return (_times[keyNumber] & TIME_AGO_BITS) * NOTE_ON_OFF_PERIOD;
}
