#include "MidiKeyboard.h"


MidiKeyboard::MidiKeyboard(uint8_t midiChannel, uint8_t nrOfKeys)
: 
	_midiChannel(midiChannel),
	_nrOfKeys(nrOfKeys)
{
	_notes = new uint8_t[nrOfKeys];
}


MidiKeyboard::~MidiKeyboard()
{
	delete _notes;
}


void MidiKeyboard::ProcessMidiNoteOn(uint8_t midiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2)
{ 

	
}


void MidiKeyboard::ProcessMidiNoteOff(uint8_t midiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2)
{
	

}