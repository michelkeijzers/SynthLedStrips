#ifdef _WINDOWS

#include "MidiStub.h"
#include "AssertUtils.h"
#include "SerialUtils.h"


MidiInterface midiB;
MidiInterface midiC;


MidiInterface::MidiInterface()
:
	_midiType(midi::MidiType::InvalidType),
	_midiChannel(0),
	_data1(0),
	_data2(0)
{
}


void MidiInterface::begin()
{
}


bool MidiInterface::read()
{
	if (_queue.empty())
	{
		return false;
	}
	
	_midiType = (midi::MidiType) (_queue.front() & 0xF0);
	_midiChannel = (_queue.front() & 0x0F) + 1;
	_queue.pop();
	_data1 = _queue.front();
	_queue.pop();
	_data2 = _queue.front();
	_queue.pop();

	return true;
}


midi::MidiType MidiInterface::getType()
{
	return _midiType;
}


uint8_t MidiInterface::getChannel()
{
	return _midiChannel;
}


midi::DataByte MidiInterface::getData1()
{
	return _data1;
}


midi::DataByte MidiInterface::getData2()
{
	return _data2;
}


void MidiInterface::AddToQueue(uint8_t typeAndMidiChannel, midi::DataByte dataByte1)
{
	_queue.push(typeAndMidiChannel);
	_queue.push(dataByte1);
}


void MidiInterface::AddToQueue(uint8_t typeAndMidiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2)
{
	AddToQueue(typeAndMidiChannel, dataByte1);
	Serial.print("\n");
	SerialUtils::PrintInt("AddToQueue TM", typeAndMidiChannel);
	SerialUtils::PrintInt("byte 1", dataByte1);
	SerialUtils::PrintlnInt("byte 2", dataByte2);
	_queue.push(dataByte2);
}


/* static */ uint8_t MidiInterface::GetNrOfDataBytes(midi::MidiType midiType)
{
	switch ((midi::MidiType) ((uint8_t) midiType & 0xF0))
	{
	case midi::MidiType::NoteOff:				// Fall Through
	case midi::MidiType::NoteOn:				// Fall Through
	case midi::MidiType::AfterTouchPoly:		// Fall Through
	case midi::MidiType::ControlChange:			// Fall Through
	case midi::MidiType::PitchBend:
		return 2;

	case midi::MidiType::ProgramChange:			// Fall Through
	case midi::MidiType::AfterTouchChannel:
		return 1;

	case midi::MidiType::InvalidType:			// Fall Through
		AssertUtils::MyAssert(false);
	}

	switch (midiType)
	{
	case midi::MidiType::SystemExclusive:		// Fall Through
	case midi::MidiType::TimeCodeQuarterFrame: 	// Fall Through
	case midi::MidiType::SongPosition:         	// Fall Through
	case midi::MidiType::SongSelect:           	// Fall Through
	case midi::MidiType::Undefined_F4:         	// Fall Through
	case midi::MidiType::Undefined_F5:         	// Fall Through
	case midi::MidiType::TuneRequest:          	// Fall Through
	case midi::MidiType::SystemExclusiveEnd:   	// Fall Through  
	case midi::MidiType::Clock:                	// Fall Through 
	case midi::MidiType::Tick:                 	// Fall Through
	case midi::MidiType::Start:                	// Fall Through
	case midi::MidiType::Continue:             	// Fall Through
	case midi::MidiType::Stop:                	// Fall Through
	case midi::MidiType::Undefined_FD:         	// Fall Through
	case midi::MidiType::ActiveSensing:        	// Fall Through
	case midi::MidiType::SystemReset:
	default:
		// Not supported
		AssertUtils::MyAssert(false);
	}

	return 0;
}

#endif // _WINDOWS
