#ifdef _WINDOWS


#include "MidiStub.h"


//void MIDI_CREATE_INSTANCE(SerialPort serialType, SerialClass serialNumberType, Midi name)
//{
//}



Midi midiA;
Midi midiB;
Midi midiC;
Midi midiD;


Midi::Midi()
:
	_midiType(midi::MidiType::InvalidType),
	_midiChannel(0),
	_data1(0),
	_data2(0)
{
}


Midi::~Midi()
{
}


void Midi::begin()
{
}


bool Midi::read()
{
	if (_queue.empty())
	{
		return false;
	}
	
	_midiType = (midi::MidiType) (_queue.front() & 0xF0);
	_midiChannel = _queue.front() & 0x0F;
	_queue.pop();
	_data1 = _queue.front();
	_queue.pop();
	_data2 = _queue.front();
	_queue.pop();

	return true;
}


midi::MidiType Midi::getType()
{
	return _midiType;;
}


midi::DataByte Midi::getData1()
{
	return _data1;
}


midi::DataByte Midi::getData2()
{
	return _data2;
}


void Midi::AddToQueue(midi::MidiType type, midi::DataByte dataByte1)
{
	_queue.push((uint8_t) type);
	_queue.push(dataByte1);
}


void Midi::AddToQueue(midi::MidiType type, midi::DataByte dataByte1, midi::DataByte dataByte2)
{
	AddToQueue(type, dataByte1);
	_queue.push(dataByte2);
}


/* static */ uint8_t Midi::GetNrOfDataBytes(midi::MidiType midiType)
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
		exit(0);
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
		exit(0);
	}

	return 0;
}

#endif // _WINDOWS
