
#ifdef _WINDOWS

#include "MidiStub.h"
#include "MidiInjection.h"
#include "AssertUtils.h"


MidiInjection::MidiInjection()
	: _dataBytesSent(0)
{
}


void MidiInjection::Add(uint32_t time, MidiInterface& midi, midi::MidiType type, midi::DataByte dataByte1)
{
	_data.push_back(time);
	_data.push_back((int) &midi);
	_data.push_back((uint8_t) type);
	_data.push_back(dataByte1);
}


void MidiInjection::Add(uint32_t time, MidiInterface& midi, midi::MidiType type, midi::DataByte dataByte1, midi::DataByte dataByte2)
{
	Add(time, midi, type, dataByte1);
	_data.push_back(dataByte2);
}


void MidiInjection::Inject(uint32_t timeStamp)
{
	while ((_dataBytesSent < _data.size()) && (_data[_dataBytesSent] <= timeStamp))
	{
		MidiInterface*& midi = (MidiInterface*&) _data[_dataBytesSent + 1];
		midi::MidiType type = (midi::MidiType) (_data[_dataBytesSent + 2] & 0xF0);
		uint8_t nrOfDataBytes = MidiInterface::GetNrOfDataBytes(type);
		switch(nrOfDataBytes)
		{
		case 1:
			midi->AddToQueue(type, _data[_dataBytesSent + 3]);
			break;

		case 2:
			midi->AddToQueue(type, _data[_dataBytesSent + 3], _data[_dataBytesSent + 4]);
			break;

		default:
			AssertUtils::MyAssert(false);
		}

		_dataBytesSent += 3 + nrOfDataBytes;
	}
}

#endif // _WINDOWS
