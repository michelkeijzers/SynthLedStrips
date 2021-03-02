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
	_midiType(InvalidType),
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
	
	_midiType = (MidiType) (_queue.front() & 0xF0);
	_midiChannel = _queue.front() & 0x0F;
	_queue.pop();
	_data1 = _queue.front();
	_queue.pop();
	_data2 = _queue.front();
	_queue.pop();
}


MidiType Midi::getType()
{
	return _midiType;;
}


DataByte Midi::getData1()
{
	return _data1;
}


DataByte Midi::getData2()
{
	return _data2;
}


void Midi::AddToQueue(MidiType type, DataByte dataByte1)
{
	_queue.push(type);
	_queue.push(dataByte1);
}


void Midi::AddToQueue(MidiType type, DataByte dataByte1, DataByte dataByte2)
{
	AddToQueue(type, dataByte1);
	_queue.push(dataByte2);
}


/* static */ uint8_t Midi::GetNrOfDataBytes(MidiType midiType)
{
	switch (midiType & 0xF0)
	{
	case NoteOff:				// Fall Through
	case NoteOn:				// Fall Through
	case AfterTouchPoly:		// Fall Through
	case ControlChange:			// Fall Through
	case PitchBend:
		return 2;

	case ProgramChange:			// Fall Through
	case AfterTouchChannel:
		return 1;

	case InvalidType:			// Fall Through
		exit(0);
	}

	switch (midiType)
	{
	case SystemExclusive:		// Fall Through
	case TimeCodeQuarterFrame: 	// Fall Through
	case SongPosition:         	// Fall Through
	case SongSelect:           	// Fall Through
	case Undefined_F4:         	// Fall Through
	case Undefined_F5:         	// Fall Through
	case TuneRequest:          	// Fall Through
	case SystemExclusiveEnd:   	// Fall Through  
	case Clock:                	// Fall Through 
	case Tick:                 	// Fall Through
	case Start:                	// Fall Through
	case Continue:             	// Fall Through
	case Stop:                	// Fall Through
	case Undefined_FD:         	// Fall Through
	case ActiveSensing:        	// Fall Through
	case SystemReset:
	default:
		// Not supported
		exit(0);
	}

	return 0;
}

#endif // _WINDOWS
