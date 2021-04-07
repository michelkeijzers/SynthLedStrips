
#ifdef _WINDOWS

#include "MidiStub.h"
#include "MidiInjection.h"
#include "AssertUtils.h"


MidiInjection::MidiInjection()
	: _dataBytesSent(0)
{
}


void MidiInjection::AddControlChange(
	uint32_t time, MidiInterface* midiInterface, uint8_t midiChannel, uint8_t controlChangeNumber, uint8_t value)
{
	Push(time, midiInterface, midiChannel, (uint8_t) midi::MidiType::ControlChange, controlChangeNumber, value);
}


void MidiInjection::AddNoteOn(
	uint32_t time, MidiInterface* midiInterface, uint8_t midiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2)
{
	Push(time, midiInterface, midiChannel, (uint8_t) midi::MidiType::NoteOn, dataByte1, dataByte2);
}


void MidiInjection::AddNoteOff(
	uint32_t time, MidiInterface* midiInterface,uint8_t midiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2)
{
	Push(time, midiInterface, midiChannel, (uint8_t) midi::MidiType::NoteOff, dataByte1, dataByte2);
}


void MidiInjection::Inject(uint32_t timeStamp)
{
	while ((_dataBytesSent < _data.size()) && (_data[_dataBytesSent] <= timeStamp))
	{
		MidiInterface*& midiInterface = (MidiInterface*&) _data[_dataBytesSent + 1];
		uint8_t midiChannel = _data[_dataBytesSent + 2] - 1;
		midi::MidiType type = (midi::MidiType) (_data[_dataBytesSent + 3]);
		uint8_t nrOfDataBytes = MidiInterface::GetNrOfDataBytes(type);
		switch(nrOfDataBytes)
		{
		case 1:
			midiInterface->AddToQueue((uint8_t) type | midiChannel, _data[_dataBytesSent + 4]);
			break;

		case 2:
			midiInterface->AddToQueue((uint8_t) type | midiChannel, _data[_dataBytesSent + 4], _data[_dataBytesSent + 5]);
			break;

		default:
			AssertUtils::MyAssert(false);
		}

		_dataBytesSent += 4 + nrOfDataBytes;
	}
}


void MidiInjection::Push(
	uint32_t time, MidiInterface* midiInterface, uint8_t midiChannel, uint8_t type, uint8_t dataByte1, uint8_t dataByte2)
{
	_data.push_back(time);
	_data.push_back((uint32_t) midiInterface);
	_data.push_back(midiChannel);
	_data.push_back((uint8_t) type);
	_data.push_back(dataByte1);
	_data.push_back(dataByte2);
}

#endif // _WINDOWS
