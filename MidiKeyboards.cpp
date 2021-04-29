#include "MidiKeyboards.h"
#include "SerialUtils.h"


/* static */ MidiKeyboard MidiKeyboards::_keyboards[NR_OF_MIDI_KEYBOARDS];


MidiKeyboards::MidiKeyboards()
{
}


void MidiKeyboards::Initialize()
{
	_keyboards[0].SetNrOfKeys(NR_OF_KEYBOARD_1_KEYS);
	_keyboards[1].SetNrOfKeys(NR_OF_KEYBOARD_2_KEYS);
}


MidiKeyboard& MidiKeyboards::GetMidiKeyboard(uint8_t index)
{
	return _keyboards[index];
}


void MidiKeyboards::Process()
{
	for (uint8_t midiKeyboard = 0; midiKeyboard < NR_OF_MIDI_KEYBOARDS; midiKeyboard++)
	{
		_keyboards[midiKeyboard].Process();
	}
}


void MidiKeyboards::ClearNewFlags()
{
	for (uint8_t midiKeyboard = 0; midiKeyboard < NR_OF_MIDI_KEYBOARDS; midiKeyboard++)
	{
		_keyboards[midiKeyboard].ClearNewFlags();
	}
}


void MidiKeyboards::DebugPrint()
{
	/*
	for (uint8_t midiKeyboard = 0; midiKeyboard < NR_OF_MIDI_KEYBOARDS; midiKeyboard++)
	{
		SerialUtils::PrintInt("Keyboard ", midiKeyboard);
		_keyboards[midiKeyboard].DebugPrint();
	}
	*/
}