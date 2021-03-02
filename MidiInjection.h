#pragma once

#include "ClassNames.h"
#include HEADER_FILE(MIDI_CLASS)

class MidiInjection
{
public:
	MidiInjection();
	~MidiInjection();

	void Add(uint32_t time, Midi& midi, MidiType type, DataByte dataByte1);
	void Add(uint32_t time, Midi& midi, MidiType type, DataByte dataByte1, DataByte dataByte2);

	void Inject(uint32_t counter);

private:
	std::vector<uint32_t> _data;
	uint16_t _dataBytesSent;
};

