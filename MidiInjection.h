#pragma once

#ifdef _WINDOWS

#include "MidiStub.h"

class MidiInjection
{
public:
	MidiInjection();

	void AddControlChange(uint32_t time, MidiInterface* midiInterface, uint8_t midiChannel, uint8_t controlChangeNumber, uint8_t value);
	void AddNoteOn(uint32_t time, MidiInterface* midiInterface,uint8_t midiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2);
	void AddNoteOff(uint32_t time, MidiInterface* midiInterface,uint8_t midiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2);

	void Inject(uint32_t timeStamp);

private:
	void Push(uint32_t time, MidiInterface* midiInterface, uint8_t midiChannel, uint8_t type, uint8_t dataByte1, uint8_t dataByte2);

	std::vector<uint32_t> _data;
	uint16_t _dataBytesSent;
};

#endif // _WINDOWS
