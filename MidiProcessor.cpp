#include "MidiProcessor.h"


MidiProcessor::MidiProcessor()
{
}


MidiProcessor::~MidiProcessor()
{
}


void MidiProcessor::SetMidiB(MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>* midiB)
{
	_midiB = midiB;
}


void MidiProcessor::Process()
{

}