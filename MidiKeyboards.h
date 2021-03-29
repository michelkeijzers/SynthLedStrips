#pragma once

#include <stdlib.h>
#include "SynthLedStripsTypes.h"
#include "MidiKeyboard.h"

constexpr auto NR_OF_MIDI_KEYBOARDS = 2;
constexpr auto NR_OF_MAIN_SYNTH_KEYS = 61;
constexpr auto NR_OF_MASTER_KEYBOARD_KEYS = 88;

class MidiKeyboards
{
public:
	MidiKeyboards();

	void Initialize();

	MidiKeyboard& GetMidiKeyboard(uint8_t index);

	void Process();

	void ClearNewFlags();

private:
	static MidiKeyboard _midiKeyboards[NR_OF_MIDI_KEYBOARDS];
};
