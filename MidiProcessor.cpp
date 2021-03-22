#include "AssertUtils.h"
#include "MidiProcessor.h"
#include "MidiKeyboards.h"


MidiProcessor::MidiProcessor()
{
}


MidiProcessor::~MidiProcessor()
{
}


void MidiProcessor::Process(MidiKeyboard& midiKeyboard, midi::MidiType midiType, midi::DataByte dataByte1, midi::DataByte dataByte2)
{
	switch (midiType)
	{
	case midi::MidiType::NoteOn:
		midiKeyboard.ProcessMidiNoteOn(dataByte1, dataByte2);
		break;

	case midi::MidiType::NoteOff:
		midiKeyboard.ProcessMidiNoteOff(dataByte1, dataByte2);
		break;

	default:
		AssertUtils::MyAssert(false);
	}
}
