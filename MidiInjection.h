#pragma once

#ifdef _WINDOWS

#include "MidiStub.h"

class MidiInjection
{
public:
	MidiInjection();
	~MidiInjection();

	void Add(uint32_t time, Midi& midi, midi::MidiType type, midi::DataByte dataByte1);
	void Add(uint32_t time, Midi& midi, midi::MidiType type, midi::DataByte dataByte1, midi::DataByte dataByte2);

	void Inject(uint32_t counter);

private:
	std::vector<uint32_t> _data;
	uint16_t _dataBytesSent;
};

#endif // _WINDOWS
