#include "MidiNote.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


MidiNote::MidiNote()
:
 _isPressed(false),
	_hasStatusChanged(false),
	_velocity(0),
	_releaseVelocity(0),
	_timePressed(UINT32_MAX),
	_timeReleased(UINT32_MAX)
{
}


MidiNote::~MidiNote()
{
}


bool MidiNote::HasStatusChanged()
{
	return _hasStatusChanged;
}


bool MidiNote::IsPressed()
{
	return _isPressed;
}


uint8_t MidiNote::GetVelocity()
{
	return _velocity;
}


uint8_t MidiNote::GetReleaseVelocity()
{
	return _releaseVelocity;
}


uint32_t MidiNote::GetTimePressed()
{
	return _timePressed;
}


uint32_t MidiNote::GetTimeReleased()
{
	return _timeReleased;
}


void MidiNote::ProcessNoteOn(uint8_t velocity)
{
	_isPressed = true;
	_hasStatusChanged = true;
	_timePressed = millis();
	_velocity = velocity;
}


void MidiNote::ProcessNoteOff(uint8_t releaseVelocity)
{
	_isPressed = false;
	_hasStatusChanged = false;
	_timeReleased = millis();
	_releaseVelocity = releaseVelocity;
}


void MidiNote::ClearStatusChanged()
{
	_hasStatusChanged = false;
}
