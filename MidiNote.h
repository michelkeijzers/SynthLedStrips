#pragma once

class MidiNote
{
public:
	MidiNote();
	
	bool HasStatusChanged();
	bool IsPressed();
	uint8_t GetVelocity();
	uint8_t GetReleaseVelocity();
	uint32_t GetTimePressed();
	uint32_t GetTimeReleased();

	void ProcessNoteOn(uint8_t velocity);
	void ProcessNoteOff(uint8_t releaseVelocity);
	
	void ClearStatusChanged();

private:
	bool _isPressed;
	bool _hasStatusChanged;

	uint8_t _velocity;
	uint8_t _releaseVelocity;

	uint32_t _timePressed;;
	uint32_t _timeReleased;
};
