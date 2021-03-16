#include "MidiKeyboard.h"

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


MidiKeyboard::MidiKeyboard()
: 
	_nrOfKeys(0),
	_keyOffset(0),
	_keys(NULL),
	_status(NULL)
{
}


MidiKeyboard::~MidiKeyboard()
{
	delete _keys;
	delete _status;
}


void MidiKeyboard::SetNrOfKeys(uint8_t nrOfKeys)
{
	_nrOfKeys = nrOfKeys;
	_keys = new uint8_t[nrOfKeys];
	_status = new uint16_t[nrOfKeys];
	_keyOffset = nrOfKeys == 61 ? 36 : 21; // 36 = C2, 21 = A0

	for (uint8_t key = 0; key < nrOfKeys; key++)
	{
		_keys[key] = 0;
		_status[key] = TIME_AGO_BITS;
	}
}


void MidiKeyboard::Process(uint32_t counter)
{
	for (uint8_t key = 0; key < _nrOfKeys; key++)
	{
		if (counter % NOTE_ON_OFF_PERIOD == 0)
		{
			/*if ((key == 14) && (_nrOfKeys == 61))
			{
				Serial.println("Process key 14, 61 keys");
				Serial.println(TimeAgo(key));
				Serial.println((_times[key] & TIME_AGO_BITS));
			}
			*/
			_status[key] = (_status[key] & NEW_FLAG) + MIN(TIME_AGO_BITS, (_status[key] & TIME_AGO_BITS) + 1);
		}
	}
}


void MidiKeyboard::ProcessMidiNoteOn(midi::DataByte noteNumber, midi::DataByte velocity)
{ 
	Serial.print("MIDI Note on: ");
	Serial.println(noteNumber - _keyOffset);
	_keys[noteNumber - _keyOffset] = PRESSED_FLAG | velocity;
	_status[noteNumber - _keyOffset] = NEW_FLAG;
	Serial.println(TimeAgo(noteNumber - _keyOffset));
}


void MidiKeyboard::ProcessMidiNoteOff(midi::DataByte noteNumber, midi::DataByte releaseVelocity)
{
	Serial.print("MIDI Note off: ");
	Serial.println(noteNumber - _keyOffset);
	_keys[noteNumber - _keyOffset] = releaseVelocity;
	_status[noteNumber - _keyOffset] |= NEW_FLAG;
}


void MidiKeyboard::ClearNewFlags()
{
	//Serial.println("Clear New Flags");
	for (int key = 0; key < _nrOfKeys; key++)
	{
		_status[key] = _status[key] & TIME_AGO_BITS;
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
	return (bool)(_status[keyNumber] & NEW_FLAG);
}


uint16_t MidiKeyboard::TimeAgo(uint8_t keyNumber)
{
	return (_status[keyNumber] & TIME_AGO_BITS) * NOTE_ON_OFF_PERIOD;
}


void MidiKeyboard::SetTimeAgo(uint8_t keyNumber, uint16_t timeAgo)
{
	_status[keyNumber] &= NEW_FLAG;
	_status[keyNumber] |= MIN(timeAgo / NOTE_ON_OFF_PERIOD, TIME_AGO_BITS);
}
