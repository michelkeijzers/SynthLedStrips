#include "MidiInjection.h"

MidiInjection::MidiInjection()
	: _dataBytesSent(0)
{
}


MidiInjection::~MidiInjection()
{
}


void MidiInjection::Add(uint32_t time, Midi& midi, MidiType type, DataByte dataByte1)
{
	_data.push_back(time);
	_data.push_back((int) &midi);
	_data.push_back(type);
	_data.push_back(dataByte1);
}


void MidiInjection::Add(uint32_t time, Midi& midi, MidiType type, DataByte dataByte1, DataByte dataByte2)
{
	Add(time, midi, type, dataByte1);
	_data.push_back(dataByte2);
}


void MidiInjection::Inject(uint32_t counter)
{
	while ((_dataBytesSent < _data.size()) && (_data[_dataBytesSent] <= counter))
	{
		Midi*& midi = (Midi*&) _data[_dataBytesSent + 1];
		MidiType type = (MidiType) (_data[_dataBytesSent + 2] & 0xF0);
		uint8_t nrOfDataBytes = Midi::GetNrOfDataBytes(type);
		switch(nrOfDataBytes)
		{
		case 1:
			midi->AddToQueue(type, _data[_dataBytesSent + 3]);
			break;

		case 2:
			midi->AddToQueue(type, _data[_dataBytesSent + 3], _data[_dataBytesSent + 4]);
			break;

		default:
			exit(0);
		}

		_dataBytesSent += 3 + nrOfDataBytes;
	}
}