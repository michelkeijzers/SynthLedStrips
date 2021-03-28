#include "MidiKeyboards.h"


/* static */ MidiKeyboard MidiKeyboards::_midiKeyboards[NR_OF_MIDI_KEYBOARDS];


MidiKeyboards::MidiKeyboards()
{
}


void MidiKeyboards::Initialize()
{
	_midiKeyboards[0].SetNrOfKeys(NR_OF_MAIN_SYNTH_KEYS);
	_midiKeyboards[1].SetNrOfKeys(NR_OF_MASTER_KEYBOARD_KEYS);
}


MidiKeyboard& MidiKeyboards::GetMidiKeyboard(uint8_t index)
{
	return _midiKeyboards[index];
}


void MidiKeyboards::Process()
{
	for (uint8_t midiKeyboard = 0; midiKeyboard < NR_OF_MIDI_KEYBOARDS; midiKeyboard++)
	{
		_midiKeyboards[midiKeyboard].Process();
	}
}


void MidiKeyboards::ClearNewFlags()
{
	for (uint8_t midiKeyboard = 0; midiKeyboard < NR_OF_MIDI_KEYBOARDS; midiKeyboard++)
	{
		_midiKeyboards[midiKeyboard].ClearNewFlags();
	}
}
